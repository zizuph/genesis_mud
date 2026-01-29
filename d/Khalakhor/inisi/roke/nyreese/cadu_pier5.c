/*
 * New pier - an extra slot
 * Tapakah, 04/2009
 *
 * Added ladder with way to new Golbar camp, Treacher 08/2021
 * Made room fishing place. Added angler npc. Treacher 09/2021
 * Added a teaser to the mariners' pier to the south. Tapakah 11/2021
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/std/room";
inherit STDPIER;

int
block_me ()
{
  TP->catch_msg("A wooden boom cuts the access to the construction site. "+
                "You read the label <MARINERS OF GENESIS> on the boom.\n");
  return 1;
}

void
create_room()
{
  ::create_pier();
  set_short("East end of Cadu pier");
  set_long("You are on the pier south of Cadu.\n" +
           "This pier is currently unused.\n" +
           "The beaches and the town of Cadu are seen to the north, across "+
           "the water and to the southwest there seems to be some kind " +
           "of tower on the pier. To the east the pier finally ends, with a " +
           "small ladder leading down to the water on the northeast corner. " +
           "To the far west you see a large building, and to the south a"+
           "construction has been started.\n");

  add_exit("cadu_pier4", "west");
  add_exit("cadu_pier-mariners", "south", block_me);
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
  add_item("building", "The building looks new from here, but difficult to see " +
           "from this distance.\n");
  add_item("pier",
           "The pier stretches from here to the west, where you can see some " +
            "kind of building. At the northeast end of the pier a small ladder leads " +
            "down to the water.\n");
  add_item(({"beach", "beaches"}),
            "To the north, across the water, beaches stretches out in front of " +
            "the green vegetation.\n");
  add_item("water",
           "There is water almost all around the pier, deeper on the south " +
           "side where the big ships pass by. And more shallow on the north.\n");
  add_item("shallow water",
           "You notice a narrow passage in the water where it looks particular " +
           "shallow, starting just below a ladder on the pier towards a small " +
           "stretch of the beach.\n");
  add_item("vegetation",
           "It's a thick vegetaion, effectively blocking any views beyond the beaches.\n");
  add_item(({"ladder", "small ladder"}),
           "It's a rickety ladder but looks like it should be able to hold you if you try " +
           "to climb down from the pier.\n");
  
  BEACH;

  // Make the room fishable. Change to Nyreesean biom.
  add_prop("_live_i_can_fish", "saltwater");

  add_npc(ROKEDIR + "npc/angler", 1);
}

int
climb(string s)
{
    notify_fail("Climb where?\n");
    if (s != "d" && s != "down" && s != "ladder")
    {
        return 0;
    }

    write("You climb down the rickety ladder. It wobbles and sounds like it " +
          "may break, but you make it down to the water.\n");
    say(QCTNAME(this_player()) + " leaves climbing down the ladder with a cracking noise " +
          "for every step.\n");
    tell_room(NYREESEDIR + "golbar-camp/room/beach-water",
          "The ladder starts to make cracking noises above you as " +
          QNAME(this_player()) + " climbs down from the pier.\n");
    this_player()->move_living("M", NYREESEDIR + "golbar-camp/room/beach-water", 0, 0);
    
    return 1;
}

void
init()
{
    ::init();
    add_action(climb, "climb");
}
