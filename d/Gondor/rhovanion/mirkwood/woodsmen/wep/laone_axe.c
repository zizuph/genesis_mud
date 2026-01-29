/*
 * Axe for Laone
 * Varian - August 2015
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <wa_types.h>

int do_spin(string str);

void
create_weapon()
{
    int rand;
    
    set_name(({"axe"}));
    set_pname(({"axes"}));
    set_short("steel grey axe");
    set_pshort("steel grey axes");
    set_adj(({"steel", "grey"}));
    set_long("This heavy steel axe is made to be wielded in both hands. The " +
        "blade is a dull grey, but the edge appears to be razor sharp.\n");
    	    
    rand = random(5);
    set_hit(30);
    set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18,22));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1100);
    
}

init()
{
    ::init();
    add_action("do_spin","spin");
}

int
do_spin(string str)
{
    notify_fail("Spin what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Expertly gripping the spear with both hands, you begin " +
        "to twist and twirl the spear as it cuts through the air " +
        "impressing everyone around you.\n");
    SAYBB(" spins their deadly long spear and cuts through the air " +
        "in a dazzling display of skill.");
    return 1;
}
