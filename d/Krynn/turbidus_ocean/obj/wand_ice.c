/* 
 *    Magic wand. Has a cold harm spell.
 *    
 *    Arman - 2020
 */
 
inherit "/d/Krynn/std/std_magic_obj";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

#define ICE_SPELL   "/d/Krynn/turbidus_ocean/spells/wand_ice_spell.c"

public void
create_wand()
{
    // Mask this function to customize the wand.
}

public nomask void
create_magic_obj()
{
    set_name("wand");
    add_adj("ivory");
    set_short("ivory wand");
    set_long("This is an ivory wand carved from a long thanoi tusk and " +
        "engraved with archaic runes - the language of the Ice Folk who " +
        "reside in the southern regions of Icereach. It radiates an " +
        "arctic chill.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This is a standard wand that provides some " +
        "minor spellpower benefits. " +
        "It can be used to cast an ice harm spell that has an " +
        "aid based on the users water skill and spellcraft:\n" +
        "/d/Krynn/turbidus_ocean/spells/wand_ice_spell.c\n");

    add_prop(MAGIC_AM_ID_INFO,
      ({ "This ivory wand has been enchanted by the ice wizards of the " +
         "Ice Folk, the winternorns.\n", 20,
         "The wand provides the holder with some enhancement " +
         "to their magical spellpower.\n", 30,
         "For holders of this wand with adequate water elemental skill and " +
         "spellcraft skill they are able to use the wand to 'freeze' their " +
         "enemies, sending harmful shards of ice in their direction.\n", 40 }));
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    add_cmd_item(({"runes","archaic runes"}),
        ({"translate","read"}), "@@read_runes");
    add_item(({"runes","archaic runes"}),"Beautifully carved, these " +
        "runes have been carefully engraved in to the ivory wand " +
        "by the winternorns of the Ice Folk. You may be able to " +
        "translate the runes if your language skill is good enough.\n");
        
    set_slots(W_ANYH);
    set_magic_spellpower(40);
    set_spellpower_elements(({ SS_ELEMENT_WATER, SS_ELEMENT_AIR }));
    set_keep(1);
    set_holdable(1);

    set_magic_obj_spell(ICE_SPELL);
    
    //Enable default item expiration
    set_item_expiration();
}

string
read_runes()
{
    if(this_player()->query_skill(SS_LANGUAGE) < 60)
    {
        write("You don't have the skill to decypher the " +
            "language of the Ice Folk.\n");
        return "";
    }

    write("You are able to translate a command word from the " +
        "archaic runes carved along the length of the wand - " +
        "'freeze'.\n");
    return "";
}

string
freeze_target(string str)
{
    object *oblist, target;
    string target_name;

    if(!this_object()->query_held())
    {
        write("You have to be holding the ivory wand to use it.\n");
        return "";
    }

    if(this_player()->query_prop(LIVE_O_CONCENTRATE))
    {
        this_player()->catch_tell("You are currently concentrating on casting " +
            "another spell, and cannot activate the ivory wand.\n");
        return "";
    }

    if(!str)
    {
        if (safely_load_master_file(query_magic_obj_spell()[0]))
        {
            query_magic_obj_spell()[0]->do_ability("");
            query_magic_obj_spell()[0]->set_ability_pending(this_player(), 
                environment(this_player()), 1);
        }
        return "";
    }

    if (!strlen(str))
    {
        this_player()->catch_tell("Who do you wish to target?\n");
        return "";
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        this_player()->catch_tell("Whom do you wish to target?\n");
        return "";
    }

    if (sizeof(oblist) > 1)
    {
        this_player()->catch_tell("You will have to be more specific! You can only " +
            "select one target.\n");
        return "";
    }

    target = oblist[0];
    target_name = target->short();

    if (safely_load_master_file(query_magic_obj_spell()[0]))
    {
        query_magic_obj_spell()[0]->do_ability(target_name);
        query_magic_obj_spell()[0]->set_ability_pending(this_player(), 
            environment(this_player()), 1);
    }

    return "";
}

void
init()
{
    ::init();
    add_action(freeze_target, "freeze");
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

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
} /* query_recover */

void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    ::init_keep_recover(arg);
}