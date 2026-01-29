/*
 * Updated for the new Bree.
 * This is one of the few files not imported over because of the delivery quest.
 * -- Finwe, May 2002
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Genesis/delivery/office";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"

#include "/d/Genesis/delivery/delivery.h"

// #include "/d/Shire/bree/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
//#define SUPL_DIR "/d/Shire/common/bree/supplies/"


/* Prototype */
void reset_shire_room();

static object barliman;

void
create_shire_room()
{
    set_short("The Prancing Pony");
    set_office("the Prancing Pony in Bree",3);
    set_long("You have entered Bree's and the hobbits' great pride, the largest "+
        "and biggest inn in miles around: The Prancing Pony. You see a red "+
        "banner on the wall above a counter. There is a drawing of a golden "+
        "horse, or perhaps even a golden pony, standing on its hind-legs "+
        "waving its front-legs in the air. On that same wall, next to the "+
        "banner, there is a pricelist.  A sign hangs above the counter. "+ 
        "East is a dim room, north is the game room, and south across " +
        "the road is the private dining room.\n");
    add_item("sign","The sign has writing on it.\n");
    add_cmd_item("sign","read","The sign reads:\nHere you may:\n"+
      "<ask for a delivery tour> To get a delivery task.\n"+
      "<deliver>  To deliver an assigned task.\n"+
      "<return>  To return a failed delivery.\n");
    add_item("mirror", "@@mirror_desc");  /* in innkeeper's right hand */
    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("wall", "It's used to secure the inn from wind and rain.\n");
    add_item("banner", "It's made out of some kind of tissue.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");

// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(TOWN_DIR + "innyard","south");
    add_exit(TOWN_DIR + "innfront","west");
    add_exit(OLD_BREE_DIR + "innroom","east");
    add_exit("/d/Shire/bree/rooms/town/connect4", "north");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}

string
mirror_desc()
{
    if (!barliman || !present(barliman)) 
        return "You find no mirror.\n";
    return "The mirror reflects the pricelist on the wall.\n"+
    "You are having a hard time reading the prices this way.\n";
}

string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
    "    A glass of water. . . . . . . . .  5 cc\n"+
    "    A nice cold beer. . . . . . . . .  20 cc\n"+
    "    A pint of ale . . . . . . . . . .  50 cc\n"+
    "    A glass of red wine . . . . . . .  80 cc\n"+
    "    A tiny bit of prime liquor. . . . 180 cc\n"+
    "\nSnacks:\n\n"+
    "    A large cookie. . . . . . . . . .  15 cc\n"+
    "    A ham sandwich. . . . . . . . . .  40 cc\n"+
    "    A bag of cookies. . . . . . . . . 200 cc\n"+
    "\nMeals:\n\n"+
    "    Some rabbit stew. . . . . . . . . 75 cc\n"+
    "    Steak a la maison . . . . . . . . 160 cc\n"+
    "    Fantastic feast in a bag. . . . . 210 cc\n\n"+
    "    A night's stay in the inn . . . . 144 cc\n\n\n"+
    "You may order for other players as well as order for "+
    "multiple players.\n"+
    "Try using 'order <item> for <players>' similar to how you "+
    "target players with an emotion.\n"+
    "You may also 'order <item> for team' to buy things for the "+
    "teammates.\n";
}

void
reset_shire_room()
{
    if (!barliman)
        barliman = clone_object(NPC_DIR + "butterbur");
    if (!present(barliman,this_object()))
        barliman->move(this_object());
}

void
init()
{
    ::init();
    init_office();
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

    if (!barliman || !present(barliman))
    {
        notify_fail("There is no one here to buy anything from.\n"+
          "The innkeeper has been killed!\n");
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
    case "water":
    case "waters":
    case "glass of water":
        order = clone_object(FOOD_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "cold beer":
    case "nice cold beer":
    case "beers":
    case "cold beers":
    case "nice cold beers":
        order = clone_object(FOOD_DIR + "beer");
        price = 20;
        break;
    case "ale":
    case "pint":
    case "pint of ale":
    case "ales":
    case "pints":
    case "pints of ale":
        order = clone_object(FOOD_DIR + "ale");
        price = 50;
        break;
    case "wine":
    case "red wine":
    case "glass of wine":
    case "wines":
    case "red wines":
    case "glasses of wine":
        order = clone_object(FOOD_DIR + "wine");
        price = 80;
        break;
    case "liquor":
    case "prime liquor":
    case "liquors":
    case "prime liquors":
        order = clone_object(FOOD_DIR + "liquor");
        price = 180;
        break;
    case "cookie":
    case "cookies":
        order = clone_object(FOOD_DIR + "cookie");
        price = 15;
        break;
    case "bag of cookies":
    case "bags of cookies":
        order = clone_object(FOOD_DIR + "cookie_bag");
        price = 200;
        break;
    case "sandwich":
    case "ham sandwich":
    case "sandwiches":
    case "ham sandwiches":
        order = clone_object(FOOD_DIR + "sandwich");
        price = 38;
        break;
    case "stew":
    case "rabbit stew":
    case "rabbit stew":
    case "stews":
    case "rabbit stews":
    case "rabbit stews":
        order = clone_object(FOOD_DIR + "stew");
        price = 75;
        break;
    case "steak":
    case "steak a la maison":
    case "steaks":
    case "steaks a la maison":
        order = clone_object(FOOD_DIR + "steak");
        order->add_prop("_steak_for_doggie", 1);
        price = 160;
        break;
    case "feast":
    case "fantastic feast":
    case "feasts":
    case "fantastic feasts":
        order = clone_object(FOOD_DIR + "feast");
        price = 210;
        break;

    case "key":
    case "night's stay":
    case "nights stay":
        order = clone_object(BREE_DIR + "obj/inn_key");
        price = 144;
        break;
    }
    return (({order}) + ({price}));
}


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("You cannot go there yet.\n");
    return 1;
}
