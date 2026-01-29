/* File         : /d/Khalakhor/se_speir/plains/room/rside_22.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-24   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

int climb_cliff();

int
climb_cliff()
{
    write("You are too unskilled for that kind of climb.\n");

    say(QCTNAME(this_player())+ " studies the cliff wall for "
                              + "a brief moment.\n");
    return 1;
}
void
create_khalakhor_room()
{
   add_item(({"cliff","cliff wall","wall","shelf"}),
              "The cliff wall encircles this patch "
            + "of bare ground between the river and "
            + "the higher located woodlands about "
            + "twenty feet above. Attempting to climb "
            + "it here might prove hazardous, although "
            + "it does not seem entirely devoid of "
            + "footholds and crevices.\n");
   add_item(({"foothold","footholds","crevice","crevices"}),
              "The crevices run vertically along the cliff "
            + "wall, and could be used as vital ascension "
            + "points for an experienced climber.\n");
   add_item(({"river","water","stream","rapid river"}),
              "This very rapid river is in a great hurry "
            + "southwards, running through a deep furrow in "
            + "the woodlands. From here, you have a clear "
            + "view of where this river meets another river "
            + "coming from the east, and that meeting results "
            + "in a waterfall further south.\n");
   add_item(({"waterfall"}),
              "Just where the river finally ends, it is joined "
            + "by a smaller river from the east, and together "
            + "they cascade down in a waterfall.\n");
   add_item(({"floor","forest floor","ground","carpet","layer",
              "patch","bare ground","rock","flat rock"}),
              "The ground here is basically flat, sloping rock with the "
            + "occasional twigs and branches brought in by the river. "
            + "Apart from the weeds lining the base of the cliff "
            + "wall, nothing grows down here.\n");
   add_item(({"twig","twigs","branch","branches"}),
             "Some have fallen down from the trees above, and some "
           + "have been brought here by the river.\n");
   add_item(({"weed","weeds","base","grass","clusters"}),
             "Different kinds of grass and weeds grows in clusters around "
           + "the base of the cliff wall.\n");
   add_item(({"cone","cones","pine cones","pine cone"}),
              "You see a few of pine cones on the ground, having "
            + "fallen down from the trees high above.\n");
   add_item(({"needles","pine needles"}),
              "You can't see many pine needles here, as they are "
            + "carried away by the wind when they fall from "
            + "the trees.\n");
   add_item(({"other side","deciduous wood","hardwood"}),
              "The trees on the other side of the river are "
            + "all trees carrying leaves, and they look very "
            + "old.\n");
   add_item(({"trees","tree","pine tree","pine trees","pine",
              "pines","woods","forest","woodlands"}),
              "No trees grow where you stand now, and the only "
            + "ones you see are the pine trees that grown high "
            + "above your head, as well as the trees on the "
            + "other side of the river.\n");

   add_exit(PLAINS + "rside_24","northeast",0,1,0);
   add_exit(PLAINS + "rside_23","east",0,1,0);
   add_exit(PLAINS + "rside_21","south",0,1,0);
   add_exit(PLAINS + "rside_20","southwest",0,1,0);

   add_cmd_item("cliff","climb",climb_cliff);
   add_cmd_item(({"river"}),"swim",
            "You are too far from the water.\n");

   set_short("By a rapid river");
   set_long("   You are on a wide patch of bare land between a "
          + "furious river a few steps east of you, and right "
          + "beneath the edge of a high cliff wall to your "
          + "west.\n");

   set_terrain(TERRAIN_STREAM);

   create_room_tells();
}
void
create_room_tells()
{
   add_tell(({"The fierce winds die down for a moment, and the river "
            + "becomes less loud, if only briefly.\n",
              "The treetops sway high above as a strong wind "
            + "rolls in from the north.\n",
              "You catch a glimpse of movement in the forest on "
            + "the other side of the river.\n",
              "The incessant roar of the river escalates to an even "
            + "louder level.\n",
              "The sound of the flowing water becomes louder than before.\n",}));

   set_tell_time(600);
}
