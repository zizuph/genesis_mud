inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Hooker by Sarr */
object arm1;
object arm2;
object obj1;
object looker;
void
create_monster()
{
    ::create_monster();
    set_name("missy");
    set_race_name("human");
    set_adj("scantily-clad");
    set_gender(1);
    add_adj("voluptuous");
    set_long("@@my_long@@");
    set_stats(({15,20,10,15,20,5}));
    set_act_time(3);
    add_act("emote looks at you and slowly licks her lips.");
    add_act("say Hey there, looking for some fun?");
    add_act("emote adjusts her stockings.");
    set_alarm(1.0, 0.0, "arm_me");
    add_speak("People tell me i'm the best.\n");
}
void
arm_me()
{
    seteuid(getuid(TO));
    arm1 = clone_object("/d/Kalad/common/market/arm/pdress.c");
    arm1 -> move(TO);
    arm2 = clone_object("/d/Kalad/common/market/arm/pstock.c");
    arm2 -> move(TO);
    obj1 = clone_object("/d/Kalad/common/market/obj/ppurse.c");
    obj1 -> move(TO);
    MONEY_MAKE_SC(random(10))->move(obj1);
    command("wear all");
}

string
my_long()
{
    looker = previous_object();
    set_alarm(1.0, 0.0, &command("say Hey there cutie..."));
    set_alarm(1.0, 0.0, &command("wink"));
    set_alarm(1.0, 0.0, "smile_at");
    return 
     "This is a young girl, dressed in a very sexually promiscuous way.\n"+
     "She sits at the bar chatting with various people. Its not secret\n"+
     "what her profession is. She is rather good-looking, and noticing\n"+
     "you staring at her, she turns her lovely brown eyes to you.\n";
}

void
smile_at()
{
    say(QCTNAME(TO) + " smiles at " + QCTNAME(looker) + ".\n");
    looker -> catch_msg(QCTNAME(TO) + " smiles at you.\n");
}

