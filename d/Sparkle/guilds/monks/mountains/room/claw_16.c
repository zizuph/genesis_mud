/*******************************************************************\
| CLAW_16.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 * 04/03/13 Arandir     Polished a bit
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
  set_short ("disappearing mountain path");
  set_long  ("With the cliff turning to a rocky slope, the path you tread is all " +
             "but gone under the shower of small stones. More vegetation appears, " +
             "forming dark blotchy spots on the otherwise bleached stone. With " +
             "the cliff no longer looming to your west, a broader view of the " +
             "mountains hesitantly opens in front of you.\n");

  add_exit ("claw_15", "southeast");
  add_exit ("claw_17", "northwest");

  dg_item_sky_outside ();
  mt_item_path_barely ();
  mt_item_mountains_medium ();
  mt_item_valley_heart_north ();

  add_item (({ "cliff", "face", "cliff face", "slope" }),
            "An unsurmountable obstacle just a little bit further " +
            "down, the cliff is now but a steep slope, weathered " +
            "and creased by the harsh weather.\n");

  add_item (({ "rock", "rocks", "stone", "stones", "shower", "shower of stones", "groove", "grooves" }),
            "Small stones, many with sharp edges, litter the steep slope." +
            dg_embed_when_winter (" Bits of snow appear where the rocks form shallow grooves.") +
            dg_embed_when_spring (" In places, driplets of melting snow sparkle along the shallow grooves between the rocks.") +
            dg_embed_when_summer (" Shallow grooves suggest water sometimes runs down the slope.") +
            dg_embed_when_autumn (" Frost paints some of the stones with tiny crystals.") +
            "\n");

  add_item (({ "snow", "frost", "crystal", "crystals", "shard", "shards" }),
            dg_embed_when_winter ("Bits of snow warn you of the harsh conditions further up the mountains.") +
            dg_embed_when_spring ("The last crystals of snow melt away in a sparkle of tiny water drops.") +
            dg_embed_when_summer ("No traces of snow are visible on the dry ground.") +
            dg_embed_when_autumn ("Tiny shards of frozen water line few of the stones.") +
            "\n");

  add_item (({ "vegetation", "patch", "patches", "spot", "spots", "plant", "plants" }),
            "Unlikely as it seems, the dark green patches of vegetation " +
            "suggest the steep slope is friendlier to the plants than " +
            "the steeper cliff below.\n");
}

//-------------------------------------------------------------------

