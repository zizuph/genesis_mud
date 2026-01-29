#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <std.h>

private int order_members(object a, object b);

private int
filter_dragonarmy(object who)
{
    string coven;

    if (!IS_MEMBER(who))
	return 0;

    if (who == TP)
	return 1;

    /* Wizards see everyone */
    if (TP->query_wiz_level())
	return 1;

#ifndef DA_TESTING
    /* Wizards are not shown to mortals */
    if (who->query_wiz_level())
	return 0;

    /* Wizards jr are not shown to mortals */
    if (extract(who->query_real_name(), -2) == "jr")
	return 0;
#endif DA_TESTING

    if (who->query_dragonarmy_division() != TP->query_dragonarmy_division())
	return 0;

    return 1;
}

mixed
make_list(object *members)
{
    string name, title, str1, str2, list = "";
    int i, size, cnt = 0;

    size = sizeof(members);
    i = -1;
    while (++i < size)
    {    
	str1 = SECURITY->query_wiz_pretitle(members[i]);
	str2 = "";

	if (strlen(name = members[i]->query_name()))
	{
	    str1 += (strlen(str1) ? " " + name : name);
	}
	else
	{
	    continue;
	}

	if (strlen(title = members[i]->query_title()))
	{
	    str1 += (strlen(str1) ? " " + title : capitalize(title));
	}

	if (TP->query_wiz_level())
	{
	    str2 = "(" + (members[i]->query_wiz_level() ? "wiz" :
	      members[i]->query_average_stat()) + ")";
	}

	cnt++;
	list += sprintf("- %=-68s %-5s\n", str1, str2);
    }
    
    return ({ list, cnt });
}

int
list(string str)
{
    mixed tmp;
    string list;
    int cnt;
    object *members;

    if(str != "dragonarmy members")
    {
	NF(C(query_verb())+" what?\n");
	return 0;
    }

    if (MANAGER->query_punishment(TP->query_real_name(), PUN_NOWHO)) {
        NF("You are prevented from accessing this due to punishment.\n");
        return 0;
    }

    members = sort_array(filter(users(), filter_dragonarmy), order_members);

    tmp = make_list(members);
    list = tmp[0];
    cnt = tmp[1];

    list += "======================================================="+
    "======================\n";
    list += "Total number of active soldiers is " + cnt + ".\n";

#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    /* If there is a room where statues of linkdead people can be found,
     * we add that to the list.
     */
    members = filter((all_inventory(find_object(OWN_STATUE)) - members), 
	&not() @ &->query_npc());
    members = sort_array(filter(members, filter_dragonarmy), order_members);
    tmp = make_list(members);
    if (cnt = tmp[1])
    {
	list += "Currently sleeping in camp " + (cnt > 1 ? "are:\n" : "is:\n");
	list += tmp[0];
    }
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD



    if (query_verb()[0..0] == "m")
    {
	setuid();
	seteuid(getuid());
	TP->more(list);
    }
    else
    {
	write(list);
    }

    return 1;
}

private int
order_members(object a, object b)
{
    int ai, bi;

    ai = a->query_dragonarmy_promotions();
    bi = b->query_dragonarmy_promotions();
    if (ai < bi)
	return 1;
    if (ai > bi)
	return -1;

    ai = a->query_dragonarmy_rank_stat();
    bi = b->query_dragonarmy_rank_stat();
    return ((ai < bi) ? 1 : (ai == bi ? 0 : -1));  
}
