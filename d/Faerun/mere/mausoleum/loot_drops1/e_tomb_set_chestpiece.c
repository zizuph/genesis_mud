/*  /d/Ravenloft/droptables/fos_drops/e_tomb_set_chestpiece.c
 *
 *  Epic armouritem. Drops from chest in the
 *  Forest of Shadows, tomb.
 *
 *  Nerull, 2015
 *
 */

inherit "/std/armour";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

// Custom name.
string wname = "Jakredak";

void
create_armour()
{
    set_name("chestpiece");
    set_adj(wname);
    add_adj("bone");

    set_short(wname + "bone chestpiece");
    set_pshort(wname + "bone chestpieces");

    set_long("Pulsing with necromantic powers this chestpiece "
    +"fulfills " + wname + "'s prayer. " + wname + "'s ribcage has been "
    +"removed and cast in adamantine to create this awful looking "
    +"chestpiece. Chipped and broken ribs can easily be seen "
    +"under the metal coating. Magic allows the chestpiece to "
    +"breathe. Rumours say that if worn, it will breath for you "
    +"allowing you the endurance of a frost giant. This chestpiece "
    +"is extremely cold.\n");
    
    add_item(({"ribcage", "ribs", "cage",}), "The ribcage of "+wname+" is "
    +"massive. It has been formed into some unholy platemail armour "
    +"through some necormantic process. It shimmers, coated with "
    +"adamtinium.\n");
    
    set_default_armour(TOMB_E_CHESTPIECE_AC, A_BODY, 0, this_object());

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This armour is enchanted to give "
        + "better protection.\n",1, }));

    add_prop(OBJ_S_WIZINFO, "This is a Rare armour dropping from monsters in "
        + "the Forest of Shadows, Ravenloft. "
        + "It is slightly enchanted to offer better ac.\n");

    add_prop(OBJ_I_VALUE, TOMB_E_CHESTPIECE_VALUE);
    add_prop(OBJ_I_WEIGHT, TOMB_E_CHESTPIECE_WEIGHT);
    add_prop(OBJ_I_VOLUME, TOMB_E_CHESTPIECE_VOLUME);
}


