/* This is a backpack sold in the general store in the gnome
village of Rust. Created by Bishop (modeled after Maniacs pack
sold in the Crystalline palace), 6/11/98 - Calia. */

#pragma save_binary

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"

object this;

void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("light backpack");
    set_pshort("light backpacks");
    set_adj("llight");
    set_long("This backpack looks like it could hold a fair amount" +
        " of stuff. It is lightweight, and looks like it's made to fit" +
        " a gnome or a hobbit. The leather straps are adjustable, so" +
        " it could probably fit a human or elf as well. It's been dyed" +
        " in a greyish green colour, probably to make it stand out less" +
        " when hiding in the underbrush.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 2000);      
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 4500);      
    add_prop(CONT_I_MAX_VOLUME, 100000); 

    add_prop(OBJ_I_VALUE, 500);                 
 
    this = TO; 
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}
