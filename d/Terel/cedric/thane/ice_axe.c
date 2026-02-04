/*

    Modified 30 Apr 2003, by Bleys:
        - Changed to use /d/Terel/include/Terel.h
        - Changed to use /d/Terel/include/recover.h
        - Changed to use <wa_types.h>
        - Added the very specific name so that the corpse
            /d/Terel/cedric/thane/ice_corpse.c
            can tell if the axe is present().

*/

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include "/d/Terel/cedric/thane/defs.h"

#include <wa_types.h>  /* wa_types.h contains some definitions we want */
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("axe");
    add_name(THANE_ICE_AXE_NAME, 1);
    add_adj("ice");
    set_short("ice axe");
    set_pshort("ice axes");
    set_long(BS("This sturdy little axe looks like it was made with the ice "
    + "climber in mind; it would probably be a helpful mountaineer's tool but "
    + "doesn't look like much of a weapon.\n"));
    set_hit(5);
    set_pen(8);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
