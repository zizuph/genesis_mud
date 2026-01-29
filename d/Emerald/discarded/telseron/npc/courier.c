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

   alignlook = ({"proud", 50, "good natured", 200,
	"confident", 50, "kindly", 300, "cheerful", 100, "nice", 100,
	"sweet", 100, "gentle", 200, "calm", 50, "trustworthy", 300,
	"smiling", 100, "bemused", 50, "devout", 400, "honourable", 400,});

   x = random(sizeof(featurelook));
   y = random(sizeof(alignlook)/2)*2;
   add_adj(featurelook[x]);
   add_adj(alignlook[y]);
   set_alignment(alignlook[y+1]);
   set_race_name("elf");
   add_name("courier");
   set_long("This elf is wearing a tunic emblazoned with the mark of "+
	"the Royal House of Telseron. He appears to be some sort of "+
	"courier delivering a message to another Emerald kingdom.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_m_in("dashes in.");
   set_m_out("dashes");
   set_random_move(4);
   set_restrain_path( ({ TELSERON_DIR, TELSERON_DIR + "castle" }) );
   set_whimpy(80);
   set_gender(0);
   add_equipment( ({TELSERON_DIR + "wep/cour_dagger",
		TELSERON_DIR + "arm/cour_tunic",
		TELSERON_DIR + "arm/cour_cap"}) );
   MONEY_MAKE_SC(5 + random(1))->move(TO, 1);
}


void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}

get_assistance(object enemy)
{
     command("shout Guards!! Help me now!!");
     ::get_assistance(enemy);
}
