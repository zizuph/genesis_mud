inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("shell");
   set_adj("cracked");
   add_adj("large");
   set_short("large cracked shell");
   set_long("This large shell has come from a mythical beast of the sea, " +
       "the fearsome dragon turtle. While exceedingly thick and tough " +
       "this one is badly cracked, although would probably still return " +
       "a nice price from merchants of the realms!\n");

   add_prop(OBJ_I_VOLUME, 600);
   add_prop(OBJ_I_WEIGHT, 6500);
   add_prop(OBJ_I_VALUE, 9000); // A bit over 5 plat for a broken shell.
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER;
}