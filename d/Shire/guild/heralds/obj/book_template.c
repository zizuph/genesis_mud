/*
 *  Based on /d/Sparkle/guilds/new_merc/obj/merc_book.c
 *
 *  This is the standard book object used by the Heralds Library.
 *
 */
#pragma strict_types
inherit "/std/guild_library_book";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>


/* Prototypes */
public void        create_library_book();

/*
 * Function name:        create_library_book
 * Description  :        the object constructor
 */
public void
create_library_book()
{
    set_short("library book");
    add_name( ({ "_herald_library_book" }) );
    add_adj( ({ "library" }) );

    set_long("This is one of the books from the Heralds of the Valar library. You"
      + " can <read> it at your leisure, but be sure to <return> it before"
      + " you leave the library.\n");
} /* create_library_book */


