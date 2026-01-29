/*******************************************************************\
| TESTER-WEAPON.C                                                   |
\*******************************************************************/

/*
 * 06/09/03 Arandir     Created
 *
 */

#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/weapon";

//-------------------------------------------------------------------

void create_weapon ()
{
  set_name (({ "tester", "sword" }));
  set_short ("tester sword");
  set_long ("This is a combat tester sword. It never dulls nor breaks.\n");

  set_default_weapon (40, 40, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);

  // The following settings are likely to stop dulling and breaking,
  // but to make sure, further blocks are installed in did_hit.

  set_likely_dull (-999999999);
  set_likely_break (-999999999);

  add_prop(OBJ_I_VOLUME, 1000);
  add_prop(OBJ_I_WEIGHT, 2000);
}


varargs int did_hit (int iAttack, string sHitloc, int iPHurt, object oEnemy, int iDamageType, int iPHit, int iDamage, int iHitloc)
{
  // The overriden did_hit starts with hits ++ and derives
  // dulling and breaking of the weapon from the value of hits.

  hits --;

  return (::did_hit (iAttack, sHitloc, iPHurt, oEnemy, iDamageType, iPHit, iDamage, iHitloc));
}


varargs void remove_broken (int iSilent)
{
  // Overriding this function prevents explicit breaking.
}

//-------------------------------------------------------------------

