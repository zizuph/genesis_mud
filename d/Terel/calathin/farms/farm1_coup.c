/*
 * farm1_coop.c
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
    set_short("chicken coop");
    set_long("You stand in a chicken coop. Along the walls of the coop " +
      "are nests. The nests are made of straw, down and chicken feathers. " +
      "The coop is covered to keep the elements and predators from " +
      "the chickens and their eggs.\n");

    add_item(({"egg","eggs"}), "You dont see any eggs, perhaps if you looked " +
      "a little closer at the nests you might find some.\n");

    add_item(("barn"),"The two story red barn stands to the side of the small " +
      "house. A hayloft door can be seen at the top level of the barn.\n");

    add_item(({"nest","nests"}),
      "The nests look untidy. But to a chicken, its home.\n");

    add_exit(CFARMS + "farm1d","yard",0,1);

    add_npc(CFARMS + "monsters/chicken", 8);
}
