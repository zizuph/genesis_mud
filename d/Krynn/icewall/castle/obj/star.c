/* Ten pointed star needed to open manhole */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>

create_object()
{
set_name("star");
set_adj("ten pointed");
set_long("The star has ten points and seems to made of magical glass.\n");
add_prop(OBJ_I_VALUE, 24);

}
