/*
 * stdio.c
 *
 *  Created on: 27-03-2012
 *      Author: ext-mlebik
 */

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

#include "serial.h"

#define FL_LEFTADJUST  0x0001U
#define FL_SIGN        0x0002U
#define FL_ZEROPAD     0x0004U
#define FL_ALTERNATE   0x0008U
#define FL_SPACE       0x0010U
#define FL_SHORT       0x0020U
#define FL_LONG        0x0040U
#define FL_LONGDOUBLE  0x0080U
#define FL_POINTER     0x0100U
#define FL_LONGLONG    0x0200U
#define FL_CHAR        0x0400U

#define MAX_WIDTH      ((SHRT_MAX - 9) / 10)

#ifdef OUTFMT_NO_FLOAT
#define BUFFER_LEN 24
#else
#define BUFFER_LEN (22 + 10)
#endif

#define WCHAR_NUL L'\0'

#define WCHAR_T_PTR(p, i)				\
   ((sizeof(unsigned short) == sizeof(WCHAR_NUL))	\
    ? (((const unsigned short *)(p))[i])		\
    : (((const unsigned int   *)(p))[i]))

#define PUTCHAR(szPutStr)						\
{									\
   if (iOutFoo(pvOutData, (const char *)szPutStr, 1U) < 0)		\
      return -1;							\
   ++iOutCount;								\
}

#define PUTSTR(szPutStr, iPutLen)		\
   {						\
   if (iPutLen > 0) \
   {									\
      if (iOutFoo(pvOutData, (const char *)szPutStr, (size_t)iPutLen) < 0) \
         return -1;							\
      iOutCount += iPutLen;						\
   }									\
}

#define PUTWSTR(szPutStr, iPutLen)					\
{									\
   while (iPutLen > 0)							\
   {									\
      iTmp = 0;								\
      while (iTmp < BUFFER_LEN && iTmp < iPutLen)			\
      {									\
	 aucBuffer[iTmp]=(unsigned char)(WCHAR_T_PTR(szPutStr,iTmp)&0xff); \
	 iTmp++;							\
      }									\
      if (iOutFoo(pvOutData, (const char *)aucBuffer, (size_t)iTmp) < 0) \
	 return -1;							\
      iOutCount += iTmp;						\
      iPutLen -= iTmp;							\
      szPutStr = (char *)((ptrdiff_t)szPutStr +				\
			  (ptrdiff_t)(iTmp * sizeof(WCHAR_NUL)));	\
   }									\
}

#define PAD(szPadStr, iPadLen)						\
{									\
   if (iPadLen > 0)							\
   {									\
      iTmp = iPadLen;							\
      while (iTmp >= 32)						\
      {									\
	 if (iOutFoo(pvOutData, (const char *)szPadStr, (size_t)32u) < 0) \
	    return -1;							\
         iOutCount += 32;						\
         iTmp -= 32;							\
      }									\
      if (iTmp)								\
      {									\
         if (iOutFoo(pvOutData, (const char *)szPadStr, (size_t)iTmp) < 0) \
            return -1;							\
         iOutCount += iTmp;						\
      }									\
   }									\
}

#define PADSPACES(iPadWidth) PAD(szSpaces, iPadWidth)
#define PADZEROS(iPadWidth)  PAD(szZeros,  iPadWidth)

static const char szSpaces[] = "                                ";
static const char szZeros [] = "00000000000000000000000000000000";

struct SSnprintf
{
    char   *cpBuf;
    size_t  tRoomFor;
};

static int
snprintfOutFoo(void *ps, const char *szStr, size_t tLen)
{
   struct SSnprintf *psSnprintf = (struct SSnprintf *)ps;

   if (szStr != NULL)
   {
      while (psSnprintf -> tRoomFor > 1 && tLen > 0)
      {
         psSnprintf -> tRoomFor--;
         tLen--;
         *psSnprintf -> cpBuf++ = *szStr++;
      }
   }
   else
   {
      if (tLen != 0)
         return -1;
      if (psSnprintf -> tRoomFor)
      {
	 psSnprintf -> tRoomFor--;
	 *psSnprintf -> cpBuf++ = '\0';
      }
   }
   return 0;
} /* snprintfOutFoo */

#define iOutFoo snprintfOutFoo
#define OUTFMT_NO_FLOAT
int _vsOutFmt(void       *pvOutData,
              const char *szFmt,
              va_list     tArg)
{
   int iOutCount = 0;

   while (*szFmt)
   {
      unsigned int   uiFlags;
      int            iWidth, iPrec, iPrefixLen, iLeadingZeros, iTmp;
      int            iStrLen;
      const char    *szStr;
      const char    *szPrefix;
      unsigned char  aucBuffer[BUFFER_LEN];

      if (*szFmt != '%')
      {
         szStr = szFmt++;

         while (*szFmt != '\0' && *szFmt != '%')
            ++szFmt;
         iStrLen = (int)(szFmt - szStr);
         PUTSTR(szStr, iStrLen);
         if (*szFmt == '\0')
            break;
      }
      szPrefix = "";
      iStrLen = iPrefixLen = 0;
      uiFlags = 0;
      ++szFmt;
      while ((*szFmt == '-') || (*szFmt == '+') ||
             (*szFmt == '0') || (*szFmt == '#') || (*szFmt == ' '))
      {
         switch (*szFmt++)
         {
            case '-': uiFlags |= FL_LEFTADJUST; break;
            case '+': uiFlags |= FL_SIGN;       break;
            case '0': uiFlags |= FL_ZEROPAD;    break;
            case '#': uiFlags |= FL_ALTERNATE;  break;
            case ' ': uiFlags |= FL_SPACE;      break;
            default:                            // error
				while (1) ;
				break;
         }
      }

      /* Get width */
	 for (iWidth = 0 ; (*szFmt >= '0') && (*szFmt <= '9') ; szFmt++)
	 {
		if (iWidth < MAX_WIDTH)
		   iWidth = iWidth * 10 + (*szFmt - '0');
	 }

      /* Get precision */
    iPrec = -1;

      /* Get size */
      switch (*szFmt)
      {
	 /*lint -save -e506 -e774 */
         case 'l':
            if (szFmt[1] == 'l')
            {
               uiFlags |= FL_LONGLONG;
               szFmt += 2;
            }
            else
            {
               uiFlags |= FL_LONG;
               ++szFmt;
            }
            break;
         case 'L':
            uiFlags |= FL_LONGDOUBLE;
            ++szFmt;
            break;
         case 't':
            if (sizeof(ptrdiff_t) > sizeof(int))
            {
               if (sizeof(ptrdiff_t) == sizeof(long))
                  uiFlags |= FL_LONG;
#ifndef OUTFMT_NO_LONG_LONG
               else if (sizeof(ptrdiff_t) == sizeof(long long))
                  uiFlags |= FL_LONGLONG;
#endif
            }
            ++szFmt;
            break;
         default:;
	 /*lint -restore */
      }

      switch (*szFmt)
      {
         case 'x': case 'X': /*lint !e616 */
         case 'o': case 'u':
         case 'd': case 'i':
         {
            unsigned long ulValue;
            char *pcChar = (char *)&aucBuffer[(sizeof aucBuffer) - 1];
#ifndef OUTFMT_NO_LONG_LONG
            unsigned long long ullValue = 0U;
#endif

            *pcChar = '\0';
            if (uiFlags & FL_LONG)
               ulValue = (unsigned long)va_arg(tArg, long);
            else if (uiFlags & FL_LONGLONG)
            {
#ifdef OUTFMT_NO_LONG_LONG
               szStr = "(no 'long long' support)";
               goto OutStr;
#else
               ullValue = (unsigned long long)va_arg(tArg, long long);
               /* Check if a 'long' can hold the value... */
               if (*szFmt == 'd' || *szFmt == 'i')
               {
                  if ((long)ullValue == (long long)ullValue)
                  {
                     /* ...if so, handle it as a long from now on. */
                     uiFlags ^= FL_LONGLONG;
                     uiFlags |= FL_LONG;
                     ulValue = (unsigned long)(long)ullValue;
                  }
                  else
                  {
                     /* Make sure we don't get trapped in the: "Don't
                      * print anything?" check below.
                      */
                     ulValue = 1;
                  }
               }
               else if ((unsigned long)(ullValue) == ullValue)
               {
                  /* ...if so, handle it as an unsigned long from now on. */
                  uiFlags ^= FL_LONGLONG;
                  uiFlags |= FL_LONG;
                  ulValue = (unsigned long)ullValue;
               }
               else
               {
                  /* Make sure we don't get trapped in the: "Don't
                   * print anything?" check below.
                   */
                  ulValue = 1;
               }
#endif
            }
            else if (sizeof(long) > sizeof(int))
            {
               ulValue = (unsigned long)(long)va_arg(tArg, int);
               if (*szFmt != 'd' && *szFmt != 'i')
                  ulValue = (unsigned long)(unsigned int)ulValue;
            }
            else
               ulValue = (unsigned long)va_arg(tArg, int);

            /* Don't print anything? */
            if (iPrec == 0 && ulValue == 0U)
	       break;

            if (*szFmt == 'd' || *szFmt == 'i')
            {
#ifndef OUTFMT_NO_LONG_LONG
               if (uiFlags & FL_LONGLONG)
               {
                  if ((long long)ullValue < 0)
                  {
                     ullValue = -(long long)ullValue; /*lint !e732 */
                     szPrefix = "-";
                     iPrefixLen = 1;
                  }
                  do
                  {
                     int iChar = ullValue % 10U;
                     ullValue /= 10U;
                     *--pcChar = (char)('0' + iChar);
                     iStrLen++;
                  } while (ullValue);
               }
               else
#endif
               {
                  if (uiFlags & (FL_CHAR | FL_SHORT))
                  {
                     ulValue = (uiFlags & FL_CHAR)
                        ? (long)(signed char)ulValue
                        : (long)(signed short)ulValue;
                  }
                  if ((long)ulValue < 0)
                  {
                     ulValue = -(long)ulValue; /*lint !e732 */
                     szPrefix = "-";
                     iPrefixLen = 1;
                  }
                  do
                  {
                     int iChar = ulValue % 10U;
                     ulValue /= 10U;
                     *--pcChar = (char)('0' + iChar);
                     iStrLen++;
                  } while (ulValue);
               }
               if (iPrefixLen == 0)
               {
                  if (uiFlags & FL_SPACE)
                  {
                     szPrefix = " ";
                     iPrefixLen = 1;
                  }
                  else if (uiFlags & FL_SIGN)
                  {
                     szPrefix = "+";
                     iPrefixLen = 1;
                  }
               }
            }
            else
            {
               const unsigned uiRadix = (*szFmt == 'u')
                  ? 10U
                  : (*szFmt == 'o') ? 8U : 16U;
               const char *acDigits = (*szFmt == 'X')
                  ? "0123456789ABCDEF"
                  : "0123456789abcdef";

#ifndef OUTFMT_NO_LONG_LONG
               if (uiFlags & FL_LONGLONG)
               {
                  do
                  {
                     *--pcChar = acDigits[ullValue % uiRadix];
                     ullValue /= uiRadix;
                     iStrLen++;
                  } while (ullValue);
               }
               else
#endif
               {
                  if (uiFlags & (FL_CHAR | FL_SHORT))
                  {
                     ulValue = (uiFlags & FL_CHAR)
                        ? (unsigned long)(unsigned char)ulValue
                        : (unsigned long)(unsigned short)ulValue;
                  }
                  do
                  {
                     *--pcChar = acDigits[ulValue % uiRadix];
                     ulValue /= uiRadix;
                     iStrLen++;
                  } while (ulValue);
               }
               if ((uiFlags & FL_ALTERNATE) && *pcChar != '0')
               {
                  if (*szFmt == 'o')
                  {
                     iStrLen++;
                     *--pcChar = '0';
                  }
                  else if (*szFmt == 'X')
                  {
                     szPrefix = "0X";
                     iPrefixLen = 2;
                  }
                  else if (*szFmt == 'x')
                  {
                     szPrefix = "0x";
                     iPrefixLen = 2;
                  }
               }
            }
            szStr = pcChar;
         }

         /* Calc number of leading zeros */
         iLeadingZeros = iStrLen < iPrec ? iPrec - iStrLen : 0;

         if (iPrec < 0 &&
             ((uiFlags & (FL_ZEROPAD | FL_LEFTADJUST)) == FL_ZEROPAD))
         {
            iTmp = iWidth - iPrefixLen - iLeadingZeros - iStrLen;
            if (iTmp > 0)
               iLeadingZeros += iTmp;
         }

         iWidth -= iPrefixLen + iLeadingZeros + iStrLen;

         if ( !(uiFlags & FL_LEFTADJUST))
            PADSPACES(iWidth);
         PUTSTR(szPrefix, iPrefixLen);
         PADZEROS(iLeadingZeros);
         PUTSTR(szStr, iStrLen);
         if (uiFlags & FL_LEFTADJUST)
            PADSPACES(iWidth);
	 break;

         case 'a': case 'A':
         case 'f':
         case 'e': case 'E':
         case 'g': case 'G':
         {
#ifdef OUTFMT_NO_FLOAT
            szStr = "(no float support)";
            goto OutStr;
#endif
         }
         case 'c':
	    /* This works equally well for 'char' as for 'wchar_t' (of
	     * the same size as short or int) since 'short unsigned
	     * int' is promoted to 'int' when passed through '...'.
	     */
            aucBuffer[0] = (unsigned char)(va_arg(tArg, int) & 0xff);
            szStr = (char *)aucBuffer;
	    /* iStrLen == 1 */
	    if (uiFlags & FL_LEFTADJUST)
	    {
	       PUTCHAR(szStr);
	       PADSPACES(iWidth - 1);
	    }
	    else
	    {
	       PADSPACES(iWidth - 1);
	       PUTCHAR(szStr);
	    }
	    break;

         case 's':
            szStr = va_arg(tArg, char *);
            if (szStr == NULL)
               szStr = "(null)";
         OutStr:
            iStrLen = 0;
	    if (!(uiFlags & FL_LONG))
	    {
	       if (iPrec < 0)
	       {
		  while (szStr[iStrLen] != '\0')
		     iStrLen++;
		  goto DoOutStr;
	       }
	       while (iPrec > iStrLen && szStr[iStrLen] != '\0')
		  iStrLen++;
	      DoOutStr:
	       iWidth -= iStrLen;
	       if (uiFlags & FL_LEFTADJUST)
	       {
		  PUTSTR(szStr, iStrLen);
		  PADSPACES(iWidth);
	       }
	       else
	       {
		  PADSPACES(iWidth);
		  PUTSTR(szStr, iStrLen);
	       }
	    }
	    else
	    {
	       if (iPrec < 0)
	       {
		  while (WCHAR_T_PTR(szStr,iStrLen) != WCHAR_NUL)
		     iStrLen++;
		  goto DoOutWStr;
	       }
	       while ((iPrec > iStrLen) &&
		      (WCHAR_T_PTR(szStr,iStrLen) != WCHAR_NUL))
	       {
		  iStrLen++;
	       }
	      DoOutWStr:
	       iWidth -= iStrLen;
	       if (uiFlags & FL_LEFTADJUST)
	       {
		  PUTWSTR(szStr, iStrLen);
		  PADSPACES(iWidth);
	       }
	       else
	       {
		  PADSPACES(iWidth);
		  PUTWSTR(szStr, iStrLen);
	       }
	    }
	    break;

         case '%':
	    PUTCHAR("%");
	    break;

         case 'n':
            if (uiFlags & FL_CHAR)
               *va_arg(tArg, signed char *) = (signed char)iOutCount;
            else if (uiFlags & FL_SHORT)
               *va_arg(tArg, short *) = (short)iOutCount;
#ifndef OUTFMT_NO_LONG_LONG
            else if (uiFlags & FL_LONGLONG)
               *va_arg(tArg, long long *) = (long long)iOutCount;
#endif
            else if (uiFlags & FL_LONG)
               *va_arg(tArg, long *) = (long)iOutCount;
            else
               *va_arg(tArg, int *) = (int)iOutCount;
	    break;

         default:
	    szStr = szFmt;
	    while(*--szStr != '%' && iStrLen < 16)
	       ++iStrLen;
	    PUTSTR(szStr, iStrLen + 2);
	    break;
      }
      ++szFmt;
   }
   if (iOutFoo(pvOutData, NULL, 0) < 0)
      return -1;
   return iOutCount;
} /* _vsOutFmt */

int sprintf(char *acBuf, const char *szFmt, ...)
{
   va_list tArg;
   int iOutCnt;
   struct SSnprintf ssnprintf;

   ssnprintf.cpBuf    = acBuf;
   ssnprintf.tRoomFor = (size_t)UINT_MAX;

   va_start(tArg, szFmt);
   iOutCnt = _vsOutFmt((void *)&ssnprintf, szFmt, tArg);
   va_end(tArg);
   return iOutCnt;
} /* sprintf */

int printf(const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[200] = {0};

	va_start(args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = sprintf(printbuffer, fmt, args);
	va_end(args);

	/* Print the string */
	serial_puts(printbuffer);
}

