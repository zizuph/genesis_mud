inherit "/std/monster";

#include "/d/Emerald/defs.h"

mapping objects;

void
create_monster()
{
    set_name("minstrel");
    set_adj("loud");
    add_adj("gay");
    set_race_name("human");
    set_short("loud minstrel");
    set_long("This brash young man is trying to be a minstrel. "+
             "His voice is untrained and the songs are barely learnt "+
             "properly.\n");

    set_base_stat(SS_STR, 38);
    set_base_stat(SS_DEX, 30);
    set_base_stat(SS_CON, 40);
    set_base_stat(SS_INT, 20);
    set_base_stat(SS_WIS, 22);
    set_base_stat(SS_DIS, 34);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 25);
    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_AWARENESS, 45);

    set_all_hitloc_unarmed(10);  /* Inherent AC of 10 without equip */

    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);

    set_chat_time(10);                             /* Set speaking interval */
    add_chat("Would you like me to sing for you?"); /* A bit of random chat */
    add_chat("Have you heard about those magi?");

    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("I'll never come back here you know!");            /* The usual combat talk */
    add_cchat("Help! Help! Someone please help me!");

    set_act_time(10);                    /* Set action interval           */
    add_act("sing");              /* A few courteous actions       */
    add_act("dance");

    objects = ([ ]);

    set_alarm(1.0,0.0,"arm_me");
}


void
arm_me()
{
    object eq = clone_object(VILLAGE_DIR + "obj/gamb");
    if (eq)
        eq->move(this_object());
    command("wear all");
}
