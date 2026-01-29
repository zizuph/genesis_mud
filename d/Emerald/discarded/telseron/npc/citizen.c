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

   featurelook = ({"olive-skinned", "long-haired", "grey-haired",
	"dark-eyed", "pudgy", "tan-skinned", "light-skinned",
	"ivory-skinned", "wrinkled", "blue-eyed", "green-eyed",
	"brown-haired", "chestnut-haired", "brown-eyed",
	"red-haired", "round-nosed", "blonde-haired", "thin-nosed",
	"silver-haired", "hawk-nosed", "white-skinned", "thin-lipped",
	"porcelain-skinned", "rosey-cheeked", "slack-jawed", "dimpled"});

   alignlook = ({"proud", 0, "proud", 50, "proud", -50, "good natured", 200,
	"confident", 50, "kindly", 300, "cheerful", 100, "nice", 100,
	"sweet", 100, "gentle", 200, "calm", 50, "trustworthy", 300,
	"smiling", 100, "bemused", 50, "devout", 400, "honourable", 400,
	"mischevious", 0, "impartial", 0, "indifferent", 0, "passive", 0,
	"ordinary", 0, "nasty", -300, "maelevolent", -400, "selfish", -100,
	"mean-spirited", -200, "rude", -50, "callous", -75, "mean",
	-150, "sinister", -300, "grating", -50, "slimy", -300, "leacherous",
	-200, "shadowy", -200 });

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   set_alignment(alignlook[y+1]);
   set_race_name("elf");
   set_long("This elf is a citizen of the Elven city of Telseron. "+
	"As the city is full of elves of different walks of life, "+
	"one can never generalize the behaviors of these citizens."+
	" @@align_extra");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_short(featurelook[x] + " " + alignlook[y] + " " + query_race_name() + " citizen");
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_m_in("walks in.");
   set_m_out("walks");
   set_gender(random(2));
   set_restrain_path( ({ TELSERON_DIR }) );
   set_random_move(5);
   set_whimpy(40);
   MONEY_MAKE_CC(20 + random(11))->move(TO, 1);
   MONEY_MAKE_SC(random(5))->move(TO, 1);
   add_equipment(my_equip());
}

public string
align_extra()
{

	switch (TO->query_alignment())
	  {
	  case -100000..-100:
	    return "This specific elf looks like " + HE_SHE(TO) + " is " +
		"capable of any evil.\n";
	  case -99..-1:
	    return "This one appears to be one of the elves less inclined to good deeds.\n";
	  case 0..99:
	    return "This particular elf appears to care little about anyone "+
		"other than " + HIM_HER(TO) + "self.\n";
	  case 100..299:
	    return "This citizen wears a beaming smile and " + HE_SHE(TO) +
		" seems very friendly.\n";
	  case 300..100000:
	    return "This elf maintains a look of peace and harmony that spreads like an aura of joy to the people around " + HIM_HER(TO) + ".\n";
	  }
}

my_equip()
{

	string mywep, myarm, myarm2;
	int g, h;
	g = random(5);
	h = random(5);
	switch (g)
	{
		case 0:
			mywep = "/d/Emerald/wep/trv_quarterstaff";
			break;
		case 1:
			mywep = "/d/Emerald/wep/trv_walking_stick";
			break;
		case 2:
			mywep = "/d/Emerald/wep/trv_curved_dagger";
			break;
		case 3:
			mywep = "/d/Emerald/wep/trv_sharp_knife";
			break;
		case 4:
			mywep = "/d/Emerald/wep/trv_shortsword";
			break;
		default:
			break;
	}

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
  if(TO->query_alignment() > 50)
     ::get_assistance(enemy);
}
