#pragma strict_types

#include <macros.h>
#include <ss_types.h>

#include <macros.h>

inherit "/d/Earthsea/gont/beach/karg_ships/std/base_karg_ship";

#define CUT_CHAIN_PEN 52
#define NUM_KARG_GUARDS 4

int chain_cut = 0;
int anchor_up = 0;

string chain_dependent();
string anchor_dependent();
mixed biggest_karg();

object *guards = allocate(NUM_KARG_GUARDS);
object captain;


void create_karg_ship_room()
{
  set_short("Front of the ship");
  set_long("You are at the front of the longship. A beautiful " +
	   "dragon head rises from the deck carved into the bow of " +
	   "the ship. Looking far ahead beyond the dragon head " +
	   "you see nothing but a part of Gont jutting out into the " +
	   "sea and a number of sea bird flying carelessly in the air. " +
	   "The other longships in the Karg fleet have anchored on the " +
	   "starboard side of this ship nearby in formation between " +
	   "this ship and the beach. A heavy metal chain rests on the " +
	   "deck here. " +
	   "@@fire_dependent@@\n");
  add_item(({"beach", "beaches"}),
	   "Waves roll into golden sand of the beach and quickly " +
	   "retreats back to the sea.\n");
  add_item(({"ship", "ships", "longship", "longships"}),
	   "The other Karg longships are of similar construct to " +
	   "this ship, but smaller.\n");
  add_item(({"bird", "birds"}),
	   "You spot a seagull, a pelican, a puffin, and an albatross.\n");
  add_item(({"chain", "metal chain", "heavy metal chain"}),
	   "@@chain_dependent@@\n");
  add_item("anchor",
	   "@@anchor_dependent@@\n");
  add_item("formation",
	   "The ships are anchored quite closely together.\n");
  add_item(({"dragon head", "head", "bow"}),
	   "The dragon head is carved into the bow of the ship to " +
	   "make the ship look more terrifying.\n");
  add_exit("midfore", "aft");
  reset_room();
}

string chain_dependent()
{
  if (chain_cut)
    {
      if (anchor_up)
	{
	  return "The heavy metal chain is connected to a " +
	    "heavy anchor currently on the deck. However, the " +
	    "chain is severed in the middle making stopping the " +
	    "ship by dropping anchor a futile effort.";
	}
      return "Presumably the heavy metal chain was connected to " +
	"the anchor currently on the seafloor securing the " +
	"longship in place. The chain has been severed leaving " +
	"the longship untethered to the anchor keep it in place.";
    }
  if (anchor_up)
    {
      return "The heavy metal chain is connected to a " +
	"heavy anchor currently on the deck.";
    }
  return "Presumably the heavy metal chain is tethered to " +
    "the anchor currently on the seafloor securing the " +
    "longship in place.";
}

string anchor_dependent()
{
  if (anchor_up)
    {
      return "The anchor is currently on deck.";
    }
  return "The anchor has been dropped.";
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

int cut_chain(string str)
{
  object weapon, tp = this_player();
  object karg;

  if (parse_command(str, environment(tp),
		    "[the] 'chain' 'with' %o.\n", weapon))
    {
      karg = biggest_karg();
      if (objectp(karg))
	{
	  karg->command("$shout Oh don't you dare do that.");
	  tp->catch_msg(QCTNAME(karg) + " steps in front of you preventing " +
			"you access to the chain.\n");
	  tell_room(QCTNAME(karg) + " steps in front of " + QTNAME(tp) +
		    " preventing " + tp->query_objective() + " access " +
		    "to the chain.\n", tp);
	  return 1;
	}
      tp->catch_msg("You raise your " + weapon->query_short() +
		    " high above your head and drop it " +
		    "on the heavy metal chain with all your might.\n");
      /* slash pen must be greater than 52 to cut the chain */
      if (weapon->query_modified_pen()[1] > CUT_CHAIN_PEN &&
	  tp->query_stat(SS_STR) > 75)
	{
	  chain_cut = 1;
	  tp->catch_msg("Your " + weapon->query_short() +
			" strikes the heavy metal chain and the " +
			"chain snaps.\n");
	  return 1;
	}
      tp->catch_msg("Your " + weapon->query_short() +
		    " strikes the heavy metal chain. " +
		    "Sparks fly everywhere, but the chain " +
		    "holds. You probably need something " +
		    "very powerful to cut this chain.\n");
      return 1;
    }
  notify_fail("Cut the chain with what?\n");
  return 0;
}

int draw_anchor(string str)
{
  object tp = this_player();
  object karg;

  if (str != "anchor")
    {
      notify_fail("Draw what? The anchor?");
      return 0;
    }
  karg = biggest_karg();
  if (objectp(karg))
    {
      karg->command("$shout Oh don't you dare do that.");
      tp->catch_msg(QCTNAME(karg) + " steps in front of you preventing " +
		    "you access to the chain.\n");
      tell_room(QCTNAME(karg) + " steps in front of " + QTNAME(tp) +
		" preventing " + tp->query_objective() + " access " +
		"to the chain.\n", tp);
      return 1;
    }
  if (anchor_up)
    {
      write("The anchor is already on the deck.\n");
      return 1;
    }
  anchor_up = 1;
  write("You slowly draw the anchor back onto the deck.\n");
  tell_room(environment(tp),
	    QCTNAME(tp) + " slowly draws the anchor back onto the deck.\n",
	    tp);
  return 1;
}

int drop_anchor(string str)
{
  object tp = this_player();
  object karg;

  if (str != "anchor")
    {
      notify_fail("Drop what? The anchor?");
      return 0;
    }
  karg = biggest_karg();
  if (objectp(karg))
    {
      karg->command("$shout Oh don't you dare do that.");
      tp->catch_msg(QCTNAME(karg) + " steps in front of you preventing " +
		    "you access to the chain.\n");
      tell_room(QCTNAME(karg) + " steps in front of " + QTNAME(tp) +
		" preventing " + tp->query_objective() + " access " +
		"to the chain.\n", tp);
      return 1;
    }
  if (!anchor_up)
    {
      write("The anchor is already off the deck.\n");
      return 1;
    }
  anchor_up = 1;
  write("You drop the anchor back into the sea.\n");
  tell_room(environment(tp),
	    QCTNAME(tp) + " drop the anchor back into the sea.\n",
	    tp);
  return 1;
}

void init()
{
  ::init();
  add_action(cut_chain, "cut");
  add_action(cut_chain, "break");
  add_action(draw_anchor, "draw");
  add_action(draw_anchor, "pull up");
  add_action(drop_anchor, "lower");
  add_action(drop_anchor, "drop");
}

public void
reset_room()
{
  int i;
  object here = this_object();

  if (!objectp(captain))
    {
      captain =
	clone_object("/d/Earthsea/gont/tenalders/npc/karg_captain");
      captain->move(here);
      captain->command("$emote strides in.\n");
    }
  for (i = 0; i < NUM_KARG_GUARDS; i++)
    {
      if (!objectp(guards[i]))
	{
	  guards[i] =
	    clone_object("/d/Earthsea/gont/tenalders/npc/karg6");
	  guards[i]->move(here);
	  captain->team_join(guards[i]);
	  guards[i]->command("$emote strides in.\n");
	}
    }
}

mixed biggest_karg()
{
  int i;
  if (objectp(captain))
    {
      return captain;
    }
  for (i = 0; i < NUM_KARG_GUARDS; i++)
    {
      if (objectp(guards[i]))
	{
	  return guards[i];
	}
    }
  return 0;
}
