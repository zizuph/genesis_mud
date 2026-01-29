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

    set_short("At the entrance of Sammath Naur, the fires of Doom"); 

    set_long("You are at the eastern side of the mighty volcano Orodruin.  The " +
     "pathway ends here leaving nothing but an entrance into the side of the " +
     "cone, known as the entrance to Sammath Naur, the Doorway of Fire.  You " +
     "sense small shakes and an immense heat radiating from " +
     "the cone.  The top of Orodruin looms above you, making you unsure of " +
     "traveling further as it might erupt at any time.  The " +
     "Black tower; Barad-Dur, appears into the view, still far away " +
     "northeastwards, but yet you feel feel its presence and a " +
     "terrible feeling of being watched...\n");

    
    add_exit(ROOM + "oro8", "south");
    add_exit(ROOM + "cha1", "west");


    add_item(({ "path" }), "This is a small cobbered pathway that ensnares " 
 + "upwards at the side of the cone of Orodruin.\n");

    add_item(({ "doom", "mt.doom", "mount doom", "orodruin" }), "Standing "
 + "alone in the center of Gorgoroth, the massive volcano dominates the "
 + "plateau with its red glow emanating from the cone.\n");

     add_item(({ "ephel duath" }), "The mountainrange Ephel Duath, also known "
 + "as the mountains of Shadow, stretches from the northwestern corner from "
 + "Udun, to Lhugdhol in the southeastern part of Mordor.\n");

     add_item(({ "ered lithui" }), "The mountainrange Ered Lithui, also known "
 + "as the ash mountains, stretches from the northwestern corner from "
 + "Udun, to Carndil in the northeastern part of Mordor.\n");

     add_item(({ "barad-dur", "tower", "contruction" }), "Builth on a spur of the " +
   "Ered Lithui, this Citadel of Darkness consists of a great central tower with " +
   "nine radial towers connected to it by fortified bridges. No stronger fortress " +
   "exists in Middle-Earth by the rumours, and it's the main seat of the " +
   "Dark Lord's Power!\n");
  
}

void my_message_func() 
{
tell_room(TO, "BLABLABLABLABLABLABLALBABLABLA");
}

int reset_room()
{
add_prop(MORDOR_ROOM_SOUND_EFFECT, my_message_func);
}

int
do_call(string str)
{
//NF ("call what?\n");

if (!str)
{
return 0;
}

if (TP->query_wiz_level() == 0)
{
write("You cannot call anything except your Death.\n");
return 1;
}

if (str == "enforcements")
{
tell_room(TO, "You can hear someone approaching!\n");
}
return 1;
}

public void
init()
{
add_action("do_call", "demand");

::init();
}