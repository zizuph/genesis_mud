/* File         : /d/Khalakhor/se_speir/plains/room/rside_btm.c
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
#include "plains.h"

#define NEEDED_FATIGUE 60

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

string climb_cliff();
int swim_river();
int dive_pool();
int climb_ridge();

string
climb_cliff()
{
    if (TP->query_fatigue() <= NEEDED_FATIGUE)
    {
        return "You study the cliff wall thoroughly, but soon "
             + "realize that in your current state you would "
             + "become tired quickly, and fall down to a "
             + "certain death. Either you need rest, or you "
             + "need to get some muscles.\n";
    }
    else
    {
        if (TP->query_skill(SS_CLIMB) > 20)
        {
            TP->move_living("climbing up the cliff",PLAINS + "rside_wall_up",1,0);
            return "";
        }
        else return "You look desperately for a way to climb up the cliff, "
                  + "but you lack the skills needed to reach the top safely.\n";
    }
}

int
climb_ridge()
{
    write("You are too unskilled for an attempt like this.\n");

    say(QCTNAME(this_player())+ " looks hesitantly up towards the "
                              + "crest of the ridge.\n");
    return 1;
}

int
swim_river()
{
    write("You begin to prepare yourself for the crossing, when "
        + "you suddenly realise the consequenses of such a "
        + "reckless attempt.\n");

    say(QCTNAME(this_player())+ " watches the water intently for a while, "
                              + "then shudders and looks away.\n");
    return 1;
}

int
dive_pool()
{
    write("After a quick inspection of the pool of water, you "
        + "decide that you won't dive into it after all, due "
        + "to its depth and temperature.\n");

    say(QCTNAME(this_player())+ " sticks a hand down into the pool "
                              + "of water.\n");

    return 1;
}

void
create_khalakhor_room()
{
   add_item(({"cliff","cliff wall","wall","shelf"}),
              "The cliff wall does not seem totally devoid "
            + "of footholds, and since it gently slopes "
            + "on it's way skywards, you could probably attempt "
            + "to climb it.\n");
   add_item(({"ridge","earth wall"}),
              "The ridge to your west has been created by the "
            + "water carving through the land. It is quite steep, "
            + "and looks too unsafe to climb up at this point.\n");
   add_item(({"river","water","stream","rapid river"}),
              "The river begins here, from where the masses of "
            + "water crashes down from high above, forming a "
            + "deep pool before rushing off. It is quite "
            + "rapid, and trying to cross could prove fatal. It "
            + "flows away south into the lower woodlands.\n");
   add_item(({"waterfall"}),
              "The waterfall cascades loudly downwards from the "
            + "cliffs high above, eventually reaching the lower "
            + "woodlands with much noise. Where it hits the ground, "
            + "the water gathers in a deep pool, and then, eager to "
            + "continue, rushes off southwest in the form of "
            + "a newly born river.\n");
   add_item(({"pool","deep pool"}),
              "The pool is where the water falling down from above "
            + "gathers before flowing away southwest. It seems "
            + "quite deep, and the water looks icy cold.\n");
   add_item(({"trees","tree","pine tree","pine trees","pine",
              "pines","woods","forest","woodlands","treetops","treetop"}),
              "No trees grow where you stand now, and the only "
            + "ones you see are the pine trees that grown high "
            + "above your head, as well as the trees on the "
            + "other side of the river.\n");
   add_item(({"underbrush","undergrowth","bush","bushes","ground",
              "floor","forest floor","vegetation","plants"}),
              "The ground you stand on is soft and wet, completely "
            + "covered by dense vegetation. You wonder how deep "
            + "down the actual ground is.\n");
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

   add_exit(PLAINS + "rside_18","southwest",0,7,0);

   add_cmd_item(({"cliff","the cliff","up the cliff",
                  "cliff wall","the cliff wall","up the cliff wall",
                  "wall","the wall","up the wall"}),
                  "climb",
                   climb_cliff);
   add_cmd_item(({"ridge","the ridge","up ridge","up the ridge","up"}),
                  "climb",
                   climb_ridge);
   add_cmd_item(({"river","the river","across river","across the river"}),
                ({"swim","wade"}),
                   swim_river);
   add_cmd_item(({"river","the river"}),
                  "cross",
                   swim_river);
   add_cmd_item(({"pool","the pool","into the pool","deep pool",
                  "the deep pool","into the deep pool","water",
                  "the water","into the water"}),
                ({"dive","jump"}),
                   dive_pool);

   set_short("At the base of a waterfall");
   set_long("   You stand at the base of a waterfall, cascading "
          + "down from the cliffs high above. The water immediately "
          + "runs southwards after reaching the ground, creating the "
          + "river east of you. Your way north is blocked by the "
          + "cliff wall, and west by the ridge, making this place "
          + "a dead end.\n");

   create_room_tells();
}
void
create_room_tells()
{
   add_tell(({"The treetops sway high above as a strong wind "
            + "rolls in from the south.\n",
              "You catch a glimpse of movement in the forest on "
            + "the other side of the river.\n",
              "You hear a faint sploshing sound from the south.\n",
              "The sound of the waterfall becomes louder than before.\n",}));

   set_tell_time(800);
}

