#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

#define OTHER_ROOM	(OSG_DIR + "wbridge1")
#define NPC_ROOMS	({ ITH_DIR + "osgiliath/eosg5", })
#define AWARE_NEEDED    20
#define DISCOVERED_LADDER   "_gondor_i_found_osg2_ladder"

// Prototypes:
public string  long_func();
public string  exa_bridge();
public string  exa_pillars();
public string  exa_ladder();
public string  exa_river();

// Global variables:
static int     rq_stage_stored = rq_stage();

public int
query_bridge_broken()
{
    if ((rq_stage_stored <  RQ_OSGILIATH_BROKEN) ||
        (rq_stage_stored >= RQ_OSGILIATH_FIXED))
        return 0;

    return 1;
}

public void
reset_exits()
{
    if (query_bridge_broken())
	// Remove the bridge if it's broken:
        remove_exit("west");
    else if (member_array("west", query_exit_cmds()) < 0)
	// Add the bridge, but only once:
        add_exit(OSG_DIR + "ebridge2", "west", 0, 1);

    FIX_EUID;
    OTHER_ROOM->reset_room();
    NPC_ROOMS->replace_npcs();
}

public void
reset_room()
{
    int      stage = rq_stage();

    if (stage <= rq_stage_stored)
        return;

    rq_stage_stored = stage;

    reset_exits();
}

public void
create_gondor()
{
    set_short("the east end of the bridge of Osgiliath");
    set_long(long_func);
    add_exit(ITH_DIR + "osgiliath/eosg5", "east", 0);
    add_item(({"pillars", "stone pillars", }), exa_pillars);
    add_item(({"bridge","ruined bridge"}), exa_bridge);
    add_item("ladder", exa_ladder);

    reset_exits();

    add_item(({"building","buildings","ruins"}), BSN(
     "The ancient stone buildings of Osgiliath are mostly crumbled to "
     + "the ground. The ruins give you an impression of a large and lovely "
     + "city though, although that was a long time ago."));
    add_item(({"river", "anduin", "river anduin", "Anduin", }),
	     exa_river);
}

public string
exa_river()
{
    string txt;
    txt = "The great river Anduin flows by a few feet below you, its "
	+ "surface rippled by a calm breeze. Out in the river to the west "
	+ "is the central part of Osgiliath, with the ruined Royal Palace "
	+ "and the Hall of Stars. ";
    if (rq_stage_stored >= RQ_OSGILIATH_FIXED)
        txt += "The bridge leading across the Anduin to the "
            + "central islet has been newly repaired, after it was "
            + "broken during the attacks a while ago. ";
    else if (rq_stage_stored >= RQ_OSGILIATH_BROKEN)
        txt += "The bridge that once crossed the river over to "
	    + "the islet is now in ruins after the attacks by the Enemy. ";
    else 
        txt += "An ancient stone bridge crosses the river just "
	    + "west from here, allowing access to the central islet and "
	    + "the fields of Anorien on the other side. ";
    return BSN(txt);
}

public string
long_func()
{
    string  time = tod(),
    longtxt,
    moon;
    
    if (rq_stage_stored >= RQ_OSGILIATH_FIXED)
        longtxt = "Right before you to the west is the east bridge "
	    + "of Osgiliath. It seems to have been repaired recently, as "
            + "the stones it is built out of look freshly cut.";
    else if (rq_stage_stored >= RQ_OSGILIATH_BROKEN)
        longtxt = "Right before you to the west there are only some "
	    + "pillars left of the ancient stone bridge of Osgiliath. "
	    + "The recent fighting for the control of the bridge has "
	    + "destroyed it, making it rather impossible to cross the "
	    + "Anduin without a boat.";
    else
        longtxt = "Right before you to the west is the ancient stone "
	    + "bridge of Osgiliath. The construction is many centuries "
	    + "old, but still holds.";
    longtxt += " Further out in the middle of the great River "
	+ "Anduin you see the central parts of the ruined city of Osgiliath. "
	+ "Collapsed buildings of stone line the street, which continues east.";

    if (rq_stage_stored < RQ_STAGE_WAR) 
    {
        switch(time)
        {
	case "night":
	    longtxt += " Darkness covers Osgiliath now at night.";
	    switch(moon = qsmoon())
	    {
	    case "full":
		longtxt += " The full moon provides light enough to see though.";
		break;
	    case "waxing crescent":
	    case "waning crescent":
	    case "waxing gibbous":
	    case "waning gibbous":
		longtxt += " The "+moon+" moon provides some light though.";
		break;
	    default:
		longtxt += " Not even the moon is in the sky to provide some light.";
		break;
	    }
	    break;
	case "afternoon":
	    longtxt += " The afternoon sun shines down at the ruined city.";
	    break;
	case "morning":
	    longtxt += " The sun is on its way up in the morning sky to the east.";
	    break;
	case "noon":
	    longtxt += " The sun is at its peak on its way across the sky. "
		+ "It is the middle of the day in Middle-earth.";
	    break;
	case "evening":
	    longtxt += " The sun is setting in the west, colouring the sky golden red.";
	    break;
	case "early morning":
	    longtxt += " The sun is rising in the east, casting long shadows "
		+ "across the ruins of Osgiliath.";
	    break;
        }
    }
    else 
    {
        switch(time) 
        {
	case "night":
	case "early morning":
	    longtxt += " Massive dark clouds cover the sky, making it difficult "
		+ "to distinguish night and day. The clouds seem to be coming "
		    + "from the east, where Mordor lies. You suspect it is night "
			+ "now, as it is as dark as it can get.";
	    break;
	case "morning":
	case "noon":
	    longtxt += " A thick cover of clouds prevent the sun from shining "
		+ "down on Ithilien and the ruins of Osgiliath, and it is almost "
		    + "as dark as at night. You do however guess that it is probably "
			+ "morning, as it is steadily getting less dark.";
	    break;
	case "afternoon":
	case "evening":
	    longtxt += " A thick mass of clouds covers the sky, making it hard "
		+ "to see far. It is growing steadily darker, so you guess it is "
		    + "afternoon or evening, but it's really hard to tell.";
	    break;
        }
    }
    return BSN(longtxt);
}

public string
exa_bridge()
{
    string btxt;
    if (rq_stage_stored >= RQ_OSGILIATH_FIXED)
        btxt = "The stone bridge leading west across the Anduin looks "
          + "recently repaired. It had been destroyed during heavy "
          + "fighting for the control over this strategically important "
          + "place. The bridge is supported by large stone pillars, and "
          + "provides a safe crossing over the Anduin to the central "
          + "islet of Osgiliath.";
    else if (rq_stage_stored >= RQ_OSGILIATH_BROKEN)
        btxt = "Only the stone pillars out in the river are left of "
          + "the ancient bridge. The recent fighting has resulted in "
          + "the destruction of the bridge, and people will need boats "
          + "to get across. This was the only bridge across the Anduin.";
    else
        btxt = "The ancient stone bridge of Osgiliath leads west across "
          + "the mighty Anduin, to the central islet and to the lands "
          + "of Anorien. This is indeed a place of strategic importance "
          + "for any army wanting to cross the Anduin. Arching spans of "
          + "stone are supported by pillars down to the river bottom, "
          + "forming the only bridge across the Anduin River.";
    if (TP->query_skill(SS_AWARENESS) > AWARE_NEEDED  &&
        query_bridge_broken())
    {
        btxt += " You discover a rickety ladder by the side of the bridge.";
        TP->add_prop(DISCOVERED_LADDER,1);
    }
    return BSN(btxt);
}

string
exa_pillars()
{
    string txt;
    if (rq_stage_stored >= RQ_OSGILIATH_FIXED)
        txt = "Ancient stone pillars built into the river bottom "
          + "support a newly repaired bridge leading "
          + "across to the central islet. ";
    else if (rq_stage_stored >= RQ_OSGILIATH_BROKEN)
        txt = "A row of stone pillars protruding from the waters "
          + "of the river Anduin, is all that remains of the old "
          + "stone bridge that once allowed an easy crossing of "
          + "the river. ";
    else txt = "The ancient stone bridge is supported by a row of "
          + "stone pillars built into the bottom of the river. ";
    return BSN(txt);
}

string
exa_ladder()
{
    if (TP->query_prop(DISCOVERED_LADDER) && query_bridge_broken())
    {
        return BSN("You see a rickety wooden ladder leading down the side of the broken bridge.");
    }
    else
        return "You don't see any ladder here.\n";
}

int
climb_down(string str)
{
    object *others;
    int     i;

    if (query_verb() == "climb")
    {
        if (str != "down" && str != "ladder")
        {
            NF("Climb what?\n");
            return 0;
        }
    }
    if (!TP->query_prop(DISCOVERED_LADDER)  || !query_bridge_broken())
    {
        NF("You can't see any way of going down here.\n");
        return 0;
    }
    others = FILTER_PLAYERS(all_inventory(TO));
    while (i < sizeof(others)) 
    {
        others[i]->add_prop(DISCOVERED_LADDER,1);
        i++;
    }
  
    write("You climb down the rickety ladder.\n");
    set_dircmd(str);
    TP->move_living("down a rickety ladder",ITH_DIR+"osgiliath/underbridge");
    return 1;
}

void
init()
{
    ::init();
    add_action(climb_down,"climb");
    add_action(climb_down,"down");
    add_action(climb_down,"d");
}
