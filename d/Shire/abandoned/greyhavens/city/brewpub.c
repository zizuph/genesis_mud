/*

   Drunken Boar Brewpub
   
*/

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})


/* Prototype */
void reset_shire_room();

static object fliilun;

void
create_shire_room()
{
    set_short("The Drunken Boar");

    set_long("The entrance of The Drunken Boar. On the "+
        "wall there is a pricelist."+ 
        "\n");

    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("wall", "It's made of rough hewn oak.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}


string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
    "0. 'A glass of water'  ...........      5 cc\n"+
    "1. 'A pint of ale' ...............     50 cc\n"+
    "2. 'A pint of stout' .............     50 cc\n"+    
    "3. 'A glass of red wine ..........     80 cc\n"+
    "4. 'A bag of nuts' ...............     15 cc\n"+
    "5. 'Some rabbit stew' ............     75 cc\n"+
    "6. 'Steak of the Day' ............    160 cc\n"+
    "7. A night's stay in the inn.....    144 cc\n\n\n"+
    "You may order for other people as well as yourself.\n"+
    "Try using 'order <num> <item> for <person(s)>'\n"+
    "You may also 'order <num> <item> for team' to buy things for your "+
    "teammates.\n";
}

void
reset_shire_room()
{
;
 /*   if (!fliilun)
        fliilun = clone_object(NPC_DIR + "fliilun");
    if (!present(fliilun,this_object()))
        fliilun->move(this_object());
	*/
}

void
init()
{
    ::init();
    init_shire_inn();
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

/*
int
do_order(string str) 
{

    if (!fliilun || !present(fliilun))
    {
        notify_fail("The brewmaster is not here.\n"+);
        return 0;
    }

    return ::do_order(str);
}
*/

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
    case "0":
        order = clone_object(FOOD_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "cold beer":
    case "nice cold beer":
    case "beers":
    case "cold beers":
    case "nice cold beers":
    case "1":
        order = clone_object(FOOD_DIR + "beer");
        price = 20;
        break;
    case "ale":
    case "pint":
    case "pint of ale":
    case "ales":
    case "pints":
    case "pints of ale":
    case "2":
        order = clone_object(FOOD_DIR + "ale");
        price = 50;
        break;
    case "wine":
    case "red wine":
    case "glass of wine":
    case "wines":
    case "red wines":
    case "glasses of wine":
    case "3":
        order = clone_object(FOOD_DIR + "wine");
        price = 80;
        break;
    
    case "nuts":
    case "bag of nuts":
    case "bag":
    case "bags":
    case "5":
        order = clone_object(FOOD_DIR + "cookies");
        price = 15;
        break;
    case "sandwich":
    case "ham sandwich":
    case "sandwiches":
    case "ham sandwiches":
    case "6":
        order = clone_object(FOOD_DIR + "sandwich");
        price = 38;
        break;
    case "stew":
    case "rabbit stew":
    case "rabbit stew":
    case "stews":
    case "rabbit stews":
    case "rabbit stews":
    case "7":
        order = clone_object(FOOD_DIR + "stew");
        price = 75;
        break;
    case "steak":
    case "steak a la maison":
    case "steaks":
    case "steaks a la maison":
    case "8":
        order = clone_object(FOOD_DIR + "steak");
        price = 160;
        break;
    case "feast":
    case "fantastic feast":
    case "feasts":
    case "fantastic feasts":
    case "9":
        order = clone_object(FOOD_DIR + "feast");
        price = 210;
        break;

    case "key":
    case "night's stay":
    case "10":
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
