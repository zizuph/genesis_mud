/*
 * Master include file for making money on any npc. 5 April 1994 Mayhem
 * Clone money for npcs according to average stat
 * Idea, formulas, code by Mayhem@Genesis
 * Modified for Gondor by Olorin, August 1994
 *
 * How to use this:
 * In arm_me(), call: get_money();
 *
 * Modification log:
 * Changed to inherit, Olorin, Feb 1997.
 *
 * This version is obsolete!
 * Replace it in old files and do not use it in new ones!
 * inherit /d/Gondor/common/lib/make_money.c instead!
 *
 */
#include <files.h>
#include <money.h>

private varargs void
make_money(int i, string type = "copper")
{
    object money;

    if ((i < 0) || (member_array(type, MONEY_TYPES) < 0))
        return;

    seteuid(getuid(this_object()));

    log_file("money", file_name(this_object()) + " includes make_money.h!\n");

    money = clone_object(COINS_OBJECT);
    money->set_heap_size(i);
    money->set_coin_type(type);
    if (money->move(this_object()))
	money->move(this_object(), 1);
}

static void
get_money()
{
    int     npc_avg = this_object()->query_average_stat(),
            ran_num = random(13),
            am1 = 0,
            am2 = 0;
    string  type1 = "copper",
            type2 = "silver";

    switch (npc_avg)
    {
    case 0..24:
	am1 = npc_avg + ran_num;
	break;
    case 25..36:
	am1 = npc_avg / 2 + ran_num;
	am2 = 1 + ran_num / 4;
	break;
    case 37..60:
	am1 = npc_avg / 3 + ran_num;
	am2 = npc_avg / 12 + ran_num / 3;
	break;
    case 61..84:
	am1 = npc_avg / 4 + ran_num;
	am2 = npc_avg / 6 + ran_num / 2;
	break;
    case 85..108:
	am1 = npc_avg / 12 + ran_num;
	type1 = "silver";
	am2 = random(npc_avg / 36) + ran_num / 6;
	type2 = "gold";
	break;
    case 109..144:
	am1 = npc_avg / 12 + ran_num / 2;
	type1 = "silver";
	am2 = npc_avg / 36 + ran_num / 4;
	type2 = "gold";
	break;
    default:
	am1 = npc_avg / 24 + ran_num;
	type1 = "silver";
	am2 = npc_avg / 24 + ran_num / 3;
	type2 = "gold";
	break;
    }

    if (am1 > 0)
        make_money(am1, type1);
    if (am2 > 0)
        make_money(am2, type2);
}
