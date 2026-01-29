/*
 * glad_soul.c    Coded by Mylos 6.8.93
 * 
 */

inherit "/cmd/std/command_driver";

#include "guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include "combat.h"

#define tpro this_player()->query_pronoun()
#define tpos this_player()->query_possessive()
#define GLAD_I_CHARGED "glad_i_charged"

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "gladiator";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
   return ([
/*
		"berserk" : "berserk",
		"gchallenge" : "gchallenge",
		"charge" : "charge",
		"crouch" : "crouch",
		"dare" : "dare",
		"defy" : "defy",
		"dust" : "dust",
		"eye" : "eye",
		"gadjust" : "gadjust",
		"gbite" : "gbite",
		"glaugh" : "glaugh",
		"glook" : "glook",
		"grage" : "grage",
		"gshake" : "gshake",
		"gspit" : "gspit",
                "hear" : "hear",
		"roar" : "roar",
		"salute" : "salute",
		"sign" : "sign",
		"stance" : "stance",
		"tooth" : "tooth",
*/
           ]);
}

void
create()
{
    seteuid(getuid());
}

int
gchallenge(string str)
{
	object *oblist;

	notify_fail("Challenge whom?\n");
	if(!strlen(str))
	    return 0;

	oblist = parse_this(str, "%l");
	if(!sizeof(oblist))
	    return 0;

	target(" challenges you to combat with bloodlust "+
	   "in "+tpos+" eye.", oblist);
	actor("You challenge", oblist," to combat with bloodlust "+
	   "in your eye.");
	all2act(" challenges", oblist," to combat with bloodlust "+
	   "in "+tpos+" eye.");
	return 1;
}

int
crouch(string str)
{
   object *oblist;

   if(!strlen(str))
   {
        write("You jump into a fighting crouch.\n");
        allbb(" jumps into a fighting crouch.");
        return 1;
   }
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;

   targetbb(" jumps into a fighting crouch in front of you.", oblist);
   actor("You jump into a fighting crouch in front of", oblist);
   all2actbb(" jumps into a fighting crouch in front of", oblist);
   return 1;
}

int
dare(string str)
{
   object *oblist;
   if(!strlen(str))
   {
      write("You trace a line on the ground in front of you and "+
	"dare anyone to cross it.\n");
	allbb(" traces a line on the ground before "+
	   TP->query_objective()+" and "+
	"dares anyone to cross it.\n");
	return 1;
   }
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
      return 0;

	targetbb(" traces a line in the ground before you and "+
     "dares you to cross it.", oblist);
	actor("You trace a line on the ground in front of you "+
	   "and dare",oblist," to cross it.");
	all2actbb(" traces a line on the ground before "+
	   TP->query_objective()+" and "+
     "dares", oblist, " to step across it.");
     return 1;
}

int
defy(string str)
{
	object *oblist;

	notify_fail("Defy whom?\n");
	if(!strlen(str))
	return 0;

	oblist = parse_this(str, "%l");
	if(!sizeof(oblist))
	   return 0;

	target(" stands toe to toe with you in utter "+
	   "defiance.", oblist);
	actor("You stand toe to toe with", oblist, " in "+
	   "utter defiance.");
	all2actbb(" stands toe to toe with", oblist, " in "+
	   "utter defiance.");
	return 1;
}

int
dust(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	write("You shake more Athasian dust from your boots.\n");
	allbb(" shakes more Athasian dust from "+tpos+" boots.");
	  return 1;
	}
}

int
eye(string str)
{
   object *oblist;

   
   notify_fail("Eye up whom?\n");
   if(!strlen(str))
        return 0;

   oblist = parse_this(str, "[up] %l");
   if(!sizeof(oblist))
        return 0;

   targetbb(" eyes you up as a possible adversary.", oblist);
   actor("You eye up", oblist," as a possible adversary.");
   all2actbb(" eyes up", oblist," as a possible adversary.");
   return 1;
}

int
gadjust(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	write("You adjust your armour, in preparation for battle.\n");
	  allbb(" adjusts "+tpos+" armour, in preparation for battle.");
	  return 1;
	}
}

int
gbite(string str)
{
	object *oblist;

	if(!strlen(str))
	{
	  write("You bite your tongue until blood runs "+
	     "down your chin.\n");
	  allbb(" bites "+tpos+" tongue until blood runs "+
	   "down "+tpos+" chin.");
	return 1;
	}
}

int
glaugh(string str)
{
	object *oblist;

	notify_fail("Laugh at whom?\n");
	if(!strlen(str))
	{
	write("You roll your head back and roar with laughter.\n");
	  all(" rolls "+tpos+" head back and roars with "+
	     "laughter.");
	  return 1;
	}

	oblist = parse_this(str, "[at] %l");
	if(!sizeof(oblist))
	    return 0;
	target(" rolls "+tpos+" head back and roars with "+
	    "laughter at you.", oblist);
	actor("You laugh at", oblist);
	all2act(" rolls "+tpos+" head back and roars with "+
	    "laughter at", oblist);
	   return 1;
}

int
glook(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	write("You make a quick scan of the area, searching "+
	   "for your next victim.\n");
	  allbb(" makes a quick scan of the area, searching "+
	     "for "+tpos+" next victim.");
	  return 1;
	}
}

int
grage(string str)
{
        object *oblist;
        string his_her;

        notify_fail("Rage at whom?\n");
        if(!strlen(str))
                return 0;

        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;

        his_her = oblist[0]->query_possessive();
        targetbb(" looks at you with absolute rage on "+tpos+" face.", oblist);
        actor("You look with rage at", oblist);
        all2actbb(" looks with rage at", oblist);
        return 1;
}

int
gshake(string str)
{
   object *oblist;

   if (!strlen(str))
   {
      write("You shake your hands, making the blood of your last "+
	    "kill splatter over everything.\n");
      allbb(" shakes "+tpos+" hands and splatters the blood from "+
	    tpos+" last kill all over.\n");
      return 1;
   }

   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
      return 0;

    if (sizeof(oblist) == 1)
    {
        actor("As you shake hands with", oblist, ", you drip blood from " +
            "your last kill on " + oblist[0]->query_objective() + ".");
        all2actbb(" shakes hands with", oblist, ", dripping blood from " +
            tpos + " last kill on " + oblist[0]->query_objective() + ".");
    }
    else
    {
        actor("As you shake hands with", oblist, ", you drip " +
            "blood from your last kill on them.");
        all2actbb(" shakes hands with", oblist, " dripping blood from " +
            tpos + " last kill on them.");
    }
   target(" shakes your hand, dripping blood from "+tpos+" last "+
	  "kill onto you.", oblist);
   return 1;
}

int
gspit(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	write("You spit out mud from the dust of Athas.\n");
	  allbb(" spits out mud from the dust of Athas.");
	  return 1;
	}
}

int
hear(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	 write("You close your eyes and listen pleasantly "+
	    "to your favorite sound: death.\n");
	 allbb(" closes "+tpos+" eyes and gets a pleasant smile "+
	    "on "+tpos+" face as "+tpro+" quietly "+
	    "listens to the glorious sounds of death.");
	 return 1;
	}
}
int
roar(string str)
{
   object *oblist;

   if(!strlen(str))
   {
        write("You roar loudly in anger.\n");
        all(" roars loudly in anger.");
        return 1;
   }

   oblist = parse_this(str, "[at] %l");
   if(!sizeof(oblist))
        return 0;
   target(" roars loudly at you in anger.", oblist);
   actor("You roar loudly at", oblist);
   all2act(" roars loudly at", oblist);
   return 1;
}

int
salute(string str)
{
        object *oblist;
        string him_her;

        if(!strlen(str))
        {
	     write("You salute all in the room.\n");
                allbb(" salutes everyone in the room.");
                return 1;
        }

        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;

        him_her = oblist[0]->query_objective();
        targetbb(" salutes you as "+tpro+" prepares to dismember you.", oblist);
        actor("You salute",oblist," as you prepare to dismember "+him_her+".");
        all2actbb(" salutes", oblist," as "+tpro+" prepares to "+
        "dismember "+him_her+".");
        return 1;
}

int
sign(string str)
{
   object *oblist;


	notify_fail("Sign whom?\n");
   if(!strlen(str))
        return 0;

   oblist = parse_this(str, "[at] %l");
   if(!sizeof(oblist))
        return 0;
   targetbb(" salutes you as a brave and worthy opponent.", oblist);
   actor("You salute", oblist," as a brave and worthy opponent.");
   all2actbb(" salutes", oblist," as a brave and worthy opponent.");
   return 1;
}

int
stance(string str)
{
   object *oblist;

   notify_fail("Stance whom?\n");
   if(!strlen(str))
        return 0;
   
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;

   targetbb(" carefully assumes a professional stance in front of you.", oblist);
   actor("You assume a professional stance in front of", oblist);
   all2actbb(" carefully assumes a professional stance in front of", oblist);
   return 1;
}

int
tooth(string str)
{
	object *oblist;
	if(!strlen(str))
	{
	write("You spit out another tooth.\n");
	  all(" spits out another tooth.");
	  return 1;
	}
}


/********************* charge *******************************************/
int
charge(string str)
{
   object ob, *obj;
   mixed *hitresult;
   string how;

   seteuid(getuid());

   if (!str)
    {
      ob = TP->query_attack();
      NF("Charge whom?\n");
      if (!ob)
        return 0;
    }

   else 
   {
      obj = parse_this(str, "%l");
      if (sizeof(obj) > 0)
         ob = obj[0];
      if (sizeof(obj) > 1)
      {
         NF("Choose one victim to charge.\n");
         return 0;
      }
   }
   /* so I want to attack ob, may I do that? */
   how = c_can_attack(ob, query_verb());
   if (stringp(how))
   {
      NF(how);
      return 0;
   }

   {
     /* check my charge status, may I do one now ? */      
      if (TP->query_prop(GLAD_I_IS_CHARGE) == 1)
         write("You can't do a charge now.\n");
      else if (TP->query_prop(GLAD_I_IS_CHARGE) > 1)
         write("You are already preparing a charge.\n");
      else
      {
         TP->add_prop(GLAD_I_IS_CHARGE, 3);
         call_out("charge_ob", 3, ({ ob, TP }));
         TP->catch_msg("You get yourself ready for a charge.\n");
      }  
      return 1;
   }
   write("You cannot charge, you are already attacking that victim.\n");
   return 1;
}

void
charge_ob(object *ob)
{
   string how;

   set_this_player(ob[1]);
   how = c_can_attack(ob[0], "charge");
   /* recheck that we may attack */
   if (stringp(how))
   {
      write("You are unable to charge that person.\n");
      TP->remove_prop(GLAD_I_IS_CHARGE);
      return;
   }

	call_out("allow_charge", MIN(100, ((125)-(TP->query_skill(SS_CHARGE)))),
	  TP);

/* Are we still in the same room ? */
   if (ob[0] && environment(TP) != environment(ob[0]))
      return;

   set_alarm(2.0,0.0,"spell_attack",TP,ob[0]);

/* Start fighting */
   TP->attack_object(ob[0]);
   TP->add_prop(GLAD_I_IS_CHARGE, 2);
}

void
allow_charge(object ob) 
{ 
	tell_object(ob , "\nYou feel ready to charge again.\n\n");
   ob->remove_prop(GLAD_I_IS_CHARGE);
}

/********************* berserk *******************************************/
int
berserk()
{
    if (TP->query_prop(GLAD_I_IS_BERSERK) == 1)
        write("You are foaming at the mouth as it is.\n");
    else
    {
        TP->add_prop(GLAD_I_IS_BERSERK, 1);
        call_out("do_berserk", 5, TP);
	    TP->catch_msg("Your breathing becomes heavier.\n");
	    say(QCTNAME(TP)+" breaks out in a sweat as "+TP->query_possessive()+" breath becomes heavier.\n", TP);
    }  
    return 1;
}

void
do_berserk(object ob)
{
    int str, dis, con, skill, time, old_hp, old_maxhp, new_hp, new_maxhp;

    skill = ob->query_skill(SS_BERSERK);
    time = 25 + skill/4;  /* time between 25 and 50 seconds */
    str = ob->query_base_stat(SS_STR)/7;
    dis = ob->query_base_stat(SS_DIS)/7;
    /* con bonus is skill dependant */  
    con = ob->query_base_stat(SS_CON) * (5 + skill/ 10) / 100;
 
    /* let the mudlib take care of str and dis */
    ob->add_tmp_stat(SS_STR, str, time/20);
    ob->add_tmp_stat(SS_DIS, dis, time/20);

    old_maxhp = ob->query_max_hp();
    if (old_maxhp == 0) old_maxhp = 1; /*to avoid division by zero */

    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,con+ob->query_stat_extra(SS_CON));
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);
    
    call_out("expire_berserk", time, ({ob, con}));
    ob->catch_msg("You start slavering at the mouth.\n");
	say(QCTNAME(ob) + " works "+ob->query_objective()+"self"+
	   " into a wild battle rage.\n", ob);
}

void
expire_berserk(mixed arg)
{
    object ob;
    int con, old_hp, old_maxhp, new_hp, new_maxhp;

    ob = arg[0]; con = arg[1];

    if (!objectp(ob)) return;

    old_maxhp = ob->query_max_hp();
    if (old_maxhp == 0) old_maxhp = 1; /*to avoid division by zero */
    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,ob->query_stat_extra(SS_CON)-con);
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);
    
	 ob->add_fatigue(-(SS_CON/2));

    call_out("allow_berserk", MAX(10, 25 - ob->query_skill(SS_BERSERK)/6), ob);
    ob->catch_message("You begin to calm down and return to a normal frame "+
       "of mind.\n");
    tell_room(environment(ob), QCTNAME(ob) + " seems to have returned to "+
	      "a normal frame of mind.\n", ob);
}

void
allow_berserk(object ob) 
{ 
    tell_object(ob, "\nYou can now enter a berserked state again.\n\n");
    ob->remove_prop(GLAD_I_IS_BERSERK);
}

/*************************** Special attacks end up here ****************/

void
spell_attack(object attacker, object target)
{
    object *items, allow;
    string how;
    mixed *hitresult;
    int i, skill, str, dis;

    if (!target || !attacker || environment(attacker) != environment(target))
	return;

 if (attacker->query_prop(GLAD_I_IS_CHARGE) == 2)
    {
        attacker->add_prop(GLAD_I_IS_CHARGE, 1);
        if (random(F_CHARGE_HIT(attacker, target)) > random(CHARGE_HIT))
        {
            hitresult = target->hit_me(F_CHARGE_PEN(attacker, target),
				       W_BLUDGEON, attacker, -1);
	    how = "amused by such a feeble attack";

            if (hitresult[0] > 0)
                how = "dazed";
            if (hitresult[0] > 15)
                how = "injured";
            if (hitresult[0] > 30)
                how = "hurt";
            if (hitresult[0] > 50)
                how = "severely hurt";
            if (hitresult[0] > 75)
                how = "on the verge of collapse";

            if (target->query_hp() > 0)
            {
              attacker->catch_msg("You charge into " + QTNAME(target) +
                  ".\n");
              attacker->catch_msg(QCTNAME(target) + " looks " + how + ".\n");

              target->catch_msg(QCTNAME(attacker) +
                  " charges headlong into you.\n");
              target->catch_msg("You feel " + how + ".\n");

              tell_watcher(QCTNAME(attacker) + " charges into "+ QTNAME(target)+ 
                  " with a brave attack.\n", attacker, target);
            }
            else  
            {
	       attacker->catch_msg("Bones break and blood splatters as you "+
	          "run full force into " + QTNAME(target) + ", throwing " +
	          target->query_objective() + " to the ground in a bloody, "+
	          "lifeless heap.\n");

	       tell_watcher(QCTNAME(target) + " lets out a final shriek in "+
                  "horrible agony and falls lifelessly to the "+
	          "ground at the feet of " + QTNAME(attacker) + "\n",
                  attacker, target);

               target->do_die(attacker);
            }              
            return;
        }

        attacker->add_attack_delay(5,0);
        target->hit_me(0, W_BLUDGEON, attacker, -1);
        attacker->catch_msg("You try to charge into " + QTNAME(target) +
            " but miss completely.\nYou run past "+
                target->query_objective()+".\n");
        target->catch_msg(QCTNAME(attacker) +
            " tries to charge into you.\n" + 
                C(attacker->query_pronoun()) + " runs past you.\n");
        tell_watcher(QCTNAME(attacker) + " tries to charge " + QTNAME(target) +
            " but runs past as "+attacker->query_pronoun()+
                " misses.\n", attacker, target);
        return;
    }
}
