/* Magic blue disk for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name(({"disk", "_blue_pass_medal_"}));
    set_adj("round");
    add_adj("blue");
    set_short("round blue disk");
    set_long("This round blue disk looks slightly opaque, and feels " + 
        "light in your hand. It is strangely warm, and you have the " + 
        "oddest feeling that it has some spell cast over it.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment"}));
    add_prop(OBJ_S_WIZINFO, "This disk is a magically enchanted key " + 
        "which allows passage through a door in Shunar's tower.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"This disk has been magically enchanted " + 
        "as a means to pass through a door.\n"}));
}

