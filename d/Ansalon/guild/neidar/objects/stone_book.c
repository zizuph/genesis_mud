/*
 *  Based on /d/Sparkle/guilds/new_merc/obj/merc_book.c
 *
 *  This is the standard book object used by the Neidar Library.
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
    add_name( ({ "_neidar_library_book" }) );
    add_adj( ({ "library" }) );

    set_short("stone library book");
    set_pshort("stone library books");
    set_long("This is a stone book from the library of the mighty Neidar Clan."
      + " It is fashioned from thin sheets of stony mica bound together by"
      + " sturdy metal rings. Runes of dwarvish wisdom are chiselled into"
      + " its glittering pages. You can <read> for as long you wish -- but"
      + " be sure to <return> it before you leave the library.\n");

} /* create_library_book */


