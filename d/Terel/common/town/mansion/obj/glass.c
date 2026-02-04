/* A wine glass */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define BSN(xx) break_string(xx + "\n", 70)

create_object()
{
   set_name("glass");
   set_pname("glasses");
   set_short("elegant glass");
   set_pshort("elegant glasses");
   set_long("It's an elegant wine glass.\n");
   set_adj("elegant");
   add_prop(OBJ_I_VALUE,  70);
   add_prop(OBJ_I_WEIGHT, 80);
   add_prop(OBJ_I_VOLUME, 40);
}
