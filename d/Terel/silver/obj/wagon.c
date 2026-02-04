/*
  Caravan wagon,
  by Udana, 03/06
*/
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#include <filter_funs.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"


/* A room that holds wagon's inside */
string inside = CARAVAN + "wagon1.c";

string colour;

/* Links and fills the inside of the wagon room */
public void create_wagon(string col, string inside_path);



/*returns 1, every caravan object has such a rutine*/
public int is_caravan();
public int is_caravan_wagon(object o);

/* This function has a very tricky body, I used parse_command rutines.*/
int climb_wagon(string a);

public string query_colour();

/*called on caravan disbanding, in that case few more actions has to be taken before removing
  this object*/
public void remove_caravan_object();

public string query_inside();

string contain_desc();


public void create_object()
{
    set_name("wagon");
    add_name("_caravan_wagon_");
    set_short("@@query_colour@@ painted wagon");
    set_long("It's a large wagon, pulled by mules. You see:\n @@contain_desc@@ on it.\n");
    add_prop(OBJ_M_NO_GET, 1);
}

public string query_inside()
{
 return inside;
}

public string query_colour()
{
 return colour;
}

public void create_wagon(string col, string inside_path)
{
  inside = inside_path;
  colour = col;
  set_adj(col);
}


public void init()

{

  ::init();

  add_action(climb_wagon, "climb");

  add_action(climb_wagon, "enter");

}


public int add_passenger(object o)

{
  if((inside)->room_left() <= 0)
  {
    write("The wagon is filled with people, there is no room left.\n");
    return 1;
  }
  write("You climb on the " + colour + " wagon...\n");
  say(QCTNAME(TP) + " climbs up the wagon.\n");
  if(member_array(TO, all_inventory(E(o))) != - 1)
    o->move_living("M", inside);
  return 1;
}


public int is_caravan_wagon(object o)
{
	if(member_array("_caravan_wagon_", o->query_names()))
		return 1;
	return 0;
}

int climb_wagon(string a)

{
  notify_fail(CAP(QVB) + " what?\n");
  object *climbed_wagons;
  if(!strlen(a))
    return 0;
  if(!parse_command(a, E(TO), "%i", climbed_wagons))
    return 0;
  climbed_wagons = NORMAL_ACCESS(climbed_wagons, "is_caravan_wagon", TO);   
  if(sizeof(climbed_wagons) == 1 && climbed_wagons[0] == TO)
  {
   add_passenger(TP);
   return 1;
  }
  return 0;
}



public int is_caravan()
{
  return inside->is_manned();
}



public void remove_caravan_object()

{

  inside->remove_caravan_object();

  remove_object();

}



string contain_desc()
{
  return CAP(find_object(inside)->contain_desc(TP));
}