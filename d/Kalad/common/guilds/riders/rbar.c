inherit "/d/Kalad/room_std.c";
inherit "/lib/pub";
#include "/d/Kalad/defs.h"

object ob;

void
create_room()
{
    set_short("The Lone Wolf");
    set_long("This is Lone Wolf Pub, a social hangout for all the "+
    "members of the Dark Alliance to come and relax. There are 4 large "+
    "ebony tables in here, each has a long bench on each side. The "+
    "light in here is bright, and comes from many oil lamps on the "+
    "walls, and in the centers of the tables. There is a large Goblin "+
    "standing behind a bar along the north wall. Ready to serve you up "+
    "what you wish to order. The air here smells of buring oil lamps, "+
    "and fresh food.\n");
    add_item("bar", "A polished ebony bar with a menu on it.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("benches","these benches are made of ebony, and very sturdy.\n"); 
    add_item("tables", "They are smooth ebony tabels, shiny and clean.\n");
    add_cmd_item("menu", "read", "@@read");
    add_prop(ROOM_I_INSIDE,1); 
    add_drink( ({ "ale", "ales", "amber", "amber ale" }),
        "ale", "amber", 100, 20, 75, 0, 0,
        "It has a light amber collor, and smeels wonderful.\n", 0);
    add_drink( ({ "draft", "drafts", "rider's", "rider's draft" }),
        "draft","rider's", 100, 20, 100, 0, 0,
        "This draft is a dark beer, brewed by the Riders of the Red Fang.\n", 0);
    add_drink( ({ "brandy", "brandys", "strong", "strong brandy" }),
        "brandy", "strong", 100, 30, 150, 0, 0,
        "This is a stong, hearty brandy, very tasty, it has a bite!.\n", 0);
    add_drink( ({ "special", "specials","rider","rider special" }),
        "special", "rider", 100, 50, 300, 0, 0,
        "This is a Rider special, a bunch of mixed, really strong alchohol!.\n", 0);
    add_food( ({ "chicken","soup","hot chicken soup" }),
        "soup", "chicken", 60, 60, 0, 0,"hot, spicy chicken soup, mmmmm....\n", 0);
    add_food( ({ "sirloin","thanar", "grilled","sirloins", "grilled thanar sirloins" }),
        "sirloin", "thanar", 120, 160, "grilled thanar sirloin",
        "grilled thanar sirloins","Hot, freshly grilled, Thanarim sirloin, with a light glaze.\n", 0);
    add_food(({"bloody","huge","huge bloody steak","steak","steaks"}),
        "steak","huge",900,750,"huge bloody steak",
        "huge bloody steaks","A huge Raw Steak.\n",0);
    add_exit(COMMON(guilds/riders/train),"south",0,-1,-1);
    reset_room();
        ob = clone_object(COMMON(/guilds/riders/cook));
        ob->move(TO);
}


void
init()
{
    ::init(); 
    init_pub();
}

int
read(string str)
{
    write(
        "+------------------------------------+\n"+
        "|            The Lone Wolf           |\n"+
        "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"+
        "| Amber Ale      -  75 cc            |\n"+
        "| Rider's Draft  - 100 cc            |\n"+
        "| Strong Brandy  - 150 cc            |\n"+
        "| Rider Special  - 300 cc            |\n"+
        "|                                    |\n"+
        "| Hot Chicken Soup         -   60 cc |\n"+
        "| Grilled Thanar Sirloin   -  160 cc |\n"+
        "| Huge Bloody Steak        -  750 cc |\n"+   
        "|                                    |\n"+
        "+------------------------------------+\n");
    return 1;
}

