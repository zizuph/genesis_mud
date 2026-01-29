/*
  Spell object for the fire mites spell for the Fire College.

  Coded by Bishop of Calia, July 2003.

 */

#pragma strict_types
 
inherit "/std/armour";
inherit "/d/Calia/guilds/colleges/specials/common_functions";
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

varargs public int dispel_spell_effect(object dispeller);

//In this spell, potency is an expression of how many fire mites
//there are. The fewer there are, the lower the chance of them 
//doing anything useful.
int potency;

void 
create_armour()
{
    set_name("college_fire_mites");
    set_short("college_fire_mites");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 

    set_ac(0);
    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (dest == spell_caster)
    {
        set_this_player(spell_caster);
        wear_me();
        set_this_player(this_player());
    }
}


void
check_mite_attack()
{
    int pen = 100 + random(100);
    int task = TASK_ROUTINE + 2*potency + 
        find_controlling_stat("fire", spell_caster);
    object target = spell_caster->query_attack();
    string desc;
    mixed hitresult;     
      
    if (environment(spell_caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        spell_caster->catch_tell("Your fire mites are unable to exist" +
            " in this place!\n");
        dispel_spell_effect();
        return;
    }      
      
    if (objectp(target))
    {
        if (target->resolve_task(task, ({TS_DEX, SKILL_WEIGHT, 70, SS_DEFENCE, 
        SKILL_WEIGHT, 30, SS_ACROBAT})) < 0)
        {
        
            pen -= target->query_magic_res(MAGIC_I_RES_FIRE) * pen/100;
            pen -= target->query_magic_res(MAGIC_I_RES_MAGIC) * pen/100;
            
            hitresult = target->hit_me(pen, MAGIC_DT, spell_caster, -1);
           
            switch(hitresult[3])
            {
                case 0:
                    desc = "unscathed.";
                    break;
                case 1..40:
                    desc = "lightly burnt";
                    break;
                case 41..80:
                    desc = "burnt";
                    break;
                case 81..140:
                    desc = "badly burnt";
                    break;
                default:
                    desc = "severely burnt";
            }
            
            target->catch_tell("A few of the fiery insects surrounding "
                + spell_caster->query_the_name(target) + " leave the" +
                " swarm, heading straight for you! They sting you," +
                " leaving you " + desc + ".\n");
            spell_caster->catch_tell("A few of the fiery insects surrounding "
                + "you leave the swarm, heading straight for " + 
                target->query_the_name(spell_caster) + "! They sting " +
                target->query_objective() + ", leaving " + 
                target->query_objective() +
                " " + desc + ".\n");
            spell_caster->tell_watcher("A few of the fiery insects surrounding"
                + " " + QTNAME(spell_caster) + " leave the swarm, heading" +
                " straight for " + QTNAME(target) + "! They sting " +
                target->query_objective() + ", leaving " + 
                target->query_objective() +
                " " + desc + ".\n", ({ target }));
                
            potency--;
        
            if (spell_caster->query_wiz_level())
            {
                spell_caster->catch_tell("Enemy was dealt " + hitresult[3]
                    + " hp.\n");
            }            
        }
    }
   
    if (potency < 30)
    {
        dispel_spell_effect();
    }
    else
    {
        set_alarm(itof(6 + random(6)), 0.0, &check_mite_attack()); 
    }
}
        


public int
start()
{
    int stat = find_controlling_stat("fire", spell_caster);

    potency = min(50 + random(stat) + random(stat), 250);
    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Spell potency is: " + potency + ".\n");
    }

    set_spell_effect_desc("fire_mites");
    
    spell_caster->catch_tell("As you finish your summoning ritual," +
        " a cloud of tiny points of light appears in front of you." +
        " Each point expands, becoming a small insectlike being" +
        " composed entirely out of fire. They swarm together and" +
        " surround you, shielding you.\n");
    tell_room(environment(spell_caster), "As " + QTNAME(spell_caster)
        + " finishes the ritual, a cloud of tiny points of light" +
        " appears in front of " + spell_caster->query_objective() +
        ". Each point expands, becoming a small insectlike being" +
        " composed entirely out of flame. They swarm together and" +
        " surround " + spell_caster->query_objective() + ".\n",
        spell_caster);    
    
            
    spell_caster->add_subloc("_college_fire_mites_", TO);
    
    set_alarm(5.0, 0.0, &check_mite_attack());

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The swarm of fire mites surrounding" +
        " you disperses.\n");
    tell_room(environment(spell_target),"The swarm of tiny,"+
        " fiery beings surrounding "+ QNAME(spell_target)+
        " disperses.\n", spell_target );

    remove_me();
    remove_spell_effect_object();

    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
    if (subloc != "_college_fire_mites_")
        return me->show_subloc(subloc, me, observer);

    if ((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || query_worn() != me))
            return "";

    return "A swarm of tiny, insectlike beings composed entirely"+
        " out of fire surrounds " + ( observer == me ? "you" :
        me->query_objective() ) + ".\n";
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 *                
 *                My redefinition of got_hit implements the damaging
 *                shield. For each hit that deals damage, the attacker
 *                has to succeed in a task, or get burned. The task is
 *                easier if you're wielding a two handed weapon, a bit 
 *                harder if you have a one-handed weapon and harder still
 *                if you're unarmed. 
 * 
 *
 *
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    mixed hitresult;
    object *weapons, wearer;
    string desc;
    int task;
    int pen;

    weapons = att->query_weapon(-1);
    wearer = spell_caster;
    pen = 100 + random(100);
    task = TASK_ROUTINE + 2*potency + 
        find_controlling_stat("fire", spell_caster);
        
    pen -= att->query_magic_res(MAGIC_I_RES_FIRE) * pen/100;
    pen -= att->query_magic_res(MAGIC_I_RES_MAGIC) * pen/100;

    if (!sizeof(weapons))
    {
        task += 200;
    }
    else
    if (weapons[0]->query_hands() != 2)
    {
       task += 100;
    }

    if (dam > 0 && att->resolve_task(task, ({TS_DEX, SKILL_WEIGHT, 70,
        SS_DEFENCE, SKILL_WEIGHT, 30, SS_ACROBAT})) < 0)
    {
        hitresult = att->hit_me(pen, MAGIC_DT, spell_caster, -1);
        
        switch(hitresult[3])
        {
            case 0:
                desc = "unscathed.";
                break;
            case 1..40:
                desc = "lightly burnt";
                break;
            case 41..80:
                desc = "burnt";
                break;
            case 81..140:
                desc = "badly burnt";
                break;
            default:
                desc = "severely burnt";
        }
        
        att->catch_tell("While landing your attack, you are" + 
            " stung by the swarm of fiery insects surrounding " +
            wearer->query_the_name(att) + "! You end up " + desc +
            ".\n");
        wearer->catch_tell("While landing " + att->query_possessive()
            + " attack, " + att->query_the_name(wearer) + " is stung" +
            " by the swarm of fire mites surrounding you! " + 
            capitalize(att->query_pronoun()) + " ends up " + desc + ".\n");
        wearer->tell_watcher("While landing " + att->query_possessive()
            + " attack, " + QTNAME(att) + " is stung by the swarm of" +
            " fiery insects surrounding " + QTNAME(wearer) + "! " +
            capitalize(att->query_pronoun()) + " ends up " + desc + ".\n", 
            ({att}));

        if (wearer->query_wiz_level())
        {
            wearer->catch_tell("Enemy was dealt " + hitresult[3] + " hp.\n");
        }

        if (att->query_hp() <= 0)
        {
            att->do_die(wearer);
        }
        
        potency--;
        
        if (potency < 30)
        {
            dispel_spell_effect();
        }
    }
    ::got_hit(hid, ph, att, dt, dam);
}

/*
 * called from the set_at - we want to be able to wear
 * the armour without printing messages
 */
public mixed
wear(object obj)
{
  return 1;
}

public mixed
remove(object obj)
{
  return 1;
}

int
query_recover()
{
    return 0;
}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

int 
set_condition(int i)
{
    i=0;
    ::set_condition(i);
}

varargs void
remove_broken(int silent = 0)
{
    return;
}