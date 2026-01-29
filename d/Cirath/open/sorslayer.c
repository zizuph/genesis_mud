inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
        set_name(({"axe", "sorslayer"}));
        set_short("broad ancient axe");
        set_long("The axe-head got two different blades, one blade that "
		+"points to the right and the other pointing to the left. "
		+"The right blade have a serrated edge, which makes it tear "
		+"out flesh from the victim if you hit a non protected area. "
		+"The other blade is a narrow and extremely sharp. With the "
		+"weight of the serrated blade the narrow blade will cut very "
		+"deep into the enemy which it hits. The handle is made of "
		+"polished wood, giving the axe a incredible balance. The "
		+"serrated blade is covered with runes. This is a mighty "
		+"weapon that probably been heritaged in generations, it "
		+"looks ancient but still very powerful.\n");

	add_item("runes", "You can't understand all the runes, most of them "
		+"is worn down. But you can make out the words 'Behold', "
		+"'Name' and the word 'Sorslayer' engraved on the blade.\n");

        set_adj  ("broad");
        add_adj  ("ancient");

        set_hit(42);
        set_pen(38);

        set_wt(W_AXE);
        set_dt(W_SLASH | W_BLUDGEON);
        set_hands(W_BOTH);

	add_prop(OBJ_M_NO_BUY, "No I don't want to sell this weapon. I'll "
			+"keep it to my self.");
        add_prop(OBJ_I_WEIGHT,10000);
        add_prop(OBJ_I_VOLUME,1800);
	add_prop(OBJ_I_VALUE, 2000);
	add_prop(OBJ_S_WIZINFO, "Got a special attack based on the wielders "
		+"strength. Owned by Ulf (/d/Cirath/tyr/npc/jailtemp.c)");

	set_wf(TO);
}

public int
wield(object wep)
{
	object  tp = this_player();

    	// sanity checks.
    	if ((wep != this_object()) || (tp != environment(this_object())))
        return -1;
        
	TP->catch_msg("You are successful in wielding the ancient axe.\n");
	return 0;
}

public int
unwield(object wep)
{		
	object  tp = this_player();

    	// sanity checks.
    	if ((wep != this_object()) || (tp != environment(this_object())))
        return -1;	
	
	TP->catch_msg("With a sigh you unwield the ancient axe.\n");
	return 0;
}

int
did_hit(int aid, string hdesc, int phurt, 
	object enemy, int dt, int phit, int dam)
{
	object me = ENV(TO);
	mixed* hitresult;
	string how;

	::did_hit();

	if(random(4)) return 0;

	hitresult=enemy->hit_me(TP->query_base_stat(SS_STR)+
		random(TP->query_base_stat(SS_STR)), W_SLASH, me, -1);

	how = "but misses completely";
	if (hitresult[0] > 1) how = "and draws some blood";
	if (hitresult[0] > 5) how = "and makes some blood appear";
	if (hitresult[0] > 10) how = "and makes some blood run down "
		+HIS_HER(enemy)+" neck";
	if (hitresult[0] > 30) how = "and makes some blood fly through the air";
	if (hitresult[0] > 50) how = "and almost manage to do it ";

	if(enemy->query_hp()<= 0) 
	{
		me->catch_msg("You totaly massacre "+QTNAME(enemy)
			+"'s body with the ancient axe in an attempt to chop "
			+HIS_HER(enemy)+" head off.\n");
		me->tell_watcher(QCTNAME(me)+" totaly massacre "+QTNAME(enemy)
			+"'s body in an attempt to chop "+HIS_HER(enemy)+" "
			+"head off.\n");
		enemy->do_die(me);
		return 1;
	}

	me->catch_msg("You try to chop "+QTNAME(enemy)+"'s head off "
			+how+".\n");
	me->tell_watcher(QCTNAME(me)+" tries to chop "+QTNAME(enemy)+
			"'s head off "+how+".\n");
	enemy->catch_msg(QCTNAME(me)+" tries to chop your head off "
			+how+".\n");

	return 1;
}
