inherit "/d/Krynn/std/std_magic_obj";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_magic_obj()
{
    set_name("wand");
    add_adj("pale");
    set_long("This is a thin delicate wand carved from wood. It is very " +
        "pale, almost translucent.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This is a wand of light. When held the owner is able " +
           "to cast the light spell 'shirak'. Waving the wand has the " +
           "same effect as casting the spell.\n", 20 }));
        
    set_slots(W_ANYH);
    set_keep(1);

    set_holdable(1);
    
    set_magic_obj_spell("/d/Krynn/tharkadan/spells/tremorsense.c");
    set_magic_obj_effect("_tremorsense_object_");
    
    add_cmd_item(({"pale wand","wand"}),"wave","@@wave_wand");
}

string
wave_wand()
{
    if(!this_object()->query_held())
    {
        write("You have to be holding the wand to wave it.\n");
        return "";
    }

    if (safely_load_master_file(query_magic_obj_spell()[0]))
        query_magic_obj_spell()[0]->do_ability("");
    
    return "";
}