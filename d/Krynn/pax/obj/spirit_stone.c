/* Arman May 2016 - spirit stone, based on Icewall ioun stones 
 * 
 * - No further mana restoration for hp items are to be allowed.
 *   all such functionality has been disabled.
 *   /AoB - Cotillion
 *
 * - Changed the benefit to an increase in SS_FORM_ENCHANTMENT
 *   Penalty remains, although frequency reduced.
 *  Updates:
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 35.
 */

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>

#define MAX_SKILL_GAIN   10

/* Global variable */
static int alarm_id = 0;
int skill_bonus = MAX_SKILL_GAIN;

public void
create_object()
{
    set_name("stone");
    add_name("_pax_banshee_spirit_stone_");
    set_adj("icy");
    add_adj("black");
    add_adj("spirit");
    set_short("icy black stone");

    set_long("This jet black stone is icy to touch. Staring too long at " +
       "it gives you a feeling of distressing vertigo, as if you were " +
       "looking down into the Abyss itself.\n");
 
    add_prop(OBJ_I_WEIGHT, 235);
    add_prop(OBJ_I_VOLUME, 79);
    add_prop(OBJ_I_VALUE, 3 * 12 * 12);

    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 30 }));

    add_prop(MAGIC_AM_ID_INFO, ({
	"There is something magical about the stone.\n", 1,
        "This is a spirit stone, used by powerful elven mages to " +
        "chain the soul of an evil elf of ages past for unspeakable " +
        "crimes. When held, the stone enhances any skill you have with enchantment " +
        "spells, however the residual icy cold of undeath will drain " +
        "your health.\n", 30 }) );

    add_prop(OBJ_S_WIZINFO, "This magic stone allows a minor increase in  " +
        "SS_FORM_ENCHANTMENT at the cost of health and panic.\n");
    will_not_recover = (random(100) < 80);
    set_slots(W_LEFT);
    set_keep(1);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(35);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_WATER
    }));
}

void
ioun_regeneration()
{
    /* Don't penalise when the player is very low on health. */
    if (holder->query_hp() > 100)
    {
        holder->catch_msg("You feel the icy cold of the black stone " +
           "drain your health.\n");
        holder->heal_hp(-100);
        holder->add_panic(20 + random(10));
    }

    alarm_id = set_alarm(120.0, 0.0, ioun_regeneration);   
}

public mixed
hold()
{

    if(holder->query_skill(SS_FORM_ENCHANTMENT))
        write("As you grasp the icy black stone in your hand, " +
           "you feel remnant memories of a lost soul pass in to you - " +
           "knowledge of curses and the dominating of minds - while your " +
           "life force drains in to the stone.\n");

    holder->set_skill_extra(SS_FORM_ENCHANTMENT, 
         holder->query_skill_extra(SS_FORM_ENCHANTMENT) + skill_bonus);

    alarm_id = set_alarm(3.0, 0.0, ioun_regeneration);   
    return 0;
}

public mixed
release()
{
    write("You feel warmth return to your limbs as you release the icy black stone.\n");

    holder->set_skill_extra(SS_FORM_ENCHANTMENT, 
         holder->query_skill_extra(SS_FORM_ENCHANTMENT) - skill_bonus);
    
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

public string
query_recover()
{
  return MASTER;
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
