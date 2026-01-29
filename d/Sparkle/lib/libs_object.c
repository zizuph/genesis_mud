/*******************************************************************\
| LIBS_OBJECT.C                                                     |
\*******************************************************************/

/*
 * 06/02/21 Arandir	Created
 *
 */

#include "defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Cloning functions                                                 |
\*******************************************************************/

/*
 * Function name : s_clone_here
 * Description   : Clones an object and moves it to this object.
 *   sFile         : The name of the file to clone
 *   sInit         : Function to call in object once it is cloned
 * Returns       : Pointer to the cloned object
 *
 */

varargs object s_clone_here (
  string sFile,
  string sInit = "")
{
  object oResult;

  S_FIXUID;

  oResult = clone_object (sFile);
  oResult->move (this_object (), MOVE_SUBLOC_ALWAYS);

  if (strlen (sInit)) call_other (oResult, sInit);

  return (oResult);
}

//-------------------------------------------------------------------

