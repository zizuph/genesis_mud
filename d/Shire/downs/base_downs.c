/*
 * Base file for the Barrow downs
 * Original concept and area by Dondon, October 1993
 * Expanded and enlarged by Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

void create_barrows_room() {}

//string what_time;


public void
create_room()
{
    set_short("A tunnel inside a barrow beneath the Downs");

    add_item(({"ground", "floor"}),
        "The ground is covered with crisscrossed stone blocks. " +
        "Once fine looking and smooth, the blocks are chipped and " +
        "cracked from countless centuries.\n");
    add_item(({"walls", "wall"}),
        "The walls are made of stone blocks. They are chipped and " +
        "cracked. Faint, painted decorations adorn the walls.\n");
    add_item(({"decorations", "faint painted decorations", "painted decorations",
            "faint, painted decorations"}),
        "The decorations are happy scenes of days long past, " +
        "probably of the people once buried here. Now, the " +
        "decorations are faded, leaving only a faint impression of " +
        "their glory.\n");
    add_item("ceiling",
        "The ceiling is rough looking. It is made from stone blocks " +
        "that are now cracked. Some roots hang from the ceiling " +
        "and have cracked the stone blocks leaving a rough looking " +
        "surface.\n");
    add_item("roots",
        "The roots are of various sizes. Some appear to be tree, " +
        "shrub, and grass roots.\n");
    add_item(({"stone blocks", "blocks", "stone block", "block"}),
        "The stone blocks are grey. They were once smooth and " +
        "level, but now are cracked and chipped from the passage " +
        "of time. They make up the walls, ceiling and floor.\n");
    add_item(({"piles of dirt", "piles of earth", "clods of dirt",
            "clods of earth", "dirt", "earth"}),
        "The piles of dirt are dark and lay in various sized " +
        "piles about the room. They have a rich, loamy look to them.\n");


    set_room_tell_time(60+random(120));
    add_room_tell("A cold breeze blows past you.");
    add_room_tell("A cold wind rushes past you.");
    add_room_tell("A feeling of death permeates the area.");
    add_room_tell("Something in the distance whispers: Come to me...");
    add_room_tell("Something in the distance whispers: Follow me. " +
        "I will reward you.");
    add_room_tell("Water drips in the distance.");

    create_barrows_room();
}


string psg_desc1()
{
    return "A tunnel inside a barrow beneath the Downs. The " +
        "passage smells dusty and of death. It is cold, wet, and " +
        "gloomy. The walls are made of stone that is cracked and " +
        "crumbling. Roots grow from cracks in the ceiling. ";
}

string psg_desc2()
{
    return "This is beneath the Downs inside a dark tunnel inside " +
        "a barrow. The passage smells dusty and of death. The " +
        "walls are made of crumbly stone. Roots grow from cracks " +
        "in the ceiling in this cold and gloomy place. ";
}

string psg_desc3()
{
    return "Somewhere inside a dark tunnel beneath the Downs " +
        "east of the Great Forest. Roots grow from the ceiling, " +
        "pushing stones aside. The tunnel is dark and dank, an " +
        "evil and haunted place, some say. ";
}

string psg_desc4()
{
    return "You stand in a dark tunnel. The walls are made of " +
        "stones that are cracked and weathered from countless " +
        "ages. The passage is moist from dripping water and very " +
        "cold. ";
}


public string long_desc()
{
    string desc;

    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
	    desc +=extraline;

    if (functionp(vbfc_extra))
	    desc +=vbfc_extra();

    return (desc);
}
