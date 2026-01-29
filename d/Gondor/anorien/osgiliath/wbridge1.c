/*
 * Modification Log:
 * Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *   instead of rq_stage_stored.
 */ 
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define OTHER_ROOM		(ITH_DIR + "osgiliath/eosgbridge")
#define AWARE_NEEDED    20
#define DISCOVERED_LADDER    "_gondor_i_found_osg_ladder"

public string  exa_bridge();
public string  exa_ladder();
public string  long_func();

// int     rq_stage_stored = rq_stage();

public int
query_bridge_broken()
{
    if ((rq_stage() <  RQ_OSGILIATH_BROKEN) ||
        (rq_stage() >= RQ_OSGILIATH_FIXED))
        return 0;

    return 1;
}

void
reset_exits()
{
    if (query_bridge_broken())
        remove_exit("northeast");
    else if (member_array("northeast", query_exit_cmds()) < 0)
	// add the bridge only once!
        add_exit(OSG_DIR+"wbridge2", "northeast", 0, 1);

    FIX_EUID
    OTHER_ROOM->reset_room();
}

void
reset_room()
{
//    int      stage = rq_stage();
//
//    if (stage <= rq_stage_stored)
//        return;
//
//    rq_stage_stored = stage;

    reset_exits();
}

public void
create_gondor()
{
    set_short("the west end of the bridge of Osgiliath");
    set_long(long_func);
    add_exit(OSG_DIR+"wosg3","southwest", 0, 1);
    add_item(({"bridge","ruined bridge"}), exa_bridge);
    add_item("ladder", exa_ladder);

    reset_exits();
}

public string
long_func()
{
    string  time = tod(),
            longtxt,
            moon;

    if (rq_stage() >= RQ_OSGILIATH_BROKEN)
        longtxt = "You are standing at the edge of the ruined bridge of Osgiliath.";
    else if (rq_stage() >= RQ_OSGILIATH_FIXED)
        longtxt = "You are standing at the west end of the repaired bridge of Osgiliath.";
    else
        longtxt = "You are standing at the west end of the ancient bridge of Osgiliath.";
    longtxt += " Further northeast on an islet in the river Anduin "
      + "are the ruins of the central parts of Osgiliath. The west parts "
      + "of the ruined city are accessible along the street leading southwest.";

    if (rq_stage() < RQ_STAGE_WAR) 
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
                  + "down on Anorien and the ruins of Osgiliath, and it is almost "
                  + "as dark as at night. You do however guess that it is "
                  + "probably morning, as it is steadily getting less dark.";
                break;
            case "afternoon":
            case "evening":
                longtxt += " A thick mass of clouds covers the sky, making it "
                  + "hard to see far. It is growing steadily darker, so you "
                  + "guess it is afternoon or evening, but it's really hard to tell.";
                break;
        }
    }
    return BSN(longtxt);
}

public string
exa_bridge()
{
    string btxt;

    if (rq_stage() >= RQ_OSGILIATH_FIXED)
        btxt = "The stone bridge leading across the Anduin looks "
          + "like it has been recently repaired, as it had been "
          + "destroyed during the War. Now it is again possible to "
          + "reach the central parts of Osgiliath, and Ithilien, by foot.";
    else if (rq_stage() >= RQ_OSGILIATH_BROKEN)
        btxt = "There are only the pillars left of the ancient stone "
          + "bridge. The recent fighting in the War destroyed the "
          + "bridge spans, and now people will have to use boats or "
          + "rafts to cross the mighty Anduin river.";
    else
        btxt = "The ancient stone bridge of Osgiliath leads northeast "
          + "across the mighty Anduin to the central islet and to the "
          + "lands of Ithilien. This is indeed a place of strategic "
          + "importance for any army wanting to cross the Anduin. "
          + "Arching spans of stone are supported by pillars built "
          + "down to the river bottom, forming the only bridge "
          + "across the Anduin river.";
    if ((TP->query_skill(SS_AWARENESS) > AWARE_NEEDED) &&
        query_bridge_broken())
    {
        btxt += " You discover a rickety ladder by the side of the bridge.";
        TP->add_prop(DISCOVERED_LADDER, 1);
    }
    return BSN(btxt);
}

public string
exa_ladder()
{
    if ((TP->query_prop(DISCOVERED_LADDER)) &&
        query_bridge_broken())
    {
        return BSN("You see a rickety wooden ladder leading down the "
          + "side of the broken bridge.");
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
    if (!TP->query_prop(DISCOVERED_LADDER)  ||
        !query_bridge_broken())
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
    TP->move_living("down a rickety ladder",OSG_DIR+"underbridge");
    return 1;
}

void
init()
{
    ::init();
    add_action(climb_down, "climb");
    add_action(climb_down, "d");
    add_action(climb_down, "down");
}

