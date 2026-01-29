/*******************************************************************\
| TESTER-ARMOUR.C                                                   |
\*******************************************************************/

/*
 * 06/09/04 Arandir     Created
 *
 */

#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/armour";

//-------------------------------------------------------------------

void create_armour ()
{
  set_name (({ "tester", "suit" }));
  set_short ("tester suit");
  set_long ("This is a combat tester suit. It never wears down nor breaks.\n");

  set_ac (40);
  set_am (({ 0, 0, 0 }));
  set_at (A_HEAD | A_BODY | A_ARMS | A_LEGS );

  // The following settings are likely to stop wearing down and breaking,
  // but to make sure, further blocks are installed in set_condition.

  set_likely_cond (-999999999);
  set_likely_break (-999999999);

  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_WEIGHT, 3000);
}


int set_condition (int iCondition)
{
  return (FALSE);
}


varargs void remove_broken (int iSilent)
{
  // Overriding this function prevents explicit breaking.
}

//-------------------------------------------------------------------

