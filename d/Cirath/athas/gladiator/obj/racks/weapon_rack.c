/**********************************************************************
 * - weapon_rack.c                                                  - *
 *
 * - A rack for holding weapons that are not axes for Gladiator  - *
 * - Guild.                                                         - *
 *
 * - Created by Damaris@Genesis 09/2005                             - *
 * April 2013 (Serpine) - Converted to bin for clarity
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
    set_name("pile");
    remove_name("rack");
    set_adj("weapon");
    add_adj("weapons");
    set_short("weapon pile");

    set_long("This pile is the dumping spot for all the weapons " +
        "gladiators fine less worthy of respect: Specifically those " +
        "that lack axelike qualities and thus are less likely to " +
        "amuse the bloodthirsty arena audience.\n" +
        "You may <sort weapon pile> to organise this somewhat.\n");
        
    set_no_show_composite(1);
        
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_RIGID, 1);

    add_prop(OBJ_I_NO_GET, "Its a pile; Be more specific.\n");
}



public int
prevent_enter(object ob)
{
    int weapon;
        
    if (IS_WEAPON_OBJECT(ob) && (ob->query_wt() != W_AXE))
        return 0;

    write("This pile is not for axes or armours.\n");
    return 1;
}
