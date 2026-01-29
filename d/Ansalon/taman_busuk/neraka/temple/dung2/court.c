/* This is the Inquisitor's court where the Inquisitor will hold court.
 * In the check_runes functon, I would like to see the runes being 
 * impossible to understand what they are if someone other than a full 
 * priest is looking at them.
 *
 * Also a door should be added behind the tapestry which leads to the
 * Inquisitor's private chamber. I have not coded that part because I
 * thought we would not need it until there is an actual Inquisitor.
 * Also I thought it would be a nice touch if the first Inquisitor had 
 * the chance to come up with the interior of that room.
 *
 * Edited by mortis 02.2006 to change :::: to :: on line 110.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include <macros.h>

inherit TEMPLE + "std_temple.c";

object gDoor;

void
create_temple_room()
{
    ::create_temple_room();

     set_short("Circular chamber");
    set_long("You are standing in a large circular room. Opposite the " +
        "arched entrance is a dais with a large oak chair standing on " +
        "it. Along the southern wall are two rows of benches and " +
        "standing in the centre of the room is a simple wooden chair " +
        "facing the dais. On the wall behind the oak chair hangs a " +
        "large tapestry.\n");

    add_item(({"entrance", "arched entrance"}),
        "Beyond the arched entrance you see a narrow corridor.\n");

    add_item(({"dais", "stone dais"}),
        "Three steps lead up to the stone dais which is semi-circular. " +
        "On it lies a blood-red carpet and a large dark oak chair has " +
        "been placed on the centre of it.\n");

    add_item(({"carpet", "blood-red carpet"}),
        "The carpet which lies on the dies is thick and blood-red in " +
        "colour. It has a darker line running three inches from the " +
        "edge.\n");

    add_item(({"line", "darker line"}),
        "The line is an inch wide and consists of black runes woven " +
        "into the carpet.\n");

    add_item(({"runes", "black runes"}),
        "@@check_runes");

    add_item(({"chair"}),
        "Which chair do you want to look at? The large oak chair or " +
        "the simple wooden one?\n");

    add_item(({"large chair", "oak chair", "large oak chair"}),
        "This large oak chair dominates the room as it stands on the " +
        "stone dais. It seems to be carved from a single piece of wood " +
        "and it has become so dark through time that it appears to be " +
        "black. The back of the chair is ornamently carved as are the " +
        "armrests.\n");

    add_item(({"back", "back of the chair"}),
        "The back of the chair has been carved into a large dragon " +
        "with its wings half spread out as if to take flight.\n");

    add_item(({"armrest", "armrests"}),
        "The ends of the armrests are carved into dragon claws " +
        "gripping the chair firmly.\n");

    add_item(({"dragon", "large dragon", "wings", "claws", "dragon claws"}),
        "It is so well carved that every little detail can be seen " +
        "clearly.\n");

    add_item(({"benches", "bench", "rows of benches"}),
        "The benches are mad eof wood and are unadorned.\n");

    add_item(({"wooden chair", "simple chair", "simple wooden chair"}),
        "This is a very simple and unassuming chair. It is standing " +
        "in the very centre of the room facing the dais.\n");

    add_item(({"tapestry", "large tapestry"}),
        "@@check_tapestry");

    add_item(({"constellation", "stars"}),
        "The stars on the tapestry are arranged to show the " +
        "constellation of the Dark Queen.\n");

    add_item(({"nightsky"}),
        "The nightsky on the tapestry is woven with pitch-black silk " +
        "thread.\n");

    add_exit( DUNGTWO + "torture.c", "north");
    add_exit( DUNGTWO + "corr6.c", "east");

    gDoor = clone_object( DOOR + "inquisitor1.c");
    gDoor->move(this_object());
}

varargs public mixed
long(string str)
{
    string l;
    mixed lg;
    
    lg = ::long(str);
    if (stringp(str))
        return lg;

    l = query_long();
    if (gDoor->query_known(this_player()))
    {
        if (gDoor->query_open())
            l += gDoor->standard_open_desc();
        else
            l += gDoor->standard_closed_desc();
    }
    
    return (l + exits_description());
}

int
do_unveil_door(string arg)
{
    if (!arg && arg != "tapestry" && arg != "large tapestry")
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    write("You " + query_verb() + " the large tapestry " +
        "to unveil a door behind it.\n");
    say(QCTNAME(this_player()) + " does something with the " +
        "large tapestry.\n");

    gDoor->make_me_known(this_player());

    return 1;
}

void
init()
{
    ::init();
    
    add_action(do_unveil_door, "lift");
    add_action(do_unveil_door, "move");
    add_action(do_unveil_door, "push");
    add_action(do_unveil_door, "pull");
}

string
check_tapestry()
{
    string str;

    str = "The tapestry is woven with black silk and silver metal " +
        "thread. It is four by six feet and shows a constellation " +
        "in the nightsky.";
        
    if (this_player()->query_skill(SS_AWARENESS) < 35)
        return str + "\n";
    
    return str + " It would appear this tapestry is set up to hide " +
        "something.\n";
}

string
check_runes()
{
    if (this_player()->query_guild_level() < GUILD_LEVEL_HIGH_PRIEST)
        return "You study the runes but you cannot understand what they " +
            "mean.\n";

    return "These are runes of divination and protection.\n";
}
