/*
 * Council Log Book, adapted from old EW guild
 *
 * Created by Petros, April 2014
 */

#include <stdproperties.h>
#include "defs.h"

inherit CALIAN_GUILD_BASE_DIR + "objects/log_book";

#define BOOK_MAX_SIZE 12000

public void
read_it(string str)
{
    ::read_it("mread");
}

public void
create_log_book()
{
    setuid();
    seteuid(getuid());

    set_name("book");
    set_adj("leather");
    set_short("leather book");
    set_long("A leather book with a brown cover.  "+
        "The title of the book is: \"Elemental Circle Council Log\".\n");
    set_file(COUNCIL_LOG);
    set_max_size(BOOK_MAX_SIZE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
	"The council log book is fixed here by the magic of the Elementals.\n");
}
