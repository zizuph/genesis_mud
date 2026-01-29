inherit "/std/object.c";
 
#include <macros.h>
#include <stdproperties.h>

#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define book            this_object()

void
create_object()
{
    set_name("book");
	
	add_cmd_item(({ "book" }), ({ "open" }), ({ "You open the book.\n" }));

set_long("A small, black, leatherbound journal.\n");
}

