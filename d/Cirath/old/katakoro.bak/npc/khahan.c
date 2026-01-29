/* Khahan
 * Created 15 March 1995
 * by Chaos
 */

inherit "/std/monster";

#include "defs.h"
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

create_monster()
{
	set_name("khahan");
	set_race_name("human");
	set_adj("impressive");
	add_adj("dark-eyed");
	set_long("This is the Khahan of of the endless wastes.  He is "+
		"short man, but still an imposing figure.  From the scars "+
		"on his face it is obvious that he is not a stranger to "+
		"battle.  He wears his hear long, similar to that of the "+
		"men in his army, and has similarly shaved the crown of "+
		"his head.  For a man that wield such power, he seems "+
		"rather average looking.\n");

	set_stats(({140,120,140,90,100,150}));
	set_skill(SS_WEP_SWORD,85);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);
	set_skill(SS_PARRY,85);
	set_skill(SS_2H_COMBAT,83);

}

arm_me()
{
	MONEY_MAKE_SC(random(25)+1)->move(TO,1);
	clone_object(KAT_DIR+"equipment/jacket")->move(TO);
	clone_object(KAT_DIR+"equipment/robe")->move(TO);
	clone_object(KAT_DIR+"equipment/kkupba")->move(TO);
 	clone_object(KAT_DIR+"equipment/knife")->move(TO);
	clone_object(KAT_DIR+"equipment/khansword")->move(TO);
	command("wear all");
	command("wield all");
}

