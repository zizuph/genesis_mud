/*
* /d/Faerun/guilds/warlocks/obj/war_heart_charm_4.c
*
* Spell component for the warlock guild.
*
* Nerull 2017
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../guild.h"

string *required_spell_names;
string received_effect_name;
int maximum_charges = 1;


void
setup_spell_effect(mixed spellnames, string effectname, int charges)
{
    required_spell_names = pointerp(spellnames) ? spellnames : ({ spellnames});
    
    received_effect_name = effectname;
    
    maximum_charges = charges;
}


public varargs int
query_spell_active(object player)
{
    if (!objectp(player))
        player = this_player();

    if (player->query_guild_name_lay() != WARLOCK_NAME)
        return 0;
    
    if (player->query_guild_level_lay() < DESECRATE_UNLOCK)
        return 0;

    return 1;
}


/* This function takes into account that for the generic spell casting
 * system, each spell is it's own spell object.
 */
int
has_spell(object player, string spellname)
{
    object spellobj = player->find_spell(spellname);
    
    if (!objectp(spellobj)) return 0;
    
    return spellobj->query_spell_can_be_learned(player);
}


void
war_special_effect()
{
    string *available_spells = filter(required_spell_names, 
        &has_spell(this_player()));

    if (!sizeof(available_spells)) return;
    
    int final_charges = maximum_charges;

    setuid();
    seteuid(getuid());

    object spell_ingredient = clone_object(WARLOCK_SPELLS_DIR + "spell_ingredient");
    spell_ingredient->configure_spell_ingredient(received_effect_name,available_spells);
    spell_ingredient->set_heap_size(final_charges);

    if(!present(received_effect_name, this_player())) 
    {
        write("You can now cast " + COMPOSITE_WORDS(available_spells) + ".\n");
    }

    spell_ingredient->move(this_player(), 1);
}


int
use_charm(string str)
{
    if (str == "frosty charm" 
        || str == "frosty heart charm"
        || str == "hardened frosty heart charm")
    {
        write("You sacrfice a hardened frosty heart charm to "
        +"your patron!\n");
        
        war_special_effect();

        this_object()->reduce_heap_size(1);
        
        return 1;
    }

    return 0;
}   

void
create_heap()
{
    set_heap_size(1);
    
    set_name("charm");
    set_pname("charms");
    add_name("_war_heart_charm_4");
    add_prop(HEAP_S_UNIQUE_ID, "_war_heart_charm_4");
    
    set_adj("hardened");
    add_adj("frosty");
    add_adj("heart");
    
    set_short("hardened frosty heart charm");
    set_pshort("hardened frosty heart charms");
    set_long("This magical charm made from a piece of heart "
    +"muscle is roughly triangular in "
    +"shape. It measures about two inches in lenght on all sides, and "
    +"about a quarter of an inch in thickness. A vague "
    +"arcane symbol of power is etched into both sides of "
    +"the frost-covered muscle tissue.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 2);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 2);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 4000);
    
    setup_spell_effect("desecrate", "_desecrate_charge", SPELL_STD_CHARGE);
}

public void
init()
{
    ::init();
    
    add_action(use_charm, "flare");
}

/* 
 * This is called when an autoloading object is reloaded.  We use
 * it to restore the heap to it's correct size.
 */
void
init_arg(string arg)
{
    set_heap_size(atoi(arg));
}

/*
 * This is called when the player is logging out.  We use it to
 * store the size of the heap so that we can restore it to the right
 * amount when the player logs back in.
 */
string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}
