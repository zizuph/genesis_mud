/*
 * Kitchen in Imladris
 * By Finwe, February 1998
 */

#pragma strict_types

#include "local.h"
#include <money.h>

inherit HOUSE_IN_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define FOOD_DIR "/d/Shire/rivendell/room/valley/food/"
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
    /*
    add_item("sign","The sign has writing on it.\n");
    add_cmd_item("sign","read","The sign reads:\nHere you may:\n"+
      "<ask for a delivery tour> To get a delivery task.\n"+
      "<deliver>  To deliver an assigned task.\n"+
      "<return>  To return a failed delivery.\n");
    */
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    //    add_item("wall", "It's used to secure the inn from wind and rain.\n");
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
        order = clone_object(FOOD_DIR + "mead");
        order = clone_object("/std/drink");
        order->set_name("mead");
        order->set_pname("mead");
        order->set_short("fresh golden mead");
        order->set_pshort("fresh golden meads");
        order->set_adj(({"fresh", "golden"}));
        order->set_long("The mead is cool and refreshing, with " +
            "distinctive flowery scent.\n");
        order->set_soft_amount(110);
        order->set_alco_amount(4);
        order->add_prop(OBJ_I_WEIGHT, 220);
        order->add_prop(OBJ_I_VOLUME, 220);
        price = 20;
    break;

    case "nectar":
    case "pint":
    case "pint of nectar":
    case "pints":
    case "pints of nectar":
    case "1":
        order = clone_object("/std/drink");
        order->set_name(({"nectar", "pint", "pint of nectar"}));
        order->set_pname(({"pints", "pints of nectar"}));
        order->set_short("pint of nectar");
        order->set_pshort("pints of nectar");
        order->set_long("The pint of nectar is cold and looks good.\n");
        order->set_soft_amount(100);
        order->set_alco_amount(14);
        order->add_prop(OBJ_I_WEIGHT, 540);
        order->add_prop(OBJ_I_VOLUME, 540);
        price = 50;
    break;

    case "slice of bread":
    case "slices of bread":
    case "bread":
    case "2":
        order = clone_object(FOOD_DIR + "bread");
    // order = clone_object(SUPL_DIR + "bread");
        order->set_name(({"slice of bread", "slice", "bread"}));
        order->set_pname("slices of bread");
        order->set_short("slice of bread");
        order->set_pshort("slice of breads");
        order->set_long("This is a delicious slice of freshly " +
            "baked wheat bread.\n");
        order->set_amount(50);
        order->add_prop(OBJ_I_WEIGHT, 50);
        order->add_prop(OBJ_I_VOLUME, 100);
        add_prop(HEAP_S_UNIQUE_ID,"slices of bread");
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
        order = clone_object("/std/food");
        order->set_name("brick of cheese");
        order->add_name(({"brick of cheese", "cheese", "brick"}));
        order->set_pname("bricks of cheese");
        order->set_short("brick of cheese");
        order->set_pshort("bricks of cheese");
        order->set_adj("small");
        order->set_long("The brick of cheese is white with " +
            "flecks of orange in it.\n");
        order->set_amount(130);
        order->add_prop(OBJ_I_WEIGHT, 140);
        order->add_prop(OBJ_I_VOLUME, 150);
        order->add_prop(HEAP_S_UNIQUE_ID,"cheese");
        price = 45;
    break;

    case "mushrooms":
    case "steamed mushrooms":
    case "basket of steamed mushrooms":
    case "baskets of steamed mushrooms":
    case "baskets of mushrooms":
    case "basket of mushrooms":
    case "4":
        order = clone_object("/std/food");
        order->set_name("basket of steamed mushrooms");
        order->add_name("mushrooms");
        order->add_name("steamed mushrooms");
        order->add_name("basket");
        order->set_pname("baskets of steamed mushrooms");
        order->set_short("basket of steamed mushrooms");
        order->set_pshort("baskets of steamed mushrooms");
        order->set_adj(({"large", "steamed"}));
        order->set_long("A large basket full of large steamed " +
            "mushrooms, they are the best you've ever seen. Most " +
            "likely the mushrooms come from somewhere in the Shire. \n");
        order->set_amount(200);
        order->add_prop(OBJ_I_WEIGHT, 200);
        order->add_prop(OBJ_I_VOLUME, 300);
        order->add_prop(HEAP_S_UNIQUE_ID,"mushrooms");
        price = 75;
    break;

    }
    return (({order}) + ({price}));
}
