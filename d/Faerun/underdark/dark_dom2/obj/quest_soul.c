inherit "/std/object.c";
 
#include <macros.h>
#include <stdproperties.h>

#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define soulgem         this_object()

void
create_object()
{
    set_name("soulgem");
	add_name("_necro_soulgem");
    add_name("gem");

	add_cmd_item(({ "energy" }), ({ "channel" }), ({ "You focus your energy on the soulgem, but nothing seems to happen.\n" }));
///                  silk          drape          You hold the scarf.\n
set_long("A gem that seems to radiate energy. Someone versed in the dark arts might be able to channel energy through it.\n");
}
