#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("salvira");
    add_name("lady");
    set_race_name("elf");
    set_adj("voluptuous");
    add_adj("barely-clad");
    set_gender(G_FEMALE);
    set_long("This gorgeous lady is the most beautfiul creature you have "+
      "ever had the priviledge of laying eyes upon. She gazes at you with "+
      "a look that tells you that she's here to please, perhaps you should "+
      "oblige her.\n");
    set_stats(({40, 60, 40, 50, 50, 40}));
    set_skill(SS_AWARENESS, 100);
    set_title("the Mistress of Pleasure");
    set_act_time(6);
    add_act("love all");
    add_act("smile seductively");
    add_act("smile sex all");
    add_act("fondle all");
    add_act("wiggle erotically");
    add_act("emote moves sensually.");
    add_act("ruffle all");
    add_speak("I'll please you if you please me.\n");
    trig_new("%w 'drops' %s", "react_drop");
}

void
return_drop(string who)
{
    object obj;
    int ran;

    if (obj = present(who, environment()))
    {
	command("get all");
	command("say Why thank you for the gift, " + obj->query_nonmet_name() + ".");
	command("smile innocently");
    }
}

int
react_drop(string who, string dummy)
{
    if (who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_drop(who));
	return 1;
    }
}

void
return_kiss(object who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("growl sexily");
	command("french " + OB_NAME(obj));
    }
}

void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (emote=="kiss") set_alarm(1.0, 0.0, &return_kiss(actor));
}
