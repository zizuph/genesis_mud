/*
 *  This is an example of a wand item that incorporates 
 *  spells using the magic system.
 *
 *  This type of item can be applied to any object type,
 *  the key element being the inherit of the std_magic_obj.c
 *
 *  Arman Sept 2017
 */


inherit "/d/Genesis/specials/examples/std_magic_obj";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_magic_obj()
{
    set_name("wand");
    add_adj("example");
    set_long("This is an example of a wand that incorporates spells from the " +
        "magic system. The command to use it is <flick>.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a wand of light. When held the owner is able " +
         "to cast the light spell 'illuminatus'. Waving the wand has the " +
         "same effect as casting the spell.\n", 20 }));
        
    set_slots(W_ANYH);
    set_keep(1);

    set_holdable(1);
    
    add_magic_obj_spell("[the] [example] 'wand'", ({ "flick" }),
                        "/d/Genesis/specials/examples/wand_example_light_spell.c");

    // important to set this to align with the spell object name so that if
    // the wand is dropped or unheld the effect ends.
    set_magic_obj_effect(({ "_example_wand_light_object_" }));
    
}
