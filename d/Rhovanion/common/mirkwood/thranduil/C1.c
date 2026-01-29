inherit "/d/Rhovanion/lib/caves.c";
#include "/d/Rhovanion/defs.h"
#include "def.h"
#include "/sys/macros.h"
#include "door.h"

object player;

create_cave()
{
  object door, key;
  
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(4);
  set_long(" This is a cell in which Thranduil throws those who are "
	   + "not obeying his laws.");
  add_prop("_prisoner_free", 0);
  
  door = clone_object(THIS_DIR + "C1_doori");
  door -> move(TO);
  door -> set_key(SILVER);
}

void
test_tour(object player)
{
  object note;
  if (present("Thranduil_Tour_Note",player))
    {
      note = present("Thranduil_Tour_Note",player);
      if (note -> query_tour_no() != 2) return;
      note -> set_tour_done();
      call_out("tour_done",5,player);
      return;
    }
  return;
}

tour_done(player)
  {
  tell_object(player,"A dwarf creeps out of the corner, looks carefully " +
	      "at you, then he thanks you profoundly and runs out of " +
	      "the door. You have solved the task and can return to the " +
	      "Advisor. \n");
  return 1;
  }

void init()
{
  ;
  ::init();
  test_tour(TP);
  tour_done(player);
}
