/* Kashik Guards
 * Created 15 March 1995
 * by Chaos
 */

inherit "/std/monster";

#include "/d/Cirath/common/teamfnc.h"
#include "defs.h"
#include <money.h>

create_monster()
{
	set_name("kashik");
	set_race_name("human");
	set_adj("battle-hardened");
	set_long("This is a member of the Khahan's elite guard known "+
		"as the Kashik.  They have been chosen for thier "+
		"exceptional skill and ability to protect the life "+
		"of their Khahan.  His hair is worn in long braids, "+
		"bound with silver disks and tassels of blue yarn.\n");
	set_gender(0);
	set_stats(({140,140,140,110,110,140}));
	set_skill(SS_WEP_SWORD,85);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);


}

arm_me()
{
        MONEY_MAKE_SC(random(10)+1)->move(TO);
   clone_object(KAT_DIR+"equipment/ksword")->move(TO);
	clone_object(KAT_DIR+"equipment/kalat1")->move(TO);
	command("wear all");
	command("wield all");
}

void
do_hide()
{
     add_prop(OBJ_I_HIDE, 75);
}
