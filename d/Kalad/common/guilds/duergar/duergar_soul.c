/*
* The soul of the duergar race guild
* Made by Korat
* August - December 1996
*/

#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/duergar/default.h"
#include <cmdparse.h>
#include <filter_funs.h>
#define HELP_FILE "BLAH"
#define MORE_OBJ "BLAH"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Duergar"; }

public int kicking=0;

public mapping
query_cmdlist()
{
   return ([
#include "dcommands.h"
          ]);
}

/**********************
 *
 * General emotes:
 *
 **********************/
public int
e_dslice(string arg)
{
   object *oblist;
   object weapon;
   
   NF("Dslice with what? You are not wielding anything.\n");
   weapon = TP->query_wielded(W_RIGHT);
   if (!objectp(weapon))
      weapon = TP->query_wielded(W_LEFT);
   if (!objectp(weapon))
      weapon = TP->query_wielded(W_BOTH);
   if (!objectp(weapon))
      return 0;
   
   if (!strlen(arg))
      {
      allbb(" slices the air with his "+weapon->query_short());
      write("You slice the air with your "+weapon->query_short()+".\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You slice the air with your "+weapon->query_short()+
      ", just in front of", oblist, ".");
   all2actbb(" slices the air with "+TP->query_possessive()+" "+weapon->query_short()+
      ", just in front of", oblist, ".");
   targetbb(" slices the air with "+TP->query_possessive()+" "+weapon->query_short()+
      ", inches in front of your face.", oblist);
   return 1;
}

public int
e_dplant(string arg)
{
   object *oblist;
   NF("Dplant at who?\n");
   
   if (!strlen(arg))
      {
      all(" plants the feet on the ground, taking a stand.");
      write("You plant your feet on the ground, taking a stand.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You plant your feet on the ground, taking a stand against", oblist);
   all2act("  plants "+TP->query_possessive()+" feet on the ground, taking "+
      "a stand against", oblist);
   target(" plants "+TP->query_possessive()+" feet on the ground, taking "+
      "a stand against you.", oblist);
   return 1;
}

public int
e_drespect(string arg)
{
   object *oblist;
   
   NF("Drespect who?\n");
   if (!strlen(arg))
      return 0;
   
   oblist = parse_this(arg, "[the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You give a short bow to", oblist, " showing your respect towards "+
      "another worthy fighter.");
   all2actbb(" gives a short bow at", oblist, " showing respect towards another "+
      "worthy fighter.");
   targetbb(" gives a short bow towards you, "+
      "granting you the respect that a worthy fighter deserves.", oblist);
   return 1;
}

public int
e_dlust(string arg)
{
   object *oblist;
   NF("Dlust at whom?\n");
   if(!strlen(arg))
      {
      allbb(" lust for blood seems to seize control over "+TP->query_objective()+".");
      write("You almost loose control through your lust for blood.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   actor("You almost loose control through your lust for the blood of", oblist,
      ".");
   tell_room(E(TP),"The lust for "+QTNAME(oblist[0])+" seems to seize control "+
      "over "+QTNAME(TP)+".\n",oblist[0]);
   oblist[0]->catch_msg("The lust for your blood seems to seize control over "+
      QTNAME(TP)+".\n");
   return 1;
}

public int
e_dpush(string arg)
{
   object *oblist;
   NF("Dpush to get in front of who?\n");
   if(!strlen(arg))
      {
      allbb(" pushes you away to be the first to strike at any enemy.");
      write("You push at everyone to be the first to strike at any enemy.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You push away everyone to make sure it is you that will "+
      "take any damage from", oblist);
   all2actbb(" pushes you away, preparing to take any damage from", oblist);
   targetbb(" pushes everyone away to make sure it is "+TP->query_objective()+
      " that will be the first to strike at you. The vicious gleam in "+
      TP->query_objective()+" eyes does "+
      "not make you happy.", oblist);
   return 1;
}

public int
e_dhelp(string arg)
{
   object *oblist;
   NF("Get Dhelp against whom?\n");
   if(!strlen(arg))
      {
      tell_room(E(TP),"In panic, the beaten "+QTNAME(TP)+"'s eyes searches "+
         "for help.\n");
      write("In panic, you search around with your eyes for help.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("In panic, your eyes search for help against", oblist,".");
   all2actbb(" eyes searches in panic for help against", oblist, ".");
   targetbb(" eyes searches in panic for help against you.", oblist);
   return 1;
}

public int
e_drage(string arg)
{
   object *oblist;
   NF("Drage at whom?\n");
   if(!strlen(arg))
      {
      allbb(" seems to loose control in pure rage!");
      write("You loose control in pure rage!\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You turn slowly to face", oblist, ", with rage flowing in your veins.");
   all2actbb(" turns slowly to face", oblist, ". "+C(TP->query_pronoun())+
      " seems to be loosing control over "+TP->query_objective()+"self in pure rage!");
   targetbb(" turns slowly to face you. "+TP->query_pronoun()+" seems to loose "+
      "control over "+TP->query_pronoun()+"self in pure rage!", oblist);
   return 1;
}

public int
e_dfury(string arg)
{
   object *oblist;
   NF("Dfury at whom?\n");
   if(!strlen(arg))
      {
      allbb(" screams aloud in fury.");
      write("You scream aloud in fury.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You scream aloud in fury, cursing the very existance of", oblist, ".");
   all2actbb("  screams aloud in fury, cursing the very existance of", oblist, ".");
   targetbb(" screams aloud in fury, cursing your very existance.", oblist);
   return 1;
}

public int
e_dforget(string arg)
{
   object *oblist;
   NF("Dforget who?\n");
   if(!strlen(arg))
      {
      allbb(" seems to forget that you even exist.");
      write("With surprise you notice that you still are not alone.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You make sure", oblist, " understands that you wish "+oblist[0]->query_objective()+
      " to vanish. Hopefully for ever.");
   all2actbb(" makes sure", oblist, " understands that "+TP->query_pronoun()+" wants "+
      oblist[0]->query_objective()+" to vanish. Hopefully for ever.");
   targetbb(" seems to forget that you even exist.", oblist);
   return 1;
}

public int
e_dprotect(string arg)
{
   object *oblist;
   object *dummy;
   NF("Dprotect what or who?\n");
   if(!strlen(arg))
      {
      allbb(" warns you from touching anything in "+TP->query_possessive()+
         " possession.");
      write("You warn everyone from touching anything of yours.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %o");
   if(!sizeof(oblist))
      return 0;

   actor("You walk over to", oblist, ", turn around and protectively"+
      "prepare for the first strike.");
   all2actbb(" walks over to", oblist, ", turns around and "+
      "protectively prepares "+TP->query_objective()+
      "self for the first strike.");

   dummy = FILTER_LIVE(oblist);
   if(sizeof(dummy))
      targetbb(" walks over to you, turns around and prepares to "+
         "defend you from anyone.", oblist);
   return 1;
}

public int
e_dgreet(string arg)
{
   object *oblist;
   object weapon;
   string with_what;
   
   weapon = TP->query_wielded(W_RIGHT);
   if (!objectp(weapon))
      weapon = TP->query_wielded(W_LEFT);
   if (!objectp(weapon))
      weapon = TP->query_wielded(W_BOTH);
   if (!objectp(weapon))
      with_what = "clenched fist";
   else
      with_what = weapon->query_short();
   
   NF("Dgreet who?\n");
   if(!strlen(arg))
      {
      allbb(" lifts "+TP->query_possessive()+" "+with_what+" into the air in greeting.");
      write("You lift your "+with_what+" into the air in greeting.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You punch the shoulder of", oblist, " with "+TP->query_possessive()+
      " "+with_what+" in a friendly way.");
   all2actbb(" punches the shoulder of", oblist, " with "+TP->query_possessive()+
      " "+with_what+" in a friendly way.");
   targetbb(" punches your shoulder in a friendly way with "+TP->query_possessive()+
      " "+with_what+".", oblist);
   return 1;
}

public int
e_dgreed(string arg)
{
   object *oblist;
   NF("Dgreed at whom?\n");
   if(!strlen(arg))
      {
      allbb(" peers around with greedy, lust-filled eyes..");
      write("You peer around with greedy, lust-filled eyes.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You study the possessions of", oblist, " with greedy, lust-filled eyes.");
   all2actbb(" studies the possessions of", oblist, " with greedy, lust-filled eyes.");
   targetbb(" studies your possessions with greedy, lust-filled eyes.", oblist);
   return 1;
}

public int
e_dsmile(string arg)
{
   object *oblist;
   NF("Dsmile at who [how]?\n");
   if(!strlen(arg))
      {
      allbb(" smiles at you with the eyes gleaming like sunshine on pure gold.");
      write("You smile with your eyes gleaming like sunshine on pure gold.\n");
      return 1;
   }
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if(!sizeof(oblist))
      return 0;
   actor("You smile broadly at", oblist, " with the pleasure of seeing "+
      oblist[0]->query_possessive()+" in good health visible on your face.");
   all2actbb(" smiles broadly at", oblist, " with "+TP->query_possessive()+
      "eyes revealing the pelasure of seeing "+oblist[0]->query_possessive()+
      " in good health.");
   targetbb(" smiles broadly at you with the eyes revealing pleasure of seeing you "+
      "in good health.", oblist);
   return 1;
}

public int
e_dgrin(string arg)
{
   object *oblist;
   
   NF("Dgrin at whom?\n");
   
   if (!strlen(arg))
      {
      allbb(" grins insanely, showing off the true nature of his Duergar roots.");
      write("You grin insanely, marking yourself as a Duergar.\n");
      return 1;
   }
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (!sizeof(oblist))
      return 0;
   
   actor("You grin insanely at ", oblist, ", as only a Duergar could.");
   all2actbb(" grins insanely at ", oblist, ", as only a Duergar can.");
   targetbb(" grins insanely at you, as only a Duergar can.", oblist);
   return 1;
}

int
e_dcackle(string what)
{
   object *a,ob;
   NF("Dcackle what?\n");
   if(!strlen(what))
      return 0;
   write("You cackle: "+what+"\n");
   say(QCTNAME(TP)+" cackles: "+what+"\n");
   return 1;
}


/**************************
 * Other special emotes:
 **************************/


/* Return the title */

public string
q_title(object ob, int wiz)
{
   if (!ob->query_guild_member("Duergar dwarven race guild"))
      return 0;
   if (!wiz && ob->query_wiz_level())
      return 0;
   if (wiz && !ob->query_wiz_level())
      return 0;
   if (extract(ob->query_name(), -2) == "jr")
      return 0;
   return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
      "\n    ");
}

/* List members logged on */

public int
e_dlist(string arg)
{
   int i;
   i = (query_verb() == "mwlist" ? 1 : 0);
   write("After listening to the panicstricken rumours, you think the "+
      "following duergars are currently roaming around in this world:\n\n"+
      implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
         "\n") + "\n");
   return 1;
}

/*  Function: e_dsay()
 *  Description: The raceguilds special language
 *  Arguments: arg - what the player wants to say
/*
public int
e_dsay(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the Duergar jargon?\n");
      return 0;
   }
   
   if(TP->query_skill(SS_LANGUAGE) < 10)
      {
      NF("You haven't learned the rough language used by the duergars "+
         "well enough yet.\n");
      return 0;
   }
   
   if (this_player()->query_get_echo())
      write("In the duergar jargon, you utter: " + arg + "\n");
   else
      write("Ok.\n");
   
   /* Tell others what we said */
   filter(all_inventory(environment(this_player())) - ({ this_player() }),
      "do_say", this_object(), arg);
   return 1;
}

/*
* Function name: do_say
* Description:   This function is called each time the player talks in the guilds special language
* Arguments:     who  -  who we want to speak to 
*                arg  - what we want to say
*/
public int
do_say(object who, string arg)
{
   int i;
   string text;
   string dummy;
   
   /* only speak to livings */
   if (!living(who))
      return 0;

   /* check if we want to give <arg> unscrambled to 'who' */
   if ((IS_MEMBER(who) || who->query_skill(SS_LANGUAGE) > 70)
   {
      tell_object(who, this_player()->query_The_name(who) + " growls " +
         "in the Duergar jargon: " + arg + "\n");
      return 1;
   }

   /* Check if we want to totally scramble what we say */
   if(who->query_skill(SS_LANGUAGE) < 30)
      {   
      tell_object(who, this_player()->query_The_name(who) + " growls " +
         "some harsh sounds. You find it utterly uncomprehensable.\n");
      return 1;
   }
   
   /* We will now scramble the text, 'arg', according to language skill */
   /* remove vocals from arg according to ss_language skill */
   text="";
   for (i=0; i<strlen(arg); i++)
   {
      dummy=extract(arg,i,i);
      if(dummy != "a" && dummy !="e" && dummy != "i" &&
         dummy != "o" && dummy != "u" && dummy !="s" && dummy != "y")
      {
         text=text+dummy;
      }
      else
      {
         if (random(who->query_skill(SS_LANGUAGE) - 20) > 25)
            text=text+dummy;
         else
            switch(random(4))
         {
            case 0: text=text+"x"; break;
            case 1: text=text+"r"; break;
            case 2: text=text+"gh"; break;
            case 3: text=text+"z"; break;
            default: text=text+"r"; break;
         }
      }
   }

   /* give the output to 'who' */
   tell_object(who, this_player()->query_The_name(who) + " growls "+
      "something in the Duergar jargon: "+
      text+".\n");
}

/*
* Function name: e_dkick
* Description:   A very small combat-kick. It will initiate combat, but will
*                not do much damage. Hitpen as a found weapon. It is also a
*                emote, and the player can kick corpses and weapons/armours.
* Arguments:     arg - what to kick
*/
public int
e_dkick(string arg)
{
   object *oblist, *oblive, *obdead;
   int result;
   object ob, *obj;
   mixed *hitresult;
   string str;
   string how;
   string what;
   string *name;
   int i;
   
   if (!strlen(arg))
      {
      allbb(" kicks the ground hard, in pure rage!");
      write("You kick the ground hard in pure rage!\n");
      return 1;
   }
   if(arg=="all")
      {
      write("You kick at everything in sight, making a havvock!\n");
      allbb(" kicks at everything in sight, looking utterly mad!");
      return 1;
   }
   
   NF("But you are already preparing a kick!\n");
   if(kicking) return 0;

   NF("Dkick at whom/what?\n");
   
   /* Lets check if the player kicks someone. If so we will make an attempt
    * to do damage and then initiate combat.
   */
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (sizeof(oblist))
      {
      if(LIVING(oblist[0])) set_alarm(0.0,0.0,"do_kick",oblist[0], TP);
      return 1;
   }
   
   /* The player kicks at something. This can be weapons, armours or
   * corpses. We test the first object to find out. 
   */
   
   if(!parse_command(arg,all_inventory(E(TP)), "[at] / [to] / [toward] [the] %s",what))
      return 0;
   if(!sizeof(obdead=FIND_STR_IN_OBJECT(what,E(TP))))
      return 0;
   if(sizeof(obdead)>1)
      {
      NF("Be more specific, please.\n");
      return 0;
   }
   
   /* is the object a weapon or an armour ? */
   if((function_exists("create_object", obdead[0]) == "/std/weapon") ||
      (function_exists("create_object", obdead[0]) == "/std/armour"))
   {
      result = TP->query_base_stat(SS_STR) / 4

      /* we deal with max 120 in strength! */
      if (result > 30) result = 30;

      /* we get the kilos the item weights and subtract it from the strenght*/ 
      result = result - (obdead[0]->query_prop(OBJ_I_WEIGHT)/1000));

      if(result<0)
         {
         str="but it is so heavy that it doesn't move an inch!";
         write("Your toes really hurts from the impact, but being a duergar "+
            "you manage to make your face of pain look like a grin of "+
            "extreme cruelty. The " + obdead[0]->short() + 
            " doesn't move an inch though!\n");
      }

      /* result is between 0 and 30 */
      switch (result)
      {
      case 0..3: str="with the result that it moves an inch.";break;
      case 4..7: str="making it turn around twize.";break;
      case 8..15: str="making it roll around on the ground.";break;
      case 16..19: str="making it almost shatter upon the impact.";break;
      case 20..25: str="and watches it whirl away.";break;
      default: str="and sends it flying!";break;
      }

      /* Not much of an effect to kick something broken */
      if(obdead[0]->query_prop(OBJ_I_BROKEN))
         str="just to make sure it stays broken.";

      if(result >= 0)
      {
         write("You kick hard into the "+obdead[0]->short()+
               " in pure rage, "+str+"\n");
         allbb(" kicks hard into the "+ obdead[0]->short() +
               " on the ground in pure rage, "+str);
      }

      /* This treatment of the weapon/armour will damage it. */
      if(obdead[0]->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
         obdead[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
      {
         /* magical items is harder to break */
         result=result / 6; // varies between 0 and 5
      }
      else
      {
         /* nonmagical items breaks easier */
         result=result / 3; // varies between 0 and 10
      }

      /* We add damage to the object */
      if(!obdead[0]->query_prop(OBJ_I_BROKEN))
         {
         obdead[0]->set_dull(obdead[0]->query_dull()+result);
         set_alarm(1.0,0.0,"check_broken",obdead[0]); // we have to manually break the item
      }
      return 1;
   }
   
   /* kicking a corpse? */
   
   if(obdead[0]->query_name()=="corpse")
      {
      name=obdead[0]->query_names();
      write("You kick hard into the "+name[5]+
         " in pure comtempt! You can hear the dry sound of ribs "+
         "cracking from the impact.\n");
      tell_room(E(TP),QCTNAME(TP)+" kicks hard into the "+name[5]+
         " in pure contempt. You can hear the dry sound of ribs "+
         "cracking from the impact.\n",TP);
      return 1;
   }
   return 0;
}

/*
* Function name: check_broken
* Description:   This function will break weapons
*/
void
check_broken(object ob)
{
   if(ob->query_prop(OBJ_I_BROKEN))
      {
      tell_room(E(ob),"The "+ob->short()+
         " breaks from the impact!\n");
   }
}

/*
* Function name: do_kick
* Description:   A very small combat-kick. It will initiate combat, but will
*                not do much damage. Hitpen as a found weapon. 
* Arguments:     who - who to kick
*/

void
do_kick(object who, object me)
{
   set_this_player(me); // called by an alarm.

   if (!F_DARE_ATTACK(TP, who))
      {
      write("You don't dare to do it!\n");
      return;
   }
   if (who && environment(TP) != environment(who))
      {
      write("Dissapointedly, you realise that "+QTNAME(who)+" is "+
         "not here anymore.\n");
      return;
   }
   if(!member_array(who,TP->query_enemy(-1)))
      {
      write("You can't kick that gully person now. You two are in "+
         "a deadly fight!\n");
      return;
   }

   kicking=1;
   write("With delight, you prepare break some bones.\n");
   TP->attack_object(who);
   TP->add_attack_delay(2);
   TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
   return;
}

void
spell_attack(object attacker, object target)
{
   string how;
   mixed *hitresult;
   object is_here;
   
   is_here=present(target,E(attacker));
   if(!is_here)
      {
      kicking = 0;
      attacker->catch_msg("Dissapointedly, you realise that "+QTNAME(target)+
         "has dissapeared. What a coward!\n");
      return;
   }
   hitresult = target->hit_me(15, W_BLUDGEON, attacker, -1);
   how = "unharmed";
   if (hitresult[0] > 0)
      how = "a rib";
   if (hitresult[0] > 5)
      how = "two ribs";
   if (hitresult[0] > 10)
      how = "some ribs";
   if (hitresult[0] > 20)
      how = "several ribs";
   if (hitresult[0] > 50)
      how = "the chest itself";
   
   if(hitresult[0] > 0)
      {
      attacker->catch_msg("The kick lands hard into "+
         QTNAME(target)+"'s chest. You hear "+
         "the dry sound of "+how+" cracking from the impact!\n");
      target->catch_msg(QCTNAME(attacker) +
         " kicks you in the chest with all "+attacker->query_possessive()+
         " might. You feel "+how+" crack from the impact!\n");
      tell_watcher(QCTNAME(attacker) + " kicks " + QTNAME(target) +
         " hard in the chest. You can hear the dry sound of "+
         how+" cracking from he impact!\n", attacker, target);
      if (target->query_hp() <= 0)
         target->do_die(attacker);
      kicking = 0;
      return;
   }
   attacker->catch_msg("You miss with the kick against "+
      QTNAME(target)+"'s chest and fall flatfaced down on the ground.\n");
   target->catch_msg(QCTNAME(attacker) +
      " tries to kick you in your chest, but misses utterly and "+
      " falls flatfaced down on the ground.\n");
   tell_watcher(QCTNAME(attacker) + " tries to kick " + QTNAME(target) +
      " in the chest, but misses utterly and falls flatfaced down "+
      " on the ground.\n", attacker, target);
   TP->add_attack_delay(2);
   kicking = 0;
   return;
}

/* function: e_dspit
 * description: allows the player to spit at non-living objects
 * arguments: arg - what to spit at
/*
public int
e_dspit(string arg)
{
   string *name;
   object *corpse;
   string what_at;
   int i, nr;
   
   NF("Dspit at whom/what?\n");
   
   if (!strlen(arg))
      {
      tell_room(E(TP),QCTNAME(TP)+" spits on the ground, showing "+
         TP->query_possessive()+" contempt!\n",TP);
      write("You spit on the ground in pure contempt!\n");
      return 1;
   }
   if(arg=="all")
      {
      write("You are not sure you have enough salvia to do that.\n");
      return 1;
   }
   
   NF("Dspit what?\n");
   if(!parse_command(arg,all_inventory(E(TP)), "[at] / [to] / [toward] [the] %s",what_at))
      return 0;
   NF("Dspit what? There are no corpses here!\n");
   if(!sizeof(corpse=FIND_STR_IN_OBJECT(what_at,E(TP))))
      return 0;
   NF("Be more specific. You don't have enough salvia to spit at all that.\n");
   if(sizeof(corpse)>1)
      return 0;
   
   /* The player spits at something. If this is a corpse, then ok. 
   */
   
   if(corpse[0]->query_name()=="corpse")
      {
      name=corpse[0]->query_names();
      write("You spit at the "+ name[5]+
         ".\n");
      tell_room(E(TP),QCTNAME(TP)+" spits at the "+name[5]+".\n",TP);
      return 1;
   }
   NF("Wierd ... the corpse suddenly dissapeared.\n");
   return 0;
}

/**********************************
 * UNDER CONSTRUCTION !!!!!!!!!!! *
 **********************************/

/* function: e_dloot
 * description: a more advanced looting skill
 * arguments: arg - what to loot
*/


/* removed for now since it is not ready.
public int
e_dloot(string arg)
{
   object *oblist;
   object *obcorpses = ({});
   string *name;
   int i,nr;
   
   if (!strlen(arg))
      {
      tell_room(E(TP),QCTNAME(TP)+" starts to loot any valuables "+
         "lying around, with a greedy glint in the eyes.\n",TP);
      write("You start to loot all valuables you see on the ground.\n");
      TP->command("get coins");
      return 1;
   }
   if(arg=="all")
      {
      tell_room(E(TP),QCTNAME(TP)+" starts to loot everything "+
         TP->query_pronoun()+" can see with a grin of greed clearly "+
         "visible on "+TP->query_possessive()+" face.\n",TP);
      write("You start to loot everything you see around you.\n");
      TP->command("get coins");
      TP->command("get weapons");
      TP->command("get armours");
      return 1;
   }
   if(arg=="coins" || arg=="c" || arg=="co" || arg=="coi")
      {
      tell_room(E(TP),QCTNAME(TP)+" grins with greed "+
         "sparkling in the eyes, and starts to loot any coins visible.\n",TP);
      write("Your eyes sparkle with greed as you start to loot!\n");
      TP->command("get coins");
      return 1;
   }
   if(arg=="weapons" || arg=="w" || arg=="we" || arg=="wea")
      {
      tell_room(E(TP),QCTNAME(TP)+" grins with greed "+
         "sparkling in the eyes, and starts to loot any weapons visible.\n",TP);
      write("Your eyes sparkle with greed as you start to loot!\n");
      TP->command("get weapons");
      return 1;
   }
   if(arg=="armours" || arg=="a" || arg=="ar" || arg=="arm")
      {
      tell_room(E(TP),QCTNAME(TP)+" grins with greed "+
         "sparkling in the eyes, and starts to loot any armours visible.\n",TP);
      write("Your eyes sparkle with greed as you start to loot!\n");
      TP->command("get armours");
      return 1;
   }

   /* we try to loot corpses */
   nr=0;
   oblist=FILTER_DEAD(all_inventory(E(TP)));
   if(!sizeof(oblist)) return 0;
   NF("Dloot what? There is no corpses here!\n");

   for (i=0;i<sizeof(oblist);i++)
      if(oblist[i]->query_name()=="corpse") obcorpses[nr++]=oblist[i];

   if(!sizeof(obcorpses))
      return 0;

   name=obcorpses[0]->query_names();
   if(arg=="corpse" || arg=="c" || arg=="co" || arg=="cor")
      {
      tell_room(E(TP),QCTNAME(TP)+" starts frantically to loot "+
         "the "+name[5]+".\n",TP);
      write("You start to loot the "+name[5]+".\n");
      set_alarm(0.0,0.0,"do_loot",obcorpses[0],"all");
      return 1;
   }
   
   if(arg=="corpses")
      {
      for(i=0;i<sizeof(obcorpses);i++)
      {
         name=obcorpses[0]->query_names();
         tell_room(E(TP),QCTNAME(TP)+" starts frantically to loot all "+
            "the corpses "+TP->query_pronoun()+" can see.\n",TP);
         write("You start to loot all the corpses you can see.\n");
         
         /* this next lines will loot all the corpses in TP's environment */
         
         set_alarm(0.0,0.0,"do_loot",obcorpses[i],"all");
      }
      return 1;
   }
   
   /* the player has asked for a specific corpse to loot. */
      write("not made yet\n");
   return 1;
}

void
do_loot(object corpse, string what)
{
   int i, nr;
   string str;
   object *to_loot = ({});
   object *loot;
   string *name;
   to_loot=all_inventory(corpse);
   name=corpse->query_names();
   nr=0;
   for(i=0;i<sizeof(to_loot);i++)
   {
      if(!to_loot[i]->query_prop(OBJ_I_NO_GET))
         {
         switch (what)
         {
            case "weapons":
            break;
            case "armours":
            break;
            case "all":
            looted[nr++]=loot[i];
            break;
            default: break;
         }
       }
   }
   if(!sizeof(looted))
      {
      write("You looted nothing from the "+name[5]+".\n");
      tell_room(E(TP),QCTNAME(TP)+" looted nothing from the "+name[5]+".\n",TP);
      return;
   }
   for(i=0;i<sizeof(looted);i++)
   {
      looted[i]->move(TP);
      if(!i==(sizeof(looted)-1))
         str=str+looted[i]->query_short()+", ";
      else
         str=str+"and "+looted[i]->query_short();
   }
   write("You looted "+str+" from the "+name[5]+".\n");
   tell_room(E(TP),QCTNAME(TP)+" looted "+str+" from the "+name[5]+".\n",TP);
   return;
}

*/

