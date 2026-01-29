/*
 * cas_c7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Fixed with proper door and cleaned up by Tapakah, 06/2021.  
 */

/*  Ged  */

#pragma strict_types

#include "defs.h"

inherit "/std/room";

object wizard, grimoire, door;


void
reset_room()
{
  ::reset_room();

  object key;
  
  if (!wizard) {
    tell_room(TO, "An evil wizard shimmers into view before you.\n");
    wizard = clone_object(ROKEDIR + "npc/refnas");
    wizard->equip_me();
    wizard->move(TO);
    if (!present("grimoire", TO)) {
      tell_room(TO, "The evil wizard puts a grimoire on the table.\n");
      grimoire = clone_object(ROKEDIR + "obj/grimoire");
      grimoire->move(TO);
    }
    if (! present("_refnas_key", wizard)) {
      key = clone_object(REFNAS_KEY);
      key->set_key(REFNAS_KEY_ID);
      key->move(wizard);
    }
  }
  if (door->query_open())
    wizard->command("close door");
  if (! door->query_locked())
    wizard->command("lock door with key");
}

void
create_room()
{
  set_short("Castle in Cadu");
  set_long("This is the workroom of the great magician Refnas.\n" +
           "Here the walls and the floor are made out of pure " +
           "marble and gently treated with magic to get a really " +
           "scary color. But even though the walls and floor are " +
           "black, this is still the most lit up room on the entire " +
           "level. This comes from the strong magical light emitted " +
           "by the ceiling. There's also a desk here.\n");
  
  add_item("desk",
           "A large, oak desk without drawers or any kind of markings.\n");
  
  INSIDE;
  add_exit("cas_c6", "west");
  door = clone_object(REFNAS_DOOR_OUT);
  door->move(TO);
  door->set_key(REFNAS_KEY_ID);
  
  reset_room();
}
