/* /d/Ansalon/goodlund/nethosak/docks/room/kitchen01.c
   Glain

   Get a pan/pot of the ceiling.
   Open stove and search ashes for a ring.
   One of the crates/barrels is open and has some food in it.
   One of the minotaurs will be in here.  (the cook)
   Read markings, based on language skill.
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

object door;

void reset_nethosak_room()
{
   return;
}

void create_nethosak_room()
{
    set_short("Kitchen of the Storm Seeker");
    set_long(
      "The smell of old food hangs in the air of this small room.  " +
      "Pots and pans of all shapes and sizes hang from the ceiling " +
      "and walls, clanging together noisily as the ship gently " +
      "rocks in the bay.  A few pots are resting on the large " +
      "stove nestled in the corner.  Next to the stove is a wooden " +
      "counter, the surface of which is covered in chip marks and " +
      "scratches from its frequent use.  The rest of the room is " +
      "taken up by a large number of barrels and crates, leaving " +
      "little space to work with.  A large wooden door leads back " +
      "to the outside.\n");    

    add_item("smell",
      "It appears to be coming from the pots that have been left " +
      "on the stove.\n");
    add_item("pots",
      "All of the pots and pans that are hanging about the room " +
      "have been scrubbed clean, with no traces of food to be " +
      "found on them.  You might even be able to reach one of " +
      "of them if you tried.  On the stove a few pots still sit, " +
      "the remnants of food inside now caked on.  You do not envy " +
      "the poor soul who will have to clean this mess.\n");
    add_item("stove",
      "A simple wood stove that, from the number of food stains " +
      "on it, appears to get a lot of use.  A few pots are still " +
      "sitting on it.  The hatch to put wood inside is shut.\n");
    add_item("pans",
      "All of the pots and pans that are hanging about the room " +
      "have been scrubbed clean, with no traces of food to be " +
      "found on them.  You might even be able to reach one of " +
      "then if you tried.\n");
    add_item("hatch",
      "A small metal door to the stove.  A handle allows you to " +
      "open it safely when the stove is going, so no one gets " +
      "burned.\n");
    add_item(({"counter","wooden counter"}),
      "Chip marks and scratches adorn the surface of this long " +
      "wooden counter, testifying to its age and usefulness.  " +
      "It has been recently cleaned and scrubbed down.\n");
    add_item(({"crates","barrels"}),
      "Wooden barrels and crates have been crammed into this " +
      "room.  All appear to be tightly sealed and each have " +
      "markings on their surface that you might be able to " +
      "make out on closer examination.\n");
    add_item("markings",
      "Each crate has burned into it several markings.  You " +
      "could try and read them.\n");
    add_item("door",
      "A large wooden door, set against the aft wall, leads " +
      "back out to the main deck.\n");

    door = clone_object(DOBJ + "door1b.c");
    door->move(TO);

    reset_nethosak_room();
} 