/*
 * New mess hall for the AA
 * Based on teh Prancing Pony
 * -- Finwe, February 2019
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
#include "/d/Shire/sys/defs.h"
#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist", "list", "prices", "menu", "board"})

/* Prototype */
void reset_shire_room();

static object karolok;

void
create_shire_room()
{
    set_short("Mess hall");
    set_long("This is the Army's mess hall. Judging by the scraps of food lying about the crumb-covered tables and chairs, it looks like it has been appropriately named. Running the length of the north wall is a rough oak counter behind which are an array of different pots and saucepans. Scratched up on a large black board is today's selection.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(AA_DIR+"rooms/c3", "west");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}


string
pricelist_desc()
{
    return "We serve the following dishes:\n\n" +
    "\tBeef Stew . . . . . . . . . . . 1 silver\n" +
    "\tVenison Jerkey . . . . . . . . .3 silver\n" +
    "\tPheasant Soup . . . . . . . . . 4 silver\n" +
    "\tSlice of Bread. . . . . . . . . 2 silver\n" +
    "\tLoaf of Bread . . . . . . . . . 9 silver\n" +
    "\tRhubarb Crumble . . . . . . . . 1 gold\n\n" +
    "You can order for yourself and other army members\n" +
    "Do 'order <item> for <players>'.\n"+
    "You can also 'order <item> for team' to buy things for the "+
    "team mates.\n";
}

void
reset_shire_room()
{
    if (!karolok)
        karolok = clone_object(AA_DIR + "npc/karolok");

    if (!present(karolok,this_object()))
        karolok->move(this_object());
}

void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);
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

    if (!karolok || !present(karolok))
    {
        notify_fail("The cook is gone, so you can't get any food.\n");
        return 0;
    }

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

    case "pheasant soup":
    case "pheasant soups":
        order = clone_object(FOOD_DIR + "ph_soup");
        price = 48;
        break;
    case "rhubarb crumble":
    case "rhubarb crumbles":
        order = clone_object(FOOD_DIR + "crumble");
        price = 144;
        break;
    case "beef stew":
    case "beef stews":
        order = clone_object(FOOD_DIR + "beef_stew");
        price = 12;
        break;
    case "venison jerkey":
    case "venison jerkeys":
        order = clone_object(FOOD_DIR + "jerkey");
        price = 36;
        break;
    case "slice of bread":
    case "slices of bread":
    case "bread slice":
    case "bread slices":
        order = clone_object(FOOD_DIR + "bread_slice");
        price = 24;
        break;
    case "loaf of bread":
    case "loaves of bread":
    case "loafs of bread":
        order = clone_object(FOOD_DIR + "bread_loaf");
        price = 108;
        break;
 
    }
    return (({order}) + ({price}));
}


int
block_room()
{
    if (this_player()->query_wiz_level()) 
        return 0;

    write("You cannot go there yet.\n");
    return 1;
}
