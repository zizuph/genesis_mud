/* Magical bracers worn by the dark dwarf savant lord.
 *
 * Arman - 2 March 2018
 */


inherit "/std/armour";
inherit "/d/Genesis/specials/examples/std_magic_lib";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

#define TREMORSENSE   "/d/Krynn/tharkadan/spells/tremorsense"

int charge = 3;

void
create_armour()
{
    setuid();
    seteuid(getuid());
    
    set_name("bracers");
    add_name("_umber_hulk_bracers");
    set_ac(50);
    set_at(A_ARMS);
    set_am( ({ -2, 3, 0 }) );
    set_adj("hulk");
    set_adj("umber");
    set_adj("umberhulk");
    set_short("bracers of the umber hulk");
    set_pshort("pairs of bracers of the umber hulk");
    set_long("This pair of bracers have been made from the incredibly " +
        "tough chitinous carapace of an umber hulk - a fearsome " +
        "subterranean monster capable of ripping through rock as though " +
        "it were light underbrush. Dark dwarven runes have been engraved " +
        "along the length of both bracers.\n");
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_ARMS));
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(53)));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This is a pair of magical bracers that has " +
        "been enchanted to capture the senses of the umber hulk for its " +
        "wearer when they are pressed together, activating the ability " +
        "'tremor sense' - allowing detection of invisible creatures.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This pair of bracers have been enchanted by dark dwarf " +
        "savants, allowing the wearer of these bracers to make use of " +
        "the umber hulk ability 'tremor sense' when the bracers are " +
        "pressed together, allowing the detection of hidden and " +
        "invisible creatures for a brief period. This ability can be " +
        "used a maximum of three times.\n", 30}));
    
   add_magic_obj_spell("[the] 'bracers' [of] [the] [umber] [hulk] 'together'",
       ({ "press" }), "/d/Krynn/tharkadan/spells/tremorsense.c");

    set_magic_obj_effect(({"_tremorsense_object_"}));

    set_af(this_object());
}


/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    add_magic_obj_effects(wearer);
    return 0;
} /* wear */

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    remove_magic_obj_effects(wearer);
    return 0;
} /* remove */

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!charge)
    {
        write("The enchantments charging the bracers of the umber " +
           "hulk have been exhausted. You cannot call upon the " +
           "tremor sense ability anymore.\n");
        return 0;
    }

    if(!this_object()->query_worn())
    {
        write("You have to be wearing the bracers to activate " +
            "tremor sense.\n");
        return 0;
    }

    if(TREMORSENSE->has_spell_object(E(TO)))
    {
        write("The bracers of the umberhulk are already activated!\n");
        return 0;
    }

    if(TREMORSENSE->query_ability_preparing(E(TO)))
    {
        write("The bracers of the umberhulk are currently activating!\n");
        return 0;
    }

    charge = charge - 1;

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
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Press what together? The bracers of the umber " +
            "hulk?\n");
    
    return result;
} /* cmd_parse_spell_action */