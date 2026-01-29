/* Code for promoting soldiers */
#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

int
promote_soldier(string str)
{
    object ob, *obj;
    int promotion_level, num_total, num, num_allowed, new_stat;
    string highlord, divis, name;

    setuid();
    seteuid(getuid());
    if(!str || !sizeof(obj = PARSE_THIS(str, "[the] %l")))
    {
	NF(C(query_verb())+" who?\n");
	return 0;
    }
    if(sizeof(obj) > 1)
    {
	NF("Be more specific! You can "+query_verb()+" only one at a time.\n");
	return 0;
    }
    ob = obj[0];

    if(!IS_MEMBER(ob))
    {
	NF(QCTNAME(ob)+" is not a part of the dragonarmy.\n");
	return 0;
    }
    divis = TP->query_dragonarmy_division();
    if(ob->query_dragonarmy_division() != divis)
    {
	NF(QCTNAME(ob)+" is not from the "+C(divis)+" dragonarmy.\n");
	return 0;
    }
    promotion_level = ob->query_dragonarmy_promotions() + 1;
    if(promotion_level > 3)
    {
	NF(QCTNAME(ob)+" already has maximum promotions.\n");
	return 0;
    }

    /*Only HOs++ can promote - Louie*/
    if((promotion_level >= TP->query_dragonarmy_promotions() ||
        TP->query_dragonarmy_promotions() < 3) &&
       (TP->query_real_name() != "clerk" && !interactive(TP)) &&
       (TP->query_real_name() != "bakaris" && !interactive(TP)))
    {
	NF("You are not of a high enough authority to be able to "+
	    query_verb()+" "+QTNAME(ob)+".\n");
	return 0;
    }

    if(promotion_level > ob->query_max_promotions())
    {
	NF(QCTNAME(ob)+ " is not ready for a promotion yet.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());
    if(!MANAGER->query_promoted(ob) && TP->query_dragonarmy_promotions() < 3)
    {
	name = MANAGER->query_promoter(ob);
	if((name != MANAGER->get_name(TP)) &&
	   (MANAGER->query_promotions(name) >= TP->query_dragonarmy_promotions()))
	{
	    NF(ob->query_The_name(TP)+" was demoted by "+C(name)+
		" and you are not of high enough authority to reverse it.\n");
	    return 0;
	}
    }

    /*Only General and HOs are limited by number now - Louie*/
    num_total = MANAGER->query_member_count(4, divis);
    num = num_total - MANAGER->query_member_count(promotion_level-1, divis);
    if(num > 1)
    {
	switch(promotion_level)
	{
	case 3:
	    //num_allowed = num_total / 8; break;
        num_allowed = 7;
        break;
	case 2:
	    //num_allowed = num_total / 4; break;
        num_allowed = 10000;
        break;
	default:
	    num_allowed = num_total;
	}
	if(num+1 > MAX(1, num_allowed))
	{
	    NF("There is enough of "+PROMOTION_LEVELS[promotion_level]+
		"s for this army. No promotion is allowed in this level now.\n");
	    return 0;
	}
    }

    if(!ob->set_promotion_level(promotion_level, TP))
    {
	return 0;
    }
    ob->set_skill(SS_DRAGONARMY_PROMOTION, ob->stat_to_exp(ob->query_stat(SS_OCCUP)));

    switch(divis)
    {
    case RED_ARMY:
	highlord = "Dragon Highlord Ariakas, Emperor of Krynn";
	break;
    case BLUE_ARMY:
	highlord = "the Dark Lady, Dragon Highlord Kitiara";
	break;
    default:
	highlord = "the Queen of Darkness, Takhisis";
    }
    TP->catch_tell("Solemnly you declare to " +ob->query_the_name(TP));
    ob->catch_tell(TP->query_The_name(ob)+ " solemnly declares to you");
    tell_room(E(TP), QCTNAME(TP)+ " solemnly declares to " +QTNAME(ob), ({ob, TP}) );
    tell_room(E(TP), ": By the authority given to me by " + highlord +
	", I promote you to the " + ob->query_guild_title_occ() + "!\n");
    return 1;
}
