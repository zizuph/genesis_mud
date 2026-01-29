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
object Orc1, Orc2, Orc3, Orc4;


public string long_func();
public string trench_desc();
public string camp_desc();
public string sw_tent_desc();
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
    set_short("at the north side of the camp in Ithilien");
    set_long(long_func);
    add_item(({"clearing","fort","outpost","camp"}),camp_desc);
    add_item(({"wall","walls","wooden walls"}),wall_desc);
    add_item(({"tents","tent"}),tent_desc);
    add_item(({"trench","small trench"}),trench_desc);
    add_item(({"southwest tent","west tent","second tent"}),sw_tent_desc);
    add_exit(CAMP_ROOM_DIR + "fort2.c","south");
    add_exit(CAMP_ROOM_DIR + "fort4.c","southwest");

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
	longtxt = "This is the northern end of this small outpost.  " +
	"A small trench is being dug here, to provide the area from which " +
	"a large wall will be built.  " +
	"An area is also marked off nearby, apparently where a tent will " +
	"be placed.  There is nothing but trees to the north.  ";
    }

    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	longtxt = "You are standing at the northern edge of a fort in " +
	"the Ithilien forest.  " +
	"The massive wall which surrounds this camp has been painted " +
	"black in most places, and decorated with drawings " +
	"of the Red Eye.  " +
	"A black tent rests here as well, and another one can be seen to " +
	"the southwest.  The center of this outpost is to the south.  ";
    }


    if ((rq_stage() < RQ_OSGILIATH_ATTACK) &&
      (rq_stage() >= RQ_GANDALF_IN_BAGEND))
    {
	longtxt = "This is the northern end of this outpost.  " +
	"A massive wall rises before you, completely surrounding the " +
	"camp.  " +
	"A large tent is also here, and you can see another tent to " +
	"the southwest.  To the south is the center of this outpost.  ";
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
	    break;
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
	return "The outpost is not yet built, " + 
	"but it looks as if it will not be long before " +
	"the West gains another foothold in this area.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "This outpost looks quite strong, with a " +
	"large wooden wall surrounding it and a few tents " +
	"providing shelter from the elements.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "This fort is a grisly image of decay.  " +
	"The strong wooden walls surrounding the camp is black " +
	"in many places, and many spots appear to be long-dried " +
	"blood.  The entire place smells of evil.\n";
    }
}

public string
tent_desc()
{

    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "There is no tent here yet, just a small " +
	"area marked off for its construction.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "The tent standing before you is quite large and green, " + 
	"though it is impossible to tell what is inside.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "The tent standing before you has been painted black, " +
	"and is adorned with a crude drawing of a large red eye.\n";
    }
}

public string
wall_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "There are no walls around the soon-to-be " +
	"outpost, just a trench where it will soon stand.\n";
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
sw_tent_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "There is no tent to the southwest.\n";
    }
    if (rq_stage() >= RQ_GANDALF_IN_BAGEND)
    {
	return "It is too difficult to make out details about the " +
	"tent to the southwest, though a path leads there.\n";
    }
}

public string
trench_desc()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	return "This is just a plain trench that shall hold up a wall.\n";
    }
    if (rq_stage() >= RQ_GANDALF_IN_BAGEND)
    {
	return "You don't see that here.\n";
    }
}


public void
reset_room()
{
    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	remove_exit("north");
    }

    if (rq_stage() >= RQ_GANDALF_IN_BAGEND)
    {
	if (member_array("north",query_exit_cmds()) < 0)
	    add_exit(CAMP_ROOM_DIR + "tent1","north");
    }

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
	    Orc1 = ::clone_npc(Orc1, CAMP_NPC_DIR + "ithil_olog");
	    Orc1->set_monster_home(CAMP_ROOM_DIR + "fort3");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, CAMP_NPC_DIR + "ithil_orc");
	}
	if (!objectp(Orc3))
	{
	    Orc3 = ::clone_npc(Orc3, CAMP_NPC_DIR + "ithil_orc");
	}
	if (!objectp(Orc4))
	{
	    Orc4 = ::clone_npc(Orc4, CAMP_NPC_DIR + "ithil_orc");
	}
    }
}

public object
clone_npc(object npc, string npc_file)
{

    if (objectp(npc))
	return npc;

    npc = clone_object(npc_file);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

