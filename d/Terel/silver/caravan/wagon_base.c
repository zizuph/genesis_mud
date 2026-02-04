/*

 Inside of the caravan wagon,

 by Udana, 03/06

*/


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <composite.h>

#define PLAYER_I_ATTACKED_CARAVAN "_player_i_attacked_caravan"


inherit STDROOM;

inherit "/d/Terel/std/room_tell.c";



object this_wagon = 0;
int crate_count = 0;


/* If there is someone to drive the wagon */
public int is_manned();

/* How many people can board the wagon. */
public int room_left();

/* handles the add action thing */
int jump_off(string a);

/* what can be seen from outside of the wagon. */
string contain_desc(object looker);

/* When whole caravan is disbanded, things inside wagons must be handled */
public void remove_caravan_object();

/* When the caravan is created near Calathin, if direction is positive the wagon carries goods from calathin */
int create_inside(object wagon, int direction);

/* Gives additionaly description for a guy who drives it. */
void set_coachman(object c);

public string query_colour();

/* Gives the wagon a new couchman */
public void get_new_coachman();

public void picked_chest(object thief);

public void create_room()
{
  ::create_room();
  set_short("@@my_short");
  set_long("@@my_long");

  reset_room();
  set_tell_time(300 + random(100));
  add_tell("@@tell1");
  add_tell("You hear birds singing in the forest by the road.\n");
}

int create_inside(object wagon, int direction)
{
	int res;
	/* if the wagon wasn't removed we just need to fill it with people. */
	if(objectp(this_wagon) && stringp(E(this_wagon)) && member_array(file_name(E(this_wagon)) + ".c", ROUTE) != -1)
	{
		res = 0;
		tell_room(TO, "A calathin merchant in company of few guards and coachman arrives.\n");
	}
	else
	{
		this_wagon = wagon;
		/* cleaning leftovers */
		reset_room();
		remove_caravan_object();
		res = 1;
	}
  /*adding coachman*/
  object c = clone_object(NPC + "coachman.c");
  c->move(TO);
  c->set_colour(this_wagon->query_colour());
  set_coachman(c);
  c->add_prop(LIVE_S_EXTRA_SHORT, " sitting on a small chair in front of the wagon");

  /*adding merchant*/
  c = clone_object(NPC + "merchant.c");
  c->move(TO);
  c->set_colour(this_wagon->query_colour());

  /*adding guards*/
  for(int i = 0; i < 4; ++i)
  {
    c = clone_object(NPC + "guard.c");
    c->move(TO);
    c->set_colour(this_wagon->query_colour());
  }
  
  /*adding crates*/
  crate_count = random(3) + 1;
  for(int i = 0; i < crate_count; ++i)
  {
    object ith_crate = clone_object(OBJ + "crate");
    ith_crate->move(TO);
    ith_crate->set_contents(direction);
  }
  return res;
}

public int room_left()
{
	return MAX_INSIDE_CARAVAN_WAGON - sizeof(FILTER_LIVE(all_inventory(TO)));
}

public void picked_chest(object thief)
{
  /* If the wagon isn't moving, it's easier to keep a balance */
  if(!is_manned())
    return;
  thief->add_prop(PLAYER_I_ATTACKED_CARAVAN, 1);
  thief->catch_msg("The weight of the crate makes you lose you balance! You take few steps backwards "+
    "and fall of the wagon.\n");
  tell_room(TO, "The weight of the crate makes " + QTNAME(thief) + " lose " + thief->query_possessive() +
    " balance! " + (thief->query_gender() ? "She" : "He") + " takes few steps backwards and falls of the wagon.\n",
    thief);
  thief->move_living("falling from the wagon", E(this_wagon), 1, 0);
  thief->heal_hp(- thief->query_max_hp() / 20);
 // if(thief->query_hp() <= 0)
 //   thief->do_die();
}


public string query_colour()
{
 return this_wagon->query_colour();
}

public int is_manned()

{
  return sizeof(filter(all_inventory(TO), &->is_caravan()));

}

string tell1()
{
  return (is_manned() ? "The wagon jumps over a bump on the road.\n" : "The flies gather over the corpses.\n");
}

string my_short()
{
 return "On " + (is_manned() ? "a merchant " : "an abandoned ") + "wagon";
}
/* Also shows what's outside the wagon */

string my_long()

{

	if(!objectp(this_wagon))
		remove_caravan_object();
  object *visible_things = FILTER_CAN_SEE(all_inventory(E(this_wagon)), TP); 
  object *alive_things = FILTER_LIVE(visible_things);                           
  string *descriptions = ({});

  string desc;

  if(is_manned())

    desc = "You're standing on a large merchant wagon, pulled by two mules"+

     ", travelling slowly through the silver forest. ";

  else

    desc = "You're standing on an abandoned merchant wagon. ";

  if(CAN_SEE_IN_A_ROOM(TP, E(this_wagon)))
  {
    desc += "Outside you see:\n";
    desc += CAP(E(this_wagon)->query_short());
    desc += " \n";
    if(sizeof(alive_things))
    {
       desc += COMPOSITE_LIVE(alive_things);
       desc += ", ";
    }
    /* The other half, alive_things are dead_things now */
    alive_things = FILTER_DEAD(visible_things);
    if(sizeof(alive_things))
       desc += COMPOSITE_DEAD(alive_things);
  }

  return desc + ".\n";

}



void set_coachman(object c)

{
  c->add_prop(IS_CARAVAN_COACHMAN, 1);
  c->add_act("emote pulls the reins a bit.");

}



public void get_new_coachman()
{
  if(is_manned())
    set_coachman(filter(all_inventory(TO), &->is_caravan())[0]);
}


public void init()
{
	::init();
	start_room_tells();
	add_action(jump_off, "jump");
	add_action(jump_off, "climb");
}


int jump_off(string a)
{
  notify_fail(CAP(QVB) + " where?\n");
  if(!strlen(a))
	return 0;
  if(!parse_command(a, ({}), "'of' / 'down' / 'out' [the] [wagon]"))
	return 0;
  TP->move_living("from the wagon", E(this_wagon), 1, 0);
  return 1;
}



/* called from outside, describe what's in the wagon */
string contain_desc(object looker)
{
  object *visible_things = FILTER_CAN_SEE(all_inventory(TO), looker); 
  object *alive_things = FILTER_LIVE(visible_things);                           
  string *descriptions = ({});

  string desc = "";

  if(CAN_SEE_IN_A_ROOM(looker, TO))
  {
    if(sizeof(alive_things))
    {
       desc += COMPOSITE_LIVE(alive_things);
       desc += ", ";
    }
    /* The other half, alive_things are dead_things now */
    alive_things = FILTER_DEAD(visible_things);
    if(sizeof(alive_things))
       desc += COMPOSITE_DEAD(alive_things);
  }
  return desc;
}



void handle_player(object ppl)
{
  ppl->catch_msg("As the caravan's heading into the town, you're forced of the wagon.\n");
  ppl->move_living("from the wagon", E(this_wagon), 1, 0);
}



public void remove_caravan_object()
{
  object *p = FILTER_PLAYERS(all_inventory(TO));
  for(int i = 0; i < sizeof(p); ++i)
    handle_player(p[i]);
  for(int i = 0; i < sizeof(all_inventory(TO)); ++i)
    all_inventory(TO)->remove_object();
}



