/*
 * rlattack.c
 *
 * This file contains all the code for the 'rlattack' special attacks
 * for the Riders of Last, and is included into their shadow.
 *
 * Construction and checks based off of the special attack code
 * used in the Khalakhor Blademaster guild.
 *
 * TAX:
 *     Preparation time: 10 sec.
 *     Recovery time   : 10 sec.
 *     Total time      : 20 sec -> 4 combat rounds per attack
 *   HIT CALCULATIONS
 *     cb_tohit        : The chance of a blademaster landing a battack
 *                       special attack is identical to his chances
 *                       of landing a normal attack with this weapon,
 *                       so no modifiers.      
 *   PEN CALCULATIONS
 *     wc_pen calc     : F_PENMOD(attack_pen, sword skill)
 *     attack_pen      : pen scaled so if the weapon's pen is above
 *                       50, only 1/2 the difference above 50 is
 *                       used. I.e., a weapon with a pen of 60 is
 *                       considered to have a pen of 55. Then this
 *                       value is multiplied by the guildstat as
 *                       a percent, up to 120%.
 *     Max pen         : F_PENMOD(88,100), assuming 100 sword skill,
 *                       100 guildstat, and weapon with a
 *                       pen of 40. Equals 582.
 *     Max pen normally: F_PENMOD(40, 100) (same as above, without the
 *                       guildstat modifier). Equals 280.
 *     Combat adv.     : 1/5 * 582/280 = 42%
 *     Tax             : 7% (1% for every 6% combat advantage, rounded up).
 *                       
 * Tomas - April 2000 
 *
 * Modifications / Bugfixes
 *
 * 
 */
#pragma strict_types


#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <formulas.h>

#define PREPARING_ATTACK       1
#define RECOVERING_FROM_ATTACK 2

#define PREPARATION_TIME       10.0
#define RECOVERY_TIME          10.0

#define FATIGUE_COST           7





int attack_state,
prepare_alarm_id,
last_attack_prepare;

private void launch_attack_1(object *weapons, object target);
private void resolve_attack(object target, int dt, mixed hl, mixed wep,
  int style, int form, mixed aid);

/*
 * Function name: enter_env (MASK)
 * Descripion   : Called whenever this object enters a new environment.
 *                Used here to 'spoil' preparations made if a player
 *                changes rooms.
 * Arguments    : to - Object pointer to new environment.
 *                from - Object pointer to last environment.
 * Returns      : n/a
 */
public void
enter_env(object to, object from)
{
    shadow_who->enter_env(to, from);

    if (get_alarm(prepare_alarm_id))
    {
        tell_object(shadow_who, "Your movement has prevented " +
          "completion of your attack!\n");
        remove_alarm(prepare_alarm_id);
        attack_state = 0;
    }
}

/*
 * Function name: recover_from_attack
 * Description  : Lets the player attack again.
 * Arguments    : n/a
 * Returns      : n/a
 */
private void
recover_from_attack()
{
    attack_state = 0;
    tell_object(shadow_who, "You feel ready to use your special " +
      "attack again.\n");
}

/*
 * Function name: select_attack
 * Description  : Decides which attack should be used.
 * Arguments    : style - Int from 1 to 3, which represents which
 *                       of the three styles to attack with.
 *                arr - An array of object pointers to the weapons
 *                      being used.
 * Returns      : An array:({
 *                    Array of object pointers to weapons used,
 *                    Form number as an int,
 *                    Array of attack id's for weapons used.})
 */
public mixed
select_attack(int style, object *weapons)
{
    int form,
    *aid;

    /* Attack style 1, which is a single one-handed weapon. */
    /* Possible forms are: */
    /*   1:  Viper Strikes From Den     */
    /*   2:  Heron Evades And Attacks   */
    /*   3:  Viper Strikes Low          */
    /*   4:  Heron Parts The Rushes     */
    if (style == 1)
    {
        if (sizeof(weapons) > 1)
            weapons = ({weapons[random(sizeof(weapons))]});
        form = random(4) + 1;
        aid = ({weapons[0]->query_attack_id()});
    }

    /* Attack style 2, which is two one-handed weapons. */
    /* Possible forms are: */
    /*   1:  Tiger Faces Dragon        */
    /*   2:  Dragon Strikes The Tiger  */       
    /*   3:  Tiger Flanks The Dragon   */
    /*   4:  Dragon Unleashes Fire     */
    if (style == 2)
    {
        form = random(4) + 1;
        aid = weapons->query_attack_id();
    }

    /* Attack style 3, which is one two-handed weapon. */
    /* Possible forms are: */
    /*   1:  Falling Of The Mountain   */
    /*   2:  Crack Of Lightning        */
    /*   3:  Wind Drives Stone         */
    /*   4:  Water Cuts Through Earth  */
    if (style == 3)
    {
        form = random(4) + 1;
        aid = weapons->query_attack_id();
    }

    /* Now we return the weapon(s) to use, which form of the */
    /* specified style to use, and the attack id's of the weapons */
    return ({weapons, form, aid});
}

/*
 * Function name: can_still_attack
 * Description  : Decides whether or not the player can continue 
 *                with the prepared attack. If not, it delivers
 *                appropriate fail messages and resets combat
 *                variables, currently, when an attack fails at
 *                this stage, the state var is simply set to 0, so
 *                the player can begin another attack right away.
 * Arguments    : weapons - Object array containing which weapons to use.
 *                target - Object pointer to the living to attack.
 *                style - Integers 1 to 3, representing the attack style.
 * Returns      : 1 - Attack cannot proceed.
 *                0 - Attack can proceed.
 */
private int
can_still_attack(object *weapons, object target, int style)
{
    /* Make sure the attacker isn't too fatigued to attack, */
    /* if he is, fail, if he's not, drain fatigue here. */
    if ((shadow_who->query_fatigue() - FATIGUE_COST) < 0)
    {
        tell_object(shadow_who, "You are too tired to use " +
          "your special attack!\n");
        attack_state = 0;
        return 1;
    }

    /* Make sure target is still in the room and is still fighting. */
    if (!present(target, environment(shadow_who)))
    {
        tell_object(shadow_who, "It appears your foe has " +
          "escaped before you could attack.\n");
        attack_state = 0;
        return 1;
    }

    /* Can't continue an attack while stunned! */
    if (shadow_who->query_prop(LIVE_I_ATTACK_DELAY) ||
      shadow_who->query_prop(LIVE_I_STUNNED))
    {
        tell_object(shadow_who, "You are too stunned to "+
          "finish your special attack.\n");
        attack_state = 0;
        return 1;
    }

    /* Can't attack a ghost. */
    if (target->query_ghost())
    {
        tell_object(shadow_who, "Your attack is " +
          "usless against a ghost!\n");
        attack_state = 0;
        return 1;
    }

    /* Can't start an attack with this, target must be an */
    /* active enemy. */
    if (member_array(target, shadow_who->query_enemy(-1)) < 0)
    {
        shadow_who->catch_msg("You are no longer fighting " +
          target->query_the_name(shadow_who) + ", and " +
          "halt your attack.\n");
        attack_state = 0;
        return 1;
    }

    /* Make sure all variables in the weapons array are valid */
    /* object pointers. */
    weapons = filter(weapons, objectp);

    /* Make sure all variables in the weapons array are being */
    /* wielded by this player. */
    weapons = filter(weapons, &operator(==)(shadow_who) @
      &->query_wielded());

    /* If the weapons that the player started the attack with are */
    /* no longer present (should be one weapon for attack forms */
    /* 1 and 3, and two weapons for attack form 2), it means they've */
    /* been somehow destructed, so fail. Also, by the second filter, */
    /* weapons no longer wielded by the player will not be considered. */
    if (!sizeof(weapons) || (sizeof(weapons) == 1 && style == 2))
    {
        tell_object(shadow_who, "It appears your sword is gone!\n");
        attack_state = 0;
        return 1;
    }

    shadow_who->add_fatigue(-FATIGUE_COST);

    return 0;
}

/* Function name: launch_attack_1
 * Description  : Executes an attack using a single one-handed sword.
 * Arguments    : weapons - Object array containing which weapons to use.
 *                target - Object pointer to the living to attack.
 * Returns      : n/a
 */
private void
launch_attack_1(object *weapons, object target)
{
    mixed my_attack;
    object wep,
    cob,
    *watchers,
    *masters;
    int form,
    aid,
    damage_type,
    hit_location;
    string s_he,
    s_him,
    s_his,
    t_he,
    t_him,
    t_his,
    mounted,
    attack_desc;

    /* First off, ensure the attack can proceed. If 'can_still_attack' */
    /* Returns an true value, the attack cannot proceed. Fail messages */
    /* and changes to combat status are performed in that function. */
    if (can_still_attack(weapons, target, 1))
        return;

    my_attack = select_attack(1, weapons);
    wep = my_attack[0][0];
    form = my_attack[1];
    aid = my_attack[2][0];

    cob = shadow_who->query_combat_object();

    watchers = all_inventory(environment(shadow_who)) - ({shadow_who,
      target});
    watchers = FILTER_PLAYERS(watchers);
    mounted = shadow_who->query_prop("_live_o_steed");      /* Check to see if we are mounted */ 
    watchers -= masters;

    s_his = shadow_who->query_possessive();
    s_he = shadow_who->query_pronoun();
    s_him = shadow_who->query_objective();
    t_his = target->query_possessive();
    t_he = target->query_pronoun();
    t_him = target->query_objective();

    attack_desc = shadow_who->query_weapon(aid)->short();
    switch (form) 
    {
    case 1: /* single handed,  single weapon:  W_SLASH, A_HEAD */
        if (interactive(target))
        {
            if (mounted)
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " suddenly swings "+ s_his +" steed " +
                  "to one side using the momentum to bring " +
                  s_his +" "+ attack_desc +" down in a " +
                  "deadly arc!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " dodges with "+ s_his +" "+ attack_desc +
                  " then swings wide attempting to strike " +
                  "your head!\n");

        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " forces "+ s_his +" steed to the side using " +
          "the momentum in "+ s_his +" swing as "+ s_he +
          " attempts to strike " + QTNAME(target) +
          " in the head!\n",target, ({shadow_who}) +
          watchers);

        target->tell_watcher(QCTNAME(shadow_who) +
          " feints with "+ s_his +" " + attack_desc + " " +
          "then swings wide attempting to strike" +
          " " + QTNAME(target) + " in the head!.\n", target,
          ({shadow_who}));

        damage_type = W_SLASH;
        hit_location = A_HEAD;            
        break;

    case 2: /* single handed, single sword: W_IMPALE, A_BODY */
        if (interactive(target))
        {
            if (mounted)
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " leans sideways atop the horse " +
                  "attempting to skewer you " +
                  " with "+ s_his +" "+ attack_desc +"!\n");  
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " suddenly, ducks under your defenses " +
                  "thrusting "+ s_his +" "+ attack_desc + " " +
                  "towards your mid-section!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " leans sideways atop the horse attempting to " +
          "skewer " + QTNAME(target) + " with "+ s_his + 
          " "+ attack_desc +"!\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " suddenly, ducks below " + QTNAME(target) +
          "'s defences thrusting  "+ s_his +" "+ attack_desc + 
          " towards " + QTNAME(target) +"'s " +
          "mid-section!\n",target, ({shadow_who}));
        damage_type = W_IMPALE;
        hit_location = A_BODY;           
        break;

    case 3: /* single handed, single sword: W_SLASH, A_BODY */
        if (interactive(target))
        {
            if (mounted)
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " rears "+ s_his +" steed forward " +
                  "as "+ s_he +" swipes at your chest with " +
                  s_his +" "+ attack_desc +"!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " swipes at your chest with " +
                  s_his +" "+ attack_desc +"!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " rears "+ s_his +" mount forward " +
          "as "+ s_he +" swipes at the chest of " + QTNAME(target) + 
          "!\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " ducks beneath " + QTNAME(target) + "'s " +
          "attack, then leaps forward, slashing at " +
          QTNAME(target) + "'s stomach with " + s_his +
          " " + attack_desc + "!\n",
          target, ({shadow_who}));
        damage_type = W_SLASH;
        hit_location = A_BODY;            
        break;
    default: /* single handed single sword: W_SLASH, A_BODY */
        if (interactive(target))
        {
            if (mounted)
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " pushes "+ s_his +" horse forward attempting " + 
                  "to strike you in the chest with"+ s_his +
                  " "+ attack_desc +"!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " deflects your attack with "+ s_his +
                  " "+ attack_desc + ", then " +
                  "slashes outward attempting to slice " +
                  "at your stomach!\n"); 
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " pushes "+ s_his +" horse forward slicing " +
          "at "+ QTNAME(target) +"'s stomach!\n",
          target, ({shadow_who}) + watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " deflects "+ QTNAME(target) +"'s attack with " +
          s_his +" "+ attack_desc + ", then " +
          "follows through attempting to slice " +
          "at their stomach!\n", 
          target, ({shadow_who}));
        damage_type = W_SLASH;
        hit_location = A_BODY;            
    }

    /* Now that we've made an attack message, generate the actual */
    /* attack with resolve_attack. */
    resolve_attack(target, damage_type, hit_location,
      wep, 1, form, aid);

}


/*
/* Function name: launch_attack_2
 * Description  : Executes an attack using two one-handed swords.
 * Arguments    : weapons - Object array containing which weapons to use.
 *                target - Object pointer to the living to attack.
 * Returns      : n/a
 */
private void
launch_attack_2(object *weapons, object target)
{
    mixed my_attack;
    object *wep,
    cob,
    *watchers,
    *masters;
    int form,
    *aid,
    damage_type,
    *hit_location;
    string s_he,
    s_him,
    s_his,
    t_he,
    t_him,
    t_his,
    attack_desc_1,
    attack_desc_2;

    /* First off, ensure the attack can proceed. If 'can_still_attack' */
    /* Returns an true value, the attack cannot proceed. Fail messages */
    /* and changes to combat status are performed in that function. */
    if (can_still_attack(weapons, target, 2))
        return;

    my_attack = select_attack(2, weapons);
    wep = my_attack[0];
    form = my_attack[1];
    aid = my_attack[2];

    cob = shadow_who->query_combat_object();

    watchers = all_inventory(environment(shadow_who)) - ({shadow_who,
      target});
    watchers = FILTER_PLAYERS(watchers);
    masters = filter(watchers, &->is_blademaster());
    watchers -= masters;

    s_his = shadow_who->query_possessive();
    s_he = shadow_who->query_pronoun();
    s_him = shadow_who->query_objective();
    t_his = target->query_possessive();
    t_he = target->query_pronoun();
    t_him = target->query_objective();

    attack_desc_1 = shadow_who->query_weapon(aid[0])->short();
    attack_desc_2 = shadow_who->query_weapon(aid[1])->short();

    switch (form) 
    {
    case 1: /* Tiger Faces Dragon */
        tell_object(shadow_who, 
          "You execute Tiger Faces Dragon at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Tiger Faces " +
                  "Dragon!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " crosses " + s_his + " arms across " +
                  s_his + " chest, with " + s_his + " " +
                  attack_desc_1 + " and " + attack_desc_2 +
                  " behind " + s_his + " back, then lunges " +
                  "forward at you, slashing high and low with " +
                  "the weapons!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Tiger Faces Dragon.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " crosses " + s_his + " arms across " +
          s_his + " chest, with " + s_his + " " +
          attack_desc_1 + " and " + attack_desc_2 +
          " behind " + s_his + " back, then lunges " +
          "forward at " + QTNAME(target) + 
      ", slashing high and low with " +
          "the weapons!\n",target,
          ({shadow_who}) + masters);
        damage_type = W_SLASH;
        hit_location = ({A_TORSO, A_LEGS});            
        break;

    case 2: /* Dragon Strikes The Tiger */
        tell_object(shadow_who, 
          "You execute Dragon Strikes The Tiger at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Dragon Strikes " +
                  "The Tiger!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " slips towards you, slashing across " +
                  "your legs with " + s_his + " " +
                  attack_desc_1 + " then, abruptly twirls " +
                  s_his + " " + attack_desc_2 + " high and " +
                  "brings it down across your chest!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Dragon Strikes The Tiger.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " slips towards " + QTNAME(target) + ", slashing " +
          "across " + t_his + " legs with " + s_his + " " +
          attack_desc_1 + " then, abruptly twirls " +
          s_his + " " + attack_desc_2 + " high and " +
          "brings it down across " + QTNAME(target) + "'s chest!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_IMPALE;
        hit_location = ({A_LEGS, A_TORSO});
        break;
    case 3: /* Tiger Flanks The Dragon */         
        tell_object(shadow_who, 
          "You execute Tiger Flanks The Dragon at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Tiger Flanks " +
                  "The Dragon!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " slashes at you with " + s_his + " " +
                  attack_desc_1 + " high, driving you " +
                  "back a step, then abruptly swings " +
                  "around the other way and thrusts " +
                  "into your side with " + s_his + " " +
                  attack_desc_2 + "!\n"); 
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Tiger Flanks The Dragon.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " slashes at " + QTNAME(target) + " with " + 
          s_his + " " + attack_desc_1 + " high, driving " +
          t_him + " back a step, then abruptly swings " +
          "around the other way, thrusting " + s_his + " " +
          attack_desc_2 + " into " + QTNAME(target) +
          "'s side!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_IMPALE;
        hit_location = ({A_LEGS, A_TORSO});
        break;

    default: /* Dragon Unleashes Fire */
        tell_object(shadow_who, 
          "You execute Dragon Unleashes Fire at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Dragon Unleashes " +
                  "Fire!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " charges at you, " + s_his + " " +
                  attack_desc_1 + " and " + attack_desc_2 +
                  " flashing in and out in inter-weaving " +
                  "figure eights, slashing at you from " +
                  "seemingly all directions!\n"); 
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Dragon Unleashes Fire.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " charges at " + QTNAME(target) + ", " + 
          s_his + " " + attack_desc_1 + " and " +
          attack_desc_2 + " flashing in and out in inter-" +
          "weaving figure eights, slashing at " +
          QTNAME(target) + " from seemingly all " +
          "directions!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_SLASH;
        hit_location = ({A_HEAD, A_TORSO});
    }

    /* Now that we've made an attack message, generate the actual */
    /* attack with resolve_attack. */
    resolve_attack(target, damage_type, hit_location,
      wep, 2, form, aid);
}

/* Function name: launch_attack_3
 * Description  : Executes an attack using a single two-handed sword.
 * Arguments    : weapons - Object array containing which weapons to use.
 *                target - Object pointer to the living to attack.
 * Returns      : n/a
 */
private void
launch_attack_3(object *weapons, object target)
{
    mixed my_attack;
    object wep,
    cob,
    *watchers,
    *masters;
    int form,
    aid,
    damage_type,
    hit_location;
    string s_he,
    s_him,
    s_his,
    t_he,
    t_him,
    t_his,
    attack_desc;

    /* First off, ensure the attack can proceed. If 'can_still_attack' */
    /* Returns an true value, the attack cannot proceed. Fail messages */
    /* and changes to combat status are performed in that function. */
    if (can_still_attack(weapons, target, 3))
        return;

    my_attack = select_attack(3, weapons);
    wep = my_attack[0][0];
    form = my_attack[1];
    aid = my_attack[2][0];

    cob = shadow_who->query_combat_object();

    watchers = all_inventory(environment(shadow_who)) - ({shadow_who,
      target});
    watchers = FILTER_PLAYERS(watchers);
    masters = filter(watchers, &->is_blademaster());
    watchers -= masters;

    s_his = shadow_who->query_possessive();
    s_he = shadow_who->query_pronoun();
    s_him = shadow_who->query_objective();
    t_his = target->query_possessive();
    t_he = target->query_pronoun();
    t_him = target->query_objective();

    attack_desc = shadow_who->query_weapon(aid)->short();
    switch (form) 
    {
    case 1: /* Falling Of The Mountain */
        tell_object(shadow_who, 
          "You execute Falling Of The Mountain at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Falling Of The " +
                  "Mountain!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " begins a brutal series of hacks " +
                  "at you with " + s_his + " " +
                  attack_desc + ", then suddenly " +
                  "reverses the blade and thrusts at " +
                  "your chest!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Falling Of The Mountain.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " begins a brutal series of hacks " +
          "at " + QTNAME(target) + " with " + s_his + " " +
          attack_desc + ", then suddenly " +
          "reverses the blade and thrusts at " +
          QTNAME(target) + "'s chest!\n",target,
          ({shadow_who}) + masters);
        damage_type = W_IMPALE;
        hit_location = A_TORSO;            
        break;
    case 2: /* Crack Of Lightning */
        tell_object(shadow_who, 
          "You execute Crack Of Lightning at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Crack Of " +
                  "Lightning!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " breaks into a forward roll beneath " +
                  "your attacks, and thrusts " + s_his +
                  " " + attack_desc + " upwards into " +
                  "your chest!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Crack Of Lightning.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " breaks into a forward roll beneath " +
          QTNAME(target) + "'s attacks, and thrusts " + 
          s_his + " " + attack_desc + " upwards into " +
          t_his + " chest!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_IMPALE;
        hit_location = A_BODY;           
        break;
    case 3: /* Wind Drives Stone */
        tell_object(shadow_who, 
          "You execute Wind Drives Stone at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Wind Drives " +
                  "Stone!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " rolls forward beneath your attack, " +
                  "and allows " + s_his + " weight to " +
                  "carry " + s_him + " to one side of " +
                  "you, slashing at your chest brutally " +
                  "with " + s_his + " " + attack_desc +
                  " on the way!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Wind Drives Stone.\n", target, ({shadow_who}) +
          watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " rolls forward beneath " + QTNAME(target) +
          "'s attack, and allows " + s_his + " weight " +
          "to carry " + s_him + " to one side of " +
          QTNAME(target) + ", slashing at " + t_his +
          " chest with " + s_his + " " + attack_desc +
          " on the way!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_SLASH;
        hit_location = A_TORSO;            
        break;
    default: /* Water Cuts Through Earth */
        tell_object(shadow_who, 
          "You execute Water Cuts Through Earth at " + 
          target->query_the_name(shadow_who) + "!\n");
        if (interactive(target))
        {
            if (target->is_blademaster())
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " strikes at you with Water Cuts " +
                  "Through Earth!\n");
            else
                tell_object(target,
                  shadow_who->query_The_name(target) +
                  " calmly begins beating away all " +
                  "your attempts at attack, until " +
                  "suddenly you realize " + s_he + "'s " +
                  "created an opening in your defense, " +
                  "through which " + s_he + " thrusts savagely " +
                  "at your chest with " + s_his + 
                  " " + attack_desc + "!\n");
        }
        target->tell_watcher(QCTNAME(shadow_who) +
          " strikes at " + QTNAME(target) + " with " +
          "Water Cuts Through Earth.\n",
          target, ({shadow_who}) + watchers);
        target->tell_watcher(QCTNAME(shadow_who) +
          " calmly begins beating away all " +
          QTNAME(target) + "'s attempts at attack, until " +
          "suddenly you realize " + s_he + "'s " +
          "created an opening in " + t_his + " defense, " +
          "through which " + s_he + " thrusts savagely " +
          "at " + QTNAME(target) + "'s chest with " + s_his + 
          " " + attack_desc + "!\n",
          target, ({shadow_who}) + masters);
        damage_type = W_IMPALE;
        hit_location = A_TORSO;            
    }

    /* Now that we've made an attack message, generate the actual */
    /* attack with resolve_attack. */
    resolve_attack(target, damage_type, hit_location,
      wep, 3, form, aid);
}



*/



/*
 * Function name: resolve_attack
 * Description  : Delivers the damage dealt by an attack.
 * Arguments    : target - Object pointer the living to attack.
 *                dt - Damage type (W_SLASH or W_IMPALE)
 *                hl - Hit location (W_HEAD, W_TORSO, etc.)
 *                wep - Object pointer to the weapon(s) used.
 *                style - Which style the attack is based on.
 *                form - Which form the attack is based on.
 *                aid - Attack id(s) of the attack.
 * Returns      : n/a
 */
private void
resolve_attack(object target, int dt, mixed hl, mixed wep, int style,
  int form, mixed aid)
{
    object cob;
    int attack_hit,
    attack_pen,
    skill,
    guildstat;
    mixed attarr,
    hitresult;
    string s_he,
    hit_mesg;

    /* First we have to see what we got for 'wep' and 'aid' vars, */
    /* in case of a double-weapon attack, we'll use the weapon */
    /* with the best pen for damage. */
    if (style == 2)
    {
        if (wep[0]->query_pen() > wep[1]->query_pen())
        {
            hl = (int)hl[0];
            aid = (int)aid[0];
        }
        else
        {
            hl = (int)hl[1];
            aid = (int)aid[1];
        }
    }

    skill = shadow_who->query_skill(SS_WEP_SWORD);

    cob = shadow_who->query_combat_object();

    attarr = cob->query_attack(aid);
    attack_hit = attarr[0];
    attack_pen = attarr[1][member_array(dt,
        ({W_IMPALE, W_SLASH, W_BLUDGEON}))];

    /* If the pen is > 50, reduce it by 1/2 the amount over */
    /* 50 to keep things sane with magic weapons. */  
    if (attack_pen > 50)
        attack_pen = 50 + ((attack_pen - 50) / 2);

    /* Increase pen by guild stat as a %, up to a max. of 120% */
    guildstat = shadow_who->query_base_stat(SS_LAYMAN);
    guildstat = (guildstat > 120 ? 120 : guildstat);
    attack_pen += ftoi(itof(attack_pen) * itof(guildstat) / 100.0);
    attack_pen = F_PENMOD(attack_pen, skill);

    s_he = shadow_who->query_pronoun();

    /* First see if our attack can actually hit the target. */  
    if (cob->cb_tohit(aid, attack_hit, target) < 0)
    {
        tell_object(shadow_who,
          target->query_The_name(shadow_who) + " avoids your " +
          "blow, and you miss by a mile!\n");
        tell_object(target, 
          "You avoid " + shadow_who->query_the_name(target) + 
          "'s blow, and " + s_he + " misses by a mile!\n");
        target->tell_watcher(QCTNAME(target) + " avoids " +
          QTNAME(shadow_who) + "'s blow, and " + s_he + 
          " misses by a mile!\n", target, ({shadow_who}));
        attack_state = RECOVERING_FROM_ATTACK;
        set_alarm(RECOVERY_TIME, 0.0, recover_from_attack);
        return;
    }

    /* Ok, we seem to be able to hit, now lets see how well we */
    /* hit, and deliver appropriate messages. */
    hitresult = target->hit_me(attack_pen, dt, shadow_who, aid, hl);

    /* hitresult[0] is the percentage of damage done / total health */
    /* remaining, i.e. when hitresult[0] == 10, we've just taken */
    /* away 10% of the target's remaining hp. */  
    if (hitresult[0] == 0)
        hit_mesg = "barely scratches";
    else if (hitresult[0] < 10)
        hit_mesg = "lightly wounds";
    else if (hitresult[0] < 25)
        hit_mesg = "mildly cuts";
    else if (hitresult[0] < 40)
        hit_mesg = "roughly cuts";
    else if (hitresult[0] < 55)
        hit_mesg = "badly slashes";
    else if (hitresult[0] < 70)
        hit_mesg = "horribly slices";
    else if (hitresult[0] < 85)
        hit_mesg = "viciously mauls";
    else if (hitresult[0] < 99)
        hit_mesg = "near-fatally wounds";
    else
        hit_mesg = "fatally wounds";

    tell_object(shadow_who, "Your attack " + hit_mesg + " " +
      target->query_the_name(shadow_who) + "!\n");
    if (interactive(target))
        tell_object(target, shadow_who->query_The_name(target) +
          "'s attack " + hit_mesg + " you!\n");
    target->tell_watcher(QCTNAME(shadow_who) + "'s attack " +
      hit_mesg + " " + QTNAME(target) + "!\n", target, ({shadow_who}));

    /* Have we taken _all_ of the target's hp? If we have... */
    /* BURN THE WITCH!!! BURN HER!!! */
    if (target->query_hp() < 1)
    {
        tell_object(shadow_who,target->query_The_name(shadow_who) +
          " stares in stunned silence at the fatal wound left " +
          "by the flash of your blade.\n");
        target->tell_watcher(QCTNAME(target) + " stares in " +
          "stunned silence at the fatal wound left by the " +
          "flash of " + QTNAME(shadow_who) + "'s blade.\n",
          target, ({shadow_who}));
        if (interactive(target))
            target->catch_tell("You stare in stunned silence " +
              "at the fatal wound left by the flash of " +
              shadow_who->query_the_name(target) + "'s blade.\n");
    }

    /* Ok, all messages away, damage is done, death is dealt, if */
    /* necessary, set the player's attack state to recovering, and */
    /* start up the recovery alarm. */
    attack_state = RECOVERING_FROM_ATTACK;
    set_alarm(RECOVERY_TIME, 0.0, &recover_from_attack());
    return;
}

/*
 * Function name: bm_get_style
 * Description  : Returns the most appropriate style for the player
 *                to be using, based on weapons wielded, skills, and
 *                stats.
 * Arguments    : n/a
 * Returns      : 1 - 4 are fail flags.
 *                    1 - No swords wielded.
 *                    2 - Two one-handers wielded, but not enough skill
 *                        in two-handed combat to use them, and not 
 *                        dex for single one-handed sword forms.
 *                    3 - Single two-hander wielded, but not enough
 *                        strength for those forms.
 *                    4 - Single one-handed sword wielded, not enough
 *                        dexterity for those forms.
 *                On success, an array: ({style number, ({weapons wielded})})
 */
public mixed
bm_get_style()
{
    mixed form;
    object *obarr;

    /* Find any swords the player might be wielding. Note that */
    /* blademasters attacks work _only_ with swords. */
    obarr = filter(shadow_who->query_weapon(-1),
      &operator(==)(W_SWORD) @ &->query_wt());

    /* Fail if the player has no swords wielded. */
    if (!sizeof(obarr))
        return 1;

    /* Figure out which form is appropriate (a single 1-handed sword, */
    /* two 1-handed swords, or one 2-handed sword), and fail if the */
    /* player doesn't have the min form requirements. */

    /* If the player has two one-handed swords. */
    if (sizeof(obarr) == 2)
    {
        /* First we'll check for two-handed skill. */
        if (shadow_who->query_skill(SS_2H_COMBAT) >= FORM_2H_MIN)
            form = ({2, obarr[0], obarr[1]});
        /* Insufficient 2-handed skill, so we'll make a dex */
        /* check to use a single-weapon form. */
        else if (shadow_who->query_stat(SS_DEX) >= FORM_DEX_MIN)
            form = ({1, obarr[0], obarr[1]});
        /* Player can't use any forms of one-handed weapons, so fail. */
        else
            return 2;
    }
    /* Ok, player's only wielding one sword, lets see if it's one or */
    /* two handed, and if he's skilled enough to use the relevant */
    /* forms. First check for two-handed.*/
    else if (obarr[0]->query_hands() == W_BOTH)
    {
        if (shadow_who->query_stat(SS_STR) >= FORM_STR_MIN)
            form = ({3, obarr[0]});
        else
            return 3;
    }
    /* Ok, the weapon must be a one-hander. */
    else
    {
        if (shadow_who->query_stat(SS_DEX) >= FORM_DEX_MIN)
            form = ({1, obarr[0]});
        else
            return 4;
    }
    return form;
}

/*
 * Function name: do_battack
 * Description  : Allows the blademaster to attempt to execute a special
 *                attack. The blademaster has no control over which
 *                attack he/she uses, it is selected based on the combat
 *                situation, and random if more than on possible attack
 *                exists.
 * Arguments    : str - Extra args to the battack command.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_battack(string str)
{
    object *obarr,
    wep,
    target;
    mixed  temp,
    tararr,
    form;

    if (!str)
        str = "";

    /* Can't launch a new attack if already preparing for one. */
    if (attack_state == PREPARING_ATTACK)
    {
        /* Safety Check to see if the attacks are locked */
        if (time() > last_attack_prepare + 2 * ftoi(PREPARATION_TIME) +
          ftoi(RECOVERY_TIME))
        {
            attack_state = 0;
        }
        else
        {
            NF("You are already preparing to attack.\n");
            return 0;
        }
    }

    /* Can't launch a new attack if recovering from one. */
    if (attack_state == RECOVERING_FROM_ATTACK)
    {
        /* Safety check to see if the attack is locked up */
        if (time() > last_attack_prepare + 2 * ftoi(PREPARATION_TIME) +
          ftoi(RECOVERY_TIME))
        {
            attack_state = 0;
        }
        else
        {
            NF("It's been too soon since your last attack.\n");
            return 0;
        }
    }   

    if (intp(temp = bm_get_style()))
    {
        if (temp == 1)
            NF("You have no swords to attack with!\n");
        else if (temp == 2)
            NF("You have neither the skill to attack with the "+
              "two one-handed sword forms, nor the dexterity " +
              "to attack with the single one-handed sword forms!\n");
        else if (temp == 3)
            NF("You do not have the strength to attack with " +
              "the two-handed weapon forms!\n");
        else
            NF("You do not have the dexterity to attack with " +
              "the single one-handed weapon forms!\n");
        return 0;
    }
    else
        form = temp;

    /* Now we should have the which of the three forms to use. */

    /* Try to identify the desired target. */
    if (parse_command(str, all_inventory(environment(shadow_who)),
        "[the] %l", tararr))
    {
        if (!sizeof(tararr))
        {
            NF("Attack who?\n");
            return 0;
        }
        if (tararr[0] == 0 && sizeof(tararr) > 2)
        {
            NF("You can only attack one thing at a time.\n");
            return 0;
        }
        if (tararr[0] > 1)
        {
            NF("You can only attack one thing at a time.\n");
            return 0;
        }
        if (tararr[0] == 1)
        {
            target = tararr[1];
        }
        else if (tararr[0] < 0)
        {
          if ((tararr[0] = -tararr[0]) >= sizeof(tararr)) {
              NF("Attack who?\n"); 
              return 0; 
          } 
            target = tararr[tararr[0]];
        }
    }
    else
    {
        target = shadow_who->query_attack();
    }

    if (!target)
    {
        NF("Attack who?\n");
        return 0;
    }

    /* Ok, we've found a target, now see if we can battack. */
    /* Because of the pain in the butt associated with legally */
    /* initiating an attack, players can't start fights with */
    /* battack, so if the target isn't in the enemies list, */
    /* fail. */
    if (member_array(target, shadow_who->query_enemy(-1)) < 0)
    {
        NF("You can only use battack on opponents you are " +
          "already in combat with.\n");
        return 0;
    }

    /* Fail if the player's in a no_attack room. */
    if (temp = environment(shadow_who)->query_prop(ROOM_M_NO_ATTACK) )
    { 
        if (stringp(temp))
        {
            notify_fail(temp);
            return 0;
        }
        else 
        {
            notify_fail("A magical force prevents you from attacking.\n");
            return 0;
        }
    }

    /* Fail if stunned or delayed. */
    if (shadow_who->query_prop(LIVE_I_STUNNED) ||
      shadow_who->query_prop(LIVE_I_ATTACK_DELAY))
    {
        NF("You've been stunned, and cannot gather your concentration " +
          "to the degree needed to attack!\n");
        return 0;
    }

    /* Ok, we've got a form, a target, and verified the attack can */
    /* proceed, now start the prep time, and call the appropriate */
    /* attack function. */
    attack_state = PREPARING_ATTACK;
    last_attack_prepare = time();
    if (form[0] == 1)
        prepare_alarm_id = set_alarm(PREPARATION_TIME, 0.0,
          &launch_attack_1(form[1..], target));
    else if (form[0] == 2)
        prepare_alarm_id = set_alarm(PREPARATION_TIME, 0.0,
          &launch_attack_2(form[1..], target));
    else if (form[0] == 3)
        prepare_alarm_id = set_alarm(PREPARATION_TIME, 0.0,
          &launch_attack_3(form[1..], target));

    tell_object(shadow_who, "You begin preparations to use a " +
      "special attack form.\n");
    return 1;
}

