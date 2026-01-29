/*  file:  /d/Calia/sea/beach/cliff/base_cliff_room.c
 *  description: Base room for cliff above Calian sea
 *  coder: Tigerlily
 *  date:  2002-05-03
 *  specials: To climb cliff, player needs level of 
 *            dex and climb skill
 *            --no wielding of weapons
 *            --creates fatigue
 *            --potential to fall 
 *            --create_paths() creates some semi-random exits
 *  notes:
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"
#define EXTRA_SHORT " clinging to the side of the cliff"



#define UNDERSCORE "_"

inherit "/std/room";
inherit ROOM_TELL;

static mixed room_exits;

/* prototype function declarations */

int make_cliff_room(int level);
int climb_syntax(string str);
int navigate_cliff();
string str_level(int level);
int calc_fatigue();
public int falls_down(object tp, int degree);
public int create_paths(string rm_name, string verb);
void special_reset_room();
public int falls_horribly();
public int look_alternate(string str);


/******************************************************************
 * Function name: make_cliff_room
 * Description  : This function adds set_short, set_long,
 *                and adds items and tells based on the
 *                level of the cliff 
 * Arguments    : int level -- how high up the cliff 0-5
 */
void
make_cliff_room(int level)
{
    set_short("Granite cliff above the Calian sea");
    set_long("You are clinging precariously to the nearly vertical"+
      " side of a granite cliff above the Calian sea."+ 
      " Cracks go deep into the eroded granite in some areas,"+
      " and the rough rock crumbles under feet and hands."+
      " With your face pressed against the cliff, your"+
      " position allows you to look a small distance to the"+
      " left or right, up or down. You stand"+
      str_level(level));

    add_item(({"cliff", "granite"}), "The vertical cliff"+
      " stands dark against the blue sky. The granite is"+
      " seamed with cracks due to erosion"+
      " by wind and sea. With your face plastered against"+
      " the cliff, clinging tightly, you can only look a little"+
      " distance to the right, left, up or down.\n");
    add_item(({"cracks", "erosion"}), "There are some cracks in"+
      " the rough granite, apparently due to erosion from sea and"+
      " wind. Luckily they give you something to grasp.\n");
    add_item(({"side", "on either side"}),"You can look to the"+
      " right or left. Your position doesn't permit you room"+
      " to turn around or look behind you over the sea.\n");
    add_item(({"either side","right", "to the right", "east", 
	"to the east", "left", "to the left"}),
      "Standing close against the cliff you can see"+
      " a small distance to the right and left. The dark"+
      " granite is seamed with irregular cracks"+
      " and pitted with holes where erosion has worn it"+
      " away.\n");

    switch(level)
    {
    case 0:
	add_item(({"down", "base", "base of cliff"}), "You are"+
	  " just above the rocks at the base of the cliff."+
	  " The waves crashing on the rocks below make"+
	  " a roaring sound.\n");
	add_item(({"up", "u", "above"}), "You look up to see the"+
	  " cliff wall extending high above you. Rough rock outcroppings"+
	  " block the view of the top.\n");
	add_tell("Waves crash against the rocks"+
	  " just below you.\n");
	add_tell("The granite crumbles under your hands"+
	  " and small pieces fall down the cliff.\n");
	add_tell("A large sea osprey circles overhead.\n");
	add_tell("A blast of wind beats at your back.\n");
	add_tell("A small black spider crawls out from a crack"+
	  " in the cliff and scurries across your hand.\n");
	add_tell("Your foot slips on the wet granite,"+
	  " causing you to stumble.\n");
	add_tell("Seagulls fly close and peer "+
	  "at you curiously.\n");

	break;

    case 1:
	add_item(({"up", "above"}), "You look up to see the"+
	  " cliff extending high above you, standing dark"+
	  " against the blue sky.\n");
	add_item(({"down","base","base of cliff"}), "You are"+
	  " a little distance above the rocks at the base"+
	  " of the cliff. The waves crashing on the rocks"+
	  " below makes a roaring sound.\n");
	break;

    case 2:
	add_item(({"up", "above"}), "You look up to see the"+
	  " cliff extending rather high above you, standing dark"+
	  " against the blue sky.\n");
	add_item(({"down","base","base of cliff"}), "You are"+
	  " about a third of the way up the cliff.\n");
	break;

    case 3:
	add_item(({"up", "above"}), "You look up to see"+
	  " the cliff extending some distance above you,"+
	  " standing dark against the blue sky. You glimpse"+
	  " the clifftop from here.\n");
	add_item(({"down","base","base of cliff"}), "You"+
	  " judge that you are about two-thirds of the"+
	  " distance up the cliff."+
	  " Looking down, you get a dizzy sense of vertigo.\n");
	break;

    case 4:
	add_item(({"up", "above"}), "You look up and see the"+
	  " clifftop is just above. You see a large nest"+
	  " perched on the crag of rock.\n");
	add_item(({"down", "base","base of cliff"}), "Looking down,"+
	  " you see the waves crashing on the rocks far below.\n");
	add_tell("From above you hear the cry of some"+
	  " large sea bird.\n");
	add_tell("You press your face against the rough"+
	  " granite surface and cling on for dear life.\n");
	add_tell("A wave of vertigo threatens to overcome"+
	  " you with intense dizziness and nausea.\n");
	add_tell("Rocks crumble under your grasp,"+
	  " and loose rubble falls down the cliff.\n");

	break;


    default:
	break;
    }

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_HIDE, -1);


    set_tell_time(150);
    add_tell("Gales of sea spray and wind beat against"+
      " your back.\n");
    add_tell("A rock crumbles under your feet and"+
      " falls down the cliff.\n");

}
/**********************************************************************
 * Function name: init
 * Description  : Add direction commands to livings in the room.
 * Special:     : Borrowed and modified from /std/room/exits.c
 *                so that right and left can be added to default
 *                directions.
 */
public void
init()
{

    ::init();
    if (member_array("right", query_exit_cmds()) == -1)
	add_action(unq_no_move, "right"); 


    if (member_array("left", query_exit_cmds()) == -1)
	add_action(unq_no_move, "left"); 

    add_action(&climb_syntax(), "climb", 0);
    add_action(&look_alternate(), "look", 0);
    add_action(&look_alternate(), "l", 0);

}



/********************************************************
 * Function name: enter_inv
 * Description  : Adds to player's short description when
 *                climbing the cliff
 * Arguments    : object ob = player, from = previous location
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!living(ob))
	return;
    ob->add_prop(LIVE_S_EXTRA_SHORT, EXTRA_SHORT);
}

/********************************************************
 * Function name: leave_inv
 * Description  : removes extra short description when
 *                player leaves cliff
 * Arguments    : object ob = player, to = whereto
 */

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (!living(ob))
	return;

    ob->remove_prop(LIVE_S_EXTRA_SHORT);
}

/**********************************************************
 * Function name: navigate_cliff()
 * Description  : This function is called when player tries to 
 *                navigate around on the cliff. Whether he
 *                can move in any direction is determined by
 *                the topography and player's skill and dex
 * Arguments    : none
 * Returns      : 0 if ok to move, else returns a 1
 */
public int
navigate_cliff()
{
    object tp = this_player();
    string dir = query_verb();
    string extra_cmd = query_dircmd();
    int chance_falling;
    mixed *weapon_list = ({});
    object held_item;
    string rocks_room = ({CLIFF_ROOM + "rocks1", 
      CLIFF_ROOM + "rocks2", CLIFF_ROOM + "rocks3",})[random(3)];
    int degree = 3 + random(4);


    int i;

    if (extra_cmd)
    {
	write(capitalize(dir) + " what? do you mean " + dir + "?\n");
	return 1;
    }

    /* can't climb the cliff while wielding weapons */
    weapon_list = tp->query_weapon(-1);

    if (sizeof(weapon_list) > 0)
    {
	chance_falling = random(3);
	switch(chance_falling)
	{
	case 0:
	    // player drops weapon and it falls below
	    held_item = weapon_list[0];
	    if (objectp(held_item))
	    {
		held_item->move(rocks_room, 1);
		write("While fumbling for a hold on"+
		  " the cliff side, you clumsily drop your "+
		  LANG_SHORT(held_item) + " and glance down sadly"+
		  " as it bounces off the cliff and falls"+
		  " to the rocks below.\n");
		tell_room(environment(held_item), "Suddenly "+
		  LANG_ASHORT(held_item) +
		  " falls in from above, nearly missing your head!"+
		  " It falls harmlessly onto the rocks.\n");
	    }
	    return 1;

	    break;

	case 1:
	    // heaviness and encumbrance cause
	    // player to fall
	    if (tp->query_encumberance_weight() > 30)
	    {
		return(falls_down(tp, degree));
	    }
	    write("You clumsily fumble around but are"+
	      " unable to grasp anything with your hands occupied.\n");
	    return 1;
	    break;

	case 2:
	    // player falls down to bottom of cliff
	    return(falls_down(tp, degree));
	    break;

	default:
	    write("Your hands must be empty in order to maintain"+
	      " a hold on the side of the cliff.\n");
	    return 1;
	}

    }

    // if panicky, can't proceed

    if (tp->query_panic() > 900)
    {
	write("You feel a wave of intense vertigo "+
	  "and feel too frozen with fear to proceed.\n");
	tp->command("$tremble");
	return 1;
    }



    /* skills and dex stats test */
    if (tp->resolve_task(TASK_ROUTINE, ({TS_DEX, SS_CLIMB})) <= 0)
    {
	write("You slip and nearly fall! Your heart pounds"+
	  " as you realize how close you came to falling.\n");
	tp->add_panic(20 + random(10));
	if (dir == "right" || dir == "left")
	    say(QCTNAME(tp) + " slips trying to climb to the "+
	      dir + ".\n");
	else
	if (dir == "up" || dir == "down")
	    say(QCTNAME(tp) + " slips trying to climb " + dir + ".\n");
	return 1;
    }

    /* if player is super clumsy */
    else if (tp->resolve_task(TASK_ROUTINE, ({TS_DEX,SS_CLIMB})) <= -35)
    {
	return(falls_down(tp, degree));

    }

    /* otherwise player successfully navigates the cliff */
    if (dir == "right" || dir == "left")
    {
	write("You slowly edge your way to the "+
	  dir + ", grasping hold"+
	  " of the rough rock with your fingertips.\n");
    }
    if (dir == "up" || dir == "down")
    {
	write("You slowly edge your way "+
	  dir + ", grasping hold"+
	  " of the rough rock with your fingertips.\n");
    }

    tp->add_panic(20 + random(10));
    /* ok to go in that direction */
    return 0;
}

/***********************************************************
* Function name: str_level
* Description  : Adds an extra line to the long description based
*                on the level of the cliff. 
* Arguments    : int level--how high up the cliff.
*/
string
str_level(int level)
{
    switch(level)
    {
    case 0:
	return " just above the base of the cliff.\n";
	break;

    case 1:
	return " a little way up the side of the cliff.\n";
	break;

    case 2: 
	return " about a third of the distance up"+
	" the cliff.\n";
	break;

    case 3:
	return " about two-thirds up the side of the cliff.\n";
	break;

    case 4:
	return " just below the clifftop.\n";
	break;

    default:
	return " on the side of the clifftop.\n";
    }
}


/******************************************************************
 * Function name: climb_syntax
 * Description  : Proper syntax for navigating cliff
 * Arguments    : str from unq_no_move
 * returns      : 1
 */

private int
climb_syntax(string str)
{
    write("You can try to proceed up, down, right or left"+
      " if you can find a fingerhold or foothold in that direction.\n");
    return 1;
}

/**************************************************************** 
 * Function name: unq_no_move
 * Description  : shadows unq_no_move from /std/room.c functions
 *                to make a more natural-sounding response when
 *                player can't navigate in a direction or exit
 * Arguments    : str = command
 * Returns:     : 0 with a notify_fail message
 */ 
int 
unq_no_move(string str)
{
    notify_fail("You explore the cliff with your hands and feet,"+
      " but you are unable to grab hold in that direction.\n");
    return 0;
}
/****************************************************************
 * Function name: calc_fatigue
 * Description  : calculates fatigue caused from climbing
 * Arguments    : none
 * returns      : value of fatigue
 */
public int
calc_fatigue()
{
    return random(3);
}

/****************************************************************
 * Function name: falls_down
 * Description  : what happens when player falls to rocks below
* Arguments    : tp = this_player, degree = degree of hurt
 * returns      : returns 1
 */
public int
falls_down(object tp, int degree)
{
    write("You suddenly lose your grip and plummet"+
      " down to the rocks below.\n");
    tp->command("$scream");
    tell_room(environment(tp), QCTNAME(tp)+ " suddenly loses "+ 
      tp->query_possessive()+
      " grip and plummets to the rocks below.\n", ({tp}));
    tp->move_living("M", CLIFF_ROOM+"rocks1", 1, 1);
    tell_room(environment(tp), QCTNAME(tp) + " falls in from"+
      " above.\n", ({tp}));
    write("You land with a crash on the sharp rocks.\n");

    // ouch!!

    tp->heal_hp(-1*tp->query_max_hp()/degree);
    tell_room(environment(tp), QCTNAME(tp) + " falls in a"+
      " ruin onto the sharp rocks. Blood splatters"+
      " everywhere!\n", ({tp}));

    // *very* small chance of dying

    if ((tp->query_hp() <= 0) && (random(50) > 48))
    {
	tp->do_die(this_object());
	// log death
	log_file("falling_death", tp->query_real_name() +
	  " fell from the cliff and died:"+
	  " " + ctime(time())+".\n");
	if (tp->query_wiz_level())
	    write("Good thing you are immortal, else"+
	      " you would have died.\n");
	else 
	    write("Alas! you die from the fall.\n");
    }
    return 1;
}
/**********************************************************************
 * Function name: create_paths
 * Description  : creates some semi-random exits in the room when the
 *                   room is created, based on the last command player
 *                   issued to enter the room
 * Arguments    : string: current room name, verb: query_verb() from
 *                    create_room--player's command that loaded the room
 * Special:     : 
 */

public int
create_paths(string rm_name, string verb)
{
    mixed str;
    string rm2_name;
    int num_exits, i;
    int x1, y1;
    string *brstr = explode(rm_name, "");
    string *compass = ({"left", "down", "right", "up"});
    string *myexits = ({compass[(member_array(verb, compass) + 2) % 4]});

    setuid();
    seteuid(getuid());
    compass -= myexits;
    compass -= ({compass[random(3)]});
    myexits += compass;

    // identify current location and coordinates

    x1 = atoi(brstr[strlen(rm_name) - 3]);
    y1 = atoi(brstr[strlen(rm_name) - 1]);
    str = CLIFF_ROOM + "cliff";


    //configure exits
    num_exits = sizeof(myexits);
    i = 0;
    for (i = 0; i < num_exits; i++)
    {
	// get coordinates of current room
	x1 = atoi(brstr[strlen(rm_name) - 3]);
	y1 = atoi(brstr[strlen(rm_name) - 1]);

	switch (myexits[i])
	{
	case "up":
	    y1++;
	    break;

	case "down":
	    y1--;
	    break;

	case "right":
	    x1++;
	    break;

	case "left":
	    x1--;
	    break;

	default:
	}

	if (x1 >= 0 && y1 >= 0 && x1 < 5 && y1 < 5)
	{
	    rm2_name = str + x1 + UNDERSCORE + y1;
	    add_exit(rm2_name, myexits[i], &navigate_cliff(),
	      &calc_fatigue(), 1);
	    switch (myexits[i])
	    {
	    case "right":
		add_item(({"right", "to the right"}),
		  "You glance to the right and notice that the"+
		  " rough surface of the cliff grants some"+
		  " purchase in that direction.\n");
		break;

	    case "left":
		add_item(({"left", "to the left"}),
		  "Your eagle eyes notice that the rough"+
		  " texture of the cliff to the left"+
		  " may give some extra traction for"+
		  " climbing in that direction.\n");
		break;

	    case "up":
		add_item(({"up", "above"}),
		  "You look up and estimate that the"+
		  " eroded cracks on the cliff"+
		  " might provide enough traction"+
		  " for you to ascend in that direction.\n");
		break;

	    case "down":
		add_item(({"down", "below"}),
		  "You glance down and sense that"+
		  " the cracks might give you something"+
		  " to hold on to in order to descend.\n");
		break;

	    default:
		add_item(({"around", "left", "right", "up", "down"}),
		  " It is difficult to estimate whether you can"+
		  " go in any direction from here.\n");


	    }
	}

	// end for loop
    }

    if (member_array("up", myexits) == -1)
    {
	add_item("up", "The rock looks loose and crumbly"+
	  " in that direction.\n");
	add_exit(CLIFF_ROOM + "rocks1", "up", &falls_horribly(), 0, 1);
    }
    return 1;
}


/**********************************************************************
 * Function name: special_reset_room
 * Description  : This function will be called in reset_room on the 
 *                cliff rooms, so that they will periodically be 
 *                removed and then the path will change when players
 *                reload rooms as they ascend or descend
 * Arguments    : none, called from reset_room in cliff rooms
 * Special:     : 
 */

void
special_reset_room()
{
    if (sizeof(FILTER_LIVE(all_inventory(this_object()))) == 0)
	this_object()->remove_object();
    return;
}
/*********************************************************************
 * Function name:  falls_horribly()
 * Description:    This function is called when someone falls to give
 *                 a randomized result of damage after falling
 * Argument:       none
 */

public int
falls_horribly()
{
    //degree of hurt from falling
    // is divided into maximum health
    // of player in formula

    int degree = random(5) + 4;
    // This is what happens when player tries to go up
    // and is not careful about checking out the descriptions
    // in that direction.

    falls_down(this_player(), degree);
    return 1;
}

/*******************************************************************
 * Function name:  look_alternate()
 * Description  :  allows a player to 'look' left or right on
 *                 the side of the cliff
 * Argument     :  string str--the rest of the command
 * returns      :  1 if successful--0 if not and returns to default look
 */


public int
look_alternate(string str)
{
    object tp = this_player();

    if (!str)
	return 0;



    switch (str)
    {
    case "right":
    case "r":
	this_player()->command("$examine right");
	return 1;
	break;

    case "left":
    case "l":
	this_player()->command("$examine left");
	return 1;
	break;

    case "up":
    case "u":
	this_player()->command("$examine up");
	return 1;
	break;

    case "down":
    case "d":
	this_player()->command("$examine down");
	return 1;
	break;

    default:
	return 0;
    }



    return 0;


}
