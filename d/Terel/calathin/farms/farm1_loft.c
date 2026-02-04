/*
 * farm1_loft.c
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
    set_short("hayloft");
    set_long("A large pile of hay has been stacked before the hayloft " +
      "door to the north. Some tools hang on the wall to the east. " +
      "Bins of oats and other various feed rest below the tools.\n");

    add_item(({"hayloft door","door"}),
      "The hayloft door provides access to the loft from the outside. " +
      "A pulley hangs on a beam just outside the door.\n");

    add_item(({"hay","pile of hay","pile"}),
      "A large pile of hay used as feed for the animals.\n");

    add_item(("tools"),"Various farming impliments.\n");

    add_item(({"bins","bin"}),"The wooden bins hold various feed " +
      "for the animals.\n");

    add_exit(CFARMS + "farm1_barn","down",0,1);

    add_object(ZODIAC_DIR + "bucket");
}
