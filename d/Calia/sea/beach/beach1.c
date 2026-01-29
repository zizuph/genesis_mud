
/*
        A beach room in the Calia west coast water area. 
        Connects to a water-kroug cave. 

	coder(s):   Amelia & Jaacar
	history:
                  Revised by Maniac  15/8/96
                  Revised by Uhclem  13/10/02,
                      added Halloween code in reset_room()
                      (also added to beach4)
*/

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int knife;

void
reset_room()
{

    /****  Begin Halloween code  ****/
    object ob;
    string *datetext = explode(ctime(time()), " ");
    if (strlen(datetext[2]) == 1)
    {
        datetext[2] = "0" + datetext[2];
    }

    /*
     *  Halloween items are deployed starting at 23:00:01 the day before
     *  Halloween so that they ready for the beginning of the game-wide
     *  scavenger hunt.  The turtle dispenser is invisible to mortals and
     *  requires no entry message.
     */

    if ((datetext[1] == "Oct" &&
        (datetext[2] == "31" ||
        (datetext[2] == "30" && datetext[3] > "23:00:00")))
        ||
        (datetext[1] == "Nov" && datetext[2] <= "03"))
    {
        if (!present("calia_turtle_dispenser", this_object()))
        {
            ob = clone_object("/d/Calia/weenware/turtle_dispenser");
            ob->move(this_object());
        }
    }
    /****  End Halloween code  ****/

    knife = 1;
}

void
create_room()
{
    set_short("A white, sandy beach");
    set_long("You are walking on a beach, with sand like white "+
        "sugar. A row of rocks blocks the path to the "+
        "north, stretching northwest a fair way out "+
        "to sea. It is the southern area of the bay that "+
        "houses the piers in the docks of Calia, which you can "+
        "see just over the rocks to the north. To the "+
        "south the beach continues, flanked on the east by "+
        "a row of sand dunes. There is a path leading up the dune "+
        "to your east. To the west the blue-green sea stretches to "+
        "the horizon. You notice a large fissure or crack "+
        "between the boulders and the side of the sand dune...\n");
		
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop(OBJ_S_SEARCH_FUN,"do_search");
	add_prop(OBJ_I_SEARCH_TIME, 5);
	add_item("waves", "The waves look very inviting.\n"); 
	
	add_item((({"gulls", "gull", "sea birds", "sea gulls"})),
		("Sea gulls apparently nest in the rocks and "+
		"are somewhat noisy as they fly around.\n"));

	add_item((({"land", "rocky land", "rocks"})),
		"@@knife_there");

	add_item((({"dock", "piers"})),
		("The beach is south of the dock area of "+
		"Gelan. You can see lots of activity there, "+
		"and occasionally a ship docks or leaves.\n"));

	add_item((({"fissure", "crack", "large crack"})),
		"The opening is dark, and it's hard to see what "+
		"might be inside.\n");

        add_item((({"dunes", "sand dunes"})),
            "To your east the slope is shallow enough for you to " +
            "climb the dunes, but to the southeast this changes. "+
            "They are fairly barren except for occasional "+
            "sea grasses.\n");

	add_item("sand",
		"The sand is very white, like sugar, "+
		"and is soft beneath your feet.\n");

	add_item((({"water", "sea", "blue-green sea"})),
		("The sea stretches before you to the west, all the "+
		"way to the horizon, where it converges with the "+
		"sky. Here the water is a light blue-green, getting darker "+
		"farther out toward the deeps.\n"));

	add_item("view",
		"There is a beautiful view of the sea that stretches "+
		"to the horizon, where it converges with the sky. "+
		"Far out you can see a sailboat tacking in the wind. "+
		"To the north over the rocks you see the busy port "+
		"of Gelan.\n");


	set_tell_time(80);
		
	add_tell("A large wave crashes on the shore.\n");
	add_tell("Sea foam washes against your feet.\n");
	add_tell("Gulls cry and swoop above you.\n");
        add_exit(SECTOR_PATH(0, 4, 0) + "wr_0_4_0","west",0,0);
	add_exit(BEACH+"sea_path3", "east", 0, 5);
	add_exit(BEACH+"beach2","south",0,0);
	reset_room();
}


string
do_search(object searcher, string str)
{
	string s;
	object k;

	if ((str=="rocks")||(str=="rocky land"))
	{
	if (knife==1)
		{
		k = clone_object(SEA_WEAPONS+"free_knife");
		k->move(this_object());
		knife = 0;
		tell_room(environment(TP),QCTNAME(TP)+" found a knife in the "+
		"rocks!\n", ({TP}));
		return "You found a knife!\n";
		}
		else
		return "You find nothing of interest there.\n";
	}
	else
	return "You find nothing of interest there.\n";
}

string
knife_there()
{
	if (!knife)
		return
		"To the north you see a line of granite rocks "+
		"that blocks further progress in that direction. The rocks "+
		"extend out into the sea, where they form a barrier "+
		"between the beach and the dock area of Gelan. There is a "+
		"large fissure or crack where the rocks meet the dune...\n";
	else
	if (knife)
	return
		"To the north you see a line of granite rocks "+
		"that blocks further progress in that direction. The rocks "+
		"extend out into the sea, where they form a barrier "+
		"between the beach and the dock area of Gelan. "+
		"There is a large fissure or crack where the rocks "+
		"meet the side of the dune ... Lying among the "+
		"rocks you spot something shiny.\n";

}

int
enter_crack(string str)
{
    notify_fail("Enter where?\n");
    if (str == "crack" || str == "fissure"||
        str == "large fissure")  {
	TP->move_living("into the fissure", BEACH+"sea_cave.c", 1);
	return 1;
    }
    return 0;
}

int
do_collect(string str)
{
    object sand;
    int num;
    if (str != "sand")
    {
        NF("What?\n");
        return 0;
    }
    sand=clone_object("/d/Calia/sea/objects/sand");
    sand->move(TP,1);
    write("You collect a handful of sand from the beach.\n");
    say(QCTNAME(TP)+" collects some sand from the beach.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_collect,"collect");
    add_action(enter_crack,"enter");
}
