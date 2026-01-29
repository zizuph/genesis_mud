inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    object trapdoor;
 
    add_prop(ROOM_I_INSIDE, 1);
    set_short("Escape tunnel");
    set_long("   This tunnel was made for escape in case of "+
             "attacks from unfriendly neighbours. It continues north from "+
             "here. You can barely make out a trapdoor above you and "+
             " ground under your feet.\n\n");

    add_item("ground","It's soft.\n");

    add_exit(TEMPLE_DIR + "tunnel2", "north", 0);
    trapdoor=clone_object(TEMPLE_DIR + "doors/trapdoor_b");
    trapdoor->move(this_object());
}
