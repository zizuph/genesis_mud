#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

#pragma save_binary

inherit "/std/monster";

coffee(object tp);
dest_coffee(object ob);
gettired();
heal(string s);
remove_int();
#define GOT_NASTY_DISEASE "Poor_TP_Got_A_Nasty_Disease"
#define LOGLIB "d/Roke/motorhead"
int has_introduced=0;
int refreshed=0;

create_monster()
{
   int i;
   if(!IS_CLONE)
      return;
   
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   
   set_name("jhonlee");
   add_name("healer");
   set_living_name("jhonlee");
   set_long("This is an old man, wearing white robes and some kind of harp or\n"+
      "maybe a zither. His appearance radiates ancient wisdom and magic.\n"+
      "He has obviously returned from his journey to The Other Side.\n");
   set_title("ancient master of magical arts and knowledges");
   set_race_name("human");
   set_gender(0);
   for (i = 0; i < 6; i++)
   set_base_stat(i, 100);
   set_alignment(50);
   set_skill(SS_UNARM_COMBAT, 50); 
   set_all_attack_unarmed(50, 50);
   add_act("emote looks tired and tries to avoid to fall asleep.");
   add_act("emote mumbles something about dwarves.");
   add_act("say There is not so much mystery in the world as it used to be.");
   add_act("say Chastity could be the solution to your problems.");
   add_act("say I've seen so much violence and diseases. I can cure but a few.");
   add_act("yawn");
   add_act("emote mumbles something about coffee made for kings.");
   set_act_time(7);
   trig_new("%w 'introduces' %s","react_introduce");
   /*    ::create_monster(); */
   
   trig_new("%w 'gives' 'you' 'a' 'cup' 'of' 'coffee.\n' %s" , "coff");
   trig_new("%w 'says:' 'help\n' %s" , "hea");
   trig_new("%w 'says:' 'help' %s","hea");
   trig_new("%w 'says:' 'healing\n' %s","hea");
   trig_new("%w 'says:' 'cure\n' %s","hea");
   trig_new("%w 'says:' 'cure' %s","hea");
   trig_new("%w 'says:' 'disease\n' %s","hea");
   trig_new("%w 'says:' 'disease' %s","hea");
   
   add_ask(({"cure","heal","healing","help","heal me",
            "help me"}),VBFC_ME("hea"));
}

coff()
{
  set_alarm(1.0, 0.0, &coffee(TP));
   return 1;
}

coffee(object tp)
{
   object ob;
   
   set_this_player(tp);
   
   if(!(ob=present("real_coffee",TO)))
      {
      command("emote obviously doesn't enjoy the gift.");
      return 1;
   }
   tell_room(E(tp), "The old man greedily accepts the cup of coffee from the hands\n" +
      "of "+QCTNAME(tp)+". He drinks it in a few long pulls and looks really\n" +
      "refreshed. His eyes glistens with wisdom and magical knowledge.\n" +
      "'Right!' he says, 'Now, what seems to be the problem?'\n");
  set_alarm(10.0, 0.0, &dest_coffee(ob));
   refreshed=1;
  set_alarm(2000.0, 0.0, gettired);
   return 1;
}

dest_coffee(object ob)
{
   ob->remove_object();
   return 1;
}

hea()
{
   set_alarm(1.0, 0.0, &heal(TP));
   return "";
}
enter_inv(object ob,object nob)
{
   ::enter_inv(ob,nob);
   
   if(!nob)
      return;
   
   if(ob->query_name()!="cup")
      {
    set_alarm(1.0, 0.0, &command("emote returns "+ob->short()+"."));
      ob->move(nob);
   }
}
heal(string s)
{
   object ob1, ob2;
   string *Genderlist = ({"son" , "daughter" , "dear thing"});
   if (refreshed) 
      {
      if(TP->neuterized())
         {
         command("say I'm sorry, dear thing, but it doesn't seem like I");
         command("say can do anything for you. You better find a");
         command("say sorcerer to take care of your problems");
         return 1;
       }
      if(TP->query_prop(GOT_NASTY_DISEASE))
         { if((ob1=present("log", TP) && (ob2=present("mm_badge",TP))))
            { 
            cure();
            return 1;
         }
         if((ob1=present("log", TP)))
            {
            command("say You have brought the staff, I see.");
            command("say But I need a proof that your heart is pure, too.");
            command("say You should join the fight against immoralties.");
            command("say Then return and ask for healing again.");
            return 1;
         }
         
         tell_room(E(TO),"Jhonlee looks at you.\n'My friend, you have fallen deep into the black pit of Sin.\n"+
            "There is cure for your problems, but it's not easily obtained.\n"+
            "I need two items to be able to help you.' he says.\n"+
            "I need the aid of an old friend of mine. He used to walk around in\n"+
            "the forests of Gont. His goes by the name of Furnak.  He\n"+
            "carries with him a staff made of Holy Oak. Tell him I send you. That item I need. And I need"+
            " a proof that your heart is pure and free from sin.\n"+
            "Then return here and ask for healing again.\n");
         return 1;
       }
      tell_room(E(TO), "Jhonlee declares: Help? I can bring but guidance my "+
         Genderlist[TP->query_gender()] +". Stay away from sin\n" +
         "and your soul will be saved. Otherwise, you might perish, my child.\n");
      return 1;
   }
   tell_room(E(TO),"The old human falls asleep in front of you. Maybe he could\n" +
      "use a cup of coffee.\n");
   return 1;
   
}

void
introduce_me()
{
   command("introduce myself");
}

void
remove_int()
{
   has_introduced=0;
}

void
react_introduce(string person,string who)
{
   if (!has_introduced)
      {
      has_introduced=1;
     set_alarm(3.0, 0.0, introduce_me);
      
      set_alarm(30.0, 0.0, remove_int);
   }
}

gettired()
{
   refreshed=0;
   return 1;
}

cure()
{
   object ob , virus;
   ob=present("log",TP);
   tell_room(E(TO), "Jhonlee shreds the staff to pieces with his fingernails,\n" +
      "tosses them into the fire and chants in some ancient tounge.\n");
   
   ob->remove_object();
   
   virus=present("virus", TP);
   tell_room(E(virus), "You feel your evil disease scatter in the wind. You feel\n"+
      "free and your strength returns quickly.\n");
   virus->remove_object();
   TP->remove_prop(GOT_NASTY_DISEASE);
   command("say Now don't you ever get infected like that again, you hear me?!");
   ROKE_LOG("infected","Healed "+capitalize(TP->query_real_name())+"\n");
   
   return 1;
}


