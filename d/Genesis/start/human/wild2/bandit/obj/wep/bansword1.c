/*
 * Varian - October 5 2015
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <wa_types.h>

int do_stab(string str);

void
create_weapon()
{
    int rand;
    
    set_name(({"sword"}));
    add_name(({"shortsword"}));
    set_short("fine shortsword");
    set_adj(({"fine"}));
    set_long("This sword is exquisitely balanced, and seems to have a fine " +
        "edge and a sharp point. A practice stab with the sword shows you " +
        "that this could be deadly in the hands of a skilled swordsman.\n");
    	    
    set_hit(32);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 700);
    
}

init()
{
    ::init();
    add_action("do_stab","stab");
}

int
do_stab(string str)
{
    notify_fail("Stab what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Gripping the handle of your notched shortsword tightly, you " +
        "quickly lunge forward with a dangerous looking stab.\n");
    SAYBB(" lunges forward with surprising speed, the notched shortsword " +
        "in their hand jabbing out with a dangerous looking stab.");
    return 1;
}
