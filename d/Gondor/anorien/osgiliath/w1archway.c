/*
 *	/d/Gondor/anorien/osgiliath/w1archway.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define CLIMB_DIFF   15
#define AWARE_NEEDED 35

static object  Ranger;
static int     Key_Found;

public void
create_area_room()
{
    set_areadesc("archway facing west");
    set_area("western");
    set_areaname("the ruins of Osgiliath");
    set_land("Gondor");
    set_grass("no");
    set_extraline("Some light enters through the stone archway, and beyond it, "+
    "the bridge stretches southwest on arched pillars across the river. "+
    "The room you are in is gloomy because of the dim light, and the naked "+
    "stone walls echo every sound. A collapsed stairway once lead up here, "+
      "but now it is only possible to follow a corridor southeast.");
  
    add_item("bridge", BS(
    "The current bridge must be quite recently reconstructed, as the "+
    "stones of the foundations seem to be fresh from the quarry.\n"));
    add_item(({"stairway","pile"}),BSN("The stairway collapsed long ago. But "+
    "considering the size of the stone-pile remaining, perhaps it is still "+
    "possible to climb up."));
    add_item(({"ruins","archway"}),BSN("Before you to the southwest is a "+
    "gaping archway of stone allowing exit from the ruins out onto the "+
    "bridge across the Anduin."));
    add_item("corridor",BSN("The corridor is dark, you only see that it leads "+
			  "southeast from here, and nothing more."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_I_SEARCH_TIME, 6);
    add_prop(OBJ_S_SEARCH_FUN, "search_fun");

    add_exit(OSG_DIR + "lvl1corr1", "southeast", 0, 1);
    add_exit(OSG_DIR + "wbridge3",  "southwest",  0, 1);

    reset_room();
}

public void
reset_room()
{
    Ranger = clone_npc(Ranger, NPC_DIR + "random_ranger", OSG_DIR);
    Ranger->set_random_move(15);
    Key_Found = 0;
}

public int
climb_stair(string str)
{
    if (!str) 
    { 
	NF("Climb what? Where?\n"); 
	return 0; 
    }
    if (str != "stair" && str != "pile" && str != "up" && str != "stairway") {
    NF("Climb what, where?\n"); return 0;
    }
  if (TP->query_skill(SS_CLIMB) > random(CLIMB_DIFF)) {
    write("You find a way to struggle up the heap of stones where the\n"+
    "stairway once was, and with some skilled effort you reach the\n"+
    "next floor. You wipe a little sweat off your forehead.\n");
    tell_room(OSG_DIR+"w2stairway",QCNAME(TP)+" climbs out of the stairwell from below.\n");
    TP->move_living("climbing up the collapsed stairway to the floor above",OSG_DIR+"w2stairway",1);
    return 1;
    }
  else {
    write("Struggling to find a way up the pile of stones, you discover\n"+
    "it looked easier than it actually is. You decide to reconsider\n"+
    "the possibilities, and step down from the collapsed stair.\n");
    say(QCTNAME(TP)+" tries to climb up the collapsed stairway, but fails miserably.\n",TP);
    return 1;
    }
}

public void
init()
{
    ::init();
    add_action(climb_stair, "climb");
}

private string
find_key(object pl)
{
    object  key;

    if (Key_Found) 
	return "";
    Key_Found = 1;
    if ((key = clone_object(OSG_DIR+"obj/rlib_key"))->move(pl))
	key->move(TO);
    return "You find a rusty key among the stones.\n";
}

public string
search_fun(object pl, string place)
{
    if (place == "stairway" || place == "pile") 
    {
	if (pl->query_skill(SS_AWARENESS) > AWARE_NEEDED) 
	    return find_key(pl);
    }
    return "";
}
