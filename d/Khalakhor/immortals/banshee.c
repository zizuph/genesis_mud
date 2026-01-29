#pragma strict_type

#include <composite.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#undef UNDEAD_DEBUG
#define MIN_PEN_TOHIT 300

inherit "/std/monster";

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object *temp;
    int i;

#ifdef UNDEAD_DEBUG
    tell_object(attacker, "WCPEN = " + wcpen + "\n");
#endif

    if (wcpen > MIN_PEN_TOHIT || dt == MAGIC_DT)
        return ::hit_me(wcpen, dt, attacker, attack_id);
    temp = attacker->query_weapon(-1);
    for (i = 0; i < sizeof(temp); i++)
    {
        if (temp[i]->query_attack_id() == attack_id)
        {
            if (temp[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
                return ::hit_me(wcpen, dt, attacker, attack_id);
            else
            {
                tell_object(attacker, "Your " + temp[i]->query_name() +
                    " passes harmlessly through the " + short() +
                    "!\n");
                tell_room(environment(), QCTNAME(attacker) + "'s " +
                    temp[i]->query_name() + " passes harmlessly " +
                    "through the " + short() + "!\n", attacker);
                return ({0, 0, 0, 0});
            }
        }
    }
    tell_object(attacker, "Your " + 
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the " + short() + "!\n");
    tell_room(environment(), QCTNAME(attacker) + "'s " +
        attacker->cr_attack_desc(attack_id) + " passes " +
        "harmlessly through the " + short() + "!\n", attacker);
    return ({0, 0, 0, 0});
}

public void
create_monster()
{
    set_name(({"apparition","banshee","ghost","spirit"}));
    set_adj(({"glowing","transluscent"}));
    set_long("The apparition before you is that of a beautiful woman, " +
        "though her face distorted into a mask of pain and loathing. " +
        "Transluscent and pulsing with a sickly green glow, her tattered " +
        "robes flow about her as if on an unseen wind as she hovers above " +
        "the ground.\n");

  /* Set up stats, all stats to 300 */  
    default_config_npc(300);

  /* Set aggressive, npc will autoattack. */
    set_aggressive(0);

  /* Set up skills. */
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_DEATH, 100);

  /* Set up props */
    add_prop(LIVE_I_UNDEAD, 100);    // A banshee's about as undead as it gets.
    add_prop(LIVE_I_NO_CORPSE, 1);   // No real body, no corpse.
    add_prop(LIVE_I_SEE_DARK, 100);  // Can see in dark.
    add_prop(OBJ_I_RES_POISON, 100); // No body, hardly susceptible to poison.
    add_prop(OBJ_I_RES_DEATH, 100);  // Already dead, death magic pointless.
    add_prop(OBJ_I_RES_MAGIC, 50);   // High natural resistance to all magic.
    add_prop(NPC_I_NO_RUN_AWAY, 1);  // Nothing will scare this thing off.
    add_prop(LIVE_I_NEVERKNOWN, 1);  // No players can ever know it's name.
    add_prop(NPC_I_NO_FEAR, 1);      // No dis check to attack.
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 300);
  
  /* Some custom movement messages.
    set_m_in("shimmers into view with a horrifying wail!");
    set_mm_in("fades from view with a horrifying wail!");
    set_m_out("glides out of the room to the");
    set_mm_out("glides into the room with a deafening shriek!");

  /* A bit of work on it's appearance. */
    set_race_name("human");
    set_size_descs("extremely tall", "lean");
    set_race_name("apparition");
    set_gender(G_FEMALE);
    set_appearance_offset(50);     // Make it nasty looking

}
