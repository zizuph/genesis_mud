#include "../guild.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <language.h>
#include <tasks.h>

inherit "/cmd/std/command_driver";

#define SW this_player()

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

#define DRAIN_LOG(x)

static int drain_status, drain_alarm, times;
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

public object
query_vamp_drain()
{
    if (drain_status == DRAIN_STATUS_DRAINING)
    {
        return drainee;
    }

    return 0;
}

public int
query_vamp_drain_status()
{
    return drain_status;
}

/* Called when a vampire should be unwillingly stopped from
 * draining (eg. the vampire has been attacked)
 */
void 
break_vamp_drain()
{
    if ((drain_status != DRAIN_STATUS_DRAINING) || !drainee)
    {
        return;
    }

    set_this_player(drainee);      
    target(" breaks free from your grip, sending you staggering " +
        "back, half dazed.", ({ SW }));
    actor("You break free from", ({ SW }), "'s grip.");
        all2actbb(" breaks free from", ({ SW }), "'s grip.");

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

    if (QP(drainee, LIVE_I_STUNNED))
    {
        drainee->catch_tell("You can't manage to drain " +
            drainee->query_the_name(drainer) + ".\n");
        return 1;
    }
  
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
    drainee = who;
    drain_status = DRAIN_STATUS_START_DRAIN;
}

void
continue_vamp_drink(object who)
{
    who->add_prop(LIVE_O_VAMP_DRAINER, SW);
    drainee = who;
    drain_status = DRAIN_STATUS_DRAINING;
 
    if (drain_alarm)
    {
        remove_alarm(drain_alarm);
    }

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
  
        drainer->drink_blood(1);
  
#ifdef DRAIN_SHADOW  
        drainee->drain_me();
#endif
        drainee->heal_hp(-DRINK_HP);
        drainee->add_mana(-DRINK_MANA);
        drainee->add_fatigue(-DRINK_FATIGUE);
  
        if (IS_MEMBER(drainee))
        {
            drainee->add_thirst(1);
        }
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
        "The sound of " + drainer->query_the_name(drainee) +
            "'s heart beating in sync with your own echos " +
            "through your mind.\n",
        "You feel " + drainer->query_the_name(drainee) + 
            "'s hot breath blasting against your neck like " +
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
        "A thin stream of blood trickles down " + QTNAME(drainee) +
            "'s neck.\n",
        QCTNAME(drainer) + " looks up for a moment, licks the blood " +
            "from his lips, and continues to feed on " + QTNAME(drainee) + 
            ".\n",
        QCTNAME(drainee) + " lets out a soft moan of ecstacy.\n",
        QCTNAME(drainee) + " clutches at " + QTNAME(drainer) + "'s " +
            "clothing, pulling " + POS(drainer) + " closer.\n",
        QCTNAME(drainee) + " opens " + POS(drainee) + " eyes for a moment, " +
            "apparently lost in overwhelming sensations.\n",
        QCTNAME(drainee) + "'s eyelids flutter.\n",
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
        set_this_player(drainer);
        actor("You release", ({ drainee }), " from your embrace.");
        target(" releases you from " + POS(drainer) + " embrace.", 
            ({ drainee }));
       
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
            all2actbb(" releases", ({ drainee }), " from " + POS(drainer) + 
                " embrace.");
        }
    }
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
}

void
start_vamp_drain(object who)
{
    drainee = who;
    drain_status = DRAIN_STATUS_START_DRAIN;
}

void
continue_vamp_drain(object who)
{
    object right, left;
    string drainee_name, drainer_name;
    int hitsuc, hit;

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
    drain_status = DRAIN_STATUS_DRAINING;

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
    object drainer = SW;

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
        drainer->drink_blood(1);
    }
  
#ifdef DRAIN_SHADOW  
    drainee->drain_me();
#endif
    drainee->heal_hp(-DRAIN_HP);
    drainee->add_mana(-DRAIN_MANA);
    drainee->add_fatigue(-DRAIN_FATIGUE);

    if (IS_MEMBER(drainee))
    {
        drainee->add_thirst(1);
    }

    if (drainee->query_hp() <= 0)
    {
#if 0
        release_vamp_drainee(1);
        drainee->do_die(drainer); 

        set_this_player(drainer);
        if (!drainee || drainee->query_ghost())
	{

            drainer->catch_tell("You release " + 
            	drainee->query_the_name(drainer) + " from your " +
                "embrace, letting " + POS(drainee) + " lifeless " +
                "corpse slip to the ground in a heap at your feet.\n");
            all2actbb(" releases", ({ drainee }), " from " + 
                POS(drainer) + " embrace, letting " + POS(drainee) +
                " lifeless corpse slip to the ground in a heap at " +
                POS(drainer) + " feet.");
            release_vamp_drainee(1);
	}
        else
	{
            drainer->catch_tell("Having drained " +
                drainee->query_the_name(drainer) + " of blood, " +
                "you release " + OBJ(drainee) + " from your " +
                "embrace.\n");
            all2actbb(" releases", ({ drainee }), " from " +
                POS(drainer) + "embrace.");
        }
#else
        set_this_player(drainer);
        drainer->catch_tell("You release " + 
            drainee->query_the_name(drainer) + " from your " +
            "embrace, letting " + POS(drainee) + " lifeless " +
            "corpse slip to the ground in a heap at your feet.\n");
        all2actbb(" releases", ({ drainee }), " from " + 
            POS(drainer) + " embrace, letting " + POS(drainee) +
            " lifeless corpse slip to the ground in a heap at " +
            POS(drainer) + " feet.");
        release_vamp_drainee(1);
        drainee->do_die(drainer); 
#endif
    }
}

int
query_vamp_drainer_success()
{
    object drainer = SW;
    int drainer_success, left, right;

    DRAIN_LOG(sprintf("\nDrainer: %-11s STR: %-3d DEX: %-3d", 
        drainer->query_real_name(), drainer->query_stat(SS_STR), 
        drainer->query_stat(SS_DEX)));
 
    /* base success is a random number based on dex and str */
    drainer_success = drainer->find_drm(({ TS_DEX, TS_STR })) * 2;

    drainer_success += random(500) - random(500);

    DRAIN_LOG("Base success: " + drainer_success);
            
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
    drainer_success -= ABS(QP(drainer, CONT_I_VOLUME) - 
                 QP(drainee, CONT_I_VOLUME)) / 100;

    DRAIN_LOG(sprintf("Drainer Vol: %-6d Drainee Vol: %-6d\n" +
        "Success after volume: %d",
        QP(drainer, CONT_I_VOLUME), QP(drainee, CONT_I_VOLUME),
        drainer_success))
      
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

    return drainer_success;
}      

int
query_vamp_drainee_success()
{
    object drainer = SW;
    int drainee_success;

    DRAIN_LOG(sprintf("\nDrainee: %-11s STR: %-3d DEX: %-3d", 
        drainee->query_real_name(), drainee->query_stat(SS_STR), 
        drainee->query_stat(SS_DEX)));

    /* base success is a random number based on dex and str */
    drainee_success = 
        drainee->find_drm(({ SKILL_WEIGHT, 65, TS_DEX, TS_STR })) * 2;
      
    drainee_success += random(500) - random(500);
 
    DRAIN_LOG("Base success: " + drainee_success);
     
    /* subtract a percent based on fatigue */
    drainee_success = MIN(drainee_success, drainee_success * (100 * 
        (drainee->query_fatigue() * 3) / 
        drainee->query_max_fatigue()) / 50);

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
