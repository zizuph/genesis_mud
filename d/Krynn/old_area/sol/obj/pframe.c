/* A picture frame, totally useless
 * by Teth, Feb15,96
*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("frame");
   set_adj("picture");
   set_short("picture frame");
   set_pshort("picture frames");
   set_long("This is a once-beautiful picture frame. It is carved " +
            "from oak or maple. Cracking varnish peels off in places.\n");
   
   add_prop(OBJ_I_VALUE, 15);
   add_prop(OBJ_I_WEIGHT,200);
   add_prop(OBJ_I_VOLUME,1500);
}
