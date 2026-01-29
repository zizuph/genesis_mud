inherit "/d/Krynn/std/std_magic_obj";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TO this_object()

public void
create_wand()
{
    // Mask this function to customize the wand.
}

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
           "same effect as casting the spell.\n", 20,
           "The wand also provides the holder with some enhancement " +
           "to their magical spellpower.\n", 30 }));
        
    set_slots(W_ANYH);
    set_magic_spellpower(35);
    set_keep(1);

    set_holdable(1);
    
    set_magic_obj_spell("/d/Krynn/tharkadan/spells/wand_light_spell.c");
    set_magic_obj_effect("_light_object_");
    
    add_cmd_item(({"pale wand","wand"}),"wave","@@wave_wand");

    //Enable default item expiration
    set_item_expiration();
    // Call the create_wand function for customization purposes
    // Give it a moment to load props before calling
    set_alarm(1.0, 0.0, &create_wand());
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

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}
 
void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    ::init_keep_recover(arg);
}


void 
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}