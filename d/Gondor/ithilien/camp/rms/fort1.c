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


#define ITHILIEN_CAMP_ENTRANCE_WARNING "_ithilien_camp_entrance_warning"

public void create_gondor();
public void reset_room();

object *Rangers = allocate(4);
object Orc1, Orc2, Orc3, Orc4;


public string long_func();
public string tree_desc();
public string body_desc();
public string supply_desc();
public string camp_desc();
public string tent_desc();
public string wall_desc();
public int warning();

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
    set_short("between two large trees in Ithilien");
    set_long(long_func);

    add_item(({"tree","trees","path","here"}), tree_desc);
    add_item(({"body","rotting body","humanoid","rotting humanoid"}),
      body_desc);
    add_item(({"clearing","fort","outpost","camp"}),camp_desc);
    add_item(({"wall","walls","wooden walls"}),wall_desc);
    add_item(({"tents","tent"}),tent_desc);
    add_item(({"supplies","building supplies"}),supply_desc);

    /*
	add_exit(CAMP_ROOM_DIR + "fort2.c","west");
    */
    add_exit(CAMP_ROOM_DIR + "fort2","west",warning,1);
    add_exit(ITH_DIR + "road/nr3","east");

    reset_room();

}

public int
warning()
{


    if (TP->query_prop(ITHILIEN_CAMP_ENTRANCE_WARNING))
    {
	write("You bravely enter the camp!\n");
	return 0;
    }

    write("The camp may be highly dangerous, with terrible " +
      "things that will attempt to hunt you down and slay " +
      "you like vermin!  Best think twice before entering!\n");
    TP->add_prop(ITHILIEN_CAMP_ENTRANCE_WARNING, 1);
    return 1;
}


public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;

    if (rq_stage() < RQ_GANDALF_IN_BAGEND)
    {
	longtxt = "You are standing between two trees in the forest " +
	"of Ithilien.  " +
	"A clearing stretches out to the west, where several " +
	"building supplies are laying around.  " +
	"It appears as if this area is to be an outpost of " +
	"some sort.  ";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	longtxt = "You are standing at the edge of a fort in " +
	"in the Ithilien forest.  " +
	"Hanging from a nearby tree is a rotting body of " +
	"some humanoid, its foul stench casting a pall on " +
	"the area.  The outpost is surrounded by a wall of " +
	"wood, and extends to the west.  ";
    }

    if ((rq_stage() < RQ_OSGILIATH_ATTACK) &&
      (rq_stage() >= RQ_GANDALF_IN_BAGEND))
    {
	longtxt = "You are standing at the entrance to a " +
	"small outpost in the forest of Ithilien.  " +
	"The walls of the outpost surround the clearing " +
	"to the west, where a few tents house the members " +
	"of the fort.  ";
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
	    longtxt += "The bright noon day sun showers the land " +
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
	return "The clearing to the west is full of " + 
	"building supplies, " +
	"which are likely going to be used to turn this area " +
	"into a fort of some sort.\n";
    }
    if ((rq_stage() >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage() < RQ_OSGILIATH_ATTACK))
    {
	return "The outpost to the west looks quite strong, with a " +
	"large wooden wall surrounding it and a few tents " +
	"providing shelter from the elements.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "The fort to the west is a grisly image of decay.  " +
	"The strong wooden walls surrounding the camp is black " +
	"in many places, and many spots appear to be long-dried " +
	"blood.  The entire place smells of orcs.\n";
    }
}

public string
body_desc()
{
    if (rq_stage() < RQ_OSGILIATH_ATTACK)
    {
	return "You don't see that here.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "This rotting corpse swings from one of the " + 
	"trees on this " +
	"path, a horrible welcome sign to this outpost.\n";
    }
}

public string
tree_desc()
{
    if (rq_stage() < RQ_OSGILIATH_ATTACK)
    {
	return "The trees on either side of this path mark " + 
	"the entrance " +
	"to this hidden camp.\n";
    }
    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "This trees beside the path have been hacked " +
	"and marred " + 
	"to the point " +
	"where they may not live much longer.  " +
	"The rotting body of a humanoid hangs from one of the trees.\n";
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
	"painted black, " +
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
	return "The pile of supplies in the clearing to the " + 
	"west seems " +
	"to contain materials for building large walls, tents, and " +
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
            Orc1->set_monster_home(CAMP_ROOM_DIR + "fort1");
        }

        if (!objectp(Orc2))
        {
            Orc2 = ::clone_npc(Orc2, CAMP_NPC_DIR + "ithil_uruk");
            Orc2->set_monster_home(CAMP_ROOM_DIR + "fort1");
        }

        if (!objectp(Orc3))
        {
            Orc3 = ::clone_npc(Orc3, CAMP_NPC_DIR + "ithil_uruk");
            Orc3->set_monster_home(CAMP_ROOM_DIR + "fort1");
        }

        if (!objectp(Orc4))
        {
            Orc4 = ::clone_npc(Orc4, CAMP_NPC_DIR + "ithil_uruk");
            Orc4->set_monster_home(CAMP_ROOM_DIR + "fort1");
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

