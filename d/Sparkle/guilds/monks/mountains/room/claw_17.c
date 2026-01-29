/*******************************************************************\
| CLAW_17.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 * 04/03/18 Arandir     Polished up
 *
 */

#include <tasks.h>
#include <ss_types.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("rocky outcropping");
  set_long  ("The rocky cliff that you stand upon extends into space in a proud " +
             "gesture that ends with a sudden drop, opening a view of a valley " +
             "below. A group of stunted pine trees lines the edge of the cliff, " +
             "leaning towards the empty space with a longing of a caged bird. " +
             "The wind is very strong here, whizzing and soughing over the few " +
             "branches of the pines.\n");

  add_exit ("claw_16", "southeast");

  dg_item_sky_outside ();
  mt_item_mountains_medium ();
  mt_item_valley_heart_north ();

  add_item (({ "slope", "cliff", "face", "cliff face" }),
            "The steep slope to your south brought you here, to the very " +
            "end of a rocky cliff that stands tall over the valley below.\n");

  add_item (({ "drop", "edge" }),
            dg_embed_when_night ("The feeling of emptiness envelops you as you try to make anything out in the " +
                                 "darkness below. The cliff drops too far down for that though.") +
            dg_embed_when_not_night ("The cliff drops a way down, making the valley below look almost picturesque " +
                                     "with all the miniature details you can make out. With the occassional gusts " +
                                     "of wind getting pretty strong, you make sure to stand near one of the stunted " +
                                     "trees and hold on to it when leaning over the edge, not really eager to get " +
                                     "closer too quickly.") +
            "\n");

  add_item (({ "tree", "trees", "pine", "pines", "pine tree", "pine trees" }),
            "A few pine trees huddle together at the edge of the cliff, desperately " +
            "clinching to the hard rock of the mountains. Their trunks have been " +
            "forced into bent and twisted shapes by the wind, defining a strangely " +
            "attractive kind of natural beauty.\n");
}

//-------------------------------------------------------------------

