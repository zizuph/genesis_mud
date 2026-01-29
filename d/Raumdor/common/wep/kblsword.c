inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/*
 * Purpose    : A black steel longsword.
 * Created By : Sarr 17.Jun.96
 * Modified By: 
 * 
 * Cotillion - 2006-04-20
 * - Fixed call of ::did_hit 
 */

void
  create_weapon()
{
    ::create_weapon();
    set_name("longsword");
    add_name("sword");
    set_adj("black");
    add_adj("steel");
    set_short("black steel longsword");
    set_long("This is a sword made of blackened steel. The blade is long, "+
	     "sleek, and double sided. No light reflects off its razor sharp edge. "+
	     "The hilt is adorned with silver trimming, and in the center is a "+
	     "carving of a skull. Set into the bottom of the hilt is a small ruby. "+
	     "You see runes along the blade.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_hit(37+random(3));
    set_pen(37+random(3));
    add_prop(OBJ_I_WEIGHT,7200);
    add_prop(OBJ_I_VOLUME,4500);
    add_prop(OBJ_I_VALUE,1300);
    add_item(({"runes"}),"@@runes");
    add_item(({"skull"}),"A rather grim looking skull, with two tiny "+
	     "red rubies for eyes.\n");
    add_item(({"ruby"}),"It sparkles in the light.\n");
}

string
  runes()
{
    if(TP->query_skill(109) > 30)
	return "You make out the words: Khiraa.\n";
    return "You can't understand them.\n";
}


static void
  tell_watcher(string str, object enemy)
{
    object mee,*ob;
    int i;
    mee = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(mee))) - ({ mee });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (!ob[i]->query_option(OPT_BLOOD))
	    ob[i]->catch_msg(str);
}

public int
  did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	  int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;
    int i_see_combat = 1;
    object me = query_wielded();

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return 1;
    }
 
    if (phurt == -1 || phurt == -2)
    {
        TP->add_panic(1); 
        if (i_see_combat)
        {
            me->catch_msg("You cut a massive swath in the air near "+
			  QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" cuts a massive swath in the "+
			     "air near your "+hdesc+" with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" cuts a massive swath in the air near "+
		     QTNAME(enemy)+"'s "+hdesc+" with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }
    enemy->add_panic(-3 - (phurt / 5));
    if(phurt > -1 && phurt < 5)
    {
        if (i_see_combat)
        {
            me->catch_msg("You strike a glancing blow on "+QTNAME(enemy)+
			  "'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" strikes a glancing blow on "+
			     "your "+hdesc+" with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" strikes a glancing blow on "+QTNAME(enemy)+
		     "'s "+hdesc+" with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }

    if(phurt > 4 && phurt < 10)
    {
        if (i_see_combat)
        {
            me->catch_msg("You slash your "+short()+" across "+
			  QTNAME(enemy)+"'s "+hdesc+", inflicting much pain.\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" slashes "+HIS(me)+" "+short()+
			     " across your "+hdesc+", inflicting much pain.\n");
        }
        tell_watcher(QCTNAME(me)+" slashes "+HIS(me)+" "+short()+
		     " across "+QTNAME(enemy)+"'s "+hdesc+", inflicting much pain.\n",enemy);
        return 1;
    }
    
    if(phurt > 9 && phurt < 20)
    {
        if (i_see_combat)
        {
            me->catch_msg("You lunge forward and stab "+QTNAME(enemy)+"'s "+
			  hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" lunges forward and stabs your "+
			     hdesc+" with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" lunges forward and stabs "+
		     QTNAME(enemy)+"'s "+hdesc+" with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }

    if(phurt > 19 && phurt < 30)
    {
        if (i_see_combat)
        {
            me->catch_msg("You feign to the right, then stab deeply "+
			  "into "+QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" feigns to the right, then "+
			     "stabs deeply into your "+hdesc+" with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" feigns to the right, then stabs deeply "+
		     "into "+QTNAME(enemy)+"'s "+hdesc+" with "+HIS(me)+" "+short()+
		     ".\n",enemy);
        return 1;

    }


    if(phurt > 29 && phurt < 50)
    {
        if (i_see_combat)
        {
            me->catch_msg("You tear across "+QTNAME(enemy)+"'s "+hdesc+
			  " with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" tears across your "+hdesc+
			     "with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" tears across "+QTNAME(enemy)+"'s "+hdesc+
		     " with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }

    if(phurt > 49 && phurt < 70)
    {
        if (i_see_combat)
        {
            me->catch_msg("You shred apart "+QTNAME(enemy)+"'s "+hdesc+
			  " with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" shreds apart your "+hdesc+
			     " with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" shreds apart "+QTNAME(enemy)+"'s "+
		     hdesc+" with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }
    if(phurt > 69 && phurt < 90)
    {
        if (i_see_combat)
        {
            me->catch_msg("You rip large chunks of flesh off "+
			  QTNAME(enemy)+"'s "+hdesc+" with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" rips large chunks of flesh "+
			     "off your "+hdesc+" with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" rips large chunks of flesh off "+
		     QTNAME(enemy)+"'s "+hdesc+" with "+HIS(me)+" "+short()+
		     ".\n",enemy);
        return 1;
    }
    if(phurt > 90)
    {
        if (i_see_combat)
        {
            me->catch_msg("You slash "+QTNAME(enemy)+"'s "+hdesc+
			  " cleanly in half with your "+short()+".\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(QCTNAME(me)+" slashes your "+hdesc+
			     " cleanly in half with "+HIS(me)+" "+short()+".\n");
        }
        tell_watcher(QCTNAME(me)+" slashes "+QTNAME(enemy)+"'s "+hdesc+
		     " cleanly in half with "+HIS(me)+" "+short()+".\n",enemy);
        return 1;
    }

}

