/*
 *  temple2.c
 *
 *  This is a room for the druid temple in Mithas, it is
 *  the exit of the temple.
 *
 *  Created by Carnak, January 2016
 */
#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_IN;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#include "./local.h"


create_mithas_room()
{
    set_short("Temple entrance");
    set_long("@@long_desc");
	
    add_exit(TDIR +"temple1", "west", 0);
    add_exit(TDIR +"temple3", "east", 0);
    add_exit("", "out", "@@open_gates");

    add_item(({"floor","ground","weeds","grass","rocks","dirt",
	"granite rocks"}),
    "The floor is tiled with smooth rocks and covered in dirt, some "+
    "grass and weeds have emerged from beneath the granite rocks.\n");
    
    add_item(({"ancient ruin","ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"hallway"}),
    "You are in the midst of the hallway, it stretches east and "+
    "westwards. The hallway is nearly void of decorations.\n");
    
    add_item(({"decorations","decor"}),
    "In the far corners of the hallway you can glance floor "+
    "mounted candelabras.\n");

    add_item(({"candelabras","candelabra"}),
    "You should move closer if you are interested in the decor.\n");

    add_item(({"bowls","herbs","incense","burnt incense"}),
    "Three bowls have been placed upon mounds of stone, the "+
    "center bowl is empty but shows signs of burnt incense. The "+
    "two other bowls contain a mix of various dried herbs, "+
    "filling the air with a calming scent.\n");

    add_item(({"mounds"}),
    "There are three mounds formed from granite stones, upon "+
    "which bowls have been placed.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");

    add_item(({"north wall","northern wall","wall","cracks"}),
    "The north wall stretches east and westwards along the "+
    "hallway. The stones appear to be from the same source "+
    "as the rest of the walls, however the wall stops just "+
    "short of the roof.\n");

    add_item(({"wooden roof","roof","hatch","ceiling"}),
    "The wooden roof appears to be in good condition. A hatch "+
    "in the roof has been propped open, allowing light to "+
    "spread throughout the temple during the day.\n");

    add_item(({"walls","roots"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability.\n");

    add_item(({"gates","wooden gates","sturdy gates",
	"sturdy wooden gates"}),
    "The sturdy wooden gates hang on hinges, opening outwards. "+
    "An iron latch has been secured to the wall, which could be "+
    "lowered to secure the temple.\n");
	
    add_item(({"latch"}),
    "An iron latch has been secured to the wall, which could be "+
    "lowered to secure the temple. It appears to have rusted in "+
    "place.\n");
	
    add_item(({"entrance","entryway"}),
	"This is the entrance of an ancient ruin, in the midst of a "+
	"hallway nearly void of decorations. Three bowls have been "+
	"placed upon mounds of stones heaped against the north wall "+
	"infront of the entryway.\n");

    add_cmd_item(({"gate","gates"}),"open","@@open_gates");
    add_cmd_item(({"latch"}),"lower","@@lower_latch");

}

string
long_desc()
{
    return tod_desc()+ "" +season_desc()+
    "This is the entrance of an ancient ruin, in the midst of a "+
    "hallway nearly void of decorations. Three bowls have been "+
    "placed upon mounds of stones heaped against the north wall "+
    "infront of the entryway. A faint scent of herbs permeate the "+
    "area, forming a sense of serenity.\n";
}

int
open_gates()
{
    write("You push the gates open with a creaking sound, and "+
    "leave the temple.\n");
    say("The gates creak as " + QTNAME(TP) + " leaves the "+
    "temple, closing the gates behind " + HIM(TP) + ".\n");

    TP->move_living("M",TDIR + "forest101.c", 1, 0);

    write("You close the gates behind you.\n");
    say(QCTNAME(TP) + " arrives from within the temple, closing "+
    "the doors behind "+HIM(TP)+".\n");
    return 1;
}

int
lower_latch()
{
    write("You attempt to lower the latch, but fail. The latch "+
    "appears to have rusted in an upwards position.\n");
    say(QCTNAME(TP) + " attempts to lower the latch to lock "+
    "the gates, but fail.\n");
    return 1;
}