/*
 * Ported to new ship system and rerouted to Sparkle
 * Tapakah, 10/2008
 */

#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>

inherit STDPIER;

void
create_pier()
{
  set_short("At a golden pier");
  set_long(break_string(
    "You are standing on a a pier covered with bricks of pure gold. The pier "+
    "leads into a high, well-kept, tower, with a golden roof. An entrance to "+
    "it is to the north. A small white building is to the west. The surrounding "+
    "island looks quite tropical, with palmtrees and thick vegetation. The pier "+
    "is in a lagoon with green, warm water. This place looks like paradise.\n",60));
	
  OUTSIDE;
  LIGHT;

  add_item("pier",
    "The pier is covered with golden bricks and very neat. No dirt is present "+
    "here. Everything is shining and extremely well-kept.\n");
  add_item(({"brick","bricks"}),
    "These bricks are for real! It _is_ gold. You haven't seen such wealth "+
    "before.\n");
  add_item("tower",
    "The tower is quite high, painted white, and has a golden roof. The sign of "+
    "The Rich Men's Club hangs on the wall.\n");
  add_item("roof",
    "More gold...these guys must be RICH!\n");
  add_item("entrance",
    "North is an entrance to a tower, west to a small white building.\n");
  add_item("island",
    "This island is like your dreams of paradise. Nice climate. the right light, "+
    "great beaches... Yes, everything for a perfect life.\n");
  add_item(({"palm","palms","palmtree","palmtrees"}),
    "They are high with large leaves, and coconuts.\n");
  add_item(({"coconut","coconuts","nut","nuts"}),
    "They look tasty... Hope that you don't get hit in the head by one though.\n");
  add_item("paradise",
    "Why don't you ask Death to send you there, or rather the opposite... ;)");
  add_item("lagoon",
    "The lagoon is quite big and not very deep. Many different species of fishes "+
    "live in waters like these. Perfect for diving and bathing.\n");
  add_item("water",
    "The water looks warm. It would be nice to take a little swim in it.\n");
  add_item("building",
    "It's a small building with a sign hanging over the door. The sign says: "+
   "GnOMeS AcCOUnT SErvIcE.\n");

  add_exit(RMCROOMS+"joining","north");
  add_exit(RMCROOMS+"gnomes","west");

  add_pier_entry(MASTER_OB(this_object()), "Golden Island", "Pier to Sparkle");    
}

void
init()
{
  ::init();

  add_action("swim","swim");
  add_action("dive","dive");
  add_action("enter","enter");
  add_action("get","get");
  add_action("get","take");
}

int
swim()
{
  write("As you start to take off your clothes when a guard enters.\n"+
    "The guard says: Sorry, nudism is not allowed here! Put on your clothes "+
    "again!\nThe guard leaves north.\n");
  say(QCTNAME(TP)+" starts to take off "+TP->query_possessive()+" clothes.\nA "+
    "guard enters.\nThe guard tells "+QTNAME(TP)+" to put on "+TP->query_possessive()+
    " clothes again, since nudism isn't allowed here.\nThe guard leaves north.\n");

  return 1;
}

int
dive(string str)
{
  NF("Dive into what?\n");

  if (str == "into water")
  {
    swim();
    return 1;
  }
  return 0;
}

int
enter(string str)
{
  NF("Enter what?\n");

  if (str == "water")
  {
    swim();
    return 1;
  }
  return 0;
}

int
get(string str)
{
  NF("Get/Take what?\n");

  if (str == "brick" || str == "bricks")
  {
    write("As you try to get one of the bricks, a guard rushes in and prevents "+
      "you from doing it. He also calls you some nasty nicknames before he leaves "+
      "again.\n");
    say("As "+QTNAME(TP)+" tries to get one of the bricks, a guard rushes in "+
      "and prevents "+TP->query_objective()+" from doing it. The guard calls "+
      QTNAME(TP)+" some really nasty nicknames before he leaves again.\n");
    return 1;
  }
  return 0;
}

