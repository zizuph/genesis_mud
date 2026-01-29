/* 
 *Money changer in the Trollshaws
 *Altrus, July 2005
 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit SHIRE_MONSTER;

string *list_introduced = ({ });

void 
create_shire_monster()
{
	set_name("durnk");
	set_living_name("durnk");
    set_title("the Purveyor of Monetary Exchange");
    set_long("This somewhat greedy looking dwarf seems to be offering his services as an exchanger of coins.\n");
	set_race_name("dwarf");
	set_gender(0);
	set_appearance(40);
	add_adj(({"blunt","money-grubbing"}));
	set_stats(({250, 140, 230, 100, 120, 200}));
	add_prop(CONT_I_WEIGHT, 35000);
	add_prop(CONT_I_HEIGHT, 600);
	
	set_introduce(1);
	
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_PARRY, 75);
	set_skill(SS_UNARM_COMBAT, 90);
	set_skill(SS_WEP_CLUB, 100);
	
	set_act_time(9);
	add_act("grumble .");
	add_act("peer suspiciously");
	add_act("emote complains loudly about stingy people.");
	add_act("emote idly fingers a few coins in his pocket.");
	
	set_cchat_time(7);
    add_cchat("Ye're more stupid than ye look!");
	add_cchat("Fine, ye don't want money, ye don't get money!");
	add_cchat("If'n ye don't run now, I'll paint the walls with yer blood!");
	add_cchat("I'll use yer skin to make me another coin purse!");
    
	set_chat_time(7);
	add_chat("What the hell are ye lookin' at?");
	add_chat("Stoopid idjit!!!");
	add_chat("I wants yer coins, not a look at yer face!");
	add_chat("Ye going t'stand there all day? I gots coins t'make!");
	add_chat("Ye have enough money?");

	add_ask("instructions", VBFC_ME("answer_help"));
	
	
	clone_object("/d/Shire/common/trollsh/weapon/dwarf_pick")->move(TO);
	clone_object("/d/Shire/common/trollsh/arm/metal_arm")->move(TO);
	clone_object("/d/Shire/common/trollsh/arm/metal_cap")->move(TO);
	clone_object("/d/Shire/common/trollsh/arm/iron_greaves")->move(TO);
	clone_object("/d/Shire/common/trollsh/arm/iron_chainmail")->move(TO);
	clone_object("/d/Shire/common/trollsh/arm/iron_shield")->move(TO);
	
	command("wear armours");
	command("wield weapons");
}

void
add_introduced(string who)
{
    if(member_array(who, list_introduced) == -1)
	list_introduced += ({ who });
    set_alarm(2.0, 0.0, "return_introduce");
}

void return_introduce()
{
    command("introduce myself");
    command("say Now ye know me name, so bugger off!!");
    return;
}

int query_introduced(object who)
{
    if(member_array(who->query_real_name(), list_introduced) == -1)
	return 0;
    return 1;
}

string answer_help()
{
    string who_ask = TP->query_real_name();

    if(member_array(who_ask, list_introduced) == -1)
    {
	command("say Introduce yourself first! I like to know who am I talking to.");
	command("peer "+who_ask);
	return "";
    }
    command("say Yes, I can relieve you of the burden of heavy coins.");
    command("smile greedily");
    command("say You can change platinum and gold for copper...");
    command("say then change 100 platinum for copper...");
    command("say maybe even change platinum for 10 silver...");
    command("hmm");
    command("scratch");
    command("say Yes...");
    command("say you can do test change 100 platinum for copper too!");
    command("poke "+who_ask);
    command("think");
    command("scratch");
    command("peer "+who_ask);
    command("say O.K. I tell you...");
    command("say You can even minimize coins!");
    command("say But I don't like to do this very much.");
    command("grin");
    command("say I think that's all...");
    command("smile "+who_ask);
    command("think");
    command("oops");
    command("say I forgot the most important part!!!");
    command("say Of course I take some small fee for my service.");
    command("smile greedily");
    return "";
}
void init_attack(){}

