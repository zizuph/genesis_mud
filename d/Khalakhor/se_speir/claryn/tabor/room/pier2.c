/*
 * pier2.c
 *
 * This is the small pier at Tabor Sogh - not much here initially
 *
 * Now accepts a line from Port Macdunn, Tapakah, 05/2009
 * Modified for a teaser, Tapakah, 10/2021
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

#include "room.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

#define  PIER_COORDS ({-1, 5})
 
 
// room coordinate functions
int * query_local_coords ()  { return PIER_COORDS;    }
int * query_global_coords () { return VILLAGE_COORDS; }

int
block_me ()
{
  TP->catch_msg("A wooden boom cuts the access to the construction site. "+
                "You read the label <MARINERS OF GENESIS> on the boom.\n");
  return 1;
}

void
create_khalakhor_room ()
{
  set_short("small wooden pier");
  set_long("   You are standing on a small wooden pier which jutts "+
           "out over the waters of Lear Min, the great southern sea. "+
           "To the east is the sleepy fishing village called Tabor Sogh, "+
           "a small settlement of stone buildings with thatched roofs. "+
           "You see a dusty dirt road that runs north and south along the "+
           "rocky shoreline, lined with the homes and other buildings of the "+
           "village along its east side. The waves of the sea lap endlessly "+
           "against the rotting wooden poles which hold the pier above "+
           "the cold waters.\n"+
           "You notice that some extension works has been started on the "+
           "pier in the western direction.\n");
 
  add_item("pier",
           "It is an old pier made simply of logs bound together, supported "+
           "by large wooden poles which hold it above the sea's cold "+
           "waters. It seems old and rotten, but strangely sturdy.\n");
  add_item("poles",
           "Large wooden poles, made of the trunks of thick trees, stand "+
           "straight out of the sea and hold up the pier. Constantly "+
           "battered by the waves of the sea, they look rather water-logged "+
           "and rotten, though strangely sturdy.\n");
  add_item("road",
           "To the east is a dusty dirt road, hardpacked by years of "+
           "trodding feet and wagon wheels. It runs along the shoreline "+
           "to the north and south, fronting the small stone buildings "+
           "of the village. You can step off the pier onto it to the "+
           "east.\n");
  add_item(({"town","settlement","village","tabor sogh","Tabor Sogh"}),
           "Tabor Sogh is an old fishing village, but has never " +
           "grown much beyond a handful of homes and a few " +
           "necessities for fishing. The village consists of " +
           "a single road upon which all buildings are built " +
           "of dark grey stone.\n");
  add_item(({"sky"}),
           "Looking up, you see the sky is partially overcast, " +
           "with thick grey clouds drifting through an " +
           "otherwise blue sky.\n");
  add_item(({"clouds","thick clouds", "grey clouds",
             "thick grey clouds"}),
           "Thick clouds drift lazily across the sky high above " +
           "your head.\n");
  add_item(({"buildings","stone buildings","low buildings","homes"}),
           "A number of buildings occupy the village, most " +
           "look pretty much identical with stone walls and " +
           "thatched roofs.\n");
  add_item(({"wall","walls"}),
           "The walls of all the buildings are are made " +
           "in a similar fashion, of thin plates of dark " +
           "grey stone which have been neatly stacked together. " +
           "No mortar or packing is evident, but the walls " +
           "appear quite sturdily built regardless.\n");
  add_item(({"stones","blocks"}),
           "The stones which make up the walls of most of " +
           "the buildings here are thin plates of dark grey " +
           "stone, carefully stacked to form walls for the " +
           "buildings.\n");
  add_item(({"shore","shoreline"}),
           "It is a rocky shoreline which disappears into the distance "+
           "to the north and south, lapped by the colds waters of the sea.\n");
  add_item(({"water","sea","Lear Min","lear min","waves"}),
           "The waters of Lear Min are are slate grey in colour, " +
           "with white caps topping the larger of the waves in " +
           "the choppy waters as far as the eye can see.\n");
  reset_room();
  add_exit("pier", "east");
  add_exit("pier3", "west", block_me);
  add_pier_entry(MASTER_OB(TO), "Tabor Sogh", "Cabotage to Port Macdunn");
  initialize_pier();
}
