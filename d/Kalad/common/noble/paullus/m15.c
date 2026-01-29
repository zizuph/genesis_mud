inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In a bedroom of the House of Paullus");
    set_long("You now find yourself in a very beautiful "+
    "bedroom. The ground is made of polished wood, and there "+
    "is a warm fur rug on the floor. In one corner, you see "+
    "a delicate canopy bed. In another corner, a table sits with "+
    "two chairs on either side. The walls are covered with "+
    "beautiful decorations. There is a chest in the corner.\n");
    
    add_item("chest","Nothing but old clothes in it.\n");
    add_item("rug","It looks like it is made out of rabbit pelts, "+
    "and is very soft to the touch.\n");
    add_item("bed","A large fluffy bed with a white satin sheet haning "+
    "over it.\n");
    add_item("table","A large wooden table. A bowl of fruit is placed "+
    "on it.\n");
    add_item("chairs","Two chairs surrond the table.\n");
    add_item("decorations","Paintings and tapestries adorn this room.\n");
    add_item(({"fruit","bowl"}),"A large bowl of yummy fruit.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m14),"east",0,-1,-1);
}
