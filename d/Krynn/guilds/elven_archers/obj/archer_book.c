/*
 *  Based on /d/Sparkle/guilds/new_merc/obj/merc_book.c
 *
 *  This is the standard book object used by the Elven Archer Library.
 *
 */
#pragma strict_types
#include "../guild.h"

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
    add_name( ({ "_elven_archer_library_book" }) );
    add_adj( ({ "library" }) );

    set_long("This is one of the books from the Library of the Elven Archers of Ansalon. You"
      + " can crack its wax sheath open and <read> it at your leisure, but be sure to"
      + " <return> it before you leave the library, so that the bees can attend to it.\n");

} /* create_library_book */


