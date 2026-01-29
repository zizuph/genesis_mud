inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Escape tunnel");
    set_long("   You are in the tunnel which makes you feel very far "+ 
             "under the ground. Despite the fact that the tunnel is so "+
             "narrow that your elbows touch the walls all the "+
             "time, the ceiling is so high that it's unreachable. "+
             "A few tree roots hang down from the ceiling. It's dark here except "+
             "for a dim light south of you. The tunnel continues north and south.\n\n");

    add_item("ground","It's soft.\n");
    add_item(({"wall","walls"}), "Walls are made of hard ground.\n");
    add_item("ceiling","It's unreachable. Few tree roots hang out "+
              "from it.\n");
    add_item("roots","It seems there is a tree growing over the tunnel.\n");

    add_exit(TEMPLE_DIR + "tunnel1", "south", 0);
    add_exit(TEMPLE_DIR + "tunnel3", "north", 0);
}
