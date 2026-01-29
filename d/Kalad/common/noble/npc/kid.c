/*
    kid.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("butthead");
    set_adj("slack-jawed");
    add_adj("dull");
    add_name("noble");
    set_race_name("human");
    set_short("dull slack-jawed noble");
    set_long("This ugly, adolescent noble stares at you with dull eyes."+
        " His mouth is slightly open, and he smells bad. His eyes narrow "+
        "in suspicion as his slow brain tries to comprehend your presence.\n");
    set_stats(({50,50,50,35,30,40}));
    set_skill(SS_DEFENCE,30);
    set_alignment(600);
    set_knight_prestige(-300);

    set_act_time(5);
    add_act("say What are you doing here you stinker!");
    add_act("say My dad is richer than you! I can do whatever I want!");
    add_act("say Lick my feet now, slave!");
    add_act("say This is going to be MY house, so get out of here!");
    add_act("say My arse is too good for you to kiss!");
    add_act("say You puny fool, I am an Alexander! I could crush you!");
    set_cact_time(3);
    add_cact("shout Help! Guards! Help!");
}

void
help_me(object enemy)
{
    if (!objectp(enemy))
        return;

    command("shout Help ! Guards! WAAAAA! MOMMY!!!");
    ENV(TO)->aid_kid(enemy);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.1, 0.0, &help_me(ob)); 
}

