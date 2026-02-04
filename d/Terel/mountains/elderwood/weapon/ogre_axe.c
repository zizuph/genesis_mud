/*
 * Axe coded for std_ogre.c in the elderwood forest.
 * Tomas -- May 2000
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"waraxe","axe"}));
    set_adj(({"stone","huge"}));
    set_short("huge stone waraxe");
    set_pshort("huge stone waraxes");
    set_long("The huge stone waraxe looks quite deadly. " +
       "The head of the waraxe appears to have been a solid piece of " +
       "granite chipped and and honed to a jagged, sharp edge. " +
       "The blunt edge of the axe head has been bevelled for strength " +
       "and doubles as a club if the need arises.\n");

    set_default_weapon(30, 35+random(5), W_AXE, W_BLUDGEON | W_SLASH, W_BOTH, TO);
    set_wf(TO);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, 2500);
}

/*
int
wield()
{
   if((TP->query_race_name() == "ogre"))
   {
      set_hands(W_ANYH);
      return 0;
   }
  return 0;
}


int
unwield()
{
   return 0;

}

*/