inherit "/std/object.c";
 
#include <macros.h>
#include <stdproperties.h>

#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define silk            this_object()

void
create_object()
{
    set_name("silk");
	add_name("_nerissa_scarf");
    add_name("scarf");

	add_cmd_item(({ "silk" }), ({ "drape" }), ({ "You hold the scarf.\n" }));

set_long("A soft, silken scarf.\n");
}
