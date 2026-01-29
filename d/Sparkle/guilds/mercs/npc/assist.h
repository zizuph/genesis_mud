#include <filter_funs.h>

public void 
get_assistance(object ob)
{
    object *livings = FILTER_LIVE(all_inventory(environment(this_object())));
    int i;

    for (i=0;i<sizeof(livings);i++)
	if (livings[i]->id("_mercenary_guild_guard_"))
	    livings[i]->assist_other(this_object()->query_attack());
}

int query_not_attack_me(object who, int aid)
{
    get_assistance(this_object());

    ::query_not_attack_me(who, aid);
}
