//
//  A catwalk room which allows people to look and leap to the ground
//  below.  It also allows people to leap on others, starting combat.
//
//  Coded by:  Morbeche, Nov 8th 1999
//             with help from Shiva
//
//                                      Copyright @Morbeche Nov 8th 1999
//  Modification log:
//  Gwyneth 4/1/01
//  Fixed a runtime error caused by a room not loading when looked at.
//
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
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <formulas.h>


public void create_gondor();
public void reset_room();

public string long_func();
public string wall_desc();

public void clone_npc(object npc, string npc_file);
public int do_leap(string str);
public int leap_access(object obs);

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
    set_short("on the catwalk above the north end of the camp");
    set_long(long_func);
    add_item(({"clearing","camp","down","ground","tent"}),"@@exa_camp|" +
"Looking down you can see a barracks tent at the north " +
"end of this hidden camp.  |"+
      CAMP_ROOM_DIR+"fort3@@");
    add_item(({"wall","walls","wooden walls"}),wall_desc);

    add_exit(CAMP_ROOM_DIR + "wall1.c","southeast");
    add_exit(CAMP_ROOM_DIR + "wall3.c","southwest");


    reset_room();

}

public void
init()
{
    ::init();

    add_action(do_leap,"leap");

}


public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;


    longtxt = "This catwalk runs along the tops of the trees on " +
    "the northern end of this outpost.  " +
    "Below is the northern tent of the camp, which is used to house " +
    "some of the members of the outpost.  ";

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
wall_desc()
{

    if (rq_stage() >= RQ_OSGILIATH_ATTACK)
    {
	return "The wooden walls of this catwalk have been " +
	"charred to a " +
	"deep black colour, marking this area under the control " +
	"of the East.  From here you can look down at the camp below.\n";
    }

    return "The wooden walls of this catwalk stretch some twenty " +
    "feet above the " +
    "ground, allowing you a look down at the camp below.\n";

}



int
do_leap(string str)
{
    mixed *obs;

    if (!strlen(str))
    {
	notify_fail("Leap down, or on whom?\n");
	return 0;
    }

    if (str == "down" ||
      parse_command(str, ({}), "[down] 'to' [the] 'ground'"))
    {
	write("You leap down to the ground below.\n");
	say(QCTNAME(TP) + " leaps down to the ground below.\n");

	TP->move_living("M",CAMP_ROOM_DIR + "fort3");
	TP->catch_msg("You land with a hard thud.\n");
	tell_room(ENV(TP),QCTNAME(TP)+" leaps out of the trees " +
	  "above you, landing with a thud on the ground.\n",TP);
	return 1;
    }

    if (!parse_command(str, all_inventory(find_object(
	    CAMP_ROOM_DIR+"fort3")),
	"[down] 'on' / 'upon' [the] %i", obs) ||
      !sizeof(obs = NORMAL_ACCESS(obs, "leap_access", this_object())))
    {
notify_fail("Leap down, or on whom\n");
	return 0;
    }

    if (sizeof(obs) > 1)
    {	
	notify_fail("You can only leap upon one thing!\n");
	return 0;
    }

    if (!living(obs[0]))
    {
	notify_fail("You can only leap upon people!\n");
	return 0;
    }


    write("You leap down to the ground below, prepared to do battle!\n");
    say(QCTNAME(TP)+" leaps down to the ground below, intent on battle!\n");

    TP->move_living("M",CAMP_ROOM_DIR+"fort3");

    TP->catch_msg("You land viciously on the back " +
      "of your unsuspecting target!\n");
    tell_room(ENV(TP),"The forest suddenly erupts in noise " +
      "as "+QTNAME(TP)+" leaps out of the trees, " +
      "intent on doing battle!\n",TP);
    obs->catch_msg("You feel a sharp pain in your back as " +
      QTNAME(TP)+" lands squarely on you!\n");

    obs->command("scream");
    TP->attack_object(obs);
    obs->attack_object(TP);
    tell_room(ENV(TP),QCTNAME(TP)+" launches a surprise attack!\n",TP);
    return 1;

}

public int
leap_access(object obs)
{
    if (!obs)
    {
	return 0;
    }

    if (!CAN_SEE_IN_OTHER_ROOM(TP,CAMP_ROOM_DIR+"fort3"))
    {
	return 0;
    }
    if (!CAN_SEE(TP,obs))
    {
	return 0;
    }

    if (!F_DARE_ATTACK(TP,obs))
    {
TP->catch_msg("You don't dare to do that!\n");
	return 1;
    }

    // maybe do some other checks?

    return 1;
}

public string
exa_camp(string desc, string street_file)
{
    object  street, *people; 

    street_file->teleledningsanka();
    street = find_object(street_file);

    if (!objectp(street))
        return "\n";

    people = FILTER_LIVE(all_inventory(street));
    if (!CAN_SEE_IN_OTHER_ROOM(TP,CAMP_ROOM_DIR+"fort3"))
    {
	desc += "It is too dark below to see anything.";
	return 0;
    }
    if (sizeof(people))
	desc += "You can see " + COMPOSITE_LIVE(people) + 
	" down below.";
    else
	desc += "There is no one below you.";

    return BSN(desc);
}                                                                              

public void
reset_room()
{

 
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












