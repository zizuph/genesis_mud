/* Magical axe wielded by Ergothian sea captain
 *
 * Arman - January 2021
 *
 * Ckrik - Feb 2022
 *     Made into spell enhancers 
 */

inherit "/std/weapon";
inherit "/d/Genesis/specials/examples/std_magic_lib";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

#define HASTE   "/d/Krynn/turbidus_ocean/spells/phoenix_axe_haste.c"

void
create_weapon()
{
    set_name("axe");
    add_name("_blue_phoenix_axe");
    add_name("axe");
    set_adj("bladed");
    add_adj("phoenix");
    add_adj("phoenix-bladed");
    set_short("phoenix-bladed axe");
    set_long("This is a beautifully crafted axe forged from the " +
        "finest Ergothian steel and expertly tinted pale blue. " +
        "The head of the axe has been shaped to look like a phoenix " +
        "in flight, its wings flaring out into the very sharp blade " +
        "of the axe.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is the Blue Phoenix, a famed axe " +
         "crafted at the height of the Ergothian Empire, 1800 years before " +
         "the Cataclysm. It was crafted in reverence to the good god " +
         "Habbakuk.\n", 15, "This axe dulls very slowly, and when " +
         "the Blue Phoenix Habbakuk is praised an enchantment of speed " +
         "is bestowed upon the wielder at the cost of mental energy.\n", 25}));
    add_prop(OBJ_S_WIZINFO, "This weapon can be wielded by the Erothian captain " +
         "/d/Krynn/turbidus_ocean/living/ergothian_captain.c\nIt dulls at " +
         "33% the rate of normal weapons, and when the command 'praise " +
         "habbakuk' is used it grants a quickness enhancement that is outlined " +
         "in /d/Krynn/turbidus_ocean/spells/phoenix_axe_haste.c, equating to " +
         "a boost of 27 live_i_quickness or 15 caid. This effect lasts for " +
         "15 minutes and costs 150 mana to activate, with standard ongoing " +
         "spell maintenance cost as with all standardised maintained spell " +
         "effects.\n");

    set_default_weapon(35, 35, W_AXE, W_SLASH, W_LEFT);
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(42);
    set_spellpower_elements(({ SS_ELEMENT_AIR, SS_ELEMENT_WATER }));
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 4500);

   add_magic_obj_spell("[the] [blue] 'phoenix' / 'habbakuk' ",
       ({ "praise" }), HASTE);

    set_magic_obj_effect(({"_phoenix_haste_object_"}));

    set_wf(this_object());
    seteuid(getuid(this_object()));
}

/*
 * Function name:        set_dull
 * Description  :        Ignore or give chance to ignore dull
 * Returns      :        int - New dull amount
 */
public int
set_dull(int x)
{
    if (!random(3))
        return query_dull();
    else
        return set_dull(x);
} /* set_dull */

mixed 
wield(object what)
{
    add_magic_obj_effects(TP);
    return 0;
}

mixed 
unwield(object what)
{
    remove_magic_obj_effects(TP);
    return 0;
}

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!this_object()->query_wielded())
    {
        write("You have to be wielding the " +short()+ " to " +
            "activate it.\n");
        return 0;
    }

    if(HASTE->has_spell_object(E(TO)))
    {
        write("The " +short()+ " is already activated!\n");
        return 0;
    }

    if(HASTE->query_ability_preparing(E(TO)))
    {
        write("The " +short()+ " is currently activating!\n");
        return 0;
    }

    return 1;
}

void
init()
{
    ::init();
    
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}

/*
 * Function:    leave_env
 * Description: Standard leave_env, removes magic effects and
 *              handles holdable object.
 * Arguments:   object from - the environment we are leaving.
 *              object to   - the environment we are entering.
 */
void
leave_env(object env, object to)
{
    /* Required to remove the previously added effects to the item */
    remove_magic_obj_effects(env);
    
    ::leave_env(env, to);
} /* leave_env */

/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    arg = lower_case(arg);

    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Praise who?\n");
    
    return result;
} /* cmd_parse_spell_action */

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
