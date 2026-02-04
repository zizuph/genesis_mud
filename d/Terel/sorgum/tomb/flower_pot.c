/*
 * inspired by Janus' strange gizmo
 */

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "/d/Terel/common/terel_std_rec.h"
#include "tomb.h"

int on_safe = 0;

init()
{
     add_action("mix", "mix");
     add_action("ignite", "ignite");
     add_action("set", "set");
     ::init();
}

create_container()
{
         set_name("flower pot");
	 set_short("flower pot");
	 set_pshort("flower pots");
	 set_long("It's a porcelin flower pot with a small hole in the " +
		  "bottom.\n");
	 set_adj(({"porcelin", "flower"}));
	 
	 add_prop(OBJ_I_VALUE, 10 + random(20));

	 add_prop(CONT_I_WEIGHT, 1000);
	 add_prop(CONT_I_MAX_WEIGHT, 1200);
	 add_prop(CONT_I_VOLUME, 2000);
	 add_prop(CONT_I_MAX_VOLUME, 4000);
	 add_prop(CONT_I_TRANSP, 1);
	 add_prop(CONT_I_RIGID, 1);
}

mix(string str)
{
     object flakes, al_powder;
     object *objlist;
     int extra_objs, i;
     int ok;

     flakes = present("rust");
     al_powder = present("aluminum");

     if (flakes && al_powder) {
	  ok = 1;
	  flakes->remove_object();
	  al_powder->remove_object();
     }

     objlist = all_inventory(TO);
     extra_objs = sizeof(objlist);

     for (i = 0; i < sizeof(objlist); i++) {
	  if ((objlist[i]->query_prop("is_reactive") == 1) ||
	      (objlist[i]->query_prop("is_mixable") == 1)) {
	       if (objlist[i]->query_prop("is_explosive") == 0)
		    objlist[i]->remove_object();
	  }
     }

     say(QCTNAME(TP) + " mixes something in the flower pot\n");
     
     if ((extra_objs == 0) && (ok == 1)) {
	  write(BSN("You mix the ingredients together carefully and " +
		    "produce a new compound.\n"));
	  clone_object(TOMBDIR + "thermit")->move(TO);
	  return 1;
     }

     if (extra_objs > 0) {
	  write("You grind the contents of the pot together and produce " +
		"a mess in the flower pot\n");
	  add_item(({"mess", "contents"}), BSN("An gooey mess of mixed " +
					      "ingredients\n"));
     }
     else {
	     if (!ok) write("There is not much to mix\n");
	}

     return 1;
}
	      
set(string str)
{
     object safe;
     object *objlist;

     safe = present("trunk", environment(TP));
     if (!safe) safe = present("trunk", environment(TO));
     
     if ((str == "pot on trunk") || (str == "flower pot on trunk")) {
	  if (safe) {
	       write("You set the flower pot on the trunk.\n");
	       say(QCTNAME(TP) + "puts the flower pot on the trunk.\n");
	       on_safe = 1;
	  }
	  else {
	       write("There is no trunk here.\n");
	  }
     }
     else
	  {
	    write(BSN(
		   "You were going to set the pot down on something " +
		   "but you change your mind at the last second.\n"));
       }

     return 1;
}

ignite(string str)
{
     object ribbon, thermit;
     object gunpowder, craked_safe;
     string self;
     int i;

     ribbon = present("ribbon");
     if (!ribbon) {
	  write("You need something to ignite the mixture with.\n");
	  return 1;
     }

     write(BSN(
	 "You ignite the ribbon and it burns so brilliantly it hurts you're " +
	 "eyes to look at it."));

     say(BSN(QCTNAME(TP) +" ignites the ribbon and it burns so brialliantly " +
	     "it hurts your eyes to look at it."));
     
     gunpowder = present("gunpowder");
     if (gunpowder) {
	  write("The black powder in the pot ignites and explodes!\n");
	  say("The black powder in the pot ignites and explodes!\n");
	  write("You are hurt by the explosion!\n");
	  say(QCTNAME(TP) + " is hurt by the explosion\n");
	  TP->reduce_hit_point(2000);
	  TP->do_die(TO);
	  TO->remove_object();
	  return 1;
     }

     thermit = present("thermit");

     if (ribbon && thermit) {

	  say("The ribbon ignites the thermit in the pot " +
	      "and it burns VERY hot.  The molten mixture seeps " +
              "through the hole in the bottom of the pot..."
	  );

	  write(
	      "The ribbon ignites the thermit in the pot " +
	      "and it burns VERY hot.  The molten mixture seeps " +
              "through the hole in the bottom of the pot...\n"
	  );  
	  
	  if (on_safe) {
	       say(BSN(
		   "The thermit slags the surface of the trunk and melts " +
		   "a large hole in it."));

	       write(BSN(
		   "The thermit slags the surface of the trunk and melts " +
		   "a large hole in it."));	       

	       objlist = all_inventory(TP);
	       for (i = 0; i < sizeof(objlist); i++) {
		    if (objlist[i]->query_prop("_melted") == 0) {
			 objlist[i]->remove_object();
			 craked_safe = clone_object(TOMBDIR + "craked_safe");
			 craked_safe->move(environment(TP));
			 return 1;
		    }
		    else
			 if (objlist[i]->query_prop("_melted") == 1) {
			      write("Someone else has already melted it!\n");
			      return 1;
			 }
	       }
		    
	  else {
    	          if (environment(TO) == TP) {

		       self = TP -> query_possessive();
		       if (self == "his") self = "him";
		       
		       write("The burning mixture seeps on to you and " +
			     "melts you!  You are severly burned!\n");
		       say(BSN(
                         "You smell buring flesh as the thermit seeps " +
		          "onto " + QCTNAME(TP) + " and MELTS " + self  +"!"));

		       TP->reduce_hit_point(5000);
		       TP->do_die(TO);
		  }
		  else {
		         tell_room("and slags a hole in the floor.\n");
			 add_item("hole", "A small hole created by something "+
				  "melting\n");
		    }
	     } 

	  TO->remove_object();
	  return 1;
     }

     tell_room("The mixture in flower pot ignites, but nothing happens\n");
     ribbon->remove_object();
     return 1;
     
}
     

