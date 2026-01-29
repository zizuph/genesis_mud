#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";

int attack = 0;

create_weapon()
{
    set_name("knife");
    add_adj("newbie");
    set_short("tiny newbie knife");
    set_long("This is a newbie knife. It has no real value to anyone"+
	" but a real newbie. It's not a great weapon but its "+
	"better than nothing at all.... "+"@@strange_look");
    set_default_weapon(25, 25, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This is a magical knife, enchanted by "+
      "elves of unknown origin. When wielded by a newbie "+
      "it will aid them considerably.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This knife is magical.\n", 5,
	"A smaller person can have use of this.\n", 10,
	"The knife is a newbie-helper knife, created by elves.\n", 25,
	"To gain the power, one must be small, and grip the weapon \n", 50 }));
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40) + 2500);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    set_wf(TO);
    set_pm(({-3,0,3}));
    seteuid(getuid(TO));
}



string
strange_look()
{
    if (TP->query_skill(SS_AWARENESS) >= 50)
	return "\n\nSomehow , this newbie knife does not "+
      "look quite like others you have seen... strange.\n";
   
    else return ".\n";
}


void
init()
{
    add_action("grip", "grip");
     ::init();
}

int
grip (string str)
{
    object *tar;

    NF("What?\n");
    if (TO->query_wielded() != TP)
	return 0;

    NF("Grip what?\n");
    if (!str)
	return 0;

    if (str == "knife" || str == "newbie knife" || str == "tiny newbie knife")
    {
	if(TP->query_average_stat()<50 && attack==0)
	{
	write("You grip the knife tightly in your hand, and when doing so, "+
	  "you feel some obscure power starting to guide your hand.\n");
	TP->add_mana(-30);
	attack=1;
 	}
	else
	{
	write("You grip the knife, but feel nothing.\n");
	}

	return 1;
    }

}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{

    int a = random(150)+10;
    int hp = enemy->query_hp();
    int per = a * 100;
    string *desc;
    string str;
    object me = query_wielded();
 

    per = (hp == 0 ? per : per / hp);
    str = file_name(environment(me));
    
    if (attack == 1)
    {

	attack = 0;

	switch(per)
	{
	case 0..15:
	    desc = ({ "a ray of raw power shoots forth from it, grazing "+
	      QTNAME(enemy)+" and throwing you back four feet.\n",
	      "a ray of power shoots from it , grazing you, and throwing"+
		" "+QTNAME(environment())+" back four feet.\n",
	      "a ray of power shoots from it, grazing "+
	      QTNAME(enemy)+", and throwing "+QTNAME(environment())+" back four feet.\n"});
		 break;
	case 16..30:
	    desc = ({ "a ray of raw power shoots from it, striking"+ 
		      " "+QTNAME(enemy)+" squarely in the chest.\n",
	     "a ray of raw power shoots from it, striking"+ 
		      " you squarely in the chest.\n",
	      "a ray of raw power shoots from it, striking"+ 
		      " "+QTNAME(enemy)+" squarely in the chest.\n"});
	    break;
	case 31..45:
	    desc = ({ "a large ray of raw power shoots forth from it"+
	      ", burning into "+QTNAME(enemy)+
	      "'s flesh.\n",
	      "a large ray of raw power shoots forth from it"+
	      " towards you, burning "+
	      "into your flesh.\n",
	      "a large ray of raw power shoots forth from it"+
	      ", burning into "+QTNAME(enemy)+
	      "'s flesh.\n"});
	    break;
	default:
	    desc = ({ "an enormous ray of power shoots forth "+
	      "from it into the head of "+QTNAME(enemy)+
	      ", whos head start smoking and reeking from burnt hair.\n",
	      "an enormous ray of power shoots forth from it"+
	      "hitting you in the head. You smell hair burning.\n",
	      "an enormous ray of power shoots forth "+
	      "from it into the head of "+QTNAME(enemy)+
	      ", who's head start smoking and reeking from burnt hair.\n"});
	    break;
	}

	enemy->heal_hp(-a);

	if (enemy->query_hp() > 0)
	{
	    wielder->catch_msg("You hold your "+short()+" defensively "+
	      "in front of you, and "+desc[0]);
	    enemy->catch_msg(QCTNAME(me)+"holds "+POSSESSIVE(me)+
	      " "+short()+" defensively towards you, and "+desc[1]);
	    me->tell_watcher(QCTNAME(me)+" holds "+POSSESSIVE(me)+ " "+
	      short()+" defensively towards "+QTNAME(enemy)+", and "+
	      desc[2], enemy);
	}


	if (enemy->query_hp() <= 0)
	{
	    enemy->add_prop(LIVE_I_NO_CORPSE, 1);
	    me->catch_msg("The ray of power erupts with great intensity, "+
	      "hitting "+QTNAME(enemy)+" with a devestating result. Bits and "+
	      "pieces of "+QTNAME(enemy)+"is spread all over the area.\n");
	    me->tell_watcher("The ray of power erupts with great intensity, "+
	      "hitting "+QTNAME(enemy)+" with a devestating result. Bits and "+
	      "pieces of "+QTNAME(enemy)+" is spread all over the area.\n",enemy);
     	    enemy->do_die(me);
	}
	return 1;
    }



    switch(phurt)
    {
    case -1..0:
	wielder->catch_msg("You fence wildly with the "+short()+", "+
	  "utterly embarrasing yourself as you are nowhere near the "+
	  "enemy.\n");
	enemy->catch_msg(QCTNAME(wielder)+" looks pretty silly, fencing "+
        "wildly with the "+short()+", and failing miserably to hit you.\n");
	me->tell_watcher(QCTNAME(wielder)+" looks pretty silly, fencing "+
        "wildly with the "+short()+", but failing miserably to hit "+QTNAME(enemy)
	  +".\n", enemy);
	break;

    case 1..4:
	wielder->catch_msg("You fence wildly with the "+short()+", "+
	  "and manage to inflict a minor cut on "+QTNAME(enemy)+"'s "+hdesc+".\n");
	enemy->catch_msg(QCTNAME(wielder)+"fences wildly with the "+short()+" inflicting"+
	  "a minor cut in your "+hdesc+". Hmph, lucky shot....\n");
	me->tell_watcher(QCTNAME(wielder)+"fences wildly with the "+short()+", "+
	  "managing to inflict minor cut in the "+hdesc+" of "+
	  QTNAME(enemy)+".\n",enemy);
	break;

    case 5..9:
	wielder->catch_msg("Desperately lounging forward with the "+short()+", you "+
	  "stumble into "+
	  QTNAME(enemy)+"'s "+hdesc+", cutting him.\n");
	enemy->catch_msg("Desperately lounging forward with "+POSSESSIVE(wielder)+
	  " "+short()+", "+PRONOUN(wielder)+" stumbles towards you, cutting your "+
	  hdesc+".\n");
	me->tell_watcher("Desperately lounging forward with "+POSSESSIVE(wielder)+
	  " "+short()+", "+PRONOUN(wielder)+" stumbles towards "+QTNAME(enemy)+"'s"+
        " "+hdesc+", cutting it.\n",enemy);
	break;

    case 10..19:
	wielder->catch_msg("You stab viciously at "+QTNAME(enemy)+
	  ", managing to hit his "+POSSESSIVE(enemy)+" "+hdesc+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" stabs viciously at you "+
	  "with "+POSSESSIVE(wielder)+" "+short()+", hitting "+
	  "your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+" stabs viciously at "+
	  QTNAME(enemy)+" with "+POSSESSIVE(wielder)+" "+short()+", "+
	  "hitting "+QTNAME(enemy)+"'s "+hdesc+".\n",
	  enemy);
	break;

    case 20..29:
	wielder->catch_msg("You make a berserk attack with your "+short()+
	", running fearlessly towards "+QTNAME(enemy)+
	  ", slashing deeply into "+POSSESSIVE(enemy)+" "+hdesc+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" makes a berserk attack with "+short()+
	 ", running fearlessly towards "+
	  "you , slashing deeply into your "+hdesc+".\n");
	me->tell_watcher(QCTNAME(wielder)+" makes a berserk attack with "+short()+
	  ", running fearlessly towards "+
	  QTNAME(enemy)+" , slashing deeply into "+
	  POSSESSIVE(enemy)+" "+hdesc+".\n",enemy);
	break;

    case 30..49:
	wielder->catch_msg(QCTNAME(enemy)+" looks very surprised as you manage to "+
	  "sneak past his defences with your "+short()+" sliding the blade into "+
        POSSESSIVE(enemy)+" "+hdesc+
	  ".\n");
	enemy->catch_msg("You are very surprised when a sharp pain "+
	 "in your "+hdesc+" makes you aware that "+QTNAME(wielder)+" slipped"+
       " past your defences.\n");
	me->tell_watcher(QCTNAME(enemy)+" looks very surprised as "+QTNAME(wielder)+
	  " sneaks past "+POSSESSIVE(enemy)+" defences, sliding the "+short()+
        " into"+POSSESSIVE(enemy)+
	  " "+hdesc+".\n",enemy);
	break;

    case 50..75:
	wielder->catch_msg("Screaming insanely, you swiftly flick the "+short()+
	  " into "+QTNAME(enemy)+"'s "+
	  hdesc+" with a twist of your wrist.\n");
	enemy->catch_msg("Screaming insanely "+QCTNAME(wielder)+" swiftly flicks the "
	  +short()+" into your "+hdesc+".\n");
	me->tell_watcher("Screaming insanely "+QCTNAME(wielder)+" swiftly flicks "+
	  POSSESSIVE(wielder)+" "+short()+" into "+QTNAME(enemy)+
	  "'s "+hdesc+", with a mere twist of the wrist.\n",
	  enemy);
	break;

    case 76..99:
	wielder->catch_msg("Throwing yourself forward with the "+short()+", you "+
	  "impale "+QTNAME(enemy)+" ripping up a horrible wound in "+POSSESSIVE(enemy)+
	  " "+hdesc+".\n");
	enemy->catch_msg(QTNAME(wielder)+" throws himself at you, ripping up a "+
	  "horrible wound in your "+hdesc+". \n");
	me->tell_watcher(QCTNAME(wielder)+" throws himself forward at "+QTNAME(enemy)+", ripping  "+
	  "up a horrible wound in "+POSSESSIVE(enemy)+" "+hdesc+".\n",enemy);
	break;

    default:
	wielder->catch_msg("With a final effort you close in on "+
	  QTNAME(enemy)+" to end this fight. With a calculating thrust "+
	  "you pierce "+POSSESSIVE(enemy)+" breastbone, puncturing "+
	  POSSESSIVE(enemy)+" heart. As the blood flows onto the ground, life leaves "+
        QTNAME(enemy)+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" closes in on you. You try "+
	  "to rise, but feel to weak. With a final blow, you feel your "+
	  "breastbone being punctured. Gasping, all fades into blackness. "+
	  "Who is that figure ? Oh no.....\n");
	me->tell_watcher(QCTNAME(wielder)+" closes in on "+QTNAME(enemy)+
	  ". With a final blow to the chest,"+
	  QTNAME(enemy)+"'s heart is pierced, and "+PRONOUN(enemy)+" slides "+
	  "lifeless to the ground.\n",enemy);
	break;
    }
    return 1;
}
