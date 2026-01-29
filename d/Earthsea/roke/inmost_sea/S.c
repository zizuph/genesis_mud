
/* A vicious area where the sharks swim! */
/* Joshua 1995-02-06               */
#include "defs.h"
#include "/d/Earthsea/sys/room_defs.h"
inherit "/d/Earthsea/std/room";
#include <defs.h>
#include <stdproperties.h>
#include <macros.h>

#pragma strict_types;
object shark;

/* Function Headers */
public void sink(object ob);

public void
dive_shark(object shark)
{
  tell_room(environment(TP), 
	    "The shark looks disdainfully at you and dives into " +
	    "the ocean again!\n");
  shark->move_living("diving", INMOST_SEA + "dive1");
}

int
sacrifice(string str)
{
  object trident;
  string verb = query_verb(); 
  
  notify_fail(verb +" what? \n");  
  if (str=="")
    return 0;
  notify_fail("You cant " + verb +" that. \n");
  if (str == "trident" || str == "trident into sea")
    
    {
      if (present("trident",TP))
	{
	  trident = present("trident_for_sharkquest",TP);
	  write("You throw the trident with all your force "+
		"into the unruly sea. \n");
	  trident->remove_object();
	  if (!objectp(shark))
            {
	      shark = clone_object(INMOST_SEA + "monster/shark");
	      shark->move(TO);
	      
	      tell_room(environment(TP), "A gigantic white shark "+
			"suddenly emerges from "+
			"the bottom of the sea, seeking revenge on "+
			"the poor beeing that disturbed its slumber...\n");
	      set_alarm(5.0, 0.0, &dive_shark(shark));
	    }
	  return 1;
	}
      notify_fail("You don't have a trident. \n");
      return 0;
    }
  else
    return 0;  
}

void
create_earthsea_room()
{
   set_short("Open Sea");
   set_long("The boat shivers tremendously. Something just "+
      "attacked it! The boat plunges and pitches from this "+
      "sudden attack, but eventually rocks itself to "+
      "stillness, drifting on the uneasy waves. You crouches "+
      "in it, numb, unthinking, struggling to draw breath, "+
      "until at last cold water welling under your hands warns "+
      "you that you must see to the boat. The thing in the "+
      "sea could as easily had attacked you, the boat offering "+
      "only rudimentary protection...\n");
   
   
   add_item("boat", "On either side of its prow an eye is painted. "+
      "It feels like the boat is staring at you. \n");
   add_item("waves", "The waves lap feebly around you. \n");
   add_item("sea", "Out of the sea there rises storms and monsters, "+
      "but no evil powers: evil is of earth. \n");
   
   
   
   add_exit("", "east", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|S@@");
   add_exit("", "west", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|S@@");
   add_exit("", "north", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|S@@");
   add_exit("", "south", "@@enter_map:/d/Earthsea/roke/inmost_sea/"+
      "area_handler|S@@");
   
   SEA;
}

void
init()
{
   ::init();
   add_action("sacrifice", "sacrifice");
   add_action("sacrifice", "throw");
   add_action("dive_function", "dive");
}

public int
dive_function(string where)
{
   notify_fail("Dive where?\n");
   if(where != "ocean" && where != "sea" && where != "water")
      return 0;
   say(QCTNAME(TP) + " dives into the ocean!\n");
   write("You dive into the ocean.\n");
   TP->move_living("diving", INMOST_SEA + "dive1");
   return 1;
}

public void
enter_inv(object ob,object from)
{
   object waterobj;
   ::enter_inv(ob,from);
   if(waterobj = present("waterobj", ob))
      waterobj->remove_object();
   if(living(ob))
      return;
   
   
   set_alarm(1.0, 0.0, &sink(ob));
}

public void
sink(object ob)
{
   tell_room(TO,"The "+ob->query_name()+" sinks to the " +
      "bottom of the sea.\n");
   if(ob->id("shark"))
      {
      ob->move_living("diving", INMOST_SEA + "dive1");
      return;
   }
   ob->remove_object(); 
}
