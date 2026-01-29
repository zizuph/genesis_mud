#pragma strict_types

#include <macros.h>

inherit "/d/Earthsea/gont/beach/karg_ships/std/base_karg_ship";

#define NUM_KARG_GUARDS 3

string fire_dependent();
string sail_status();
string rope_status();

object *guards = allocate(NUM_KARG_GUARDS);

public int guard_block();

int sail_status = 0;

void create_karg_ship_room()
{
  set_short("Middle of the longship");
  set_long("The midsection of a Karg longship. A single mast rising up " +
	   "here holds the giant red square sail bearing the emblem " +
	   "of the Kargad Empire located across the vast sea to the east. " +
	   "Rows of benches and resting long oars flank both sides " +
	   "of the ship. Peering over the starboard side of the longship " +
	   "you see the sandy beaches of Gont and the snowy mountain " +
	   "peak at the center of the island rising through " +
	   "the misty clouds. You also spot a number of Karg longships " +
	   "in formation. " +
	   "@@fire_dependent@@\n");
  add_item(({"sail", "emblem", "red sail"}),
	   "@@sail_status@@");
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
  add_item(({"mountain", "peak"}),
	   "The mountain rises steeply right through the center of " +
	   "Gont.\n");
  add_item("formation",
	   "The ships are anchored quite closely together.\n");
  add_item("mast", "@@rope_status@@\n");
  add_item("rope", "A rope holds the red sail in place. @@rope_status@@\n");
  add_exit("midfore", "fore", "@@guard_block@@");
  add_exit("midaft", "aft", "@@guard_block@@");

  reset_room();
}

string rope_status()
{
  if (sail_status)
    {
      return "The rope has been cut and no longer tied to the mast.";
    }
  else
    {
      return "The rope is tied to the mast.";
    }
}

string sail_status()
{
  if (sail_status)
    {
      return "The sail is down and billowing in the wind, revealing " +
	"the emblem of the Kargad Empire.\n";
    }
  else
    {
      return "The sail is rolled up, hiding the emblem of the " +
	"Kargad Empire.\n";
    }
}

int query_sail_status()
{
  return sail_status;
}



string fire_dependent()
{
  switch(query_fire())
    {
    case 0:
      return "";
    case 1..2:
      return "The decks of the ship is charred by fire.";
    case 3..4:
      return "Some fire damage is noticeable around the ship.";
    case 5..8:
      return "There is severe fire damage all over.";
    default:
      return "The ship is so charred that it will sink any moment now.";
    }
}

int
cut_rope(string str)
{
  object weapon, tp = this_player();
  if (parse_command(str, environment(tp),
		    "[the] 'rope' 'with' %o", weapon))
    {
      if (weapon->query_modified_pen()[1])
	{
	  sail_status = 1;
	  tp->catch_msg("You cut the rope holding the sail closed " +
			"with your " + weapon->query_short() + ".\n");
	  tell_room(environment(tp),
		    QCTNAME(tp) + " cuts the rope holding the sail closed " +
		    "with " + tp->query_possessive() + " " +
		    weapon->query_short() + ".\n", tp);
	  return 1;
	}
      tp->catch_msg("Your " + weapon->query_short() + " cannot be used " +
		    "for cutting.\n");
      return 1;
    }
  notify_fail("Cut what with what?\n");
  return 0;
}

void init()
{
  ::init();
  add_action(cut_rope, "cut");
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
