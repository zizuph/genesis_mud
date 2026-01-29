/* Empress
 * 18 April 1995, Chaos
 */

inherit "/std/monster";

#include "defs.h"
#include <money.h>

create_monster()
{
   set_name("empress");
	set_race_name("human");
   set_adj("vibrant");
   add_adj("bright-eyed");
   set_long("This is the wife of the Khahan, called mother by "+
	"the majority of the tribe.  This also is true for the "+
	"Khahan as well, as she is his mother.  It is tradition "+
	"for the son to marry his defeated father's widow, and "+
	"so this marriage is in name only.  Still the Empress "+
	"has great power among the followers of the Khahan.  It "+
	"would not be wise to cross her.\n");

   set_gender(1);
   set_stats(({75,110,80,120,125,90}));
   set_skill(SS_WEP_KNIFE,80);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);
	set_skill(SS_PARRY,85);

}

arm_me()
{
	MONEY_MAKE_SC(random(25)+1)->move(TO,1);
   clone_object(KAT_DIR+"equipment/ekalat")->move(TO);
   clone_object(KAT_DIR+"equipment/eknife")->move(TO);
	command("wear all");
	command("wield all");
}

