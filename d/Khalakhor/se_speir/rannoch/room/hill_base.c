/* File         : /d/Khalakhor/se_speir/rannoch/room/hill_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-21         
 * Purpose      : Base hill file for the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Heavily modified/updated 01-03-18
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

string *herbs;

public void
setup_hill_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_STREET,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"grass","ground","here"}),2);
}

void
create_add_items()
{
    add_item(({"view","surroundings"}),
               "There are no trees blocking your view, and looking "
             + "east you see a great lake. West, south and north is "
             + "nothing but hills and woods.\n");
    add_item(({"ground","dirt","floor","hill"}),
               "The ground here is bare, except for grass and a "
             + "few shrubs and bushes, along with a lot of dandelions.\n");
    add_item(({"shrub","shrubs","bush","bushes"}),
               "You see only a few shrubs scattered across the "
             + "bare hill, and they do not look a bit interesting.\n");
    add_item(({"dandelion","dandelions","yellow flowers"}),
               "They grow in clusters near the treeline, small plants "
             + "with bright yellow flowers.\n");
    add_item("heather",
             "Strangely enough, no heather grows up here, though you "
           + "can see it near the edge of the forest.\n");
    add_item(({"grass","weeds","green grass"}),
               "Grass and a few weeds along with some shrubs are "
             + "all that grow up here, except the giant oak at the "
             + "very top of the hill. It is fresh green grass, however.\n");
    add_item(({"lake","loch","rannoch","inland lake"}),
               "Stretching across your east view is a great lake, "
             + "one of the many inland lakes called lochs by the "
             + "natives. The southern end of the lake disappears "
             + "from view behind high hills, but the northern end "
             + "can clearly be seen, and the gentle river that "
             + "flows out into it from the mountains. It looks "
             + "extremely deep.\n");
    add_item(({"river","stream"}), 
               "A calm river flows out from the mountains of the "
             + "north, providing the lake with fresh water. Where "
             + "the river joins the lake, a village can be seen.\n");
    add_item(({"village"}),
               "It is too far away to see anything clearly, but "
             + "there is definitely an inhibited village down there. "
             + "Small boats can be seen on the water around the "
             + "village, probably fishing boats.\n");
    add_item(({"boat","boats","fishing boat","fishing boats"}),
               "You can not make out anything special about the boats "
             + "from this distance.\n");
    add_item(({"mountains","mountain","range","mountain range",
               "wall of rock"}),
               "Looming over the lake along its east side and beyond, "
             + "stretches a mountain range, creating no shore but only "
             + "a merciless wall of rock.\n");
    add_item(({"forest","trees","woods","woodland","woodlands"}),
               "No trees grow up here, except the giant oak at the "
             + "very center of the hilltop. The forest surrounding "
             + "this hilltop stretches out in all directions.\n");
    add_item(({"hilltop"}),
               "You are not far from the top of the hill, where a "
             + "giant oak grows amidst what looks like a heap of "
             + "stones.\n");               
    add_item(({"oak","tree"}),
               "It is very large, its branches stretching out across "
             + "the whole hilltop. Around the base of its trunk you "
             + "notice a circular heap of stones.\n");
    add_item(({"heap","stones","heap of stones","heap of old stones",
               "cairn","stone circle","structure","ancient structure",
               "remains"}),
               "From here it looks just like a heap of old stones, "
             + "but it is clearly the remains of an ancient structure.\n");
    add_item(({"bird","lone bird"}),
               "You can not see what kind of bird it is, but it has been "
             + "circling high above your head since you came here.\n"); 

    add_cmd_item(({"tree","the tree","trees","up"}),
                   "climb",
                   "There are no trees here to climb.\n");

}

void
create_room_tells()
{
   add_tell(({"A chilling wind sweeps up from the east, whistling "
            + "through the grass, and then dies away.\n",
              "The leaves of the mighty oak rustle in the wind.\n",
              "You notice a lone bird circling high above you.\n",}));

}

public void
create_loch_room()
{
    set_short("Hillside");
    set_long("You are travelling through the hills, rising "
           + "above the surrounding forests. The air is clear, "
           + "the ground is soft, and you feel truly at ease. "
           + "Heather grows practically everywhere in sight, "
           + "creating a sea of pink and green around you. ");

    set_terrain(TERRAIN_RHILL);

    create_add_items();

    set_tell_time(630);
    create_room_tells();

    setup_hill_herbs();
}
