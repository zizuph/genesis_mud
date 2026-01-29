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
    set_short("heavy shortsword");
    set_adj(({"heavy"}));
    set_long("This sword feels a little bit too heavy, almost as if it " +
        "is slightly unbalanced. After testing the sword with a quick " +
        "stab or two, you feel that it can at least be servicable.\n");
    	    
    set_hit(25);
    set_pen(25);
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
