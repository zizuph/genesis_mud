/* This is Derryn's weapon, a tremendous two-handed axe. Like most of
   the best weapons on Athas, it has been touched by psionics, ensuring,
   amongst other things, that it will never dull, or break. It also
   conveys a degree of protection from poison upon its wielder.
   Code (c) 1998 Damian Horton
*/

#pragma strict_types
#pragma save_binary


inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <formulas.h>
#include "defs.h"

#define QTME     (enemy->query_the_name(me))
#define QTENEMY  (me->query_the_name(enemy))
#define QCTME    (enemy->query_The_name(me))
#define QCTENEMY (me->query_The_name(enemy))

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

  set_hit(38);
  set_pen(44);

  set_wt(W_AXE);
  set_dt(W_SLASH);
  set_hands(W_BOTH);
  add_prop(OBJ_I_WEIGHT,23700);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(38,44) - random(100));
  add_prop(OBJ_I_VOLUME,13700);
  add_prop(OBJ_M_NO_BUY,"You must be joking - I would never sell that "+
			"to the likes of you!\n");

  likely_dull=0;
  likely_corr=0;
  likely_break=0;

  add_prop(MAGIC_AM_MAGIC,({40,"psionic"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO, ({"You detect that some psionics have been"+
      "employed on this weapon. ", 10,"Psionics have strengthened "+
      "material out of which this weapon was constructed, ensuring "+
      "that it will never dull or break",25,"A more subtle use of "+
      "psionics also serves to help protect the wielder from the "+
      "damaging effects of poisonous substances he or she may come "+
      "into contact with.",50}));

  add_prop(OBJ_S_WIZINFO, "- Never dulls, breaks or corrodes.\n"+
      "- Grants the wielder a poison resistance level of x.\n"+
      "- Requires an 80 strength to wield.\n");

  set_wf(TO);
}
varargs void
tell_watcher(string str, object enemy, mixed arr)
{
    object *ob;
    int i, size;
    object me = ENV(TO);

    ob = all_inventory(environment(me)) - ({ me, enemy });

    if (arr)
    {
        if (pointerp(arr))
            ob -= arr;
        else
            ob -= ({ arr });
    }

    i = -1;
    size = sizeof(ob);
    while(++i < size)
    {
        if (ob[i]->query_see_blood() && CAN_SEE_IN_ROOM(ob[i]))
        {
            if (CAN_SEE(ob[i], me))
                ob[i]->catch_msg(str);
            else
                tell_object(ob[i], enemy->query_The_name(ob[i]) +
                    " is hit by someone.\n");
        }
    }
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

    me=ENV(TO);
    
    ::did_hit();
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
	tell_watcher("With a mighty swing, "+QTNAME(me)+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon "+
		  QTNAME(enemy)+"'s right shoulder, severing "+
		  HIS_HER(enemy)+" arm!\n"+ HE_SHE(enemy)+" collapses to "+
		  " the ground, a fountain of blood gushing from the opened "+ 
		  " shoulder.\n");
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
		  HE_SHE(enemy)+" collapses to the ground, a fountain of "+
		  "blood gushing from the opened shoulder.\n");
      tell_watcher("With a mighty swing, "+QTNAME(me)+" brings "+
		  HIS_HER(me)+" enormous obsidian battleaxe down upon "+
		  QTNAME(enemy)+"'s lefy shoulder, severing "+
		  HIS_HER(enemy)+" arm!\n"+ HE_SHE(enemy)+" collapses to "+
		  " the ground, a fountain of blood gushing from the opened "+ 
		  " shoulder.\n");
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
      tell_watcher("With a tremendous overhead strike, "+
		  QTNAME(me)+" cleaves through "+QTNAME(enemy)+"'s skull "+
		  "with "+HIS_HER(me)+" enormous obsidian battleaxe!\n");
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
      tell_watcher("A powerful swing from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe "+QTNAME(enemy)+"'s "+leg+
		  " leg, just below the groin!\n"+CAP(HE_SHE(enemy))+
		  "falls over, blood gushing from the severed extremity.\n");
	      enemy->catch_tell("A powerful swing from "+QTENEMY+"'s "+ 
		  "enormous obsidian battleaxe severs your "+leg+" leg from "+
		  "just below the groin!\n"+"You tumble over backwards, "+
		  "striking the ground before the pain registers. When it "+
		  "does, all you can do is pray for Death. Fortunatly, "+
		  "your prayers are answered swiftly.\n");
	      break;
	  case "body":  
	      me->catch_tell("A devestasting blow from your enormous "+
		  "obsidian battleaxe catches "+QTME+" right in "+
		  "the gut!\n"+"A mixture of blood and organs spews forth "+
		  "from the resulting wound, staining the ground.\n");
      tell_watcher("A devestating blow from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe catches "+QTNAME(enemy)+
		  " right in the gut!\n"+"A mixture of blood and organs "+
		  "spews forth from the resulting wound, staining the "+
		  "ground.\n");
	      enemy->catch_tell("A devestating blow from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe catches you right in the "+
		  "gut!\n"+"A mixture of blood and organs spews forth "+
		  "from the resulting wound, staining the ground.\n");
	      break;
	  default:
	      me->catch_tell("You raise the enormous obsidian battleaxe "+
		  "high above your head, and bring it down in one final, "+
		  "violent strike!\n");
      tell_watcher(QTNAME(me)+" raises "+HIS_HER(me)+" enormous "+
		  "obsidian battleaxe high above "+HIS_HER(me)+" head and "+
		  "then brings it down upon "+QTNAME(enemy)+" in one final, "+
		  "violent strike!\n");
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
      case -1:
	rndnum = (random(3));
	switch(rndnum)
	{ 
	  case 1: 
	      me->catch_tell(QCTME+" barely gets out of the way "+
		  "of your enormous obsidian battleaxe as it comes "+
		  "crashing down where "+HE_SHE(enemy)+" was just "+
		  "standing!\n");
     tell_watcher(QCTNAME(enemy)+" barely gets out of the "+
		  "way of "+QTNAME(me)+"'s enormous obsidian battleaxe as "+
		  "it comes crashing down where "+HE_SHE(enemy)+" was just "+
		  "standing!\n");
	      enemy->catch_tell("You barely get out of the way of "+QTENEMY+
		  "'s enormous obsidian battleaxe as it comes crashing down "+
		  "where you were just standing!\n");
	      break;
	  case 2:
	      me->catch_tell(QCTME+" steps back and out of reach "+
		  "as you swing for "+HIM_HER(enemy)+" with your enormous "+
		  "obsidian battleaxe.\n");
     tell_watcher(QCTNAME(enemy)+ " steps back and out of "+
		  "reach as "+QTNAME(me)+" swings for "+HIM_HER(enemy)+
		  " with "+HIS_HER(me)+" enormous obsidian battleaxe.\n");
	      enemy->catch_tell("You step back so as to be out of reach as "+
		  QTENEMY+" swings for you with "+HIS_HER(me)+
      " enormous obsidian battleaxe.\n");
	      break;
	  default:
	      me->catch_tell("You swing wildly with your enormous obsidian "+
		  "battleaxe, catching nothing but thin air.\n");
	tell_watcher(QCTNAME(me)+" swings wildly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe, catching "+
		  "nothing but thin air.\n");
	      enemy->catch_tell(QCTENEMY+" swings wildly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe, catching "+
		  "nothing but thin air.\n");
		break;
	  }
	  break;
      case 0..2:
	me->catch_tell("You scratch "+QTME+"'s "+hdesc+" with "+
	    "your enormous obsidian battleaxe.\n");
	tell_watcher(QCTNAME(me)+" scratches "+QTNAME(enemy)+"'s "+
	    hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe.\n");
	enemy->catch_tell(QCTENEMY+" scratches your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe.\n");
	break;
      case 3..6:
	me->catch_tell("You graze "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe.\n");
	tell_watcher(QCTNAME(me)+" grazes "+QTNAME(enemy)+"'s "+
	hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe.\n");
	enemy->catch_tell(QCTENEMY+" grazes your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe.\n");
	break;               
      case 7..15:  
	me->catch_tell("You slice "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe!\n");
	tell_watcher(QCTNAME(me)+" slices "+QTNAME(enemy)+"'s "+
	hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe!\n");
	enemy->catch_tell(QCTENEMY+" slices your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe!\n");
	break;               
      case 16..35:
	me->catch_tell("You cut deeply into "+QTME+"'s "+hdesc+" with "+
	   "your enormous obsidian battleaxe!\n");
	tell_watcher(QCTNAME(me)+" cuts deeply into "+QTNAME(enemy)+"'s "+
	hdesc+" with "+HIS_HER(me)+" enormous obsidian battleaxe!\n");
	enemy->catch_tell(QCTENEMY+" cuts deeply into your "+hdesc+" with "+
	    HIS_HER(me)+" enormous obsidian battleaxe!\n");
	break;               
      case 36..70:
	switch(hdesc)
	{
	  case "head":
	      me->catch_tell(QCTME+"'s feeble attempt to parry succeeds in "+
		  "in turning the blade of the enormous obsidian "+
		  "battleaxe away from "+HIS_HER(enemy)+ "head, but it "+
		  "still strikes side-on with terribly concussive "+
		  "force!\n");
tell_watcher(QCTNAME(enemy)+" feeble attempts to parry "+
		  "succeed in turning the blade of "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe away from "+HIS_HER(enemy)+
		  " head, but it still strikes side-on with terrible "+
		  "concussive force!\n");
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
	tell_watcher("The blade of "+QTNAME(me)+"'s enormous "+
		  "obsidian battleaxe travels in a graceful arc which "+
		  "culminates with it being embedded nearly an "+
		  "inch deep in "+QTNAME(enemy)+"'s ribcage!\n");
	      enemy->catch_tell("The balde of "+QTENEMY+"'s enormous "+
		  "obsidian battleaxe travels in a graceful arc which "+
		  "culminates with it being embedded nearly an inch deep "+
		  "into your ribcage!\n");
	      break;
	  case "left arm":
	      me->catch_tell("A sidelong strike from your enormous "+
		  "obsidian battleaxe removes a large chunk of flesh "+
		  "from "+QTME+"'s left arm!\n");
	tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s left arm!\n");
	      enemy->catch_tell("A sidelong strike from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from your left arm!\n");
	      break;
	  case "right arm":
	      me->catch_tell("A sidelong strike from your enormous "+
		  "obsidian battleaxe removes a large chunk of flesh "+
		  "from "+QTME+"'s right arm!\n");
	tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s right arm!\n");
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
	tell_watcher("A sidelong strike from "+QTNAME(me)+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from "+QTME+"'s "+leg+" leg!\n");
	      enemy->catch_tell("A sidelong strike from "+QTENEMY+"'s "+
		  "enormous obsidian battleaxe removes a large chunk "+
		  "of flesh from your "+leg+" leg!\n");
	      break;
	default:
	      me->catch_tell("You strike "+QTME+" with a tremendous blow "+
		  "from your enormous obsidian battleaxe!\n");
	tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+
	    "with a tremendous blow from "+HIS_HER(me)+" enormous "+
		  "obsidian battleaxe!\n");
	      enemy->catch_tell("You are struck by a tremendous blow "+
		  "from "+QTENEMY+"'s enormous obsidian battleaxe!\n");
	      break;
	}
     default:    
	switch (hdesc)
	{  
	  case "head":
	      me->catch_tell("You strike "+QTME+"'s head with a powerful "+
		  "blow from your enormous obsidian battleaxe. You are "+
		  "amazed that "+HE_SHE(enemy)+" is still standing!\n");
	tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+"'s "+
		  "head with a powerful blow from the enormous obsidian "+
		  "battleaxe! You are amazed that "+HE_SHE(enemy)+" is "+
		  "still standing!\n");
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
	tell_watcher(QCTNAME(me)+" slices open "+QTNAME(enemy)+
		  "'s belly with "+HIS_HER(me)+" enormous obsidian "+
		  "battleaxe! "+QCTNAME(enemy)+" clings to life, and "+
		  HIS_HER(enemy)+" guts by the barest of margins!\n");
	      enemy->catch_tell(QCTENEMY+" slices open your belly with "+
		  HIS_HER(me)+" enormous obsidian battleaxe! You cling "+
		  "to your life, and your guts by the barest of margins!\n");
	      break;
	  case "right arm":
	      me->catch_tell("You chop "+QTME+"'s "+hdesc+" to the "+
		  "bone, nearly lopping it off!\n");
	tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  hdesc+" to the bone, nearly lopping it off!\n");
	  enemy->catch_tell(QCTENEMY+" chops your "+hdesc+" "+
		 "to the bone, nearly lopping it off!\n");
	      break;
	  case "left arm":
	      me->catch_tell("You chop "+QTME+"'s "+hdesc+" right into the "+
		  "bone, nearly lopping it off!\n");
	tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  hdesc+" right into the bone, nearly lopping it off!\n");
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
	tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"s "+
		  leg+" leg to the bone, nearly lopping it off!\n");
	      enemy->catch_tell(QCTENEMY+" chops your "+leg+" leg "+
		 "to the bone, nearly lopping it off!\n");
	      break;
	  default:
	      me->catch_tell("You deal "+QTME+" a near mortal blow with "+
		  "your enormous obsidian battleaxe!\n");
	      me->tell_watcher(QCTNAME(me)+" deals "+QTNAME(enemy)+" a "+
		  "a near mortal blow with "+HIS_HER(me)+" enormous "+
		  "obsdian battleaxe!\n");
	      enemy->catch_msg(QCTENEMY+" deals you a near mortal blow "+
		  "with "+HIS_HER(me)+" enormous obsidian battleaxe!\n");
	      break;
	}
    }
    return 1;
}

mixed
query_magic_protection(string prop, object what)
{
    query_wielded()->catch_msg("QUery_magic_protection has been called!");
    if ((what==(TO->query_wielded())) & (prop == "MAGIC_I_RES_POISON"))
    {
        return({20,1});
    }
    return ::query_magic_protection(prop, what);
} 

mixed
wield(object to)
{
    if(STR(TP)<80)
    {
	return("You try to wield the enormous obsidian battleaxe, but lack "+
	    "the strength needed to make effective use of such a heavy "+
	    "weapon.\n");
    }
    else
    { 
	ENV(TO)->add_magic_effect(TO);  
	TP->catch_msg("As you grasp the handle of enormous obsidian "+ 
	    "battleaxe firmly in both hands, an odd feeling comes over "+
	    "you. You almost get the impression that the weapon is "+
	    "somehow trying to protect you from harm.\n");
	return 0;
    }
}

mixed
unwield(object to)
{
    ENV(TO)->remove_magic_effect(TO);
    return 1;
}  
