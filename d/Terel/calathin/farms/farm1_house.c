/*
 * farm1_house.c
 *
 * Calathin external house.
 * 11/22/1999 -- Tomas
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
    set_short("farmhouse");
    set_long("The interior of the farmhouse is neat and tidy. " +
      "The furnishings and decor are practical like you would " +
      "expect to find on a farm. A cast iron stove sits " +
      "in the middle of the house providing warmth.\n");

    add_item(({"stove","iron stove","cast iron stove"}),
      "The cast iron stove looks very old. Yet the stove " +
      "does its job well. The room is quite cozy as a result " +
      "of its work. A coffee pot sits on top of the stove.\n");

    add_item(({"coffee pot","pot"}),
      "A coffee pot rests upon the cast iron stove.\n");

    add_item(({"furnishings","furniture","chair","table","chairs"}),
      "The furnishings mostly homemade from wood, are of a " +
      "practical design. But they look quite comfy.\n");

    room_add_object(CFARMS + "obj/farm1_door1");
    add_npc(CFARMS + "npc/farmer");
}
