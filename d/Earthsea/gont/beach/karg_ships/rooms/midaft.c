#pragma strict_types

#include <macros.h>

inherit "/d/Earthsea/gont/beach/karg_ships/std/base_karg_ship";

#define NUM_KARG_GUARDS 3
object *guards = allocate(NUM_KARG_GUARDS);
public int guard_block();

void create_karg_ship_room()
{
  set_short("Halfway to aft");
  set_long("You are halfway to the rear of the ship. " +
	   "Rows of benches and resting long oars flank both sides " +
	   "of the ship. Looking towards the rear of the ship, " +
	   "you see a small cabin. Small windows line both sides " +
	   "of the cabin door. " +
	   "@@fire_dependent@@\n");
  add_item(({"long oars", "oars"}),
	   "The long oars are used to propel the longship when the " +
	   "fair winds do not blow.\n");
  add_item("benches",
	   "The benches are currently empty.\n");
  add_item(({"window", "windows", "door", "cabin door"}),
	   "The windows and doors are all luxuriously decorated.\n");
  add_item(({"cabin"}), "The cabin is at the rear of the ship.\n");
  add_exit("midship", "fore");
  add_exit("cabin", "cabin", "@@guard_block@@");
  reset_room();
}

string fire_dependent()
{
  switch(query_fire())
    {
    case 0:
      return "";
    case 1..2:
      return "The deck of the ship is charred by fire.";
    case 3..4:
      return "Some fire damage is noticeable around the ship.";
    case 5..8:
      return "There is severe fire damage all over.";
    default:
      return "The ship is so charred that it will sink any moment now.";
    }
}

void reset_room()
{
  int i;

  for (i = 0; i < NUM_KARG_GUARDS; i++)
    {
      if (!objectp(guards[i]))
	{
	  guards[i] =
	    clone_object("/d/Earthsea/gont/tenalders/npc/karg6");
	  guards[i]->move(this_object());
	  guards[i]->command("$emote strides in.\n");
	}
    }
}

public int guard_block()
{
  int i;

  for (i = 0; i < NUM_KARG_GUARDS; i++)
    {
      if (objectp(guards[i]) && CAN_SEE(guards[i], this_player()))
	{
	  write("The " + guards[i]->query_short() + " blocks your way.\n");
	  return 1;
	}
    }
  return 0;
}
