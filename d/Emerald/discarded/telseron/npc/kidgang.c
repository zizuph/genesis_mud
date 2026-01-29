inherit "/d/Emerald/std/emerald_monster.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Emerald/defs.h"

int my_gender();
mixed my_equip();

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

   alignlook = ({"proud", -50, "nasty", -300, "maelevolent", -400,
	 "selfish", -100,
	"mean-spirited", -200, "rude", -50, "callous", -75, "mean",
	-150, "sinister", -300, "grating", -50, "slimy", -300, "leacherous",
	-200, "shadowy", -200 });

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   set_alignment(alignlook[y+1]);
   set_race_name("elf");
   set_long("This elf looks like a hardened, rough child. "+
	capitalize(HE_SHE(TO)) + " is usually seen running around "+
	"with a group of kids and a leader, looking for trouble.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_short(featurelook[x] + " " + alignlook[y] + " " + query_race_name() + " kid");
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 40+random(30));
   set_skill(SS_PARRY, 40);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_gender(my_gender());
   set_restrain_path( ({ "/d/Emerald/telseron" }) );
   set_m_in("runs in.");
   set_m_out("runs");
   set_whimpy(40);
   MONEY_MAKE_CC(4 + random(4))->move(TO, 1);
   add_equipment(my_equip());
}

int 
my_gender()
{
    int p;
    p = random(3);
    switch(p)
      {
      case 0:
	{
	return 1;
	break;
	}
      case 1..2:
	{
	return 0;
	break;
	}
      }
}

my_equip()
{

	string mywep, myarm, myarm2;
	int g, h;
	h = random(5);
			mywep = "/d/Emerald/telseron/wep/shiv";
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
  object *teamothers;
  int i;
  ::attacked_by(enemy);
  teamothers = TO->query_team_others();
  command("say Help me!!");
  for( i = 0 ; i < sizeof(teamothers) ; i++ )
    {
	teamothers[i]->help_me_out(enemy);
    }
}

void
help_me_out(object nastyone)
{
  if(!query_attack())
    {
        command("emote jumps in to help "+HIS_HER(TO)+" friend!");
	attack_object(nastyone);
    }
}
