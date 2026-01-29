/* This is the magical weapon which Derryn may wield, a tremendous two-handed
   axe. It has been blessed by a druid to grant the stone the durability of
   the best steel, as well as to protect its wielder from poisons.
   
   Code (c) 1998 Damian Horton, updated March 2001 for Raumdor.

   Updated, November 2002, by Casimir: Fixed hit_me() returns -2 bug.
   Addendum: Corrected bugs in the fix, November 11.       
*/

#pragma strict_types
#pragma save_binary

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Cirath/defs.h"

#define QTME     (enemy->query_the_name(me))
#define QTENEMY  (me->query_the_name(enemy))
#define QCTME    (enemy->query_The_name(me))
#define QCTENEMY (me->query_The_name(enemy))

inherit "/std/weapon";
inherit "/lib/keep"; //this weapon may be kept

void create_weapon()
{  
    set_name("axe");
    add_name("battleaxe");
    set_short("enormous obsidian battleaxe");
    set_long("An enormous, double-bladed battleaxe crafted purely from "+
	     "obsidian. The weapon is very well balanced, and is "+
	     "possessed of an amazingly sharp edge which shows no "+
	     "evidence of having ever dulled. Combine the balance, "+
	     "the sharpness of the edge, and the 25 kilograms of "+
	     "solid rock out of which it is made and you have a truly "+
	     "devestating weapon.\n");

  set_adj ("enormous");
  add_adj ("obsidian");
  add_adj ("double-bladed");

  set_hit(36);
  set_pen(46);

  set_wt(W_AXE);
  set_dt(W_SLASH);
  set_hands(W_BOTH);
  add_prop(OBJ_I_WEIGHT, 23700);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(36, 46) - random(100));
  add_prop(OBJ_I_VOLUME, 13700);
  add_prop(OBJ_M_NO_BUY,"You must be joking - I would never sell that "+
			"to the likes of you!\n");

  likely_dull = 4;
  likely_corr = 1;
  likely_break = 2;
  set_keep(1);

  //resistances of the axe itself
  add_prop(OBJ_I_RES_ACID, 50);
  add_prop(OBJ_I_RES_COLD, 50);
  add_prop(OBJ_I_RES_ELECTRICITY, 50);
  add_prop(OBJ_I_RES_FIRE, 50);
 
  add_prop(MAGIC_AM_MAGIC,({40, "enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_ID_INFO, ({"You detect that some enchantments have been"+
      "employed on this weapon. ", 10, "They have strengthened "+
      "material out of which this weapon was constructed, ensuring "+
      "that it will never dull or break",25, "A more subtle enchantment"+
      "also serves to help protect the wielder from the "+
      "damaging effects of poisonous substances he or she may come "+
      "into contact with.", 50}));

  add_prop(OBJ_S_WIZINFO,
      "- Grants the wielder a non-additive  poison resistance 25.\n"+
      "- Requires an 80 strength to wield.\n");

  set_wf(TO);
  set_keep(1); //this weapon is 'kept' by default
}

/* Returns one (at random) of the shield objects presently worn by a given
   player. Returns false (0) if the player is not wearing a shield.
*/
mixed
get_shield(object enemy)
{
    mixed* shields;
    
    shields = enemy->query_armour(-1);
    shields = filter(shields, &operator(==)(A_SHIELD, ) @  
		     &->query_at());
    
    if (! sizeof(shields)) return 0;
    return shields[random(sizeof(shields))];
}

/* Returns a random weapon wielded by the enemy, if any. Returns false if the
   argument is not wielding any weapons.
*/
mixed
get_random_weapon(object enemy)
{
    mixed* weapons = enemy->query_weapon(-1);
    if (! sizeof(weapons)) return 0;
    return weapons[random(sizeof(weapons))];
}
       
int
did_hit(int aid, string hdesc, int phurt,
	object enemy, int dt, int phit, int dam)
{
    object me;
    object special;     
    int rndnum;
    int rndlegs;
    string leg;
    mixed parrier; //object used to parry the attack, if applicable
    string parrier_short; //short description the parrying object

    me=ENV(TO);
    
    if(enemy->query_hp()<=0)
    {
	switch(hdesc)
	{
	  case "right arm":  
	      me->catch_tell("With a mighty swing, you bring your enormous "+
		  "obsidian battleaxe down upon "+QTME+"'s right "+
		  "shoulder, severing "+HIS_HER(enemy)+" arm!\n"+
		  HE_SHE(enemy)+" collapses to the ground, a fountain of "+
		  "blood gushing from the opened shoulder.\n");
	      me->tell_watcher("With a mighty swing, "+QTNAME(me)+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon "+
		  QTNAME(enemy)+"'s right shoulder, severing "+
		  HIS_HER(enemy)+" arm!\n"+ HE_SHE(enemy)+" collapses to "+
		  " the ground, a fountain of blood gushing from the opened "+ 
		  " shoulder.\n", enemy);
	      enemy->catch_tell("With a mighty swing, "+QTENEMY+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon your "+
		  "right shoulder, severing your arm from your body!\n"+
		  "Moments later, you are overcome by blinding pain from "+
		  "the wound. Mercifully, as abruptly as it came the pain "+
		  "ceases, being replaced by a mindnumbing blackness.\n");
	      break;
	  case "left arm":  
	    me->catch_tell("With a mighty swing, you bring your enormous "+
		  "obsidian battleaxe down upon "+QTME+"'s left "+
		  "shoulder, severing "+HIS_HER(enemy)+" arm!\n"+
		  capitalize(HE_SHE(enemy)) + " collapses to the ground, "+
			   "a fountain of "+
		  "blood gushing from the opened shoulder.\n");
	    me->tell_watcher("With a mighty swing, "+QTNAME(me)+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon "+
		  QTNAME(enemy)+"'s left shoulder, severing "+
		  HIS_HER(enemy)+" arm!\n"+ 
		  capitalize(HE_SHE(enemy))+" collapses to "+
		  " the ground, a fountain of blood gushing from the opened "+ 
		  " shoulder.\n", enemy);
	    enemy->catch_tell("With a mighty swing, "+QTENEMY+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon your "+
		  "left shoulder, severing your arm from your body!\n"+
		  "Moments later, you are overcome by blinding pain from "+
		  "the wound. Mercifully, as abruptly as it came the pain "+
		  "ceases, being replaced by a mindnumbing blackness.\n");
	      break;
	  case "head":  
	      me->catch_tell("With a tremendous overhead strike, you cleave "+
		  "through "+QTME+"'s skull with your enormous obsidian "+
		  "battleaxe!\n");
	      me->tell_watcher("With a tremendous overhead strike, "+
		  QTNAME(me)+" cleaves through "+QTNAME(enemy)+"'s skull "+
		  "with "+HIS_HER(me)+" enormous obsidian battleaxe!\n",
		  enemy);
	      enemy->catch_tell(QCTENEMY+" brings "+HIS_HER(me)+" enormous "+
		  "obsidian battleaxe crashing down upon your skull with "+
		  "a tremendous overhead strike. A surge of white pain "+
		  "courses through you as your skull shatters under the "+
		  "force of the blow!\n");
	      break;
	  case "legs":  
	      rndlegs=(random(2));
	      if (rndlegs == 1) 
		 leg="right"; 
	      else 
		 leg="left";
	      
	      me->catch_tell("A powerful swing with your enormous obsidian "+ 
		  "battleaxe severs "+QTME+"'s "+leg+" leg, just "+
		  "below the groin!\n"+CAP(HE_SHE(enemy))+" falls over, "+
		  "blood gushing from the severed extremity.\n");
	      me->tell_watcher("A powerful swing from "+QTNAME(me)+"'s "+    
		  "enormous obsidian battleaxe "+QTNAME(enemy)+"'s "+leg+
		  " leg, just below the groin!\n"+CAP(HE_SHE(enemy))+
		  " falls over, blood gushing from the severed extremity.\n",
			       enemy);
	      enemy->catch_tell("A powerful swing from "+QTENEMY+"'s "+ 
		  "enormous obsidian battleaxe severs your "+leg+" leg from "+
		  "just below the groin!\n"+"You tumble over backwards, "+
		  "striking the ground before the pain registers. When it "+
		  "does, all you can do is pray for death. Fortunatly, "+
		  "your prayers are answered swiftly.\n");
	      break;
	  case "body":  
	      me->catch_tell("A devestasting blow from your enormous "+
		  "obsidian battleaxe catches "+QTME+" right in "+
		  "the gut!\n"+"A mixture of blood and organs spews forth "+
		  "from the resulting wound, staining the ground.\n");
	      me->tell_watcher("A devestating blow from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe catches "+QTNAME(enemy)+
		  " right in the gut!\n"+"A mixture of blood and organs "+
		  "spews forth from the resulting wound, staining the "+
		  "ground.\n", enemy);
	      enemy->catch_tell("A devestating blow from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe catches you right in the "+
		  "gut!\n"+"A mixture of blood and organs spews forth "+
		  "from the resulting wound, staining the ground.\n");
	      break;
	  default:
	      me->catch_tell("You raise the enormous obsidian battleaxe "+
		  "high above your head, and bring it down in one final, "+
		  "violent strike!\n");
	      me->tell_watcher(QTNAME(me)+" raises "+HIS_HER(me)+" enormous "+
		  "obsidian battleaxe high above "+HIS_HER(me)+" head and "+
		  "then brings it down upon "+QTNAME(enemy)+" in one final, "+
		  "violent strike!\n", enemy);
	      enemy->catch_msg(QCTENEMY+" raises "+HIS_HER(me)+
		  "enormous obsidian battleaxe high above "+HIS_HER(me)+
		  "head and then brings it down upon you in one final, "+
		  "violent strike!\n");
	  break;
	  }
	enemy->do_die(query_wielded());

	return 1;
    }

    switch(phurt)
    {
	//new case which applies when an attack is parried	
    case -2:
	parrier = get_shield(enemy);
	if (! parrier)
	{
	    parrier = get_random_weapon(enemy);
	    if (! parrier)
	    {
		//this should never happen, since it is impossible to parry
		//without a weapon, but in case it does, we fall through to
		//the dodge -1 default messages
		phurt = -1;
	    }
	    else
	    {
		//we parried with a weapon, since we possessed no shield
		parrier_short = parrier->short();
		me->catch_msg(QCTNAME(enemy) + " brings " + HIS_HER(enemy) + " " + 
		    parrier_short + " forcefully across " + 
		    HIS_HER(enemy) + " body, knocking aside your "+
		    "enormous obsidian battleaxe before it cleaves " + 
                    HIM_HER(enemy) + " in two.\n");
		me->tell_watcher(QCTNAME(enemy) + " brings " + HIS_HER(enemy) +
		    " " + parrier_short + " forcefully across " + 
		    HIS_HER(enemy) + " body, knocking aside " + 
		    QTENEMY + "'s enormous obsidian battleaxe "+
		    "it cleaves " + HIM_HER(enemy) + " in two.\n", enemy);
		enemy->catch_tell("You bring your " + parrier_short + 
		    " forcefully across your body, knocking aside " +
		    QTENEMY + "'s enormous obsidian battleaxe before "+
		    "it cleaves you in two.\n");
		return 1;
	    }
	}
	
	if (parrier)
	{
	    //the enemy was wearing a shield, so a parry result is more likely
	    //to have been performed with a shield ... especially against a 
	    //massive and heavy weapon such as this
	    parrier_short = parrier->short();
	    me->catch_msg("You rattle a bone-jarring blow of your "+ 
		      "enormous obsidian battleaxe off of " + 
		      QTNAME(enemy) + "'s " + parrier_short + ".\n");
	    me->tell_watcher(QCTNAME(me) + " rattles a bone-jarring blow of "+
			 HIS_HER(me) + " enormous obsidian battleaxe off of "+
			 QTNAME(enemy) + "'s " + parrier_short + ".\n", enemy);
	    enemy->catch_tell("You bring your " + parrier_short + " up just "+
			      "in time to block a blow from " + QTENEMY +
			  "'s enormous obsidian battleaxe. "+
			  "Waves of numbness travel up your arm as it "+
			  "crumples under the force of the blow.\n");
	    break;
	}
    
    case -1:
	rndnum = (random(3));
	switch(rndnum)
	{ 
	  case 1: 
	      me->catch_tell(QCTME+" barely gets out of the way "+
		  "of your enormous obsidian battleaxe as it comes "+
		  "crashing down where "+HE_SHE(enemy)+" was just "+
		  "standing.\n");
	      me->tell_watcher(QCTNAME(enemy)+" barely gets out of the "+
		  "way of "+QTNAME(me)+"'s enormous obsidian battleaxe as "+
		  "it comes crashing down where "+HE_SHE(enemy)+" was just "+
		  "standing.\n", enemy);
	      enemy->catch_tell("You barely get out of the way of "+QTENEMY+
		  "'s enormous obsidian battleaxe as it comes crashing down "+
		  "where you were just standing.\n");
	      break;
	  case 2:
	      me->catch_tell(QCTME+" steps back and out of reach "+
		  "as you swing for "+HIM_HER(enemy)+" with your enormous "+
		  "obsidian battleaxe.\n");
	      me->tell_watcher(QCTNAME(enemy)+ " steps back and out of "+
		  "reach as "+QTNAME(me)+" swings for "+HIM_HER(enemy)+
		  " with "+HIS_HER(me)+" enormous obsidian battleaxe.\n", enemy);
	      enemy->catch_tell("You step back so as to be out of reach as "+
		  QTENEMY+" swings for you with "+HIS_HER(me)+
		  " enormous obsidian battleaxe.\n");
	      break;
	  default:
	      me->catch_tell("You swing wildly with your enormous obsidian "+
		  "battleaxe, catching nothing but thin air.\n");
	      me->tell_watcher(QCTNAME(me)+" swings wildly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe, catching "+
		  "nothing but thin air.\n", enemy);
	      enemy->catch_tell(QCTENEMY+" swings wildly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe, catching "+
		  "nothing but thin air.\n");
		break;
	  }
	  break;
      case 0..2:
	me->catch_tell("You scratch "+QTME+"'s "+hdesc+" with "+
	    "your enormous obsidian battleaxe.\n");
	me->tell_watcher(QCTNAME(me)+" scratches "+QTNAME(enemy)+"'s "+ 
	    hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe.\n",
			 enemy);
	enemy->catch_tell(QCTENEMY+" scratches your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe.\n");
	break;
      case 3..6:
	me->catch_tell("You graze "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe.\n");
	me->tell_watcher(QCTNAME(me)+" grazes "+QTNAME(enemy)+"'s "+ 
	hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe.\n",
			 enemy);
	enemy->catch_tell(QCTENEMY+" grazes your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe.\n");
	break;               
      case 7..15:  
	me->catch_tell("You slice "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe.\n");
	me->tell_watcher(QCTNAME(me)+" slices "+QTNAME(enemy)+"'s "+ 
	hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe.\n",
			 enemy);
	enemy->catch_tell(QCTENEMY+" slices your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe.\n");
	break;               
      case 16..35:
	me->catch_tell("You cut deeply into "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe!\n");
	me->tell_watcher(QCTNAME(me)+" cuts deeply into "+QTNAME(enemy)+
			 "'s "+hdesc+" with "+HIS_HER(me)+
			 " enormous obsidian battleaxe!\n", enemy);
	enemy->catch_tell(QCTENEMY+" cuts deeply into your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe!\n");
	break;               
      case 36..70:
	switch(hdesc)
	{
	  case "head":
	      me->catch_tell(QCTME+"'s feeble attempt to parry succeeds in "+
		  "in turning the blade of the enormous obsidian "+
		  "battleaxe away from "+HIS_HER(enemy)+ " head, but it "+
		  "still strikes side-on with terrible concussive "+
		  "force!\n");
	      me->tell_watcher(QCTNAME(enemy)+" feeble attempts to parry "+
		  "succeed in turning the blade of "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe away from "+HIS_HER(enemy)+
		  " head, but it still strikes side-on with terrible "+
		  "concussive force!\n", enemy);
	      enemy->catch_tell("A powerful sidelong swing from "+
		  QTENEMY+" strikes you off guard. You feebly attempt to "+
		  "parry the blow, suceeding in turning the enormous "+
		  "obsidian blade away from you head, but it still "+
		  "strikes you side-on with terrible concussive force!\n");
	      break;
	  case "body":
	      me->catch_tell("The blade of your enormous obsidian "+
		  "battleaxe travels in a graceful arc which culminates "+
		  "with it being buried nearly an inch deep into "+QTME+
		  "'s ribcage!\n");
	      me->tell_watcher("The blade of "+QTNAME(me)+"'s enormous "+
		  "obsidian battleaxe travels in a graceful arc which "+
		  "culminates with it being embedded nearly an "+
		  "inch deep in "+QTNAME(enemy)+"'s ribcage!\n", enemy);
	      enemy->catch_tell("The blade of "+QTENEMY+"'s enormous "+
		  "obsidian battleaxe travels in a graceful arc which "+
		  "culminates with it being embedded nearly an inch deep "+
		  "into your ribcage!\n");
	      break;
	  case "left arm":
	      me->catch_tell("A sidelong strike from your enormous "+
		  "obsidian battleaxe removes a large chunk of flesh "+
		  "from "+QTME+"'s left arm!\n");
	      me->tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s left arm!\n", enemy);
	      enemy->catch_tell("A sidelong strike from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from your left arm!\n");
	      break;
	  case "right arm":
	      me->catch_tell("A sidelong strike from your enormous "+
		  "obsidian battleaxe removes a large chunk of flesh "+
		  "from "+QTME+"'s right arm!\n");
	      me->tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s right arm!\n", enemy);
	      enemy->catch_tell("A sidelong strike from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from your right arm!\n");
	      break;
	  case "legs":
	    rndlegs=(random(2));
	      if (rndlegs == 1) 
		 leg="right"; 
	      else 
		 leg="left";
	      
	      me->catch_tell("A sidelong strike from your enormous "+
		  "obsidian battleaxe removes a large chunk of flesh "+
		  "from "+QTME+"'s "+leg+" leg!\n");
	      me->tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s "+leg+" leg!\n", enemy);
	      enemy->catch_tell("A sidelong strike from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from your "+leg+" leg!\n");
	      break;
	default:
	      me->catch_tell("You strike "+QTME+" with a tremendous blow "+
		  "from your enormous obsidian battleaxe!\n");
	      me->tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+
		  "with a tremendous blow from "+HIS_HER(me)+" enormous "+
		  "obsidian battleaxe!\n", enemy);
	      enemy->catch_tell("You are struck by a tremendous blow "+
		  "from "+QTENEMY+"'s enormous obsidian battleaxe!\n");
	      break;
	}
	break;
     default:    
	switch (hdesc)
	{  
	  case "head":
	      me->catch_tell("You strike "+QTME+"'s head with a powerful "+
		  "blow from your enormous obsidian battleaxe. You are "+
		  "amazed that "+HE_SHE(enemy)+" is still standing!\n");
	      me->tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+"'s "+
		  "head with a powerful blow from the enormous obsidian "+
		  "battleaxe! You are amazed that "+HE_SHE(enemy)+" is "+
		  "still standing!\n", enemy);
	      enemy->catch_tell("You are struck in the head by a powerful "+
		  "blow from "+QTENEMY+"'s enormous obsidian battleaxe! "+
		  "Somehow, the force of the blow was not enough to "+
		  "crack your skull, and thus you live still...\n");
	      break;
	  case "body":
	      me->catch_tell("You slice open "+QTME+"'s belly with "+
		  "your enormous obsidian battleaxe! "+CAP(HE_SHE(enemy))+
		  " clings to life, and "+HIS_HER(enemy)+" guts by the "+
		  "barest of margins!\n");
	      me->tell_watcher(QCTNAME(me)+" slices open "+QTNAME(enemy)+
		  "'s belly with "+HIS_HER(me)+" enormous obsidian "+
		  "battleaxe! "+QCTNAME(enemy)+" clings to life, and "+
		  HIS_HER(enemy)+" guts by the barest of margins!\n",
			       enemy);
	      enemy->catch_tell(QCTENEMY+" slices open your belly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe! You cling "+
		  "to your life, and your guts by the barest of margins!\n");
	      break;
	  case "right arm":
	      me->catch_tell("You chop "+QTME+"'s "+hdesc+" to the "+
		  "bone, nearly lopping it off!\n");
	      me->tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  hdesc+" to the bone, nearly lopping it off!\n", enemy);
	  enemy->catch_tell(QCTENEMY+" chops your "+hdesc+" "+
		 "to the bone, nearly lopping it off!\n");
	      break;
	  case "left arm":
	      me->catch_tell("You chop "+QTME+"'s "+hdesc+" right to the "+
		  "bone, nearly lopping it off!\n");
	      me->tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  hdesc+" right into the bone, nearly lopping it off!\n",
			       enemy);
	      enemy->catch_tell(QCTENEMY+" chops your "+hdesc+" right "+
		 "into the bone, nearly lopping it off!\n");
	      break;
	  case "legs":
	      rndlegs=random(2);
	      if (rndlegs == 1) 
		 leg="right"; 
	      else 
		 leg="left";
	      
	      me->catch_tell("You chop "+QTME+"'s "+leg+" leg, to "+
		  "the bone, nearly lopping it off!\n");
	      me->tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  leg+" leg to the bone, nearly lopping it off!\n", enemy);
	      enemy->catch_tell(QCTENEMY+" chops your "+leg+" leg "+
		 "to the bone, nearly lopping it off!\n");
	      break;
	  default:
	      me->catch_tell("You deal "+QTME+" a near mortal blow with "+
		  "your enormous obsidian battleaxe!\n");
	      me->tell_watcher(QCTNAME(me)+" deals "+QTNAME(enemy)+" a "+
		  "a near mortal blow with "+HIS_HER(me)+" enormous "+
		  "obsdian battleaxe!\n", enemy);
	      enemy->catch_msg(QCTENEMY+" deals you a near mortal blow "+
		  "with "+HIS_HER(me)+" enormous obsidian battleaxe!\n");
	      break;
	}
    }
    return 1;
}
mixed
wield(object to)
{
    if(TP->query_stat(SS_STR) < 80)
    {
	say(QCTNAME(TP) + " tries feebly to wield the " + short() + " but "+
	    "fails!\n");
	return("You try to wield the enormous obsidian battleaxe, but lack "+
	       "the strength needed to make effective use of such a heavy "+
	       "weapon.\n");
	
    }
    else
    {   
	TP->catch_tell("As you grasp the handle of enormous obsidian "+ 
	    "battleaxe firmly in both hands, an odd feeling comes over "+
	    "you. You almost get the impression that the weapon is "+
	    "somehow trying to protect you from harm.\n");
	TP->add_magic_effect(this_object());
	return 0;
    }
}

mixed
unwield(object to)
{
    TP->remove_magic_effect(this_object());
    return 0; //unwielded with the normal messages
}

/* Grants a non-additive poison resistance of 25 to the wielder. */
mixed
query_magic_protection(string prop, object what)
{
    if (what == query_wielded())
    {
	if (prop == MAGIC_I_RES_POISON)
	{
	    return ({25, 0});
	}
    }
    
    return ::query_magic_protection(prop, what);
}





