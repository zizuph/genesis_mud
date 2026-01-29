/*
 *    The inside base file for the outer city of Neraka
 *
 *    i_outer_city.c
 *    --------------
 *
 *    Coded .........: 97/06/26
 *    By ............: Ashlar
 *
 *    Latest update .: 97/08/18
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AR_FILE

#include "clone_npc.c"

#define CREATE "create_neraka_room"
#define RESET  "reset_neraka_room"

string quarter = "";
/*
 * dragons are supported by the following functions

 1. neraka_dragon_enter(object dragon, object from)
        Write a message saying that the dragon enters
 2. neraka_dragon_exit(object dragon, object to)
        Write a message saying that the dragon exits
 3. neraka_dragon_fail_enter(object dragon)
        Write a message saying that the dragon tries, but fails to enter
        If these function returns a string, that string is written to:
        1. the from room
        2. the to room
        3. the environment of the dragon

 neraka_dragon_prevent_enter(object dragon)
   Return true if the dragon is prevented from entering, otherwise 0.
 */

/*
 * Defaults to dragons not being able to run indoors
 */
public int
neraka_dragon_prevent_enter(object dragon)
{
    return 1;
}

/*
 * Default fail message
 */
public string
neraka_dragon_fail_enter(object dragon)
{
    return "The " + dragon->short() + " screams in fury as it realises " +
    "that it's too big for that place.\n";
}

int
prevent_enter(object ob)
{
    if (living(ob) && (ob->query_race_name() == "dragon") &&
        function_exists("neraka_dragon_prevent_enter", TO) )
    {
    	int x;

    	x = TO->neraka_dragon_prevent_enter(ob);
    	if (x)
    	{
    	    mixed s;

    	    if (function_exists("neraka_dragon_fail_enter", TO))
    	    {
    	    	s = TO->neraka_dragon_fail_enter(ob);
    	    	if (stringp(s))
    	    	{
    	    	    tell_room(E(ob), s);
    	    	}
    	    }
    	    return 1;
    	}
    }
    return ::prevent_enter(ob);
}

void
enter_inv(object ob, object from)
{
    if (living(ob) && (ob->query_race_name() == "dragon") &&
        function_exists("neraka_dragon_enter", TO) )
    {
    	string s;
    	s = TO->neraka_dragon_enter(ob, from);
    	if (stringp(s) && objectp(from))
    	{
    	    tell_room(from, s);
    	}
    }
    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    if (living(ob) && (ob->query_race_name() == "dragon") &&
        function_exists("neraka_dragon_exit", TO) )
    {
    	string s;
    	s = TO->neraka_dragon_exit(ob, to);
    	if (stringp(s) && objectp(to))
    	{
    	    tell_room(to, s);
    	}
    }
    ::leave_inv(ob, to);
}

string
query_quarter()
{
    return quarter;
}

void
set_quarter(string q)
{
    quarter = q;
}

void
add_item_inside()
{
    add_item("walls",
        "You see nothing special about the walls here.\n");
    add_item("wall",
        "Which wall do you mean?\n");
    add_item("north wall",
        "You see nothing special about the north wall.\n");
    add_item("south wall",
        "You see nothing special about the south wall.\n");
    add_item("east wall",
        "You see nothing special about the east wall.\n");
    add_item("west wall",
        "You see nothing special about the west wall.\n");
    add_item("floor","The floor is dirty, but otherwise unremarkable.\n");
    add_item("ceiling",
        "You see nothing special about the ceiling.\n");
}

void
add_item_tent()
{
    add_item(({"pit","fire pit"}),"The fire pit contains many grey ashes, as well " +
        "as burnt out wooden logs. Red glowing embers still burn within.\n");
    add_item("bedrolls","There are were the troops sleep. They are lined "+
        "along the walls of the tent. Next to them, are chests.\n");
    add_item("chests","There wooden chests contain the possessions of the "+
        "troops who live here. They are locked shut.\n");
    add_item("tent","The tent is made of black canvas.\n");
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

