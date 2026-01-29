/* The normal guards by Percy. */
// defense raised and do_heal func added by Grace 20 Sept 1995

#include "../local.h"
#include <formulas.h>
#include <macros.h>

inherit VSTD + "vin_knight_base";

#define OUTKEEP VROOM + "gate"

int i_am_alarmed = 0;

void
create_knight_npc()
{
    set_level(random(2) + 2);
    set_block_dir("out");
    add_cact("@@do_heal");
}
void
init_living()
{
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
	set_alarm(0.5, 0.0, "attack_func", TP);
    ::init_living();
    ADD("alarm_me","alarm");
}

int
alarm_me(string str)
{
    NF("What?\n");
    if (!(TP->id("knight") || TP->query_guild_name_occ() == "Solamnian Knights"))
	return 0;
    if (E(TO) == find_object(OUTKEEP))
	return 0;
    if (i_am_alarmed)
	return 0;
    if (str == "guard" || str == "guards")
    {
	i_am_alarmed = 1;
	NF("You alarm the guards.\n");
	if (str == "guards")
	    command("alarm guards");
	else
	    write("You alarm a guard.\n");
	command("out");
	command("south");
	command("south");
	do_rescue();
	/*attack_object(.....)*/
	/* should be a normal attacking here in case the rescue fails*/
	return 1;
    }
    return 0;
}

void
set_me_alarmed(int i)
{
    i_am_alarmed = i;
}

void
do_heal()
{
    command("smile joy");
    TO->heal_hp(100+random(50));
}
