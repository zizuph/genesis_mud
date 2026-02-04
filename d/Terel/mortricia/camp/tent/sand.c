/* Some silverish sand */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define BSN(xx) break_string(xx + "\n", 70)

create_object()
{
   set_name("sand");
   set_pname("sand");
   set_short("handful of silverish sand");
   set_pshort("handfuls of silverish sand");
   set_long("It's some silverish sand.\n");
   set_adj("silverish");
   add_prop(OBJ_M_NO_GET, "It's in the hourglass.\n");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 100);
}
