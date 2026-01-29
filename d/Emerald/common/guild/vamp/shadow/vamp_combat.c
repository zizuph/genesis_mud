/* vamp_combat.c created by Shiva@Genesis.
 * This file contains code related to vampire combat
 * This is a subpart of the vampire guild shadow.
 *
 * Shiva, Jul 28 2004 -- Possibly temporary change, lessening penalty
 * for using slash against armoured hitlocations.
 */

#include "../guild.h"
#include "../voptions.h"
#include "/d/Emerald/sys/skills.h"
#include "/std/combat/combat.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <math.h>
#include <composite.h>

#define COMBAT_ALARM_DELAY 30.0
#define LIVE_M_NO_SLASH  "_live_m_no_slash"
#ifndef NO_FLURRY
#define FLURRY_ATTACK_NUM 4
#define LIVE_M_NO_FLURRY "_live_m_no_flurry"
#endif NO_FLURRY

#define SW shadow_who

static private object enemy;
static private int slash_alarm;
static private int combat_alarm;
static private int celerity_lvl;
#ifndef NO_FLURRY
static private int flurry_alarm;
static private int flurry_reset_alarm;
#endif NO_FLURRY

void do_slash(object target, int hitloc_id);
void desc_slash(int dam, object target, string hit_desc);
int query_celerity();
int humanoid(object ob);

string c_can_attack(object target, string verb)
{
    if (!target || !living(target) || (target == SW))
    {
        return capitalize(verb) + " whom?\n";
    }

    if (QP(target, OBJ_I_NO_ATTACK))
    {
        return "You sense a divine presence protecting the intended victim.\n";
    }

    if (E(target) && QP(E(target), ROOM_I_NO_ATTACK))
    {
        return "Your senses detect a magical peace spell over the room.\n";
    }

    if (!SW->query_npc() && SW->query_met(target) &&
        QP(SW, LIVE_O_LAST_KILL) != target)
    {
        AP(SW, LIVE_O_LAST_KILL, target);
        return "Attack " + target->query_the_name(SW) +
               "?!? Please confirm by trying again.\n";
    }

    if (!F_DARE_ATTACK(SW, target))
    {
        return "You don't dare to attack.\n";
    }
}

void do_combat_checks()
{
    if (!sizeof(SW->query_enemy(-1)))
    {
        remove_alarm(combat_alarm);
        combat_alarm = 0;
        return;
    }

    if (SW->query_attack())
    {
        break_unseen(0, 0);
        add_thirst_random(10);
    }
}

void start_combat_alarm()
{
    if (!combat_alarm)
    {
        combat_alarm = set_alarm(COMBAT_ALARM_DELAY, COMBAT_ALARM_DELAY,
            do_combat_checks);
    }
}

void attack_object(object ob)
{
    SW->attack_object(ob);
    break_unseen(ob, 0);
    start_combat_alarm();
}

void attacked_by(object ob)
{
    SW->attacked_by(ob);
    break_unseen(ob, 0);  
    start_combat_alarm();
}
    
varargs void
vamp_attack(object ob, int force_switch = 1)
{
    if (ob)
    {
        if (force_switch)
        {
            if (ob != SW->query_attack())
            {
                attack_object(ob);
            }
        }
        else
        {
            if (!SW->query_attack())
            {
                attack_object(ob);
            }
            else if (member_array(ob, SW->query_enemy(-1)) == -1)
            {
                ob->attacked_by(SW);
            }
        }

        SW->reveal_me();
    }

    enemy = ob;
}

object query_vamp_attack() { return enemy; }

public int
target_present(object target)
{
    return target && (environment(SW) == environment(target));
}

#ifndef NO_FLURRY
public void
reset_flurry()
{
    flurry_reset_alarm = 0;
    SW->catch_tell("You have recovered from your flurry of attacks.\n");
}

public int
query_flurry_reset()
{
    return !flurry_reset_alarm;
}

mixed query_flurry() 
{ 
    mixed *arr;

    if (!flurry_alarm || !pointerp(arr = get_alarm(flurry_alarm)))
    {
        return 0;
    }

    return arr[4];
}

void exec_flurry(object *targets)
{
    object enemy_ob, target;
    mixed *flurry_attacks = ({});
    int i, j, il, size, hitsuc, tmp, dt, *attack_ids, *dbits, speed;
    mixed *attack, hitresult, pen, why, prop;

    flurry_alarm = 0;

    enemy_ob = SW->query_enemy();

    size = sizeof(targets);
    targets = filter(targets, target_present);

    if (!sizeof(targets))
    {
        SW->catch_tell("Your " + (size == 1 ? "enemy seems" : "enemies seem") +
            " to have slipped away before you could attack.\n");
        return;
    }

    if (QP(SW, LIVE_I_STUNNED))
    {
        SW->catch_tell("You miss your chance to slash at " +
            target->query_the_name(SW) + ".\n");
        return;
    }

    // If the current enemy is among the targets, put him at the front,
    // to be sure he gets hit.
    if (enemy_ob && ((i = member_array(enemy_ob, targets)) != -1))
    {
        object tmp = targets[0];
        targets[0] = targets[i];
        targets[i] = tmp;
    }

    // If there are fewer targets than flurry can hit, we'll simply add
    // multiple entries for the same targets.
    while (sizeof(flurry_attacks) < FLURRY_ATTACK_NUM)
    {
        flurry_attacks += targets;
    }

    // Truncate the attack array, since we might have added too many above
    flurry_attacks = flurry_attacks[..FLURRY_ATTACK_NUM];

    // There are several ways we could handle multiple attack entries for one
    // target. Grouping them with unique_array seems as good as any....
    flurry_attacks = unique_array(flurry_attacks, identity);

    SW->catch_tell("You unleash a flurry of attacks on " +
        FO_COMPOSITE_LIVE(map(flurry_attacks, &operator([])(, 0)), SW) + ".\n");

    speed = ftoi(SW->query_combat_object()->cb_query_speed() + 0.5);

    if (speed <= 0)
    {
        speed = 5;
    }

    speed = speed * 5;

    flurry_reset_alarm = set_alarm(itof(speed), 0.0, reset_flurry);

    // Execute flurry attack(s) on each target
    for (i = 0; i < sizeof(flurry_attacks); i++)
    {
        // All the entries in this array should be the same object, so we'll
        // just pick the first
        target = flurry_attacks[i][0];

        if (stringp(why = c_can_attack(target, "flurry")))
        {
            SW->catch_tell(why);
            continue;
        } 

        if (prop = QP(target, LIVE_M_NO_FLURRY))
        {
            if (stringp(prop))
            {
                SW->catch_msg(prop);
		continue;
             }

            SW->catch_tell("You can't bring yourself to attack " +
                  target->query_the_name(SW) + ".\n");
            continue;
        }


        attack_ids = SW->query_combat_object()->query_attack_id();

        // One or more flurry attacks on this target. This code is more or less straight
        // from /std/combat/cbase.c, so it mimics a standard attack--deviations are noted
        // below.
        for (j = 0; j < sizeof(flurry_attacks[i]); j++)
        {
            il = -1;
            size = sizeof(attack_ids);
            while(++il < size)
            {
                attack = SW->query_combat_object()->query_attack(attack_ids[il]);
                /*
                 * Will we use this attack this round? (random(100) < %use)
                 */
                if (random(100) < attack[ATT_PROCU])
                {
                    /*
                     * The attack has a chance of failing. If for example the attack
                     * comes from a wielded weapon, the weapon can force a fail or
                     * if the wchit is to low for this opponent.
                     */
                    hitsuc = SW->query_combat_object()->cb_try_hit(attack_ids[il]);
                    if (hitsuc <= 0)
                    {
                        continue;
                    }
        
                    /* 
                     * The intended victim can also force a fail. like in the weapon
                     * case, if fail, the cause must produce explanatory text himself.
                     */
                    hitsuc = target->query_not_attack_me(SW, attack_ids[il]);
                    if (hitsuc > 0)
                    {
                        continue;
                    }

                    // use a 'to hit' value more in line with a special attack, rather than
                    // a standard attack    
                    hitsuc = SW->query_combat_object()->cb_tohit(attack_ids[il], 90, target);
        
                    if (hitsuc > 0)
                    {
#if CRITS_ENABLED
                        /* Choose one damage type */
                        if (crit = (!random(10000)))
                        {
                            // Critical hit!
                            pen = attack[ATT_M_PEN];
                            if (sizeof(pen))
                            {
                                pen = pen[0];
                            }
         
//                          if (random(10))
                            {
                                pen *= 5;
                            }
//                          else
//                          {
//                                pen *= 10;
//                                pen += attack_ob->query_max_hp();
//                          }
                        }
                        else
#endif CRITS_ENABLED
                        {
                            pen = attack[ATT_M_PEN];
        
                            if (sizeof(pen))
                            {
                                tmp = MATH_FILE->quick_find_exp(dt);
                                if((tmp < sizeof(pen)))
                                    pen = pen[tmp];
                                else
                                    pen = pen[0];
                            }
                        }
        
                        dt = attack[ATT_DAMT];
                        dbits = ({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({0});
                        dt = sizeof(dbits) ? one_of_list(dbits) : W_BLUDGEON;
        
                        hitresult = (mixed*)target->hit_me(pen, dt, SW, attack_ids[il]);
                    }
                    else
                    {
                        hitresult = 
                            (mixed*)target->hit_me(hitsuc, 0, SW, attack_ids[il]);
                    }
        
                    /*
                     * Generate combat message, arguments Attack id, hitloc description
                     * proc_hurt, Defender
                     */
                    if (hitsuc > 0)
                    {
                        hitsuc = attack[ATT_WCPEN][tmp];
                        if (hitsuc > 0)
                        {
                            hitsuc = 100 * hitresult[2] / hitsuc;
                        }
                        else
                        {
                            hitsuc = 0;
                        }
                    }
                    if (hitresult[1])
                    {
                        SW->query_combat_object()->cb_did_hit(attack_ids[il], hitresult[1], hitresult[4], hitresult[0], 
                               target, dt, hitsuc, hitresult[3]);
                    }
                    else
                    {
                        break; /* Ghost, linkdeath, immortals etc */
                    }
        
                    /* Oops, Lifeform turned into a deadform. Reward the killer. */
                    if ((int)target->query_hp() <= 0)
                    {
                        target->do_die(SW);
                        break;
                    }
                }
            }
        }
    }
}

public void
flurry(object *targets)
{
    int speed;

    map(targets, &vamp_attack(, 0));

    if (flurry_alarm)
    {
        remove_alarm(flurry_alarm);
    }

    speed = ftoi(SW->query_combat_object()->cb_query_speed() + 0.5);

    if (speed <= 0)
    {
        speed = 5;
    }

    speed = speed * 5;

    flurry_alarm = 
        set_alarm(itof(speed), 0.0, &exec_flurry(targets));
    
}

#endif NO_FLURRY

/* Start the "slash" special attack.  This has been moved into the
 * shadow to avoid problems when the soul is updated.
 */
void slash(object target, int hitloc)
{
    int speed;

    vamp_attack(target);
    
    if (slash_alarm)
    {
        remove_alarm(slash_alarm);
    }

    speed = ftoi(SW->query_combat_object()->cb_query_speed() + 0.5);

    if (speed <= 0)
    {
        speed = 5;
    }

    speed = speed + random(speed * 2); //average speed of speed * 2;

    slash_alarm = 
        set_alarm(itof(speed), 0.0, &do_slash(target, hitloc));
}

void do_slash(object target, int hitloc_id)
{
    string why, hit_desc;
    object attacker_combat_ob, armour, right, left, ob;
    int hitsuc, phit, hit;
    mixed *target_hitloc, prop, ac, *hit_res;
    int pen;

    slash_alarm = 0;
    vamp_attack(0);

    if (!SW)
    {
        return;
    }

    if (SW->query_npc())
    {
        set_alarm(0.0, 0.0, &SW->ready_to_slash());
    }

    /* make checks to be sure we can still attack */

    if (!target || (environment(SW) != environment(target)))
    {
        SW->catch_tell("Your enemy seems to have slipped away " +
            "before you could slash.\n");
        return;
    }

    if (prop = QP(target, LIVE_M_NO_SLASH))
    {
        if (stringp(prop))
        {
            SW->catch_msg(prop);
            return;
        }

        SW->catch_tell("You can't bring yourself to slash " +
            "at " + target->query_the_name(SW) + ".\n");
        return;
    }

    if (QP(SW, LIVE_I_STUNNED))
    {
        SW->catch_tell("You miss your chance to slash at " +
            target->query_the_name(SW) + ".\n");
        return;
    }

    if (target->query_not_attack_me(this_player(), -1))
    {
        SW->catch_tell("You can't manage to slash at " +
            target->query_the_name(SW) + ".\n");
        return;
    }

    if (stringp(why = c_can_attack(target, "slash")))
    {
        SW->catch_tell(why);
        return;
    }

    attacker_combat_ob = SW->query_combat_object();
    if (pointerp(target_hitloc = 
        target->query_combat_object()->query_hitloc(hitloc_id)))
    {
        phit = target_hitloc[HIT_PHIT];
    }
    else
    {
        setuid();
        seteuid(getuid());
        log_file("vamp_slash_bad_hitloc", ctime(time()) + " " + MASTER_OB(target) + " hitloc id: " + hitloc_id + "\n");
        return;
    }

    /* hitlocs w/ a lower % hit are harder to hit */
    hit = MAX(85, 155 - (100 - phit));

    /* reduce hit if SW has wielded weapons or worn shields */
    right = SW->query_tool(W_RIGHT);
    left  = SW->query_tool(W_LEFT);

    if (right && left)
    {
        SW->catch_tell("You have too many things in your hands to slash " +
            "at " + target->query_the_name(SW) + ".\n");
        return;
    }

    if (ob = (right || left))
    {
        hit = min(hit * (100 - (ob->query_prop(OBJ_I_WEIGHT) / 600)) / 100,
                  hit * (100 - (ob->query_prop(OBJ_I_VOLUME) / 300)) / 100);
    }
  
    /* Test to see if we hit the target and apply damage if so. */
    if (phit && ((hitsuc = attacker_combat_ob->cb_tohit(-1, hit, target)) > 0))
    {
        // hit!  

        /* We have this issue with npcs that have "built-in" armour values,
         * which are more frequently done to toughen up npcs than to 
         * reflect any real inherent armour.  Of course, npcs do exist with
         * such armour (dragons, for instance).  This is a rather arbitrary
         * solution to this issue:  if the target is humanoid and the
         * hitloc is not protected by a proper armour, we do damage as if
         * the area were unarmoured; otherwise, the ac is taken into
         * account normally.
         */
        if (!humanoid(target) && !target->query_armour(hitloc_id))
        {
            ac = target_hitloc[HIT_AC];
            if (sizeof(ac) && (1 < sizeof(ac)))
            {
                ac = ac[1];
            }
            else if (sizeof(ac))
            {
                ac = ac[0];
            }
            else if (!intp(ac))
            {
                ac = 0;
            }
        }
        else if (armour = target->query_armour(hitloc_id))
        {
            ac = armour->query_ac(hitloc_id) + armour->query_am(hitloc_id)[1];
        }
        else
        {
            ac = 0;
        }

        pen = MIN(150, STR(SW)) / 3 + 
              MIN(150, DEX(SW)) * 7 / 5 + 
              SW->query_skill(SS_VAMP_SLASH) * 3 / 2;

        pen = (random((query_celerity() ? 200 : 100) < ac) ? pen * 4 / 5 : pen);
        hit_res = target->hit_me(pen, W_SLASH, SW, -1, hitloc_id);
    }
    else
    {
        // miss!
        hit_res = target->hit_me(hitsuc, 0, SW, -1);
    }

    if (!pointerp(hit_res))
    {
        setuid();
        seteuid(getuid());
        log_file("vamp_slash_bad_hit_me", ctime(time()) + " " + MASTER_OB(target) + "\n");
        return;
    }

    /* apply fatigue */
    if (SW->query_fatigue() > 2)
    {
        SW->add_fatigue(-3);
    }
    else
    {
        SW->set_fatigue(0);
        SW->heal_hp(-3);
    }

    SW->add_attack_delay(random(3));

    /* Give some nice messages */

    hit_desc = target_hitloc[HIT_DESC];
    if (hit_res[0] >= 0)
    {
        SW->add_panic(-3 - hit_res[3] / 5);

        desc_slash(hit_res[3], target, hit_desc);

        /* Kill the target if hps are <= 0 */
        if (target->query_hp() <= 0)
        {
            target->do_die(SW);
        }
    }
    else
    {
        desc_slash(-1, target, hit_desc);
    }
}

void desc_slash(int dam, object target, string hit_desc)
{
    string *how;
    int brief = query_vamp_option(VOPT_BRIEF_ATTACKS);
    int inter = interactive(target);
    object *watchers, *brief_watchers;

    watchers = FILTER_LIVE(all_inventory(environment(SW))) - ({ SW });
    brief_watchers = filter(watchers, &operator(!=)(0) @
        &->query_vamp_option(VOPT_BRIEF_ATTACKS));
    watchers -= brief_watchers;


    if (dam < 0)
    {
        /* if we get here, then the SW has missed completely */

        // add some panic
        SW->add_panic(1);
        // add some extra time for recovery
        SW->add_attack_delay(random(5) + 2, 0);
  
        if (brief)
        {
            SW->catch_tell("You slash your enemy but miss.\n");
        }
        else
        {
            SW->catch_tell("You slash at the " + hit_desc + " of " +
                target->query_the_name(SW) + " with your claws but miss.\n");
        }

        if (inter)
        {
            target->catch_tell(SW->query_The_name(target) + " slashes at " +
                "your " + hit_desc + " with " + POS(SW) + " claws but " +
                "misses.\n");
        }

        SW->tell_watcher(QCTNAME(SW) + " slashes at the " +
            hit_desc + " of " + QTNAME(target) + " but misses.\n", target,
            brief_watchers);

        if (sizeof(brief_watchers))
        {
            SW->tell_watcher(QCTNAME(SW) + " slashes at " + POS(SW) + 
                " enemy, but misses.\n", target, watchers);
        }
        return;
    }

    if (dam == 0)
    {    
        if (brief)
        {
            SW->catch_tell("You slash your enemy, but the attack doesn't " +
                "even break the skin.\n");
        }
        else
        {
            SW->catch_tell("You slash at " + 
                target->query_the_possessive_name(SW) + " " + hit_desc +
                ", but your attack doesn't even break the skin.\n");
        }

        if (inter)
        {
            target->catch_tell(SW->query_The_name(target) + " slashes " +
                "at your " + hit_desc + " with " + POS(SW) +
                " claws, but the attack doesn't even break the skin.\n");
        }

        SW->tell_watcher(QCTNAME(SW) + " slashes at " +
            QTNAME(target) + "'s " + hit_desc + " with " + POS(SW) +
            " claws, but the attack doesn't even break the skin.\n",
            target, brief_watchers);

        if (sizeof(brief_watchers))
        {
            SW->tell_watcher(QCTNAME(SW) + " slashes at " + POS(SW) +
                " enemy, but the attack doesn't even break the skin.\n",
                target, watchers);
        }

        return;
    }

    how = ({
               ({ "scratch", "scratches", "scratching" }),
               ({ "rake", "rakes", "raking" }),
               ({ "slash", "slashes", "slashing" }),
               ({ "gash", "gashes", "slashing" }),
               ({ "rend", "rends", "rending" }),
           })[MIN(4, dam / 20)];
    /*
Miss
Scratch
Rake
Slash
Gouge
Gash
Tear
Rend
Shred
*/

    if (brief)
    {
        SW->catch_tell("You " + how[0] + " your enemy with your claws.\n");
    }

    switch (random(6))
    {
        case 0:
            if (!brief)
            {
                SW->catch_tell("You rush by " + 
                    target->query_the_name(SW) + ", your extended " +
                    "claws " + how[2] + " " + POS(target) + " " + hit_desc +
                    ".\n");
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) + " rushes " +
                    "by you, " + POS(SW) + " extended claws " + how[2] +
                    " your " + hit_desc + ".\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " rushes by " +
                QTNAME(target) + ", " + POS(SW) + " extended claws " +
                how[2] + " " + POS(target) + " " + hit_desc + ".\n", target,
                brief_watchers);

            break;
        case 1:
            if (!brief)
            {
                SW->catch_tell("You leap within " +
                    target->query_the_name(SW) + "'s defences, savagely " +
                        how[2] + " " + POS(target) + " " + hit_desc + ".\n");
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) + " leaps " +
                    "your defences, savagely " + how[2] + " your " + hit_desc +
                    ".\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " leaps within " +
                QTNAME(target) + "'s defences, savagely " + how[2] + " " +
                POS(target) + " " + hit_desc + ".\n", target, brief_watchers);
            break;
        case 2:
            if (!brief)
            {
                SW->catch_tell("You " + how[0] + " the " + hit_desc + 
                    " of " + target->query_the_name(SW) + 
                    " with a lightning cross-slash.\n");
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) + " " +
                    how[1] + " your " + hit_desc + " with a lightning " +
                    " cross-slash.\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " " + how[1] +
                " the " + hit_desc + " of " + QTNAME(target) +
                " with a lightning cross-slash.\n", target, brief_watchers);
            break;
        case 3:
            if (!brief)
            {
                SW->catch_tell("You duck low and savagely slash upwards, " +
                    how[2] + " " + target->query_the_name(SW) + "'s " +
                    hit_desc + ".\n");
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) + 
                    " ducks low and savagely slashes upwards, " + how[2] +
                    " your " + hit_desc + ".\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " ducks low and " +
                "savagely slashes upwards, " + how[2] + " " + QTNAME(target) +
                "'s " + hit_desc + ".\n", target, brief_watchers);
            break;
        case 4:
            if (!brief)
            {
                SW->catch_tell("You dodge to the side and " + how[0] +
                    " the " + hit_desc + " of " + target->query_the_name(SW) +
                    " with a spinning slash.\n", brief_watchers);
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) +
                    " dodges to the side and " + how[1] + " your " +
                    hit_desc + " with a spinning slash.\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " dodges to the " +
                "side and " + how[1] + " the " + hit_desc + " of " +
                QTNAME(target) + " with a spinning slash.\n", target,
                brief_watchers);
            break;
        case 5:
            if (!brief)
            {
                SW->catch_tell("You leap ferociously upon " + 
                    target->query_the_name(SW) + " and " + how[0] +
                    " " + POS(target) + " " + hit_desc + " with a powerful " +
                    "scissor-slash.\n");
            }

            if (inter)
            {
                target->catch_tell(SW->query_The_name(target) +
                    " leaps ferociously upon you and " + how[1] + " your " +
                    hit_desc + " with a powerful scissor-slash.\n");
            }

            SW->tell_watcher(QCTNAME(SW) + " leaps ferociously " +
                "upon " + QTNAME(target) + " and " + how[1] + " " +
                POS(target) + " " + hit_desc + " with a powerful scissor-" +
                "slash.\n", target, brief_watchers);
             break;
        default:
             SW->catch_tell("BUG!\n");
             break;
    }

    if (sizeof(brief_watchers))
    {
        SW->tell_watcher(QCTNAME(SW) + " " + how[1] + " " + POS(SW) +
            " enemy with " + POS(SW) + " claws.\n", target, watchers);
    }
}

// is ob a humanoid?
int humanoid(object ob)
{
    return ob->query_humanoid();
}
    
mixed query_slash() 
{ 
    mixed *arr;

    if (!slash_alarm || !pointerp(arr = get_alarm(slash_alarm)))
    {
        return 0;
    }

    return arr[4];
}

int set_celerity(int lvl)
{
    int prop;
 
    if (celerity_lvl && !lvl)
    {
	/* Changed from 50 to 100 to compensate for taxed combat aid loss due
	 * to quickness changes */
        prop = -100;
    }
    else if (!celerity_lvl && lvl)
    {
        /* Changed from 50 to 100 to compensate for taxed combat aid loss due
         * to quickness changes */
	prop = 100;
    }
    else
    {
        celerity_lvl = lvl;
        return 0;
    }

    CP(SW, LIVE_I_QUICKNESS, prop);
    SW->query_combat_object()->cb_update_speed();
    celerity_lvl = lvl;
    return 1;
}

int query_celerity()
{
    return celerity_lvl;
}  

int query_not_attack_me(object attacker, int att_id)
{
    if (random(100) < celerity_lvl)
    {
        attacker->catch_tell(SW->query_the_name(attacker) + 
            " is moving with such celerity that you miss your chance to " +
            "strike at " + OBJ(SW) + ".\n");
        return 1;
    }

    return SW->query_not_attack_me(attacker, att_id);
}

int special_damage(int aid, string hdesc, int phurt, object enemy, int phit,
    int dam)
{
    int hurt, res, fire_dam;
    string with, where, how, what, owhat;

    SW->add_panic(-3 - (phurt / 5));
  
    /* give an attack description */
    with = "claws";
  
    where = " the " + hdesc + " of ";
  
    switch (phurt)
    {
      case 0..4:
          how = "";
          what = "tickle";
          owhat = "tickles";
          break;
      case 5..9:
          how = "";
          what = "graze";
          owhat = "grazes";
          break;
      case 10..19:
          how = "";
          what = "hurt";
          owhat = "hurts";
          break;
      case 20..29:
          how = ", rather bad";
          what = "hurt";
          owhat = "hurts";
          break;
      case 30..49:
          how = ", very bad";
          what = "hurt";
          owhat = "hurts";
          break;
      case 50..69:
          how = ", very hard";
          what = "smash";
          owhat = "smashes";
          break;
      case 70..89:
          how = ", with a bone crushing sound";
          what = "smash";
          owhat = "smashes";
          where = " ";
          break;
      default:
          how = "";
          what = "massacre";
          owhat = "massacres";
          where = " ";
    }
  
    SW->catch_tell("You " + what + where + enemy->query_the_name(SW) +
        " with your " + with + how + ".\n");
  
    if (interactive(enemy))
    {
        enemy->catch_tell(SW->query_The_name(enemy) + " " + owhat + 
            " your " + hdesc + " with " + SW->query_possessive() + " " +
            with + how + ".\n");
    }
  
    SW->tell_watcher(QCTNAME(SW) + " " + 
        owhat + where + QTNAME(enemy) + " with " + 
        SW->query_possessive() + " " + with + how + ".\n", enemy);
  
    return 1;
}

int cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    if (!query_vamp_option(VOPT_VAMP_ATTACKS) || random(5))
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    if ((phurt >= 0) && (aid & W_BOTH) && !SW->query_weapon(aid) &&
        special_damage(aid, hdesc, phurt, enemy, phit, dam))
    {
        return 1;
    }

    return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    SW->cr_got_hit(hid, ph, att, aid, dt, dam);

    if (dam > 50)
    {
        break_unseen(att, dam);
    }
}
