/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    /*clone_object(OBJ + "pipe")->move(TO);*/
    clone_object(OBJ + "pullover")->move(TO);
    clone_object(OBJ + "trousers")->move(TO);
    clone_object(OBJ + "boots")->move(TO);
    command("wear all");
    command("emote plops himself into his rocking chair.");
    MONEY_MAKE_SC(random(20))->move(TO);
    MONEY_MAKE_CC(random(20))->move(TO);
}

void
create_citizen()
{
    set_name("reling");
    add_name("captain");
    set_race_name("dwarf");
    set_introduce("Sturmflag, Retired Captain");
    set_gender(0);
    set_adj("wrinkled");
    add_adj("leather-skinned");
    set_long("@@my_long");
    set_extra_long("He is sitting on a rocking chair.\nHe is smoking a pipe.\n");
    default_config_npc(random(50) + 20);
    add_prop("_live_m_attack_thief","call_guards");
    set_act_time(10);
    add_act("smile sadly");
    add_act("say Oh, de old days, I remember it just like'd was yesterday.");
    add_act("say Oh, well.");
    add_act("say Yes, yes, de old times were much better.");
    add_act("say Hello there, how goes?");
    add_act(({"say I used to sail de Ergothian sea before dey had dese huge ships.",
	      "say Now dat was excitement.",
	      "say I was out dere by meself trying to stay alive.",
	      "emote whispers: But I tell ya! It was a sure thing to catch enough.",
	      "say That wasn't the problem.",
	      "say De coming back was.",
	      "say Tides, ya know. I keep wondering how dem ships here manage to get beyond de bay.",
	      "say Must be magic, I say.",
	      "say Way too dangerous out dere. Ya never know what comes up and eats de ship.",
	      "say Considering the circumstances, it coulda been worse." }));

    remove_ask("lighthouse");
    add_ask("lighthouse","say A sure! right in de middle of de harbour. Figures, eh?",1);
    add_ask(({"deep blue","ship"}),
	    "say De Deep Blue was my ship of course, too bad de big sea monster " +
	    "took it. Twas a wonderful ship.",1);
    add_ask(({"monster","sea monster"}),
	    "say Ya never know when it strikes, but it's deadly. I'm de only one " +
	    "dat ever survived.",1);
}

string
my_long()
{
    string str = query_art_name(TP);
    if (str == query_name())
      return str + " Sturmflag, Retired Captain of the Deep Blue.\n";
    else
      return "He is " + str + "\n";
}

void
call_guards(object thief, object victim, object what)
{
    command("say Hey, I might be old, but I'm not stupid!");
    command("say Cut it out!");
    call_the_guards(thief->query_real_name(),"xxx");
}
