/*
 * farm1_barn.c
 *
 * Calathin external house.
 * 11/21/1999 -- Tomas
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
    INSIDE;
    set_short("barn");
    set_long("The barn is separated into various stalls. The stalls " +
      "along the east wall are home for milking cows. " +
      "Along the west wall are the horse stalls. A ladder leading " +
      "up to the hayloft has been nailed to the south wall " +
      "alongside the the southern exit.\n");

    add_item(("barn"),"The two story red barn stands to the side of the small " +
      "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(("hayloft"),"Above you is the hayloft. It can be reached " +
      "by using the ladder on the south wall.\n");

    add_item(({"stall","stalls"}),
        "The stalls are home to cows and horses.\n");

    add_item(({"ground","floor"}),
        "The dirt floor is covered in hay.\n");

    add_item(("hay"),"Is used not only as feed but to keep the ground dry.\n");

    add_exit(CFARMS + "farm1_loft","ladder",0,1);

    room_add_object(CFARMS + "obj/farm1_barn_door1");
    room_add_object(CFARMS + "obj/farm1_barn_door2");

    add_npc(CFARMS + "npc/farmer");
    add_npc(CFARMS + "monsters/cow", 2);
    add_npc(CFARMS + "monsters/horse", 2);
}
