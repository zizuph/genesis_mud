/* A coffer for the money of the knights. It is possible to deposit coins
 * in it, or withdraw coins from it. Deposits and withdrawals are accounted
 * into the CHARITY skill.
 * 
 *
 * ~Aridor 04/97
 *
 * Modifications:
 */

#include <money.h>
#Include <language.h>
#include "../knight/guild.h"

inherit "/std/object";

private int copper = 0;
private int silver = 0;
private int gold = 0;
private int platinum = 0;

string
money2string()
{
    string str = "";
    int morethanone = 0;
    if (platinum)
    {
	if (platinum != 1)
	  morethanone = 1;
	str += LANG_ASHORT(platinum);
    }
    if (gold)
    {
	if (gold != 1 || str != "")
	  morethanone = 1;
	str += LANG_ASHORT(gold);
    }
    if (silver)
    {
	if (silver != 1 || str != "")
	  morethanone = 1;
	str += LANG_ASHORT(silver);
    }
    if (copper)
    {
	if (copper != 1 || str != "")
	  morethanone = 1;
	str += LANG_ASHORT(copper);
    }

    if (morethanone)
      str = "are " + str;
    else
      str = "is " + str;
    return str;
}

void
create_object()
{
    set_name("coffer");
    add_adj("knight");
    set_short("coffer");
    set_long("This coffer looks much like a treasure chest. Currently, there " +
	     "@@money2string@@ in it.\n");

    load_object(MASTER);
}

void
init()
{
    ADA("withdraw");
    ADA("deposit");
    ::init();
}

int
withdraw(string str)
{
    object withdraw;
    int chskill, value = 0;
    int amt;
    string tpe;

    NF("Only Knights of Solamnia may use this coffer!\n");
    if (!MEMBER(TP))
      return 0;

    NF("Withdraw what? You can only withdraw coins.\n");
    if (!str)
      return 0;

    if (sscanf(str,"%d %s coins",amt,tpe) != 2)
      return 0;

    if (member_array(tpe,MONEY_TYPES) < 0)
      return 0;

    chskill = TP->query_skill(SS_CHARITY);

    withdraw = MONEY_MAKE(amt,tpe);
    value = withdraw->query_value();
    
    if (chskill < value)
      
    chskill = chskill - (value*3);
    /* We need some really elaborate formula here!!!!!
     * Coin type should be taken into account!
     * 
     */
    TP->set_skill(SS_CHARITY, chskill);
    write("You withdraw " + COMPOSITE_DEAD(deposit) + " from the coffer " +
	  "of the Knights of Solamnia.\n");
    say(QCTNAME(TP) + " makes a transaction at the coffer of the " +
	"Knights of Solamnia.\n");
    if (withdraw->move(TP))
    {
	withdraw->move(E(TP),1);
	write("You drop some of the money.\n");
    }
    return 1;
}

int
manip_drop_access(object ob)
{
    if (!objectp(ob))
	return 0;
    if (function_exists("create_coins",ob) != "/std/coins")
        return 0;
    return (environment(ob) == this_player());
}

int
deposit(string str)
{
    function f;
    object tmp1, tmp2;
    object *deposit = ({ });
    int i, value = 0, chskill;

    NF("Only Knights of Solamnia may use this coffer!\n");
    if (!MEMBER(TP))
      return 0;

    NF("Deposit what? You can only deposit coins.\n");
    if (!str)
      return 0;

    if (!parse_command(str, E(TP),"%i",deposit))
      return 0;

    deposit = CMDPARSE_STD->normal_access(deposit,"manip_drop_access",TO,0);
    
    if (sizeof(deposit) == 0)
      return 0;

    tmp1 = find_object("/cmd/live/things");
    tmp2 = find_object("/d/Krynn/common/void");
    f = &tmp1->manip_relocate_to(,tmp2);

    deposit = filter(deposit,f);
		   
    if (sizeof(deposit) <= 0)
      return 0;

    for(i=0;i<sizeof(deposit);i++)
      value += deposit[i]->query_value();

    chskill = TP->query_skill(SS_CHARITY);
    chskill = chskill + (value/3); /*We need some really elaborate formula here!!!!! */
    TP->set_skill(SS_CHARITY, chskill);
    write("You deposit " + COMPOSITE_DEAD(deposit) + " in the coffer " +
	  "of the Knights of Solamnia.\n");
    say(QCTNAME(TP) + " makes a transaction at the coffer of the " +
	"Knights of Solamnia.\n");
    deposit->remove_object();
    return 1;
}
