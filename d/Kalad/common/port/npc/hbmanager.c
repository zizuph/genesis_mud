/* Change the alignment to 200
 * From 1000 which seemed kind of 
 * extreme for this NPC 
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include <stdproperties.h>
int beer;
string long;
object halfbrewman;
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("regis");
    add_name("ilustrious brewery manager");
    add_name("ilustrious manager");
    add_name("brewery manager");
    add_name("manager");
    set_race_name("hobbit");
    set_adj("cherubic");
    add_adj("pot-bellied");
    set_long("A foppish-looking halfling dressed in extravagant clothes. "+
      "A big, childish smile is plastered onto his face, making you wonder "+
      "why he's so happy. His reddened cheeks and nose lead you to the "+
      "conclusion that he's rip-roaring drunk.\n");
    set_stats(({80,120,80,60,60,50}));
    set_alignment(200);
    set_skill(SS_WEP_KNIFE,90);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_HIDE,60);
    set_skill(SS_SNEAK,60);
    set_act_time(3);
    add_act("burp");
    add_act("emote pats his head.");
    add_act("emote rubs his belly.");
    add_act("emote tries to pat his head and rub his belly at the same time and fails miserably.");
    add_act("emote stumbles around the room, almost hurting himself.");
    add_act("emote belches right in your face.");
    add_act("fart");
    add_act("say Whersch myy beeer??");
    add_act("say I wantchs schom bearr!");
    add_act("confused");
    add_act("emote smiles drunkenly.");
    set_cact_time(3);
    add_cact("say Wouldn't you rather drink some beer than hurt little old me?");
    add_cact("sigh");
    add_cact("sniff");
    add_cact("cry");
    add_cact("say Youse meany old baddy guy!");
    add_speak("I woush weally wike my special bweer...rites bout now.\n");
    set_knight_prestige(-10);
    set_title("Rumblebelly, the Ilustrious Brewery Manager");
    set_default_answer("The manager burps rudely in your face.\n");
    add_ask(({"beer","liquor","alcohol","beverage"}),"The manager manages to say: "+
      "Unhhh...I wanna drink...do youse knows wherr sit it?\n");
    add_ask(({"drink"}),"The manager burps: Thwat's whas I whants.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object arm, wep;
    seteuid(getuid(this_object()));
    arm = clone_object("/d/Kalad/common/port/arm/regishat");
    arm -> move(this_object());
    arm = clone_object("/d/Kalad/common/port/arm/regisshirt");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/regisneck");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/regisgloves");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/regisbelt");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/regisboots");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/regisdagger");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(10))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say You mean old " + ob->query_race_name() + "!");
	command("say Stop fighting my friend!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
beer_return()
{
    beer = 1;
}
public void
enter_inv(object ob, object from)
{
    if(MASTER_OB(ob) != "/d/Kalad/common/port/obj/hbmbeer")
    {
	::enter_inv(ob, from);
	set_alarm(2.0,0.0,"drop_the_object",ob);
	return;
    }
    if(!interactive(from))
	return;
    else
	set_this_player(from);
    if(from->test_bit("Kalad",0,5))
    {
	write(query_The_name(from) + " drunkenly thanks you, and then "+
	  "proceeds to throw up before you.\n");
    }
    else{
	write("The manager drunkenly thanks you.\n");
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(500);
	TP->set_bit(0,5);
    }
    ::enter_inv(ob, from);
    set_alarm(2.0,0.0,"remove_the_object",ob);
}
void
remove_the_object(object ob)
{
    command("burp");
    command("wave " + (ob->query_real_name()));
    command("emote stumbles out of the room.");
    if(halfbrewman=present("manager",environment(TP)))
    {
	halfbrewman->remove_object();
    }
}
