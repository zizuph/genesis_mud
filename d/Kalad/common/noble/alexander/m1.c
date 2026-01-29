inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("The entrance of the House of Alexander");
    INSIDE;
    set_long("You have now stepped into the grand house of "+
        "Alexander. The walls around you are made of black oak. The "+
        "marble floor is a pattern of black and white. There are three "+
        "doorways leading out of here, one to the north and south, and "+
        "one to the east, while to the northeast and southeast, you "+
        "see small hallways that lead to spiral staircases. On the "+
        "ceiling above you, there is a giant candle holder that "+
        "holds dozens of candles, lighting up the room. Two tables "+
        "are set in front of you, with burning incense and candles. "+
        "There are statues along the east wall, as well as many "+
        "paintings.\n");
    add_item("floor","The floor is very clean. A patern of "+
        "black and white covers its entirety.\n");
    add_item("walls","The walls are black. They are polished, however, "+
        "and you can see your reflection on them.\n");
    add_item("holder","The candle holder lights up the room.\n");
    add_item("staircases","Stone staircases that spiral to the upper "+
        "level of this house.\n");
    add_item("statues","There are many statues, each one portraying "+
        "a warrior in combat armour.\n");
    add_item("paintings","They are of the armies of Lord Kabal leading "+
        "his troops into battle.\n");
    add_item("tables","The tables are made of polished oak. On them "+
        "rests candles and incense.\n");
    add_item("candles","Candles are everywhere, lighting up the room.\n");
    add_item("incense","They emmit dark, musky scents.\n");
    add_exit(NOBLE(alexander/g3),"west",0,-1,-1);
    add_exit(NOBLE(alexander/m2),"north",0,-1,-1);
    add_exit(NOBLE(alexander/m4),"northeast",0,-1,-1);
    add_exit(NOBLE(alexander/m5),"east",0,-1,-1);
    add_exit(NOBLE(alexander/m6),"southeast",0,-1,-1);
    add_exit(NOBLE(alexander/m3),"south",0,-1,-1);
}
