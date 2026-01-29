/*
 * File:     novlib3.c
 * Created:  Lilith
 * Purpose:  Library for the Novice members
 */
#pragma strict_types
#include "../defs.h"

inherit NOVLIB;

public void
union_room(void)
{
    set_short("novice library, level three");
    set_long("This is the third level of the Library of Novices of "+
      "the Shadow Union. Nearly identical to the rooms below, the "+
      "walls and high ceiling of this room are made of stone of the "+
      "deepest black, and draw most of the light from the room. "+
      "It is very plainly furnished, with the only concession to comfort "+
      "being group of flat grey cushions placed around the base of the "+
      "reading table. A small staircase leads upward into the "+
      "darkness. Just past it, another staircase leads downward. "+
      "A narrow set of shelves leans against the north wall."+
      "@@library_table_desc@@\n");

    add_exit("novlib4", "up", up_exit_block);
    add_exit("novlib2", "down");

    phrases = ({
	"It is our privilege to serve Jazur in all things.",
	"Those who are meek are too frightened to Serve.",
	"All training is but a prelude to the Trial of the Flame.",
	"Though some of what is taught may be painful, it "+
	    "helps a great deal at such moments to realize that there " +
	    "is also much pain in self-deception.",
	"When you encounter a Warrior, remember to state what "+
	    "level of training you have passed before you ask: How may "+
	    "I serve thee, that I may learn the ways of the Shadow Union?",
	"You shall now be known to all as a Student of Unity.",
	"Pride is a Virtue which requires balance, that it does "+
	    "not veer into Arrogance and thus pollute Dignity.",
    });

    /* Setup library */
    add_book_shelf(({ "third" }));
    union_library(3);
}
