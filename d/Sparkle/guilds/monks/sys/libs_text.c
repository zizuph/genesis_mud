/*******************************************************************\
| LIBS_TEXT.C                                                       |
+-------------------------------------------------------------------+
| Library functions to work with text.                              |
\*******************************************************************/

/*
 * 03/05/17 Arandir	Ported and bugfixed the text framing
 *                      function by Cirion
 * 03/09/17 Arandir     More efficient dg_capitalize_array
 * 03/12/21 Arandir     Character manipulation functions
 * 04/08/24 Arandir     Fixed dg_remove_whitespace to remove
 *                      runtime pointed out by Lucius and Valen
 * 05/04/24 Arandir     Added dg_decapitalize_array
 * 05/05/09 Arandir     Added dg_repeated_string
 * 05/05/10 Arandir     Added dg_capitalize_words
 *
 */

#include "../defs.h"

//-------------------------------------------------------------------

#define DG_FRAME_WIDTH  62

#define DG_FRAME_FILLER ({ \
  " / /\\ ",  \
  "/ /\\ \\", \
  "\\ \\/ /", \
  " \\/ / "   \
})

//-------------------------------------------------------------------

/*******************************************************************\
| Array manipulation functions                                      |
\*******************************************************************/

/*
 * Function name : dg_capitalize_array
 * Description   : Capitalizes all entries of an array.
 *
 */

string *dg_capitalize_array (string *asArray)
{
  return (map (asArray, capitalize));
}

/*
 * Function name : dg_decapitalize_array
 * Description   : Decapitalizes all entries of an array.
 *
 */

string *dg_decapitalize_array (string *asArray)
{
  return (map (asArray, lower_case));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Character manipulation functions                                  |
\*******************************************************************/


/*
 * Function name : dg_is_alpha
 * Function name : dg_is_numeric
 * Function name : dg_is_alphanumeric
 * Function name : dg_is_alphanumeric_or_space
 * Description   : Tells whether a character is certain class.
 *
 */

int dg_is_alpha (int iCharacter)
{
  return (((iCharacter >= 'A') && (iCharacter <= 'Z')) ||
          ((iCharacter >= 'a') && (iCharacter <= 'z')));
}


int dg_is_numeric (int iCharacter)
{
  return ((iCharacter >= '0') && (iCharacter <= '9'));
}


int dg_is_alphanumeric (int iCharacter)
{
  return (dg_is_alpha (iCharacter) ||
          dg_is_numeric (iCharacter));
}


int dg_is_alphanumeric_or_space (int iCharacter)
{
  return ((iCharacter == ' ') ||
          dg_is_alpha (iCharacter) ||
          dg_is_numeric (iCharacter));
}

//-------------------------------------------------------------------

/*******************************************************************\
| String manipulation functions                                     |
\*******************************************************************/

/*
 * Function name : dg_remove_whitespace
 * Description   : Removes leading and trailing whitespace from a string.
 *
 */

string dg_remove_whitespace (string sText)
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
 * Function name : dg_remove_doublespace
 * Description   : Removes double spaces from a string.
 *
 */

string dg_remove_doublespace (string sText)
{
  string sResult = "";
  int    iIndex;

  for (iIndex = 0 ; iIndex < strlen (sText) ; iIndex ++)
  {
    if (sText [iIndex] == ' ')
    {
      sResult += " ";
      do { iIndex ++; }
      while ((iIndex < strlen (sText)) &&
             (sText [iIndex] == ' '));
    }
    sResult += strchar (sText [iIndex]);
  }

  return (sResult);
}


/*
 * Function name : dg_repeated_string
 * Description   : Creates a repetitive string of a given length.
 *   sPattern      : Pattern to repeat
 *   iLength       : Length of string
 *
 */

string dg_repeated_string (string sPattern, int iLength)
{
  string sResult = sPattern;
  while (strlen (sResult) < iLength)
  {
    sResult += sResult;
  }
  return (sResult [1 .. iLength]);
}


/*
 * Function name : dg_capitalize_words
 * Description   : Capitalizes a string word by word.
 *
 */

string dg_capitalize_words (string sText)
{
  // Note that this does not work for other separator than a space

  return (implode (dg_capitalize_array (explode (sText, " ")), " "));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Text formatting functions                                         |
\*******************************************************************/

/*
 * Function name : dg_framed_text
 * Description   : Returns the text in a decorative frame.
 *   sText         : The text to put in the frame
 * Returns       : The text in a decorative frame
 *
 */

string dg_framed_text (string sText)
{
  string sFormatted;
  string *asLines;
  string sResult;
  string sLine;
  int    iLine;

  sResult  = " .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\n";
  sResult += "/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n";
  sResult += "\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n";
  sResult += " \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ /\n";

  asLines = explode (sText, "\n");
  for (iLine = 0 ; iLine < sizeof (asLines) ; iLine ++)
  {
    sLine = dg_remove_whitespace (asLines [iLine]);
    if (strlen (sLine) > DG_FRAME_WIDTH - 2)
    {
      sLine = break_string (sLine, DG_FRAME_WIDTH - 2);
    }
    asLines [iLine] = sLine;
  }
  sFormatted = implode (asLines, "\n");
  asLines = explode (sFormatted, "\n");

  asLines = ({ "" }) + asLines + ({ "" });
  while (sizeof (asLines) % sizeof (DG_FRAME_FILLER) != 0)
  {
    asLines += ({ "" });
    if (sizeof (asLines) % sizeof (DG_FRAME_FILLER) != 0)
    {
      asLines = ({ "" }) + asLines;
    }
  }

  for (iLine = 0 ; iLine < sizeof (asLines) ; iLine ++)
  {
    sLine = asLines [iLine];
    while (strlen (sLine) < DG_FRAME_WIDTH)
    {
      sLine += " ";
      if (strlen (sLine) < DG_FRAME_WIDTH)
      {
        sLine = " " + sLine;
      }
    }

    sResult += DG_FRAME_FILLER [iLine % sizeof (DG_FRAME_FILLER)] +
               sLine +
               DG_FRAME_FILLER [iLine % sizeof (DG_FRAME_FILLER)] +
               "\n";
  }

  sResult += " / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\\n";
  sResult += "/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n";
  sResult += "\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /\n";
  sResult += " `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\n";

  return (sResult);
}

//-------------------------------------------------------------------

