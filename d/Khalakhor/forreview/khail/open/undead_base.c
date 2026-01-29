#pragma strict_type

#include "defs.h"
#include <composite.h>

inherit "/std/monster";

int type,
    strength_block,
    dexterity_block,
    min_wcpen_tohit,
    always_block;

/*
 * Function name: try_to_block
 * Description  : Gives this npc a chance to prevent a player
 *                from using an exit, based on several factors.
 * Arguments    : who - Object pointer to the player to try and
 *                      block.
 * Returns      : 0 - Npc couldn't block player.
 *                1 - Npc blocked player.
 */
public int
try_to_block(object who)
{
  /* Can't block something that doesn't exist or isn't in */
  /* this room. */
    if (!who || environment(who) != environment())
        return 0;

  /* Sometimes, we always want the npc to block. */
    if (always_block)
    {
        tell_object(who, TO->query_The_name(who) + 
            " refuses to let you pass!\n");
        return 1;
    }

  /* Can't block something we can't see. */
    if (!CAN_SEE(TO, who) || !CAN_SEE_IN_ROOM(TO))
    {
        tell_object(who, TO->query_The_name(who) +
            " doesn't seem to notice you as you slip past.\n");
        return 0;
    }

  /* Can't block if we're stunned. */
    if (TO->query_prop(LIVE_I_STUNNED))
    {
        tell_object(who, TO->query_The_name(who) +
            " doesn't seem too happy about letting you " +
            "past, but is in no condition to stop you.\n");
        return 0;
    }

  /* Can't block a ghost. */
    if (who->query_ghost())
    {
        tell_object(who, TO->query_The_name(who) +
            " moves to block you, but in your " +
            "incorporeal state, it has no " +
            "way of blocking your path.\n");
        return 0;
    }

  /* _Really_ strong players might be able to force their way */
  /* past. Absolutely no chance of anyone with less than 200 */
  /* str making it. */
    if (random(who->query_stat(SS_STR)) > 
        strength_block + random(query_stat(SS_STR)))
    {
        tell_object(who, TO->query_The_name(who) + 
            " tries to stop you, but you force your " +
            "way past it.\n");
        return 0;
    }

  /* Same holds for really dextrous players. */
    if (random(who->query_stat(SS_DEX)) >
        dexterity_block + random(query_stat(SS_DEX)))
    {
        tell_object(who, TO->query_The_name(who) + 
            " tries to stop you, but you deftly slip " +
            "past it.\n");
        return 0;
    }

    tell_object(who, TO->query_The_name(who) +
        " blocks your way!\n");
    tell_room(environment(who), QCTNAME(who) + " attempts " +
        "to leave, but " + QTNAME(TO) + " blocks " +
        who->query_possessive() + " way!\n", ({who}));
    return 1;
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object *temp;
    int i;

#ifdef UNDEAD_DEBUG
    tell_object(attacker, "WCPEN = " + wcpen + "\n");
#endif

    if (wcpen > min_wcpen_tohit || dt == MAGIC_DT)
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
create_undead_monster(int undead_type)
{
    switch(undead_type)
    {
        case UNDEAD_LORD:
            default_config_npc(90);
            set_skill(SS_WEP_AXE, 90);
            set_skill(SS_PARRY, 80);
            set_skill(SS_DEFENSE, 90);
            set_skill(SS_AWARENESS, 100);
            set_skill(SS_BLIND_COMBAT, 100);
            strength_block = 200;
            dexterity_block = 200;
            min_wcpen_tohit = 200;
            break;
        case UNDEAD_KNIGHT:
            default_config_npc(70);
            set_skill(SS_WEP_SWORD, 70);
            set_skill(SS_PARRY, 60); 
            set_skill(SS_DEFENSE, 70);
            set_skill(SS_AWARENESS, 90);
            set_skill(SS_BLIND_COMBAT, 70);
            strength_block = 150;
            dexterity_block = 150;
            min_wcpen_tohit = 150;
            break;
        default:
            default_config_npc(45);   
            set_skill(SS_WEP_SWORD, 50);
            set_skill(SS_PARRY, 40);
            set_skill(SS_DEFENSE, 50);
            set_skill(SS_AWARENESS, 70);
            set_skill(SS_BLIND_COMBAT, 70);
            undead_type = UNDEAD_WARRIOR;
            strength_block = 100;
            dexterity_block = 100;
            min_wcpen_tohit = 100;
            break;
    }
    type = undead_type;
    set_aggressive(1);
    set_m_in("rages into view from the depths of shadows!");
    set_mm_in("rages into view from the depths of the shadows!");
    set_m_out("vanishes into the shadows to the");
    set_mm_out("vanishes into the shadows around you.");
    set_gender(G_NEUTER);
    set_appearance_offset(50);     // Make it nasty looking
    add_prop(LIVE_I_UNDEAD, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_HEIGHT, 300);

}
