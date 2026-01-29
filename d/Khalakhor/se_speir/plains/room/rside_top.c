/* File         : /d/Khalakhor/se_speir/plains/room/rside_top.c
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

#define NEEDED_FATIGUE 60

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

string climb_down();
int swim_river();

string
climb_down()
{
    if (TP->query_fatigue() <= NEEDED_FATIGUE)
    {
        return "You study the way down thoroughly, but soon "
             + "realize that in your current state you would "
             + "become tired quickly, and fall down to a "
             + "certain death. Either you need rest, or you "
             + "need to get some muscles.\n";
    }
    else
    {
        if (TP->query_skill(SS_CLIMB) > 20)
        {
            TP->move_living("climbing down the cliff",PLAINS + "rside_wall_down",1,0);
            return "";
        }
        else return "You look desperately for a way to climb down the slope, "
                  + "but you lack the skills needed to make it to the bottom.\n";
    }
}
int
swim_river()
{
    write("You begin to prepare yourself for the crossing, when "
        + "you suddenly realise the consequenses of such a thing.\n");

    say(QCTNAME(this_player())+ " watches the river intently for a moment.\n");
    return 1;
}
void
create_khalakhor_room()
{
   add_item(({"cliff","cliff wall","wall","shelf"}),
              "A sheer cliff wall lines the river's "
            + "west side, only allowing a few yards "
            + "of walkable space between it and the "
            + "river.\n");
   add_item(({"slope","rocky slope","rocks"}),
              "The waterfall crashes down a rocky slope and "
            + "down into the lower forest. The slope becomes steeper "
            + "further down, but climbing down looks possible, due "
            + "to the rocky nature of the slope permitting a "
            + "relatively safe passage.\n");
   add_item(({"river","water","stream","rapid river"}),
              "This rapid river ends here, crashing down the "
            + "rocky slope and down into the woodlands below. "
            + "You quickly realise that an attempt to even "
            + "try to cross the river would prove fatal.\n");
   add_item(({"waterfall"}),
              "Just where the river finally ends, it is joined "
            + "by a smaller river from the east, and together "
            + "they cascade down in a waterfall down the rocky "
            + "slope.\n");
   add_item(({"floor","forest floor","ground","carpet","layer",
              "patch","bare ground","rock","flat rock"}),
              "The ground here is basically flat, sloping rock with the "
            + "occasional twigs and branches brought in by the river."
            + "Apart from the weeds lining the base of the cliff "
            + "wall, nothing grows here. Due to the massive flow "
            + "of water nearby, the ground here is slippery and "
            + "treacherous.\n");
   add_item(({"twig","twigs","branch","branches"}),
             "Some have fallen down from the trees above, and some "
           + "have been brought here by the river.\n");
   add_item(({"weed","weeds","base","grass","clusters"}),
             "Different kinds of grass and weeds grows in clusters around "
           + "the base of the cliff wall.\n");
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
              "From where you stand, the only trees to see are "
            + "the ones growing below the slope and for a long "
            + "distance south, as well as the trees on the "
            + "other side of the river.\n");

   add_exit(PLAINS + "rside_19","north",0,1,0);

   add_cmd_item(({"down","down slope","down the slope"}),
                  "climb",
                   climb_down);
   add_cmd_item(({"river","the river","across river","across the river"}),
                ({"swim","wade"}),
                   swim_river);
   add_cmd_item(({"river","the river"}),
                  "cross",
                   swim_river);
   add_cmd_item(({"waterfall","the waterfall","into the waterfall"}),
                ({"dive","jump"}),
                  "There are more glorious ways to die, you know.\n");

   set_short("By a waterfall");
   set_long("   You are at the end of a narrow strip of bare land "
          + "between a loud waterfall east of you, and just "
          + "beneath the edge of a high cliff wall to your west. "
          + "The rocky ground slopes gently downwards into the "
          + "lower woodlands to your south.\n");

   set_terrain(TERRAIN_STREAM);

   create_room_tells();
}
void
create_room_tells()
{
   add_tell(({"The treetops sway high above as a strong wind "
            + "rolls in from the north.\n",
              "You catch a glimpse of movement in the forest on "
            + "the other side of the river.\n",
              "The incessant roar of the waterfall escalates to an even "
            + "louder level.\n",
              "The sound of the waterfall becomes louder than before.\n",}));

   set_tell_time(600);
}