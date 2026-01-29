/*
 * /d/Gondor/common/guilds/morgulmage/potions/base_potion.c
 *
 * Base file for all Morgul Mage potions. 
 */

#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "../morgulmage.h"

inherit "/std/potion";

#define ROUND_UP(f) (ftoi(f + 0.999))

string *required_spell_names;
string received_effect_name;
int maximum_charges = 1;

void
create_morgul_potion() 
{

}

/*
 * Function name: query_strength
 * Description  : Redefine this function in your potion to calculate the
 *                strength based on the alcohol and soft values. The
 *                resulting strength should be in the range 0 .. 100.
 * Arguments    : int - the strength
 */
int
query_strength()
{
    return 0;
}

public string
strength_adj()
{
    if (!query_identified())
        return "strange";

    switch(query_strength())
    {
        default:
        case 0..50:
            return "watery";
        case 51..70:
            return "light";
        case 71..90:
            return "strong";
        case 91..100:
            return "powerful";
     }
}

public string
short_desc()
{
    string adjs = implode(query_adjs(), " ");

    return (strength_adj() + " " + adjs + " " + query_name());
}

public nomask void
create_potion()
{
    create_morgul_potion();
    set_short(short_desc);
    set_effect(HERB_SPECIAL, "spell_effect", 0);
}

/* Called from the potion store to set up the potion. */
void
set_up_effect(int soft, int alco)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
}

/* Called from the mortar to set up the potion. */
public int
set_up_potion(mixed ingr)
{
    set_up_effect(ingr[0]->query_soft_amount(),
                  ingr[0]->query_alco_amount());

    return 0;
}

void
setup_spell_effect(mixed spellnames, string effectname, int charges)
{
    required_spell_names = pointerp(spellnames) ? spellnames : ({ spellnames });
    received_effect_name = effectname;
    maximum_charges = charges;
}

public varargs int
query_spell_active(object player, int spell_min)
{
    if (!objectp(player))
        player = this_player();

    if (player->query_guild_name_occ() != GUILD_NAME)
        return 0;
    if (player->query_morgul_level() < spell_min)
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
special_effect()
{
    if (query_strength() < 10) return;

    string *available_spells = filter(required_spell_names, 
        &has_spell(this_player()));

    if (!sizeof(available_spells)) return;
    
    int charges_for_strength = ROUND_UP(itof(maximum_charges) * itof(query_strength()) / 100.0);
    int final_charges = MAX(1, MIN(charges_for_strength, maximum_charges));

    setuid();
    seteuid(getuid());

    object spell_ingredient = clone_object(MORGUL_POTION_DIR + "spell_ingredient");
    spell_ingredient->configure_spell_ingredient(received_effect_name, available_spells);
    spell_ingredient->set_heap_size(final_charges);

    if(!present(received_effect_name, this_player())) 
    {
        write("You can now cast " + COMPOSITE_WORDS(available_spells) + ".\n");
    }

    spell_ingredient->move(this_player(), 1);
}

void
init_recover(string str)
{
    string  dummy;
    int     value;

    ::init_recover(str);

    /* Support for old style recovery of morgul potions. */
    sscanf(str, "%s#sa#%d#%s", dummy, value, dummy);
    if (value) set_soft_amount(value);
    sscanf(str, "%s#aa#%d#%s", dummy, value, dummy);
    if (value) set_alco_amount(value);
}
