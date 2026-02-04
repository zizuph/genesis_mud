inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP              this_player
#define TO              this_object

void
create_object()
{
   set_name("ash");
   add_name("piece of ash");
   set_short("piece of ash");
   set_pshort("pieces of ash");
   set_long("It's just some plain ash.\n");

	add_prop(OBJ_I_VALUE, 1);
}
