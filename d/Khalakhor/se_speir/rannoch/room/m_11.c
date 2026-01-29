/* File         : /d/Khalakhor/se_speir/rannoch/room/m_11.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
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
#include "room.h"

inherit "/d/Khalakhor/std/room";

void
create_add_items()
{

    add_item(({"view","surroundings"}),
               "The great lake is before you, deep, dark and cold "
             + "underneath its glittering surface, perhaps holding "
             + "many secrets.\n");
    add_item("surface",
               "The lake is calm, and the surface is like a mirror.\n");
    add_item(({"lake","loch","water","inland lake","rannoch"}),
               "Stretching across your east view is a great lake, one "
             + "of the many inland lakes called lochs by the natives. "
             + "The southern end of the lake disappears from view "
             + "behind high hills and cliffs, but the northern end "
             + "can clearly be seen, and the gentle river that flows "
             + "out from the mountains. It looks very deep.\n");
    add_item(({"river","stream"}), 
               "A gentle river flows out from the mountains of the "
             + "north, the lake's primary source of water. Just where "
             + "the river joins the lake, a village has been built "
             + "on both sides.\n");
    add_item(({"mountains","mountain","range","mountain range",
               "wall","mountain wall"}),
               "Looming over the lake along its east side and "
             + "beyond, stretches a mountain range, creating no "
             + "shore but only a merciless wall of rock.\n");
    add_item(({"village","buildings"}),
               "Built on both the western and eastern banks of the "
             + "river, the village consists of many grey-brown "
             + "buildings. The eastern half of the village " 
             + "is built on a hillside, whose southern flank is just "
             + "a sheer rock wall dropping down into the lake. You "
             + "can see a few boats out on the lake near the village, "
             + "and you also notice a wooden wall around the western "
             + "half of the village.\n");
    add_item(({"wall","wooden wall","village wall"}),
               "It is a wall made of thick wooden poles, but you can " 
             + "see it protecting the village's western flank, since "
             + "the whole south side faces the lake, the eastern side "
             + "climbs upward and into a mountainside. The northern "
             + "parts can not, obviously, be seen from here.\n");
    add_item(({"boat","boats","fishing boat","fishing boats"}),
               "The fishing boats are long, wooden vessels with "
             + "tall masts and greyish-white sails. Most of them "
             + "seem to be docked in the village or staying close "
             + "to it, but a few are far away as well.\n");
    add_item(({"cliff","cliffs","hill","slope","hillside"}),
               "The land east of the river slopes upwards only to "
             + "stop where the mountains takes over. The "
             + "lake cuts through the hill, creating a sheer cliff wall "
             + "that does not look that safe to live next to.\n");
    add_item(({"dock","small dock","simple dock","wooden dock"}),
               "A simple wooden dock, just long enough for a "
             + "few small boats to dock. It is made of a few poles "
             + "with thick planks nailed to it, and secured with "
             + "ropes.\n");
    add_item(({"pole","poles","wooden pole","wooden poles"}),
               "The poles have been driven deep into the lake bottom, "
             + "providing support for the planks you stand on. The "
             + "planks have been secured to the supports with nails and "
             + "some rope.\n");
    add_item(({"support","supports","long planks","beam","long beam",
               "long beams"}),
               "Nailed to the sides of the poles are long, horizontal "
             + "beams, serving as support for the planks you stand on.\n");
    add_item(({"nail","nails"}),
               "They are ordinary iron nails, hammered through the planks "
             + "and into the supports of the poles.\n");
    add_item(({"rope","lengths of rope","plain rope"}),
               "It is plain rope, tied around the poles to lend some "
             + "additional support for the planks.\n");
    add_item(({"plank","thick plank","thick planks","planks","board","boards"}),
               "The planks that the dock is made of are dark and smooth, "
             + "and in good shape.\n");

    add_cmd_item(({"tree","the tree","trees","up"}),
                   "climb",
                   "There are no trees here to climb.\n");
    add_cmd_item(({"lake","the lake","loch","the loch","water","the water",}),
                 ({"swim","enter"}),
                   "The water is too cold to swim around in.\n");

    add_exit(ROOM + "m_10.c","west",0,1,0);

    clone_here(NPC + "iasgair")->move(this_object());

}

void
create_room_tells()
{

   add_tell(({"The wooden boards you are standing on creaks loudly.\n",
              "A sudden wind sweeps in from the lake and into the woods.\n",
              "You notice a small boat with a high mast sailing by, far out "
            + "on the lake.\n",
              "You hear something moving in the woods to your west.\n",}));
}

public void
create_khalakhor_room()
{

   set_short("On a small dock");
   set_long("You stand on a small wooden dock, and it moves slightly " +
            "as you walk on it. No boat is docked here at the moment, " +
            "but it looks as if it is used often.\n");

    set_terrain(TERRAIN_RPIER);

    create_add_items();

    set_tell_time(550);
    create_room_tells();
}
