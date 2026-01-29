/*
 * /d/Kalad/common/sewers/arm/orange_scalemail.c
 * Purpose    : Worn by the lizard king in the lizard caves.
 * Located    : lizardcaves
 * Created By : Sir Toby, 97-09-12
 * Modified By: 
 * First Modif: 
 */

#pragma strict_types

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>

#define ARMOUR_CLASS (45 + random(3))

void
create_armour()
{
::create_armour();


    set_name("scalemail");
    set_pname("scalemails");

    set_short("orange scalemail");
    set_pshort("orange scalmails");
    set_long("This is a orange scalemail, made out of dried lizardskin. " +
	     "The scales overlap each other and behind them you notice " +
	     "a thin layer of soft leather for the wearers comfort. " +
	     "You also notice that the scales are slightly bent at the " +
	     "end, forming thorns that would hurt if stricken bare handed. " +
	     "The lizardskin is thin thus making this fine piece of " +
	     "armour very light. \n");

    set_adj("orange");
    add_adj("scale");

    set_ac(ARMOUR_CLASS);

//          impale, slash, bludgeon 
    set_am(({   0,     3,     -1 }));

    set_at(A_BODY);   
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS - 5) + random(10) );
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 5400 + random(200) );

    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(OBJ_S_WIZINFO,"This armour is very sharp to hit hurting " +
			   "the opponent and it has high AC.\n" +
			   "As it is orange it will reduce sneak and " +
			   "hide by 15.\n");

return;
}


varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    ::got_hit(hid, ph, att, dt, dam);

    if(!(sizeof(att->query_weapon(-1))))
	if(!(att->query_armour(A_HANDS)))
	{
		tell_object(query_worn(),"You smile confidently when your " +
					 "opponent strikes your scalemail, " +
					 "knowing that the scales must hurt " +
					 "the bare flesh.\n");
		tell_object(att,"As you hit the scalemale you feel " +
				"intense pain when the scales dig into " +
				"your flesh.\n");

		
		if(att->query_base_stat(SS_STR) > 135)
		{
		dam = dam/10+random(10);

 			if(att->query_base_stat(SS_STR) > 160)
			dam = dam/10+random(10)+random(10);
		}
		else
		dam = dam/10;

		att->heal_hp(-dam);
		if(att->query_hp() <= 0)
		{
			att->do_die();
		}
	}
}


int
wear(object obj)
{
    TP->set_skill_extra(SS_HIDE,TP->query_skill_extra(SS_HIDE)-15);
    TP->set_skill_extra(SS_SNEAK,TP->query_skill_extra(SS_SNEAK)-15);

    write("You wear the " +short()+ " proudly knowing that, " +
	  "wearing this, you will be the centre of attention.\n");
    say(QCTNAME(TP) + " wears " +HIS(TP)+ " " +short()+ 
	" proudly.\n");

return 1;
}

int
remove(object obj)
{
    TP->set_skill_extra(SS_HIDE,TP->query_skill_extra(SS_HIDE)+15);
    TP->set_skill_extra(SS_SNEAK,TP->query_skill_extra(SS_SNEAK)+15);

    write("You slowly remove the " +short()+ ". You are no longer " +
	  "the centre of attention.\n");
    say(QCTNAME(TP) + " slowly removes " +HIS(TP)+ " " +short()+
	" with sadness in " +HIS(TP)+ " eyes.\n");

return 1;
}


 
