/* 
 *    Magic wand. Has an earth harm spell, and is a quest item
 *    for the WoHS.
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

#define PETRIFY   "/d/Krynn/throtyl/spells/wand_petrify_spell.c"

public void
create_wand()
{
    // Mask this function to customize the wand.
}

public int
query_magic_spellpower()
{
    return 20;
}

public nomask void
create_magic_obj()
{
    set_name("stick");
    add_name("wand");
    add_name("_stick_of_ancestors");
    set_short("petrified stick");
    set_long("This is an ancient stick, petrified by age. Once a gnarled limb " +
        "of what would be a great oak, it radiates an alpine chill.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This is a standard wand that provides some " +
        "minor spellpower benefits. It is largely used by WoHS to claim " +
        "the 'stellar alignment' spell from the Tree of Ancestors at " +
        "/d/Ansalon/guild/neidar/rooms/ancestor_tree.c\n"+ 
        "It also can be used to cast an earth harm spell that has an " +
        "aid based on the users earth skill and spellcraft:\n" +
        "/d/Krynn/throtyl/spells/wand_petrify_spell.c\n");

    add_prop(MAGIC_AM_ID_INFO,
      ({ "This petrified stick is actually a limb from the Tree of Ancestors, " +
         "the venerated symbol of the hill dwarves based in the Tharkadan " +
         "Mountain Ranges where Doomseekers take their death-oath. You feel " +
         "a strong pull to return this stick to its place of origin.\n", 20,
         "This petrified stick can be used as a wand of sorts, with " +
         "residual enchantments providing some spell power to its holder. " +
         "If the holder has an adequate earth elemental skill and conjuration " +
         "skill they can also draw power from the Tree of Ancestors and " +
         "'petrify' enemies with a blast of earth magic.\n", 40,
         "The wand also provides the holder with some enhancement " +
         "to their magical spellpower.\n", 45 }));
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
        
    set_slots(W_ANYH);
    set_magic_spellpower(40);
    set_spellpower_elements(({
        SS_ELEMENT_EARTH, SS_ELEMENT_AIR, SS_ELEMENT_WATER
    }));
    set_keep(1);
    set_holdable(1);

    set_magic_obj_spell(PETRIFY);
    
    //Enable default item expiration
    set_item_expiration();
}

string
petrify_target(string str)
{
    object *oblist, target;
    string target_name;

    if(!this_object()->query_held())
    {
        write("You have to be holding the petrified stick to use it.\n");
        return "";
    }

    if(this_player()->query_prop(LIVE_O_CONCENTRATE))
    {
        this_player()->catch_tell("You are currently concentrating on casting " +
            "another spell, and cannot activate the petrified stick.\n");
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
    add_action(petrify_target, "petrify");
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