/**********************************************************************
 * - supply_rack.c                                                  - *
 *
 * - A rack for holding misc for Gladiator guild.                   - *
 *
 * April 2013 (Serpine) 
 *********************************************************************
 */

#pragma strict_types
#pragma save_binary

#include <files.h>
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"
inherit RACK_BASE;

public void
create_rack()
{
    set_name("chest");
    remove_name("rack");
    set_adj("huge");
    add_adj("stone");
    add_adj("supply");
    
    set_short("huge stone supply chest");

    set_long("This massive stone chest is used to hold equipment for " +
        "the Gladiators so they can keep themselves supplied. As this "+
        "saves their master Kalak money, he encourages them to use, "+
        "supply, and defend it as they see fit.\n"+
        "You may <sort chest> to organise it.\n");
        
    set_no_show_composite(1);
        
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this " +
        "thing.\n");
}



public int
prevent_enter(object ob)
{

    if (!IS_WEAPON_OBJECT(ob) && !IS_ARMOUR_OBJECT(ob))
            return 0;

    write("The chest is not for weapons and armor.\n");
        return 1;
}
