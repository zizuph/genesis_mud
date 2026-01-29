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

	set_name("Skeletal cat");
	set_race_name("cat");
	set_long("This animal is all bone! It has no flesh but it is still alive!\n"
		 + "Its a bit hard to make out but you think it might have once\n"
		 + "been a cat.\n");
	set_adj("undead");

	set_random_move(10);
	
	for (i = 0; i < 6; i++)
		set_base_stat(i, 5 + random(5));
	set_attack_unarmed(1,  1,  1, W_IMPALE, 70, "bite");

	set_hitloc_unarmed(1,  4, 30, "body");
	set_hitloc_unarmed(2,  4, 32, "left foreleg");
	set_hitloc_unarmed(4,  4, 32, "right hindleg");
	set_hitloc_unarmed(8,  4,  6, "head");
	
	set_alignment(-20);
	set_knight_prestige(5);
	set_monster_home(TDIR+"grave3");
	set_restrain_path(TDIR);
	set_chat_time(6);
	add_chat("melowug");
	add_chat("Hissth");
	add_chat("Screacgh");
	add_prop(LIVE_I_UNDEAD, 1);
	add_prop(LIVE_I_NO_CORPSE, 1);

}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","cat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","cat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","cat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","cat");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","cat");
    ob->move(E(TO));
    ::do_die(killer);
}
