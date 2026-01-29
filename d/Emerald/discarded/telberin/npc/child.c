inherit "/d/Emerald/std/emerald_monster.c";
inherit "/d/Emerald/std/aid_npc.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Emerald/defs.h"

mixed my_equip();
public string align_extra();

void
create_emerald_monster()
{
   int x, y;

   string *featurelook;
   mixed *alignlook;

   featurelook = ({"olive-skinned", "long-haired", "short-haired",
	"dark-eyed", "pudgy", "tan-skinned", "light-skinned",
	"ivory-skinned", "runny-nosed", "blue-eyed", "green-eyed",
	"brown-haired", "chestnut-haired", "brown-eyed",
	"red-haired", "round-nosed", "blonde-haired", "thin-nosed",
	"silver-haired", "hawk-nosed", "white-skinned", "thin-lipped",
	"porcelain-skinned", "rosey-cheeked", "slack-jawed", "dimpled"});

   alignlook = ({"proud", 0, "proud", 50, "good natured", 200,
	"confident", 50, "well-behaved", 300, "cheerful", 100, "nice", 100,
	"sweet", 100, "gentle", 200, "calm", 50, "trustworthy", 300,
	"smiling", 100, "bemused", 50, "devout", 300, "honourable", 400,
	"mischevious", 0, "impartial", 0, "indifferent", 0, "passive", 0,
	"ordinary", 0, "nasty", -100, "selfish", -100,
	"rude", -50, "naughty", -75, "frowning", -50, "troublemaking", -200,
	 "bratty", -200 });

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   set_alignment(alignlook[y+1]);
   set_race_name("elf");
   add_name("child");
   set_random_move(5);
   set_long("This elf child is one of many that wander around the Elven "+
	"capital city of Telberin." +
	" @@align_extra");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_short(featurelook[x] + " " + alignlook[y] + " " + query_race_name() + " child");
   set_stats(({ 20+random(10), 20+random(15), 20+random(10),
		20+random(20), 20+random(20), 20}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_gender(random(2));
   set_act_time(7);
   set_chat_time(10);
   set_cact_time(5);
   set_cchat_time(6);
   set_m_in("wanders in.");
   set_m_out("wanders");
   set_restrain_path( ({ "/d/Emerald/telberin" }) );
   set_whimpy(60);
   MONEY_MAKE_CC(random(4))->move(TO, 1);
   add_equipment(my_equip());
}

public string
align_extra()
{

	switch (TO->query_alignment())
	  {
	  case -100000..-100:
	    TO->add_act("grin nast");
	    TO->add_act("swear");
	    TO->add_chat("Yah...just try and dicipline me");
	    TO->add_cact("panic");
	    TO->add_cchat("Get offa me!!");
	    return "This little terror wanders around the streets" +
		" just looking to get into trouble. " +
		 capitalize(HE_SHE(TO)) + " seems to make everyone "+
		"clutch their purses just a little closer to their "+
		"chest just by looking at them.\n";
	  case -99..-1:
            TO->add_act("smirk");
            TO->add_act("giggle misc");
	    TO->add_chat("Hehe...I'm good when I'm good...I'm better when "+
		"I'm bad.");
	    TO->add_cact("panic");
	    TO->add_cchat("Help!!");
	    return "This little bratty elf seems to just fall into trouble. "+
		capitalize(HE_SHE(TO)) + " may not mean to be naughty, but "+
		"it's just in " + TO->query_possessive() + " nature.\n";
	  case 0..99:
	    TO->add_act("smile slight");
	    TO->add_act("yawn");
	    TO->add_chat("Hi. How do you like Telseron?");
	    TO->add_cact("panic");
	    TO->add_cchat("Help!! Guards!!");
	    return "This kid seems to be your average little inhabitant of " +
		"Telberin. " + capitalize(HE_SHE(TO)) + " doesn't seem "+
		"to be particularly good or naughty.\n";
	  case 100..299:
	    TO->add_act("smile hap");
	    TO->add_act("greet all");
	    TO->add_chat("Greetings stranger!");
	    TO->add_cchat("Help me please!!");
	    return "This charming child smiles happily at everyone " +
	        HE_SHE(TO) + " meets.\n";
	  case 300..100000:
	    return "This elf maintains a look of peace and harmony that " +
		"spreads like an aura of joy to the people around " +
		 HIM_HER(TO) + ".\n";
	  }
}

my_equip()
{

	string mywep, myarm, myarm2;
	int h;

	mywep = "/d/Emerald/wep/trv_curved_dagger";

	h = random(5);

	switch (h)
	{
		case 0:
			myarm = "/d/Emerald/arm/trv_cloak";
			myarm2 = "/d/Emerald/arm/trv_black_tunic";
			return ({ mywep , myarm , myarm2 });
			break;
		case 1:
			myarm = "/d/Emerald/arm/trv_black_tunic";
			return ({ mywep ,  myarm });
			break;
		case 2:
			myarm = "/d/Emerald/arm/trv_red_tunic";
			return ({ mywep ,  myarm });
			break;
		case 3:
			myarm = "/d/Emerald/arm/trv_leather_shirt";
			myarm2 = "/d/Emerald/arm/trv_leather_boots";
			return ({ mywep , myarm , myarm2 });
			break;
		case 4:
			myarm = "/d/Emerald/arm/trv_robes";
			return ({ mywep ,  myarm });
			break;
		default:
			break;
	}
}

void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}

get_assistance(object enemy)
{
  /* guards will help even evil kids that aren't in a gang */
     ::get_assistance(enemy);
}

int query_knight_prestige() { return -100; }
