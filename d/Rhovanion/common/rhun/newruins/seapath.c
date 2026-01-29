
inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("Path along the walls");
    set_long("You are walking a narrow path close to"+
    " the walls of the old fort. From the west, you hear the"+
    " sound of breaking waves and the sounds of seagulls."+
    " The road lies to the east\n");
    
    add_exit(RHUN_DIR + "newruins/gates", "east");
    add_exit(RHUN_DIR + "newruins/seashore", "west");
    
    add_item(({"wall","walls"}),"The walls look ancient. They"+
    " are made of huge granite blocks, and you can see traces of carvings"+
    " along the top of the walls.\n");
    add_item (({"carvings"}),"The carvings have been worn smooth by"+
    " time, worse than by the gates, maybe because of the winter"+
    " storms blowing from the sea.\n");

}
 