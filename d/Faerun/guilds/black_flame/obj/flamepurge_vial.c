/*
* /d/Faerun/guilds/black_flame/obj/flamepurge_vial.c
*
* Spell component for the Black flame guild.
*
* Nerull 2022
*/

inherit "/std/heap";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../guild.h"

string *required_spell_names;
string received_effect_name;
int maximum_charges = 1;


int
query_band_fit()
{
	return 1;
}


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

    if (player->query_guild_name_lay() != LAY_BF_GUILD_NAME)
        return 0;
    
    if (player->query_guild_level_lay() > 0)
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
bf_special_effect()
{
    string *available_spells = filter(required_spell_names, 
        &has_spell(this_player()));

    if (!sizeof(available_spells)) return;
    
    int final_charges = maximum_charges;

    setuid();
    seteuid(getuid());

    object spell_ingredient = clone_object(BF_SPELLS_DIR + "spell_ingredient");
    spell_ingredient->configure_spell_ingredient(received_effect_name,available_spells);
    spell_ingredient->set_heap_size(final_charges);

    if(!present(received_effect_name, this_player())) 
    {
        write("You can now cast " + COMPOSITE_WORDS(available_spells) + ".\n");
    }

    spell_ingredient->move(this_player(), 1);
}


int
use_bf_vial(string str)
{
    if (str == "fiery vial" 
        || str == "tiny fiery vial"
		|| str == "tiny vial"
		|| str == "vial")
    {
        write("You consume a tiny fiery vial!\n");
        
        bf_special_effect();

        this_object()->reduce_heap_size(1);
        
        return 1;
    }

    return 0;
}   


void
create_heap()
{
    set_heap_size(1);
    
	set_name("_flamepurge_vial");
    add_name("purgatory");
    add_name("vial");
    set_pname("vials");
    add_name("_spell_ingredient");
    add_prop(HEAP_S_UNIQUE_ID, "_flamepurge_vial");
    
    set_adj("tiny");
    add_adj("fiery");
    
    set_short("tiny fiery vial");
    set_pshort("tiny fiery vials");
	
    set_long("This vial is formed like a cylinder "
	+"and mesaures about 3 centimeters in height, and about "
	+"2 centimeters in diameter. It is made of glass, "
	+"and is fiery.\n");

    /* Weight of a single heap item */
    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    /* Volume of a single heap item */
    add_prop(HEAP_I_UNIT_VOLUME, 9);
    /* Value of a single heap item */
    add_prop(HEAP_I_UNIT_VALUE, 4000);
    
    setup_spell_effect("flamepurge", "_flamepurge_charge", SPELL_STD_CHARGE);
}


public void
init()
{
    ::init();
    
    add_action(use_bf_vial, "consume");
}


/*
 * Function name: query_auto_load
 * Description  : Charms are autoloading. 
 * Returns      : string - the auto-load string.
 */
public string
query_auto_load()
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;
    
    return (MASTER + ":" + num_heap());
}


/* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the type of shard
 * Arguments    : string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    int size;
    
    if (sscanf(arg, "%d", size) == 1)
    {
        set_heap_size(max(1, size));
    }
}