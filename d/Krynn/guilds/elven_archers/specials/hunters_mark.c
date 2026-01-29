/*
* Cotillion - 2020-10-04
* - Fixed type confusion
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <tasks.h>
#include <formulas.h>

#include "/std/combat/combat.h"

#include "../guild.h"
#include "missile_functions.c"


// Prototypes
// Global Variables
mapping marked = ([]);

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_ability()
{
    ::config_ability();
    set_combat_aid(3);
    set_tohit(105); // 89% hit chance
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 60, TS_DEX, SKILL_WEIGHT, 25, TS_WIS,
                  SKILL_WEIGHT, 15, TS_STR }) );
    set_skills( ({ SS_WEP_MISSILE }) );
    set_ability_prep_time(0);
    set_ability_cooldown_time(300);
    set_ability_target(target_one_distant_living);
    set_ability_target_verify(0);
    set_ability_visual(0);
    set_ability_name("hunt");

    set_guild_stat_modifier(SS_OCCUP, 90, 200);

    setuid();
    seteuid(getuid());
} /* config_ability */

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_resolve_ability(int pen, int dt, int damage)
{
    string name, logfile;

    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    logfile = FILE_PATH(MASTER_OB(this_object()));
    logfile += short() + "_damage";
    logfile = implode(explode(logfile, " "), "");

    send_debug_message(short(), name + " hits with Pen of "
        + pen + ", " + "Damage of " + damage, logfile);
} /* report_resolve_ability */

/*
 * Function name:   special_did_hit
 * Description:     Mask this function to process when the special scores.
 *                  Descriptions seen by everyone are set here.
 * Arguments:       1. (int) aid        - attack id
 *                  2. (string) hdesc   - hit description
 *                  3. (int) hid        - hitloc id
 *                  4. (int) phurt      - extent of damage
 *                  5. (object) enemy   - person being hit by special
 *                  6. (int) dt         - damage type
 *                  7. (int) phit       - percent hit success
 *                  8. (int) dam        - damage amount
 *                  9. (mixed *) items  - items used
 *                  10. (int) result    - result of cb_tohit
 * Returns:         Nothing
 */
public varargs void
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    object  bow, cmbt, arrow, archer;
    string *archer_msg, *enemy_msg, *others_msg, rnd_desc;
    int     attack_location, hitsuc, pen, hit, loaded = 0;
    mixed   hitres;

    archer = this_player();

    if (!filter_bow(bow = items[0]))
        return;

    archer->catch_msg("You seize the opportunity to attack " + QTNAME(enemy)
    + " as " + enemy->query_pronoun() + " attempts to leave.\n");
    enemy->catch_msg(QCTNAME(archer) + " seizes the opportune moment to attack "
    + "as you attempt to leave.\n");
    archer->tell_watcher(QCTNAME(archer) + " seizes the opportune moment to "
    + "attack as " + QTNAME(enemy) + " is attempting to leave.\n", ({ enemy }));

    if (objectp(bow->query_projectile()) &&
        objectp(cmbt = archer->query_combat_object()))
    {
        hit = bow->query_hit();

        attack_location = filter(cmbt->query_attack_id(),
                                &operator(==)(, bow) @
                                &operator([])(, 6) @
                                &cmbt->query_attack())[0];

        if ((cmbt->cb_try_hit(attack_location) > 0) &&
            (enemy->query_not_attack_me(archer, attack_location) <= 0) &&
            (hitsuc = cmbt->cb_tohit(attack_location, hit, enemy)) > 0)
        {
            pen = cmbt->query_attack(attack_location)[ATT_M_PEN][0];

            if (!random(10000))
                pen *= 5;

            hitres = enemy->hit_me(pen, dt, archer, attack_location);
        }
        else
        {
             hitres = enemy->hit_me(hitsuc, 0, archer, attack_location);
        }

        if (hitsuc > 0)
        {
            hitsuc = bow->query_pen();
            if (hitsuc > 0)
            {
                hitsuc = 100 * hitres[2] / hitsuc;
            }
            else
            {
                hitsuc = 0;
            }
        }

        if (hitres[1])
        {
            // We dont want to call damage from the special, or this would
            // boost the damage proportional to the special. Instead we modify
            // the value to minimum 1 if damage was done, so a miss from the
            // false arrow shot doesnt give us a non-fitting description.
            cmbt->cb_did_hit(attack_location, hitres[1], phurt,
                            hitres[0], enemy, dt, phit,
                            (dam ? (hitres[3] ? hitres[3] : 1) : dam));

            loaded = 1;
        }
    }

    if (!loaded)
    {
        // Handles the arrow stacks
        if (phurt < 5)
            arrow = reduce_and_miss(enemy, bow, items[1]);
        else
            arrow = reduce_and_hit(enemy, bow, items[1]);

        arrow->add_prop(OBJ_O_BELONGS_TO_ARCHER, archer);

        switch(phurt)
        {
            case -2..0:
            archer_msg = ({
                "You hurriedly nock and fire "
                + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + ". It flies past your target, missing "
                + enemy->query_objective(),
            });

            enemy_msg = ({
                "You hear the hiss of an arrow flying through the air as "
                + QTNAME(archer) + " hurriedly shoots "
                + LANG_ADDART(arrow->singular_short()) + " at you"
            });

            others_msg = ({
                QCTNAME(archer) + " hurriedly nocks and shoots "
                + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + ", but it just flies past "
                + enemy->query_objective() + ", barely missing "
                + "the target",
            });

                break;
            case 1..2:

            archer_msg = ({
                "You nock and shoot " + LANG_ADDART(arrow->singular_short())
                + " at " + QTNAME(enemy) + ", but it merely glances off "
                + enemy->query_possessive() + " " + hdesc + ", just nicking "
                + enemy->query_possessive() + " skin",
            });

            enemy_msg = ({
                QCTNAME(archer) + " nocks and shoots "
                + LANG_ADDART(arrow->singular_short()) + " at "
                + "you, but it merely glances off your " + hdesc + ", just "
                + "nicking your skin",
            });

            others_msg = ({
                QCTNAME(archer) + " nocks and shoots "
                + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + ", but it merely glances off "
                + enemy->query_possessive() + " " + hdesc + ", just nicking "
                + enemy->query_possessive() + " skin",
            });

                break;
            case 3..5:

            archer_msg = ({
                "You nock " + LANG_ADDART(arrow->singular_short()) + " and "
                + "shoot wildly at " + QTNAME(enemy) + ", with the arrow just "
                + "grazing " + enemy->query_possessive() + " " + hdesc
                + " and falling to the ground",
            });

            enemy_msg = ({
                QCTNAME(archer) + " nocks "
                + LANG_ADDART(arrow->singular_short()) + " and shoots "
                + "wildly at you, but the arrow just grazes your " + hdesc
                + " and falls to the ground",
            });

            others_msg = ({
                QCTNAME(archer) + " nocks "
                + LANG_ADDART(arrow->singular_short()) + " and shoots "
                + "wildly at " + QTNAME(enemy) + ", but the arrow just grazes "
                + enemy->query_possessive() + " " + hdesc + " and falls to the "
                + "ground",
            });

                break;
            case 6..15:

            rnd_desc = one_of_list( ({
                                    "opening a nasty wound",
                                    "causing significant damage",
                                    "leaving a minor wound",
                                }) );

            archer_msg = ({
                "You swiftly nock " + LANG_ADDART(arrow->singular_short())
                + " and fire accurately "
                + "at " + QTNAME(enemy) + ", the arrow pierces "
                + enemy->query_possessive() + " " + hdesc + ", " + rnd_desc,
            });

            enemy_msg = ({
                QCTNAME(archer) + " swiftly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "fires accurately at you, the arrow pierces your " + hdesc
                + ", " + rnd_desc,
            });

            others_msg = ({
                QCTNAME(archer) + " swiftly nocks "
                + LANG_ADDART(arrow->singular_short()) + " and "
                + "fires " + "accurately at " + QTNAME(enemy) + ". The arrow "
                + "pierces " + enemy->query_possessive() + " " + hdesc + ", "
                + rnd_desc,
            });

                break;
            case 16..27:

            archer_msg = ({
                "You load your bow with " + LANG_ADDART(arrow->singular_short())
                + " " + "and shoot at " + QTNAME(enemy) + ". The arrow stabs "
                + "deeply into " + enemy->query_possessive() + " " + hdesc
            });

            enemy_msg = ({
                QCTNAME(archer) + " loads " + archer->query_possessive() + " "
                + bow->short() + " and shoots "
                + LANG_ADDART(arrow->singular_short()) + " at you. "
                + "The arrows stabs deeply into your " + hdesc
            });

            others_msg = ({
                QCTNAME(archer) + " loads " + archer->query_possessive() + " "
                + bow->short() + " and shoots "
                + LANG_ADDART(arrow->singular_short()) + " at "
                + QTNAME(enemy) + ". The arrow stabs deeply into "
                + enemy->query_possessive() + " " + hdesc
            });

                break;
            case 28..43:

            rnd_desc = one_of_list( ({  "deeply",
                                        "badly",
                                        "easily",
                                        "forcefully",
                                        "accurately",
                                        "solidly"
                                    }) );

            archer_msg = ({
                "You swiftly load your " + bow->short() + " with "
                + LANG_ADDART(arrow->singular_short()) + ", focus intently on "
                + QTNAME(enemy) + " and then shoot, sending the arrow in "
                + enemy->query_possessive() + " direction. It " + rnd_desc + " "
                + "impales " + enemy->query_possessive() + " " + hdesc,
            });

            enemy_msg = ({
                QCTNAME(archer) + " loads " + archer->query_possessive() + " "
                + bow->short() + " with " + LANG_ADDART(arrow->singular_short())
                + " and shoots, sending it rapidly in your direction. It "
                + rnd_desc + " impales your " + hdesc,
            });

            others_msg = ({
                QCTNAME(archer) + " loads " + archer->query_possessive() + " "
                + bow->short() + "with " + LANG_ADDART(arrow->singular_short())
                + " and shoots at " + QTNAME(enemy) + ", sending it rapidly in "
                + enemy->query_possessive() + " direction. It " + rnd_desc
                + " impales " + enemy->query_possessive() + " " + hdesc,
            });

                break;
            case 44..65:

            if (enemy->query_humanoid())
            {
                archer_msg = ({
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot " + QTNAME(enemy) + " with great precision. "
                    + capitalize(enemy->query_pronoun()) + " grasps "
                    + enemy->query_possessive() + " " + hdesc + ", which is "
                    + "deeply punctured by the arrow",
                });

                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at you with great precision. You grasp your "
                    + hdesc + ", which is deeply punctured by the arrow",
                });

                others_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at " + QTNAME(enemy) + " with great "
                    + "precision. " + capitalize(enemy->query_pronoun()) + " "
                    + "grasps " + enemy->query_possessive() + " " + hdesc + ", "
                    + "which is deeply punctured by the arrow",
                });
            }
            else
            {
                archer_msg = ({
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot at " + QTNAME(enemy) + " with great "
                    + "precision. The arrow deeply punctures "
                    + enemy->query_possessive() + " " + hdesc,
                });

                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at you with great precision. The arrow "
                    + "deeply punctures your " + hdesc,
                });

                others_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at " + QTNAME(enemy) + " with great "
                    + "precision. The arrow deeply punctures "
                    + enemy->query_possessive() + " " + hdesc,
                });
            }

                break;
            case 66..99:

            archer_msg = ({
                "You rapidly draw " + LANG_ADDART(arrow->singular_short())
                + " to your " + bow->short() + " and shoot accurately at "
                + QTNAME(enemy) + ", who staggers " + "when the arrow lances "
                + "through " + enemy->query_possessive() + " " + hdesc + ", "
                + "opening a heavily bleeding wound"
            });

            enemy_msg = ({
                QCTNAME(archer) + " rapidly draws "
                + LANG_ADDART(arrow->singular_short()) + " to "
                + archer->query_possessive() + " " + bow->short() + " and "
                + "shoots accurately at you. You stagger when the arrow lances "
                + "through your " + hdesc + ", opening a heavily bleeding wound"
            });

            others_msg = ({
                QCTNAME(archer) + " rapidly draws "
                + LANG_ADDART(arrow->singular_short()) + " to "
                + archer->query_possessive() + " " + bow->short() + " and "
                + "shoots accurately at " + QTNAME(enemy) + ", who staggers "
                + "when the arrow lances through " + enemy->query_possessive()
                + " " + hdesc + ", opening a heavily bleeding wound"
            });

                break;
            default:

            if (enemy->query_humanoid())
            {
                archer_msg = ({
                    "You rapidly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot " + QTNAME(enemy) + " through the neck who "
                    + "falls to the ground, desperately clutching "
                    + enemy->query_possessive() + " throat",
                });

                enemy_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots you through the neck and you fall to the "
                    + "ground, desperately clutching your throat",
                });

                others_msg = ({
                    QCTNAME(archer) + " rapidly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots " +  QTNAME(enemy) + " through the neck. "
                    + capitalize(enemy->query_pronoun()) + " falls to the "
                    + "ground, desperately clutching "
                    + enemy->query_possessive() + " throat",
                });
            }
            else
            {
                archer_msg = ({
                    "You swiftly nock " + LANG_ADDART(arrow->singular_short())
                    + " and shoot at " + QTNAME(enemy) + " with devastating "
                    + "precision. "
                    + capitalize(enemy->query_pronoun()) + " falls to the "
                    + "ground, with an arrow sticking from a mortal wound in "
                    + enemy->query_possessive() + " " + hdesc,
                });

                enemy_msg = ({
                    QCTNAME(archer) + " swiftly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at you with devastating precision. You fall "
                    + "to the ground, with an arrow sticking from a mortal "
                    + "wound in your " + hdesc,
                });

                others_msg = ({
                    QCTNAME(archer) + " swiftly nocks "
                    + LANG_ADDART(arrow->singular_short()) + " "
                    + "and shoots at " + QTNAME(enemy) + " with devastating "
                    + "precision. " + capitalize(enemy->query_pronoun()) + " "
                    + "falls to the ground, with an arrow sticking from a "
                    + "mortal wound in " + enemy->query_possessive() + " "
                    + hdesc,
                });

            }
        }

        archer->catch_msg(archer_msg[0] + ".\n");
        enemy->catch_msg(enemy_msg[0] + ".\n");
        archer->tell_watcher(others_msg[0] + ".\n", enemy);

        /* Calls the hit in the arrow */
        if (dam > 0)
        {
            if (objectp(arrow))
            {
                int max_dmg, prc_dmg, wep_dmg, wep_pen, wep_lev;

                /*
                 * This damage is calculated from the percentual success of the
                 * special and the F_PENMOD on weapons and bow skill. Keep in
                 * mind, this does not add damage unless the arrow itself has a
                 * special that is applied in such a way.
                 */

                max_dmg = calculate_damage(archer, enemy, items, 0, result);
                prc_dmg = dam * 100 / max_dmg;
                wep_pen = calc_base_pen(items);
                wep_lev = archer->query_skill(SS_WEP_MISSILE);
                wep_dmg = F_PENMOD(wep_pen, wep_lev) * prc_dmg / 100;

                arrow->projectile_hit_target(archer, aid, hdesc, phurt, enemy,
                                             dt, phit, wep_dmg, hid);
            }

        }
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(archer);
} /* special_did_hit */

/*
 * Function name:   check_required_items
 * Description:     Does some validation to make sure that the archer has arrows
 * Arguments:       1. (object) actor - The actor of the ability
 *                  2. (mixed *) targets - The targets of the ability
 *                  3. (string) arg - The arguments used
 *                  4. (int) - pretest
 * Returns:         (mixed *) items that are required.
 */
static mixed *
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    mixed   arrow,
            bow;

    if (!objectp(bow = query_wielded_bow(actor)))
        return 0;

    if (!objectp(arrow = bow->query_projectile()) &&
        !objectp(arrow = find_arrows(actor, bow)))
        return 0;

    return ({ bow, arrow });
} /* check_required_items */

/*
 * Function name:   check_valid_action
 * Description:     Perform ability-specific checks
 * Arguments:       1. (object) The player
 *                  2. (mixed *) The targets
 *                  3. (string) Arguments passed to the command
 *                  4. (int) Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
static int
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    if (!::check_valid_action(actor, targets, arg, execute))
        return 0;

    if (SNIPE->query_ability_preparing(actor))
        return 0;

    // If it passes everything, return success
    return 1;
} /* check_valid_action */

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability, object player)
{
    // Don't display any messages
} /* hook_stopped_ability */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     This function is called if the ability is in cooldown,
 *                  displaying a cooldown message.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    // Don't display any messages
} /* hook_special_in_cooldown */

/*
 * Function name:   hook_special_complete
 * Description:     This gets called whenever the special is ready again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_complete()
{
    // Don't display any messages
} /* hook_special_complete */

/*
 * Function name:   hook_already_active
 * Description:     This gets called if the special is already active when the
 *                  actor attempts to use it.
 * Arguments:       (object) ability - The ability being used.
 * Returns:         Nothing
 */
public void
hook_already_active(object ability)
{
    // Don't display any messages
} /* hook_already_active */

/*
 * Function name:   ability_msg
 * Description:     This function displays a message when the ability is being
 *                  activated.
 * Arguments:       None
 * Returns:         Nothing
 */
static void
ability_msg(object actor, mixed *targets, string arg)
{
    // Don't display any messages
} /* ability_msg */
