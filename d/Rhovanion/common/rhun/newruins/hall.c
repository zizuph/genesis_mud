inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>;
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("Hallway by the doors.");
    set_long("You stand in a dark hallway, the only light comes" +
            " from the open doors behind you, and you can see the " + 
            " grey skies of Rhun through their yawning portal. Three" +
            " halls lead away from the doorway, disappearing into the" +
            " dark gloom of the ruins. The halls are wide and paved" +
            " with stone, making your footsteps echo heavily through" +
            " the deserted halls as you walk across the floor. The" +
            " corridors lead south, west and east, and you can return" +
            " to the courtyard through the doors to your north.\n");

    add_exit(RHUN_DIR + "newruins/hallw","west");
    add_exit(RHUN_DIR + "newruins/halle","east");
    add_exit(RHUN_DIR + "newruins/stairs","north");
    add_exit(RHUN_DIR + "newruins/halls","south");
 
    add_item(({"halls","hallway"}),"The halls are wide and paved with" +
            " stone. The walls are like the outside walls of the fort," +
            " rough and and damp with moisture.  Dust covers everything," +
            " heavy layers of dust have settled on everything during the" +
            " centuries but in the center of each hallway you see tracks" +
            " in the dust.\n");

    add_item(({"portal","doors"}),"The portal leading outside looks even" +
            " bigger from the inside. Gaping holes are all that remains " +
            " of the wooden beams that once were used to seal these " +
            " doors as a last line of defence.\n");

    add_item("floor","The floor is made of stone and covered with centuries" +
            " of dust and debris, but as you look closer you notice" +
            " tracks in them.\n");

    add_item("tracks","In the dust covering the floor there are tracks" +
            " of what appears to be small creatures but in the hall " +
            "leading south there is a passage almost free from dust " +
            "down the center of the hall. It is impossible to tell " +
            "what kind of creature that made these tracks.\n");

    add_prop(ROOM_I_INSIDE,1);
}