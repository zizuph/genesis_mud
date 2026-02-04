/* A silver plate */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define BSN(xx) break_string(xx + "\n", 70)

create_object()
{
   set_name("plate");
   set_short("silver plate");
   set_long("It's an elegant silver plate.\n");
   set_adj("silve");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 80);
}
