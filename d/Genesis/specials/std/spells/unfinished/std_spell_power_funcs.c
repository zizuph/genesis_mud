/*   Created by Arman 9 October 2020
 *
 *   Inherit this in weapons or objects to allow for spell power
 *   to be incorporated in to the object when held/wielded/worn. 
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>

int magic_spellpower;
int appraise_chance = min(100, (20 + random(100)));

public int
query_magic_spellpower_app_chance()
{
    return appraise_chance;
}

public int
query_magic_spellpower()
{
    return magic_spellpower;
}

/*
 * Function name: set_magic_spellpower
 * Description:   This function sets the spellpower of an item in the 
 *                create_object or create_weapon etc function.
 * Argument:      Power provides a 'pen' supplement for magical harm and 
 *                heal spells in 
 *                /d/Genesis/specials/std/spells/centralized_spell.c
 *
 *                Treat the power argument in the same way you would
 *                set_pen for weapons. Items providing 50+ should be
 *                powerful relics that are very challenging to get.
 *                In general power should not exceed 60.
 *
 *                All items with set_magic_spellpower need to be classed
 *                as magical items, documented as such, and reviewed by
 *                the AoB. These items also required to decay from use.
 */

public void
set_magic_spellpower(int power)
{
    power = max(0, (min(68, power)));

    magic_spellpower = power;
}

/*
 * Function name: query_spellpower_desc
 * Description:   This function describes the spell power of an object
 *                when appraised. Mask this if you wish to change the
 *                spell power appraise description.
 */

public void
query_spellpower_desc()
{
    string desc;
    int spell_skill = this_player()->query_skill(SS_SPELLCRAFT);

    if (spell_skill < 20)
        return;

    if(spell_skill < appraise_chance)
    {
        write("\nYou feel "+LANG_THESHORT(this_object())+ 
            " may enhance spell power, but on this inspection " +
            "you are unable to determine more than that.\n");
    }

    switch(magic_spellpower)
    {
        case 0:
            desc = " not enhance the power of spells at all.";
            break;
        case 1..10:
            desc = " enhance the power of spells slightly.";
            break;
        case 11..20:
            desc = " enhance the power of spells somewhat.";
            break;
        case 21..30:
            desc = " enhance the power of spells.";
            break;
        case 31..40:
            desc = " reasonably enhance the power of spells.";
            break;
        case 41..50:
            desc = " greatly enhance the power of spells.";
            break;
        case 51..60:
            desc = " mightily enhance the power of spells.";
            break;
        default:
            desc = " supremely enhance the power of spells.";
            break;
    }

    write("\nWith your knowledge of spellcraft, you feel "+ 
        LANG_THESHORT(this_object())+ " will" +desc+ "\n");
}


