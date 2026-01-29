/* File         : /d/Khalakhor/se_speir/rannoch/room/shore_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-21         
 * Purpose      : Base shore file for the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Heavily modified/updated 01-03-19
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

int wash_me();
string *herbs;

public void
setup_shore_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_FRESHBEACH,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"ground","here","treeline"}),2);
}

int
wash_me()
{

    write("You reach down and scoop up a handful of icy cold "
        + "water, and it is so cold when you wash your face "
        + "with it, that your head feels a bit numb.\n");

    TP->add_mana(-5);

    return 1;

}

void
create_add_items()
{
    add_item(({"ground","shore","beach","strip"}),
               "The narrow strip of bare land between the trees and "
             + "the lake consists of small pebbles and rocks.\n");
    add_item(({"pebble","pebbles","rock","rocks","gravel","stone",
               "stones","larger rocks"}),
               "The ground here is covered in small stones and larger "
             + "rocks. They are wet and rather dull to look at.\n");
    add_item(({"trees","woods","woodland","woodlands","forest",
               "old tree","old trees","grey tree","grey trees"}),
               "There are no trees here at the beach where you stand, "
             + "but the forest rises up just to your west.\n");
    add_item(({"branch","branches","gnarly branch","gnarly branches"}),
               "The trees here are old and grey, but their gnarly "
             + "branches still carries fresh green leaves.\n");
    add_item(({"leaves","twigs","twig","root","roots","leaf"}),
               "Scattered across the beach are mostly leaves, but "
             + "also a few twigs that have fallen down from above, "
             + "as well as some roots protruding from the gravel and "
             + "rocks.\n");
    add_item(({"treetop","treetops","canopy","foliage","ceiling"}),
               "The branches of the trees west of you leans out "
             + "above the whole shoreline, creating a green ceiling "
             + "above your head.\n");
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
    add_cmd_item(({"tree","the tree","trees","up"}),
                   "climb",
                   "There are no trees here to climb.\n");
    add_cmd_item(({"lake","the lake","loch","the loch","water","the water",}),
                 ({"swim","enter"}),
                   "The water is too cold to swim around in.\n");
    add_cmd_item(({"pebbles","gravel","stones","rocks","beach",
                   "strip","ground","shore"}),
                   "search",
                   "You stick your hand down into the gravel and small "
                 + "stones and poke around a little, but all you manage "
                 + "to end up with are cold and wet hands.\n");
    add_cmd_item(({"face","face with water","face in lake","face in water",
                   "my face","my face with water"}),
                   "wash",
                   wash_me);
}

void
create_room_tells()
{
   add_tell(({"A sudden wind sweeps in from the lake and into the woods.\n",
              "You notice a small boat with a high mast sailing by, far out "
            + "on the lake.\n",
              "A wave washes over the ground you stand on.\n",
              "You hear something moving in the woods to your west.\n",}));
}

public void
create_loch_room()
{
    set_short("Along the shore of the great lake");

    set_long("The forest grows very near the shore of the lake, "
           + "allowing only a strip of barren, rocky land between it "
           + "and the water. The view here is stunning, allowing a clear "
           + "view of the lake, the mountains on the opposite side, as "
           + "well as a village on the lake's northern end.\n");

    set_terrain(TERRAIN_RSHORE);

    create_add_items();

    set_tell_time(500);
    create_room_tells();

    setup_shore_herbs();
}
