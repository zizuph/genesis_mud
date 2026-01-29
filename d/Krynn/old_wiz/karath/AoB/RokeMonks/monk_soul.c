/* The commandsoul of the Kaheda order
* A Glindor production
*
* 930713 Added 'You feel ready to attack again'    Ged
*
* 930722 Changed the plexus and the roundhouse so they make more
*        damage.
*        I made 'the best hit' so that it stuns the enemy 25 (instead of 15)
*        please consider this as a critical hit.   /Ged
*
* 931214 Removed parse_this /gres
*
* 940227
* Changed PREPTIME() (skill/14) -> (skill/15) (bonus to skill for DEX and ACROBAT)
* Added backflips,maegeri,axekick
* Modified plexus,roundhouse        all attacks are stats/skill dependant now
   *
* backflips - you get bonus on SS_DEFENCE but you sacrifice all your atacks
   *             for duration of backflips. No SS_DIS necessary.
* plexus - you stunn enemy. DIS+(WIS/10) must be at least half of average
*          of stats of you opponent to be able to try it
* maegeri - simple kick. No DIS necessary.
* roundhouse - kick with turn. DIS+(WIS/10) must be at least half of average
*              of stats of you opponent to be able to try it  
* axekick - hard but very effective. DIS+(WIS/10) must be at least average
*           of stats of you opponent (you must trust yourself with this one)
*
*  Milan
*
* 9404
* A lot of changes, including the new focus skill. /Glindor
*
* 95** added some emotes /gres
* 96** Mona added emotes*
*/

#pragma save_binary

inherit "/cmd/std/command_driver";

#include <options.h>
#include "/d/Roke/common/defs.h"

#define DEBUG_WHO find_player("shiva")
#define DEBUG_ON
#undef DEBUG_ON
#include "debug.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <math.h>
#include "/std/combat/combat.h"
#include "/d/Roke/common/gont/monks/guild.h"

#include "monks.c"

#define MONK_I_PREPARE "_monk_i_prepare"
#define MONK_I_STUNNED "_monk_i_stunned"

#define WAITING 1
#define BACKFLIPS 2
#define PLEXUS 3
#define MAEGERI 4
#define ROUNDHOUSE 5
#define AXEKICK 6
#define PREPTIME(skill) (15 - (skill/15))

#ifdef STUN
#undef STUN
#endif
#define STUN "/d/Roke/common/gont/monks/obj/test_stun"

do_spec_attack(object tp);
remove_prepare(object who);
end_backflips(mixed foo);

void spec_attack(object me, object enemy);
int stopped = 0;
int bludgeon = (int)MATH_FILE->quick_find_exp(W_BLUDGEON);

/* The soul identification */
   string get_soul_id()
{
   return "Kaheda Order";
}

int query_cmd_soul() { return 1; }

/* To make Dump alarms work */
mixed
query_alarms()
{
   return get_all_alarms();
}

/* **************************************************************************
* The list of verbs and functions. 
*/

/* This should be shadowed by the occ/lay versions of the soul. */
mapping query_cmdlist()
{
    return ([
            "bang"       : "bang", 
            "mbang"      : "bang",
            "bless"      : "bless", 
            "mbless"     : "bless",
            "mchant"     : "chant",
            "chastise"   : "chastise", 
            "mchastise"  : "chastise",
            "convert"    : "convert", 
            "mconvert"   : "convert",
            "cross"      : "cross", 
            "mcross"     : "cross",
            "despair"    : "despair", 
            "gkick"      : "gkick", 
            "mgkick"     : "gkick",
            "help"       : "help",
            "inspire"    : "inspire", 
            "minspire"   : "inspire",
            "kiai"       : "kiai", 
            "mkiai"      : "kiai",
            "mbusy"      : "mbusy",
            "mcalm"      : "mcalm",    //ny
            "mdefend"    : "defend",
            "mdisplay"   : "mdisplay", // ny
            "meditation" : "meditation", 
            "mmeditation": "meditation", // ny
            "mhands"     : "mhands",       //ny
            "mlook"      : "mlook",          //ny
            "monks"      : "monks",
            "mmonks"     : "monks",
            "mpray"      : "pray",
            "mshun"      : "mshun",   //ny
            "mutter"     : "mutter",
            "preach"     : "preach", 
            "mpreach"    : "preach",
            "smite"      : "smite", 
            "msmite"     : "smite",
            "knuckles"   : "knuckles",
            "mknuckles"  : "knuckles",
            "mrap"       : "rap",
            "rap"        : "rap",
            "kata"       : "kata",
            "mkata"      : "kata",
            "step"       : "step",
            "mstep"      : "step",
            "relax"      : "relax",
            "mrelax"     : "relax",
            "gaze"       : "gaze",
            "mgaze"      : "gaze",
            "mscout"     : "mscout",
             "mcontrol"  : "mcontrol",

#ifndef NO_AXEKICK           
            "axekick"    : "axekick",
#endif
#ifndef NO_BACKFLIPS
            "backflips"  : "backflips",
#endif
#ifndef NO_MAEGERI
            "maegeri"    : "maegeri",
#endif
#ifndef NO_PLEXUS
            "plexus"     : "plexus",
#endif
#ifndef NO_ROUNDHOUSE
            "roundhouse" : "roundhouse",
#endif
#ifndef NO_UNARMED
#endif
         ]);
}

/* Shouldnt update this while people are using the commands.
Call this about one minute before you update the soul. */
void
stop_soul(int a = 1)
{
   stopped = a;
}

int
check_stop()
{
   if (stopped)
      {
      write("The Kaheda special attacks has been disabled temporarily.\n"+
         "They should be back any minute.\n");
      return 1;
   }
   return 0;
}

int kolla(object ob)
{
   if(!living(ob))
      return 0;
   
   return 1;
}

int defend(string s)
{
  object o;

  if(!s ||s=="me" || s=="myself")
    {
      write("You take a defensive stance to fend off your attackers.\n");
      say(QCTNAME(TP)+" takes a defencive stance to fend off "+
          TP->query_possessive()+" attackers.\n");
      return 1;
    }

  if(!(o = present(s, E(TP))))
    o = present(s, TP);

  if(o==TP)
    return defend(0);

  if(!o)
    {
      write("You feel a little silly, trying to defend something that's not here.\n");
      say(QCTNAME(TP)+" tries to defend something against an invisible attacker.\n");
      return 1;
    }

  if(living(o))
    {
      TP->catch_msg("You defend "+QTNAME(o)+".\n");
      tell_room(E(TP),QCTNAME(TP)+" takes a defencive stance to protect "+QTNAME(o)+".\n", ({o,TP}));
      o->catch_msg(QCTNAME(TP)+" takes a defencive stance to protect you.\n");
      return 1;
    }

  write("You protect the "+o->query_name()+" against all evil.\n");
  say(QCTNAME(TP)+" protects the "+o->query_name()+" against all evil.\n");

  return 1;
}

int mdisplay(string s)
{
  object o;

  write("You perform a display of complex maneuvers to demonstrate your abilities.\n");
  say(QCTNAME(TP)+" performs a display of complex and acrobatic " + 
      "maneuvers, the fluid motion and deadly grace leave you in awe.\n");
  return 1;
}

int meditation(string s)
{
  object o;

  if (s) 
  {
      notify_fail("Meditation what?\n");
      return 0;
  }

  write("Unable to find the answer to your problem, you decide "+
        "to meditate upon the problem, hoping you'll receive guidance.\n");
  say(QCTNAME(TP)+" sits down and starts to meditate, seeking guidance "+
      "for "+TP->query_possessive()+" dilemma.\n");
  return 1;
}

int pray(string s)
{
  object o;
  notify_fail("Pray for what?\n");

  if(!s)
    {
      write("You pray to your Gods.\n");
      say(QCTNAME(TP)+" prays to "+TP->query_possessive()+" gods.\n");
      return 1;
    }

  if(s=="gods" || s=="to gods")
    {
      write("You kneel, clasping your hands in a reverant appeal to your gods.\n");
      say(QCTNAME(TP)+" kneels, clasping "+TP->query_possessive()+
          " hands in a reverant appeal to "+TP->query_possessive()+" gods.\n");
      return 1;
    }

  if(!(o = present(s, E(TP))))
    o = present(s, TP);

  if(!o)
    {
      write("You pray for "+s+".\n");
      say(QCTNAME(TP)+" prays for "+s+".\n");
      return 1;
    }

  if(living(o))
    {
      TP->catch_msg("You pray for the soul of "+QCTNAME(o)+".\n");
      tell_room(E(TP),QCTNAME(TP)+" prays for the soul of "+QCTNAME(o)+".\n", ({o,TP}));
      o->catch_msg(QCTNAME(TP)+" prays for your soul.\n");
      return 1;
    }

  write("You pray for the poor soulless "+o->query_name()+".\n");
  say(QCTNAME(TP)+" prays for the poor soulless "+o->query_name()+".\n");

  return 1;
}
  
int
bang(string str)
{
   notify_fail("Bang what?\n");
   if (str) return 0;
   
   write("You fall to the ground, banging your head on the earth in reverence to your gods.\n");
   say(QCTNAME(TP)+" falls to the ground, banging "+TP->query_possessive()+" head on the earth in reverence to "+TP->query_possessive()+" gods.\n");
   return 1;
}

int
bless(string someone)
{
   object *a,ob;
   
   if (!someone || someone == "all")
      {
      write("You bestow the powers of Kaheda on your audience.\n");
      say(QCTNAME(TP)+" blesses everybody with the powers of Kaheda.\n");
      return 1;
   }
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   NF("Bless who?\n");
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      TP->catch_msg("You bless yourself with the powers of Kaheda.\n");
      return 1;
   }
   
   TP->catch_msg("You bestow the powers of Kaheda on "+QTNAME(ob)+".\n");
   tell_room(E(TP),QCTNAME(TP)+" blesses "+QTNAME(ob)+
      " with the powers of Kaheda.\n",({TP,ob}));
   
   ob->catch_msg(QCTNAME(TP)+" has blessed you with the powers of Kaheda.\n");
   return 1;
}

chant()
{
   say(QCTNAME(TP)+" chants in a strange language and gains more strength.\n");
   write("You chant a prayer and feel the powers of Kaheda within your body.\n");
   return 1;
}

chastise(string someone)
{
   object *a,ob;
   
   if (!someone || someone=="all")
      {
      write("You scowl and shake your finger.\n");
      say(QCTNAME(TP)+" scowls and shakes "+TP->query_possessive()+" finger.\n");
      return 1;
   }
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   NF("Chastise who?\n");
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      TP->catch_msg("You shake your finger at yourself, feels rather dumb.\n");
      return 1;
   }
   
   TP->catch_msg("You chastise "+QCTNAME(ob)+".\n");
   
   tell_room(E(TP),QCTNAME(TP)+" scowls and shakes "+TP->query_possessive()+
      " finger at "+QTNAME(ob)+".\n",({TP,ob}));
   
   ob->catch_msg(QCTNAME(TP)+" scowls and shakes "+TP->query_possessive()+
      " finger at you.\n");
   return 1;
}

int
convert(string someone)
{
   object *a,ob;
   
   NF("Convert who?\n");
   if (!someone) return 0;
   
   if (someone=="all")
      {
      write("This needs personal touch if you want to be succesfull.\n");
      return 1;
   }
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      TP->catch_msg("You try to convert yourself, feels rather dumb.\n");
      return 1;
   }
   
   if(ob->query_guild_name_occ()==GUILD_NAME)
      {
      TP->catch_msg("No! You don't want to convert anyone away from Kaheda!\n");      return 1;
   }
   
   if((ob->query_guild_name_lay()==GUILD_NAME) &&
         (TP->query_guild_name_lay()==GUILD_NAME))
   {
      TP->catch_msg("You must join Kaheda occupationally first!!! "+
         "Be a good example!.\n");
      return 1;
   }
   
   if(ob->query_guild_name_lay()==GUILD_NAME)
      {
      TP->catch_msg("You attempt to convert "+QTNAME(ob)+
         " to join Kaheda occupationally.\n");
      ob->catch_msg(QCTNAME(TP)+" nags you to see the light and join "+
         TP->query_possessive()+" order occupationally.\n");
      tell_room(E(TP),QCTNAME(TP)+" takes "+QTNAME(ob)+" around "+
         ob->query_possessive()+" shoulders and argues long "+
         "time about something.\n",({TP,ob}));
      return 1;
   }
   
   TP->catch_msg("You attempt to convert "+QTNAME(ob)+
      " to join Kaheda.\n");
   ob->catch_msg(QCTNAME(TP)+" nags you to see the light and join "+
      TP->query_possessive()+" order.\n");
   tell_room(E(TP),QCTNAME(TP)+" takes "+QTNAME(ob)+" around "+
      ob->query_possessive()+" shoulders and argues long "+
      "time about something.\n",({TP,ob}));
   return 1;
}

int
kolla2(object ob)
{
   if (living(ob) || ob->id("corpse"))
      return 1;
   return 0;
}

int
cross(string someone)
{
   object *a,ob;
   
   if (!someone)
      {
      write("You make a cross-like pattern across your chest.\n");
      say(QCTNAME(TP)+" gestures with "+TP->query_possessive()+
         " hand in a cross-like pattern across "+TP->query_possessive()+
         " chest.\n");
      return 1;
   }
   if(someone == "all")
      {
      write("You make a cross sign on everyone.\n");
      say(QCTNAME(TP)+" gestures in your direction with "+
         TP->query_possessive()+" hand in a cross-like pattern.\n");
      return 1;
   }
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla2","kolla2");
   
   NF("Cross who?\n");
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      write("You make a cross-like pattern across your chest.\n");
      say(QCTNAME(TP)+" gestures with "+TP->query_possessive()+
         " hand in a cross-like pattern across "+TP->query_possessive()+
         " chest.\n");
      return 1;
   }
   
   if (!living(ob))
      {
      write("You make a cross sign on the "+ob->short()+".\n");
      tell_room(E(TP),QCTNAME(TP)+" gestures over the "+QSHORT(ob)+
         " with "+TP->query_possessive()+" hand in a "+
         "cross-like pattern.\n",({TP}));
      return 1;
   }
   TP->catch_msg("You make a cross sign on "+QTNAME(ob)+".\n");
   tell_room(E(TP),QCTNAME(TP)+" gestures in "+QTNAME(ob)+"'s direction "+
      "with "+TP->query_possessive()+" hand in a "+
      "cross-like pattern.\n",({TP,ob}));
   ob->catch_msg(QCTNAME(TP)+" gestures in your direction with "+
      TP->query_possessive()+" hand in a cross like pattern.\n");
   return 1;
}

drool()
{
    say(QCTNAME(TP)+" drools exactly like the Cute Drooling Dragon.\n");
    write("You drool just like your pet.\n");
    return 1;
}

int 
shun_check(object ob)
{
    return 1;
}

int
mshun(string someone)
{
   object *a,ob;
   
   if (!someone)
   {
       notify_fail("Shun what?\n");
       return 0;
   }

   a = CMDPARSE_ONE_ITEM(someone,"shun_check","shun_check");
   
   NF("Shun what?\n");
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
   {
       write("You shun yourself. Feels rather silly.\n");
       return 1;
   }
   
   if (!living(ob))
   {
       if (ob->num_heap() > 1)
       write("You shun the "+ob->short()+
             " since " + (ob->num_heap() > 1 ? "they": "it") +
             " represents a great sin in your eyes.\n");
       say(QCTNAME(TP)+" does not acknowledge the existence of the " 
           + QSHORT(ob) + ", except for a slight look of utter revulsion "+
           "which appears on "+TP->query_possessive()+ " face.\n");
       return 1;
   }

   TP->catch_msg("You shun "+QTNAME(ob)+ " because " +
                 ob->query_pronoun() + " has committed a "+
                 "great crime in your eyes.\n");
   ob->catch_msg(QCTNAME(TP)+ " hardly appears to notice you exist, except "+
                 "for the slight look of utter revulsion on "+
                 TP->query_possessive()+" face.\n");
   say(QCTNAME(TP)+" does not acknowledge " + QTNAME(ob) +
       "'s existence, except for a slight look of utter revulsion "+
       "which appears on "+TP->query_possessive()+ " face.\n", ({ob,TP}));
   return 1;

}

query_type()
{
   if(TP->query_gender()==1)
      return "nun";
   else
      return "monk";
}

despair()
{
  if(!(present("munkmedalj",TP)->query_shaved()))
    return 0;

  TP->catch_msg("You tear a lump of hair from your nose.\n");
  tell_room(E(TP),QCTNAME(TP)+" tears a lump of hair from "+
            TP->query_possessive()+" nose in despair.\n", TP);
  return 1;
}


gkick(string someone)
{
   object *a,ob;
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   NF("Kick who?\n");
   
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      TP->catch_msg("You quickly decide against kicking yourself.\n");
      return 1;
   }
   
   TP->catch_msg("You kick "+QTNAME(ob)+" in the groin.\n");
   tell_room(E(TP),QCTNAME(TP)+" kicks "+QTNAME(ob)+" in the groin.\n",({TP,ob}));
   
   ob->catch_msg(QCTNAME(TP)+" kicks you in the groin.\n");
   
   if(!ob->query_gender()) {
      ob->catch_msg("You fall to the ground, stunned by the"+
         " immense pain.\n");
      tell_room(E(TP),"He falls to the ground, stunned by the immense pain.\n",({ob})); }
   else
      ob->catch_msg("It hurts, but fortunately you are not male.\n");
   return 1;
}

mcalm(string someone)
{
   object *a,ob;
   
   a = PARSE_THIS(someone, "%l");
   
   NF("Mcalm who?\n");
   
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
   {
       write("You practice breathing in the manner of the ancients, "+
             "in an effort to remain calm despite your own ignorance.\n");
       return 1;
   }
   
   TP->catch_msg("You practice breathing in the manner of the ancients, "+
                 "in an effort to remain calm while "+QTNAME(ob) +
                 " proudly displays " +ob->query_possessive() +
                 " ignorance.\n");

   ob->catch_msg(QCTNAME(TP)+" re-centers " + TP->query_objective() + "self"+
                 " with a breathing technique, remaining calm and forgiving "+
                 "despite your obvious ignorance.\n");
   
   tell_room(E(TP),QCTNAME(TP)+" re-centers "+TP->query_objective() +
             "self with a breathing "+
             "technique, remaining calm and forgiving despite "+
             QTNAME(ob)+"'s ignorance.\n",({TP,ob}));
   
   return 1;
}

mhands(string someone)
{
   object *a,ob;
   mixed b;

   NF("Mhands what?\n");
   
   b = parse_adverb_with_space(someone, "triumphantly", 0);

   write("You raise your fist to the heavens"+b[1]+
         ", summoning the powers of the gods.\n");

   say(QCTNAME(TP)+" raises "+TP->query_possessive()+" fist"+b[1]+
       " in the air. You feel the air stir with Great Power.\n");
   
   return 1;
}

mlook(string someone)
{
   object *a,ob;
   mixed b;

   NF("Mlook who?\n");
   
   if (!strlen(someone)) return 0;

   b = parse_adverb_with_space(someone, ".", 1);


   a = PARSE_THIS(b[0], "%l");
   
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
   {
       write("You try to look"+b[1]+" at yourself, but fail.\n");
       return 1;
   }
   
   TP->catch_msg("You look"+b[1]+" in "+QTNAME(ob)+ "'s direction, giving "+
                 ob->query_objective()+" the keen feeling of the danger of "+
                 "trifling with a Kahedan.\n");

   ob->catch_msg(QCTNAME(TP)+" looks"+b[1]+" in your direction. You are "+
                 "sure trifling with a Kahedan would not be wise.\n");
   
   tell_room(E(TP),QCTNAME(TP)+" looks"+b[1]+" in "+QTNAME(ob)+"'s "+
             "direction, clearly making "+ob->query_objective()+
             " aware of the dangers of trifling with a Kahedan.\n",({TP,ob}));
   
   return 1;
}

int help(string s)
{
   if (s=="kaheda")
   {
       setuid();
       seteuid(getuid());
       cat(HELPFILE);
       return 1;
   }

  if (s=="kaheda emotes")
   {
       setuid();
       seteuid(getuid());
       cat(HELP_EMFILE);
       return 1;
   }

   return 0;
 
/*
   TP->catch_msg(
      "These commands are available:\n"+
      "chant - chant a prayer\n"+
      "gkick - kick someone in the groin\n"+
      "preach - lecture someone on the finer points of religion\n"+
      "chastise - scowl and shake your finger\n"+
      "bless - bless someone\n"+
      "kiai - combat yell\n"+
      "mutter - mutter something under your breath\n"+
      "bang - bang your head on the ground\n"+
      "inspire - when you have an inspiration\n"+
      "convert - try to convert someone\n"+
      "mpray to gods- clear, isn't it?\n"+
      "(or mpray <something/someone/text>)\n"+
      "defend - defend something\n"+
      "cross - make cross sign on someone\n"+
      "smite - smite someone with ruler\n"+
      "knuckles - tend wounded knuckles\n"+
        "step- a token of peace\n"+
      "kata  - preform a kata.\n"+
      "mrap - rap your ruler against your palm in warning\n"+
      "relax - relax and seek inner peace\n"+
      "gaze - gaze at someone with the wisdom of a Kahedan\n"+
      "mscout - scan your surroundings for potential misgivings\n"+
       "mcontrol - gain control over your anger\n"+
      "mtell - monk tell line command\n"+
      "mbusy - dont hear the monk tells\n"+
      "drool - drool like the dragon\n\n"+
      "Occupational members also have:\n"+
      "backflips  : make backflips so it is harder to hit you\n"+
      "plexus     : give your opponent a stunning blow in the stomach\n"+
      "maegeri    : simple kick forward - very fast and quite effective\n"+
      "roundhouse : a special kick involving fast turn to add more power\n"+
      "axekick    : jumping axe kick - hard to hit people with it because\n"+
      "             it is slow, but the least it will do is break their\n"+
      "             collar bone\n\n"+
      "The robe also provides some emotes. Try 'help robe' when you have one.\n");
*/   
   return 1;
}

int
inspire(string str)
{
   notify_fail("Inspire what?\n");
   if (str) return 0;
   
   write("You see the light!\n");
   say(QCTNAME(TP)+" stares in glossy-eyed rapture at the sky, you "+
      "wonder what "+TP->query_pronoun()+" sees up there...\n");
   return 1;
}

int
kiai(string str)
{
   int skill;
   
   notify_fail("Kiai what?\n");
   if (str) return 0;
   
   skill=this_player()->query_skill(SS_UNARM_COMBAT);
   
   if (skill<10)
      {
      write("You make a funny sound.\n");
      say(QCTNAME(TP)+" makes a funny sound. Something like 'ia'.\n");
   }
   else if (skill<40)
      {
      write("You raise a cry.\n");
      say(QCTNAME(TP)+" raises a cry: Hi-Ya!\n");
   }
   else if (skill<80)
      {
      write("HIII-YAAAA!\n");
      say(QCTNAME(TP)+" yells: HIII-YAAA!\n");
   }
   else
      {
      write("H H I I I   Y Y  A   A   A !\n");
      write("HHH I I I   Y Y A A A A A A!\n");
      write("H H I I I    Y  AAA AAA AAA!\n");
      write("H H I I I    Y  A A A A A A!\n");
      write("Everyone steps back, terrified.\n");
      say(QCTNAME(TP)+" yells: HIII-YAAA!\n");
      say("You step back, terrified.\n");
   }
   return 1;
}

int mbusy()
{
   int apa;
   
   apa = TP->query_prop(MONK_IS_BUSY);
   
   TP->add_prop(MONK_IS_BUSY,1-apa);
   
   TP->catch_msg("You are now "+(apa?"all ears.\n":"very busy.\n"));
   return 1;
}

int
mtell(string str)
{
   string who,text;
   object ob;
   
   if (!str || sscanf(str,"%s %s",who,text) != 2) 
      {
      NF("Mtell what?\n");
      return 0;
   }
   who = lower_case(who);
   
   if (!(ob=find_living(who)) || !query_ip_number(ob))
      {
      NF("Couldn't locate "+capitalize(who)+".\n");
      return 0;
   }
   
   if (!IS_MEMBER(ob) &&
         !("/secure/master"->query_wiz_dom(TP->query_real_name())=="Roke"))
   {
      write("You can only send to Kaheda members.\n");
      return 1;
   }
   if (TP->query_mana() < 5)
      {
      write("You are too exhausted to do that.\n");
      return 1;
   }
   
   TP->add_mana(-5);
   
   if(find_living(who)->query_prop(MONK_IS_BUSY))
      {
      TP->catch_msg("It seems like "+capitalize(who)+" doesn't listen.\n");
      return 1;
   }

   if (TP->query_option(OPT_ECHO))
      write("You told this to "+capitalize(who)+": "+text+"\n");
   else
      write("Ok\n");
   
   if(!ob->query_wiz_level())
      ob->catch_msg("You feel the presence of "+
      capitalize(TP->query_real_name())+".\n"+
      capitalize(TP->query_pronoun())+" tells you: "+text+"\n");
   else
      {
      ob->catch_msg(capitalize(TP->query_real_name())+" Kaheda-tells you: "+
         text+"\n");
      ob->add_prop("_reply_wizard",TP->query_real_name());
   }
   return 1;
}    

int
mutter(string str)
{
   notify_fail("Mutter what?\n");
   if (str) return 0;
   
   write("You mutter something under your breath.\n");
   say(QCTNAME(TP)+" mutters something under "+TP->query_possessive()+" breath.\n");
   return 1;
}

preach(string someone)
{
   object *a,ob;
   
   if (!someone || someone=="all")
      {
      write("You lecture your audience on the finer points of religion.\n");
      say(QCTNAME(TP)+" lectures everybody on the finer points of religion.\n");
      return 1;
   }
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   NF("Preach who?\n");
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      TP->catch_msg("You lecture yourself on the finer points of religion.\n");
      TP->catch_msg("It feels good to speak to someone who listen.\n");
      return 1;
   }
   
   TP->catch_msg("You lecture "+QTNAME(ob)+
      " on the finer points of religion.\n");
   tell_room(E(TP),QCTNAME(TP)+" lectures "+QTNAME(ob)+
      " on the finer points of religion.\n",({TP,ob}));
   
   ob->catch_msg(QCTNAME(TP)+
      " lectures you in depth on the finer points of religion.\n");
   return 1;
}

int
smite(string someone)
{
   object *a,ob;
   
   NF("Smite who?\n");
   if (!someone) return 0;
   
   a = CMDPARSE_ONE_ITEM(someone,"kolla","kolla");
   
   if(!sizeof(a))
      return 0;
   
   ob = a[0];
   
   if(ob == TP)
      {
      write("You pull out your handy ruler and smite yourself across "+
         "the knuckles.\nOuch!!!\n");
      say(QCTNAME(TP)+" produces a ruler and rap it across "+
         TP->query_possessive()+" knuckles.\n");
      return 1;
   }
   
   TP->catch_msg("You pull out your handy ruler and smite "+QTNAME(ob)+
      " across the knuckles.\n");
   tell_room(E(TP),QCTNAME(TP)+" produces a ruler and rap it across the "+
      "knuckles of "+QTNAME(ob)+".\n",({TP,ob}));
   ob->catch_msg(QCTNAME(TP)+" produces a ruler and smite you across "+
      "the knuckles.\nOuch!!!\n");
   return 1;
}

int knuckles(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "carefully", 0);
 
    if (!strlen(how[0]))
    {
        write("You nurse your knuckles" + how[1] + ", in " +
            "hopes the pain will subside.\n ");
        allbb(" nurses "  + TP->query_possessive() + " knuckles"
            +how[1] + ", in an effort to stop the pain.");
    }
    else
    {
    NF("mknuckles whom?\n");
    if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
    {
        return 0;
    }
        targetbb(how[1] + " tends your wounded knuckles.",
            oblist);
        actor("You nurse", oblist, "'s knuckles" +how[1] +
            ", in an effort to stop the pain.");
        all2actbb("  nurses", oblist, "'s knuckles" + how[1]+
            ", in an effort to stop the pain.");
    }
        return 1;
}


int rap(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "warily", 0);
 
    NF("Mrap how? At whom?\n");
    if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
    {
        return 0;
    }
    targetbb(" raps " + TP->query_possessive() + " ruler "+
        "on the base of " + TP->query_possessive() + 
        " palm, eyeing you" +how[1]+ ".",oblist);
    actor("You rap your ruler on the base of your palm, "+
        "eyeing", oblist, "" +how[1] + ".");
    all2actbb(" raps " + TP->query_possessive() + " ruler"+
        " on the base of " + TP->query_possessive() +
        " palm, eyeing", oblist, ""+ how[1] + ".");
    return 1;
}
int step(string str)
{
 object *oblist;

 if (!strlen(str))
  {
    write("You lightly take a step backwards in a subtle gesture "+
         "of peace.\n");
    allbb(" steps back lightly, in a subtle gesture of peace.");

  return 1;
}
 NF("Step away from who?\n");
 if (!sizeof(oblist = parse_this(str, "[away] / [back] [from] [the] %l")))
  {
    return 0;
  }
  targetbb(" steps back lightly.  It appears that "+TP->query_pronoun()+
       " does not mean you any harm.", oblist);
  actor("You lightly take a step out of", oblist, "'s way in a " +
       "subtle gesture of peace.");
  all2actbb(" lightly steps back, in a subtle gesture of peace " +
       "towards", oblist, ".");

return 1;
}

int relax(string str)
{
  if (strlen(str))
  {
    return 0;
  }
 
  write("You relax your body in an attempt to achieve inner" +
        " peace.\n");
  allbb(" becomes extremely calm and relaxed.  Suddenly you" +
        " notice how still and peaceful everything has become.");
 
  return 1;
}

int kata(string str) 
{
    object *oblist;
 
    if (!strlen(str))
    {
        write("You perform a kata with poise and grace, "+
            "maintaining at all times a keen and sharp "+
            "awareness of your surroundings.\n");
        allbb(" gracefully preforms a kata, moving smoothly"+
            " from one form to the next with catlike refle"+
            "xes, all the while " + TP->query_possessive()+
            " eyes alert and " +TP->query_possessive() +
            " brow set in concentration.");
    }
    else
    {
    NF("Mkata to whom?\n");
    if (!sizeof(oblist = parse_this(str,
        "[to] / [before] [the] %l")))
 
        {
            return 0;
        }
        targetbb(" gracefully preforms a kata before you, "+
            "moving smoothly from one form to the next "+
            "with catlike reflexes, all the while " +
            TP->query_possessive()+ " eyes never leave "+
            "yours. Still you get a strong sense that "+
            TP->query_pronoun()+ " is completely aware of "+
            TP->query_possessive()+ " surroundings.", oblist);
        actor("You preform a kata before", oblist,
            " orienting on " + oblist[0]->query_possessive()+
            " gaze, yet you maintain a keen and sharp "+
            "awareness of your surroundings.\n");
        all2actbb(" gracefully preforms a kata before",
            oblist, ", moving smoothly from one form to the "+
            "next. "+ TP->query_name()+ "'s eyes never leave "+
            oblist[0]->query_possessive() +
            "'s, yet all the while "+
            TP->query_pronoun() + " maintains a catlike "+
            "awareness and fluidity of motion, eyes alert "+
            "and brow set in concentration.");
    }
        return 1;
}
 
int gaze(string str)
{
  object *oblist;
 
  if (!strlen(str))
  {
    write("Your eyes gleam as you reflect on the vast wisdom "+
        "of the gods.\n");
  allbb("'s eyes gleam with the brilliance of untold wisdom.");
 
    return 1;
  }
 
  NF("Gaze at whom?\n");
  if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
  {
    return 0;
  }
 
  target("'s eyes gleam as " +TP->query_pronoun()+
        " gazes at you with the brilliance of untold wisdom.", oblist);
  actor("Your eyes gleam as you gaze at", oblist," with the " +
        "wisdom of a Kahedan.");
  all2actbb(" 's eyes gleam as "+TP->query_pronoun()+ 
        " gazes at", oblist," with the brilliance of untold wisdom.");

  return 1;
}

int mscout(string str)
{
  if (strlen(str))
  {
    return 0;
  }
 
write("Remembering the enslavement of the first Kahedans," +
        " you carefully scan your surroundings for potential " + 
        "misgivings.\n");
  allbb(" scans the surrounding area very carefully.  "+
      capitalize(TP->query_pronoun())+ " seems apprehensive.");
        
  return 1;
}

int mcontrol(string str)
{
 object *oblist;

  if (!strlen(str))
  {
    write("You fight to maintain the ideals of a Kahedan " +
        "despite your anger.\n");
    all("'s face visibly clouds as " + TP->query_pronoun() +
        " fights to control " + TP->query_possessive() + " anger.");

    return 1;
  }

  NF("Control your anger at whom?\n");
  if (!sizeof(oblist = parse_this(str, "[my] [anger] [at] [the] %l")))
  {
    return 0;
  }

    target("'s face clouds visibly as " + TP->query_pronoun()+
        " struggles to control " + TP->query_possessive() +
        " anger at your behavior.", oblist);
    actor("You fight to maintain the ideals of a Kahedan " +
        "despite", oblist, "'s offensive behavior.");
    all2act(" 's face clouds visibly as " + TP->query_pronoun()+
        " fights to control " + TP->query_possessive() +
        " anger despite", oblist,  "'s behavior.");

    return 1;
}
 
/* The special attacks */

static void
tell_watcher(string str, object me, object enemy)
{
   object *ob;
   int i;
   
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
 if (ob[i]->query_option(!OPT_BLOOD))
        ob[i]->catch_msg(str);
}

void
remove_prepare(object who)
{
   DEBUG("Removing preparation: " + who->query_real_name());
   if (who->query_prop(MONK_I_PREPARE) > 1)
      who->catch_msg("Kaheda Debug Message (TM) : High prepare removed.\n");
   who->add_prop(MONK_I_PREPARE,0);
   who->catch_msg("You feel ready to attack again.\n");
}

string ptext1(int a)
{
   string text;
   
   text = "a lousy";
   if (a > 40)
      text = "a mediocre";
   if (a > 60)
      text = "a good";
   if (a > 90)
      text = "an excellent";
   return text;
}

string ptext2(int a)
{
   string text;
   
   text = "unharmed";
   if (a > 0)
      text = "slightly hurt";
   if (a > 15)
      text = "rather hurt";
   if (a > 30)
      text= "very hurt";
   if (a > 50)
      text = "crushed";
   if (a > 90)
      text = "massacred";
   return text;
}

int doing_something(mixed a)
{
   if (a[0] == a[1])
      {
      write("You are already doing that.\n");
      return 1;
   }
   if (a[0] == WAITING)
      {
      write("You can't get yourself together to do that.\n");
      return 1;
   }
   if (a[0])
      {
      write("You are already preparing something else.\n");
      return 1;
   }
   return 0;
}

void
do_spec_attack(object tp)
{
   object enemy;
   
   if (!(enemy = tp->query_attack())) 
      {
      /* Hmm, maybe say something here... */
      tp->add_prop(MONK_I_PREPARE,0);
      return;
   }
   if (environment(enemy)!=environment(tp))
      {
      tp->catch_msg("Your enemy is gone.\n");
      tp->add_prop(MONK_I_PREPARE,0);
      return;
   }
   spec_attack(tp,enemy);
}

int backflips()
{
   object enemy;
   
   if (!IS_OCC(TP))
   {
     return 0;
   }

   enemy=TP->query_attack();
   if (!enemy) 
      {
      NF("But you are not fighting anyone.\n");
      return 0;
   }
   if(doing_something(({TP->query_prop(MONK_I_PREPARE),BACKFLIPS}))) return 1;
   if (check_stop()) return 1;
   /***  you dont need DIS to try avoid hitting yourself  ***/
   TP->add_prop(MONK_I_PREPARE,BACKFLIPS);
   write("You prepare for doing backflips.\n");
    set_alarm(4.0, 0.0, &do_spec_attack(TP));
   return 1;
}

void
end_backflips(mixed foo)
{
   object me = foo[0];
   int a = foo[1];
   int b;
   b = me->query_skill_extra(SS_DEFENCE);
   me->set_skill_extra(SS_DEFENCE,b-a);
   me->catch_msg("You stop doing backflips.\n");
   tell_room(environment(me),QCTNAME(me)+" stops doing backflips.\n",me);
   me->add_prop(MONK_I_PREPARE,WAITING);
   me->remove_stun();
    set_alarm(itof(MAX(4,20-a)), 0.0, &remove_prepare(me));
   return;
}

/*
object get_stun()
{
   object *stuns, stun;
   stuns = all_inventory(find_object(SOULBASE));
   
   if (!sizeof(stuns))
      {
      setuid();
      seteuid(getuid());
      stun = clone_object(STUN);
   }
   else
      {
      stun = stuns[0];
      stun->set_stored(0);
   }
   return stun;
}

store_stun()
{
   object stun;
   
   stun = previous_object();
   stun->move(this_object(),1);
   stun->set_stored(1);
}
*/

int plexus()
{
   object enemy;
   int dis_wis;
   
   if (!IS_OCC(TP))
   {
     return 0;
   }

   enemy=TP->query_attack();
   if (!enemy) 
      {
      NF("But you are not fighting anyone.\n");
      return 0;
   }
   if(doing_something(({TP->query_prop(MONK_I_PREPARE),PLEXUS}))) return 1;
   if (check_stop()) return 1;
   /*** you need DIS wisdom may help a bit too ***/
   dis_wis = TP->query_stat(SS_DIS) + (TP->query_stat(SS_WIS) / 10);
   if((enemy->query_average_stat()) > (2*dis_wis))
      {
      write("You don't dare to try plexus on "+enemy->query_objective()+".\n");
      return 1;
   }
   TP->add_prop(MONK_I_PREPARE,PLEXUS);
   write("You try to get a chance to hit "+enemy->query_objective()+
      " in the stomach.\n");
    set_alarm(4.0, 0.0, &do_spec_attack(TP));
   return 1;
}

int maegeri()
{
   object enemy;
   
   enemy=TP->query_attack();
   if (!enemy) 
      {
      NF("But you are not fighting anyone.\n");
      return 0;
   }
   if(doing_something(({TP->query_prop(MONK_I_PREPARE),MAEGERI}))) return 1;
   if (check_stop()) return 1;
   /*** no DIS needed for dhis one ***/
   TP->add_prop(MONK_I_PREPARE,MAEGERI);
   write("You prepare to do a Mae-Geri.\n");
    set_alarm(2.0, 0.0, &do_spec_attack(TP));
   return 1;
}

int roundhouse()
{
   object enemy;
   int dis_wis;
   
   if (!IS_OCC(TP))
   {
     return 0;
   }

   enemy=TP->query_attack();
   if (!enemy) 
      {
      NF("But you are not fighting anyone.\n");
      return 0;
   }
   if(doing_something(({TP->query_prop(MONK_I_PREPARE),ROUNDHOUSE}))) return 1;
   if (check_stop()) return 1;
   /*** you need DIS wisdom may help a bit too ***/
   dis_wis = TP->query_stat(SS_DIS) + (TP->query_stat(SS_WIS) / 10);
   if((enemy->query_average_stat()) > (2*dis_wis))
      {
      write("You don't dare to turn back to "+enemy->query_objective()+".\n");
      return 1;
   }
   TP->add_prop(MONK_I_PREPARE,ROUNDHOUSE);
   write("You prepare to do a roundhouse.\n");
    set_alarm(4.0, 0.0, &do_spec_attack(TP));
   return 1;
}

int axekick()
{
   object enemy;
   int dis_wis;
   
   if (!IS_OCC(TP))
   {
     return 0;
   }

   enemy=TP->query_attack();
   if (!enemy) 
      {
      NF("But you are not fighting anyone.\n");
      return 0;
   }
   if(doing_something(({TP->query_prop(MONK_I_PREPARE),AXEKICK}))) return 1;
   if (check_stop()) return 1;
   /*** you need DIS wisdom may help a bit too ***/
   dis_wis = TP->query_stat(SS_DIS) + (TP->query_stat(SS_WIS) / 10);
   if((enemy->query_average_stat()) > (dis_wis))
      {
      write("You don't think you can succeed with it on "+
         enemy->query_objective()+".\n");
      return 1;
   }
   TP->add_prop(MONK_I_PREPARE,AXEKICK);
   write("You prepare to do a jumping spinning axe kick.\n");
set_alarm(6.0, 0.0, &do_spec_attack(TP));
   return 1;
}

void 
spec_attack(object me, object enemy)
{
   int ac,skill,e_skill,pen,t,perf,pdam, a,b1,b2, *hit_ids;
   string text;
   mixed *hitresult, *hitloc;
   object stun, combat_ob;
   float tt;
   
   /************************************************************************/
   if (me->query_prop(MONK_I_PREPARE)==BACKFLIPS)
      {
      /***  skills to determine succes/recovery  ***/
      skill=(me->query_skill(SS_UNARM_COMBAT)/2) +
      (me->query_skill(SS_ACROBAT)*3/2) +
      (me->query_stat(SS_DEX));
      
      a = (5+random(skill/10));
      me->set_skill_extra(SS_DEFENCE,a);
      me->catch_msg("You start to do backflips trying to avoid being hit.\n");
      tell_room(environment(me),QCTNAME(me)+" starts to do backflips trying to "+
         "avoid being hit.\n",me);
      t = MIN((a+5),25);   /*** max duration is 25 seconds ***/
      me->add_stun();  
        set_alarm(itof(t), 0.0, &end_backflips(({ me, a})));
      return;  /***  end of Backflips ***/
   }
   /************************************************************************/
   if (me->query_prop(MONK_I_PREPARE)==PLEXUS)
   {
     /***  skills to determine succes/recovery  ***/
     skill = (me->query_skill(SS_UNARM_COMBAT) * 2) +
         (me->query_skill(SS_FOCUS) * 4) +
         (me->query_stat(SS_DEX)) / 5 ;
     e_skill = MAX(50, enemy->query_skill(SS_DEFENCE));
     /* what if he doesnt have DEFENCE? */
         
     /*** how long does it take to recover ***/
     me->add_prop(MONK_I_PREPARE, WAITING);
     DEBUG("Plexus: " + me->query_real_name());
    set_alarm(itof(MAX(6,PREPTIME(skill))), 0.0, &remove_prepare(me));
      
     /*** will we hit?  not if he's stunned already ***/ 
     if (!enemy->query_prop(MONK_I_STUNNED) && 
         random(skill) > random(e_skill))
     {
       combat_ob = enemy->query_combat_object();
       if (!(hitloc = combat_ob->query_hitloc(A_BODY)))
       {
         hit_ids = combat_ob->query_hitloc_id();
         if (sizeof(hit_ids))
         {
           for (ac = 0, a = sizeof(hit_ids); a--;)
           {
             ac += combat_ob->query_hitloc(hit_ids[a])[HIT_AC][bludgeon];
           }

           ac /= sizeof(hit_ids);

         }
       }
       else
       {
         ac = hitloc[HIT_AC][bludgeon];
       }
         
       ac = ac/2 + random(ac/2);
         
       skill = (4 * me->query_skill(SS_FOCUS) +
            2 * me->query_skill(SS_UNARM_COMBAT) +
            me->query_stat(SS_STR)) / 7;
       pen = random(skill * 2) - ac;

       text = capitalize(enemy->query_pronoun());

       if (pen <= 0)
       {
         tt=0.0;
         text += " doesn't seem to feel it.\n";
       }
       else if (pen < 30)
       {
         tt=10.0 + itof(pen) / 3.0;  /* 10-20 sec */
         text += " loses " + enemy->query_possessive() + 
             " breath for a moment. \n";
       }
       else if (pen < 90)
       {
         tt = 10.0 + itof(pen) / 3.0;  /* 20-40 sec */
         text += " looks as if " + enemy->query_pronoun() + 
             " can't breathe.\n";
       }
       else
       {
         tt = 40.0;
         text += " looks very stunned by the blow.\n";
       }

       me->catch_msg("You hit " + enemy->query_the_name(me) +
           " in the stomach.\n" + text);
       enemy->catch_msg(me->query_The_name(enemy) + 
           " hits you in the stomach.\n");
       tell_watcher(QCTNAME(me)+" hits "+QTNAME(enemy)+" in the stomach.\n"+
            text, me, enemy);

       if (tt > 0.0)
       {
         DEBUG("Got here.\n");

         setuid();
         seteuid(getuid());
    
         if (stun = clone_object(STUN))
         {
           if (stun->move(enemy, 1))
           {
             stun->remove_object();
           }
           else
           {
             stun->start_time(tt, 70.0);
           }
         }
       }
     }
     else
     {
       me->catch_msg("You try to hit " + enemy->query_the_name(me) + 
           " in the stomach but miss.\n");
       enemy->catch_msg(me->query_The_name(enemy) + 
           "tries to hit you in the stomach but misses.\n");
     }
 
     return; /***  end of plexus  ***/
   }  
   /************************************************************************/
   if (me->query_prop(MONK_I_PREPARE)==MAEGERI)
      {
      /***  skills to determine succes/recovery  ***/
      skill=(me->query_skill(SS_FOCUS) * 8 +
         me->query_skill(SS_UNARM_COMBAT) * 4 +
         me->query_skill(SS_ACROBAT) +
         me->query_stat(SS_DEX) * 2) / 10;
      e_skill=enemy->query_skill(SS_DEFENCE) +
      enemy->query_stat(SS_DEX) / 3;
      
      /*** how long does it take to recover ***/
      me->add_prop(MONK_I_PREPARE,WAITING);
        set_alarm(itof(MAX(6, PREPTIME(skill)-3)), 0.0, 
            &remove_prepare(me));
      
      /***  will we hit?  ***/
      if (random(skill*4) > random(e_skill))
         {
         skill = (me->query_skill(SS_FOCUS) * 2 +
            me->query_skill(SS_UNARM_COMBAT)) / 3;
         b1 = me->query_stat(SS_STR);
         b2 = me->query_stat(SS_DEX);
         pen = F_PENMOD(15+random(b1 / 10), skill+random(b2 / 10));
         
         hitresult = enemy->hit_me(pen, W_BLUDGEON, me, -1);
         perf = hitresult[2] * 100 / pen;
         pdam = hitresult[0];
         me->catch_msg("You do a Mae-Geri and get "+ptext1(perf)+" hit.\n"+
            QCTNAME(enemy)+" seems "+ptext2(pdam)+".\n");
         enemy->catch_msg(QCTNAME(me)+" does a Mae-Geri on you and gets "+
            ptext1(perf)+" hit.\n"+"You feel "+ptext2(pdam)+".\n");
         tell_watcher(QCTNAME(me)+ " does a Mae-Geri on "+QTNAME(enemy)+" and gets "+
            ptext1(perf)+" hit.\n"+QCTNAME(enemy)+" seems "+ptext2(pdam)+
            ".\n",me,enemy);
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return;
       }
      me->catch_msg("You try to do a Mae-Geri but miss.\n");
      enemy->catch_msg(QCTNAME(me)+" tries to do a Mae-Geri on you but misses.\n");
      return; /***  end of maegeri  ***/
   }
   /************************************************************************/
   if (me->query_prop(MONK_I_PREPARE)==ROUNDHOUSE)
      {
      /***  skills to determine succes/recovery  ***/
      skill=(me->query_skill(SS_FOCUS) * 7 +
         me->query_skill(SS_UNARM_COMBAT) * 4 +
         me->query_skill(SS_ACROBAT) * 3 +
         me->query_stat(SS_DEX) * 2) / 10;
      e_skill=(enemy->query_skill(SS_DEFENCE)) +
      (enemy->query_stat(SS_DEX) / 3);
      
      /*** how long does it take to recover ***/
      me->add_prop(MONK_I_PREPARE,WAITING);
    set_alarm(itof(MAX(6,PREPTIME(skill))), 0.0, &remove_prepare(me));
      
      /***  will we hit?  ***/
      if (random(skill*2) > random(e_skill))
         {
         skill = (me->query_skill(SS_FOCUS) * 2 +
            me->query_skill(SS_UNARM_COMBAT)) / 3;
         b1 = me->query_stat(SS_STR);
         b2 = me->query_stat(SS_DEX);
         pen = F_PENMOD(25+random(b1 / 5), skill+random(b2 / 10));
         
         hitresult = enemy->hit_me(pen, W_BLUDGEON, me, -1);
         perf = hitresult[2] * 100 / pen;
         pdam = hitresult[0];
         me->catch_msg("You do a roundhouse and get "+ptext1(perf)+" hit.\n"+
            QCTNAME(enemy)+" seems "+ptext2(pdam)+".\n");
         enemy->catch_msg(QCTNAME(me)+" does a roundhouse on you and gets "+
            ptext1(perf)+" hit.\n"+"You feel "+ptext2(pdam)+".\n");
         tell_watcher(QCTNAME(me)+ " does a roundhouse on "+QTNAME(enemy)+" and gets "+
            ptext1(perf)+" hit.\n"+QCTNAME(enemy)+" seems "+ptext2(pdam)+
            ".\n",me,enemy);
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return;
       }
      me->catch_msg("You try to do a roundhouse but miss.\n");
      enemy->catch_msg(QCTNAME(me)+" tries to do a roundhuse on you but misses.\n");
      return; /***  end of roundhouse  ***/
   }
   /************************************************************************/
   if (me->query_prop(MONK_I_PREPARE)==AXEKICK)
      {
      /***  skills to determine succes/recovery  ***/
      skill=(me->query_skill(SS_FOCUS) * 8 +
         me->query_skill(SS_UNARM_COMBAT) * 4 +
         me->query_skill(SS_ACROBAT) * 2 +
         me->query_stat(SS_DEX) * 2) / 10;
      e_skill=(enemy->query_skill(SS_DEFENCE)) +
      (enemy->query_stat(SS_DEX) / 3);
      
      /*** how long does it take to recover ***/
      me->add_prop(MONK_I_PREPARE,WAITING);
    set_alarm(itof(MAX(8,PREPTIME(skill)+3)), 0.0, &remove_prepare(me));
      
      /***  will we hit?  ***/
      if (random(skill*2) > random(e_skill*3))
         {
         skill = (me->query_skill(SS_FOCUS) * 2 +
            me->query_skill(SS_UNARM_COMBAT)) / 3;
         b1 = me->query_stat(SS_STR);
         b2 = me->query_stat(SS_DEX);
         pen = F_PENMOD(40+random(b1 / 3), skill+random(b2 / 10));
         
         hitresult = enemy->hit_me(pen, W_BLUDGEON, me, -1);
         perf = hitresult[2] * 100 / pen;
         pdam = hitresult[0];
         me->catch_msg("You do a jumping axe kick and get "+ptext1(perf)+" hit.\n"+
            QCTNAME(enemy)+" seems "+ptext2(pdam)+".\n");
         enemy->catch_msg(QCTNAME(me)+" does a jumping axe kick on you and gets "+
            ptext1(perf)+" hit.\n"+"You feel "+ptext2(pdam)+".\n");
         tell_watcher(QCTNAME(me)+ " does a jumping axe kick on "+QTNAME(enemy)+
            " and gets "+ptext1(perf)+" hit.\n"+QCTNAME(enemy)+" seems "+
            ptext2(pdam)+".\n",me,enemy);
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return;
       }
      me->catch_msg("You try to do a jumping axe kick but miss.\n");
      enemy->catch_msg(QCTNAME(me)+" tries to do a jumping axe kick on "+
         "you but misses.\n");
      return; /***  end of axekick  ***/
   }
   /************************************************************************/
}
