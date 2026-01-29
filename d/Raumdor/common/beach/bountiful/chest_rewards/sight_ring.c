/*  /d/Raumdor/common/beach/bountiful/chest_rewards/sight_ring
 *
 *
 *  Allows the wearer to see see
 *  invisible creatures.
 *
 *  Nerull, 2021
 *
 */

inherit "/std/armour";
inherit "/d/Genesis/specials/examples/std_magic_lib";
inherit "/lib/keep";
#include "../defs.h";
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <const.h>
#include <wa_types.h>

object wearer;

#define TRUESIGHT   "/d/Raumdor/common/beach/bountiful/spells/ring_truesight"

int charge = 3;


void
recharge()
{
    charge = charge + 1;
    
    if (charge > 3)
    {
        charge = 3;
    }
}


void
create_armour()
{
    set_name("ring");

    set_adj("thin");
    add_adj("gold");

    set_short("thin gold ring");
    set_pshort("thin gold rings");

    set_long("This is a very narrow band of plain "
    +"gold. It has no markings on it beside signs "
    +"of regular wear.\n");

    set_at(A_ANY_FINGER);

    set_ac(1);

    set_af(this_object());

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 60,"enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This item when rubbed will activate the "
    +"ability 'truesight'.\n",20 }));

    add_prop(OBJ_S_WIZINFO, "This item adds "
    +" 5 points of live_i_see_invis.\n");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_VALUE, 1200);
    
    add_magic_obj_spell("[the] [thin] [gold] 'ring'",
       ({ "rub" }), "/d/Raumdor/common/beach/bountiful/spells/ring_truesight.c");
       
    set_magic_obj_effect(({"_ring_truesight_object_"}));
    
    set_alarm(3600.0, 3600.0, &recharge());
}


mixed
wear(object what)
{
    add_magic_obj_effects(wearer);
    return 0;
    
}


mixed
remove(object what)
{
    remove_magic_obj_effects(wearer);
    return 0;
}


public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!charge)
    {
        write("The enchantments charging the "+short()+" " +
           "have been exhausted. You cannot call upon the " +
           "truesight ability anymore.\n");
        return 0;
    }
    
    if(!this_object()->query_worn())
    {
        write("You have to be wearing the thin gold ring to activate " +
            "truesight.\n");
        return 0;
    }
    
    if (present("_ring_truesight_object_", E(TO)))
    {
        write("The thin gold ring is already activated!\n");
        return 0;
    }
    
    if(TRUESIGHT->has_spell_object(E(TO)))
    {
        write("The thin gold ring is already activated!\n");
        return 0;
    }
    
    if(TRUESIGHT->query_ability_preparing(E(TO)))
    {
        write("The thin gold ring is currently activating!\n");
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
        notify_fail("rub what? The thin gold ring?\n");
     
    return result;
} /* cmd_parse_spell_action */


