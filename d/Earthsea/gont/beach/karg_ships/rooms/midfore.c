#pragma strict_types

#include <macros.h>

inherit "/d/Earthsea/gont/beach/karg_ships/std/base_karg_ship";

#define NUM_KARG_GUARDS 3

object *guards = allocate(NUM_KARG_GUARDS);

public int guard_block();

void create_karg_ship_room()
{
  set_short("Halfway to fore");
  set_long("You are halfway to the fore of the ship. " +
	   "Rows of benches and resting long oars flank both sides " +
	   "of the ship. From this vantage point you can see the " +
	   "faint hints of a waterfall high up in the mountain " +
	   "at the center of Gont. A number of other longships are moored " +
	   "in formation nearby on the starboard side. " +
	   "@@fire_dependent@@\n");
  add_item(({"long oars", "oars"}),
	   "The long oars are used to propel the longship when the " +
	   "fair winds do not blow.\n");
  add_item("benches",
	   "The benches are currently empty.\n");
  add_item(({"beach", "beaches"}),
	   "Waves roll into golden sand of the beach and quickly " +
	   "retreats back to the sea.\n");
  add_item(({"ship", "ships", "longship", "longships"}),
	   "The other Karg longships are of similar construct to " +
	   "this ship, but smaller.\n");
  add_item(({"waterfall", "mountain"}),
	   "You look again and notice some human activity on a mesa " +
	   "near the waterfall.\n");
  add_item("formation",
	   "The ships are anchored quite closely together.\n");
  add_exit("fore", "fore", "@@guard_block@@");
  add_exit("midship", "aft");
  
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
