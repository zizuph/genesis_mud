/*
 * The owner of the Whitfurrows Training Academy.
 * Cloned by ~Shire/eastroad/village/whit/whitschool
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

//  Prototypes
void return_introduce();
void greet(object player);
void return_smile(string who);
void arm_me();

void
create_monster() {
    if (!IS_CLONE) return;
    set_name("adebras");
    add_name(({"","captain"}));
    set_living_name("_adebras_");
    set_title("the Captain");
    set_race_name("hobbit"); 
    set_adj(({"tall","handsome"}));
    set_long("@@my_long");
    default_config_npc(30);
    set_base_stat(SS_CON, 65);
    set_base_stat(SS_STR,60);
    set_base_stat(SS_DEX,80);
    set_base_stat(SS_DIS,95);
    set_base_stat(SS_INT,50);
    set_base_stat(SS_WIS,50);
    set_gender(0);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY,70);
    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_DEFENCE,70);
    set_pick_up(75);
    set_alignment(400 + random(200));

    set_aggressive(0);
    set_attack_chance(0);

    add_prop(CONT_I_WEIGHT, 70000);   /* 70 Kg  */
    add_prop(CONT_I_VOLUME, 70000);   /* 70 Ltr */
    add_prop(LIVE_I_NEVERKNOWN, 1);

    trig_new("%s 'smiles' %s", "react_smile");

    set_act_time(3);
    add_act("emote tests the sharpness of his sword against his callused thumb.");
    add_act("emote glances at you appraisingly.");
    add_act("emote whistles a jaunty tune.");
    add_act("emote straightens up his tunic.");
    add_act("emote runs his eye over the room approvingly.");
    add_act("chuckle");
    set_alarm(1.0,0.0,&arm_me());
    trig_new("%s 'introduces' %s", "react_introduce");
}

init_living() {
    if (this_player() == this_interactive()) set_alarm(1.0,0.0,&greet(this_player()));
    ::init_living();
}

void
arm_me()
{
    object sword, tunic;
    sword = clone_object("/d/Shire/eastroad/village/whit/wep/gleaming_sword");
    sword->move(TO);
    tunic = clone_object("/d/Shire/eastroad/village/whit/arm/tunic");
    tunic->move(TO);
    command("wear all");
    command("wield all");
}

void
greet(object ob)
{
    if (!CAN_SEE(ob,this_object())) return;
    command("say Greetings " + ob->query_nonmet_name() + ". What can I teach you" +
      "?");
}

my_long() {
    if (notmet_me(this_player())) this_player()->add_introduced("adebras");
    return break_string("Meet Captain Adebras."+
      " He will train you in survival skills.\n",70);
}

react_smile(who, tmp) {
    int r;

    if (!who) return 0;
    who = lower_case(who);
    r = random(3);
    if (r) set_alarm(itof(r),0.0,&return_smile(who));
    else return return_smile(who);
    return 1;
}

return_smile(who) {
    object ob;

    ob = present(who, environment());
    if (!ob) return 0;
    switch (random(4)) {
    case 0: command("smile"); return 1;
    case 1: command("smile " + who); return 1;
    case 2: if (notmet_me(ob)) {
	    command("introduce myself to " + who);
	    return 1; 
	}
	break;
    }
    return 0;
}


react_introduce(who, tmp) {
    object ob;

    if (!who) return 0;
    who = lower_case(who);
    ob = present(who, environment());
    if (!ob) return 0;
    if (!notmet_me(ob)) return 0;
    if (!random(20)) return 0;
    set_alarm(itof(random(9)),0.0,&return_introduce());
    return 1;
}

return_introduce() {
    command("introduce myself");
}
