/*  /d/Faerun/alchemy/recipes/dragonfire_recipe.c
 *
 *  Quest Item, imbued with Exposive runes.
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
    set_name("_dragonfire_recipe");
    add_name("scroll");
    set_adj("curious");
    
    set_short("curious scroll");
    
    set_pshort("curious scroll");
    
    set_long("This is a fine scroll of papyrus that contains "
    +"a couple of alchemical recipes. It states as follows:\n"
    +"\n"
    +"  Recipe for dragonfire\n"
    +"  ---------------------\n"
    +"  1. The herb Pepper\n"
    +"  2. Volatile agent\n"
    +"\n"
    +"  Recipe for volatile agent\n"
    +"  ---------------------\n"
    +"  1. Purified sulphur\n"
    +"  2. Dragonfire crystal\n");
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 1000);
    
    set_may_not_recover();
}