//    Fixed some grammatical and spelling errors.
//    - Jaypeg Dec98

#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <options.h>

#define HIM_HER(o)  o->query_objective()
#define HE_SHE(o)   o->query_pronoun()
#define HIS_HER(o)  o->query_possessive()

varargs void
tell_watcher(string str, object enemy, mixed arr)
{
    object *ob;
    object me = query_wielded();
    int i, size;

    ob = all_inventory(environment(me)) - ({ me, enemy });

    if (arr)
    {
	if (pointerp(arr))
	    ob -= arr;
	else

	    ob -= ({ arr });
    }

    /* We only display combat messages to interactive players. */
    ob = FILTER_PLAYERS(ob);

    i = -1;
    size = sizeof(ob);
    while(++i < size) 
    {
	if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
	{
	    if (CAN_SEE(ob[i], me))
		ob[i]->catch_msg(str);
	    else
		tell_object(ob[i], enemy->query_The_name(ob[i]) +
		  " is hit by someone.\n");
	}
    }
}



varargs void
produce_msg(object enemy, string hdesc, int phurt, int dt, string short)
{

    object tp = query_wielded();

    if (!short)
	short = query_short();
    //  Produce the really cool messages if they are dead ;-)
    if (enemy->query_hp() <= 0)
    {
	switch (dt)
	{
	case W_IMPALE:
	    tp->catch_msg("Your "+short+" impales "+QTNAME(enemy)+"'s chest "+ 
	      "and "+HE_SHE(enemy)+" dies with a gurgling sound in "+
	      HIS_HER(enemy)+" throat!\n"); 
	    enemy->catch_msg(QCTNAME(tp)+"'s "+short+" impales your chest and "+ 
	      "you die with gurgling sound in your throat.\n");
	    tell_watcher(QCTNAME(tp)+"'s "+short+" impales "+QTNAME(enemy)+
	      "'s chest and "+QTNAME(enemy)+" dies with a gurgling sound in "+
	      HIS_HER(enemy)+" throat!\n",enemy);
	    break;
	case W_SLASH:
	    tp->catch_msg("You swing your "+short+" towards "+QTNAME(enemy)+
	      "'s "+hdesc+" and hit it with a sickening crunching sound.  "+
	      QCTNAME(enemy)+" falls lifeless to the ground in a puddle of "+
	      "blood!\n");
	    enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      " towards your "+hdesc+" and hits it with a sickening "+
	      "crunching sound.  You hear a sharp snap as you die.\n"); 
	    tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      " towards "+QTNAME(enemy)+"'s "+hdesc+" and hit it with a "+
	      "sickening crunching sound.  "+QCTNAME(enemy)+" falls lifeless "+
	      "to the ground in a puddle of blood!\n",enemy);
	    break;
	case W_BLUDGEON:
	    tp->catch_msg("Your "+short+" brutally crushes "+QTNAME(enemy)+"'s "+
	      hdesc+" with a shattering force. "+QCTNAME(enemy)+" is knocked "+
	      "down on the floor leaving a smashed and barely recognizable "+
	      "corpse!\n"); 
	    enemy->catch_msg(QCTNAME(tp)+"'s "+short+"  brutally crushes your "+
	      hdesc+" with a shattering force.  You see red, black, then "+
	      "nothing.\n");
	    tell_watcher(QCTNAME(tp)+"'s "+short+"  brutally crushes "+
	      QTNAME(enemy)+"'s "+hdesc+" with a shattering force.  "+ 
	      QCTNAME(enemy)+" is knocked down on the floor leaving a "+
	      "smashed and barely recognizable corpse!\n",enemy); 
	    break; 
	}
	//   Kill them 
	enemy->do_die(tp);
	return;
    }

    if (dt == W_IMPALE)
    {
	switch(phurt)
	{
	case -1:
	    tp->catch_msg("You stab the air next to "+QTNAME(enemy)+" with your "+
	      short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" stabs the air next to you with "+
	      HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" stabs the air next to "+QTNAME(enemy)+
	      " with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 0:
	    tp->catch_msg(QCTNAME(enemy)+" giggles as you harmlessly poke "+ 
	      HIS_HER(enemy)+" "+hdesc+" with your "+short+".\n");
	    enemy->catch_msg("You giggle as "+QTNAME(tp)+" harmlessly pokes "+
	      "your "+hdesc+" with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(enemy)+" giggles as "+QTNAME(tp)+" harmlessly "+
	      "pokes "+QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(tp)+
	      " "+short+".\n",enemy);
	    break;
	case 1..5:
	    tp->catch_msg("You puncture "+QTNAME(enemy)+"'s "+hdesc+" with "+ 
	      "your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" punctures your "+hdesc+" with "+
	      HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" punctures "+QTNAME(enemy)+"'s "+hdesc+
	      " with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 6..10:
	    tp->catch_msg("You impale "+QTNAME(enemy)+"'s "+hdesc+" with "+
	      "your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" impales your "+hdesc+" with "+
	      HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" impales "+QTNAME(enemy)+"'s "+hdesc+
	      " with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 11..20:
	    tp->catch_msg("You puncture "+QTNAME(enemy)+"'s "+hdesc+" neatly "+ 
	      "with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" punctures your "+hdesc+" neatly "+
	      "with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" punctures "+QTNAME(enemy)+"'s "+hdesc+
	      " neatly with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 21..40:
	    tp->catch_msg("You give "+QTNAME(enemy)+" a shallow puncture in "+
	      "the "+hdesc+" with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" gives you a shallow puncture in the "+
	      hdesc+" with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" gives "+QTNAME(enemy)+" a shallow "+
	      "puncture in the "+hdesc+" with "+HIS_HER(tp)+" "+short+".\n",
	      enemy);
	    break;
	case 41..60:
	    tp->catch_msg("You give "+QTNAME(enemy)+" a painful puncture wound "+
	      "in the "+hdesc+" with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" gives you a painful puncture wound "+
	      "in the "+hdesc+" with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" gives "+QTNAME(enemy)+" a painful "+
	      "puncture wound in the "+hdesc+" with "+HIS_HER(tp)+" "+
	      short+".\n",enemy);
	    break;
	case 61..80:
	    tp->catch_msg("With a staggering performance, you spin your "+short+
	      " and yield a puncture through "+QTNAME(enemy)+"'s "+hdesc+"!\n"); 
	    enemy->catch_msg("With a staggering performance, "+QTNAME(tp)+
	      " spins "+HIS_HER(tp)+" "+short+" and yields a puncture "+
	      "through your "+hdesc+"!\n");
	    tell_watcher("With a staggering performance, "+QTNAME(tp)+
	      " spins "+HIS_HER(tp)+" "+short+" and yields a puncture "+
	      "through "+QTNAME(enemy)+"'s "+hdesc+"!\n",enemy);
	    break;
	case 81..90:
	    tp->catch_msg("You deal a deep, piercing blow into "+QTNAME(enemy)+
	      "'s "+hdesc+" with your "+short+"!  "+QCTNAME(enemy)+ 
	      " bleeds profusely from the blow!\n"); 
	    enemy->catch_msg(QCTNAME(tp)+" deals a deep, piercing blow into "+
	      "your "+hdesc+" with "+HIS_HER(tp)+" "+short+"!   You bleed "+
	      "profusely from the blow!\n");
	    tell_watcher(QCTNAME(tp)+" deals a deep, piercing blow into "+
	      QTNAME(enemy)+ "'s "+hdesc+" with "+HIS_HER(tp)+" "+short+
	      "!  "+QCTNAME(enemy)+" bleeds profusely from the blow!\n",enemy);
	    break;
	default:
	    tp->catch_msg("You impale "+QTNAME(enemy)+"'s "+hdesc+" deep and "+
	      "gory with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" impales your "+hdesc+" deep and gory "+ 
	      "with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" impales "+QTNAME(enemy)+"'s "+hdesc+ 
	      " deep and gory with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	}
    }
    if (dt == W_SLASH)
    {
	switch(phurt)
	{
	case -1:
	    tp->catch_msg("You swing your "+short+" aimlessly around "+
	      QTNAME(enemy)+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      " aimlessly around you.\n");
	    tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      " aimlessly around "+QTNAME(enemy)+".\n",enemy);
	    break;
	case 0:
	    tp->catch_msg("The air whistles as "+QTNAME(enemy)+" narrowly "+
	      "avoids your "+short+"'s dangerous slash.\n",enemy);
	    enemy->catch_msg("The air whistles as you narrowly avoid "+ 
	      QTNAME(tp)+"'s "+short+"'s dangerous slash.\n");
	    tell_watcher("The air whistles as "+QTNAME(enemy)+" narrowly avoids "+
	      QTNAME(tp)+"'s "+short+"'s dangerous slash.\n",enemy);
	    break;
	case 1..5:
	    tp->catch_msg("Your "+short+" touches "+QTNAME(enemy)+"'s "+ 
	      hdesc+", making a nice flesh wound.\n");     
	    enemy->catch_msg(QCTNAME(tp)+"'s "+short+" touches your "+hdesc+    
	      ", making a nice flesh wound.\n");
	    tell_watcher(QCTNAME(tp)+"'s "+short+" touches "+QTNAME(enemy)+
	      "'s  "+hdesc+", making a nice flesh wound.\n",enemy);
	    break; 
	case 6..10:
	    tp->catch_msg("You cut "+QTNAME(enemy)+"'s "+hdesc+" neatly with "+
	      "your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" cuts your "+hdesc+" neatly with "+
	      HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" cuts "+QTNAME(enemy)+"'s "+hdesc+ 
	      " neatly with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break; 
	case 11..20:
	    tp->catch_msg("You perform a nice swing with your "+short+
	      ", striking "+QTNAME(enemy)+"'s "+hdesc+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" performs a nice swing with "+
	      HIS_HER(tp)+" "+short+" striking your "+hdesc+".\n");
	    tell_watcher(QCTNAME(tp)+" performs a nice swing with "+HIS_HER(tp)+
	      " "+short+" striking "+QTNAME(enemy)+"'s  "+hdesc+".\n",enemy);
	    break; 
	case 21..40:
	    tp->catch_msg("You slash "+QTNAME(enemy)+"'s "+hdesc+" with your "+
	      short+", and blood begins to trickle.\n");     
	    enemy->catch_msg(QCTNAME(tp)+" slashes your "+hdesc+" with "+
	      HIS_HER(tp)+ " "+short+", and blood begins to trickle.\n");
	    tell_watcher(QCTNAME(tp)+" slashes "+QTNAME(enemy)+"'s "+hdesc+ 
	      " with "+HIS_HER(tp)+ " "+short+", and blood begins "+
	      "to trickle.\n",enemy);
	    break;
	case 41..60:
	    tp->catch_msg(QCTNAME(enemy)+" is badly hurt as your "+short+
	      " slashes deeply into "+HIS_HER(enemy)+" "+hdesc+".\n");
	    enemy->catch_msg("You are badly hurt as "+QTNAME(tp)+"'s  "+short+
	      " slashes deeply into your "+hdesc+".\n");
	    tell_watcher(QCTNAME(enemy)+" is badly hurt as "+QTNAME(tp)+
	      "'s "+short+" slashes "+" deeply into "+QTNAME(enemy)+
	      "'s "+hdesc+".\n",enemy);
	    break; 
	case 61..80:
	    tp->catch_msg("You hit "+QTNAME(enemy)+" wickedly in the "+hdesc+
	      " with your "+short+", leaving a gaping, bloody wound.\n");     
	    enemy->catch_msg(QCTNAME(tp)+" hits you wickedly in the "+hdesc+
	      " with "+HIS_HER(tp)+ " "+short+", leaving a gaping, "+
	      "bloody wound.\n");
	    tell_watcher(QCTNAME(tp)+" hits "+QTNAME(enemy)+" wickedly in the "+
	      hdesc+" with "+HIS_HER(tp)+" "+short+ ", leaving a gaping, "+ 
	      "bloody wound.\n",enemy);
	    break; 
	case 81..90:
	    tp->catch_msg("You gut "+QTNAME(enemy)+"'s "+hdesc+" with a mighty "+ 
	      "slash of your "+short+", and "+HIS_HER(enemy)+"'s blood "+ 
	      "begins to trickle.\n");     
	    enemy->catch_msg(QCTNAME(tp)+" guts your "+hdesc+" with a mighty "+
	      "slash of "+HIS_HER(tp)+" "+short+", and your blood begins "+
	      "to trickle.\n"); 
	    tell_watcher(QCTNAME(tp)+" guts "+QTNAME(enemy)+"'s "+hdesc+" with "+
	      "a mighty slash of "+HIS_HER(tp)+" "+short+", and "+
	      QTNAME(enemy)+"'s blood begins to trickle.\n",enemy);
	    break;
	default:
	    tp->catch_msg("With a mighty slash of your "+short+", you hew "+
	      "deeply into "+QTNAME(enemy)+"'s "+hdesc+" leaving "+
	      HIM_HER(enemy)+" momentarily stunned.\n"); 
	    enemy->catch_msg("With a mighty slash of "+QTNAME(tp)+"'s "+short+
	      ", "+HE_SHE(tp)+" hews deeply into your "+hdesc+" leaving "+
	      "you momentarily stunned.\n");
	    tell_watcher("With a mighty slash of "+QTNAME(tp)+"'s "+short+
	      ", "+QTNAME(tp)+" hews deeply into "+QTNAME(enemy)+"'s "+hdesc+
	      " leaving "+HIM_HER(enemy)+ " momentarily stunned.\n",enemy); 
	    break;
	}
    }
    if (dt == W_BLUDGEON)
    {
	switch(phurt)
	{
	case -1:
	    tp->catch_msg("You swing around your "+short+", hitting nothing "+
	      "but thin air.\n");
	    enemy->catch_msg(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      ", hitting nothing but thin air.\n");
	    tell_watcher(QCTNAME(tp)+" swings "+HIS_HER(tp)+" "+short+
	      ", hitting nothing but thin air.\n",enemy);
	    break;
	case 0:
	    tp->catch_msg(QCTNAME(enemy)+" laughs mockingly as you barely bump "+ 
	      "your "+short+" into "+HIS_HER(enemy)+" "+hdesc+".\n");
	    enemy->catch_msg("You laugh mockingly as "+QTNAME(tp)+" barely "+
	      "bumps "+HIS_HER(tp)+" "+short+" into your "+hdesc+".\n");
	    tell_watcher(QCTNAME(enemy)+" laughs mockingly as "+QTNAME(tp)+
	      " barely bumps "+HIS_HER(tp)+" "+short+" into "+QTNAME(enemy)+
	      "'s "+hdesc+".\n",enemy);
	    break;
	case 1..5:
	    tp->catch_msg("You lightly tap "+QTNAME(enemy)+" in the "+hdesc+
	      " with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" lightly taps your "+hdesc+" with "+
	      HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" lightly taps "+QTNAME(enemy)+"'s "+
	      hdesc+" with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 6..10:
	    tp->catch_msg("You almost unbalance "+QTNAME(enemy)+" as your "+
	      short+" hits "+HIS_HER(enemy)+" "+hdesc+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" almost unbalances you as "+HIS_HER(tp)+
	      short+" hits your "+hdesc+".\n");
	    tell_watcher(QCTNAME(tp)+" almost unbalances "+QTNAME(enemy)+
	      " as "+HIS_HER(tp)+" "+short+" hits "+HIS_HER(enemy)+
	      " "+hdesc+".\n",enemy);
	    break;
	case 11..20:
	    tp->catch_msg("You perform a heavy blow with your "+short+
	      ", hitting "+QTNAME(enemy)+"'s "+hdesc+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" performs a heavy blow with "+
	      HIS_HER(tp)+" "+short+", hitting your "+hdesc+".\n");
	    tell_watcher(QCTNAME(tp)+" performs a heavy blow with "+ HIS_HER(tp)+
	      " "+short+", hitting "+QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
	    break;
	case 21..40:
	    tp->catch_msg(QCTNAME(enemy)+" staggers as you crushingly hammer "+ 
	      "your "+short+" upon "+HIS_HER(enemy)+" "+hdesc+".\n");
	    enemy->catch_msg("You stagger as "+QTNAME(tp)+" crushingly hammers "+
	      HIS_HER(tp)+" "+short+" upon your "+hdesc+".\n");
	    tell_watcher(QCTNAME(enemy)+" staggers as "+QTNAME(tp)+" crushingly "+
	      "hammers "+HIS_HER(tp)+" "+short+" upon "+QTNAME(enemy)+
	      "'s "+hdesc+".\n",enemy);
	    break;
	case 41..60:
	    tp->catch_msg("You crushingly schmack "+QTNAME(enemy)+"'s "+hdesc+
	      " with your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" crushingly schmacks your "+hdesc+
	      " with "+HIS_HER(tp)+" "+short+".\n");
	    tell_watcher(QCTNAME(tp)+" crushingly schmacks "+QTNAME(enemy)+
	      "'s "+hdesc+" with "+HIS_HER(tp)+" "+short+".\n",enemy);
	    break;
	case 61..80:
	    tp->catch_msg("You smash your "+short+" upon "+QTNAME(enemy)+"'s "+
	      hdesc+", with a bone crushing sound.\n"); 
	    enemy->catch_msg(QCTNAME(tp)+" smashes "+HIS_HER(tp)+" "+short+
	      " upon your "+hdesc+", with a bone crushing sound.\n");
	    tell_watcher(QCTNAME(tp)+" smashes "+HIS_HER(tp)+" "+short+
	      " upon "+QTNAME(enemy)+"'s "+hdesc+", with a bone "+
	      "crushing sound.\n",enemy);
	    break;
	case 81..90:
	    tp->catch_msg("You break several of "+QTNAME(enemy)+"'s bones as "+
	      "you smash your "+short+" into "+HIS_HER(enemy)+" "+hdesc+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" breaks several of your bones as "+
	      HE_SHE(tp)+" shashes "+HIS_HER(tp)+" "+short+" into your "+
	      hdesc+".\n");
	    tell_watcher(QCTNAME(tp)+" breaks several of "+QTNAME(enemy)+"'s "+
	      "bones as "+HE_SHE(tp)+" shashes "+HIS_HER(tp)+" "+short+
	      " into "+HIS_HER(enemy)+" "+hdesc+".\n",enemy);
	    break;
	default:
	    tp->catch_msg("Your "+short+" almost crushes "+QTNAME(enemy)+ 
	      " to a bloody pulp with a mighty blow into "+HIS_HER(enemy)+
	      " "+hdesc+".\n");
	    enemy->catch_msg(QCTNAME(tp)+"'s "+short+" almost crushes you "+
	      "to a bloody pulp with a mighty blow into your "+hdesc+".\n");
	    tell_watcher(QCTNAME(tp)+"'s "+short+" almost crushes "+
	      QTNAME(enemy)+" to a bloody pulp with a mighty blow into "+
	      HIS_HER(enemy)+" "+hdesc+".\n",enemy);
	    break;
	}
    }
    return;
}
