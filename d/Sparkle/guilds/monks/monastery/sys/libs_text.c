/*******************************************************************\
| LIBS_TEXT.C                                                       |
+-------------------------------------------------------------------+
| Library functions to work with text.                              |
\*******************************************************************/

/*
 * 03/06/25 Arandir	Ported the hitloc conversion function
 *                      by Cirion, removed overwriting of args
 * 03/11/07 Arandir     Fixed a bug in translate hitloc sometimes
 *                      mistaking head for chest or stomach
 *
 */

#include "../defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Specific translation functions                                    |
\*******************************************************************/

/*
 * Function name : m_translate_hitloc
 * Description   : Translates hitloc description to make it sexier.
 *
 */

string m_translate_hitloc (string sHitloc)
{
  string sResult;
  string sSide;

  sResult = sHitloc;
  if (sResult == "") sResult = "body";
  if (sResult == "legs") sResult = (random (2) ? "left" : "right") + " leg";

  if ((sResult == "head") && !random (5))
    sResult = random (2) ? "face" : "throat";
  if ((sscanf (sHitloc, "%s arm", sSide) == 1) && !random (2))
    sResult = random (2) ? "lower " + sResult : sSide + " shoulder";
  if ((sscanf (sHitloc, "%s leg", sSide) == 1) && !random (2))
    sResult = random (2) ? "lower " + sResult : sSide + " thigh";
  if ((sResult == "body") && !random (2))
    sResult = random (2) ? "chest" : "stomach";

  return (sResult);
}

//-------------------------------------------------------------------

