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
object Orc1, Orc2;
object Horse,Mage,Ranger;


public string long_func();
public string trench_desc();
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
    set_short("at the west side of the fort in Ithilien");
    set_long(long_func);
    add_item(({"clearing","fort","outpost","camp"}),camp_desc);
    add_item(({"wall","walls","wooden walls"}),wall_desc);
    add_item(({"tents","tent"}),tent_desc);
    add_item(({"trench","small trench"}),trench_desc);

    add_exit(CAMP_ROOM_DIR + "fort3.c","northeast");
    add_exit(CAMP_ROOM_DIR + "fort5.c","southeast");
    add_exit(CAMP_ROOM_DIR + "fort2.c","east");
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
	longtxt = "This is the west end of this fort.  " +
	"A trench is being dug here, to provide the area from which " +
	"a large wall will be built.  " +
	"An area is being also marked off nearby, " +
	"showing where a tent will " +
	"be placed.  ";
    }

    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	longtxt = "You are standing at the west end of a camp in " +
	"in the Ithilien forest.  " +
	"The massive wall which surrounds this camp has been painted " +
	"black in most places, and decorated with drawings " +
	"of the Red Eye.  " +
	"A small black tent rests here to the west, " +
	"though it is very quiet inside.  The center of this camp " +
	"is to the east.  ";
    }


    if ((rq_stage() < RQ_OSGILIATH_ATTACK) &&
      (rq_stage() >= RQ_GANDALF_IN_BAGEND))
    {
	longtxt = "You have come to the west end of this fort.  " +
	"A massive wall rises before you, completely surrounding the " +
	"camp.  " +
	"A small tent is to the west, most likely a command center for " +
	"the outpost.  To the east is the center of this outpost.  ";
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
	return "The tent standing before you is small and green, " + 
	"and very quiet inside.\n";
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
	remove_exit("west");
	remove_exit("up");
    }

    if (rq_stage() >= RQ_GANDALF_IN_BAGEND)
    {
	if (member_array("west",query_exit_cmds()) < 0)

	    add_exit(CAMP_ROOM_DIR + "tent2","west");

	if (member_array("up",query_exit_cmds()) < 0)
	    add_exit(CAMP_ROOM_DIR + "wall3","up");
    }

    if (rq_stage() < RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Rangers))
	{
	    set_alarm(2.0, 0.0, &clone_npcs(Rangers,
		NPC_DIR + "i_ranger", 1.0));
	}
	if(!objectp(Ranger))
	{
	    Ranger = ::clone_npc(Ranger, CAMP_NPC_DIR + "hathamir");
	}
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Orc1))
	{
	    Orc1 = ::clone_npc(Orc1, CAMP_NPC_DIR + "ithil_olog");
	    Orc1->set_monster_home(CAMP_ROOM_DIR + "fort4");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, CAMP_NPC_DIR + "ithil_orc");
	}
	if (!objectp(Horse))
	{
	    Horse = ::clone_npc(Horse, CAMP_NPC_DIR + "dukano_steed");
	}

	if(!objectp(Mage))
	{
	    Mage = ::clone_npc(Mage, CAMP_NPC_DIR + "dukano");
	    Mage->command("mount _dukano_steed_");
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

