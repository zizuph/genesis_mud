inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object guard,guard2;
void reset_room();

void
create_room()
{
    set_short("In a center room in the House of Paullus");
    set_long("You now stand at a central room where many other "+
    "doorways branch out of. The room is decorated with ornate "+
    "candles, tables and tapestries. A large painting adorns the "+
    "west wall. To the northwest, you can hear running water.\n");
    
    add_item("candles","Beautiful silver candle holders hold burning "+
    "candles that light the room.\n");
    add_item("tables","Beautiful oak tables polished to a shine. You "+
    "see little glass and crystal artwork on them.\n");
    add_item("tapestries","Finely woven tapestries. They have emblem "+
    "of the house of Paullus on them.\n");
    add_item("painting","It is a picture of an old man with a long "+
    "black mustache. Below it, you see the name: Lord Paullus I.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m17),"north",0,-1,-1);
    add_exit(NOBLE(paullus/m18),"northwest",0,-1,-1);
    add_exit(NOBLE(paullus/m15),"west",0,-1,-1);
    add_exit(NOBLE(paullus/m10),"south",0,-1,-1);
    add_exit(NOBLE(paullus/m11),"southeast",0,-1,-1);
    add_exit(NOBLE(paullus/m13),"east",0,-1,-1);
    add_exit(NOBLE(paullus/m16),"northeast",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(NOBLE(npc/house_guard_captain));
        guard->set_house_name("Paullus");
        guard->set_color_name("red-gold");
        guard->arm_me();
        guard->move_living("xxx",TO);
    }
    if(!guard2)
    {
        guard2 = clone_object(NOBLE(npc/house_guard));
        guard2->set_house_name("Paullus");
        guard2->set_color_name("red-gold");
        guard2->arm_me();
        guard2->move_living("xxx",TO);
    }
    guard->team_join(guard2);

}
