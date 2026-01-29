/*
 * File:     novlib2.c
 * Created:  Lilith
 * Purpose:  Library for the Novice members
 */
#pragma strict_types
#include "../defs.h"

inherit NOVLIB;

public void
union_room(void)
{
    set_short("novice library, level two");
    set_long("This is the second level of the Library of Novices of "+
      "the Shadow Union. Nearly identical to the rooms below, the walls "+
      "and high ceiling of this room are made of stone of the "+
      "deepest black, and draw most of the light from the room. "+
      "It is very plainly furnished, with the only concession to comfort "+
      "being group of flat grey cushions placed around the base of the "+
      "reading table. A small staircase leads upward into the "+
      "darkness. Just past it, another staircase leads downward. "+
      "A narrow set of shelves leans against the north wall."+
      "@@library_table_desc@@\n");

    phrases = ({
	"Forget not Who walks in Shadow with you.",
	"What price, this knowledge of shadows and flame?",
	"When you encounter a Warrior, remember to state what "+
	    "level of training you have passed before you ask: How may "+
	    "I serve thee, that I may learn the ways of the Shadow Union?",
	"You shall now be known to all as a Shadow Initiate.",
	"To be truly be sybarite, one must understand the "+
	    "Doctrine of Civility.",
	"In order to become what you should be, you must shed "+
	    "your Self of what you once were.",
	"You who would learn to fight as One with the Shadows "+
	    "must first master your Self.",
    });

    add_exit("novlib3", "up", up_exit_block);
    add_exit("novlib1", "down");

    /* Setup library */
    add_book_shelf(({ "second" }));
    union_library(2);
}
