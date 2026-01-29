/* The black dragon of the hills. ~mucalytic/hills/creatures/black_dragon */

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

inherit STD + "intro";

#define ATT_CLAW1	0
#define ATT_CLAW2	1
#define ATT_FANGS	2

#define HIT_BODY	0
#define HIT_HEAD	1
#define HIT_NECK	2
#define HIT_TAIL	3
#define HIT_LEG1	4
#define HIT_LEG2	5
#define HIT_LEG3	6
#define HIT_LEG4	7
#define HIT_WING1	8
#define HIT_WING2	9

#define AWAKE  ({ "roars: FOOLISH, FOOLISH MORTAL.", \
                  "roars: GO NOW OR BURN IN THE FLAMES OF DEATH.", \
                  "roars: FOOL! YOU THINK YOU CAN STEAL FROM ME???", \
                  "roars: THIS IS YOUR LAST CHANCE TO LEAVE MORTAL.", \
                  "roars: WHAT ARE YOU DOING HERE MORTAL? BEGONE!!!", \
                  "roars: BEGONE OR YOU SHALL BE NOTHING BUT CHARCOAL.", \
                  "roars: AWAY WITH YOU MORTAL BEFORE I LOSE MY TEMPER.", \
                  "roars: STUPID MORTAL. GO BEFORE MY WRATH DESTROYS YOU.", \
                  "roars ferociously.", \
                  "laughs mockingly at you.", \
                  "laughs scornfully at you.", \
                  "mocks your puny appearance.", \
                  "stares distainfully at you.", \
                  "gazes hypnotically over you.", \
                  "looms above you like a mountain.", \
                  "breathes a fireball into the air.", \
                  "breathes a gout of flame into the air.", \
                  "roars with distain. You are terrified.", \
                  "rends at the floor and the walls with his claws" })

#define ASLEEP ({ "snores loudly.", \
                  "grunts sleepily.", \
                  "shifts restlessly in his slumber.", \
                  "watches you from beneath his eyelids.", \
                  "snores very loudly. The walls of the cave shake.", \
                  "breathes harshly. It sounds like a minor earthquake." })

int awake;

int sleep_dragon()
{
    awake = 0;

    tell_room(E(TO), "The "+short()+" rests on it haunches and appears to "+
        "fall asleep.\n", TO);
    TO->catch_msg("You slowly fall back asleep.\n");

    add_prop(LIVE_S_SOULEXTRA, "sleeping");
    add_prop(LIVE_S_EXTRA_SHORT, " (asleep)");

    return 0;
}

void create_creature()
{
    set_name("black-dragon");
    add_name("dragon");
    set_adj("fearsome");
    set_gender(G_MALE);
    set_alignment(-500 - random(499));
    set_race_name("black-dragon");
    set_long(break_string("A very very large dragon with black scales as "+
        "large as soup plates and wings as large as a small ship's sails. His"+
        " claws and fangs are the size of daggers and twice as sharp.\n", 75));

    set_stats(({ (100 + random(30)),     /* str */
                 (60  + random(40)),     /* dex */
                 (120 + random(20)),     /* con */
                 (80  + random(20)),     /* int */
                 (70  + random(50)),     /* wis */
                 (50  + random(20)) })); /* dis */

    set_hp(50000);

                    /* Att_id     Hit Pen   Dam_type   %  Att_string */
    set_attack_unarmed(ATT_CLAW1,  18, 20,  W_SLASH,  35, "right claw");
    set_attack_unarmed(ATT_CLAW2,  18, 20,  W_SLASH,  35, "left claw");
    set_attack_unarmed(ATT_FANGS,  24, 24,  W_IMPALE, 30, "fangs");

                    /* Hit_id     Ac   %  Hit_string */
    set_hitloc_unarmed(HIT_BODY,  25, 40, "body");
    set_hitloc_unarmed(HIT_HEAD,  20,  2, "head");
    set_hitloc_unarmed(HIT_NECK,  22,  8, "neck");
    set_hitloc_unarmed(HIT_TAIL,  22, 10, "tail");
    set_hitloc_unarmed(HIT_LEG1,  26,  5, "left front leg");
    set_hitloc_unarmed(HIT_LEG2,  26,  5, "right front leg");
    set_hitloc_unarmed(HIT_LEG3,  26,  5, "left hind leg");
    set_hitloc_unarmed(HIT_LEG4,  26,  5, "right hind leg");
    set_hitloc_unarmed(HIT_WING1, 16, 10, "left wing");
    set_hitloc_unarmed(HIT_WING2, 16, 10, "right wing");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_prop(OBJ_M_NO_ATTACK, "@@wake_dragon@@");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "@@wake_dragon@@");

    add_prop(CONT_I_HEIGHT, 2000); // 20 metres.
    add_prop(CONT_I_WEIGHT, 5000000); // 5 tonnes (5000 kilogrammes).

    set_act_time(1 + random(5));
    add_act("emote @@awake_sleeping_emotes@@");

    sleep_dragon();
}

string awake_sleeping_emotes()
{
    if(awake)
        return AWAKE[random(sizeof(AWAKE))];
    else
        return ASLEEP[random(sizeof(ASLEEP))];
}

int wake_dragon()
{
    awake = 1;

    remove_prop(LIVE_S_SOULEXTRA);
    remove_prop(LIVE_S_EXTRA_SHORT);

    tell_room(E(TO), "Suddenly, the "+short()+" wakes!!!\n", TO);
    TO->catch_msg("You wake to find mortals plundering your hoard!\n");

    command("emote roars: WHAT DO YOU THINK YOU ARE DOING, MORTAL!!???");
    return 0;
}

void return_introduce(string who)
{
    object obj;
    int ran = random(3);

    if(obj = present(who, environment()) && !obj->query_npc())
    {
        command("cackle evilly");

        switch(ran)
        {
            case 0:
                command("say WHO ARE YOU TO ASK ME QUESTIONS, MORTAL?");
                break;
            case 1:
                command("say IMPETUOUS FOOL. GO NOW WHILE I STILL MY TEMPER.");
                break;
            case 2:
                command("BEGONE FROM MY REALM, MORTAL OR YOU SHALL SUFFER "+
                    "THE CONSEQUENCES.");
                break;
        }
    }
}

int special_attack(object enemy)
{
    mixed *hitresult;

    if(random(5)) // 20% chance
        return 0;

    hitresult = enemy->hit_me(random(46) + 30, W_BLUDGEON, TO, -1); // 30-75 HP

    if(!hitresult[0])
    {
        TO->catch_msg("You breathe a ball of fire at "+QTNAME(enemy)+", but "+
            PRONOUN(enemy)+" steps aside just in time.\n");
        enemy->catch_msg(QCTNAME(TO)+" breathes a ball of fire at you, but "+
            "you step aside just in time.\n");
        tell_watcher(QCTNAME(TO)+" breathes a ball of fire at "+QTNAME(enemy)+
            ", but "+PRONOUN(enemy)+" steps aside and it misses "+
            PRONOUN(enemy)+".\n", TO, enemy);
    }
    else
    {
        TO->catch_msg("You breathe a ball of fire at "+QTNAME(enemy)+" which "+
            "hits "+OBJECTIVE(enemy)+" full on, searing and burning at "+
            POSSESSIVE(enemy)+" body.\n");
        enemy->catch_msg(QCTNAME(TO)+" breathes a ball of fire at you which "+
            "hits you full on, searing and burning at your body.\n");
        tell_watcher(QCTNAME(TO)+" breathes a ball of fire at "+QTNAME(enemy)+
            ", which hits "+OBJECTIVE(enemy)+" head on, searing and burning "+
            "at "+POSSESSIVE(enemy)+" body.\n", TO, enemy);
    }

    if (enemy->query_hp() < 1)
        enemy->do_die(TO);

    return 1;
}

int query_awake()
{
    return awake;
}
