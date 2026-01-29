/*
 * cas_c6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Fixed with proper door and cleaned up by Tapakah, 06/2021.
 */

/*  Ged  */

#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit "/std/room";

#define FARM_INTACT 1
#define FARM_BROKEN 0

object door, butler;
int farm_state = FARM_INTACT;

int
query_open ()
{
  if (! door)
    return 1;
  return door->query_open();
}

void
reset_room ()
{
  ::reset_room();

  object key;
  if (!butler) {
    butler = clone_object(ROKEDIR + "npc/butler");
    tell_room(TO, "An old spooky butler arrives.\n");
    butler->move(TO);
  }
  if (! present("_refnas_key", butler)) {
    key = clone_object(REFNAS_KEY);
    key->set_key(REFNAS_KEY_ID);
    key->move(butler);
  }
  if (door->query_open())
    butler->command("close door");
  if (! door->query_locked())
    butler->command("lock door with key");
  farm_state = FARM_INTACT;
}

void
react_butler ()
{

  if (butler) {
    butler->command("scream");
    butler->command("emote falls to his knees trying to catch "+
                         "the crawling leeches");
    butler->command("drop key");
  }
  else {
    write("The absent butler roars\n");
  }
}

int
smash_farm (string str)
{
  object butler_here;
  
  if (str != "farm" && str != "compartment")
    NF0(capitalize(query_verb()) + " what?");

  if (farm_state == FARM_BROKEN) {
    write("The leech farm has already been smashed.\n");
    return 1;
  }
  write("You smash the farm with the leeches.\n");
  tell_room(TO, QCTNAME(TP) + " smashes the farm with the leeches.\n", TP);

  farm_state = FARM_BROKEN;
  set_alarm(1.0, 0.0, react_butler);
  return 1;
}

string
my_long ()
{
  return "This room looks like a huge foyer with hangers on the walls.\n" +
    "The walls seem to stretch on forever upwards. It's probably " +
    "some magical illusion. The light from the ceiling is much stronger " +
    "here. You see an exit to the west and a sturdy, wooden door to the " +
    "east. By the northern wall there's a large glass compartment "+
    "with a number of dark wiggly things in it.\n" +
    (farm_state == FARM_BROKEN ? "It is currently smashed.\n" : "");
}

void
init ()
{
  ::init();
  add_action(smash_farm, "smash");
  add_action(smash_farm, "break");
}

void
create_room ()
{
  set_short("Castle in Cadu - Refnas Foyer");
  set_long(my_long);
  
  add_exit("cas_c5", "west");
  add_exit("cas_c7", "east");

  add_item(({"leeches", "leech", "farm", "compartment", "wiggly things"}),
           "The butler seems to be growing some leeches for his master.\n");
  reset_room();

  door = clone_object(REFNAS_DOOR_IN);
  door->move(TO);
  door->set_key(REFNAS_KEY_ID);
}
