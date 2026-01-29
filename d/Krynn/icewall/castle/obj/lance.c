/* DragonLance for the quest.  To be returned to Gunthar.  May not be
used as a weapon */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>
inherit "/std/object";

void
create_object() 
{
    set_name("dragonlance");
    set_short("broken dragonlance");
    add_name("lance");
    add_name("dragon_lance");
    set_adj("broken");
    set_long("This is a dragonlance. At one time it was used to slay "
	     + "the evil dragons. Sadly, it is broken now and of not much "
	     + "use as a weapon.\n");
    
    add_prop(OBJ_I_VOLUME, 12500);
    add_prop(OBJ_I_WEIGHT, 60000);
    add_prop(OBJ_I_BROKEN, 1);
}
