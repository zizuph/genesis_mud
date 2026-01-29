/* Dragon back coded by Nick */
/* Completely rewritten by Aridor 5/95 */

#include "/d/Krynn/common/defs.h"

inherit R_FILE

#include <stdproperties.h>
#include <macros.h>

/*prototype*/
string query_place();


object dragon;
int flying;
string dragon_file,on_dragon_file, place;
string animal = "dragon"; /* what animal is transporting the players */
mapping landings;

nomask void
reset_room()
{ 
    if (dragon)
      return;
    
    if (!dragon_file)
      return;

    seteuid(getuid(TO));
    (dragon = clone_object(dragon_file))->move(VOID, 1);
    dragon->set_on_flying_dragon_room_path(MASTER);
    dragon->set_on_landed_dragon_room_path(on_dragon_file);
    flying = 0;
    place = VOID;
}

void
create_on_flying_dragon_room()
{
}

nomask void
create_room()
{
    set_short("On dragon");
    set_long("You are on the back of a bronze dragon flying high up in the air. " +
	     "You can feel the wind in your hair. The dragon flies very fast. " +
	     "Far below you can see the ground. It's a long way to fall if " +
	     "you jump.\n");

    create_on_flying_dragon_room();
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
    call_out("start_flight", 2 + random(3), TP);
    call_out("wind", 5 + random(5), TP);
    call_out("wind",10 + random(2), TP);
    call_out("wind",12 + random(6), TP);
    call_out("wind",18 + random(4), TP);
    call_out("end_flight",22 + random(2), TP);
    ADA("jump");
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
    call_out("set_flying",5,0);
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
}

void
take_off(int time_to_land, string land_where)
{
    dragon->rem_void();
    tell_room(E(dragon), "The " + animal + " leaves into the sun.\n");
    flying = 1;
    dragon->move(VOID,1);
    if (time_to_land > 0)
      call_out("land", time_to_land, land_where);
    else
      land(land_where);
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
set_flying(int i)
{
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
      (room_path_from)->set_on_flying_dragon_room_path(MASTER);
    (room_path_to)->set_on_flying_dragon_room_path(MASTER);
}

void
set_dragon(string dragon_path)
{
    if (!dragon_file)
      dragon_file = dragon_path;
}

void
set_on_landed_dragon(string on_dragon_path)
{
    if (!on_dragon_file)
      on_dragon_file = on_dragon_path;
    (on_dragon_file)->set_on_flying_dragon_room_path(MASTER);
}

void
my_test()
{
    dump_array(landings);
}
