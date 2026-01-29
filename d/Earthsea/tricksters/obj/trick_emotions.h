/*
 * Creator: Ged
 * Date: 01.07.01
 * File: /w/ged/tricksters/trick_emotions.h
 * Comments: This is tricksters soul emotions header file
 * Revision history:
 * 
 */

#include <cmdparse.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"
#include "help.h"
#include "hex.h"

#define shuffles ({"Waymeet","Brandybuck","Hobbiton","Bree",\
                   "Frogmorton","Hardbottle","Nobish"})

mapping query_trick_emotions()
{
 return
   ([
     "armpit":"armpit",
     "barf":"barf",
     "bark":"bark",
     "bonk":"bonk",
     "caper":"caper",
     "coin":"coin",
     "flame":"flame",
     "hex":"hex",
     "help":"help",
     "hiss":"hiss",
     "hotfoot":"hotfoot",
     "innocent":"innocent",
     "juggle":"juggle",
     "meet":"meet",
     "nude":"nude",
     "seduce":"seduce",
     "shoestie":"shoestie",
     "shuffle":"shuffle",
     "sneaky":"sneaky",
     "tcackle":"tcackle",
     "tdown":"tumbdown",
     "tflex":"tflex",
     "tgrin":"tgrin",
     "thumbdown":"thumbdown",
     "thumbup":"thumbup",
     "tlaugh":"tlaugh",
     "tpeer":"tpeer",
     "tpray":"tpray",
     "tricklist":"tricklist",
     "trip":"trip",
     "tsmile":"tsmile",
     "tstring":"tstring",
     "ttrap":"ttrap",
     "tup":"thumbup",
     "vent":"vent",
     "wigg":"wigg"
   ]);
}


// =================== EMOTIONS ===================

// ==================== ARMPIT =====================

int armpit(string stam)
{
 me("You flex your muscles and sniff greedily in your right armpit.");
 all(" flexes "+POS(TP)+" muscles and sniffs greedily in "+POS(TP)+
     " right armpit."); 
 return 1;
}

// ============================ BARF =========================

int barf(string who)
{
 object *list;

 if(!who)
  {
   me("You barf all over the place, making a huge stinking mess!\n"+
         "Maybe you should stop hitting the bottle so hard?");
   all(" barfs all over, making a huge mess!  Maybe "+PRO(TP)+
       " should take it easy on the booze?");
   return 1;
  }  

 list=parse_this(who,"[over] [on] %l");
 NF("There is no such person to barf all over!\n");
 if(!sizeof(list)) return 0;

 actor("You barf on",list);
 target(" barfs all over you! How gross!",list);
 all2act(" barfs all over",list);

 return 1;
}

// =========================== BARK ==========================

int bark(string who)
{
 object *list;

 if(!who)
  {
   me("You bark like a mad dog.");
   all(" barks like a mad dog.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("There is no such person to bark on!\n");
 if(!sizeof(list)) return 0;

 actor("You bark at",list);
 target(" barks at you ferociously.",list);
 all2act(" barks ferociously at",list);

 return 1;
}

// ============================= BONK ============================

int bonk(string who)
{
 object *list;

 NF("Whom do you want to bonk?\n");
 if(!who) return 0;

 list=parse_this(who,"%l");
 NF("That person doesn't seem to be here.\n");
 if(!sizeof(list)) return 0;

 NF(BS("Bonking more than one person at the same time is rather "+
   "impossible to do.\n"));
 if(sizeof(list)>1) return 0;

 actor("You bonk",list," on the head with your large stick!");
 target(" bonks you on your head with "+POS(TP)+" large stick!",list);
 all2act(" bonks",list," on the head with "+POS(TP)+" large stick!");
 return 1;
}

// ========================== COIN ================================

int coin(string who)
{
 object *list;

 if(!who)
  {
   me("You flip a gold coin in the air, just to watch it turn.");
   all(" flips a gold coin high into the air and catches it again.");
   return 1;
  }

 list=parse_this(who,"[from] %l");
 if(!sizeof(list)) return 0;

 actor("You pull a platinum coin from the ear of",list);
 target(" suddenly pulls a platinum coin from behind your ear!",list);
 all2act(" suddenly pulls a platinum coin from the ear of",list);
 return 1;
}

// ============================= FLAME ==========================

int flame(string who)
{
 object *list;

 if(!who)
  {
   me("You make your own finger burst into flame!");
   all(" makes "+POS(TP)+" fingers burst into flames! ");
   return 1;
  }

 list=parse_this(who,"[to] %l");
 NF("Flame whom?\n");
 if(!sizeof(list)) return 0;

 actor("You wave your hands and set fire to",list);
 target(" waves "+POS(TP)+" hands, and you burst into flames!",list);
 all2act(" waves "+POS(TP)+" hands, and sets fire to",list);

 return 1;
}

// ========================= HOTFOOT =============================

int hotfoot(string who)
{
 object *list,hot_obj;
 int level,chance;
 string obj;

 NF("Give yourself a hotfoot? You must be crazy!\n");
 if(!who) return 0;
  
 list=parse_this(who,"[to] %l");
 NF("You don't see that person here.\n");
 if(!sizeof(list)) return 0;

 NF("Giving more than one person a hotfoot at the same time?\n"+
    "My aren't we talented.\n");
 if(sizeof(list)>1) return 0;

 NF("It's rather impossible to give someone a hotfoot if they are "+
   "already hopping around the room from one already!\n");
 if(list[0]->query_prop_setting("_trick_i_hotfoot")) return 0;

 chance=list[0]->query_stat(SS_WIS)/18+
        list[0]->query_skill(SS_AWARENESS)/8+random(10);
 level=TP->query_trickster_level();

 setuid();
 seteuid(getuid());
 if(level>chance)
  {
   actor("You sneak up behind",list," and light some material "+
     "underfoot in order to give "+OBJ(list[0])+" a hot foot.\n");
   list[0]->catch_msg("You feel an instense burning sensation on "+
     "your foot!!\n");
   all2act(" sneaks up behind",list," and lights something under "+
     "his foot!");
   hot_obj=clone_object(TRICKSTERS+"obj/hotfoot");
   hot_obj->move(list[0]);
   hot_obj->start();
  }
 else
  {
   obj=OBJ(list[0]);
   me(C(list[0]->query_the_name(TP))+" sees you sneaking up on "
     +OBJ(list[0])+" and gives you a swift kick preventing you "+
     "from giving "+OBJ(list[0])+" a hot foot.");
   list[0]->catch_msg("You notice "+TP->query_the_name(list[0])+
   " sneaking up behind you trying to play some trick on you.\n"+
   "You give "+OBJ(TP)+" a swift kick as a warning not to do this "+
   "again.\n");
   say(QTNAME(list[0])+" catches "+QTNAME(TP)+" sneaking up on "+obj+
     "and gives "+OBJ(TP)+" a swift kick so that "+PRO(TP)+" won't do "+
     "it again.\n",({TP,list[0]}));
  }

 return 1;
}

// ============================ HISS ============================

int hiss(string who)
{
 object *list;

 if(!who)
  {
   me("You hiss dangerously.");
   all(" hisses dangerously.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("Hiss at whom?\n");
 if(!sizeof(list)) return 0;

 actor("You hiss dangerously at",list);
 target(" hisses dangerously in your direction.",list);
 all2act(" hisses dangerously at",list);
 
 return 1;
}

// ========================= INNOCENT ==============================

int innocent(string who)
{
 object *list;
 string multi;
 
 if(!who)
  {
   me("You desperately try to look as innocent as you possibly can, "+
      "in hopes that it will fool all onlookers into believing that "+
      "you aren't responsible for what happened.");
   all("'s eyes start to shift from side to side and "+PRO(TP)+
       " starts to whistle a cheerful tune in a pitiful attempt to "+
       "look innocent.");
   return 1;
 }

 list=parse_this(who,"[to] %l");
 NF("Look innocent at whom?\n");
 if(!sizeof(list)) return 0;

 if(sizeof(list)>1) multi="they"; else multi=PRO(list[0]);
 
 actor("You desperately try to look as innocent as you can at",list,
       "in hopes that "+multi+" will believe you.");
 target(" looks at you with an innocent smile on "+POS(TP)+" face."
   ,list);
 all2act(" smiles at",list," with an innocent look on "+POS(TP)+
   " face.");

 return 1;
}

// ============================ JUGGLE ===========================

int juggle(string what)
{
 object *list;
 string desc;

 NF("Juggle what?\n");
 if(!what) return 0;

 list=FIND_STR_IN_OBJECT(what,TP);
 NF("There is no "+what+" here for you to juggle!\n");
 if(!sizeof(list)) return 0;

 desc=COMPOSITE_DEAD(list);
 if(TP->query_trickster_level()<random(35))
  {
   me("You fumble your attempt to juggle "+desc+".  Causing "+
     "everything to land on your head giving you a nasty bump!!\n"+
     "Ouch!!!");
   all(" fumbles "+POS(TP)+" attempt to juggle "+desc+".  Causing "+
     "everything to land on "+POS(TP)+" head!!!");
  }
 else
  {
   me("You skillfully juggled "+desc+".");
   all(" skillfully juggles "+desc+".\nYou marvel at "+POS(TP)+" skill.");
  }

 return 1;
}

// ============================= MEET ============================

int meet(string who)
{
 object *list;
 string pos,obj;

 NF("Meet whom?\n");
 if(!who) return 0;
 
 list=parse_this(who,"%l");
 NF("That person doesn't seem to be here.\n");
 if(!sizeof(list)) return 0;

 NF("It's rather difficult to meet more than one person at a time.\n");
 if(sizeof(list)>1) return 0;

 pos=POS(list[0]);obj=OBJ(list[0]);
 actor("You greet",list," with the tricky handshake.");
 target(" greets you, shaking your hand.\n"+
        "Ouch! "+C(PRO(TP))+" must have had a tack in "+POS(TP)+
        " hand!!!",list);
 all2act(" shakes",list,"'s hand, causing "+obj+" to wince, holding "+
         pos+" hand tenderly.");

 return 1;
}

// ============================ NUDE ============================

int nude(string who)
{
 object *list;

 if(!who)
  {
   me("You wave your hands and your pants fall down! Everyone laughs "+
      "at you!");
   all(" waves "+POS(TP)+" hands, and "+POS(TP)+" pants fall down!!\n"+
       "You fall down laughing.");
   return 1;
  }

 list=parse_this(who,"%l");
 NF("Embarrass whom?\n");
 if(!sizeof(list)) return 0;

 NF("Embarrass them all??? They might get mad at you!\n");
 if(sizeof(list)>1) return 0;

 if(TP->query_trickster_level()<random(35))
  {
   me("You fail to do the trick correctly, and your own pants "+
      "fall down.\nEveryone laughs at you.");
   all(" waves "+POS(TP)+" hands, and "+POS(TP)+" pants fall down!!\n"+
       "You fall down laughing.");
   return 1;
  }

 actor("You wave your hands, and embarrass",list);
 target(" waves "+POS(TP)+" hands and your pants fall down!\n"+
        "Everyone laughs at you.",list);
 all2act(" waves "+POS(TP)+" hands, and",list,"'s pants fall down!\n"+
         "You fall down laughing.");
 return 1;
}

// ============================= SEDUCE =========================

int seduce(string who)
{
 object *list;

 if(!who)
  {
   me("You try to look seductive.");
   all(" tries to look seductive.");
   return 1;
  }

 list=parse_this(who,"%l");
 NF("Seduce whom?\n");
 if(!sizeof(list)) return 0;

 actor("You whisper sweet words of love to",list);
 target(" tries to seduce you.",list);
 all2act(" tries to seduce",list);

 return 1;
}

// ========================= SHUFFLE ==============================

int shuffle(string who)
{
 object *list;
 int shuffle_type;

 shuffle_type=shuffles[random(6)];

 if(!who)
  {
   me("You do the "+shuffle_type+" shuffle!");
   all(" does the "+shuffle_type+" shuffle! You watch amazed!");
   return 1;
  }

 list=parse_this(who,"[with] %l");
 NF("Shuffle with whom?\n");
 if(!sizeof(list)) return 0;
 
 actor("You do the "+shuffle_type+" shuffle with",list);
 target(" does the "+shuffle_type+" shuffle with you!",list);
 all2act(" does the "+shuffle_type+" shuffle with",list,
         ".\nYou watch amazed!");

 return 1;
}

// =========================== TCACKLE ==========================

int tcackle(string who)
{
 me("You throw your head back and cackle with mischievous glee, "+
    "thoroughly enjoying all the mischief you have just caused.");
 all(" throws "+POS(TP)+" head back and cackles with mischievous glee, "+
     "reveling in all the mischief "+PRO(TP)+" has just caused.");
 return 1;
}

// ============================ TFLEX ===========================

int tflex(string who)
{
 object *list;
 int i;

 if(who) return 0;

 me("You flex your muscles to impress everyone.");
 all(" flexes "+POS(TP)+" muscles.");

 list=parse_this("all","%l");
 for(i=0;i<sizeof(list);i++)
  {
   if(TP->query_base_stat(0)>list[i]->query_base_stat(0))
     list[i]->catch_msg("WOW! Impressive!\n");
   else list[i]->catch_msg("You are not impressed at all.\n");
  }

 return 1;
}

// ========================= TGRIN ==============================

int tgrin(string param)
{
 object *list;
 string *adv;
 string how,who,multi;
 
 adv=parse_adverb(param,"wickedly",0);
 how=adv[1];who=adv[0];

 if(!who)
  {
   me("You grin "+how+", thinking of all the joys of being a "+
      "Trickster.");
   all(" grins "+how+", with a twinkle of mischief in "+POS(TP)+
       " eyes.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("Grin [how] at whom?\n");
 if(!sizeof(list)) return 0;

 if(sizeof(list)>1) multi="them"; else multi=OBJ(list[0]);
 
 actor("You grin "+how+" at",list,", thinking of all the nasty "+
       "tricks you could play on "+multi+".");
 target(" grins "+how+" at you, "+POS(TP)+" eyes sparkling with "+
        "mischief.",list);
 all2act(" grins "+how+" at",list,", with a mischievous twinkle in "+
         POS(TP)+" eyes.");
 return 1;
}

// ======================= THUMBDOWN ==========================

int thumbdown(string who)
{
 object *list;

 if(!who)
  {
   me("You turn your thumb downwards as a sign of disapproval.");
   all(" turns "+POS(TP)+" thumb downwards as a sign of disapproval.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 if(!sizeof(list)) return 0;
 
 actor("You turn your thumb downwards at",list,".");
 target(" turns "+POS(TP)+" thumb downwards in your direction.",list);
 all2act(" turns "+POS(TP)+" thumb down at",list,", as a sign of "+
         "disapproval.");

 return 1;
}

// =========================== THUMBUP ============================

int thumbup(string who)
{
 object *list;

 if(!who)
  {
   me("You hold up your thumb.");
   all(" holds up "+POS(TP)+" thumb.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 if(!sizeof(list)) return 0;

 actor("You hold up your thumb at",list,".");
 target(" holds up "+POS(TP)+" thumb in your direction.",list);
 all2act(" holds up "+POS(TP)+" thumb at",list,".");

 return 1;
}

// ============================= TLAUGH ===========================

int tlaugh(string who)
{
 object *list;

 if(!who)
  {
   me("You throw your head back and laugh mischievously, going into "+
      "a fit of hysterics.");
   all(" laughs until "+PRO(TP)+" turns red in the face and tears "+
       "stream down "+POS(TP)+" face.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("Laugh at whom?\n");
 if(!sizeof(list)) return 0;

 actor("You laugh, going into hysterics at the thought of",list,".");
 target(" points at you and laughs until "+PRO(TP)+" turns bright red!",
        list);
 all2act(" turns red in the face laughing at",list,".");

 return 1;
}

// ============================= TPEER ============================

int tpeer(string who)
{
 me("You peer mischievously around the area, searching fanatically "+
    "for your next victim.");
 all(" peers mischievously around the area, searching for something.");
 
 return 1;
}


// ========================== TRIP ==============================

int trip(string who)
{
 object *list;

 if(!who)
  {
   me("You trip over your own clumsy feet and fall down!\n"+
      "How embarassing!");
   all(" trips over "+POS(TP)+" own two feet and falls down.\n"+
       "You laugh uproariously.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("That person doesn't seem to be here.\n");
 if(!sizeof(list)) return 0;

 NF("Trying to trip more than one person?\nHow foolish of you.\n");
 if(sizeof(list)>1) return 0;

 actor("You trip",list," with a quick placement of your left foot.");
 target(" slips up next to you and trips you up.",list,
        "\nYou fall down rather gracelessly.");
 all2act(" trips",list," causing "+OBJ(list[0])+" to fall gracelessly "+
         "on "+POS(TP)+" backside.");
 
 return 1;
}

// ============================ TSMILE ============================

int tsmile(string who)
{
 object *list;
 string multi;

 if(!who)
  {
   me("You smile mischievously, day-dreaming of all the tricks you'll "+
     "be playing on some poor sucker today.");
   all(" smiles mischievously, with a queer gleam in "+POS(TP)+" eyes.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("Smile mischievously at whom?\n");
 if(!sizeof(list)) return 0;

 if(sizeof(list)>1) multi="they"; else multi=PRO(list[0]);
 actor("You smile mischievously at",list,", thinking of the perfect "+
   "prank to play on "+multi+".");
 target(" smiles mischievously at you, "+POS(TP)+" eyes filled with a "+
   "queer gleam.  You start to wonder what "+PRO(TP)+" is smiling about."
   ,list);
 all2act(" turns and smiles mischievously at",list," with a queer "+
   "gleam in "+POS(TP)+" eyes.");

 return 1;
}

// ============================ TSTRING ===========================

int tstring(string what)
{
 object *items,item,shad;
 string item_desc;
 int res;

 NF("But you've already attached your string to something!\n");
 if(TP->query_prop_setting("_trick_i_uses_string")) return 0;

 items=FIND_STR_IN_OBJECT(what,TP);

 NF("You find nothing to place your string on.\n");
 if(!sizeof(items)) return 0;
 
 NF("You can only trap one object at a time.\n");
 if(sizeof(items)>1) return 0;

 item_desc=COMPOSITE_DEAD(items);
 item=items[0];
 item->move(ENV(TP));
 setuid();
 seteuid(getuid());
 shad=clone_object(TRICKSTERS+"obj/tstring_shadow");
 res=shad->shadow_me(item);
 if(!res) write("Shadowing failed!!\n");
 item->add_prop("_trick_i_item_owner",TP);
 TP->add_prop("_trick_i_tstring_item_desc",item_desc);
 TP->add_prop("_trick_i_uses_string",1);

 me("You quickly attach a string to "+item_desc+" and place it on "+
    "the ground, hoping that some unknowing fool will come around to "+
    "entertain you.");
 all(" attaches something to "+item_desc+" and then carefully places "+
     "it on the ground infront of "+OBJ(TP)+".");
 
 return 1;
}

// ============================ VENT ===============================

void do_vent(string what)
{
 object victim,*all;
 string desc;
 int chance,level,i,noticed,my;

 desc=TP->query_prop_setting("_trick_i_item_desc");
 if(what=="")
  {
   me("You can't attempt to make "+desc+" say nothing!");
   return;
  }

 victim=TP->query_prop_setting("_trick_i_to_vent");
 all=parse_this("all","%l");

 chance=victim->query_stat(SS_WIS)/18+
        victim->query_skill(SS_AWARENESS)/8+random(10);
 level=TP->query_trickster_level();

 if(living(victim))
  {
   if(level>chance)
    {
     victim->command("say "+what);
     noticed=0;
     for(i=0;i<sizeof(all);i++)
      {
       chance=all[i]->query_stat(SS_WIS)/18+
              all[i]->query_skill(SS_AWARENESS)/8+random(10);
       if(level<=chance) 
        {
         all[i]->catch_msg(C(TP->query_the_name(all[i]))+
           "'s lips move slightly.\n");
         noticed=1;
        }
      }
     if (noticed)
       me("You think others might have caught on to you though.");
    }
   else
    {
     me(C(victim->query_the_name(TP))+" kicks you fanatically.   "+
       "OUCH!!!\n"+C(victim->query_the_name(TP))+
       " seems to have caught on to you.");
     victim->catch_msg(C(TP->query_the_name(victim))+
       " starts trying to imitate your voice.  "+
       "You quickly kick "+OBJ(TP)+" to put a stop to it.\n");
     say(C(QTNAME(victim))+" kicks "+QTNAME(TP)+" fanatically.\n",
       ({TP,victim}));
    }
  }
 else
  {
   my=TP->query_prop_setting("_trick_i_my_item");
   if(my)
    {
     me("You try to make others believe that "+desc+" you holding "+
       "says: "+what);
     say("A voice coming from "+desc+" says: "+what+"\n");
    }
   else
    {
     me("A voice coming from "+desc+" says: "+what);
     say("A voice coming from "+desc+" says: "+what+"\n");
    }

   noticed=0;
   for(i=0;i<sizeof(all);i++)
    {
     chance=all[i]->query_stat(SS_WIS)/18+
            all[i]->query_skill(SS_AWARENESS)/8+random(10);
     if(level<=chance) 
      {
       all[i]->catch_msg(C(TP->query_the_name(all[i]))+
         "'s lips move slightly.\n");
       noticed=1;
      }
    }
   if(noticed)
     me("You think others might have caught on to you though.");
  }

 TP->remove_prop("_trick_i_to_vent");
 TP->remove_prop("_trick_i_my_item");
 TP->remove_prop("_trick_i_item_desc");
}


int vent(string who)
{
 object *list,*list1;
 int my;
 string desc;

 NF("Who do you wish to ventriloquize?\n");
 if(!who) return 0;

 list=parse_this(who,"%l");
 list1=FIND_STR_IN_OBJECT(who,TP);
 my=1;
 if(!sizeof(list1)) 
  {
   list1=FIND_STR_IN_OBJECT(who,ENV(TP));
   my=0;
  }
 NF("No such person bub!\n");
 if(!sizeof(list) && !sizeof(list1)) return 0;

 NF("Yeah , right! Let's vent them all!! don't be silly!\n");
 if(sizeof(list)>1) return 0; 

 if(!sizeof(list1)) 
  {
   desc=list[0]->query_the_name(TP);
   TP->add_prop("_trick_i_to_vent",list[0]);
   TP->add_prop("_trick_i_item_desc",desc);
   me("Okay, what do you want to say through "+desc+"?");
  }
 else 
  {
   desc=COMPOSITE_DEAD(list1);
   TP->add_prop("_trick_i_to_vent",list1[0]);
   TP->add_prop("_trick_i_my_item",my);
   TP->add_prop("_trick_i_item_desc",desc);
   me("Okay, what do you want to say through "+desc+"?");
  }
 input_to(do_vent);
 return 1;
}

// ========================== WIGG =============================

int wigg(string who)
{
 object *list;

 if(!who)
  {
   me("You wiggle your fingers dangerously.");
   all(" wiggles "+POS(TP)+" fingers dangerously.");
   return 1;
  }

 list=parse_this(who,"[at] %l");
 NF("Wiggle your fingers at whom?\n");
 if(!sizeof(list)) return 0;

 actor("You wiggle your fingers at",list,".");
 target(" wiggles "+POS(TP)+" fingers dangerously in your "+
   "general direction.",list);
 all2act(" dangerously wiggles "+POS(TP)+" fingers at",list,".");

 return 1;
}


// ============================== CAPER =============================

int caper(string param)
{
 string *adv;
 string how,what,multi;
 
 adv=parse_adverb(param,"wildly",0);
 how=adv[1];what=adv[0];

 if(!what)
  {
   me("You caper "+how+" around.");
   all(" capers "+how+" around.");
   return 1;
  }

 me("You caper "+how+" around about "+what+".");
 all(" capers "+how+" around about "+what+".");

 return 1;
}

int shoestie(string who)
{
 object *list,tie,tie_sh;
 int level,chance;

 NF("Tie whos shoelaces?\n");
 if(!who) return 0;

 list=parse_this(who,"%l");

 NF("There's no such person here!\n");
 if(!sizeof(list)) return 0;

 NF("Not all of them! No no no!\n");
 if(sizeof(list)>1) return 0;

 chance=list[0]->query_stat(SS_WIS)/18+
        list[0]->query_skill(SS_AWARENESS)/8+random(10);
 level=TP->query_trickster_level();

 NF(C(PRO(list[0]))+"'s in fight! How do you expect to sneak up on "+
   OBJ(list[0])+"?\n");
 if(list[0]->query_enemy()) return 0;

 if(level>chance)
  {
   NF("Uhm... Laces on "+POS(list[0])+" shoes are already tied!\n");
   if(present("_trickster_tie_object_",list[0])) return 0;

   actor("You sneak down and tie laces on",list,"'s shoes.");
   all2act(" sneaks down and ties laces on",list,"'s shoes.");
   setuid();
   seteuid(getuid());
   tie=clone_object(TRICKSTERS+"obj/tie_object");
   tie->move(list[0]);
   tie->get_exits();
   tie_sh=clone_object(TRICKSTERS+"obj/tie_shadow");
   tie_sh->shadow_me(list[0]);
  }
 else
  {
   actor("You sneak down to tie laces on",list,"'s shoes , but "+
     PRO(list[0])+" notices the attempt and gives you swift kick "+
     "to prevent it");
   list[0]->catch_msg("You notice "+TP->query_the_name()+" trying to "+
     "tie laces on your shoes and give "+OBJ(TP)+" a swift kick, "+
     "as a warning not to try that again.\n");
   say(QTNAME(list[0])+" catches "+QTNAME(TP)+" sneaking up on "+
     OBJ(list[0])+"and gives "+OBJ(TP)+" a swift kick so that "+
     PRO(TP)+" won't do it again.\n",({TP,list[0]}));
  }

 return 1;
}

// ============================== TTRAP ==========================

int ttrap(string where)
{
 string *exit;
 object *trap,trap_ob;
 int i;

 NF("Set trap at what exit?\n");
 exit=ENV(TP)->query_exit_cmds();
 if(member_array(where,exit)==-1) return 0;

 trap=FIND_STR_IN_OBJECT("_trickster_trap_",ENV(TP));
 NF("You try to set a trap to "+where+", but suddenly notice another "+
   "trap set there!\n");
 for(i=0;i<sizeof(trap);i++)
  {
   if(trap[i]->query_trap_exit()==where)
    {
     trap[i]->add_aware(TP);
     return 0;
    }
  }

 NF("You must be hidden to set a trap!\n");
 if(!TP->query_prop_setting(OBJ_I_HIDE)) return 0;

 setuid();
 seteuid(getuid());
 trap_ob=clone_object(TRICKSTERS+"obj/trick_trap");
 trap_ob->move(ENV(TP));
 trap_ob->add_aware(TP);
 trap_ob->set_trap_exit(where);
 trap_ob->set_trap_level(TP->query_trickster_level());
 me("You cut some of the string and stretch it to block "+where+
   " exit of the room.\nYou giggle mischievously in thoughts of poor "+
   "one who's gonna stumble over the trap.");
 return 1;
}

// ========================== SNEAKY ==========================

int sneaky(string how)
{
 NF("Sneaky how? on? off? constant?\n");
 if(!how) return 0;
 if(how!="constant" && how!="on" && how!="off") return 0;

 if(how=="on")
  {
   write("You will not introduce yourself as a Trickster, "+
     "nor will you look like one.\n");
   TP->set_incognito(1);
   return 1;
  }

 if(how=="off")
  {
   write("You will be sneaky no longer.\n");
   TP->set_incognito(0);
   return 1;
  }

 if(how=="constant")
  {
   if(TP->query_autosneak())
    {
     write("You shall no longer constantly sneak around.\n");
     say(QCTNAME(TP)+" lets out sigh of disappointment , as "+
       PRO(TP)+" won't be sneaking around anymore.\n");
     TP->set_autosneak(0);
     return 1;
    }

   write("You are now constantly sneaking.\n");
   say(QCTNAME(TP)+" grins mischievously as "+PRO(TP)+" prepares "+
     "to sneak around.\n");
   TP->set_autosneak(1);
   return 1;
  }

 return 0;
}

// ======================= TRICKLIST ===========================

int tricklist()
{
 object *tr;
 string *members;
 int i;
 string full_title;

 tr=({});members=(SERVER)->get_members();
 for(i=0;i<sizeof(members);i++)
   if(find_player(members[i])) tr+=({find_player(members[i])});
 tr=sort_array(tr,"order_members",TO);

 write("These Tricksters are around somewhere:\n");
 for(i=0;i<sizeof(tr);i++)
  {
   if(!interactive(tr[i])) continue;

   if(tr[i]->query_wiz_level())
    {
     if(tr[i]->query_invis() && TP!=tr[i] && !TP->query_wiz_level()) 
       continue;
     full_title=tr[i]->query_title();
    }
   else 
    {
     full_title=tr[i]->query_trickster_title();
     if(TP->query_wiz_level()) 
       full_title+=sprintf(" (level %d)",tr[i]->query_trickster_level());
    }

   write("- "+tr[i]->query_name()+" the "+full_title+"\n");
  }

 return 1;
}

int order_members(object a, object b)
{
  int alv = a->query_trickster_level();
  int blv = b->query_trickster_level();

  return (alv > blv ? -1 : (alv == blv ? 0 : 1));
}

// ========================== TPRAY ==============================

int tpray(string stam)
{
 object *al;
 int i;

 al=parse_this("all","%l");

 me("You concentrate and mumble a dark prayer to Kina.");
 all(" concentrates and with a dark glimpse in "+POS(TP)+" eyes "+
   "mumbles some kind of a prayer.");

 for(i=0;i<sizeof(al);i++) 
   if(STAT(al[i],SS_DIS)/7<=TP->query_trickster_level())
     al[i]->command("shiver");

 return 1;
}

