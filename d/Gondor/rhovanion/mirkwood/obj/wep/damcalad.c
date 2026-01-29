/*
 * Spider Treasure - Sword
 * Varian - August 2015
 *
 * Damcalad, a sword which has a 10% chance to blind an
 * opponent on every successful hit.
 *
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <wa_types.h>

int do_swing(string str);
int do_read(string str);

void
create_weapon()
{
    
    set_name(({"sword"}));
    add_name(({"damcalad", "longsword"}));
    set_short("slender longsword");
    set_adj(({"slender"}));
    set_long("The blade of this sword is long and slender, obviously the " +
        "work of a master craftsman. When you grasp the hilt, the sword " +
        "feels almost alive in your hands, as if struggling to sing " +
        "its song to the world. Carved into the base of the hilt, you " +
        "spot an Elvish inscription.\n");
    	    
    set_hit(43);
    set_pen(39);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
        
}

init()
{
    ::init();
    add_action("do_swing","swing");
    add_action("do_read", "read");
}

int
do_swing(string str)
{
    notify_fail("Swing what? Your sword?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Expertly gripping your slender longsword, you swing it in a " +
        "series of wide, deadly arcs around your body.\n");
    SAYBB(" swings " + this_player()->query_possessive() + " slender " +
        "longsword around in a dazzling display of swordsmanship.\n" );
    return 1;
}

int
do_read(string str)
{
    notify_fail("Were you trying to read the inscription?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("The Elvish script seems to spell out the name Damcalad.\n");
    return 1;
}