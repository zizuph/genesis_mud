#pragma strict_types

#include "../defs.h"

inherit (MORDOR_LIB + "room");

public void
create_room()
{
enable_orodruin();
add_prop(MORDOR_ROOM_SOUND_EFFECT, "The ground shakes while loud " +
"cracks echoes in the entire Mordor as Orodruin, Mount Doom erupts!\n");

// add_prop(MORDOR_ROOM_CREBIANS, "some black crows appears in the view " +
// "flying in circles far above you.\n");

    set_short("At the foot of Orodruin, Mount Doom"); 

    set_long("You are a the southern side of the mighty volcano Orodruin. You " +
     "sense small shakes and an immense heat radiating from " +
     "the ground.  Orodruin looms far above you, making you unsure of " +
     "traveling further as it might erupt at any time.\n");

    
    add_exit(ROOM + "moree14", "northeast");
    add_exit(ROOM + "moree12", "west");

    add_item(({ "road" }), "It's a broad and dusty road well-used by the "
 + "armies of Mordor.\n");

    add_item(({ "doom", "mt.doom", "mount doom", "orodruin" }), "Standing "
 + "alone in the center of Gorgoroth, the massive volcano dominates the "
 + "plateau with its red glow emanating from the cone.\n");

     add_item(({ "ephel duath" }), "The mountainrange Ephel Duath, also known "
 + "as the mountains of Shadow, stretches from the northwestern corner from "
 + "Udun, to Lhugdhol in the southeastern part of Mordor.\n");

     add_item(({ "ered lithui" }), "The mountainrange Ered Lithui, also known "
 + "as the ash mountains, stretches from the northwestern corner from "
 + "Udun, to Carndil in the northeastern part of Mordor.\n");

}


