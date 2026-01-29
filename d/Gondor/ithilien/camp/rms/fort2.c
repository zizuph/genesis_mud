/*
 * Modification Log:
 * Finwe, April 2019: Updated RQ stage time so that it uses/calls rq_stage()
 * instead of rq_stage_stored.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"


public void create_gondor();
public void reset_room();

object *Rangers = allocate(2);
object Orc1, Orc2, Orc3;

public string long_func();
public string supply_desc();
public string camp_desc();
public string tent_desc();
public string wall_desc();

public void clone_npc(object npc, string npc_file);

//int rq_stage_stored = rq_stage();

public int
query_being_built()
{

    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return 0;
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return 1;
    }

    return 2;
}

public void
create_gondor()
{
    set_short("large clearing in the forest of Ithilien");
    set_long(long_func);

    add_item(({"clearing","fort","outpost","camp"}),camp_desc);
    add_item(({"wall","walls","wooden walls"}),wall_desc);
    add_item(({"tents","tent"}),tent_desc);
    add_item(({"supplies","building supplies"}),supply_desc);

    add_exit(CAMP_ROOM_DIR + "fort1","east");
    add_exit(CAMP_ROOM_DIR + "fort3","north");
    add_exit(CAMP_ROOM_DIR + "fort4","west");
    add_exit(CAMP_ROOM_DIR + "fort5","south");

    reset_room();

}

public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;

    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	longtxt = "The bulk of this clearing is completely empty, " +
	"though it does not appear that it shall stay empty for " +
	"long.  " +
	"In the middle of the clearing lies a large pile of " +
	"building supplies, which are slowly being put to " +
	"use in the creation of a hidden outpost.  " +
	"The clearing looks as if it could hold quite a few " +
	"people, once the protective walls are put in place.  ";
    }

    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	longtxt = "This fort may once have housed the defenders of " +
	"the west, but it is now firmly controlled by the Dark Lord.  " +
	"All of the tents and walls in the area have been either " +
	"painted or charred black, and crude drawings of a red eye " +
	"decorate almost every item in the area.  " +
	"The basic structures are where they were originally " +
	"placed, with tents to the north, west and south.  ";
    }

    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	longtxt = "The middle of this outpost gives a clear view " +
	"of almost everything in the fort.  " +
	"The high walls which protect the camp house a small catwalk " +
	"which allows guards to patrol the area.  " +
	"The tents along the north, west, and south walls are obviously "+ 
	"used to house the members of this outpost, while to the west " +
	"the entrance to the fort opens up into the forest.  ";
    }


    if (rq_stage() < RQ_STAGE_WAR)
    {
	switch(time)
	{
	case "night":
	    longtxt += "The area is covered in the darkness of night.  ";
	    switch(moon = qsmoon())
	    {
	    case "full":
		longtxt += "The light of the full moon illuminates the " +
		"surroundings.  ";
		break;
	    case "waxing crescent":
	    case "waning crescent":
	    case "waxing gibbous":
	    case "waning gibbous":   
		longtxt += "A bit of light is provided by " +  
		"the "+moon+" moon.  ";
		break;
	    default:
		longtxt += "No moon is visible in the sky.  ";
		break;
	    }
	    break;
	case "afternoon":
	    longtxt += "The afternoon sun casts shadows through " +
	    "the trees, as the promise of night looms near.  ";
	    break;
	case "morning":
	    longtxt += "The soft glow of the morning sun begins to push " +
	    "back the darkness of the night in Ithilien.  ";
	case "noon":
	    longtxt += "The bright noonday sun showers the land " +
	    "of Ithilien with its warm glow.  ";
	    break;
	case "evening":
	    longtxt += "The clouds overhead block what little light " +
	    "remains in the sky, as murky blackness seems to surround " +
	    "the land of Ithilien.  ";
	    break;
	case "early morning":
	    longtxt += "The darkness of night is barely broken by " +
	    "the rising of the sun.  ";
	    break;
	    break;
	}
    }
    else
    {
	switch(time)
	{
	case "night":
	case "early morning":
	case "evening":
	    longtxt += "The sky is covered by thick black clouds, " +
	    "shrouding the area in shadows during all but the noon " +
	    "hours.  " +
	    "Considering the depth of the darkness at this time, it " +
	    "is quite likely that it is night.  ";
	    break;
	case "morning":
	case "noon":
	case "afternoon":
	    longtxt += "The clouds are very thick in the sky, making " +
	    "it difficult to judge the time of day.   ";
	    break;
	}
    }
    return BSN(longtxt);
}

public string
camp_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "The clearing here is mostly barren except for the " + 
	"pile of building supplies.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "The outpost looks quite strong, with a " +
	"large wooden wall surrounding it and tents " +
	"to the north, west and south.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "This outpost has been turned into a heart of evil " +
	"right in the middle of Ithilient.\n";
    }
}


public string
tent_desc()
{

    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "Among the building supplies you think you see some " +
	"material for building tents.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "There are a few large tents to the west, " + 
	"which likely " +
	"house the members of this outpost.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "All of the tents of the fort have been " +
	"painted black " +
	"and adorned with a crude drawing of a large red eye.\n";
    }
}

public string
wall_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "There are no walls around the soon-to-be " +
	"outpost, but " +
	"judging by the supports contained among the building " +
	"supplies, this area should be well fortified before " +
	"too long.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "The wooden walls stretch some twenty feet above the " +
	"ground, with a catwalk to allow guards to patrol " +
	"the area.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "The wooden walls around the fort have been " +
	"charred to a " +
	"deep black colour, marking this area under the control " +
	"of the East.  A catwalk allows guards to patrol the area.\n";
    }
}

public string
supply_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "The pile of supplies in the clearing " + 
	"contains materials for building large walls, tents, and " +
	"other necessities for maintaining an outpost.\n";
    }
    if (rq_stage() >= RQ_GANDALF_IN_BAGEND)
    {
	return "You do not see any building supplies.\n";
    }
}

public void
reset_room()
{

    if (rq_stage() < RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Rangers))
	{
	    set_alarm(2.0, 0.0, &clone_npcs(Rangers,
		NPC_DIR + "i_ranger", 1.0));
	}
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Orc1))
	{
	    Orc1 = ::clone_npc(Orc1, CAMP_NPC_DIR + "ithil_uruk");
	    Orc1->set_monster_home(CAMP_ROOM_DIR + "fort2");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, CAMP_NPC_DIR + "ithil_uruk");
	    Orc2->set_monster_home(CAMP_ROOM_DIR + "fort2");
	}
	if (!objectp(Orc3))
	{
	    Orc3 = ::clone_npc(Orc3, CAMP_NPC_DIR + "ithil_uruk");
	    Orc3->set_monster_home(CAMP_ROOM_DIR + "fort2");
	}

    }
}

public object
clone_npc(object npc, string npc_file)
{
    int     b = 35,
    rs = random(41);

    if (objectp(npc))
	return npc;

    npc = clone_object(npc_file);
    npc->default_config_npc(b + b + rs);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

