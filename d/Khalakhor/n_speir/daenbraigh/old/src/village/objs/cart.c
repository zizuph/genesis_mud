/*
 * Pushable cart to transfer heavy items.
 * TAPAKAH, 04/2005
 */
//inherit "/d/Khalakhor/std/container";

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

int push_cart(string str);
int load_cart(string str);
int dump_cart(string str);

#define CART_EFFORT 30
#define CART_STRENGTH 140

void
create_container()
{
  ::create_container();
  
  set_name("cart");
  set_adj("old");
  add_adj("rickety");
  set_long("An old rickety cart made of wooden planks. Wooden "       +
	   "leather-covered wheels allow you to push it easily ahead "+
	   "of you in the direction you want to go.\n");

  add_prop(CONT_I_WEIGHT,250000);
  add_prop(CONT_I_MAX_WEIGHT,2500000);
  add_prop(CONT_I_VOLUME,200000);
  add_prop(CONT_I_MAX_VOLUME,2000000);
  add_prop(OBJ_I_VALUE,1000);
  add_prop(CONT_I_RIGID,1);
  add_prop(CONT_I_HIDDEN,0);
  add_prop(CONT_I_CLOSED,0);

  add_item(({"planks"}),
	   "The thick, old planks of the cart are made of wood.\n");
  add_item(({"wheel","wheels"}),
	   "The wheels of the cart are made of wood and covered with "+
	   "leather straps.\n");

}

void
init()
{
  ::init();

  add_action(push_cart,"push");
  add_action(load_cart,"load");
  add_action(dump_cart,"dump");
  add_action(dump_cart,"unload");
}

int
push_cart(string str)
{
  string ob;
  string dir;
  string *exit;
  string ef;
  int e,i,effort;
  //  float effort;
  
  if(str)
   if(sscanf(str,"%s %s",ob,dir) == 2)
    if(ob == "cart") {
      exit = ENV(TO)->query_exit();
      e = sizeof(exit);
      for(i=0;i<e;i+=3) 
	if(exit[i+1] == dir) {
	  if(TP->query_fatigue() < CART_EFFORT) {
	    write("You feel too tired to push the cart now.\n");
	    say(QCTNAME(TP) + " turns blue trying to push the cart.\n");
	  }
	  else {
	    effort =
	      query_prop(OBJ_I_WEIGHT)*CART_EFFORT*CART_STRENGTH /
	      (query_prop(CONT_I_MAX_WEIGHT) * TP->query_stat(SS_STR));
	    write("You push the cart " + dir + " with all your strength.\n");
	    say(QCTNAME(TP) + " breathes heavily pushing the cart " + dir + "\n");
	    if(move(exit[i]))
	      write("For some reason the cart rolls back!\n");
	    TP->add_fatigue(-effort);
	  }
	  return 1;
	}
      NF0("Push cart where?\n");
    }
  NF0("Push what?\n");
  return 0;
}

int
load_cart(string str)
{
  string what;
  string where;
  object cargo;

  if(str)
    if(sscanf(str,"%s onto %s",what,where) ||
       sscanf(str,"%s on %s",what,where))
      if(where == "cart") {
	cargo = present(what,TP);
	if(!cargo)
	  cargo = present(what,ENV(TO));
	if(cargo) {
	  if(cargo->move(TO)) 
	    write("You fail to load " + cargo->query_name() + " onto the cart.\n");
	  else {
	    write("You load " + cargo->query_name() + " onto the cart.\n");
	    say(QCTNAME(TP) + " loads " + cargo->query_name() + " onto the cart.\n");
	  }
	  return 1;
	}
	else 
	  NF0("Load what onto cart?\n");
      }
  NF0("Load what?\n");
}

int
dump_cart(string str)
{
  string what;
  string where;

  object room = ENV(TO);
  
  if(str)
    if(sscanf(str,"cart into %s",where) ||
       sscanf(str,"cart in %s",where) ||
       sscanf(str,"cart %s",where)) {
      if(where == "water" ||
	 where == "sea" ||
	 where == "ocean" ||
	 where == "river" ||
	 where == "lake") {
	if(room->query_prop(ROOM_I_TYPE) == ROOM_BEACH ||
	   (room->query_terrain() & TERRAIN_COASTLAND)) {
	  write("You dump the contents of the cart into the water.\n");
	  say(QCTNAME(TP) + " heaves the cart over into the water.\n");
	  all_inventory(TO)->remove_object();
	}
	else 
	  write("There is no suitable water next to here!\n");
	return 1;
      }
      else if(where == "room" ||
	      where == "here") {
	write("You dump the contents of the cart into the room.\n");
	say(QCTNAME(TP) + " heaves the cart over into the room.\n");
	all_inventory(TO)->move(room);
	return 1;
      }
      else 
	NF0("Dump cart where?\n");
    }
    else if(str == "cart") {
      write("You dump the contents of the cart into the room.\n");
      say(QCTNAME(TP) + " heaves the cart over into the room.\n");
      all_inventory(TO)->move(room);
      return 1;
    }
  NF0("Dump what?\n");
}
