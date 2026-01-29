#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dwarf/guild.h"

inherit AM_FILE

#define AXE "/d/Ansalon/estwilde/obj/weapon/iron_axe"
#define WHO(ob) ob->query_real_name()

int wielded_weapon;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("patron");
    set_adj("dwarven");
    set_short("dwarven patron");
    set_race_name("dwarf");
    set_long("This is one of the dwarven patrons here, " +
      "relaxing on a wooden stool smoking a long-stemmed " +
      "pipe.\n");

    set_stats(({55,30,120,40,40,50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_AXE, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(5);
    add_act("emote sits back contently on his " +
      "stool.");
    add_act("emote blows smoke rings into the air.");
    add_act("emote puffs on his pipe contently.");
    add_act("say Try the craft brew, Iron Delving's finest... this month");

    set_cact_time(5);
    add_cact("say Damnit! Where's me axe!");
    add_cact("say Reorx curse ye! May yer beard " +
      "fall off and boots be ever full of stones!");

    set_default_answer("The dwarven patron is relaxing. " +
      "You feel its best if you leave him alone.\n");

    add_ask(({"quest","task"}),
      VBFC_ME("quest_hint"));

    seteuid(getuid(TO));
}

void
arm_me()
{

    command("wield all");
}


string
quest_hint()
{

    if (!MEMBER(TP))
    {
	command("emote snorts.");
	command("say Leave me to my drink!");
	return "";
    }

    if(BANISHED(TP))
    {
	command("shout Get out of me sight until ye "+
	  "redeem yourself!");
	command("emote scowls into his drink.");
	return "";
    }

    if(TP->query_stat(SS_OCCUP) < GURU_QUEST_STAT)
    {
	command("say Ah lad...");
	command("say You aren't ready for that burden "+
	  "yet.");
	command("emote turns back to his drink.");
	return "";
    }

    if(TP->test_bit("ansalon", 3, 5))
    {
	command("say My friend, there is nothing more " +
	  "myself or the clan can ask of you!");
	command("smile proud");
	command("say Ye did yerself proud!");
	return "";
    }

    TP->add_prop(GIVEN_GURU_QUEST, 1);
    command("eyebrow thought "+ WHO(TP));
    command("say You may be up to it lad, you "+
      "may just be up to it...");
    set_alarm(1.0,0.0, &command("emote takes a long "+
	"swig from his mug of craft brew."));
    set_alarm(6.5,0.0, &command("emote leans forward."));
    set_alarm(8.0,0.0, &command("whisper "+WHO(TP)+
	" What I am about to tell you is the greatest shame "+
	"to befall the Clan..."));
    set_alarm(10.5,0.0, &command("whisper "+WHO(TP)+
	" Only the elders remember this incident. I am going "+
	"to hold you on your word as a dwarven warrior of "+
	"honour that you will not utter a word of this story "+
	"to anyone."));
    set_alarm(12.5,0.0, &command("emote looks at you, his "+
	"face as serious as stone."));
    set_alarm(14.5,0.0, &command("whisper "+WHO(TP)+
	" Not long ago, there was a clansman known as "+
	"Teregul Stormbolt. Of all the warriors born into the "+
	"Neidar, he was far and away the best. None could "+
	"beat him when he held an axe or warhammer in hand."));
    set_alarm(16.0,0.0, &command("whisper "+WHO(TP)+
	" Some say his family was blessed by Reorx, for he had a "+
	"daughter of surpassing beauty and kindness, Karyth."));
    set_alarm(18.5,0.0, &command("whisper "+WHO(TP)+
	" She was well loved by all... By one, far too much."));
    set_alarm(20.0,0.0, &command("whisper "+WHO(TP)+
	" There was one who covetted her, one who Teregul treated "+
	"like a son, one who was trained by Teregul himself in "+
	"the arts of combat, becoming second only to Teregul in "+
	"skill and prowess."));
    set_alarm(22.5,0.0, &command("whisper "+WHO(TP)+
	" His advances were rejected by the daughter of his mentor, "+
	"as Karyth's heart was lost to another warrior."));
    set_alarm(24.0,0.0, &command("whisper "+WHO(TP)+
	" In a rage, he took her and shamed her in a way "+
	"only scum like goblin do to the women of those they "+
	"ravage..."));
    set_alarm(26.5,0.0, &command("emote shakes visibly with "+
	"fury."));
    set_alarm(28.0,0.0, &command("emote takes another long "+
	"swig from his mug of craft brew."));
    set_alarm(35.5,0.0, &command("whisper "+WHO(TP)+
	" He fled... knowing justice would be swift and "+
	"unmerciful."));
    set_alarm(37.0,0.0, &command("whisper "+WHO(TP)+
	" Karyth, in despair, threw herself into Argin's "+
	"stream... her body was never recovered. Some "+
	"say her spirit still haunts the stream, awaiting "+
	"one to avenge her."));
    set_alarm(39.5,0.0, &command("whisper "+WHO(TP)+
	" Teregul became a shell of himself at the news of "+
	"his beloved daughters death. Not long after, he died "+
	"of grief. He was buried in a cairn not far from Iron "+
	"Delving."));
    set_alarm(41.0,0.0, &command("sigh sadly"));
    set_alarm(45.5,0.0, &command("whisper "+WHO(TP)+
	" And of the one who shamed her, we have heard no "+
	"word. He must have fled to the far corners of Ansalon."));
    set_alarm(48.0,0.0, &command("whisper "+WHO(TP)+
	" Curse him to the fires of Reorx's forge! His name "+
	"I shall not speak, as it is like poison on the tongue."));
    set_alarm(51.5,0.0, &command("whisper "+WHO(TP)+
	" But you would know him if you see him, as he carries "+
	"a weapon that dates back to the Dwarfgate wars, his "+
	"pride and joy."));
    set_alarm(53.0,0.0, &command("whisper "+WHO(TP)+
	" Avenge Karyth, mighty warrior. For the pride "+
	"of the Neidar clan."));
    set_alarm(55.5,0.0, &command("whisper "+WHO(TP)+
	" And remember! Speak not of this to anyone! To do so "+
	"would disrespect Teregul and Karyth. Now go, with "+
	"your axe held high, my friend."));
    set_alarm(58.0,0.0, &command("emote turns back to his "+
	"mug of craft brew."));
    return "";
}


void
attacked_by(object ob)
{
    command("say You're going to regret that!");

    if(!wielded_weapon)
    {
	clone_object(AXE)->move(TO);
	command("wield all");
	wielded_weapon = 1;
    }
    ::attacked_by(ob);
}
