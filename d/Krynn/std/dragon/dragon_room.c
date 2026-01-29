/* Dragon back coded by Nick */
/* Completely rewritten by Aridor 5/95 */

#include "/d/Krynn/common/defs.h"

inherit R_FILE

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>

/*prototype*/
string query_place();
void take_off(int time_to_land, string land_where);
void land(string where);


object dragon;
int flying; /* 0 on the ground,
	       1 on the ground can't be called,
	       2 in the air
	       this means:
	       On the ground:    0,1
	       In the air:       2
	       Can be called:    0
               Cannot be called: 1,2
	       */
string dragon_file, place;
string animal = "dragon"; /* what animal is transporting the players */
mapping landings;
string landed_desc_long, flying_desc_long;
int flyingalarm = 0;


nomask void
reset_krynn_room()
{
    if (dragon)
      return;
    
    if (!dragon_file)
      return;

    seteuid(getuid(TO));
    (dragon = clone_object(dragon_file))->move(VOID, 1);
    dragon->set_on_dragon_room_path(MASTER);
    flying = 0;
    place = VOID;
}

void
set_flying_long(string str)
{
    flying_desc_long = str;
}

void
set_landed_long(string str)
{
    landed_desc_long = str;
}

void
create_on_dragon_room()
{
}

string
my_long()
{
    if (flying == 2)
      return flying_desc_long;
    return landed_desc_long;
}

nomask void
create_krynn_room()
{
    set_short("On dragon");
    set_long("@@my_long@@");
    set_flying_long("You are on the back of a bronze dragon flying high " +
		    "up in the air. You can feel the wind in your hair. The " +
		    "dragon flies very fast. Far below you can see the " +
		    "ground. It's a long way to fall if you jump.\n");
    set_landed_long("You are sitting on the back of a huge dragon. There is " +
		    "room for two people to sit here. When you want the " +
		    "dragon to fly, just give him a kick.\n");

    add_exit("@@query_place", "down", "@@going_down");
    add_prop(OBJ_S_WIZINFO,"Just kick the dragon to get it to fly with you.\n");

    add_item(({"wings","wing"}), "There are two wings, one on each side. They " +
	     "help keeping the beast aloft.\n");
    add_item(({"surroundings","countryside","clouds"}),
	     "Below you are mostly clouds, but you catch a glimpse of the " +
	     "countryside every once in a while.\n");

    create_on_dragon_room();
    reset_room();
    add_prop(ROOM_I_NO_CLEANUP, 1);
}


void
set_animal(string what)
{
   animal = what;
}

void
init()
{
    ADA("jump");
    add_action("check_all_cmds","",1);
    ::init();
}

int
call_dragon(string to_where)
{
    seteuid(getuid(TO));
    VOID->load_me();
    if (flying || !dragon)
      return 0;
    
    if (place == to_where)
      return 2;

    take_off(9, to_where);/* land in 9 secs at to_where */
    return 1;
}

void
take_off(int time_to_land, string land_where)
{
    remove_exit("down");
    dragon->restart_void();
    tell_room(E(dragon), "The " + animal + " leaves into the sun.\n");
    if (flyingalarm)
    {
	remove_alarm(flyingalarm);
	flyingalarm = 0;
    }
    flying = 2;
    place = VOID;
    dragon->move(VOID,1);
    if (time_to_land > 0)
      set_alarm(itof(time_to_land),0.0,"land", land_where);
    else
      land(land_where);
}

void
do_flight(object ob)
{
    set_alarm(itof(2 + random(3)),0.0, "start_flight",ob);
    set_alarm(itof(5 + random(5)),0.0, "wind", ob);
    set_alarm(itof(10 + random(2)),0.0, "wind", ob);
    set_alarm(itof(12 + random(6)),0.0, "wind", ob);
    set_alarm(itof(18 + random(4)),0.0, "wind", ob);
    set_alarm(itof(22 + random(2)),0.0, "end_flight", ob);
}

void
start_flight(object ob)
{
    if (!ob || E(ob) != TO)
      return;

    tell_object(ob, "The " + animal + " circles upwards, climbing high " +
                    "into the sky, gaining altitude for the long flight.\n");
}

void
wind(object ob)
{
    if (!ob || E(ob) != TO)
      return;
    switch(random(7))
      {
	case 0:
	  {
	      tell_object(ob, "The " + animal + " coughed below you and you nearly fell off.\n");
	      break;
	  }
	case 1:
	case 2:
	  {
	      tell_object(ob, "You pass through some clouds.\n");
	      break;
	  }
	case 3:
	case 4:
	  {
	      tell_object(ob, "You see a bird pass by below you.\n");
	      break;
	  }
	case 5:
	case 6:
	  {
	      tell_object(ob, "Very far below, you can see the countryside.\n");
	      break;
	  }
      }
}

void
end_flight(object ob)
{
    if (!ob || E(ob) != TO)
      return;

    tell_object(ob, "The " + animal + " makes a large curve, slowly " +
                    "descending towards the ground.\n");
}

void
land(string where)
{
    int i;
    object *obj;
    
    place = where;
    flying = 1;
    flyingalarm = set_alarm(5.0,0.0,"set_flying",0);
    dragon->land();
    obj = all_inventory(TO);
    for(i = 0; i < sizeof(obj); i++)
      {
	  if (!P(obj[i], TO))
	    continue;
	  tell_object(obj[i], "The " + animal + " lands and you descend.\n");
	  obj[i]->move_living("off the " + animal, place);
	  obj[i]->remove_prop(LIVE_O_KRYNN_DRAGON);
      }
    if (member_array("down",query_exit_cmds()) == -1)
      add_exit("@@query_place", "down", "@@going_down");
}


void
set_flying(int i)
{
  if (flyingalarm)
    remove_alarm(flyingalarm);
  flyingalarm = 0;
  flying = i;
}
     
int
query_flying() 
{
    return flying; 
}
     
object
query_dragon()
{
    return dragon; 
}

string
query_place()
{
    return place;
}

void
set_place(string where)
{
    place = where;
}

int
jump()
{
    string *lands = m_indexes(landings) - ({ VOID });
    string where_to = lands[random(sizeof(lands))];
    
    if (flying != 2)
      return 0;
    
    if (where_to == "anywhere")
      where_to = m_values(landings[where_to])[0];

    /* This might be one of an array of rooms along the route! */
    where_to->load_me();
    write("You stop looking down and leap into the air.\n");
    TP->move_living("with a big scream", where_to, 1);
    TP->heal_hp(-200);
    return 1;
}

string
get_destination(string command_to_landing)
{
    string str;
    mapping lands = landings[place];
    if (lands)
      str = lands[command_to_landing];
    if (!str)
      {
	  lands = landings["anywhere"];
	  if (lands)
	    str = lands[command_to_landing];
      }
    if (str == place)
      return 0;
    return str;
}

varargs void
add_landing(string room_path_from, string command_to_landing, string room_path_to)
{
    mapping lands;
    if (!landings)
      landings = ([VOID:([])]);
    lands = landings[room_path_from];
    if (!lands)
      landings += ([ room_path_from:([ command_to_landing:room_path_to ]) ]);
    else
      lands += ([ command_to_landing:room_path_to ]);
    if (room_path_from != "anywhere")
      (room_path_from)->set_on_dragon_room_path(MASTER);
    (room_path_to)->set_on_dragon_room_path(MASTER);
}

void
set_dragon(string dragon_path)
{
    if (!dragon_file)
      dragon_file = dragon_path;
}

void
my_test()
{
    dump_array(landings);
}



/*********************** needed by the dragon on the ground ******************/

int
check_all_cmds(string str)
{
    object dragon, *ob;
    int i;
    string destination;
   
    if (flying == 2)
      return 0;

    destination = get_destination(query_verb() + " " + str);
    NF("What?\n");
    if (!destination)
      return 0;
   
    ob = all_inventory(TO);
    for (i = 0; i < sizeof(ob); i++)
      do_flight(ob[i]);
    
    take_off(27, destination);
    write("You " + query_verb() + " the dragon and off you go.\n");
    say(QCTNAME(TP) + " " + query_verb() + "s the dragon and off you go.\n");
    return 1;
}

void
drop_all()
{
    object *ob;
    int i;
    
    ob = all_inventory(TO);
    for(i = 0; i < sizeof(ob); i++)
      {
	  ob[i]->move(query_place(), 1);
	  if (living(ob[i]))
	    {
		tell_object(ob[i], "The dragon leaves suddenly and you fall to " +
			    "the ground.\n");
		tell_room(query_place(), "Suddenly " + QTNAME(ob[i]) +
			  " arrives falling through the air.\n", ob);
	    }
	  else
	    tell_room(query_place(), "Suddenly, " + LANG_ASHORT(ob[i]) +
		      "arrives falling through the air.\n");
      }
}

int
going_down()
{
    if (query_place() == VOID)
      {
	  /* Obviously a linkdead player reconnecting... */
	  write("Apparently, you were linkdead. Just kick the " + animal +
		" to take you back to the world.\n");
	  return 1;
      }
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))) <= 1)
      flying = 0;
    return 0;
}

