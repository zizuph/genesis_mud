/*
 * The inkeeper of Longbottom
 * Based on Barliman from the Prancing Pony
 * Finwe, December 2019
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes
int return_sigh(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("halifast");
    add_name(({"grubb","innkeeper", "halifast"}));
    set_living_name("grubb");
    set_title("Grubb");
    set_race_name("hobbit");
    set_adj(({"jolly","rolly-polly"}));
    set_long("@@my_long");
    default_config_npc(30);
    set_base_stat(SS_CON, 39);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,30);
//   set_pick_up(75);

    set_aggressive(0);
    set_attack_chance(0);

    add_prop(CONT_I_WEIGHT, 40000);  
    add_prop(CONT_I_VOLUME, 50000);

    set_act_time(3);
    set_chat_time(3);

    add_act("emote bustles around and clears some tables.");
    add_act("emote wipes down a table.");
    add_act("emote wipes some sweat from his brow.");
    add_act("emote stops and talks to some customers.");
    add_act("emote brushes his hair away from his eyes.");
    add_act("emote looks around nervously.");
    add_act("smile merrily");
    add_act("chuckle");
    add_act("emote greets some customers.");
    add_act("emote gets some food for some customers.");

    add_chat("Welcome to the Inn. What can I get for you?");
    add_chat("Strange things are afoot in the South Farthing, so " +
        "I've heard.");
    add_chat("We don't get many strangers here in the South Farthing.");
    add_chat("Longbottom leaf is the best leaf anywhere.");
    add_chat("Don't cause any trouble around here, or I'll call the " +
        "Shirriffe.");
    add_chat("If you need food or drink for your travels, I can help you.");
    add_chat("Rumour has it there are orcs gathering near Sarn Ford.");
    add_chat("Strangers are passing by, and it's upsetting the " +
        "villagers.");
}

init_living()
{
    ::init_living();
    if (interactive(this_player()))
    {
        set_alarm(1.0,0.0,&greet(this_player()));
    }
}

void
greet(object ob)
{
    if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level())
        return;

   command("say Greetings traveller. What can I get you?");
}

my_long()
{
    if (notmet_me(this_player())) this_player()->add_introduced("halifast");
        return "This is Halifast Grubb, Innkeeper of the Silver Tree " +
        "Inn in Longbottom. He is a jolly hobbit who is rolly-polly " +
        "looking. His brown hair is curly and has brown eyes. He " +
        "constantly rushes around the inn helping many customers.\n";
}

int
return_smile(string who) {
    object ob;

    ob = present(who, environment());
    if (!ob)
        return 0;

    switch (random(4))
    {
        case 0:
            command("smile");
            return 1;
        case 1:
            command("smile " + who);
            return 1;
        case 2:
            if (notmet_me(ob))
            {
                command("introduce myself to " + who);
                return 1;
            }
            break;
    }
    return 0;
}

int
return_sigh(string who)
{
    if (!who)
        return 0;

    who = lower_case(who);

    if (random(3))
        return 0;

    command("say Do you want to order something?");
    return 1;
}

int
add_introduced(string who)
{
    object ob;

    if (!who)
        return 0;

    who = lower_case(who);
    ob = present(who, environment());

    if (!ob)
        return 0;

    if (!CAN_SEE(this_object(), ob))
        return 0;

    if (!notmet_me(ob))
        return 0;

    if (!random(20))
        return 0;

    set_alarm(itof(random(9)),0.0,&return_introduce());
    return 1;
}

void
return_introduce()
{
   command("introduce myself");
}

void
emote_hook(string emote,object actor,string averb = 0)
{
    string name = actor->query_real_name();

    switch(emote)
    {
        case "sigh":
            set_alarm(3.0,0.0,&return_sigh(name));
            break;
        case "smile":
            set_alarm(3.0,0.0,&return_smile(name));
            break;
    }
}
