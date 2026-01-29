/*
 * Perfumery of Bree
 * Updated by Finwe, April 2002
 */

#pragma strict_types

//#include "/d/Shire/common/defs.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <money.h>

inherit "/d/Shire/std/room.c";
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "sign"})

/* Prototype */

static object gudran;

void
create_shire_room()
{
    set_short("The Perfumery of Bree");
    set_long("Powerful scents fill this place, and immediately " +
        "it is clear--this is a perfume shop. Dried flowers " +
        "from all of the Shire, and even some from other lands, " +
        "are collected here and stored, aging for the time when " +
        "their aromas are most powerful. There is a rack of " +
        "bottles across the counter standing against the wall. " +
        "They are full of oils and wonderful smells, which can be " +
        "bought for a price. A pricelist is on the wall.\n");

    add_item(({"sign","new sign"}),
        "ZIt has some fine writing on it.\n");
    add_item(({"bottle","bottles","rack","racks"}),
        "The bottles are placed in racks and are made of glass.\n");
    add_item("counter", 
        "It's made out of wood. There is a woman standing behind it.\n");
    add_item("wall", 
        "It's used to secure the store from wind and rain.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item(({"shop","here"}),"@@my_long@@");
    add_item(({"flowers","dried flowers"}),"The flowers are from all "
		+"of the Shire and even some from other lands "
		+"are collected here and stored, aging for the "
		+"time when their aromas are most powerful.\n");
    add_item(({"smell"}),
        "The smell come from all the flowers hanging behind the counter.\n");
    add_item(({"woman","clerk","salesman","saleswoman",
            "shop clerk","salesperson","perfume-maker"}),"@@clerk_desc@@");

 
    add_item(PRICELIST_ID, "@@pricelist_desc@@");
    add_prop(ROOM_I_INSIDE,1);
    reset_shire_room();

    configure_shire_inn();

   add_exit(ROAD_DIR + "broad09","out",0,0,1);
   add_exit(ROAD_DIR + "broad09","south");

}

string
clerk_desc()
{
	string str;
	str = (present(gudran))->long();
	return str;
}



string
pricelist_desc()
{
  return "\n        Scents:\n\n"+
    "        We have many perfumes and colognes available.\n"+
    "        Feel free to purchase any of them below.\n\n"+
    "        sandalwood perfume . . . . . . . .50 cc\n"+
    "        wildflower perfume . . . . . . . .75 cc\n"+
    "        rosebud perfume. . . . . . . . . .85 cc\n"+
    "        honeysuckle perfume. . . . . . . .90 cc \n"+
    "        violet perfume . . . . . . . . . .110 cc\n"+
    "        lilac perfume  . . . . . . . . . .140 cc\n"+
    "        lavender perfume  . . . . .. . . .145 cc\n"+
    "        freesia perfume. . . . . . . . . .150 cc\n"+
    "        \n\n"+
    "        Outrageous perfume. . . . . . . .175 cc\n"+
    "        Relentless cologne. . . . . . . .200 cc\n\n"+
    "        To use the perfume <dabble (name of perfume)>\n."+
    "         This will let you try on several kinds at once.\n";
}


void
reset_shire_room()
{
 if (!gudran)
    gudran = clone_object(BREE_DIR + "npc/gudran");
  if (!present(gudran))
    gudran->move(this_object());
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
    case "sandalwood": 
    case "sandalwood perfume":
    case "bottle of sandalwood perfume":
      order = clone_object(OBJ_DIR + "perfume_sandalwood");
      price = 50;
      break;

    case "wildflower":
    case "wildflower perfume":
    case "bottle of wildflower perfume":
      order = clone_object(OBJ_DIR + "perfume_wildflower");
      price = 75;
      break;

    case "rosebud":
    case "rosebud perfume":
    case "bottle of rosebud perfume":
      order = clone_object(OBJ_DIR + "perfume_rose");
      price = 85;
      break;

    case "honeysuckle":
    case "honeysuckle perfume":
    case "bottle of honeysuckle perfume":
      order = clone_object(OBJ_DIR + "perfume_honeysuckle");
      price = 90;
      break;

    case "violet":
    case "violet perfume":
    case "bottle of violet perfume":
 
      order = clone_object(OBJ_DIR + "perfume_violet");
      price = 110;
      break;

    case "lavender":
    case "lavender perfume":
    case "bottle of lavender perfume":
 
      order = clone_object(OBJ_DIR + "perfume_lavender");
      price = 145;
      break;

    case "lilac":
    case "lilac perfume":
    case "bottle of lilac perfume":
 
      order = clone_object(OBJ_DIR + "perfume_lilac");
      price = 140;
      break;

    case "freesia":
    case "freesia perfume":
    case "bottle of freesia perfume":
 
      order = clone_object(OBJ_DIR + "perfume_freesia");
      price = 150;
      break;
    case "outrageous":
    case "outrageous perfume":
      order = clone_object(OBJ_DIR + "perfume_outrageous");
      price = 175;
      break;
    case "relentless":
    case "cologne":
    case "relentless cologne":
  
      order = clone_object(OBJ_DIR + "perfume_relentless");
      price = 200;
      break;

    case "perfume":
        notify_fail("Buy what kind of perfume?\n");
        break;

    default:
      notify_fail("Buy what?\n");
      break;
//      return 0;

    }
    return (({order}) + ({price}));

}
