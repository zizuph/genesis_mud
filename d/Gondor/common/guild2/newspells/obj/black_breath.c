/*
 * copied from /d/Gondor/common/poison/black_breath.c to
 *             /d/Gondor/common/guild2/poisons/black_breath.c
 * to be used a poison for the morthul spell of the Morgul Mages
 * Olorin, 15-jul-1994
 *
 *
 * Modification started 2006-10-24 by Toby to add functionality to
 * support the shadow orb that will reveal the state of the posion
 * to the owner of the orb.
 *
 * Orb can be found in the same directory; shadow_orb.c
 *
 * 
 * Implementing October 26, 2006 by Toby, Ok by Gorboth (GM)
 *
 *    Balanced the time as pointed out from AoP, Nov 22, 2006 by Toby
 *
 *           Members with descent guildstat should get a result of
 *              20-30 min fairly regularly (min 15 min).
 *           Last 10 minutes is random to make it less guild stat 
 *              dependant.
 *
 *           Damage balance: Also hit the roof before, new formula:
 *                max(90, (5 * x / 3 - 10 + random(20)) )
 *                old formula: (5 * x / 3) 
 *
 *                Damage range now: 90-120 (with a random 20)
 *                (The roof before was almost always hit at 116, NPC 128)
 *
 *                The extra 4 should not be a biggie, but then IF they get
 *                full random, that is in rare cases some compensation for
 *                halved time. =o)
 * 
 */
#pragma strict_types

#include <poison_types.h>
#include <ss_types.h>
#include <macros.h>
#include "../spells.h"
#include "morgul_corpse.h"

inherit SPELL_OBJECT;
inherit "/std/poison_effect";

/*                                     duration = 900 - 1800sec      */
#define F_MORTHUL_DURATION(x)         (max(900, ( (x / 4) * 100 + 75) - random(600) ) )
#define F_MORTHUL_STRENGTH(x)         (max(90, ( (5 * x / 3) - 10 + random(20) ) ))
#define NAME(x)   (x->query_npc() ? file_name(x) : x->query_cap_name())


object shadow_orb;
void   create_orb();


void  create_poison_effect()
{
    ::create_poison_effect();
    set_name( "Black breath" );
    set_interval( 20 );
    set_time( 1800 );
    set_damage( ({ POISON_HP, 250, POISON_MANA, 100,
        POISON_FATIGUE, 25, POISON_STAT, SS_CON, }) );
    set_strength( 100 );
    set_poison_type( "black_breath" );
}

void create_orb()
{
    string str = one_of_list( ({"Dark Power", "rush of the Dark Lords power", 
                                "Dark Lords power", "Black Master's power",
                                "powers of the Dark Lord", }) );

    // Does the victim have an orb bound now?

    if(spell_caster->query_npc())
        return;

    shadow_orb = spell_target->query_prop(MORGUL_S_MORTHUL_TGT);
    if(!shadow_orb || shadow_orb->query_prop(OBJ_I_BROKEN))
    {
       setuid();
       seteuid(getuid());

       shadow_orb = clone_object(MORGUL_O_MORTHUL_ORB);
       shadow_orb->set_victim(spell_target);
       shadow_orb->set_mage(spell_caster);
       spell_target->add_prop(MORGUL_S_MORTHUL_TGT, shadow_orb);
    }

    /* Set the state on the orb to active posion!
     * 
     * States: 1 poisoned, 2 dead, 3 survived */
    shadow_orb->update_victim_state(1);
    shadow_orb->move(spell_caster);
    spell_caster->catch_msg("As the " +str+ " leaves your body " +
       "moving into your victim a tendril of it forms an orb which "+
       "you quickly snatch and store within the folds of your robe.\n");
    tell_room(environment(spell_caster), QCTNAME(spell_caster) +
       " makes a quick gesture with " +spell_caster->query_possessive()+
       " hand in the air as if catching something, then reaches inside " +
       "the folds of " +spell_caster->query_possessive()+ " robe.\n", spell_caster);

    return;
}

public int setup_spell_effect()
{
    set_spell_effect_desc( "black breath" );

    if (!::setup_spell_effect())
    {
        return 0;
    }
    move( spell_target, 1 );
    set_time( F_MORTHUL_DURATION( spell_power ) );
    set_strength( F_MORTHUL_STRENGTH( spell_power ) );
    if (!(spell_target->query_npc()))
    {
        SPELL_INHERIT->log_spell( "morthul", "Caster: ("+
            NAME( spell_caster )+ ") Target: ("+
            spell_target->query_cap_name()+ ")  Poison Strength: ("+
            F_MORTHUL_STRENGTH( spell_power )+ ")  Duration: ("+
            F_MORTHUL_DURATION( spell_power )+ ")" );
    }
    start_poison( spell_target );

    /* This must be last, otherwise the poison is disabled.
     * When the cloning works, add a check as above?:
     * if (!(spell_target->query_npc())) Checked inside the create_orb() /Toby
     */
    create_orb();
}

varargs public int dispel_spell_effect( object dispeller )
{
    if (objectp( dispeller ))
    {
        dispeller->catch_tell( "The poison flowing in "+
            spell_target->query_the_possive_name()+ " blood seems to "+
            "have been dispelled.\n");
    }

    timeout();
    remove_spell_effect_object();
    return 1;
}



/*
 * Function name: timeout
 * Description  : This is called when the poison duration has expired.
 *                It simply removes itself.
 */
public void timeout()
{
    /* States: 1 poisoned, 2 dead, 3 survived */
    (spell_target->query_prop(MORGUL_S_MORTHUL_TGT))->update_victim_state(3);

    ::timeout();
}

/*
 * Function name: kill_player
 * Description  : The player has died, so we kill him! 8-)
 */
public void kill_player()
{
    object corpse_sh;

    /* States: 1 poisoned, 2 dead, 3 survived */
    (spell_target->query_prop(MORGUL_S_MORTHUL_TGT))->update_victim_state(2);
    (spell_target->query_prop(MORGUL_S_MORTHUL_TGT))->add_prop(OBJ_I_BROKEN, 1);

    if (a_time)
    {
        remove_alarm( a_time );
    }
    a_time = 0;

    poisonee->catch_tell( "Suddenly you feel much better.\nBetter then "+
        "ever before!\nThat's probably because you are dead now.\n" );
    tell_room(environment(poisonee), QCTNAME(poisonee) + " draws a last rasping " +
        "breath and falls to the ground, utterly still.\n", poisonee);

    setuid();
    seteuid(getuid());
    corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
    corpse_sh->shadow_me( poisonee );
    corpse_sh->set_death_cause( MORTHUL_CS );
    corpse_sh->set_death_variant( random( MORTHUL_VR ) );
    poisonee->do_die( this_object() );
    corpse_sh->remove_shadow();
    
    remove_object();
}
