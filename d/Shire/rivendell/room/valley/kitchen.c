/*
 * Kitchen in Imladris
 * By Finwe, February 1998
 *
 * Changed cloning process for supplies
 * Removed some not active functions
 * By Taveren, January 2001
 */

#pragma strict_types

#include "local.h"
#include <money.h>

inherit HOUSE_IN_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define SUPL_DIR "/d/Shire/rivendell/room/valley/supplies/"

/* Prototype */
void reset_shire_room();

static object iorius;

void
create_house_room()
{
    set_short("The kitchen of Imladris");
    set_long("This is the great kitchen of Imladris. It is " +
      "always busy here as elves love to eat, nevertheless, " +
      "no one seems rushed or in a hurry. Wonderful smells of " +
      "delicious foods fill the air making your mouth " +
      "water. There is a menu on the wall.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("wall", "It's used to secure the inn from wind and rain.\n");
    add_item("banner", "It's made out of some kind of tissue.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");

    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    add_item(({"west windows", "western windows", "west window",
        "western windows"}), "@@west_down@@Outside a garden " +
        "surrounds the kitchen.\n");
    add_item(({"south windows", "southern windows", "south window",
        "southern windows"}), "@@south_down@@Outside a garden " +
        "surrounds the kitchen.\n");

    num_of_windows=2;


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); /* screw realism. Keep it open */
    add_exit(VALLEY_DIR + "d_cor07", "north");
    set_alarm(1.0, 0.0, reset_shire_room);
    add_prop(ROOM_I_NO_CLEANUP,1);
    configure_shire_inn();

}
/*
string
mirror_desc()
{
    if (!iorius || !present(iorius)) 
    return "You find no mirror.\n";
    return "The mirror reflects the pricelist on the wall.\n"+
    "You are having a hard time reading the prices this way.\n";
}
*/
string
pricelist_desc()
{
    return "\n"+
    "Menu\n"+
    "============\n"+
    "Fresh golden mead . . . . . . . 20 cc\n" +
    "Pint of nectar. . . . . . . . . 50 cc\n\n" +

    "Slice of bread  . . . . . . . . 15 cc\n" +
    "Small brick of cheese . . . . . 45 cc\n" +
    "Steamed mushrooms . . . . . . . 75 cc\n\n\n" +

    "You may order for other players as well as order for "+
    "mulitple players.\n"+
    "Try using 'order <num> <item> for <players>' similar to how you "+
    "target players with an emotion.\n"+
    "You may also 'order <num> <item> for team' to buy things " +
    "for teammates.\n";
}
void
reset_shire_room()
{

    if (!iorius)
    iorius = clone_object(RNPC_DIR + "iorius");
    if (!present(iorius,this_object()))
    iorius->move(this_object());
         tell_room(TO, QCTNAME(iorius)+" walks in.\n");
         iorius->command("emote inspects his shelves for " +
             "spices and supplies.");

}

void
init()
{
    ::init();
    //    init_office();
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
    /*
    if (!iorius || !present(iorius))
    {
        notify_fail("There is no-one here to buy anything from.\n"+
          "The innkeeper has been killed!\n");
        return 0;
    }
    */
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
    case "mead":
    case "golden mead":
    case "fresh golden mead":
    case "meads":
    case "cold cold meads":
    case "nice cold mead":
    case "0":
        order = clone_object(SUPL_DIR + "mead");
        price = 20;
    break;
    case "nectar":
    case "pint":
    case "pint of nectar":
    case "pints":
    case "pints of nectar":
    case "1":
        order = clone_object(SUPL_DIR + "nectar");
        price = 50;
    break;
    case "slice of bread":
    case "slices of bread":
    case "bread":
    case "2":
        order = clone_object(SUPL_DIR + "bread");
        price = 15;
    break;
    case "small brick of cheese":
    case "brick":
    case "cheese":
    case "brick of cheese":
    case "brick of cheese":
    case "bricks of cheese":
    case "small bricks of cheese":
    case "3":
        order = clone_object(SUPL_DIR + "cheese");
        price = 45;
    break;
    case "mushrooms":
    case "steamed mushrooms":
    case "basket of steamed mushrooms":
    case "baskets of steamed mushrooms":
    case "baskets of mushrooms":
    case "basket of mushrooms":
    case "4":
        order = clone_object(SUPL_DIR + "mrooms");
        price = 75;
    break;

    }
    return (({order}) + ({price}));
}
