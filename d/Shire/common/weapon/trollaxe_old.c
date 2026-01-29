/*
 * axe used by Moria trolls
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"
#include "recover"



create_weapon() {
   set_name(({"axe","waraxe"}));
   set_short("huge waraxe");
   set_pshort("huge waraxes");
   set_adj(({"trollish","huge", "steel"}));
   set_long("This waraxe is made of steel and it is clear that " +
       "it is not dwarven made. The long broad shaft is made " +
       "of smooth oak and has an impressive blade set on its " +
       "top. The handle is strapped with leather to give it a " +
       "better grip when wielding this huge waraxe.\n");
    add_item("blade",
        "The blade is curved and double edge. It look sharp and " +
        "deadly even though there are some small notches in " +
        "the blade.\n");
    add_item("notches",
        "The notches are small, scattered across the blade. " +
        "There are only a couple of them and don't affect the " +
        "effectiveness of the blade. It still looks deadly.\n");
    add_item(({"shaft", "handle", "broad shaft", "long broad shaft"}), 
        "The handle is made of oak. The handle is strapped with " +
        "leather for a better grip when wielding this huge waraxe.\n");
   set_hit(35);
   set_pen(35);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_BLUDGEON);
    add_prop(OBJ_I_VOLUME,1150);
    set_keep(0);
/*
   add_prop(MAGIC_AM_MAGIC, ({ 25, "hobbit and gnome-slaying" }));
   add_prop(MAGIC_AM_ID_INFO,
	({ "The waraxe seems magical.\n", 1,
	   "The waraxe will hit additionally against hobbits and gnomes.\n", 25 }));
*/
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

