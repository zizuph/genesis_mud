/* 
 * Base for members of the Brix gang in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.
 *
 * Mortis 05.2006
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE
inherit AUTO_TEAM

/*prototype*/

int alrm;
string adj1, adj2, myshort;

public void
create_brix_ganger()
{
}

void
create_krynn_monster()
{
    set_pick_up_team("_brix_ganger");
    set_max_team_size_auto_join(5);

	create_brix_ganger();
}

void
remove_alrm()
{
	alrm = 0;
}

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
        return;
    
	if (random(4) == 1)
		command("asay laugh This " + one_of_list(({"walkuh", "bad A",
		"gongo", "chungalungo", "cow", "smif", "pot for a head", "fat A",
		"patty licker", "bung", "krell-eater", "staff polisher",
		"sword stroker"})) + " wants to get smashed.  Le's oblige!");

    action_attack(enemy);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();

	if (TP->query_prop(LIVE_I_ATTACKED_BRIX) == 1)
    {
		if (alrm == 1)
			return;

		alrm = 1;

		set_alarm(1.5, 0.0, "remove_alrm");
        set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_BRIX, 1);

    ::attacked_by(ob);
}
