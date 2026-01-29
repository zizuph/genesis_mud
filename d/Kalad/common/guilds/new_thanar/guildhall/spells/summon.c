/* 
 * /d/Kalad/common/guilds/new_thanar/guildhall/spells/summon.c
 * 
 * Spell file for the messenger summon for thanar racial guild.
 */

#include "../guild.h"
inherit "/d/Genesis/specials/std/spells/summon.c";


/*
 * Function:    config_summon_spell
 * Description: Config function for summon spells. Redefine this in your
 *              own summon spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_summon_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_desc("Summon messenger");
    
    set_spell_fail("You are not able to connect with the divine.\n");
    
    // The default summon spell simply summons a messenger into the inventory of the caster
    set_summon_file(MESSENGER_DIR + "snake");
    set_summon_into_inventory(1);
    
    // Set the effect object filename
    set_spell_object(GSPELLS + "summon_obj.c");
}