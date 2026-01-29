/* created by Aridor 06/19/93 */

#include "../local.h"

inherit MERCH_ROOMBASE;

#include <macros.h>


object barkeeper;

query_to_jail()
{
  return ({"open door","north"});
}


query_barkeeper()
{
    return barkeeper;
}

void
reset_palan_room()
{
    if (barkeeper)
        return;
    barkeeper = clone_object(MERCH + "living/barkeeper");
    barkeeper->move_living("xx",TO);
}

void
create_palan_room()
{
    object door;

    set_short("The main room of the Silver Dragon Inn");
    set_long("This is the main room of the Silver Dragon Inn. "
       +     "There are tables with chairs everywhere and "
       +     "the barkeeper behind the bar is busy serving. "
       +     "There is a menu hanging above the bar.\n");

    LIGHT;

    add_item(({"bar"}),"It a typical bar where drinks are sold.\n");
    add_item(({"table","tables"}),"Most tables are occupied, but there "
       +     "is still a place to sit down.\n");
    add_item(({"chair","chairs"}),"A few of the chairs are still empty.\n");
    add_item("menu","@@my_menu");
    add_cmd_item("menu","read","@@my_menu");

    door = clone_object(MERCH + "doors/wooddoore");
    door->move(TO);
    add_exit(MERCH + "inn2", "west",0,0);

    set_alarm(1.0,0.0,"reset_room");

}



my_menu()
{
    string str;
    str = "        M E N U:\n"
        + "       ---------\n"
    + "\n"
    + "Pfusch beer      12 cc\n"
        + "Small wine       20 cc\n"
        + "Kustennebel     170 cc\n"
    + "\n"
    + "Roll             13 cc\n"
    + "Hardboiled egg   50 cc\n"
    + "Pancake         100 cc\n"
    + "Special Dinner  360 cc\n";
     return str;
}


