/* A cheeky monkey. ~solace/puzzle/creatures/monkey */

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../defs.h"
#include "/sys/const.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"
#include "../../../mucalytic/sys/npc_defs.h"

#define ATT_LFIST	0
#define ATT_RFIST	1
#define ATT_LFOOT	2
#define ATT_RFOOT	3
#define ATT_LELBOW	4
#define ATT_RELBOW	5

#define HIT_BODY	0
#define HIT_HEAD	1
#define HIT_TAIL	2
#define HIT_LARM	3
#define HIT_RARM	4
#define HIT_LLEG	5
#define HIT_RLEG	6

#define ACTS ({ "north",                                                    \
                "east",                                                     \
                "emote clambers onto the control panel and jumps up into "+ \
                "the hole in the ceiling. He reappears moments later.",     \
                "emote jumps down from the control panel.",                 \
                "drop pendulum",                                            \
                "smile"                                                     })

void create_creature()
{
    set_name("monkey");
    set_pname("monkeys");
    set_adj("small");
    add_adj("hairy");
    set_race_name("monkey");
    set_gender(G_MALE);
    set_alignment(100 + random(200));
    set_long("A small cute monkey covered in short brown hair. Its small "+
        "black eyes gaze at you in anticipation and its tail waves "+
        "hypnotically as it scampers about.\n");

                    /* Att_id     Hit Pen  Dam_type    %  Att_string */
    set_attack_unarmed(ATT_LFIST,  9,  10, W_BLUDGEON, 20, "left fist");
    set_attack_unarmed(ATT_RFIST,  9,  10, W_BLUDGEON, 20, "right fist");
    set_attack_unarmed(ATT_LFOOT,  10, 11, W_BLUDGEON, 20, "left foot");
    set_attack_unarmed(ATT_RFIST,  10, 11, W_BLUDGEON, 20, "right foot");
    set_attack_unarmed(ATT_LELBOW, 8,  12, W_BLUDGEON, 10, "left elbow");
    set_attack_unarmed(ATT_RELBOW, 8,  12, W_BLUDGEON, 10, "right elbow");

                    /* Hit_id    Ac   %  Hit_string */
    set_hitloc_unarmed(HIT_BODY,  3, 30, "body");
    set_hitloc_unarmed(HIT_HEAD,  2, 8,  "head");
    set_hitloc_unarmed(HIT_TAIL,  2, 8,  "tail");
    set_hitloc_unarmed(HIT_LARM,  2, 8,  "left arm");
    set_hitloc_unarmed(HIT_RARM,  2, 8,  "right arm");
    set_hitloc_unarmed(HIT_LLEG,  2, 12, "left leg");
    set_hitloc_unarmed(HIT_RLEG,  2, 8,  "right leg");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    change_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    add_prop(CONT_I_WEIGHT, (KILOS * 25));
    add_prop(CONT_I_HEIGHT, ftoi((3.0 * FEET) + (5.0 * INCHES)));

    set_stats(({ (10 + random(5)),     /* str */
                 (15 + random(5)),     /* dex */
                 (5  + random(15)),    /* con */
                 (10 + random(10)),    /* int */
                 (5  + random(5)),     /* wis */
                 (10 + random(5)) })); /* dis */

    set_hp(10000);

    set_skill(SS_PARRY, (5 + random(5)));
    set_skill(SS_DEFENCE, (10 + random(5)));
    set_skill(SS_UNARM_COMBAT, (10 + random(5)));

    set_act_time(1);
    add_act("emote chitters.");
    add_act("emote chatters.");
    add_act("emote jumps up and down.");
    add_act("emote scratches his head.");
    add_act("emote scratches his bottom.");
    add_act("emote lopes about the room.");
    add_act("emote jumps onto the walls.");
    add_act("emote rolls around on the floor.");
}

void init_living()
{
    ::init_living();

    add_action("feed_monkey", "feed");
}

int special_attack(object enemy)
{
    object me = TO;
    mixed *hitresult;

    if(random(10)) // 10% chance
        return 0;

    hitresult = enemy->hit_me(random(11) + 5, W_BLUDGEON, me, -1); // 5-15 HP

    if(!hitresult[0])
    {
        me->catch_msg("You jump up at "+QTNAME(enemy)+", but "+PRONOUN(enemy)+
            "steps aside just in time.\n");
        enemy->catch_msg(QCTNAME(me)+" jumps up at you, but you step aside "+
            "just in time.\n");
        tell_watcher(QCTNAME(me)+" jumps up at "+QTNAME(enemy)+", but "+
            PRONOUN(enemy)+" steps aside just in time.\n", enemy);
    }
    else
    {
        me->catch_msg("You jump up at "+QTNAME(enemy)+" and bowl "+
            QTNAME(enemy)+" over as you crash into "+OBJECTIVE(enemy)+".\n");
        enemy->catch_msg(QCTNAME(me)+" jumps up at you and bowls you over "+
            "as "+PRONOUN(me)+" crashes into you.\n");
        tell_watcher(QCTNAME(me)+" jumps up at "+QTNAME(enemy)+" and bowls "+
            OBJECTIVE(enemy)+" over as "+PRONOUN(me)+" crashes into "+
            OBJECTIVE(enemy)+".\n", enemy);
    }

    if(enemy->query_hp() < 1)
        enemy->do_die(me);

    return 1;
}

int feed_monkey(string str)
{
    int i;
    string food;
    object *arr, banana, obj;

    if(!strlen(str))
    {
        notify_fail("Feed who/what?\n");
        return 0;
    }

    if(member_array(TO, FIND_STR_IN_OBJECT(str, E(TP))) != -1)
    {
        notify_fail("Feed the "+str+" with what?\n");
        return 0;
    }

    if(parse_command(str, E(TP), "%o 'with' %s", obj, food))
    {
        arr = FIND_STR_IN_OBJECT(food, TP);

        if(!sizeof(arr))
        {
            notify_fail("You don't have a "+food+".\n");
            return 0;
        }

        if(!objectp(obj) || obj != TO)
        {
            notify_fail("Feed what with the "+food+"?\n");
            return 0;
        }

        for(i = 0; i < sizeof(arr); i++)
        {
            if(MASTER_OB(arr[i]) == OBJECTS + "banana")
                banana = arr[i];
        }

        if(objectp(banana))
        {
            banana->remove_object();

            set_alarm(1.0, 0.0, "get_pendulum", 0);

            TP->catch_msg(QCTNAME(TO)+" grabs the banana out of your hands "+
                "and swallows it in one gulp!\n");

            tell_room(E(TP), QCTNAME(TP)+" offers a banana to "+QTNAME(TO)+" "+
                "who grabs it out of "+POSSESSIVE(TP)+" hands and swallows "+
                "it in one gulp!\n", ({ TO, TP }));
        }
        else
        {
            TP->catch_msg(QCTNAME(TO)+" sniffs at your offering and turns "+
                "aside in disgust.\n");

            tell_room(E(TP), QCTNAME(TP)+" offers something to "+QTNAME(TO)+" "+
                "who sniffs it and turns aside in disgust.\n", ({ TO, TP }));
        }

        return 1;
    }

    notify_fail("Feed what with what?\n");
    return 0;
}

void get_pendulum(int timer)
{
    if(timer != 6)
    {
        timer++;

        command(ACTS[timer - 1]);

        set_alarm(2.0, 0.0, "get_pendulum", timer);

        if(timer == 2)
        {
            seteuid(getuid(TO));
            clone_object(OBJECTS + "pendulum")->move(TO);
        }
    }
    else
    {
        command("emote leaves west.");

        remove_object();
    }
}
