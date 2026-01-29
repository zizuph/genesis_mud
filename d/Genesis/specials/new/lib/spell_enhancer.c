/*
 *   /d/Genesis/specials/new/spell_enhancer.c
 *
 *   This defines the functions required for an item to be
 *   treated as a spell enhancer by the spell system.  This
 *   allows spellcasters to have items that can boost the
 *   damage of their attack spells.
 *
 *   It also provides a hook for the enhancer to affect the
 *   result of a spell, or to deliver additional effects beyond
 *   the spell itself.
 *
 *   Inherit this in weapons or objects to allow for spell power
 *   to be incorporated in to the object when held/wielded.
 *
 *   The spell power of the item will be analagous to the hit/pen
 *   of a weapon, but as a single number.  The values should be
 *   comparable to the hit or pen of one and two handed weapons,
 *   respectively.
 *
 *   Example usage for a weapon:
 *
 *   inherit "/std/weapon";
 *   #include "/d/Genesis/specials/local.h"
 *   inherit SPELL_ENHANCER;
 *
 *   void create_weapon()
 *   {
 *      set_short("my weapon");
 *      set_magic_spellpower(40);
 *    }
 *
 *    void appraise_object(int num)
 *    {
 *        ::appraise_object(num);
 *        write(item_spellpower_desc());
 *    }
 *
 *    string stat_object() {
 *        return ::stat_object() + stat_object_spellpower();
 *
 *
 *    Example usage for a held item:
 *
 *    inherit "/lib/holdable_item";
 *    #include "/d/Genesis/specials/local.h"
 *    inherit SPELL_ENHANCER;
 *
 *    void create_object()
 *    {
 *        set_name("my holdable item");
 *        set_magic_spellpower(40);
 *    }
 *
 *    void appraise_object(int num)
 *    {
 *        ::appraise_object(num);
 *        appraise_holdable_item();
 *        write(item_spellpower_desc());
 *    }
 *
 *    string stat_object() {
 *        return ::stat_object() + stat_object_spellpower();
 *    }
 *
  */

#include <composite.h>
#include <files.h>
#include <ss_types.h>

int magic_spellpower;    /* Enhancer spell power */

int* spellpower_elements = ({    /* Elements that the enhancer can use */
    SS_ELEMENT_FIRE,
    SS_ELEMENT_WATER,
    SS_ELEMENT_EARTH,
    SS_ELEMENT_AIR,
    SS_ELEMENT_DEATH,
    SS_ELEMENT_LIFE });

static mapping ELEMENTS_TO_SKILLS =
  ([
    SS_ELEMENT_FIRE : "fire",
    SS_ELEMENT_WATER : "water",
    SS_ELEMENT_EARTH : "earth",
    SS_ELEMENT_AIR : "air",
    SS_ELEMENT_DEATH : "death",
    SS_ELEMENT_LIFE: "life" ]);

/*
 * Function name: query_magic_spellpower
 * Description:   This function returns the spellpower that the item will
 *                provide when equipped.
 */
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
 *                In general one-handed items should not exceed 50, and
 *                two-handed items should not exceed 60.
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
 * Function name: query_spellpower_enhancer
 * Description:   Check whether this object can enhance spells.
 */
public int
query_spellpower_enhancer()
{
    return 1;
}

public int*
query_spellpower_elements()
{
    return spellpower_elements;
}

public void
set_spellpower_elements(int* element_skills)
{
    spellpower_elements = element_skills;
}

public string get_element_spells()
{
    if (member_array(SS_ELEMENT_AIR, spellpower_elements) >=0 &&
        member_array(SS_ELEMENT_FIRE, spellpower_elements) >=0 &&
        member_array(SS_ELEMENT_WATER, spellpower_elements) >=0 &&
        member_array(SS_ELEMENT_EARTH, spellpower_elements) >=0 &&
        member_array(SS_ELEMENT_DEATH, spellpower_elements) >=0 &&
        member_array(SS_ELEMENT_LIFE, spellpower_elements) >=0)
    {
        return "spells of any element";
    }
    string* elements = ({});
    foreach(int element : spellpower_elements)
    {
        elements += ({ ELEMENTS_TO_SKILLS[element] });
    }
    return COMPOSITE_WORDS(elements) + " spells";
}


/*
 * Function name: item_spellpower_desc
 * Description:   String to be shown as part of the item appraisal.
 */
public string
item_spellpower_desc()
{
    string types = get_element_spells();
    
    if (IS_WEAPON_OBJECT(this_object()))
    {
        return "\nThis weapon can be wielded to enhance " + types + ".\n";
    }
    return "\nThis item can be held to enhance " + types + ".\n";
}


/*
 * Function name: item_spellpower_desc
 * Description:   String to be displayed when an object is statted.
 */
string
stat_object_spellpower()
{
    return "Spell power: " + magic_spellpower + ", elements: " 
        + get_element_spells() + "\n";
}

/*
 * Function name: did_spell_hit
 * Description:   Allow the spell enhancer to perform an additional effect of
 *                its own.  Note that spells do not hit a specific hitloc,
 *                as resistance is constant over all hitlocs.
 * Argument       aid: Attack ID of the spell
 *                phurt: Percentage hurt.
 *                enemy: The target that was hit
 *                element: The spell element used by the spell.
 *                form: The spell form used by the spell.
 *                phit: The %success that we made with our enhancer
 *                dam: The actual damage caused by this enhancer in hit points
 *
 * Returns        An int indicating whether the item intends to override the
 *                messaging for the spell effect itself.
 */
public varargs int
did_spell_hit(int aid, int phurt, object enemy, int element,
                int form, int phit, int dam)
{
    return 0;
}
