/*
 * THIS FILE IS OBSOLETE! NEW CODE SHOULD NOT USE IT!
 *
 * INSTEAD, USE MACROS DEFINED IN <money.h>
 * FOR MONSTERS USE PROPERTY: OBJ_M_HAS_MONEY
 *
 * Mercade, 3 March 2007
 */

/* Master include file for making money on any npc. 5 April 1994 Mayhem */
/* How to use this crazy(?) system:
    First determine if you are including /d/Shire/common/defs.h.
    If you aren't, then you have to type a little more.
    If you are, within create_monster/creature/etc enter the following:
    MAKE_MONEY;
    I always put it near the end of the function, but it isn't necessary.
    If you aren't, enter the following in the same general location:
    set_alarm(1.0,0.0,"get_money");
    Note: the 1.0 can be whatever you want I suppose, but don't make it
    repeating or your guy will have WAY too much money.

    In addition, I have made available the following functions:
    make_platinum(num);
    make_gold(num);
    make_silver(num);
    make_copper(num);
       
    All those are optional, and should only be used on exceptional npcs
    to 'pad the kitty'  (Ie, make them a little richer than normal)
    Of course, you could also use them on very poor npcs, just by giving
    them a few coppers and not calling the main, "get_money", function.

    The 'automatic' addition of money uses the stat average of your npc
    and some formulas I concocted. The formulas are subject to change
    as the environment of the mud changes (just a warning), else it
    should be fairly stable and dependable.
    There is a random bit added in, so things won't get boring and 
    familiar.
    Any questions? Mail me, I love mail.
   Mayhem, 12 April 1994
 * 
 * 
 * Cotillion, 2018-04-06
 * - Fixed get_money to use OBJ_MAS_MONEY. 
 * - Fixed broken switch() statement which fell through resulting in small
 *   npcs giving out gold. 
 */

#include <money.h>
#include <stdproperties.h>

void
make_money(int num, string type)
{
  seteuid(getuid(this_object()));
  
  MONEY_MAKE_HERE(num, type);
}

void make_gold(int coin_amount)
{
  make_money(coin_amount, "gold");
}

void make_silver(int coin_amount)
{
  make_money(coin_amount, "silver");
}

void make_copper(int coin_amount)
{
  make_money(coin_amount, "copper");
}
  
void make_platinum(int coin_amount)
{
  make_money(coin_amount, "platinum");
}

void
get_money()
{
    int cc, sc, gc, pc;
    int npc_avg = this_object()->query_average_stat();
    int ran_num = random(9);

    switch (npc_avg)
    {
        case 1..49:
            cc = npc_avg + ran_num;
            break;
        case 50..99:
            cc = npc_avg / 2 + ran_num;
            sc = npc_avg / 10 + ran_num / 3;
            break;
        case 100..149:
            sc = npc_avg / 5 + ran_num;
            if (!random(10))
            {
                gc = (npc_avg + 100) / ((1 + ran_num) * 10);
            }
            else
            {
                sc += npc_avg / 10 + ran_num / 2;
            }
            break;
        default:
            if (random(10) < 2)
            {
                pc = npc_avg / 110;
                gc = npc_avg / 20;
            }
            else
            {
                gc = npc_avg / 12;
                sc = npc_avg / 15 + 2 * ran_num;
            }
            break;
    }

    add_prop(OBJ_M_HAS_MONEY, ({ cc, sc, gc, pc }));
}
