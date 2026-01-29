/*******************************************************************\
| LIBS_TEXT.C                                                       |
+-------------------------------------------------------------------+
| Library functions to work with text.                              |
\*******************************************************************/

/*
 * 08/01/27 Arandir     Support for removing double slashes
 * 06/03/18 Arandir	Created
 *
 */

#include "defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| String manipulation functions                                     |
\*******************************************************************/

/*
 * Function name : s_remove_whitespace
 * Description   : Removes leading and trailing whitespace from a string.
 *
 */

string s_remove_whitespace (string sText)
{
  int iBegin, iEnd;
  int iLen = strlen (sText);

  if (iLen)
  {
    for (iBegin = 0 ;
         (iBegin < iLen) && (sText [iBegin] == ' ') ;
         iBegin ++) { }

    for (iEnd = iLen - 1 ;
         (iEnd > iBegin) && (sText [iEnd] == ' ') ;
         iEnd --) { }

    return (sText [iBegin .. iEnd]);
  }
  else return (sText);
}


/*
 * Function name : s_remove_doublechar
 * Description   : Removes double characters from a string.
 *   sText         : String to remove characters from
 *   cChar         : Character to remove when double
 *
 */

string s_remove_doublechar (string sText, int cChar)
{
  string sResult = "";
  int    iIndex;
  int    cThis;
  int    cLast;

  cLast = 0;

  for (iIndex = 0 ; iIndex < strlen (sText) ; iIndex ++)
  {
    cThis = sText [iIndex];
    if ((cThis != cChar) || (cLast != cChar))
    {
      sResult += strchar (cThis);
    }
    cLast = cThis;
  }

  return (sResult);
}


/*
 * Function name : s_remove_doublespace
 *
 */

string s_remove_doublespace (string sText)
{ return (s_remove_doublechar (sText, ' ')); }

/*
 * Function name : s_remove_doubleslash
 *
 */

string s_remove_doubleslash (string sText)
{ return (s_remove_doublechar (sText, '/')); }

//-------------------------------------------------------------------

