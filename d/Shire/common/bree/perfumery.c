/*
 * Pub of Esgaroth
 * By Finwe, May 2001
 */

#pragma strict_types

#include "/d/Shire/common/defs.h"
//#include "/d/Shire/sys/defs.h"

#include <money.h>

//inherit HOUSE_IN_BASE;
inherit "/d/Shire/std/room.c";
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices"})

/* Prototype */
void reset_room();

static object gudran;

void
create_shire_room()
{
    set_short("The Perfumery of Bree");
    set_long("Powerful scents fill this place, and immediately " +
        "it is clear--this is a perfume shop. Dried flowers " +
        "from all of the Shire and even some from other lands " +
        "are collected here and stored, aging for the time when " +
        "their aromas are most powerful. There is a rack of " +
        "bottles across the counter standing against the wall. " +
        "The wonderful smells can be bought, for a price. A " +
        "pricelist is on the wall.\n");


    add_item(({"sign","new sign"}),
        "To use the perfume <dabble (name of perfume)>\n."+
        "This will let you try on several kinds at once.\n");
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
//    add_prop(ROOM_I_NO_ATTACK, 1);
//    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); /* screw realism. Keep it open */
    set_alarm(1.0, 0.0, reset_shire_room);
//    add_prop(ROOM_I_NO_CLEANUP,1);
    configure_shire_inn();

   add_exit(BREE_DIR + "brroad1","out",0,1);

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
    "        freesia perfume. . . . . . . . . .150 cc\n"+
    "        \n\n"+
    "        Outrageous perfume. . . . . . . .175 cc\n"+
    "        Relentless cologne. . . . . . . .200 cc\n"+
   "\n";
}


void
reset_room()
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
      order = clone_object(BREE_DIR + "obj/sndlwd_perfume");
      price = 50;
      break;

    case "wildflower":
    case "wildflower perfume":
    case "bottle of wildflower perfume":
      order = clone_object(BREE_DIR + "obj/wildflower_perfume");
      price = 75;
      break;

    case "rosebud":
    case "rosebud perfume":
    case "bottle of rosebud perfume":
      order = clone_object(BREE_DIR + "obj/rose_perfume");
      price = 85;
      break;

    case "honeysuckle":
    case "honeysuckle perfume":
    case "bottle of honeysuckle perfume":
      order = clone_object(BREE_DIR + "obj/honeysuckle_perfume");
      price = 90;
      break;

    case "violet":
    case "violet perfume":
    case "bottle of violet perfume":
 
      order = clone_object(BREE_DIR + "obj/violet_perfume");
      price = 110;
      break;

    case "lilac":
    case "lilac perfume":
    case "bottle of lilac perfume":
 
      order = clone_object(BREE_DIR + "obj/lilac_perfume");
      price = 140;
      break;

    case "freesia":
    case "freesia perfume":
    case "bottle of freesia perfume":
 
      order = clone_object(BREE_DIR + "obj/freesia_perfume");
      price = 150;
      break;



    case "outrageous":
    case "outrageous perfume":
      order = clone_object(BREE_DIR + "obj/out_perfume");
      price = 175;
      break;

    case "relentless":
    case "cologne":
    case "relentless cologne":
  
      order = clone_object(BREE_DIR + "obj/relent_col");
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
