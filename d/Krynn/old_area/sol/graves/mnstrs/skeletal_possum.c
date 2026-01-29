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
inherit "/std/act/attack";


void
create_creature()
{

	set_name("possum");
	set_race_name("possum");
	set_long("This animal is all bone! It has no flesh but it is still alive!\n"
		 + "Its a bit hard to make out but you think it might have once\n"
		 + "been a cat.\n");
	set_adj("undead");

        set_stats( ({ 10, 10, 10, 10, 10, 20 }) );
	set_attack_unarmed(1,  1,  1, W_IMPALE, 40, "bite");

	set_hitloc_unarmed(1,  4, 30, "body");
	set_hitloc_unarmed(2,  4, 32, "right foreleg");
	set_hitloc_unarmed(4,  4, 32, "left hindleg");
	set_hitloc_unarmed(8,  4,  6, "head");
	

	set_alignment(-3);
        set_aggressive(1);
	set_knight_prestige(10);
	set_chat_time(6);
	add_chat("melowug");
	add_chat("Hissth");
	add_chat("Screacgh");
	add_prop(LIVE_I_NO_CORPSE, 1);
 

}



void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","possum");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","possum");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","possum");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","possum");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","possum");
    ob->move(E(TO));
    ::do_die(killer);
}
