
/*
 *	coder(s):              Amelia
 *      history:               coded 5/5/95
 *      Minor alterations by maniac 18/8/96
 */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/herbsearch.h"
#include "defs.h"

void
reset_herb_room()
{
    set_searched(random(3));
}

void
reset_room()
{
    reset_herb_room();
}

void
create_room()
{
	set_short("Top of the dune");
	set_long("You look out from the top of the dunes.  "+
		"You feel a fresh salt breeze in your face. "+
		"Below to your west you look down on the blue-green "+
		"sea, which extends all the way to the horizon. Far out "+
		"to sea there are many rowing boats of many colours. "+
		"The view is magnificent from here. The sun "+
		"sparkles on the waves. Immediately to your south " +
                "is a small grass hut. Back to the southeast you "+
		"can see a purple moor that stretches all the way to "+
		"the foothills of Mount Kyrus.\n");

	add_item((({"grass", "pampas grass", "clumps"})),
		("The pampas grass has graceful narrow fronds, and "+
		"tall stalks with long white tassels atop them.\n"));
	add_item((({"moor", "moorland"})),
		("The purple moor looks somewhat barren but "+
		"yet interesting and mysterious.\n"));
	add_item(({"boat", "boats", "rowing boats", "fishing boats" }),
		"They seem to be small fishing boats, spread out over " +
                "a wide area of sea.\n"); 
	add_item("view",
		"There is a spectacular view from here. You can look "+
		"in (at) all four directions.\n");
	add_item((({"east", "e"})),
		("Away to the east, you see a cobbled road that "+
		"extends from Gelan to the north to "+
		"rolling heather-strewn moorland to the southeast.\n"));
	add_item((({"west","w", "sea"})),
		("Below to the west the beautiful blue-green Calian "+
		"sea extends all the way to the horizon, where "+
		"sea and sky converge. Far out you can see "+
		"little boats of many colours. "+
		"Sun sparkles on the waves, and sea birds fish there. "+
		"Waves pound the beach, peacefully and rhythmically.\n"));
	add_item((({"north", "n", "gelan"})),
		("To the north you see the busy docks of Gelan. Every "+
		"now and then, a ship arrives or departs.\n"));
	add_item((({"south", "s"})),
		("To the south you see more sand dunes. To the southeast "+
		"you see moorland stretching to the foothills of Mount " +
                "Kyrus. The mountain ridge extends downwards "+
                "to the sea. Nearby is a small grass hut.\n")); 

    add_item("hut", "The hut appears to be made of grass, and "+
        "is standing on a sand dune a little south of here.  "+
        "It appears as if you could enter it from here.\n");

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_exit(BEACH+"sea_path2", "east");
	add_exit(BEACH+"beach1", "west");

	set_tell_time(80);
	add_tell("Sea breezes ruffle your hair.\n");
	add_tell("Waves crash on the shore below you.\n");
	add_tell("A sea gull soars overhead.\n");

    reset_herb_room();
    seteuid(getuid(this_object()));
    set_search_places(({"grass", "pampas grass", "clumps"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERBS+"bch_willow");
    add_herb_file(HERBS+"cattail");
    add_herb_file(HERBS+"horsetail");
    add_herb_file(HERBS+"poison_ivy");
    add_herb_file(HERBS+"salt_wort");
}


int
enter_hut(string str)
{
    notify_fail("Enter what?  The hut?\n");
    if (str == "hut")
    {
        TP->move_living("into the hut", BEACH+"hut.c", 1);
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(enter_hut,"enter");
}

