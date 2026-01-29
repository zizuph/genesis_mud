inherit "/d/Kalad/common/raum/raum_normal_std";
#include "/d/Kalad/defs.h"
/* underground ruins, by Mhyrkhaan */

void
create_room()
{
    ::create_room();
    set_short("A damp square room.\n");
    set_long("You find yourself standing inside a damp, large, square room. The "+
    "walls are made of rough grey bricks, the mortar on the bricks has come loose "+
    "causeing many to have fallen to the floor in heaps. The room is supported by 4 pillars, "+
    "each one thick and sturdy looking. The staircase to the surface winds itself back "+
    "up in the center of the room. On the northern wall you see what appears to be a door, "+
    "made of some kind of metal, it's covered with grime and filth. A large ring hangs "+
    "from the door. You get a strange feeling about this place, dark and foreboding. Fear once "+
    "again grips your heart.\n");
    add_item(({"walls","bricks"}),"The walls are made of rough-cut, grey stone bricks. The mortar "+
    "has come loose, causeing the bricks to pile into shards on the floors.\n");  
    add_item(({"pillar","pillars"}),"The pillars are made of carved granite. They aprear to be very "+
    "sturdy, despite thier age.\n");  
     add_exit(RAUM(ruins/ruin),"up");
}
