inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
int dagger;
string long;
object guard;
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("delbin");
    add_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("furious");
    add_adj("kabal");
    set_short("guardsman of Kabal");
    set_pshort("guardsmen of Kabal");
    set_long("He is a tall, dark-haired man whose job is to insure that "+
      "order is maintained in the great city of Kabal. Oftentimes he fails, "+
      "making him ever more cruel to those that defy him.\n");
    set_stats(({80,70,70,55,55,60}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS,30);
    set_random_move(10);
    set_title("the Guardsman");
    set_act_time(6);
    add_act("grumble");
    add_act("sigh angrily");
    add_act("spit");
    add_act("frown");
    add_act("say Stinking little kid!");
    set_cact_time(3);
    add_cact("shout Militiamen, come to my aid!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_speak("Have you seen a sneaky little kid around? The little "+
      "punk stole my dagger!\n");
    set_knight_prestige(-3);
    set_title("the Guardsman");
    set_default_answer("The guardsman of Kabal says: What?\n");
    add_ask(({"captain"}),"The guardsman of Kabal says: That would be Hahmal.\n");
    add_ask(({"kid"}),"The guardsman of Kabal says: Some lousy little kid stole my "+
      "dagger!\n");
    add_ask(({"dagger"}),"The guardsman of Kabal says: Its a standard-issue "+
      "guardsman's dagger, a keen dagger to be exact. Can you help me look "+
      "for it?\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));

    arm = clone_object("/d/Kalad/common/caravan/arm/gchain");
    arm -> move(this_object());
    arm = clone_object("/d/Kalad/common/caravan/arm/ghelm");
    arm -> move(this_object());
    command("wear all");
    wep = clone_object("/d/Kalad/common/caravan/wep/gsword");
    wep -> move(this_object());
    command("say Damn! Where'd my dagger go?");
    command("wield all");
    MONEY_MAKE_GC(random(5))->move(this_object(),1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Villanous retch! Die!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
dagger_return()
{
    dagger = 1;
}
public void
enter_inv(object ob, object from)
{
    if(MASTER_OB(ob) != "/d/Kalad/common/port/wep/gdagger")
    {
	::enter_inv(ob, from);
	set_alarm(2.0,0.0,"drop_the_object",ob);
	return;
    }
    if(!interactive(from))
	return;
    else
	set_this_player(from);
    if(from->test_bit("Kalad",0,4))
    {
	write(query_The_name(from) + " thanks you gratefully for helping him again.\n");
    }
    else{
	write("The kabal guard thanks you profusely for helping him.\n");
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(200);
	TP->set_bit(0,4);
    }
    ::enter_inv(ob, from);
    set_alarm(2.0,0.0,"remove_the_object",ob);
}
void
remove_the_object(object ob)
{
    command("emote bids farewell to you.");
    command("emote departs into the depths of the city.");
    if(guard=present("guardsman",environment(TP)))
    {
	guard->remove_object();
    }
}
