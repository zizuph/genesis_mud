/*
 * Pub at Telseron
 * Updated by Finwe September 1996
 */
 
inherit "/std/room";
inherit "/lib/pub";
 
#include "/d/Emerald/defs.h"
 
void
reset_room()
{
    object drunk;
 
    drunk = present("drunk1", this_object());
    if (!drunk || drunk->query_name()=="corpse") {
        drunk = clone_object(TOWNSHIP_DIR + "npc/drunk1");
        drunk->move_living("into a room", this_object());
    }
    drunk = present("drunk2", this_object());
    if (!drunk || drunk->query_name()=="corpse") {
        drunk = clone_object(TOWNSHIP_DIR + "npc/drunk2");
        drunk->move_living("into a room", this_object());
    }
}
 
void
create_room()
{
    set_short("The Singing Tree");
    set_long( "   You are in a pub bustling with activity. All around " +
        "you, elves are enjoying a good time. Some sing raucous "+
        "drinking songs while others look around, peacably enjoyimg "+
        "their private thoughts. The bar is busy now as it fills up "+
        "up with orders. On the wall behind the bar, the bartender " +
        "has posted a menu.\n");
 
    add_item("menu", "Fine lettering is inscribed on it.\n");
    add_item(({ "table", "tables" }), "The tables are made of hard, "+
        "lignt wood, and are polished to a shine.\n");        
    add_item("chairs", "They are sturdily built, even though some " +
        "look as if they were used in a recent barfight.\n");
 
    add_cmd_item("menu", "read", "@@read");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_drink( ({ "ale", "ales" }),
        "ale", "thick", 
        100, 10, 20, 0, 0,
        "It is quite thick with foam on top.\n", 0);
    add_drink( ({ "beer", "beers", "draft beer", "draft beers" }),
        "beer", "draft", 
        100, 13, 30, 0, 0,
        "It has a good sized head with a deep colour.\n", 0);
    add_drink( ({ "wine", "wines", "house wine", "house wines" }),
        "wine", "house", 
        150, 20, 80, 0, 0,
        "There is a sweet smell from it, like that of blueberry.\n", 0);
    add_drink( ({ "special", "specials", "house special", 
        "house specials" }), "special", "house", 
        230, 35, 160, 0, 0,
        "This looks like some homebrew stuff with a spicy smell.\n", 0);
    add_drink( ({ "mindblaster", "blaster", "mindblasters", "blasters" }),
        "mindblaster", "strong", 
        350, 50, 250, 0, 0,
        "This doesn't look like it would be smart to drink...\n", 0);
 
    add_exit(TOWNSHIP_DIR + "rd16", "out");
 
    reset_room();
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
    return "  Ale               20 cc\n"+
           "  Draft beer        30 cc\n"+
           "  House wine        80 cc\n"+
           "  House special    160 cc\n"+
           "  Mindblaster      250 cc\n\n"+
           "Use 'buy ale with silver' of you want to be "+
           "specific as to what kind of coins you wish to use, or "+
           "'test buy wine' to see what would happen if you typed "+
           "'buy wine'. 'buy 7 special' would get you 7 house specials, "+
           "but it would take some time to tap them all up.\n" ;
}
