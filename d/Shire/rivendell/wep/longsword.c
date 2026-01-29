/*
 * Longsword used by the Elves of Imladris
 * Based on the draco claymore 
 * By Finwe, March 1998
 *
 * 22 feb 2007, Toby: Fixed adj 'elven'
 */
inherit "/std/weapon";
inherit "/lib/keep";
 
#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/sys/defs.h"

 
void
create_weapon()
{
    set_name(({"sword", "longsword"}));
    set_pname(({"swords", "longswords"}));
    add_name("_imladris_elven_longsword");
    set_adj( ({"elven", "runed"}));
    set_short("elven longsword");
 
    set_long("This longsword was forged in Imladris. It is " +
        "light yet looks deadly and could probably cut through " +
        "bone or armours easily. The blade is long and polished " +
        "brightly. A star is set into the base of the blade " +
        "between the pommel and the blade.\n");
 
    set_default_weapon(35,35, W_SWORD, W_SLASH | W_IMPALE, W_RIGHT);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 11500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35)); 
 
    add_item(({"runes", "rune", "elven runes", "intricate runes", 
        "elven rune"}),
        "You don't see any runes on the sword.");

    add_item("star",
        "The star is perfectly shaped, with rays emanating " +
        "from its center. It appears to be some sort of " +
        "insignia.\n");

    add_item("insignia",
        "This star represents something to do with the elves, " +
        "but you're not sure what.\n");
}


// mixed
// check_align(object what)
mixed 
wield(object weapon)
{

    /*
     * Checks alignment. if evil, player cant wield blade
     */
    if (TP->query_alignment() > -150 && 
      TP->query_race_name() !="goblin")
    {
	write("You wield the longsword and prepare " +
	  "to defend yourself.\n");
	TP->tell_watcher(QCTNAME(TP) + " wields an elven longsword.\n");
	return 1;
    }
    tell_room(ENV(TP),QCTNAME(TP)+" screams in pain and drops " +
        "an elven longsword. The sword clatters as it hits " +
        "the ground!\n", ({TP}));
    // Move the weapon to the wielders environment
    move(ENV(TP), 1);
    return "You scream in pain as a searing flash of pain " +
        "runs up your arm. You drop the "+short()+"!\n";
}


mixed
unwield(object what)
{
    return 0;
}
