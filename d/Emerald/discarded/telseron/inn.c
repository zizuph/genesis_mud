/*
 * Inn at Telseron
 * Updated by Finwe September 1996
 */
inherit "/std/room";
inherit "/lib/pub";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Dimly lit inn");
    set_long( "You are in a dimly lit inn. All around the room, "+
        "there are small tables with chairs drawn up to them. At some "+
        "of the tables, some travellers sit, enjoying a quiet time. "+
        "On the wall someone has hung a menu.\n" );
 
    add_item("menu", "There is writing on it.\n");
    add_item(({ "chair", "chairs" }), "They are made of dark wood and "+
        "looks quite solid.\n");
    add_item(({ "table", "tables" }), "The tables are made of hard, light "+
        "wood, and are polished to a shine.\n");
 
    add_cmd_item("menu", "read", "@@read");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_drink( ({ "ale", "ales", "watered", "watered ale" }),
        "ale", "watered", 100, 4, 12, 0, 0,
        "It looks like it's watered out some.\n", 0);
 
    add_food( ({ "potato", "potato soup", "soup", "soups" }),
        "soup", "potato", 65, 80, "plate of potato soup",
        "plates of potato soup",
        "It has potatoes floating around in it, but "+
        "doesn't look like anything you'd particularily want to eat, "+
        "as the potatoes doesn't look all that good.\n" , 0);
    add_food( ({ "meat", "meat soup", "soup", "soups" }),
        "soup", "meat", 100, 120, "plate of meat soup",
        "plates of meat soup",
        "It looks like quite a mouthful, and has large "+
        "lumps of fat and what you think might be meat floating "+
        "around in it.\n" , 0);
    add_food( ({ "steak", "steaks" }),
        "steak", "large", 200, 220, 0, 0,
        "It looks quite delicious. Your mouth start to water.\n", 0);
    add_food( ({ "side", "lamb", "sides", "lambs", "side of lamb",
        "sides of lamb" }),
        "lamb", ({ "side", "of" }), 350, 380, "side of lamb",
        "sides of lamb",
        "It is quite large. You're not sure you can eat it all.\n", 0);
 
    add_exit(TOWNSHIP_DIR + "rd16", "out", 0);
}
 
void
init()
{
    ::init();
    init_pub();
}
 
string
read(string str)
{
    return "  Watered ale       12 cc\n"+
           "  Potato soup       80 cc\n"+
           "  Meat soup        120 cc\n"+
           "  Steak            220 cc\n"+
           "  Side of lamb     380 cc\n\n"+
            "Use 'buy ale with silver' if you want to be "+
           "specific as to what kind of coins you wish to use, "+
           "or 'test buy steak' to see what would happen if you typed "+
           "'buy steak'. 'buy 5 ale' would get you 5 ales, but it takes "+
           "some time to tap them all up.\n" ;
}
