#include "defs.h"
inherit STD_ROOM;
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

void reset_room();

object obj;

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1); 
    ::create_room();
    set_short("The Bloody Skull Inn");
    set_long("You are in a dim, smokey tavern. It is quite large, with "+
      "many tables scattered about the room. There is a bar to the south "+
      "wall where you can order a drink or two. There are many people "+
      "around, talking, drinking and eating. To the east, the inn "+
      "continues further. There is a menu on the bar.\n");
    add_item("bar", "A nice looking wooden bar with a menu on it.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("chairs",
      "They are made out of wood as is the rest of the place.\n"); 
    add_item("tables", "They are darkened with spilled beer.\n");
    add_cmd_item("menu", "read", "@@read");
    add_drink( ({ "beer", "beers", "Raumdor", "Raumdor beer" }),
      "beer", "Raumdor", 100, 8, 12, 0, 0,
      "Dark black beer.\n", 0);
    add_drink( ({ "wine", "wines", "red", "red wine" }),
      "wine", "red", 100, 20, 80, 0, 0,
      "It has a deep red color and smells strong.\n", 0);
    add_drink(({"whiskey","whiskeys","dark","dark whiskey"}),"whiskey",
      "dark",65,25,100,0,0,"A very potent looking drink. It smells "+
      "like whiskey, but is very dark in color.\n",0);
    add_drink(({"rum","rums","heavy","heavy rum"}),"rum","heavy",100,62,
      140,0,0,"A powerful looking drink. It looks thick and heavy, "+
      "and smells strong.\n",0);
    add_food( ({ "chicken", "chickens","spiced chicken" }),
      "chicken", "spiced", 60, 60, 0, 0,
      "Mmmm, it smells wonderful.\n", 0);
    add_food( ({ "tofu", "plate of tofu and rice", "tofus", "rice" }),
      ({"tofu","rice"}), "tofu", 80, 80, "plate of tofu and rice", 
      "plates of tofu and rice",
      "Spicy, hot and sour rice with tofu chunks.\n", 0);
    add_food( ({ "beef", "mongolian", "plate of mongolian beef",
	"plate", "plates" }),
      "beef", "mongolian", 120, 120, "plate of mongolian beef",
      "plates of mongolian beef",
      "Steamy hot and spicy! A real man's meal.\n", 0);
    add_food(({"pork","mu shu","plate of mu shu pork","plate","plates"}),
      "pork","mu shu",160,160,"plate of mu shu pork",
      "plates of mu shu pork","A full plate piled high with steamy "+
      "rice and pork in special spicy sauce!\n",0);
    add_exit(DRAKMERE_DIR + "road07","northwest",0);
    add_exit(DRAKMERE_SHOP_DIR + "inn2","east",0);
    reset_room();
}
void
reset_room()
{
    if(!obj)
    {
	obj = clone_object(DRAKMERE_NPC_DIR + "b_maid.c");
	obj->move_living("xxx",TO);
    }
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
      "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"+
      "@       The Bloody Skull Inn        @\n"+
      "@-----------------------------------@\n"+
      "@ Raumdor beer   -  12 cc           @\n"+
      "@ Red wine       -  80 cc           @\n"+
      "@ Dark whiskey   - 100 cc           @\n"+
      "@ Heavy rum      - 140 cc           @\n"+
      "@                                   @\n"+
      "@ Spiced chicken -  60 cc           @\n"+
      "@ Tofu and rice  -  80 cc           @\n"+
      "@ Mongolian beef - 120 cc           @\n"+
      "@ Mu shu pork    - 160 cc           @\n"+
      "@                                   @\n"+
      "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    return 1;
}

int *
query_coordinates()
{
    return ({67, 0, 0});
}
