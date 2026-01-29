/* Camp Guards
 * Created 9 March 1995
 * by Chaos
 */

inherit "/std/monster";

#include "defs.h"
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

create_monster()
{
	set_name("guard");
	set_race_name("human");
	set_adj("weather-beaten");
	add_adj("battle-scarred");
	set_long("The border guard of this encampment has a "+
		"weather beaten look about him that makes it "+
		"impossible to determine his age.  He "+
		"has a long, thin mustache and wears his hair in long "+
		"braids hanging past his ears.  He has also shaved "+
		"the crown of his head, as is common among his people.\n");  

	set_stats(({10,10,10,5,5,10}));
	set_skill(SS_WEP_SWORD,40);
	set_skill(SS_DEFENCE,45);
	set_skill(SS_AWARENESS,35);
   set_alignment(random(100) - 50);

}

arm_me()
{
   MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   clone_object(KAT_DIR+"equipment/saber")->move(TO);
   clone_object(KAT_DIR+"equipment/kalat2")->move(TO);
	command("wear all");
	command("wield all");
}
