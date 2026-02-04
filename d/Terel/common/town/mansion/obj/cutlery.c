/* silver cutlery */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define BSN(xx) break_string(xx + "\n", 70)

create_object()
{
   set_name("cutlery");
   set_short("set of silver cutlery");
   set_pshort("sets of silver cutlery");
   set_long("It's a set of silver cutlery.\n");
   set_adj("silver");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 80);
}
