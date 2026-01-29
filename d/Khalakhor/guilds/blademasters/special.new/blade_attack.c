/*
 * blade_attack.c
 *
 * This file contains all the code for the 'battack' special attacks
 * for the Blademasters, and is included into their shadow.
 *
 * Construction and checks based off of the special attack code
 * used in the Calian Cadet's guild by Maniac.
 *
 * TAX:
 *     Preparation time: 10 sec.
 *     Recovery time   : 15 sec.
 *     Total time      : 25 sec -> 5 combat rounds per attack
 *   HIT CALCULATIONS
 *     cb_tohit        : The chance of a blademaster landing a battack
 *                       special attack is identical to his chances
 *                       of landing a normal attack with this weapon,
 *                       so no modifiers. (changed - see Feb 2002
 *                       modification)
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
 * Khail - April 3/97
 *
 * Modifications / Bugfixes
 *
 * re-added the lost decapitation code, god bless cut n' paste!
 * Igneous - July 8th 1998
 *
 * Got rid of runtime error with ordinals of targets
 * Maniac - 14/3/99
 *
 * wchit value now increased by guildstat as a %, capped at 100%
 * wchit also capped at 90.
 * Teth - 10/02/02
 *
 * Made decapitation optional.
 * Cotillion - 2005-07-15
 *
 * Converted to new Genesis specials system
 * Petros - 2008-08-26
 *
 * Added check for lack of skill as a failure condition to
 * support a blademaster staying in the guild even though their
 * skill is lower than required.
 * Petros - 2009-07-10
 
 */
#pragma strict_types

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "defs.h"

inherit "/d/Khalakhor/guilds/blademasters/special.new/blade_utility";
inherit DAMAGE_LIB;
inherit KLOGGER;

#include DEBUGGER_LIB

#define FATIGUE_COST           3
#define BATTACK_LOG            (SPECIAL + "battack-damage.log")

// Prototypes

// The following functions are masks of the underlying specials library
void             config_ability();
void             special_did_hit(int aid, string hdesc, int hid, 
                                 int phurt, object enemy, int dt, 
                                 int phit, int dam, mixed * items,
                                 int result);
int              query_tohit();
static int       check_valid_action(object player, mixed * targets, 
                                    string arg, int execute);
void             apply_costs_to_player(object player);
int              force_fail(object player, mixed * items, 
                            object enemy, int resist, int result);
void             hook_special_complete();
void             hook_targets_gone(object * targets);
static void      ability_msg(object actor, mixed * targets,
                             string arg);
static mixed *   check_required_items(object actor, mixed * targets,
                                      string arg, int pretest);                                   
// End list of masked functions for specials library
                                   
private void launch_attack_1 (object *weapons, object target);
private void launch_attack_2 (object *weapons, object target);
private void launch_attack_3 (object *weapons, object target);
// Global Variables

mixed *bm_styles_and_forms = ({
  ({
    ({ "Viper Strikes From Den" }),    
    ({ "Heron Evades And Attacks" }),
    ({ "Viper Strikes Low" }),
    ({ "Heron Parts The Rushes" })
  }),
  ({
    ({ "Tiger Faces Dragon" }),
    ({ "Dragon Strikes The Tiger" }),
    ({ "Tiger Flanks The Dragon" }),
    ({ "Dragon Unleashes Fire" }),
  }),
  ({
    ({ "Falling Of The Mountain" }),
    ({ "Crack Of Lightning" }),
    ({ "Wind Drives Stone" }),
    ({ "Water Cuts Through Earth" }),
  }),
});

varargs mixed
get_target_hitloc_id (object living, string target, int randomize=0)
{
  
  if (!target || ! strlen(target))
    return 1;

  object cbo = living->query_combat_object();
  int *hitloc_ids = cbo->query_hitloc_id();
  if (randomize)
    return one_of_list(hitloc_ids);
  
  mixed hitloc_data;
  
  foreach (int hitloc_id: hitloc_ids) {
    hitloc_data = cbo->query_hitloc(hitloc_id);
    if (lower_case(target) == lower_case(hitloc_data[2]))
      return hitloc_id;
  }
  return 0;
}

mixed * 
target_body_part (object actor, string arg)
{
    string method;
    object enemy;
    object * results;

    enemy = actor->query_attack();

    if (! enemy) {
      actor->catch_tell("You are not fighting anyone!\n");
      return ({});
    }

    int hitloc_id_random = get_target_hitloc_id(enemy, arg, 1);
    if (!arg || !strlen(arg))
      return ({ enemy, hitloc_id_random });

    int hitloc_id = get_target_hitloc_id(enemy, arg);
    if (! hitloc_id) {
      actor->catch_tell("Your enemy does not have a "
                        + arg + " you can target!\n");
      return ({ });
    }
    int skill = TP->query_skill(SS_WEP_SWORD) + TP->query_skill(SS_APPR_MON);
    int roll = random(200);
    if (roll > skill) {
      log_me("Targeting randomized because " + roll + ">" + "skill",
             "notice", "battack.log");
      return ({ enemy, hitloc_id_random });
    }
    log_me("Targeting stays because " + roll + "<" + skill,
           "notice", "battack.log");
    return ({ ({ enemy, hitloc_id }) });
}

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
void 
config_ability ()
{
  ::config_ability();
  set_combat_aid(BATTACK_COMBAT_AID);
  set_dt(W_SLASH|W_IMPALE);
  // Extra damage taken from Strength and Dex and Int
  set_stats(({ SKILL_AVG, TS_STR, TS_DEX, TS_INT, SKILL_END }) );
  set_skills(({ SS_WEP_SWORD }) );
  // Can battack once every 25 seconds on average
  set_ability_prep_time(BATTACK_PREP_TIME);
  set_ability_cooldown_time(BATTACK_COOLDOWN_TIME);
  set_ability_name("battack");
  set_ability_target(target_body_part);

  // Blademasters achieve 10 links at guild stat 200
  set_guild_stat_modifier(SS_LAYMAN, 50, 200);
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
mixed
select_attack (int style, object *weapons)
{
  int attack_form, *attack_id;
  object *_weapons;

  if (style == 1 && sizeof(weapons) > 1)
    _weapons = ({weapons[random(sizeof(weapons))]});
  else
    _weapons = weapons;

  attack_form = random(4) + 1;
  attack_id   = _weapons->query_attack_id();
  /* Now we return the weapon(s) to use, which form of the */
  /* specified style to use, and the attack id's of the weapons */
  return ({_weapons, attack_form, attack_id});
}

mapping
init_pronouns (object player, object target)
{
  mapping pn = ([
    "s_his": player->query_possessive(),
    "s_he": player->query_pronoun(),
    "s_him": player->query_objective(),
    "t_his": target->query_possessive(),
    "t_he": target->query_pronoun(),
    "t_him": target->query_objective()
  ]);
  return pn;
}

string
fill_desc (mixed *form_descs, object player,
           mixed target, string attack_desc, mapping pronouns)
{
  string value;
  foreach (string placeholder: form_descs[2]) {
    switch(placeholder) {
    case "player":
      value = QCTNAME(player);
      break;
    case "s_his":
    case "s_he":
    case "s_him":
      value = pronouns[placeholder];
    break;
    case "target":
      value = objectp(target) ? QTNAME(target) : target;
      break;
    case "attack_desc":
      value = attack_desc;
      break;
    default:
      value = placeholder;
    }
    form_descs[1] = sprintf(form_descs[1], value);
  }
}
  
mapping
set_attack_messages (int style, int attack_form, object player,
                     object target, string attack_desc, mapping pronouns)
{
  log_me("set attack message with " + style + "," +
         (attack_form-1) + "," + attack_desc,
         "info", "battack.log");
  mixed *form_descs = bm_styles_and_forms[style][attack_form-1];
  string enemy_message = target->is_blademaster()
    ? sprintf("%s strikes at you with %s!\n",
              player->query_The_name(target), form_descs[0])
    : sprintf("%s executes a complicated swirl with his %s at you!\n",
              player->query_The_name(target), attack_desc);

  string watchers_message =
    sprintf("%s executes a complicated swirl with his %s at %s.\n",
            QCTNAME(player), attack_desc, QTNAME(target));
  mapping messages = ([
    "self": sprintf("You attempt to execute %s at %s!\n",
                    form_descs[0], target->query_the_name(player)),
    "enemy": enemy_message,
    "bm_watchers": sprintf("%s strikes at %s with %s!\n",
                           QCTNAME(player), QTNAME(target),
                           form_descs[0]),
    "watchers": watchers_message,
  ]);

  return messages;
}

/* Function name: launch_attack
 * Description: wrapper around launch_attack_N
 * Arguments    : weapons - Object array containing which weapons to use.
 *                target - Object pointer to the living to attack.
 * Returns      : n/a
 */

private void
launch_attack (int style, object *weapons, object target, string hdesc)
{
  int attack_form, attack_id;
  string attack_desc;
  object wep, cob = TP->query_combat_object(),
    *watchers, *masters;
  mapping pronouns = init_pronouns(TP, target);
  mixed my_attack = select_attack(style, weapons);
  
  wep = my_attack[0][0];
  attack_form = my_attack[1];
  attack_id = my_attack[2][0];

  watchers = all_inventory(environment(TP)) - ({TP, target});
  watchers = FILTER_PLAYERS(watchers);
  masters  = filter(watchers, &->is_blademaster());
  watchers -= masters;
  attack_desc = TP->query_weapon(attack_id)->short();
  mapping messages = set_attack_messages(style, attack_form, TP, target,
                                 attack_desc, pronouns);

  tell_object(TP, messages["self"]);
  if (interactive(target))
    tell_object(target, messages["enemy"]);
  target->tell_watcher(messages["bm_watchers"], target, ({TP, target}) + watchers);
  target->tell_watcher(messages["watchers"],  target, ({TP, target}) + masters);

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
    player,
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

  player = this_player();
  my_attack = select_attack(1, weapons);
  wep = my_attack[0][0];
  form = my_attack[1];
  aid = my_attack[2][0];

  cob = player->query_combat_object();

  watchers = all_inventory(environment(player)) - ({player,
                                                    target});
  watchers = FILTER_PLAYERS(watchers);
  masters = filter(watchers, &->is_blademaster());
  watchers -= masters;

  s_his = player->query_possessive();
  s_he = player->query_pronoun();
  s_him = player->query_objective();
  t_his = target->query_possessive();
  t_he = target->query_pronoun();
  t_him = target->query_objective();

  attack_desc = player->query_weapon(aid)->short();
  switch (form)
    {
    case 1: /* Viper Strikes From Den */
      tell_object(player,
                  "You execute Viper Strikes From Den at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Viper Strikes " +
                        "From Den!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " holds " + s_his + " " + attack_desc + " " +
                        " at " + s_his + " side, reversing " + s_his +
                        " grip on its hilt, then suddenly lashes " +
                        "out at you with it!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Viper Strikes From Den.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " holds " + s_his + " " + attack_desc + " " +
                           "at " + s_his + " side, suddenly reversing " +
                           s_his + " grip on the hilt and lashing outwards " +
                           "at " + QTNAME(target) + " with it.\n", target,
                           ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = A_HEAD;
      break;
    case 2: /* Heron Evades And Attacks */
      tell_object(player,
                  "You execute Heron Evades And Attacks at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Heron Evades " +
                        "And Attacks!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " suddenly spins away from your line " +
                        "of attack, pivoting backwards around " +
                        s_his + " right foot, thrusting " + s_his +
                        " " + attack_desc + " towards you from " +
                        "the side as " + s_he + " comes around!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Heron Evades And Attacks.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " suddenly spins away from " + QTNAME(target) +
                           "'s line of attack, pivoting backwards around " +
                           s_his + " right foot, thrusting " +
                           s_his + " " + attack_desc + " towards " +
                           QTNAME(target) + " from the side as he comes " +
                           "around!\n",
                           target, ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = A_BODY;
      break;
    case 3: /* Viper Strikes Low */
      tell_object(player,
                  "You execute Viper Strikes Low at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Viper Strikes " +
                        "Low!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " ducks beneath your attack, and " +
                        "leaps forward, slashing at your " +
                        "stomach with " + s_his + " " +
                        attack_desc + "!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Viper Strikes Low.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " ducks beneath " + QTNAME(target) + "'s " +
                           "attack, then leaps forward, slashing at " +
                           QTNAME(target) + "'s stomach with " + s_his +
                           " " + attack_desc + "!\n",
                           target, ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = A_BODY;
      break;
    default: /* Heron Parts The Rushes */
      tell_object(player,
                  "You execute Heron Parts The Rushes at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Heron Parts " +
                        "The Rushes!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " catches your weapon with " + s_his +
                        " " + attack_desc + ", and with a twist " +
                        "of " + s_his + " wrist, deflects it " +
                        "to one side. Then " + s_he + " savagely " +
                        "slashes with his weapon downwards " +
                        "over your chest, and then sideways " +
                        "across your stomach!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Heron Parts The Rushes.\n",
                           target, ({player}) + watchers);
      target->tell_watcher(QCTNAME(player) +
                           " catches " + QTNAME(target) + "'s weapon with " +
                           s_his + " " + attack_desc + ", and with a twist " +
                           "of " + s_his + " wrist, deflects it to one " +
                           "side. Then " + s_he + " savagely slashes " +
                           "with his weapon downwards over " + QTNAME(target) +
                           "'s chest, and then sideways across " +
                           t_his + " stomach!\n",
                           target, ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = A_BODY;
    }
}

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
    player,
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

  player = this_player();
  my_attack = select_attack(2, weapons);
  wep = my_attack[0];
  form = my_attack[1];
  aid = my_attack[2];

  cob = player->query_combat_object();

  watchers = all_inventory(environment(player)) - ({player,
                                                    target});
  watchers = FILTER_PLAYERS(watchers);
  masters = filter(watchers, &->is_blademaster());
  watchers -= masters;

  s_his = player->query_possessive();
  s_he = player->query_pronoun();
  s_him = player->query_objective();
  t_his = target->query_possessive();
  t_he = target->query_pronoun();
  t_him = target->query_objective();

  attack_desc_1 = player->query_weapon(aid[0])->short();
  attack_desc_2 = player->query_weapon(aid[1])->short();

  switch (form)
    {
    case 1: /* Tiger Faces Dragon */
      tell_object(player,
                  "You execute Tiger Faces Dragon at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Tiger Faces " +
                        "Dragon!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " crosses " + s_his + " arms across " +
                        s_his + " chest, with " + s_his + " " +
                        attack_desc_1 + " and " + attack_desc_2 +
                        " behind " + s_his + " back, then lunges " +
                        "forward at you, slashing high and low with " +
                        "the weapons!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Tiger Faces Dragon.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " crosses " + s_his + " arms across " +
                           s_his + " chest, with " + s_his + " " +
                           attack_desc_1 + " and " + attack_desc_2 +
                           " behind " + s_his + " back, then lunges " +
                           "forward at " + QTNAME(target) +
                           ", slashing high and low with " +
                           "the weapons!\n",target,
                           ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = ({A_TORSO, A_LEGS});
      break;

    case 2: /* Dragon Strikes The Tiger */
      tell_object(player,
                  "You execute Dragon Strikes The Tiger at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Dragon Strikes " +
                        "The Tiger!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " slips towards you, slashing across " +
                        "your legs with " + s_his + " " +
                        attack_desc_1 + " then, abruptly twirls " +
                        s_his + " " + attack_desc_2 + " high and " +
                        "brings it down across your chest!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Dragon Strikes The Tiger.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " slips towards " + QTNAME(target) + ", slashing " +
                           "across " + t_his + " legs with " + s_his + " " +
                           attack_desc_1 + " then, abruptly twirls " +
                           s_his + " " + attack_desc_2 + " high and " +
                           "brings it down across " + QTNAME(target) + "'s chest!\n",
                           target, ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = ({A_LEGS, A_TORSO});
      break;
    case 3: /* Tiger Flanks The Dragon */
      tell_object(player,
                  "You execute Tiger Flanks The Dragon at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Tiger Flanks " +
                        "The Dragon!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " slashes at you with " + s_his + " " +
                        attack_desc_1 + " high, driving you " +
                        "back a step, then abruptly swings " +
                        "around the other way and thrusts " +
                        "into your side with " + s_his + " " +
                        attack_desc_2 + "!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Tiger Flanks The Dragon.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " slashes at " + QTNAME(target) + " with " +
                           s_his + " " + attack_desc_1 + " high, driving " +
                           t_him + " back a step, then abruptly swings " +
                           "around the other way, thrusting " + s_his + " " +
                           attack_desc_2 + " into " + QTNAME(target) +
                           "'s side!\n",
                           target, ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = ({A_LEGS, A_TORSO});
      break;

    default: /* Dragon Unleashes Fire */
      tell_object(player,
                  "You execute Dragon Unleashes Fire at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Dragon Unleashes " +
                        "Fire!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " charges at you, " + s_his + " " +
                        attack_desc_1 + " and " + attack_desc_2 +
                        " flashing in and out in inter-weaving " +
                        "figure eights, slashing at you from " +
                        "seemingly all directions!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Dragon Unleashes Fire.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " charges at " + QTNAME(target) + ", " +
                           s_his + " " + attack_desc_1 + " and " +
                           attack_desc_2 + " flashing in and out in inter-" +
                           "weaving figure eights, slashing at " +
                           QTNAME(target) + " from seemingly all " +
                           "directions!\n",
                           target, ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = ({A_HEAD, A_TORSO});
    }
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
    player,
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

  player = this_player();
  my_attack = select_attack(3, weapons);
  wep = my_attack[0][0];
  form = my_attack[1];
  aid = my_attack[2][0];

  cob = player->query_combat_object();

  watchers = all_inventory(environment(player)) - ({player,
                                                    target});
  watchers = FILTER_PLAYERS(watchers);
  masters = filter(watchers, &->is_blademaster());
  watchers -= masters;

  s_his = player->query_possessive();
  s_he = player->query_pronoun();
  s_him = player->query_objective();
  t_his = target->query_possessive();
  t_he = target->query_pronoun();
  t_him = target->query_objective();

  attack_desc = player->query_weapon(aid)->short();
  switch (form)
    {
    case 1: /* Falling Of The Mountain */
      tell_object(player,
                  "You execute Falling Of The Mountain at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Falling Of The " +
                        "Mountain!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " begins a brutal series of hacks " +
                        "at you with " + s_his + " " +
                        attack_desc + ", then suddenly " +
                        "reverses the blade and thrusts at " +
                        "your chest!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Falling Of The Mountain.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " begins a brutal series of hacks " +
                           "at " + QTNAME(target) + " with " + s_his + " " +
                           attack_desc + ", then suddenly " +
                           "reverses the blade and thrusts at " +
                           QTNAME(target) + "'s chest!\n",target,
                           ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = A_TORSO;
      break;
    case 2: /* Crack Of Lightning */
      tell_object(player,
                  "You execute Crack Of Lightning at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Crack Of " +
                        "Lightning!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " breaks into a forward roll beneath " +
                        "your attacks, and thrusts " + s_his +
                        " " + attack_desc + " upwards into " +
                        "your chest!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Crack Of Lightning.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " breaks into a forward roll beneath " +
                           QTNAME(target) + "'s attacks, and thrusts " +
                           s_his + " " + attack_desc + " upwards into " +
                           t_his + " chest!\n",
                           target, ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = A_BODY;
      break;
    case 3: /* Wind Drives Stone */
      tell_object(player,
                  "You execute Wind Drives Stone at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Wind Drives " +
                        "Stone!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " rolls forward beneath your attack, " +
                        "and allows " + s_his + " weight to " +
                        "carry " + s_him + " to one side of " +
                        "you, slashing at your chest brutally " +
                        "with " + s_his + " " + attack_desc +
                        " on the way!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Wind Drives Stone.\n", target, ({player}) +
                           watchers);
      target->tell_watcher(QCTNAME(player) +
                           " rolls forward beneath " + QTNAME(target) +
                           "'s attack, and allows " + s_his + " weight " +
                           "to carry " + s_him + " to one side of " +
                           QTNAME(target) + ", slashing at " + t_his +
                           " chest with " + s_his + " " + attack_desc +
                           " on the way!\n",
                           target, ({player}) + masters);
      damage_type = W_SLASH;
      hit_location = A_TORSO;
      break;
    default: /* Water Cuts Through Earth */
      tell_object(player,
                  "You execute Water Cuts Through Earth at " +
                  target->query_the_name(player) + "!\n");
      if (interactive(target))
        {
          if (target->is_blademaster())
            tell_object(target,
                        player->query_The_name(target) +
                        " strikes at you with Water Cuts " +
                        "Through Earth!\n");
          else
            tell_object(target,
                        player->query_The_name(target) +
                        " calmly begins beating away all " +
                        "your attempts at attack, until " +
                        "suddenly you realize " + s_he + "'s " +
                        "created an opening in your defense, " +
                        "through which " + s_he + " thrusts savagely " +
                        "at your chest with " + s_his +
                        " " + attack_desc + "!\n");
        }
      target->tell_watcher(QCTNAME(player) +
                           " strikes at " + QTNAME(target) + " with " +
                           "Water Cuts Through Earth.\n",
                           target, ({player}) + watchers);
      target->tell_watcher(QCTNAME(player) +
                           " calmly begins beating away all " +
                           QTNAME(target) + "'s attempts at attack, until " +
                           "suddenly you realize " + s_he + "'s " +
                           "created an opening in " + t_his + " defense, " +
                           "through which " + s_he + " thrusts savagely " +
                           "at " + QTNAME(target) + "'s chest with " + s_his +
                           " " + attack_desc + "!\n",
                           target, ({player}) + masters);
      damage_type = W_IMPALE;
      hit_location = A_TORSO;
    }
}

/*
 * Function name: check_for_head
 * Description  : Identifies the target as having a head as
 *                determined by an attack hitloc.
 * Arguments    : vic - Object pointer to the victim.
 * Returns      : 0 - 'vic' has no head.
 *                1 - 'vic' has a head.
 */
int
check_for_head(object vic)
{
  int *ids,
    i;
  object cob;

  cob = vic->query_combat_object();
  ids = cob->query_hitloc_id();
  for (i = 0; i < sizeof(ids); i++)
    {
      if ((cob->query_hitloc(ids[i]))[2] == "head")
        return 1;
    }
  return 0;
}

/*
 * Function name: decap_no_corpse
 * Description  : Called when this attack has killed something
 *                with LIVE_I_NO_CORPSE set. Special version
 *                of the normal decapitation routine.
 * Arguments    : vic - Object pointer to the victim.
 *                weps - Array of object pointers to the
 *                       weapon(s) used in the attack.
 * Returns      : n/a
 */
void
decap_no_corpse(object vic, mixed weps)
{
  object player;
    
  player = this_player();
    
  if (objectp(weps))
    weps = ({weps});

  player->catch_msg("As you slash your " +
                    weps[0]->short() + " forward to administer the final " +
                    "blow, " + QTNAME(vic) + " collapses away!\n");
  tell_room(environment(player), QCTNAME(player) +
            " raises " + player->query_possessive() + " " +
            weps[0]->short() + " to administer the final blow, " +
            "but " + QTNAME(vic) + " collapses away before " +
            player->query_pronoun() + " can swing!\n",
            ({player, vic}));
  vic->do_die(player);
}

/*
 * Function name: decap_corpse
 * Description  : Decapitate the victim's corpse.
 * Arguments    : vic - Object pointer to the victim.
 *                weps - Array of object pointers to the
 *                       weapon(s) used in the attack.
 */
void
decap_corpse(object vic, mixed weps)
{
  object here,
    player,
    head,
    corpse;
  string race,
    corpsename,
    how;

  player = this_player();
  if (objectp(weps))
    weps = ({weps});

  here = environment(vic);

  if (!check_for_head(vic))
    {
      player->catch_tell("Considering the absence of " +
                         "a head upon " +  vic->query_the_name(player) +
                         "'s shoulders, you're denied your decapitation.\n");
      vic->do_die(player);
      return;
    }

  switch (here->query_prop(ROOM_I_TYPE))
    {
    case ROOM_IN_WATER:
      how = "splashes into the water";
      break;
    case ROOM_UNDER_WATER:
      how = "drifts down through the water";
      break;
    case ROOM_IN_AIR:
      how = "falls out of the air";
      break;
    case ROOM_BEACH:
      how = "drops into the sand";
      break;
    default:
      how = "hits the ground";
    }

  player->catch_msg("As " + QTNAME(vic) + " hovers " +
                    "on the verge of death, you strike forward with your " +
                    weps[0]->short() + ". " + QCTNAME(vic) + "'s head " +
                    "rolls backwards off " + vic->query_possessive() + " " +
                    "neck in response, which " + how + " a moment " +
                    "before the rest of " + vic->query_possessive() + " body.\n");
  tell_room(here,  "As " + QTNAME(vic) +
            " hovers on the verge of death, " + QTNAME(player) +
            " strikes forward with " + player->query_possessive() +
            " " + weps[0]->short() + ". " + QCTNAME(vic) + "'s " +
            "head rolls backwards off " + vic->query_possessive() +
            " neck in response, and " + how + " a moment " +
            "before the rest of " + vic->query_possessive() + " body.\n",
            ({player, vic}));

  corpsename = "remains of " + vic->query_real_name();
  race = vic->query_race_name();
  setuid(); seteuid(getuid());
  head = clone_object(OBJ + "decap_head");
  head->setup_head(vic);
  vic->do_die(player);
  head->move(here);
  corpse = present(corpsename,environment(player));
  corpse->add_prop("_aod_decapitated_prop", 1);
  corpse->remove_leftover("head");
  corpse->remove_leftover("eye");
  corpse->remove_leftover("tooth");
  corpse->remove_leftover("nose");
  corpse->remove_leftover("ear");
  corpse->remove_leftover("scalp");
  corpse->add_adj("decapitated");
  corpse->set_short("decapitated corpse of " + LANG_ADDART(race));
  corpse->set_pshort("decapitated corpses of " +
                     LANG_ADDART(race));
  corpse->set_long("You can tell this is " + LANG_ADDART(race) + " corpse, " +
                   "but the identity of the corpse is lost to you, as " +
                   "the bloody stump of a neck where its head used to be " +
                   "makes identification rather difficult.\n");
}

/*
 * Function name: bm_get_style
 * Description  : Returns the most appropriate style for the player
 *                to be using, based on weapons wielded, skills, and
 *                stats.
 * Arguments    : n/a
 * Returns      : 1 - 5 are fail flags.
 *                    1 - No swords wielded.
 *                    2 - Two one-handers wielded, but not enough skill
 *                        in two-handed combat to use them, and not
 *                        dex for single one-handed sword forms.
 *                    3 - Single two-hander wielded, but not enough
 *                        strength for those forms.
 *                    4 - Single one-handed sword wielded, not enough
 *                        dexterity for those forms.
 *                    5 - Is not skilled enough to execute any forms
 *                On success, an array: ({style number, ({weapons wielded})})
 */
mixed
bm_get_style()
{
  mixed form;
  object *weapons;
    
  /* Fail if the player doesn't have enough skill */
  if (!is_skilled_blademaster(TP))
    return FAIL_NO_SKILL;

  /* Find any swords the player might be wielding. Note that */
  /* blademasters attacks work _only_ with swords. */
  weapons = get_swords();
    
  /* Fail if the player has no swords wielded. */
  if (!sizeof(weapons))
    return FAIL_NO_SWORD;

  /* Figure out which form is appropriate (a single 1-handed sword, */
  /* two 1-handed swords, or one 2-handed sword), and fail if the */
  /* player doesn't have the min form requirements. */

  /* If the player has two one-handed swords. */
  if (sizeof(weapons) == 2) {
    /* First we'll check for two-handed skill. */
    if (TP->query_skill(SS_2H_COMBAT) >= FORM_2H_MIN)
      form = ({2}) + weapons;
    /* Insufficient 2-handed skill, so we'll make a dex */
    /* check to use a single-weapon form. */
    else if (TP->query_stat(SS_DEX) >= FORM_DEX_MIN)
      form = ({1}) + weapons;
    /* Player can't use any forms of one-handed weapons, so fail. */
    else
      return FAIL_NO_SKILL_DEX_2H;
  }
  /* Ok, player's only wielding one sword, lets see if it's one or */
  /* two handed, and if he's skilled enough to use the relevant */
  /* forms. First check for two-handed.*/
  else if (weapons[0]->query_hands() == W_BOTH) {
    if (TP->query_stat(SS_STR) >= FORM_STR_MIN)
      form = ({3}) + weapons;
    else
      return FAIL_NO_STR_BOTH;
  }
  /* Ok, the weapon must be a one-hander. */
  /* Only DEX is required in this case.   */
  else {
    if (TP->query_stat(SS_DEX) >= FORM_DEX_MIN)
      form = ({1}) + weapons;
    else
      return FAIL_NO_DEX;
  }
  return form;
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items, int result)
{
  object player, weapon;
  mixed hit_descr, form;
  string hit_mesg, s_he;

  log_me("In special did hit at " +
         implode(({aid+"", hdesc+"", phurt+"", phit+"", dam+"", result+""}), ","),
         "info", "battack");
  player = this_player();
  s_he = player->query_pronoun();

  if (intp(form = bm_get_style())) {
    player->catch_msg("You fail to complete your attack form.\n");
    send_debug_message("battack", "Form not found on the actual "
                       + "attack hit.");
    return;
  }
  /*  
      switch (form[0]) {
      case 1:
      launch_attack_1(form[1..], enemy);
      break;
    
      case 2:
      launch_attack_2(form[1..], enemy);
      break;
    
      case 3:
      launch_attack_3(form[1..], enemy);
      break;
      }*/
  launch_attack(form[0], form[1..], enemy, hdesc);
  
  /* phurt is the percentage of damage done / total health */
  /* remaining, i.e. when hitresult[0] == 10, we've just taken */
  /* away 10% of the target's remaining hp. */        
  if (phurt >= 0) {
    if (enemy->query_hp() > 0) {
      switch (phurt) {
      case 0:
        hit_mesg = "barely scratches";
        break;
            
      case 1..9:
        hit_mesg = "lightly wounds";
        break;
            
      case 10..24:
        hit_mesg = "mildly cuts";
        break;
            
      case 25..39:
        hit_mesg = "roughly cuts";
        break;
            
      case 40..54:
        hit_mesg = "badly slashes";
        break;
            
      case 55..69:
        hit_mesg = "horribly slices";
        break;

      case 70..84:
        hit_mesg = "viciously mauls";
        break;

      case 85..99:
        hit_mesg = "near-fatally wounds";
        break;

      default:
        hit_mesg = "fatally wounds";
      } 
      
      player->catch_msg("Your attack " + hit_mesg + " " +
                        QTNAME(enemy) + " in the " + hdesc + "!\n");
      if (interactive(enemy))
        enemy->catch_msg(QCTNAME(player) +
                         "'s attack " + hit_mesg + " you in the "
                         + hdesc + "!\n");
      enemy->tell_watcher(QCTNAME(player) + "'s attack " +
                          hit_mesg + " " + QTNAME(enemy) + " in the "+
                          hdesc + "!\n", enemy, 
                          ({player}));
               
      return;
    }

    /* Have we taken _all_ of the target's hp? If we have... */
    /* BURN THE WITCH!!! BURN HER!!! */
    player->catch_msg(QCTNAME(enemy) +
                      " stares in stunned silence at the fatal wound left " +
                      "by the flash of your blade.\n");
    enemy->tell_watcher(QCTNAME(enemy) + " stares in " +
                        "stunned silence at the fatal wound left by the " +
                        "flash of " + QTNAME(player) + "'s blade.\n",
                        enemy, ({player}));
    if (interactive(enemy))
      enemy->catch_msg("You stare in stunned silence " +
                       "at the fatal wound left by the flash of " +
                       QTNAME(player) + "'s blade.\n");
        
    if (player->query_prop(BLADEMASTER_NO_DECAPITATE))
      enemy->do_die(player);
    else
      if (enemy->query_prop(LIVE_I_NO_CORPSE))
        decap_no_corpse(enemy, items);
      else
        decap_corpse(enemy, items);
    return;
  }
  else {
    player->catch_msg(
                      QCTNAME(enemy) + " avoids your " +
                      "blow, and you miss by a mile!\n");
    enemy->catch_msg(
                     "You avoid " + QTNAME(player) +
                     "'s blow, and " + s_he + " misses by a mile!\n");
    enemy->tell_watcher(QCTNAME(enemy) + " avoids " +
                        QTNAME(player) + "'s blow, and " + s_he +
                        " misses by a mile!\n", enemy, ({player}));
  }
}

/*
 * Function name: query_tohit
 * Description  : Calculates the tohit for the player. 
 * Arguments    : player - player to check
 * Returns      : input to cb_tohit function
 */
int 
query_tohit ()
{
  object player;
  int tohit, guildstat;
  mixed form;
        
  player = this_player();
    
  form = bm_get_style();
  if (intp(form))
    // Could not get a form to use for battack
    return 0;
    
  tohit = 0;
  foreach (object weapon : form[1..])
    if (weapon->query_hit() > tohit)
      tohit = weapon->query_hit();
    
  // Now we have the weapon with the highest tohit

  /* attack_hit modifications added by Teth, 8 Feb 2002 */
  /* Ok, let's deal with the attack_hit modifications */
  /* First we halve the wchit value over 40           */
  if ( tohit > 40 )
    tohit = 40 + ( (tohit - 40) / 2 );

  /* Ok, increase hit by guildstat as a %, capped at 100% */
  guildstat = player->query_base_stat(SS_LAYMAN);
  guildstat = ( guildstat > 100 ) ? 100 : guildstat;
  tohit += ftoi( itof(tohit) * itof(guildstat) / 100.0 );

  /* But we don't want attack_hit getting any higher than */
  /* 90 in any event. This is a layman attack, after all  */
  tohit = ( tohit > 90 ) ? 90 : tohit;

  /* end of additions by Teth, 8 Feb 2002                 */
            
  return tohit;
}

/*
 * Function name: validate_battack_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */

int
validate_battack_requirements(object player)
{
  mixed form;
  string message;
  object bm_parry;
  
  seteuid(getuid()); 

  if (player->query_fatigue() < FATIGUE_COST) {
    player->catch_tell("You are too tired to use a special attack "
                       + "form!\n");
    return 0;
  }

  form = bm_get_style();
  if (pointerp(form))
    return 1;
    
  switch (form) {
  case FAIL_NO_SWORD:
    message ="You have no swords to attack with!\n";
    break;
  case FAIL_NO_SKILL_DEX_2H:
    message = "You have neither the skill to attack with "
      + "the two one-handed sword forms, nor the dexterity " 
      + "to attack with the single one-handed sword forms!\n";
    break;
  case FAIL_NO_STR_BOTH:
    message = "You do not have the strength to attack "
      + "with the two-handed weapon forms!\n";
    break;
  case FAIL_NO_DEX:
    message = "You do not have the dexterity to attack "
      + "with the single one-handed weapon forms!\n";
    break;
  case FAIL_NO_SKILL:
    message = "You do not possess the skill to attack "
      + "with any sword forms.\n";
    break;
  }
  player->catch_tell(message);
  return 0;
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
  object enemy;
  object *enemies;
  int *hitloc_ids;

  if (!pointerp(targets)) {
    // No targets specified
    send_debug_message("battack", "check_valid_action failed because "
                       + "there were no targets.");
    return 0;
  }
    
  if (!validate_battack_requirements(player))
    return 0;

  /* Because of the pain in the butt associated with legally */
  /* initiating an attack, players can't start fights with */
  /* battack, so if the target isn't in the enemies list, */
  /* fail. */
  enemies = player->query_enemy(-1);
  object _target;
  foreach (object target : targets) {
    _target = pointerp(target) ? target[0] : target;
    if (IN_ARRAY(_target, enemies)) {
      enemy = _target;
      break;
    }
  }
   
  if (! enemy) 
    NF0("You can only use battack on opponents you "
        + "are already in combat with.\n");

  // Check for the targeted hitloc at the enemy
  int hitloc_id = get_target_hitloc_id(enemy, arg);

  // hitloc found or no hitloc specified, all is good
  if (hitloc_id) {
    log_me("battack resolved " + arg + " to ID " + hitloc_id +
           " in " + file_name(enemy),
           "info", "battack.log");
    return 1;
  }

  player->catch_tell("Your enemy does not have a "
                     + arg + " you can target!\n");
  return 0;
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
void
apply_costs_to_player (object player)
{
  int fatigue = player->query_fatigue();

  player->add_fatigue(fatigue > FATIGUE_COST ? -FATIGUE_COST : -fatigue);
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
int 
force_fail (object player, mixed * items, object enemy, 
            int resist, int result)
{
  return validate_battack_requirements(player) ? 0 : 1;
}

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
string
hook_stopped_ability (object ability, object player)
{
  return "You feel unable to launch a form.\n";
}

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
void
report_resolve_ability (int pen, int dt, int damage)
{
  string name = interactive(TP) ? capitalize(TPQN) : MASTER_OB(TPQN);

  send_debug_message("battack", 
                     name + " battacks with Pen of " + pen + ", "
                     + "Damage of " + damage,
                     BATTACK_LOG);
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
void
hook_special_complete ()
{
  write("You feel ready to use a special attack form again.\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
void
hook_targets_gone (object *targets)
{
  write("It appears your quarry has escaped before you could attack.\n");
}

static void 
ability_msg (object actor, mixed *targets, string arg)
{
  string extra = arg && strlen(arg) ? " targeting the " + arg : "";
  actor->catch_tell("You begin preparations to use a special attack "
                    + "form" + extra + ".\n");
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the person has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items (object actor, mixed * targets,
                      string arg, int pretest)
{
  object *swords = get_swords();

  return sizeof(swords) ? swords : 0;
}
