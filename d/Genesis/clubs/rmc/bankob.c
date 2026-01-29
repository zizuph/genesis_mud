#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

#define BANKOB_WANNA_DEST "_bankob_wanna_dest"

int
bank_account(string s)
{
    mapping acc = ACCOUNTS->query_account(s);
    int tot;
    object account_list = find_object(ACCOUNTS);
  
    if (m_sizeof(acc) < 6)
        return 0;
    return (acc["pc"] + acc["gc"]/12 + acc["sc"]/144 + acc["cc"]/1728);
}

int
bankcheck(string s)
{
    int coins;

    coins = bank_account(s);

    NF("No such account!\n");
    if (!coins)
	return 0;

    write("[BANKER] " + capitalize(s) + " has ");
    write(coins);
    write(" platinum coins in the bank.\n");

    return 1;
}

int
bankpurge(string s)
{
    int v, coins;
    
    coins = bank_account(s);

    NF("No such account!\n");
    if (!coins)
	return 0;

    if (!(s == TP->query_prop(BANKOB_WANNA_DEST)))
    {
	write("[BANKER] Really wanna dest "+CAP(s)+"'s bankaccount?\n");
	TP->add_prop(BANKOB_WANNA_DEST, s);
	return 1;
    }
    
    v = ACCOUNTS->remove_account(s);

    NF("[BANKER] Command not successful.\n");
    if (!v)
	return 0;

    write("[BANKER] "+capitalize(s)+"'s account is removed.\n");

    TP->remove_prop(BANKOB_WANNA_DEST);
    
    return 1;
}
    
void
create_object()
{
    set_long("A small bank tool. It has the following commands:\n"+
	     "  - bankcheck <player> : check the account of <player>.\n"+
	     "  - bankpurge <player> : purge the account of <player>.\n"+
	     "                         NOTE: This WILL be LOGGED!!\n");

    set_name("tool");
    set_adj("bank");
    add_adj("small");
}

void
init()
{
    ::init();

    add_action("bankcheck", "bankcheck");
    add_action("bankpurge", "bankpurge");
}

