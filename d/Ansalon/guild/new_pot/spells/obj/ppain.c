/* 
 * ppain object - paralysing pain
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stun_obj";

#define PAIN_SUBLOC "pot_pain_subloc"

object  caster;
int     active, cooldown;

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name(PAIN_ID);
    add_name("_ppain_stun_object");
    set_short("hidden ppain spell stun object");    
    set_long("A ppain spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_tohit(90);
    set_stun_chance(90); 
    set_stun_stats( TS_WIS );
    set_stun_skills( SS_FORM_TRANSMUTATION );
}

public int
query_pot_active()
{
    return active;
}

public int
query_pot_cooldown()
{
    return cooldown;
}

public string
query_pot_stun() 
{
    return caster->query_real_name();
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 * Returns      : nothing
 */
public void
attack_blocked(object player)
{
    object enemy = player->query_attack();

    if (enemy)
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You are overwhelmed with excrutiating pain, and " +
              "are unable to attack " + QTNAME(enemy)+ ".\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but " +
              "is overwhelmed with excrutiating pain and cannot seem to move.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but "+
                "is overwhelmed with excrutiating pain and cannot seem to move.\n",
                ({ player, enemy }), player);
    } 
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none 
 * Returns:       nothing
 */
public void
remove_object()
{
    foreach (object shadowobj : query_shadow_list())
    {
        remove_stun_effect(shadowobj->query_shadow_who());
    }

    caster->catch_msg("You feel it safe to again beseech the wrath of the Dark Queen " +
        "and causing debilitating pain to your enemies.\n");

    ::remove_object();
}

void
pain_message(object spell_target)
{
    string *s;
    int tmp;

    switch(random(10))
    {
        case 0..2:
            s = ({ "You scream in pain!",
            QCTNAME(spell_target) + " screams in pain!" });
            break;
        case 3..4:
            s = ({ "You twitch uncontrollably as a new wave of pain " +
            "sears through your body.",
            QCTNAME(spell_target) + " twitches uncontrollably." });
            break;
        case 5..7:
            s = ({ "You moan pitifully.",
            QCTNAME(spell_target) + " moans pitifully." });
            break;
        default:
            s = ({ "The pain sears through your body.",
            "" });
    }

    if(active)
    {
       spell_target->catch_tell(s[0] + "\n");
       if (s[1] != "")
         tell_room(environment(spell_target), s[1] + "\n", spell_target);
    }

    set_alarm(5.0, 0.0, &pain_message(spell_target)); 

}

public void
hook_stun_cooldown_in_effect(object player)
{
    caster = query_effect_caster();

    caster->catch_msg("You do not dare call upon the Queen of Darkness " +
         "so soon after calling down her wrath!\n");
}

public void
hook_stun_ended(object player)
{
    active = 0;
    cooldown = 1;

    player->remove_subloc(PAIN_SUBLOC);

    if(player->query_ghost())
        return;

    player->catch_msg("The pain leaves you as suddenly as it appeared. " +
	"You stand up, feeling a bit unsteady for a short while.\n");
    caster->catch_msg(QCTNAME(player) + " stops screaming in pain and " +
        "slowly regains " +HIS(player) + " feet.\n");
    player->tell_watcher(QCTNAME(player) + " stops screaming in pain and " +
        "slowly regains " +HIS(player) + " feet.\n", ({ caster }), ({ caster }));

}

public void
hook_stun_begin(object attacker, object target)
{
    object horse;

    caster = attacker;
    active = 1;

    int cycle = query_stun_cycle_time(target);
    int c_aid = query_effect_combat_aid(target);

    // DEBUG("ppain cycle time: "+cycle+".");
    // DEBUG("ppain combat aid: "+c_aid+".");


    if (horse = target->query_prop(LIVE_O_STEED))
    {
        target->catch_tell("The pain makes your muscles cramp, and you " +
        "lose your seat on your horse, falling to the ground.\n");

        horse->do_dismount(target,1,1);

        tell_room(E(target),QCTNAME(target) + " falls off the " +
        horse->short() + ".\n", target);
        
    }
    else
    { 
        target->catch_msg("You collapse to the ground in agony.\n"); 
        target->tell_watcher(QCTNAME(target) + " collapses to the " +
            "ground in agony.\n", ({ }) );
    }

    target->add_subloc(PAIN_SUBLOC, TO);
    set_alarm(5.0, 0.0, &pain_message(target));

}

/*
public int
do_all_commands(string str)
{
    string *allowed;

    if (E(TO) != TP)
	return 0;

    if (TP->query_wiz_level())
	return 0;

    allowed = ({ "help","commune","reply",
	"bug","typo","idea","praise","sysbug",
	"stats", "health", "h", "vitals", "v",
	"look", "l","exa",
	"scream","moan","cry"});

    if (member_array(query_verb(), allowed) >= 0)
        return 0;
    write("You are in such terrible pain that it is impossible to do that.\n");
    return 1;
}

void init()
{
    ::init();
    if (active)
      add_action(do_all_commands, "", 1);
}

*/

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are curled up on the ground, screaming in terrible pain.\n";
    else
        return C(HE(me)) + " is curled up on the ground, screaming in pain.\n";
}
