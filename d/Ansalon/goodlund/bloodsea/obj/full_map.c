inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

void
create_object()
{
    set_name(({"map","_ansalon_full_map"}));
    set_adj("fragile");
    add_adj("treasure");
    set_short("fragile treasure map");
    set_long("This fragile piece of parchment is a treasure map! Examining it " +
       "closely, you determine that the treasure of the infamous pirate " +
       "Captain Kharasa has been buried on a sandy beach on an island to the north " +
       "of Mithas, the mysterious isle of Karthay. " +
       "If you find that beach, you are sure you'll be able to dig up the treasure " +
       "with the aid of a shovel and this map!\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 0);
}
