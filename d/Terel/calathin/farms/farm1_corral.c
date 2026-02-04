/*
 * farm1_corral.c
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
    set_short("corral");
    set_long("The corral is used to exercise the larger animals such " +
      "as horses and cows. A water trough can be seen along the fence " +
      "to the north.\n");

    add_item(({"water trough","trough"}),"The water trough is used to " +
      "water the animals. The water in the trough looks frozen solid.\n");

    add_item(("fence"),"The fence was built using strong wooden planks. " +
      "It looks like it could hold even the largest of farm animals.\n");

    add_exit(CFARMS + "farm1d","yard",0,1);
}
