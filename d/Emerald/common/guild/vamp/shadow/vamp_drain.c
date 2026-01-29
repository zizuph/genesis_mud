/* Changes
 * 
 * 2005-10-11 - Cotillion
 * - Modified vdrain success to take current thirst into account,
 *   we're having problems with vamps draining huge npcs to death.
 *   The randomness of the success has been decreased a bit also.
 *   And the stat weight of the enemy increased.
 *
 * Lucius, Dec 2007: Disabled drain.log, not needed at present.
 */

#include "../guild.h"
#include "../voptions.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <language.h>
#include <tasks.h>

#define SW shadow_who

#define DRAIN_HP        60
#define DRAIN_MANA       5
#define DRAIN_FATIGUE    2
#define DRAIN_INTERVAL 2.0

#define DRINK_HP        75
#define DRINK_MANA       5
#define DRINK_FATIGUE    2
#define DRINK_INTERVAL 2.0

#define LIVE_M_NO_DRAIN "_live_m_no_drain"

#define DRAINER_SUBLOC "drainer_subloc"
#define DRAINEE_SUBLOC "drainee_subloc"

#define MYRAND(x) ((random(x) + random(x) + random(x) + random(x)) / 4)

#if 0
#define DRAIN_LOG(x) \
   setuid(); \
   seteuid(getuid()); \
   write_file(VAMP_LOG_DIR + "drain.log", x + "\n")
#else
#define DRAIN_LOG(x)
#endif

static int drain_alarm, times, vstat_mod, past_death;
static object drainee;

void recover_from_throw(string name);
void recover_from_miss(string name);
void do_vamp_drink();
void do_vamp_drain();
void release_vamp_drainee(int silent);
void desc_vamp_drink();
void desc_vamp_drain();
int query_vamp_drainer_success();
int query_vamp_drainee_success();
void drain_vampire();
void do_drain_past_death();

varargs void
tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}

public object
query_vamp_drain()
{
    return drainee;
}

/* Called when a vampire should be unwillingly stopped from
 * draining (eg. the vampire has been attacked)
 */
void 
break_vamp_drain()
{
    if (!drainee)
    {
        return;
    }

    SW->catch_tell(drainee->query_The_name(SW) + " breaks free from " +
        "your grip, sending you staggering back, half dazed.\n");
    drainee->catch_tell("You break free from " +
        LANG_POSS(SW->query_the_name(drainee)) + " grip.\n");
    tell_others(QCTNAME(drainee) + " breaks free from " +
        QTPNAME(SW) + " grip.\n", ({ SW, drainee }));

    SW->add_stun();
    set_alarm(itof(6 + random(8)), 0.0,
        &recover_from_throw(drainee->query_the_name(SW)));
        
    release_vamp_drainee(1);
}

int
can_vamp_drink(object drainer, object drainee)
{
    mixed prop;
    object *livings;
    int i;

#if 0
    if (QP(drainee, LIVE_I_STUNNED))
    {
        drainee->catch_tell("You can't manage to drain " +
            drainee->query_the_name(drainer) + ".\n");
        return 1;
    }
#endif
  
    if (prop = QP(drainer, LIVE_M_MOUTH_BLOCKED))
    {
        drainer->catch_msg(stringp(prop) ? prop : "Your mouth is blocked\n");
        return 0;
    }
  
    if (prop = QP(drainee, LIVE_M_NO_DRAIN))
    {
        drainer->catch_msg(stringp(prop) ? prop : "You can't seem to manage " +
            "to drain " + drainee->query_the_name(drainee) + ".\n");
        return 0;
    }
  
    /* We can't drain if anyone other than the target
     * is currently attacking us.
     */
    livings = FILTER_OTHER_LIVE(all_inventory(drainer) - ({ drainee, drainer }));
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainer)
        {
            drainer->catch_msg("You can't drain from " + 
            drainee->query_the_name(drainer) + " while others are fighting " +
                "you.\n");
            return 0;
        }
    }
  
    /* Don't continue if the target is in combat */
    for (i = 0; i < sizeof(livings); i++)
    {
        if (livings[i]->query_attack() == drainee)
        {
            drainer->catch_msg("You can't drain from " + 
                drainee->query_the_name(drainer) +
                " while others are fighting " + OBJ(drainee) + ".\n");
            return 0;
        }
    }

    return 1;
}

void
start_vamp_drink(object who)
{
    who->add_prop(LIVE_O_VAMP_DRAINER, SW);
    drainee = who;

    if (drain_alarm)
    {
        remove_alarm(drain_alarm);
    }

    vstat_mod = 0;
    past_death = 0;

    drain_alarm = set_alarm(DRINK_INTERVAL, DRINK_INTERVAL, do_vamp_drink);

    setuid();
    seteuid(getuid());

    drainee->add_subloc(DRAINEE_SUBLOC, this_object());
    SW->add_subloc(DRAINER_SUBLOC, this_object());

    /* paralyze drainer and drainee */
    COTO(VAMP_OBJ_DIR + "bitten_paralysis", drainee);
    COTO(VAMP_OBJ_DIR + "biter_paralysis", SW);
  
    /* add bite marks to the drainee */
    if (!present("_vamp_bite_mark", drainee) && !IS_MEMBER(drainee))
    {
        COTO(VAMP_OBJ_DIR + "bite_mark", drainee);
    }
}

public void
do_vamp_drink()
{
    object drainer = SW;

    if (!drainer || !drainee || 
        (environment(drainer) != environment(drainee)))
    {
        release_vamp_drainee(1);
        return;
    }

    if (!can_vamp_drink(drainer, drainee))
    {
        release_vamp_drainee(0);
        return;
    }

    if (drainee->query_prop(LIVE_I_NO_BODY) ||
        drainee->query_prop("_live_i_no_blood"))
    {
        drainer->catch_tell(drainee->query_The_name(drainer) +
          " doesn't seem to have any blood!\n");
        release_vamp_drainee(0);
        return;
    }

    if (drainee->query_prop(LIVE_I_UNDEAD) && !IS_MEMBER(drainee))
    {    
        drainer->catch_tell(LANG_POSS(drainee->query_The_name()) + 
            " blood tastes bitter in your mouth.  You try to swallow " +
            "it down, but your stomache churns and rejects it.\n");
        release_vamp_drainee(0);

        drainer->command("$spit");

        return;
    }

    if (times++ > (3 + random(3)))
    {
        times = 0;
    }

    if (drainee->query_hp() > DRAIN_HP)
    {
#ifdef DRAIN_SHADOW
        if (!drainee->query_vamp_drain_shadow())
        {
            clone_object(VAMP_SHADOW_DIR + "drain_sh")->shadow_me(drainee);
        }
#endif

        if (!times)
        {
            desc_vamp_drink();
        }
  
        drink_blood(1);

#ifdef DRAIN_SHADOW  
        drainee->drain_me();
#endif
        drainee->heal_hp(-DRINK_HP);
        drainee->add_mana(-DRINK_MANA);
        drainee->add_fatigue(-DRINK_FATIGUE);
  
        if (IS_MEMBER(drainee))
        {
            drain_vampire();
        }

        return;
    }
    
    release_vamp_drainee(0);
}

public void
desc_vamp_drink()
{
    object drainer = SW;
    string blood_desc;

    switch (drainee->query_hp() / 30)
    {
        case 0:
            blood_desc = "barely trickles onto your tongue";
            break;
        case 1..2:
            blood_desc = "flows slowly into your mouth";
            break;
        case 3..5:
            blood_desc = "streams steadily into your mouth";
            break;
        default:
            blood_desc = "gushes in a torrent down your throat";
            break;
    }
      
    drainee->catch_tell(({
        "Your vision fades, and you are momentarily plunged " +
            "into darkness.\nYour vision suddenly returns " +
            "with perfect clarity.\n",
        "Bright colors swirl before your eyes.\n",
        "The sound of " + LANG_POSS(drainer->query_the_name(drainee)) +
            " heart beating in sync with your own echos " +
            "through your mind.\n",
        "You feel " + LANG_POSS(drainer->query_the_name(drainee)) +
            " hot breath blasting against your neck like " +
            "flames licking at your skin.\n",
        "Your skin tingles with energy.\n",
        "With each slowing heartbeat you are tossed from " +
            "perfect clarity of mind to an utter stupor..." + 
            "from " +
            "extreme to extreme with seemingly no median.\n",
        "Adrenaline pumps through your body, electrifying " +
            "and exhilarating you.\n",
        "Violent chills race through your bones.\n",
        "You break out in a sweat as you are ravaged by " +
            "intense hot flashes.\n",
        "Images pass through your thoughts...memories dear " +
            "and long forgotten.\n",
        })[random(10)]);
    tell_room(({
        "A thin stream of blood trickles down " + QTPNAME(drainee) +
            " neck.\n",
        QCTNAME(drainer) + " looks up for a moment, licks the blood " +
            "from his lips, and continues to feed on " + QTNAME(drainee) + 
            ".\n",
        QCTNAME(drainee) + " lets out a soft moan of ecstacy.\n",
        QCTNAME(drainee) + " clutches at " + QTPNAME(drainer) + " " +
            "clothing, pulling " + POS(drainer) + " closer.\n",
        QCTNAME(drainee) + " opens " + POS(drainee) + " eyes for a moment, " +
            "apparently lost in overwhelming sensations.\n",
        QCTPNAME(drainee) + " eyelids flutter.\n",
        })[random(6)], ({ drainer, drainee }));

    drainer->catch_tell(LANG_POSS(drainee->query_The_name(drainer)) +
        " blood " + blood_desc + ".\n");
}

void
release_vamp_drainee(int silent)
{
    object ob, drainer = SW;

    drainer->remove_subloc(DRAINER_SUBLOC);
    
    while (ob = present("_vamp_biter_paralysis", drainer))
    {
        ob->remove_object();
    }

    if (drainee)
    {
        drainee->remove_prop(LIVE_O_VAMP_DRAINER);
        drainee->remove_subloc(DRAINEE_SUBLOC);
    
        while (ob = present("_vamp_bitten_paralysis", drainee))
        {
            ob->remove_object();
        }
    }

    remove_alarm(drain_alarm);
    drain_alarm = 0;

    if (!silent && drainee)
    {
        drainer->catch_tell("You release " +
            drainee->query_the_name(drainer) + " from your embrace.\n");
        drainee->catch_tell(drainer->query_The_name(drainee) +
            " releases you from " + POS(drainer) + " embrace.\n");

        if (vstat_mod < 0)
        {
            drainee->catch_tell("You feel" + 
                ({ " slightly ",
                   " somewhat ",
                   " ",
                   " very ",
                   " extremely " })[min(4, -vstat_mod / 5)] +
                   "weakened.\n");
        }

#if 0
        if (combat)
        {
            drainer->tell_watcher(QCTNAME(drainer) + " releases " + 
                QTNAME(drainee) + " from " + POS(drainer) + " embrace.\n", 
                drainee);
        }
        else
#endif
        {
            tell_others(QCTNAME(drainer) + " releases " + QTNAME(drainee) +
                " from " + POS(drainer) + " embrace.\n",
                ({ drainee, drainer }));
        }
    }

    vstat_mod = 0;
    past_death = 0;
    drainee = 0;
}

int
can_vamp_drain(object drainer, object drainee)
{
    if (drainer->query_attack() != drainee)
    {
        drainer->catch_tell("You are no longer attacking " + 
            drainee->query_the_name(drainer) + ".\n");
        return 0;
    }

    return 1;
}

void
start_vamp_drain(object who)
{
    object right, left;
    string drainee_name, drainer_name;
    int hitsuc, hit;

    vstat_mod = 0;
    past_death = 0;
    hit = 70;
  
    /* Items in either hand make it harder to grab an opponent */
  
    right = SW->query_tool(W_RIGHT);
    left  = SW->query_tool(W_LEFT);
  
    if (right && left)
    {  
        hit -= 55;
    }
    else if (right || left)
    {
        hit -= 30;
    }
  
    drainee_name = who->query_the_name(SW);
    drainer_name = SW->query_the_name(who);
  
    /* Test here to see if the attacker can grab the opponent.  We use
     * the standard cb_tohit to calculate this.
     */
    if ((hitsuc = 
        SW->query_combat_object()->cb_tohit(-1, hit, who)) <= 0)
    {
        /* attacker was unable to grab the target */
  
        SW->tell_watcher(QCTNAME(SW) + " leaps at " + 
            QTNAME(who) + ", grappling with " + OBJ(who) + ";\n" +
            QTNAME(who) + " manages to break free from " + 
            QTNAME(SW) + "'s grip, though.\n", who);
        SW->catch_tell("You leap at " + drainee_name + 
            ", but " +  PRO(who) + " manages to avoid your grasp.\n");
        who->catch_tell(capitalize(drainer_name) + " leaps at you, " +
            "but you manage to avoid " + POS(SW) + " grasp.\n");
    
        /* drainer is stunned immediately for four seconds. */
        SW->add_stun();
        set_alarm(6.0, 0.0, &recover_from_miss(drainee_name));
    
        SW->add_fatigue(-3);
        release_vamp_drainee(1);
        return;
    }
  
    /* Attacker has managed to grab the opponent */
  
    SW->tell_watcher("Moving at a blinding pace, " +
        QTNAME(SW) + " leaps at " + QTNAME(who) +
        ", viciously tearing into " + POS(who) + " flesh with " +
        "claws and fangs.\n", who);
    who->catch_tell("Moving at a blinding pace, " +
        drainer_name + " leaps at you, " +
        "tearing into your flesh with claws and fangs.\n");
    SW->catch_tell("With all your speed, you leap at " +
        drainee_name + ", ferociously tearing " +
        "at " + POS(who) + " flesh with your claws and fangs.\n");
  
    who->add_prop(LIVE_O_VAMP_DRAINER, SW);
    drainee = who;

    if (drain_alarm)
    {
        remove_alarm(drain_alarm);
    }

    drain_alarm = set_alarm(DRAIN_INTERVAL, DRAIN_INTERVAL, do_vamp_drain);

    drainee->attack_object(SW);

    setuid();
    seteuid(getuid());

    drainee->add_subloc(DRAINEE_SUBLOC, this_object());
    SW->add_subloc(DRAINER_SUBLOC, this_object());

    /* paralyze drainer and drainee */
    COTO(VAMP_OBJ_DIR + "bitten_paralysis", drainee);
    COTO(VAMP_OBJ_DIR + "biter_paralysis", SW);
  
    /* add bite marks to the drainee */
    if (!present("_vamp_bite_mark", drainee) && !IS_MEMBER(drainee))
    {
        COTO(VAMP_OBJ_DIR + "bite_mark", drainee);
    }
}

public void
do_vamp_drain()
{
    object drainer = SW, tmp;
    mixed diff;

    if (!drainer || !drainee || 
        (environment(drainer) != environment(drainee)))
    {
        release_vamp_drainee(1);
        return;
    }

    if (!can_vamp_drain(drainer, drainee))
    {
        release_vamp_drainee(0);
        return;
    }

    drainer->add_fatigue(-1);

    DRAIN_LOG("=========================\n" + ctime(time()) + "\n");

    if (query_vamp_drainer_success() < query_vamp_drainee_success())
    {
        break_vamp_drain();
        return;
    }

    if (drainee->query_prop(LIVE_I_NO_BODY) ||
        drainee->query_prop("_live_i_no_blood"))
    {
        drainer->catch_tell(drainee->query_The_name(drainer) +
          " doesn't seem to have any blood!\n");
        release_vamp_drainee(0);
        return;
    }

    if (drainee->query_prop(LIVE_I_UNDEAD) && !IS_MEMBER(drainee))
    {    
        drainer->catch_tell(drainee->query_The_name() + "'s blood tastes " +
            "bitter in your mouth.  You try to swallow it down, but your " +
            "stomache churns and rejects it.\n");
        release_vamp_drainee(0);

        drainer->command("$spit");

        return;
    }

    if (times++ > (3 + random(3)))
    {
        times = 0;
    }

#ifdef DRAIN_SHADOW
    if (!drainee->query_vamp_drain_shadow())
    {
        clone_object(VAMP_SHADOW_DIR + "drain_sh")->shadow_me(drainee);
    }
#endif

    if (!times)
    {
        desc_vamp_drain();
    }

    if (random(5))
    {
        drink_blood(1);
    }
  
#ifdef DRAIN_SHADOW  
    drainee->drain_me();
#endif
    drainee->heal_hp(-DRAIN_HP);
    drainee->add_mana(-DRAIN_MANA);
    drainee->add_fatigue(-DRAIN_FATIGUE);

    if (IS_MEMBER(drainee))
    {
        drain_vampire();
    }

    if (drainee->query_hp() <= 0)
    {
        diff = itof(thirst()) / 10.0;
        diff = TASK_SIMPLE + ftoi(pow(diff, 3.0));

        if (past_death || (!IS_MEMBER(drainee) &&
                ((drainer->resolve_task(diff, ({ TS_DIS, TS_DIS })) <= 0) ||
                    (random(6000) < (thirst() - 10)))))
        {
            do_drain_past_death();
            return;
        }

        drainer->catch_tell("You feel " + 
            LANG_POSS(drainee->query_the_name(drainer)) +
            " heartbeat slowing, weakening....  You release " +
            OBJ(drainee) + " from your embrace just as " + POS(drainee) +
            " heart faintly pulses one last time, and death glazes " +
            POS(drainee) + " eyes.  " + capitalize(POS(drainee)) +
            " limp body slips to the ground in a heap at your feet.\n");
        tell_others(QCTNAME(drainer) + " releases " + QTNAME(drainee) +
            " from " + POS(drainer) + " embrace, letting " + POS(drainee) +
            " lifeless corpse slip to the ground in a heap at " +
            POS(drainer) + " feet.\n", ({ drainer, drainee }));

        tmp = drainee;
        release_vamp_drainee(1);
        tmp->do_die(drainer); 
    }
}

int
query_vamp_drainer_success()
{
    object drainer = SW;
    int drainer_success, left, right;
    int gen_diff;

    DRAIN_LOG(sprintf("\nDrainer: %-11s STR: %-3d DEX: %-3d", 
        drainer->query_real_name(), drainer->query_stat(SS_STR), 
        drainer->query_stat(SS_DEX)));
 
    /* base success is a random number based on dex and str */
    drainer_success = drainer->find_drm(({ TS_DEX, TS_STR }));

    drainer_success += random(400) - random(400);

    DRAIN_LOG("Base success: " + drainer_success);

    /* A sire receives a very large bonus */
    if (drainee->query_sire() == drainer->query_real_name())
    {
        drainer_success += 500;
        DRAIN_LOG("Sire bonus: 500");
    }

    if ((gen_diff = drainee->query_vamp_generation() - drainer->query_vamp_generation()) > 0)
    {
        drainer_success += gen_diff * 15;
    }

    /* subtract a percent based on fatigue */
    drainer_success = MIN(drainer_success, drainer_success * (100 * 
        (drainer->query_fatigue() * 2) / 
        drainer->query_max_fatigue()) / 50);

    DRAIN_LOG(sprintf("Fatigue: %-3d (%4s\nSuccess after fatigue: %d",
        drainer->query_fatigue(), drainer->query_max_fatigue() + ")",
        drainer_success));
      
    /* it is difficult to hold on to enemies that are not the same
     * size.  Modify the success value based on size differences.
     */
    drainer_success -= max(0, (ABS(QP(drainer, CONT_I_VOLUME) - 
                 QP(drainee, CONT_I_VOLUME)) - 50000) / 200);

    DRAIN_LOG(sprintf("Drainer Vol: %-6d Drainee Vol: %-6d\n" +
        "Success after volume: %d",
        QP(drainer, CONT_I_VOLUME), QP(drainee, CONT_I_VOLUME),
        drainer_success));
      
    /* it's harder to hold on to an enemy you can't see */
    if (!CAN_SEE_IN_ROOM(drainer) || !CAN_SEE(drainer, drainee))
    {
        drainer_success -= (100 - 
            drainer->query_skill(SS_BLIND_COMBAT)) * 400 / 100;
    }

    DRAIN_LOG(sprintf("Success after blindness: %d", drainer_success));
      
    /* it's harder to hold on to an enemy if you're wielding
     * weapons or wearing a shield.
     */
    right = drainer->query_tool(W_RIGHT);
    left  = drainer->query_tool(W_LEFT);
      
    if (right && left)
    {
        drainer_success -= 250;
    }
    else if (right || left)
    {
        drainer_success -= 100;
    }

    DRAIN_LOG(sprintf("Left hand: %-3s Right hand: %-3s\n" +
        "Success after hands: %d",
        (left ? "Yes" : "No"), (right ? "Yes" : "No"), drainer_success));

    /* It's alot harder to drink yourself full from large monsters */ 
    if (thirst() < 50)
    {
        drainer_success = drainer_success * (75 + (thirst() / 2)) / 100;
    }

    DRAIN_LOG(sprintf("Thirst: %d After Thirst: %d",
                  thirst(), drainer_success));
    
    return drainer_success;
}      

int
query_vamp_drainee_success()
{
    object drainer = SW;
    int drainee_success;
    int tmp_success;
    object *attackers;

    DRAIN_LOG(sprintf("\nDrainee: %-11s STR: %-3d DEX: %-3d", 
        drainee->query_real_name(), drainee->query_stat(SS_STR), 
        drainee->query_stat(SS_DEX)));

    /* base success is a random number based on dex and str */
    drainee_success = 
        drainee->find_drm(({ SKILL_WEIGHT, 115, TS_DEX,
                             SKILL_WEIGHT, 115, TS_STR }));
      
    drainee_success += random(400) - random(400);
 
    DRAIN_LOG("Base success: " + drainee_success);
     
    /* subtract a percent based on fatigue */
    tmp_success = drainee_success;
    drainee_success = MIN(drainee_success, drainee_success * (100 * 
        (drainee->query_fatigue() * 3) / 
        drainee->query_max_fatigue()) / 50);

    // Cap the fatigue reduction at 40%
    tmp_success = tmp_success * 6 / 10;
    drainee_success = max(tmp_success, drainee_success);

    DRAIN_LOG(sprintf("Fatigue: %-3d (%4s\nSuccess after fatigue: %d",
        drainee->query_fatigue(), drainee->query_max_fatigue() + ")",
        drainee_success));
      
    // it's harder to escape from an enemy you can't see
    if (!CAN_SEE_IN_ROOM(drainee) || !CAN_SEE(drainee, drainer))
    {
        drainee_success -= (100 - 
            drainer->query_skill(SS_BLIND_COMBAT)) * 300 / 100;
    }

    DRAIN_LOG(sprintf("Success after blindness: %d", drainee_success));

    attackers = drainee->query_enemy(-1) & all_inventory(environment(drainee));
    attackers -= ({ drainer });

    drainee_success += 100 * sizeof(attackers);

    return drainee_success;
}    

void
desc_vamp_drain()
{
    object drainer = SW;
    string blood_desc;

    switch (drainee->query_hp() / 30)
    {
        case 0:
            blood_desc = "barely trickles onto your tongue";
            break;
        case 1..2:
            blood_desc = "flows slowly into your mouth";
            break;
        case 3..5:
            blood_desc = "streams steadily into your mouth";
            break;
        default:
            blood_desc = "gushes in a torrent down your throat";
            break;
    }
      
    drainee->catch_tell(({
        "You break out in a sweat as you are ravaged by " +
            "intense hot flashes.\n",
        "You feel " + drainer->query_the_name(drainee) + 
            "'s hot breath blasting against your neck like " +
            "flames licking at your skin.\n",
        "Violent chills race through your bones.\n",
        })[random(3)]);

    if (IS_MEMBER(drainee) && !random(3))
    {
        drainee->catch_tell("You feel your immortal strength weakening " +
            "by the moment.\n");
    }

    drainer->tell_watcher(({
        "A thin stream of blood trickles down " + QTNAME(drainee) +
            "'s neck.\n",
        QCTNAME(drainee) + " struggles to break free from " + 
            QTNAME(drainer) + "'s embrace, but is unable to free " +
            OBJ(drainee) + "self.\n",
        QCTNAME(drainee) + " lets out a barely audible whimper.\n",
        QCTNAME(drainer) + " looks up for a moment, licks the blood " +
            "from " + POS(drainer) + " lips, and tears back into " +
            QTNAME(drainee) + ".\n",
        "You hear a low, weak moan from " + QTNAME(drainee) + ".\n",
        QCTNAME(drainee) + "'s eyelids flutter.\n",
        QCTNAME(drainee) + " gasps for air.\n",
        })[random(7)], drainee);
    
    drainer->catch_tell(LANG_POSS(drainee->query_The_name(drainer)) +
        " blood " + blood_desc + ".\n");

}

void
recover_from_throw(string name)
{
    SW->remove_stun();
    SW->catch_tell("You recover from being thrown off " + name + ".\n");
}

void 
recover_from_miss(string name)
{
    SW->remove_stun();
    SW->catch_tell("You recover from having missed " + name + ".\n");
}

void
drain_vampire()
{
    object drainer = SW;
    int effect;

    /* Drainee gains thirst as blood is taken */
    drainee->add_thirst(1 + random(2));

    if ((query_sire() == drainee->query_real_name()) ||
        (drainee->query_sire() == drainer->query_real_name()))
    {
        effect = 5;
    }
    else
    {
        effect = drainee->query_vamp_stat() - query_vamp_stat() + 5;
        effect = min(100, effect);
    }

    /* Vampire blood is more potent, so the drainer's thirst is
     * reduced mroe quickly.
     */
    if (random(50) < effect)
    {
        drink_blood(1);
    }

    /* Do some immediate healing */
    if (random(100) < effect)
    {
        drainer->heal_hp(MYRAND(60));
        drainer->add_fatigue(MYRAND(15));
        drainer->add_mana(random(5));
    }

    /* Temporarily reduce the drainee's guild stat */
    if (!random(3))
    {
        drainee->add_tmp_vamp_stat_mod(-1);
        vstat_mod--;
    }

    /* Temporarily increase the drainer's guild stat */
    if (random(200) < effect)
    {
        add_tmp_vamp_stat_mod(1);
    }
}

int
filter_onlookers(object onlooker)
{
    return (interactive(onlooker) && CAN_SEE_IN_ROOM(onlooker));
}

void
enable_drain_past_death(object who)
{
    if (who != drainee)
    {
        return;
    }

    past_death = 1;
}

void
do_drain_past_death()
{
    object *onlookers, *met_onlookers, *nonmet_onlookers, *other_onlookers;
    string name, objname, posname, metname, nonmetname;

    /* All this is necessary to get messages right after the drainee
     * is killed.
     */
    name = drainee->query_the_name(SW);
    metname = drainee->query_met_name();
    nonmetname = drainee->query_nonmet_name();
    objname = OBJ(drainee);
    posname = POS(drainee);

    onlookers = filter(all_inventory(environment(SW)), filter_onlookers);
    onlookers -= ({ SW, drainee });

    other_onlookers = filter(onlookers, not @ &drainee->check_seen());
    met_onlookers = filter(onlookers - other_onlookers, &->query_met(drainee));
    nonmet_onlookers = onlookers - other_onlookers - met_onlookers;

    if (!IS_MEMBER(drainee))
    {
    	SW->catch_tell("You feel " + 
    	    LANG_POSS(name) + " heartbeat slowing, weakening....  " +
            capitalize(posname) + " heart faintly pulses one last time.\n");

	drainee->do_die(SW);

    	if (!past_death)   
    	{ 
    	    SW->catch_tell("Enraptured by fresh blood and driven by your " +
                "thirst, you continue drinking from " + name + "\n");
    	}
    	    
    	if (IS_WIZ(SW) || (power_check(100) > 0) || !random(200))
    	{
    	    SW->catch_tell("Continuing to swallow down " + LANG_POSS(name) +
    		 " blood as death overtakes " + objname + ", you sense " +
    		 posname + " soul quickly slipping away.  Caught in death's " +
    		 "grip, you feel your own soul being swept along into the " +
    		 "void.  You focus all your power and struggle to escape " +
    		 "death's pull as " + LANG_POSS(name) + " life force ebbs.  " +
    		 "Barely managing to extract yourself, you release " + name +
    		 " from your embrace, letting " + posname + " lifeless body " +
    		 "slip to the ground in a heap at your feet.\n");
    	}
    	else if (random(100))
    	{
    	    SW->catch_tell("Continuing to swallow down " + LANG_POSS(name) +
    		 " blood as death overtakes " + objname + ", you sense " +
    		 posname + " soul quickly slipping away.  Caught in death's " +
    		 "grip, you feel your own soul being swept along into the " +
    		 "void.  You focus all your power and struggle to escape " +
    		 "death's pull as " + LANG_POSS(name) + " life force ebbs.  " +
    		 "Barely managing to extract yourself, you release " + name +
    		 " from your embrace, letting " + posname + " lifeless body " +
    		 "slip to the ground in a heap at your feet.  You stagger " +
    		 "back, weakened by the ordeal.\n");
    
    	    setuid();
    	    seteuid(getuid());
    	    write_file(VAMP_LOG_DIR + "drain_death.log", SW->query_real_name() +
    		" failed " + ctime(time()) + "\n");
    
    	    /*
    	     * Perhaps adding more thirst is too brutal, considering thirst is
    	     * what gets you to this point anyway
    	    add_thirst(max(0, query_max_thirst() - 20 - query_thirst()));
    	     */
    	    SW->add_mana(-MYRAND(1600));
    	    SW->add_fatigue(-MYRAND(400));
    	}
    	else
    	{
    	    SW->catch_tell("Continuing to swallow down " + LANG_POSS(name) +
    		 " blood as death overtakes " + objname + ", you sense " +
    		 posname + " soul quickly slipping away.  Caught in death's " +
    		 "grip, you feel your own soul being swept along into the " +
    		 "void.  You focus all your power and struggle to escape " +
    		 "death's pull as " + LANG_POSS(name) + " life force ebbs, " +
    		 "but the tide proves too strong.\n");
    
    	    setuid();
    	    seteuid(getuid());
    	    write_file(VAMP_LOG_DIR + "drain_death.log", SW->query_real_name() +
    		" died " + ctime(time()) + "\n");
    
    	    /*
    	     * Perhaps adding more thirst is too brutal, considering thirst is
    	     * what gets you to this point anyway
    	    add_thirst(max(0, query_max_thirst() - 50 - query_thirst()));
    	     */
    	    SW->add_mana(-MYRAND(800));
    	    SW->add_fatigue(-MYRAND(200));
    	    SW->heal_hp(-SW->query_hp());
    	    SW->do_die(this_object());

        }
    }
    else
    {    
#if 0
        SW->catch_tell("As you drain the last drops of blood from " +
            name + ", its taste becomes heavy, like the blood of a mortal.  " +
            "Pulling from " + objname + " " + posname + " faltering immortal " +
            "power just as death overtakes " + objname + ", you feel an " +
            "exhilarating rush of sensations charge through you.\n");
        drainee->catch_tell("With wrenching pain, the last minim of your " +
            "immortal essence is drawn from you with your final drops of " +
            "blood.\n");
        drainee->vampire_death(SW);
#endif
    }

    met_onlookers->catch_msg(QCTNAME(SW) + " releases " + metname +
        " from " + POS(SW) + " embrace, letting " + posname +
        " lifeless corpse slip to the ground in a heap at " +
        POS(SW) + " feet.\n");
    nonmet_onlookers->catch_msg(QCTNAME(SW) + " releases " + nonmetname +
        " from " + POS(SW) + " embrace, letting " + posname +
        " lifeless corpse slip to the ground in a heap at " +
        POS(SW) + " feet.\n");
    other_onlookers->catch_msg(QCTNAME(SW) + " releases someone " +
        " from " + POS(SW) + " embrace.\n");

    release_vamp_drainee(1);
}
