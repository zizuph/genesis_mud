/*
* Created by: Luther
* Date: August 2001 
*
* File: /d/Cirath/tyr/wep/sun_swrd.c
* Comments: Zarth's sword of choice...
*/
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/wa_types.h"
#include "defs.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <language.h>
#include "/sys/stdproperties.h"

#define IS_LIGHT "is_light"

void create_weapon()
{
        set_name(({"sword", "longsword", "sunblade"}));
        set_short("ancient sun-scarred longsword");
        set_long("This sword seems to be weathered by the extreme sunshine in "
        	+"the land of Tyr. The blade is still very sharp and its "
        	+"balance is supreme. The hilt is made of a light, but hard "
        	+"stone, etched with ancient symbols of power.\n");

	add_item("symbols", "The symbols look ancient and worn down. "
		+"You try to dicipher them without any luck.\n");

        set_adj  ("ancient");
        add_adj  ("sun");
	add_adj  ("scarred");
        set_hit(45);
        set_pen(45);
	set_wt(W_SWORD);
        set_dt(W_SLASH | W_IMPALE);
        set_hands(W_LEFT);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
        add_prop(MAGIC_AM_MAGIC, ({ 50, "psionic" }));
	add_prop(OBJ_M_NO_BUY, "No I don't want to sell this weapon. I'll "
			+"keep it to myself.");
	set_likely_corr(0);
	set_likely_dull(-25);
    	add_prop(OBJ_I_WEIGHT,4000);
        add_prop(OBJ_I_VOLUME,1200);
	add_prop(OBJ_I_VALUE, 4000);
	add_prop(MAGIC_AM_ID_INFO, ({"You detect that some psionics have been "+
      		"employed on this weapon. ", 10,"Psionics have strengthened "+
      		"material out of which this weapon was constructed, ensuring "+
      		"that it will not dull or break as fast as normal weapons. ",25,"A "+
      		"more powerfull use of "+
      		"psionics also serves to help protect the wielder from the "+
      		"damaging effects of the cold elements he or she may come "+
      		"into contact with.\n",50}));
	
	add_prop(OBJ_S_WIZINFO, "Has a special attack based on the wielders " +
		"intelligence. Provides a MAGIC_I_RES_COLD of 30. " +
		"MAGIC_I_RES_FIRE reduces special damage. And Wizards " +
		"get special info when special goes off.\n");
	set_wf(TO);
	
}

int
did_hit(int aid, string hdesc, int phurt, 
	object enemy, int dt, int phit, int dam)
{
	object me = ENV(TO);
	int att, pen, res;
	mixed* hitresult;
	string how;

	::did_hit();

	if(random(4)) return 0;

	att = me->query_base_stat(SS_INT) + random(me->query_base_stat(SS_INT));
	res = enemy->query_magic_res(MAGIC_I_RES_FIRE);	
 	pen = att * (100 - res) /100;
	hitresult = enemy->hit_me(pen, MAGIC_DT, me, -1);

	
	/* hitresult=enemy->hit_me(TP->query_base_stat(SS_INT)+
		random(TP->query_base_stat(SS_INT)), W_SLASH, me, -1);
	*/
	how = "just singes";
	if (hitresult[0] > 1) how = "singes";
	if (hitresult[0] > 4) how = "slightly burns";
	if (hitresult[0] > 8) how = "burns";
	if (hitresult[0] > 12) how = "burns flesh on";
	if (hitresult[0] > 18) how = "leaves intense burns on";

	if(enemy->query_hp()<= 0) 
	{
		me->catch_msg("Making contact with " + QTNAME(enemy) + ", your " + short() + 
			" ignites " + HIM_HER(enemy) + ".\n");
		me->tell_watcher(QCTNAME(me)+ " ignites " + QTNAME(enemy)+
			" with his " + short() + ".\n", me, enemy);
		enemy->catch_msg("The " + short() + " ignites you!\n");
		enemy->do_die(me);
		return 1;
	}

	me->catch_msg("Making contact with " + QTNAME(enemy) + ", your " + short() + 
		 " " + how + " " + HIS_HER(enemy)+ " " + hdesc + ".\n");
	enemy->catch_msg("The " + short() + " " + how + " your " + hdesc + ".\n");
			
	me->tell_watcher(QCTNAME(me)+ " hits " + QTNAME(enemy)+
			" with " + HIS_HER(me)+ " " + short() + ".\n", me, enemy);
	
	if (me->query_wiz_level())
	{
		me->catch_msg("Att: " + att + ". Res: " + res + 
 			" Pen: " + pen + ".\n");
 	}		
	return 1;
}

mixed
query_magic_protection(string prop, object what)
{
    if (what == query_wielded())
    {
        switch (prop)
        {
            case MAGIC_I_RES_COLD:    return ({ 30, 1 });
        }
    }
    return ::query_magic_protection(prop, what);
}

public mixed
wield(object ob)
{
    object  tp = this_player();

    // sanity checks.
    if ((ob != this_object()) || (tp != environment(this_object())))
        return -1;

    tp->add_magic_effect(this_object());
    TP->catch_msg("As you wield the " + short() + ", you start to feel warmer.\n");
    say(QCTNAME(this_player()) + " wields the " + short() + ".\n");
    return 1;
}

public mixed
unwield(object ob)
{
    object  tp = this_player();

    // sanity checks.
    if ((ob != this_object()) || (tp != query_wielded()))
        return -1;

    if (!living(tp)) 
        return 0;

    TP->remove_magic_effect(this_object());
    TP->catch_msg("Upon releasing the " + short() + " you start to feel cold.\n");
    say(QCTNAME(this_player()) + " unwields the " + short() + ".\n");
    if (query_prop(OBJ_I_LIGHT))
    {
    	remove_prop(OBJ_I_LIGHT);    	
    }	
    return 1;
}

void remove_broken()
{
  ::remove_broken();
}

void
init()
{
    ::init();
    add_action("rub_symbol", "rub");
}

void
remove_light()
{
	object room;
	if (query_prop(OBJ_I_LIGHT))
	{
	TO->remove_prop(OBJ_I_LIGHT);
	TP->catch_msg("The " + short() + " stops eminating light.\n");
       	say(QCTNAME(this_player()) + "'s " + short() + " stops eminating light.\n");
        room = TO;
    	while(objectp(ENV(room)))
        room = ENV(room);
    	room->update_light(1);        
        }	
}

void
remove_light_prop()
{
	if (query_prop(IS_LIGHT))
	{
	TO->remove_prop(IS_LIGHT);
	}
}		

int
rub_symbol(string str)
{	
	object room;	      
   	notify_fail("Rub what?\n");
    	
       	if (str == "symbols") 
     	{
     		if (!::query_wielded())
         	{
         	TP->catch_msg("Nothing happens when you rub the symbols.\n");
		return 1;
		}
     		if (!TO->query_prop(IS_LIGHT))
     		{
     		TO->add_prop(OBJ_I_LIGHT, 3);
     		TP->catch_msg("A brilliant bright light eminates from the " + short() + " " + 
        	"when you rub the symbols.\n");
        	say(QCTNAME(this_player()) + "'s " + short() + " starts to eminate a " + 
        	"brilliant bright light.\n");
        	TO->add_prop(IS_LIGHT, 1);
        	set_alarm(itof(TP->query_base_stat(SS_INT)), 0.0, &remove_light());
        	set_alarm(itof(TP->query_base_stat(SS_INT) * 5), 0.0, &remove_light_prop());
		room = TO;
    		while(objectp(ENV(room)))
        	room = ENV(room);
    		room->update_light(1);
		return 1;
		}
		else
		{
		TP->catch_msg("Nothing happens when you rub the symbols.\n");
		return 1;
		}
	}
	return 0;
}

