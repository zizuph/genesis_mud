/*
 * farm_pen.c
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
    set_short("pig pen");
    set_long("Yuck! You are standing in a muddy pig pen. " +
      "Or at least you hope that what you are standing in is mud.. " +
      "A leanto was built to provide shelter to the pigs " +
      "from the harsh winter.\n");

    add_item(("mud"),"You stand ankle deep in warm mud.\n " +
      "Warm mud??\n");

    add_item(("leanto"),"The slanted shelter provides shelter " +
      "for the pigs. The floor of the shelter has been covered " +
      "with woodchips and hay.\n");

    add_item(({"woodchips","hay"}),"A pile of woodchips and hay " +
      "make for a warm bed for the pigs at night.\n");

    add_exit(CFARMS + "farm1d","yard",0,1);

    add_npc(CFARMS + "monsters/pig", 8);
}
