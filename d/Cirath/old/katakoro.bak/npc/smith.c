/* Smith
 * 18 April 1995, Chaos
 */

inherit "/std/monster";

#include "defs.h"
#include <money.h>


create_monster()
{
   set_name("metalsmith");
	set_race_name("human");
   set_adj("dark-skinned");
   add_adj("muscular");
   set_long("This man is obviously not of the Khahan's tribe, and "+
	"is most likely not a member of any of the steppes tribes.  "+
 	"His dark skin and large stature sets him apart from the "+
	"rest of the people here.  His skill in working with metal "+
	"must be great for the Khahan to allow him to remain among "+
	"his troops.\n");

   set_stats(({40,35,45,25,35,30}));
   set_skill(SS_WEP_CLUB,30);
   set_skill(SS_DEFENCE,33);
	set_alignment(random(100) - 50);
	
}

arm_me()
{
   MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   clone_object(KAT_DIR+"equipment/del")->move(TO);
   clone_object(KAT_DIR+"equipment/hammer")->move(TO);
   command("wield all");
   command("wear all");
}

