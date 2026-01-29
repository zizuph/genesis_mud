/* File:          /d/Khalakhor/ship/macdunn/std/pier_base.c
 * Creator:       Teth
 * Date:          September 6, 1997
 * Modifications: Teth, Feb 5, 1998 - more add_items
 * Purpose:       The pier base room, inherited by all others.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit LIBPIER;
inherit "/d/Khalakhor/std/room";

void
create_pier()
{
}

void
reset_pier()
{
}

int *
query_global_coords()
{
  return ({0, 0});
}

void
reset_room ()
{
  reset_pier();
}

string
extra_long ()
{
  return "";
}

void
create_khalakhor_room()
{
    set_short("a pier in Port Macdunn");
    set_long("   This is a wooden pier in Port Macdunn. The dock " +
             "juts out into Cala Fasgadh, the harbour which makes Port " +
             "Macdunn a safe place for a ship to rest during a storm. From " +
             "Cala Fasgadh, departing ships sail into Lear Min, the sea " +
             "between Fon Frith and Ruighe Cuideal of the continent " +
             "of Khalakhor. Lear Min becomes Cuan Siorruidh, " +
             "the ocean surrounding Khalakhor. The moorings of the pier " +
             "are covered with barnacles, but only as high as the level " +
             "the water reaches during high tide. The town of Port Macdunn " +
             "rests on a small rise to the north.\n" + extra_long());

    add_item(({"frith","fon frith"}),"The southwest speir of " +
      "Khalakhor, it is impossible to see from this distance.\n");
    add_item(({"ruighe cuideal","ruighe"}),"The southeast speir " +
      "of Khalakhor, it is where you are presently standing.\n");
    add_item(({"southeast speir","present speir"}),"This is where " +
      "you are.\n");
    add_item(({"southwest speir","distant speir"}),"You are " +
      "unable to see it.\n");
    add_item(({"speir","speirs"}),"Which one?\n");
    add_item(({"pier","wooden pier"}),"The wooden pier is in excellent " +
      "shape, indicating the pride that the citizens of Port Macdunn " +
      "take in their community.\n");
    add_item("sky","The sky is partly cloudy, and is more grey than " +
      "blue.\n");
    add_item(({"town","port","port town","port macdunn"}),"The town " +
      "of Port Macdunn resides to the north, on a slight rise. It " +
      "seems to be a fair size, and well-developed, as most of the " +
      "buildings seem to be made of stone.\n");
    add_item(({"buildings","stone buildings"}),"A closer look at the " +
      "buildings is possible by leaving the piers and wandering the " +
      "town.\n");
    add_item("dock","@@query_long");
    add_item(({"harbour","cala fasgadh"}),"This harbour is nearly " +
      "enclosed by land, buffering the effects of any storm on the " +
      "local waters.\n");
    add_item(({"waters","local waters"}),"The local waters are a " +
      "dark-blue green.\n");
    add_item("land","It is the land of Khalakhor, and more precisely, " +
      "the southeastern speir of the continent.\n");
    add_item(({"sea","lear min"}),"Past the harbour, the deep blue " +
      "waters of Lear Min can be seen.\n");
    add_item(({"ocean","cuan siorruidh"}),"Far in the distance, the " +
      "waters of Cuan Siorruidh can barely be gleaned.\n");
    add_item("moorings","These wooden posts support the pier, " +
      "having been embedded deep in the depths of the water, and " +
      "stabilized by boulders.\n");
    add_item(({"posts","wooden posts"}),"The wooden posts support " +
      "the pier, preventing it from falling into the harbour!\n");
    add_item(({"post","wooden post"}),"Each wooden post differs only " +
      "in location, and the number of barnacles covering it.\n");
    add_item("boulders","They are too deep under the water to be " +
      "seen.\n");
    add_item("water","The water of the harbour is dark blue-green. " +
      "The waves on top of the water constantly hit the shore.\n");
    add_item("shore","The shore is rocky, making movement and " +
      "direct landing on the shore impossible.\n");
    add_item("waves","The waves are dampened by the effect of " +
      "the harbour, and would only be dangerous to those who cannot " +
      "swim.\n");
    add_item(({"small rise","rise"}),"The small rise protects Port " +
      "Macdunn from the extremely rare high waves of storms.\n");
    add_item("barnacle","It is impossible to look at just one " +
      "barnacle. Try looking at all of them.\n");
    add_item("barnacles","The barnacles cover the moorings, layer upon " +
      "layer.\n");
    add_cmd_item("barnacles",({"get","take"}),"They are just out of " +
      "reach!\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PIER | TERRAIN_SALTWATER);

    create_pier();
    reset_room();
}

string
go_tide (string destination)
{
  if((this_player()->query_skill(SS_SWIM) <= 9) &&
     (this_player()->query_prop_setting(LIVE_I_MAY_DROWN) == 0)) {
    write("You almost jump off the pier, but realize suddenly " +
          "that your lack of swimming prowess might drown you!\n");
    say(QCTNAME(this_player()) + " almost jumps off the pier, " +
        "but turns back in fear.\n");
    this_player()->add_prop(LIVE_I_MAY_DROWN, 1);
    return "";
  }

  write("You jump off the pier into the harbour!\n");
  set_dircmd("harbour");
  this_player()->move_living("diving into the harbour",
                             MACDUNN_DIR + destination, 1, 0);
  return "";
 
}
string
go_tide1 ()
{
  return go_tide("tide1");
}

string
go_tide2 ()
{
  return go_tide("tide2");
}
