/* MCLUB - white ceremonial robe
** - Used in ceremonies by club.
** - Necessary for new member and 2 sponsors to wear one during initiation
** - Found in rooms/shconsac.c in the cabinet.
** - Seven available
** - no monetary or armour value
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
void create_armour() {
    set_name(({"white robe","robe"}));
    add_name(MCLUB_ROBE);
    set_adj("white");
    set_short("white robe");
    set_long("It is a white robe used for ceremonial purposes.\n");
    set_ac(1);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
