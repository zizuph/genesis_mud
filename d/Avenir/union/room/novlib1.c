/*
 * File:     novlib1.c
 * Created:  Lilith
 * Purpose:  Library for the Novice members
 */
#pragma strict_types
#include "../defs.h"

inherit NOVLIB;

public void
union_room(void)
{
    set_short("novice library, level one");
    set_long("This is the first level of the Library of Novices of "+
      "the Shadow Union. Nearly identical to the room below, the walls "+
      "and high ceiling of this room are made of stone of the deepest "+
      "black, and draw most of the light from the room. It is very "+
      "plainly furnished, with the only concession to comfort being "+
      "group of flat grey cushions placed around the base of the "+
      "reading table. A small staircase leads upward into the "+
      "darkness. Just past it, another staircase leads downward. "+
      "A narrow set of shelves leans against the north wall."+
      "@@library_table_desc@@\n");

    add_exit("novlib2", "up", up_exit_block);
    add_exit("novlib0", "down");

    phrases = ({
	"If the spirit is willing, the mind will learn.",
	"Through purity one attains Jazur's grace.",
	"When you encounter a Warrior, remember to state what "+
	    "level of training you have passed before you ask: How may "+
	    "I serve thee, that I may learn the ways of the Shadow Union?",
	"You shall now be known to all as a Shadow Novice.",
	"Let the rules of the Halls be inscribed upon your heart "+
	    "and mind.",
	"Within your hands you hold the key to your dreams. Let "+
	    "its warmth remind you of the mysteries you seek.",
    });

    /* Setup library */
    add_book_shelf(({ "first"}));
    union_library(1);
}
