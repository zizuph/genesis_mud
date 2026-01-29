/*
 * File Name        : sash.c
 * By               : Elmore.
 * Inspiration from : Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : This is the guild item for the pirates.
 *                    It is possible to wear and remove this
 *                    object.
 *
 */

#pragma strict_types

inherit "/std/armour";

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("sash");
    add_name(GUILD_EMBLEM_ID);
    set_adj("black");
    add_adj("silver-lined");
    set_short("black silver-lined sash");
    set_long("@@my_long");

    add_prop(OBJ_M_NO_DROP, "You cannot drop the sash.\n");
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  100);
    add_prop(OBJ_I_VOLUME,  100);
    remove_prop(OBJ_I_VALUE);
    set_may_not_recover();
}
   
string
my_long()
{
    return "This is a black sash, worn only by the feared pirates of "+
           "the Bloodsea. Thin silverthreads has been weaved into the "+
           "fabric, it shimmers slightly as you move the sash in the "+
           "sunlight. The words 'help sash' has been printed on it.\n";
}


