/*
 * Holiday shop for Christmas
 * Modified from the Bree Inn, Only sells things, does not buy anything
 * -- Finwe, November 2001
 */
inherit "/d/Faerun/guilds/drow/rooms/base_room.c";
inherit "/d/Shire/lib/inn";

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define ST_DIR OBJ_DIR

/* Prototype */
//void reset_room();

static object merigrin;

void
create_drow_room()
{
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");

    set_short("A small cave");
    set_long(short() + ". It has been hollowed out and is fairly deep. Cages are set against a wall, and shelves hold equipment available for sale. The ore veins continue through the walls and floor and have been polished and seem to pulse with life. A sign is posted on a shelf.\n");

    add_item(({"cages"}),
        "They are clean and different shapes and sizes, and set on shelves against the walls. The cages are made of metal and hold many animals.\n");
    add_item(({"animals"}),
        "They are well cared for and kept in cages. They have been trained by drow and may be purchased to deliver messages.\n");
    add_item(({"shelf", "tall shelves"}),
        "They are sturdy looking and made of wood. The shelves hold cages and other things for sale. A sign is posted on the shelf and shows what is for sale.\n");
    
//    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item(({"sign"}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit("start", "north");

    reset_room();

    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,0);
}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                  Drow Messengers                   |\n"+
        "\t|                                                    |\n"+
        "\t|    These animals have been captured and trained by |\n"+ 
        "\t|    the drow to deliver messages to anywhere they   |\n"+
        "\t|    are sent. All messengers cost 6 silver each.    |\n"+
        "\t|    The messengers available are:                   |\n"+
        "\t|                                                    |\n"+
        "\t|    Large Black Bat                                 |\n"+
        "\t|    Large Scaly Lizard                              |\n"+
        "\t|    Hairy Gray Mouse                                |\n"+
        "\t|    Large Black Scorpion                            |\n"+
        "\t|    Large Black Spider                              |\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}



void
reset_room()
{
//    if (!merigrin)
//    {
//        merigrin = clone_object(NPC_DIR + "merigrin");
//        merigrin->move(this_object());
//    }

}

void
init()
{
    ::init();
    init_shire_inn();
//    add_action("do_read", "read", 0);
}

int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str) 
{
//    if (!merigrin || !present(merigrin))
//    {
//        notify_fail("There is no one here to buy anything from. " +
//          "The shopkeeper has left to get more supplies.\n");
//        return 0;
//    }
    return ::do_order(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    
    switch (item_name)
    {
    case "bat":
    case "black bat":
    case "large black bat":
    case "bats":
    case "black bats":
    case "large black bats":
        order = clone_object(MESS_DIR + "bat");
        price = 72;
        break;
    case "lizard":
    case "large lizard":
    case "large scaly lizard":
    case "lizards":
    case "large lizards":
    case "large scaly lizards":
        order = clone_object(MESS_DIR + "lizard");
        price = 72;
        break;
    case "mouse":
    case "hairy mouse":
    case "hairy gray mouse":
    case "mice":
    case "hairy mice":
    case "hairy gray mice":
        order = clone_object(MESS_DIR + "mouse");
        price = 72;
        break;
    case "scorpion":
    case "large scorpion":
    case "large black bat":
    case "scorpions":
    case "black scorpions":
    case "large black scorpions":
        order = clone_object(MESS_DIR + "scorpion");
        price = 72;
        break;
    case "spider":
    case "black spider":
    case "large black spider":
    case "spiders":
    case "black spiders":
    case "large black spiders":
        order = clone_object(MESS_DIR + "spider");
        price = 72;
        break;
    }
    return (({order}) + ({price}));
}

