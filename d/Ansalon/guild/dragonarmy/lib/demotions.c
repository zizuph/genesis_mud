/* Code for demoting soldiers */
#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <macros.h>
#include <mail.h>
#include <ss_types.h>

int
demote_soldier(string str)
{
    int demotion_level;
    string divis, name;
    object ob;

    if(!str)
    {
	NF("Syntax is demote <person>.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());
    str = MANAGER->get_name(str);

    if(!MANAGER->query_member(str))
    {
	NF(C(str)+" is not a part of the dragonarmy.\n");
	return 0;
    }

    if(MANAGER->query_division(str) != TP->query_dragonarmy_division())
    {
	NF(C(str)+" is from a different division of the dragonarmy.\n");
	return 0;
    }

    /*Only HO++ can demote*/
    demotion_level = MANAGER->query_promotions(str);
    if(demotion_level >= TP->query_dragonarmy_promotions() ||
        TP->query_dragonarmy_promotions() < 3)
    {
	NF("You are not of a high enough authority to be " +
	  "able to demote "+C(str)+".\n");
	return 0;
    }

    if(demotion_level == 0)
    {
	NF(C(str)+" is as low a rank as one can get, so cannot be demoted.\n");
	return 0;
    }

    if(MANAGER->query_promoted(str) && TP->query_dragonarmy_promotions() < 3)
    {
	name = MANAGER->query_promoter(str);
	if((name != MANAGER->get_name(TP)) &&
	   (MANAGER->query_promotions(name) >= TP->query_dragonarmy_promotions()))
	{
	    NF(C(str)+" was promoted by "+C(name)+
		" and you are not of high enough authority to reverse it.\n");
	    return 0;
	}
    }

    ob = find_player(str);
    if(!ob)
    {
	if(!MANAGER->set_promotions(str, demotion_level - 1, TP))
	{
	    NF("Some strange error prevented you from demoting "+C(str)+
		".\nPlease report this to your Guild Master.\n");
	    return 0;
	}
    }
    else
    {
	if(!ob->set_promotion_level(demotion_level - 1, TP))
	{
	    NF("Some strange error prevented you from demoting "+C(str)+
		".\nPlease report this to your Guild Master.\n");
	    return 0;
	}
    }
    CREATE_MAIL("DEMOTION", "dragonarmy", str, "", ctime(time())+"\n"+
	"You have been demoted by "+C(TP->query_name())+".\nDragonarmy Informer" );
    TP->catch_tell("You demote " +C(str)+ "!\n");
    ob->set_skill(SS_DRAGONARMY_PROMOTION, ob->stat_to_exp(ob->query_stat(SS_OCCUP)));
    return 1;
}
