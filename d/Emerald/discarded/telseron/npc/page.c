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
	 "gentle", 200, "calm", 50, "trustworthy", 300, "smiling",
	 100, "bemused", 50, "devout", 400, "honourable", 40});

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   add_adj("young");
   set_alignment(alignlook[y+1]);
   set_race_name("elf");
   set_long("This young elf is a page who runs around doing errands for "+
	"their knight or lord. They are kept rather busy with mundane "+
	"tasks, but they do them dutifully in the hope that they might "+
	"one day gain the rank of squire.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_m_in("runs in.");
   set_m_out("runs");
   set_whimpy(35);
   set_gender(0);
   set_restrain_path( ({ TELSERON_DIR + "castle/" }) );
   set_random_move(5);
   MONEY_MAKE_CC(20 + random(11))->move(TO, 1);
   add_equipment( ({ TELSERON_DIR + "wep/pagesword",
		       TELSERON_DIR + "arm/pagetunic" }) );
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
