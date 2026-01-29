#pragma strict_types

#include "../defs.h"

inherit (MORDOR_LIB + "room");

public void
create_room()
{
add_prop(MORDOR_ROOM_SOUND_EFFECT, "The ground shakes while loud " +
"cracks echoes in the entire Mordor as Orodruin, Mount Doom erupts!\n");

// add_prop(MORDOR_ROOM_CREBIANS, "a black crow appears in the view " +
// "flying in circles far above you, watching you closely before it " +
// "flies eastwards towards Barad-Dur.\n");

    set_short("At a broad paved road"); 

    set_long("The broad paved road leads " +
     "southwards following Ephel Duath and northwestwards " +
     "towards Carath Angren.  Orodruin can be seen in a far distance " +
     "eastwards from here.\n");

    add_exit(ROOM + "mor9", "northwest");
    add_exit(ROOM + "mor11", "south");

    add_item(({ "road" }), "It's an broad and dusty road well-used by the "
 + "armies of Mordor.\n");

    add_item(({ "doom", "mt.doom", "mount doom", "orodruin" }), "Standing "
 + "alone in the center of Gorgoroth, the massive volcano dominates the "
 + "plateau with it's red glow emanating from the cone.\n");

     add_item(({ "ephel duath" }), "The mountainrange Ephel Duath, also known "
 + "as the mountains of Shadow, stretches from the northwestern corner from "
 + "Udun, to Lhugdhol in the southeastern part of Mordor.\n");

     add_item(({ "ered lithui" }), "The mountainrange Ered Lithui, also known "
 + "as the ash mountains, stretches from the northwestern corner from "
 + "Udun, to Carndil in the northeastern part of Mordor.\n");

 }
