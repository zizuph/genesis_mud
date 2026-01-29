#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "../defs.h"

void
create_monster() 
{
    if (!IS_CLONE)
        return;

    set_name("bonka");
    set_race_name("giant");
    set_adj("enormous");
    set_gender(2);

    set_long("You gaze in astonishment at this freak of nature. "+
             "It stands as tall and as strong as an oak tree. Its " +
             "tongue drips saliva slowly. Hunger, anger, and greed "+
             "illuminate its eyes.\n");

    /* str,  dex,  con,  int,  wis,  dis */
    set_stats(({ random(60)+190, 130, 190, 10, 5, 100}));

    set_hp(20000); /* reduced to correct level according to con. */

    set_alignment(-200);
    set_skill(SS_WEP_SWORD, 30);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 56);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_WEP_MISSILE, 55);

/*    set_attack_unarmed(1, 20, 20, W_BLUDGEON, 10, "head");
    set_attack_unarmed(1, 20, 20, W_BLUDGEON, 10, "right foot");
    set_attack_unarmed(1, 25, 25, W_BLUDGEON, 10, "left foot");
    set_attack_unarmed(1, 30, 40, W_BLUDGEON, 10, "left elbow");
    set_attack_unarmed(1, 30, 40, W_BLUDGEON, 40, "left fist");
    set_attack_unarmed(1, 30, 40, W_BLUDGEON, 10, "right elbow");
    set_attack_unarmed(1, 30, 40, W_BLUDGEON, 10, "right fist");*/
    add_prop(CONT_I_WEIGHT, 2000000);
    add_prop(CONT_I_HEIGHT, 13000);
    add_prop(CONT_I_VOLUME, 570000);
    /* add_prop(OBJ_I_NO_INS, 1); */
}

void
arm_me()
{
    seteuid(getuid(TO));

    if(!random(3))
        MONEY_MAKE(random(2) - 1, "platinum")->move(TO);

    MONEY_MAKE(random(5) + 1, "gold")->move(TO);
    MONEY_MAKE(random(40) + 10, "silver")->move(TO);
    MONEY_MAKE(random(200) + 100, "copper")->move(TO);

    clone_object(OBJ_DIR + "loin")->move(TO);
    clone_object(OBJ_DIR + "boulder")->move(TO);
    command("wear all");
    command("wield all");
}

void
initsay() {

    mixed *messages;
    int num, lines, i;

    messages = ({
        ({
            "say How nice of you to drop by.",
            "say I was just longing for someone to play with.",
            "grin",
           /* "wield "+ wpn->query_name() */
        }),
        ({
            "smile",
            "say Are you for real? I mean, really, you're mortal right?",
            "flip",
           /* "wield "+ wpn->query_name(), */
            "say I just LOOOVE mortals."
        }),
        ({
            "say Were you waiting for me?",
           /* "say I'll just get my "+ wpn->query_name() +" ready.", */
           /* "wield "+ wpn->query_name(), */
            "spit",
            "say Ok. I'm ready."

        }) ,
        ({
            "yawn",
            "say Another one?",
            "sigh",
            "say These mortals have begun to wear me out.",
           /* "wield "+ wpn->query_name() */
        }),
        ({
           /*  "wield "+ wpn->query_name(), */
            "smile"
        }),
        ({
            "say Gee, I'd love to stomp a tiny one like you.",
        /*           "wield "+ wpn->query_name(), */
            "grin"
        }),
 
        ({
            "start_fight",
          /* "wield "+ wpn->query_name() */
        }),
        ({
            "start_fight",
          /*  "wield "+ wpn->query_name()  */
        }),
        ({
            "start_fight",
          /*  "wield "+ wpn->query_name() */
        }),
        ({
            "start_fight",
          /*  "wield "+ wpn->query_name() */
        }),
        ({
            "start_fight",
          /*  "wield "+ wpn->query_name() */
        }),
        ({
            "start_fight",
          /*  "wield "+ wpn->query_name() */
        }),
        ({
            "say Look, here comes dinner!",
            "smile",
          /*  "wield "+ wpn->query_name() */
        })
    });

    num = random(sizeof(messages));
    lines = sizeof(messages[num]);

    for (i=0 ; i < lines ; i++) {
        if (messages[num][i] == "start_fight") {    /* Needed if the giant   */
            set_attack_chance(100);                 /* should start to fight */
            set_aggressive(1);                      /* right away...         */
        }
        else command(messages[num][i]);
    }
    set_attack_chance(100);
    set_aggressive(1);
}

void
init_living()
{
    ::init_living();

    set_alarm(2.0, 0.0, initsay);
}
