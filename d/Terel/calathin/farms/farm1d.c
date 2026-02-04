/*
 * farm1d.c
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
    set_short("barnyard");
    set_long("You stand in the barnyard. To the east is a corral used to train " +
      "and excercise horses. To the west is the chicken coop and to the south " +
      "is the pig pen.\n");

    add_item(({"coop","chicken coop"}),
      "The chicken coop looks large enough to house several " +
      "chickens. A feeding trough has been nailed along the side of the coop " +
      "to allow the farmer to feed the chickens without entering the coop.\n");

    add_item(({"pen","pig pen"}),
      "The pig pen houses several large pigs. A feeding trough has been " +
      "nailed along the side of the pen to allow the farmer to feed " +
      "the pigs without entering the pen.\n");

    add_item(("corral"),"A strong looking fence makes up the corral.\n");

    add_exit(CFARMS + "farm1_coup","coop",0,1);
    add_exit(CFARMS + "farm1_pen","pen",0,1);
    add_exit(CFARMS + "farm1_corral","corral",0,1);

    room_add_object(CFARMS + "obj/farm1_barn_door2a");
}
