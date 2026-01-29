inherit "/d/Emerald/std/emerald_monster.c";
inherit "/d/Emerald/std/aid_npc.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Emerald/defs.h"

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

   alignlook = ({"proud", 50, "good natured", 200, "confident", 50,
	 "kindly", 300, "cheerful", 100, "nice", 100, "sweet", 100,
	 "gentle", 200, "calm", 50, "trustworthy", 300, "smiling", 100,
		 "bemused", 50, "devout", 400, "honourable", 400 });

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   set_alignment(alignlook[y+1]);
   add_name("lady");
   add_name("lady-in-waiting");
   set_race_name("elf");
   set_long("This graceful elf is one of many ladies-in-waiting. They "+
	"attend to the needs of the Queen, and other female royalty. "+
	"Always up on the castle gossip, they can be seen whispering "+
	"the latest news to each other as they run about the castle "+
	"taking care of the boring details of the royals lives.\n");

   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_stats(({ 10+random(20), 20+random(15), 20+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_m_in("runs in.");
   set_m_out("runs");
   set_whimpy(50);
   set_gender(1);
   set_restrain_path( ({ TELSERON_DIR + "castle/" }) );
   set_random_move(5);
   MONEY_MAKE_SC(random(5))->move(TO, 1);
   add_equipment( ({TELSERON_DIR + "arm/lady_dress.c"}) );
}

void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}

get_assistance(object enemy)
{
     command("emote Cries out for help!");
     ::get_assistance(enemy);
}
