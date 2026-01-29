/* Gunthar's guards by Morrigan, Jan 11, 97 */

#include "../../local.h"

inherit NPCSTD + "vin_knight_base";

void
create_knight_npc()
{
    set_block_dir("south");
    set_level(3 + random(3));
    set_alarm(0.1, 0.0, "do_stats");
}


void do_stats()
{
    int i;

    for (i=0;i<6;i++)
	set_base_stat(i, 150 + (6 * level));

    TO->set_hp(TO->query_max_hp());
}

