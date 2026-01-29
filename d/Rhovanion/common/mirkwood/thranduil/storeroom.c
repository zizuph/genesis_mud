inherit "/d/Rhovanion/lib/caves.c";

#include "def.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h";

object player;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(3);
  set_long("This is a storeroom at the bottom of the tunnels, you " +
	   "see some barrels lying around. " +
	   " \n");
  
  add_item(({"barrel","barrels"}),
	   "The barrels looks like they have been thouroughly cleaned.\n");
  
  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave49","south",0,1);
}


test_tour(object player)
{
  object note;
  if (present("Thranduil_Tour_Note",player)) 
    {
      note = present("Thranduil_Tour_Note",player);   
      if (note->query_tour_no() != 1) return;
      note->set_tour_done();
      call_out("tour_done",5,player);
      return;
    }
  return;
}

tour_done(player)
{
  tell_object(player,"This is the place that the Advisor told you to find.\n"+
              "You can now return to him.\n");
  return 1;
}

void
  init()
{
  ;
  ::init();
  test_tour(TP); 
  tour_done(player);
}
