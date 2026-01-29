inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a bedroom of the House of Paullus");
    set_long("You have now entered a beautiful bedroom. "+
    "Along the smooth, wooden walls, a bed, table and "+
    "chest is placed. The ground is covered with a soft, "+
    "warm rug. There is also a fireplace in the corner, and "+
    "it lights this room up and fills it with warmth. "+
    "Beautiful decorations dot the room.\n");
    
    add_item("fireplace","The wood in it is nearly burnt out, "+
    "leaving some faint, but hot glowing embers that warm the "+
    "room.\n");
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

    add_exit(NOBLE(paullus/m14),"south",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/maid));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

