/*******************************************************************\
| LIBS_OBJ.C                                                        |
+-------------------------------------------------------------------+
| Library functions to work with objects.                           |
\*******************************************************************/

/*
 * 02/01/19 Arandir	Created
 * 04/08/23 Arandir     Fixed dg_is_singular to handle nameless objects
 *
 */

#include <macros.h>

#include "../defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Cloning functions                                                 |
\*******************************************************************/

/*
 * Function name : dg_clone_here
 * Description   : Clones an object and moves it to this object.
 *   sFile         : The name of the file to clone
 *   sInit         : Function to call in object once it is cloned
 *   sDesc         : Composite description for the room
 * Returns       : Pointer to the cloned object
 *
 */

varargs object dg_clone_here (
  string sFile,
  string sInit = "",
  string sDesc = "")
{
  object oResult;

  DG_FIXUID;

  oResult = clone_object (sFile);
  oResult->move (this_object (), MOVE_SUBLOC_ALWAYS);

  if (strlen (sInit)) call_other (oResult, sInit);
  if (strlen (sDesc)) this_object ()->dg_set_composite (oResult, sDesc);

  return (oResult);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Helper functions                                                  |
\*******************************************************************/

/*
 * Function name : dg_is_singular
 * Description   : Tells whether to use singular with an object.
 *
 */

int dg_is_singular (mixed xItem)
{
  string sName = objectp (xItem) ? (xItem->short ()) : xItem;
  int iLen = strlen (sName);

  if (iLen) return (sName [iLen - 1] != 's');
       else return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| File functions                                                    |
\*******************************************************************/

/*
 * Function name : dg_base_name
 * Description   : Returns base name of an object
 *
 */

varargs string dg_base_name (object oItem = this_object ())
{
  string *asExploded;

  asExploded = explode (MASTER_OB (oItem), "/");
  return (asExploded [sizeof (asExploded) - 1]);
}

//-------------------------------------------------------------------

