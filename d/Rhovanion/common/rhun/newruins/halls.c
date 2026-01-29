inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>;
#include "/d/Rhovanion/defs.h";

void create_room()
{
    set_short("South Hall.");
    set_long("This hall only continues a short distance before ending in a"+
            " doorway leading into a huge room. Through the opening you see"+
            " light filtering down from above. The floor in the hall is almost"+ 
            " free from dust.\n");

    add_exit(RHUN_DIR + "newruins/hall","north");
    add_exit(RHUN_DIR + "newruins/grand","south");
 

    add_item("floor","The floor is made of stone and almost free from dust."+
            " Judging by the rest of the fort, a lot of people (or creatures), must"+
            " have passed here recently.\n");

    add_item("doorway","The door itself has long since rotted away, but all"+
            " around the doorway you can see carvings, and right above the doorframe"+
            " a large evil-looking eye is etched deep into the stone.\n");

    add_item("carvings","The carvings depicts an elven army being crushed beneath"+
             " the onslaught of a horde of orcs and ferocious men wielding clubs.\n");

    add_item("eye", "A large eye is deeply etched into the stone above the doorway"+
             " almost like a warding symbol, but not against evil, thats for sure."+
             " The lines of the eye are deeply dyed with red, making it almost glow"+
             " in the twilight of the hall.\n"); 

    add_prop(ROOM_I_INSIDE,1);
}