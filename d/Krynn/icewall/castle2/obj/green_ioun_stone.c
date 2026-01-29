/* Navarre September 4th 2014: Added set_keep(1) as default keep setting */
/*
 *  Updates:
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 35.
 *       Zizuph, 2022-03-15:
 *         Standardized to heal and dynamic mana formulas, at 25 caid.
*/

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/d/Genesis/specials/new/resource";

inherit "/lib/item_expiration";
inherit "/lib/keep";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>

#define CAID 25

/* Global variable */
static int alarm_id = 0;

public void
create_object()
{
    set_name("stone");
    set_adj("leaf-green");
    add_adj("ioun");

    set_long("The small leaf-green stone seems to glimmer strangely. " +
       "It looks like one of the fabled ioun stones, but what powers " +
       "this one possesses, only a sage would know.\n");
 
    add_prop(OBJ_I_WEIGHT, 235);
    add_prop(OBJ_I_VOLUME, 79);
    add_prop(OBJ_I_VALUE, 3 * 12 * 12 * 12);

    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 30 }));

    add_prop(MAGIC_AM_ID_INFO, ({
	"There is something magical about the stone.\n", 1,
	"When held, the stone will grant you with the ability of " +
        "regeneration.\n", 30 }) );

    add_prop(OBJ_S_WIZINFO, "This magic stone allows regeneration.\n");

    set_slots(W_ANYH);
    set_keep(1);
    set_item_expiration();
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(35);          
}

void
ioun_regeneration()
{
    
    int mana_cost = get_dynamic_mana_cost(holder, ({ TS_WIS }), CAID, 0, 60);

    /* Don't regenerate when the player is very low on mana. */
    if (holder->query_mana() > mana_cost)
    {
        holder->catch_msg("You feel healthier as your body regenerates.\n");
        
        // Standard base - F_PENMOD(40, 100) with 40 AC resistance applied
        int heal = ftoi(itof(F_PENMOD(40, 100)) * (100.0 - F_AC_MOD(40)) / 100.0);

        // Apply CAID factor
        heal = heal * CAID / 100;
        
        // Apply alarm time vs swing time.
        heal = heal * 60 / 5;
        
        // Apply MAGIC_DT vs normal factor
        heal = heal * 4 / 5;
        
        heal = (heal / 4) + random(heal / 4)
            + random(heal / 4) + random(heal / 4);
        
        if (holder->query_wiz_level())
        {
            holder->catch_msg("Heal amount: " + heal + "\n");
        }
        holder->heal_hp(heal);
        holder->add_mana(-mana_cost);
    }

    alarm_id = set_alarm(60.0, 0.0, ioun_regeneration);   
}

public mixed
hold()
{
    write("As you grasp the leaf-green ioun stone in your hand, " +
        "you feel " +
       "different, as if pure life flowed into your body.\n");

    alarm_id = set_alarm(60.0, 0.0, ioun_regeneration);   
    return 0;
}

public mixed
release()
{
    write("As you release the leaf-green ioun stone, you feel normal again.\n");
    
    remove_alarm(alarm_id);
    alarm_id = 0;
    return 0;
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
    write(item_spellpower_desc());
}

string
query_recover()
{
  return MASTER + ":" + query_keep_recover() + query_item_expiration_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_item_expiration_recover(arg);
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
