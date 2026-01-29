/*  /d/Raumdor/common/beach/bountiful/chest_rewards/c_razor.c
 *
 *  Money Drop Item - Common.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("razor");
    set_adj("gold-handled");
    add_adj("obsidian");
    add_adj("straight");

    set_short("gold-handled obsidian straight razor");
    set_pshort("gold-handled obsidian straight razors");
    
    set_long("Each part of this folding straight razor is made with "
    +"obsidian. The cutting side is leathally sharp and the handle "
    +"is covered by a gold sheathe which depicts a large cat "
    +"on each flat side.\n");
    
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 10000);
}