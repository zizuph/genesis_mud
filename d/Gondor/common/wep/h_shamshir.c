/*
 *Shamshir(curved sword, like a scimitar) wielded by haradrim.
 *Special hit clones a bleeding object in the enemy
 *Altrus, July 2005
*/ 

inherit "/std/weapon";
inherit "/lib/keep.c";
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

#define IS_BLD "_bleeding_shamshir_wound"

void
create_weapon()
{
    set_name("shamshir");
    add_name("sword");
    set_short("red-tinted barbed shamshir");
    set_pshort("red-tinted barbed shamshirs");
    set_adj(({"red-tinted", "barbed"}));
    set_long("The steel blade of this wicked looking sword is tinted a dark red; it looks almost as if it is drenched in blood. Like most swords preferred by the men of Harad, it was forged in a broad, curving arc. Unusual to most swords, this one has a barbed hook set in the blade opposite the cutting edge. .\n");
    add_prop(OBJ_I_WEIGHT, 4500 + random(1000));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
     add_prop(MAGIC_AM_ID_INFO,({"A skilled wielder is required to use this weapon properly.\n",1,
    "It is designed to inflict bleeding wounds.\n",25,
    "If wielded by a person of skill, it can inflict wounds upon its target... However, if wielded by one who is unskilled, it can inflict wounds upon the wielder.\n",65 }));
    set_default_weapon((35 + random(11)), (40 + random(7)), W_SWORD, W_SLASH, W_ANYH, 0);
    query_keepable();
    set_wf(this_object());
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    int skill, stat, skill_e, stat_e;
    object me, bld_obj;
    string me_text, target_text, watch_text;

    me = query_wielded();
    skill = me->query_skill(SS_WEP_SWORD);
    stat = me->query_stat(SS_DEX);
    skill_e = enemy->query_skill(SS_PARRY);
    stat_e = enemy->query_stat(SS_DEX);
   	
    //Cap the stat so there is no unreasonable chance to hit or chance to miss with a large stat diff
    if (stat > 90)
        stat = 70 + random(20);
    if (stat_e > 90)
        stat_e = 70 + random(20);

    if ((random(100) < (skill)) && (random(skill+stat) > random(skill_e+stat_e)))
    {
	if(!enemy->query_prop(IS_BLD))
	{
		if(random(4))
		{
		    bld_obj = clone_object("/d/Gondor/common/wep/long_bleed_obj");
		    bld_obj->move_object(enemy);
		    enemy->add_prop(IS_BLD, 1);
		    enemy->heal_hp(-(50+random(250)));
		    me->catch_msg("You make a bold move on " + QTNAME(enemy) + ", carving a deep wound with your " + short() + "!\n");
		    enemy->catch_msg(QCTNAME(me) + " makes a bold move on you, carving a deep wound with " + HIS_HER(me) + " " + short() + "!\n");
		    me->tell_watcher(QCTNAME(me) + " makes a bold move on " + QTNAME(enemy) + ", carving a deep wound with " + HIS_HER(me) + " " + short() + "!\n");
		}
		
		else
		{
		    bld_obj = clone_object("/d/Gondor/common/wep/short_bleed_obj");
		    bld_obj->move_object(enemy);
		    enemy->add_prop(IS_BLD, 1);
		    enemy->heal_hp(-(50+random(150)));
		   me->catch_msg("You make a bold move on " + QTNAME(enemy) + ", carving a shallow wound with your " + short() + "!\n");
		    enemy->catch_msg(QCTNAME(me) + " makes a bold move on you, carving a shallow wound with " + HIS_HER(me) + " " + short() + "!\n");
		    me->tell_watcher(QCTNAME(me) + " makes a bold move on " + QTNAME(enemy) + ", carving a shallow wound with " + HIS_HER(me) + " " + short() + "!\n");
		}
		
		return 1;
	}
    }
  
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}