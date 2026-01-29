/* 
 * Base for hobgoblins in a cave along the road
 * south of Palanthas.
 *
 * Mortis 10.2006
 *
 */

#include "../local.h";
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE

/*prototype*/

public void
create_vin_hobgoblin()
{
}

void
create_krynn_monster()
{
	set_aggressive(1);

	create_vin_hobgoblin();
}

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
        return;

	if (QRACE(enemy) == "hobgoblin" &&
		enemy->query_prop(LIVE_I_ATTACKED_SOL_HOBS) != 1)
		return;

	string adv = one_of_list(({"craz", "rough", "angr", "aggress"}));

	if (random(3) == 1)
		command("asay " + adv + " This " + one_of_list(({"flugg", "doo doo",
		"mack", "sludge licker", "cow", "gobbo", "dead elf", "bone treat",
		"ladder climber"})) + " wants to feed its body to the tribe.  "
		+ "Chow down!");

    action_attack(enemy);
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_SOL_HOBS, 1);

    ::attacked_by(ob);
}
