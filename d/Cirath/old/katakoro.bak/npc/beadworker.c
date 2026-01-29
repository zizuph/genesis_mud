/* Beadworker
 * 17 April 1995, Chaos
 */

inherit "/std/monster";

#include "defs.h"
#include <money.h>


create_monster()
{
   set_name("beadworker");
	set_race_name("human");
   set_adj("weary");
   add_adj("squinty-eyed");
   set_long("This is the beadworker of the Khahan's camp, he has "+
	"spent many years at this task and is quite skilled at "+
	"shaping just about anything into finely detailed beads.  "+
	"Because of the many years of detailed work, his eyes are "+
	"constantly squinted.\n");

   set_stats(({30,45,20,15,15,25}));
   set_skill(SS_WEP_KNIFE,20);
   set_skill(SS_DEFENCE,23);
	set_alignment(random(100) - 50);
	
}

arm_me()
{
   MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   clone_object(KAT_DIR+"equipment/avgkalat")->move(TO);
   clone_object(KAT_DIR+"equipment/avgknife")->move(TO);
   command("wield all");
   command("wear all");
}

