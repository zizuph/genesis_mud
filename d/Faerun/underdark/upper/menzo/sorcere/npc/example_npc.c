/*
 *  faerun/underdark/upper/menzo/sorcere/example_drow.c
 *
 *  This is a sample drow, doesnt do much
 *
 *  Created by Wully, 12-2-2004
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_SORCERE + "base_drow";

/*
 * Function name: create_sorcere_drow
 * Description  : Construct a drow for the Sorcere part of Menzoberranzan
 */
void create_sorcere_drow()
{
    set_name("banzaai");
    set_adj( ({ "dark-haired", "black-eyed" }) );
    set_long("It's an old dark-haired black-eyed drow.\n");
    
    set_stats(({ 120, 185, 140, 155, 140, 130 }));

    set_skill(SS_ELEMENT_FIRE, 60);
    set_skill(SS_SPELLCRAFT, 70);
    set_skill(SS_FORM_CONJURATION, 40);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Set up our spellcasting stuff
    add_spell("/w/midnight/kargs/fireball");
    set_cast_chance(50);
    setup_spellcasting();
}

