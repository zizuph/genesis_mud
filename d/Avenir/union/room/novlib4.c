/*
 * File:     novlib4.c
 * Created:  Lilith
 * Purpose:  Library for the Novice members
 */
#pragma strict_types
#include "../defs.h"

inherit NOVLIB;

public void
union_room(void)
{
    set_short("novice library, level four");
    set_long("This is the fourth level of the Library of Novices of "+
      "the Shadow Union. "+
      "Nearly identical to the rooms below, the walls and high ceiling "+
      "of this room are made of stone of "+
      "the deepest black, and draw most of the light from the room. "+
      "It is very plainly furnished, with the only concession to comfort "+
      "being group of flat grey cushions placed around the base of the "+
      "reading table. A small staircase leads upward into the "+
      "darkness. Just past it, another staircase leads downward. "+
      "A narrow set of shelves leans against the north wall."+
      "@@library_table_desc@@\n");

    /* There, but not obvious */
    add_exit("novlib5", "up", up_exit_block);
    add_exit("novlib3", "down");

    phrases = ({
	"Those who use phrases without wisdom sometimes talk of "+
	    "suffering as a mystery rather than a revelation.",
	"What one calls mystery, another calls purpose.",
	"Your flesh is but dust and water, it is the shade of "+
	    "your soul for which you should have a care.",
	"In Duty you perfect your ability to dance in the shadow "+
	    "of death, for once you have, great mysteries await you.",
    });

    /* Setup library */
    add_book_shelf(({ "fourth" }));
    union_library(4);
}
