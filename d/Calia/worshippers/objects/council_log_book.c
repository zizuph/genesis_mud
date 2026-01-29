
#include <stdproperties.h>
#include "defs.h"
#pragma save_binary

inherit CALIAN_GUILD_BASE_DIR+"objects/log_book";

#define BOOK_MAX_SIZE 1200

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_log_book()
{
    set_name("book");
    set_adj("leather");
    set_short("leather book");
    set_long("A leather book with a brown cover.  "+
        "The title of the book is: \"Worshippers Council Log\".\n");
    set_file("/d/Calia/worshippers/logs/council");
    set_max_size(BOOK_MAX_SIZE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
	"The council log book is fixed here by the magic of the Elementals.\n");
}

void
update_log_book(string new_line)
{
    ::update_log_book(new_line);
}
