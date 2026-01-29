/* Easy to kill undead animal by percy */

#include "/d/Krynn/common/defs.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Krynn/solace/graves/local.h"

inherit C_FILE
inherit "/std/act/chat";
inherit "/std/act/domove";

void
create_creature()
{
	int i;

	set_name("Skeletal rat");
	set_race_name("rat");
	set_long("This animal is all bone! It has no flesh but it is still alive!\n"
		 + "Its a bit hard to make out but you think it might have once\n"
		 + "been a rat.\n");
	set_adj("undead");

	set_random_move(20);
	
	for (i = 0; i < 6; i++)
		set_base_stat(i, 10 + random(8));

	set_attack_unarmed(1,  2,  2, W_IMPALE, 50, "bite");

	set_hitloc_unarmed(1,  4, 30, "body");
	set_hitloc_unarmed(2,  4, 32, "right foreleg");
	set_hitloc_unarmed(4,  4, 32, "left hindleg");
	set_hitloc_unarmed(8,  4,  6, "head");
	
	set_alignment(-20);
	set_knight_prestige(5);
	set_monster_home(TDIR+"grave3");
	set_restrain_path(TDIR);
	set_chat_time(6);
	add_chat("meepk");
	add_chat("Slklipp");
	add_chat("blibble");
	add_prop(LIVE_I_UNDEAD, 1);
	add_prop(LIVE_I_NO_CORPSE, 1);

}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","rat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","rat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","rat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","rat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","rat");
    ob->move(E(TO));
    ::do_die(killer);
}
