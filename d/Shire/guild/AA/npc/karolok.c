/*
 * The mess hall cook in the AA guild
 * Based on Barliman from Bree and the Prancing Pony
 * Finwe, February 2019
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes

void return_introduce();
void greet(object ob);

void
create_monster() 
{
    if (!IS_CLONE) 
        return;
    set_name("karolok");
    set_living_name("karolok");
    set_race_name("human"); 
    set_adj(({"muscular","lean"}));
    set_long("@@my_long");
    default_config_npc(30);
    set_base_stat(SS_CON, 39);
   
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,30);
    set_pick_up(75);
   
    set_aggressive(0);
    set_attack_chance(0);
   
    add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
    add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
    set_act_time(3);
    set_chat_time(3);
    add_act("chuckle");
    add_act("emote runs around the mess hall.");
    add_act("emote stares at you.");
    add_act("shout Clean up after yourselves. I'm not your slave!");
    add_act("shout wipes down the counter.");
    add_act("shout the Army eats a lot of food.");

    add_chat("Leave me alone unless you're going to order food!");
    add_chat("No one appreciates how much I do here.");
    add_chat("Buy something or get ou!");
    add_chat("The Army reports there is trouble in the mountains.");
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
    if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
    command("say Hey there " + ob->query_nonmet_name() + ". What do you want?");
}

my_long() {
    if (notmet_me(this_player())) this_player()->add_introduced("karolok");
    return "This is Karolok, the cook for the Army of Angmar. He is " +
        "a lean, muscular human who knows how to feed an army. He " +
        "bustles around the mess hall, trying to keep it clean and " +
        "serve those who come here.\n";
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
