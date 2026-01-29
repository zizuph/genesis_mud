/*
ROOM: Fire Brigade bedroom of the firemen
BY: Korat
DATE: Jun 20, 1995
*/

inherit "/d/Kalad/room_std";

#include <filter_funs.h>
#include "/d/Kalad/defs.h"

#define QUEST_NAME "firequest"
#define NEXT_ROOM "/d/Kalad/common/central/plaza/test/fb_rm21"
int room_normal;
int room_inferno;
int room_ruined;
int man_living;
int water;
int quest_done;
object *throwers;
int kill_man_alarm;
int stop_inferno_alarm;
int emote_alarm;


enter_inv(object ob,object from)
{
   if(quest_done && member_array(ob,throwers))
      {
      set_alarm(1.0,0.0,"give_exp",ob);
   }
   if(living(ob))
      {
      ::enter_inv(ob,from);
      if (!emote_alarm)
         emote_alarm=set_alarm(10.0,10.0,"emotes");
      return;
   }
   if(!room_inferno)
      {
      ::enter_inv(ob,from);
      return;
   }
   if(ob->query_short()=="litre of water")
      {
      ::enter_inv(ob,from);
      set_alarm(2.0,0.0,"check_water",ob,from);
      return;
   }
   if(ob->query_short()=="wooden bucket")
      {
      ::enter_inv(ob,from);
      set_alarm(2.0,0.0,"check_water",ob,from);
      return;
   }
   ::enter_inv(ob,from);
   tell_room(TO,"The "+short(ob)+" is soon consumed by the "+
      "flames!\n");
   set_alarm(1.0,0.0,"remove_object",ob);
}

leave_inv(object ob, object from)
{
   object *people;
   people=FILTER_LIVE(all_inventory(TO));
   if(sizeof(people)==1)
      {
      remove_alarm(emote_alarm);
   }
   ::leave_inv(ob,from);
   return;
}

void
create_room()
{
   ::create_room();
   room_normal = 1;
   set_alarm(0.0,0.0,"reset_room");
   hear_bell = 2;
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_short("@@short@@");
   set_long("@@long@@");
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(plaza/test/fb_rm21), "west", 0, 0, 0);
   
   add_item(({"beds", "bunkbeds"}),  
      "@@beds@@");
   add_item("candle","@@candle@@");
   add_item("smoke","@@smoke@@");
   add_item(({"fire","flames","flame","inferno"}),
      "@@fire@@");
}

init()
{
   ::init();
   add_action("save_man","rescue");
   add_action("ext_fire","extinguish");
   add_action("ext_fire","douse");
   add_action("ext_fire","blow");
}

save_man(string str)
{
   if(!room_inferno)
      {
      NF("What?\n");
      return 0;
   }
   if(man_living)
      NF("You try to save him, but fail. The flames and smoke has created a "+
      "barrier between you and him!\n");
   else
      NF("Save a corpse?? You are too late...\n");
   return 0;
}

ext_fire(string str)
{
   NF("What?\n");
   if(!room_inferno) return 0;
   NF("You try to extinguish the fire, but fail. The smoke and flames "+
      "makes doing anything in here both impossible and very dangerous!\n");
   return 0;
}

short()
{
   if(room_normal) return "the firemens bedroom";
   if(room_inferno) return "an inferno of flames and black "+
      "smoke that chokes you.";
   if(room_ruined) return "a room destroyed by an extinguished fire";
}

long()
{
   if (room_normal)
      return "You are on the second floor of the fire brigade, in the bedroom of "+
   "all the firemen. There are some bunkbeds standing against the wall "+
   "and it seems that they are filled by firemen, judging from the "+
   "snores. Except from the bunkbeds all you see here is a table "+
   "with some papers, books and a small candle on it.\n";
   if(room_inferno)
      return "This room is an inferno of dark, "+
   "strangling smoke and orange, vicious flames that curls "+
   "themselves around the walls and along the ceiling.\n";
   if(room_ruined)
      return "This place is a havock. The walls, all the furniture "+
   "along with the ceiling are all blackened from some "+
   "extinguished fire. The acidious smell "+
   "makes you want to leave as soon as possible.\n";
}

candle()
{
   if(room_normal)
      return "Its a simple candle, placed neatly on the table to "+
   "provide light for reading. The small flame casts off "+
   "a small streak of smoke that slowly curls itself towards "+
   "the roof.\n";
   if(room_inferno) return "The heat is too burning and the smoke "+
      "makes your eyes water, so you cannot really see anything in here.\n";
   if(room_ruined) return "You don't see any candle here.\n";
}

beds()
{
   if(room_normal)
      return "The beds are occupied by some firemen. No wonder "+
   "people complain about the lousy service this station "+
   "provides.\n";
   if(room_inferno)
      return "The flames have not yet reached the beds. "+
   "At least you think so, because you can hear some "+
   "muffeled noises from them...\n";
   if(room_ruined)
      return "Well, they were once beds...now they have several "+
   "marks of being consumed by flames..\n";
}
smoke()
{
   if(room_normal || room_ruined)
      return "You see no smoke here.\n";
   return "The black smoke fills your nose, mouth and lungs, "+
   "making it extremely hard to breath. It will kill "+
   "you if you stay...\n";
}

fire()
{
   if (room_normal || room_ruined)
      return "You see no flames here.\n";
   return "The flames licks the walls and the ceiling, slowly "+
   "consuming it all. Now and then they burst up and "+
   "envelope you too! This will surely be your death "+
   "if you stay!\n";
}

reset_room()
{
   if(room_inferno) return;
   room_normal = 1;
   room_inferno = 0;
   room_ruined = 0;
   if(room_ruined)
      {
      tell_room(TO,"Some firemen arrives and fixes the place up. "+
         "Soon the room seems like new, and the firemen collapses on the "+
         "bunkbeds.\n");
   }
}

emotes()
{
   if(room_normal)
      {
      switch (random(4))
      {
         case 0:
         tell_room(TO,"The candle fizzles a bit.\n"); break;
         case 1:
         tell_room(TO,"The flame of the candle flickers slightly.\n");
         break;
         case 2:
         tell_room(TO,"Small shadows play on the wall behind you, reflected "+
            "from the candles light.\n"); break;
         case 3:
         tell_room(TO,"One of the firemen moves in his sleep.\n");
         break;
         default: break;
      }
      if(random(5)==1)
         {
         set_alarm(0.0,0.0,"burn_room");
      }
      return;
   }
   if(room_inferno)
      {
      switch (random(3))
      {
         case 0:
         tell_room(TO,"Some flames suddenly bursts out and burns you badly!\n");
         set_alarm(1.0,0.0,"fire_damage",1);
         break;
         case 1:
         tell_room(TO,"You cough loudly as the black smoke slowly strangles you!\n");
         set_alarm(1.0,0.0,"fire_damage",2);
         break;
         case 2:
         tell_room(TO,"For a brief moment you think you will "+
            "perish here, with your body getting slowly consumed by the "+
            "flames until only the ashes are left.\n");
         set_alarm(1.0,0.0,"fire_damage",0);
         break;
         default: break;
      }
      return;
   }
   if(room_ruined)
      {
      switch (random(3))
      {
         case 0:
         tell_room(TO,"A wift of burned flesh makes you want to puke.\n");
         break;
         case 1:
         tell_room(TO,"The draft removes for a swift moment the acidious smell.\n");
         break;
         case 2:
         tell_room(TO,"A small streak of smoke drifts slowly up into the air from "+
            "the burned remains of a table.\n");
         break;
         default: break;
      }
      return;
   }
}

fire_damage(int what)
{
   object *people;
   int i;
   people = FILTER_LIVE(all_inventory(TO));
   for (i=0;i<sizeof(people);i++)
   {
      switch (what)
      {
         case 0:
         people[i]->add_panic((people[i]->query_stat(SS_DIS)/5)*10);
         people[i]->catch_msg("You really feel more nervous!\n");
         break;
         
         case 1:
         people[i]->heal_hp(-(people[i]->query_max_hp()/5));
         people[i]->catch_msg("You get very badly burned!!\n");
         if(people[i]->query_hp()<=0)
            {
            people[i]->catch_msg("The flames envelope your body, "+
               "igniting your hair, eyebrows and slowly starts to "+
               "cremate your body. You feel your lifeforce "+
               "being drained away...\n");
            if(sizeof(throwers)>0 &&
                  member_array(people[i],throwers))
            throwers = throwers-({people[i]});
            people[i]->do_die(TO);
            tell_room(NEXT_ROOM,"You hear a loud scream from "+
               "the east, that slowly fades away...someone died.\n");
              }
         break;
         
         case 2:
         people[i]->add_mana(-(people[i]->query_max_mana()/5));
         people[i]->catch_msg("You feel very drained, making "+
            "it harder to think...\n");
         if(random(5)==0)
            people[i]->catch_msg("You loose conscience.\n");
         else
            people[i]->catch_msg("You almost lost conscience.\n");
         break;
         
         default: break;
      }
   }
   if(!random(3)) tell_room(TO,"You think you heard a noise of pain from "+
         "one of the bunkbeds!\n");
}


burn_room()
{
   water = 0;
   man_living=1;
   quest_done = 0;
   throwers = ({});
   tell_room(TO,"Suddenly the candle falls down...\n");
   tell_room(TO,"The small flame ignites the papers on the table!\n");
   set_alarm(2.0,0.0,"burn2");
   set_alarm(4.0,0.0,"burn3");
   set_alarm(7.0,0.0,"burn4");
   set_alarm(9.0,0.0,"burn5");
   set_alarm(11.0,0.0,"burn6");
   room_inferno = 1;
   room_normal = 0;
   room_ruined = 0;
   stop_inferno_alarm=set_alarm(120.0,0.0,"stop_inferno");
   kill_man_alarm=set_alarm(80.0,0.0,"kill_man");
}

burn2()
{
   tell_room(TO,"The flames starts to grow, igniting come clothes...\n");
}
burn3()
{
   tell_room(TO,"A man screams loudly from one of the beds!\n");
   tell_room(TO,"Someone shouts: Fiiiiireeeeee! RUUUNNN!!\n");
   tell_room(NEXT_ROOM,"Someone shouts: Fiiiiireeeeee! RUUUNNN!!\n");
}
burn4()
{
   tell_room(TO,"The flames licks the walls, growing in a terrible speed! "+
      "The heat almost knocks you down; Your lung are filled with the black "+
      "smoke that slowly envelopes the room ...\n");
   tell_room(NEXT_ROOM,"An intense heat bellows out from the room east of you.\n");
}
burn5()
{
   tell_room(TO,"Some men runs past you, gasping for air, out the door.\n");
   tell_room(NEXT_ROOM,"Some men comes running out of the room "+
      "east of you, gasping for air.\n");
}
burn6()
{
   tell_room(TO,"A man shouts weakly from one of the bunkbeds: "+
      "I am trapp ... ed! Heeell ... p ... meee.\n");
   tell_room(NEXT_ROOM,"You hear a weak shout from the room east "+
      "of you: I am trapp ... ed! Heeell ... p ... meee.\n");
   tell_room(NEXT_ROOM,"The men goes ack!\n");
   tell_room(NEXT_ROOM,"The men shouts and panics: 'Save our friend! "+
      "Extinguish that fire, faaast! Waaaterrrr!! He's trapped in "+
      "there!' ... and runs away in panic. It seems you are stuck here "+
      "to deal "+
      "with it.\n");
   tell_room(TO,"Some men shouts and panics in the room next to you: "+
      "'Save our friend! Extinguish that fire faaast! Waaaaterrrr!! He's "+
      "trapped in there!' ... and runs away. You realise you are stuck "+
      "with the situation.\n");
}

stop_inferno()
{
   tell_room(TO,"Some buckets comes flying in, with water in them..."+
      "Not very effective, but there is enough buckets to extinguish the "+
      "flames. Too late to save the man though...he died.\n");
   tell_room(NEXT_ROOM,"Some men comes running into the room "+
      "and throws both buckets and the water in them, east. "+
      "Not very effective though, but enough to extinguish the fire. "+
      "Too late to save the man though...he died.\n");
   room_normal = 0;
   room_inferno = 0;
   room_ruined = 1;
   water = 0;
   throwers = ({});
   quest_done = 0;
   man_living = 1;
}

kill_man()
{
   man_living = 0;
   tell_room(TO,"You hear a chilling death-scream voice up and then "+
      "to slowly fade away. The trapped man died.\n");
   tell_room(NEXT_ROOM,"You suddenly hear a chilling scream voice up "+
      "east of you, and then it slowly fades away. "+
      "The trapped man must have died.\n");
}

check_water(object what,object who)
{
   if(!what) return;
   if(!who) return;
   if(what->query_name()=="water")
      {
      water=water+1;
      throwers=throwers+who;
      if(water==2)
         {
         if(kill_man_alarm) remove_alarm(kill_man_alarm);
         remove_alarm(stop_inferno_alarm);
         tell_room(TO,"The fire seems to be extinguished...\n");
         tell_room(NEXT_ROOM,"You can hear some fizzling from the east ... "+
            "and then everything becomes quiet. The fire is extinguished!\n");
         quest_done = 1;
      }
      else
         {
         tell_room(TO,"The water extinguishes parts of the fire!\n");
         tell_room(NEXT_ROOM,"You can hear some fizzling from "+
            "the east ... seems like parts of the fire was "+
            "extinguished!\n");
      }
      return;
   }
   if(what->query_name()=="bucket")
      {
      if(what->query_prop("water_inside"))
         {
         tell_room(TO,"The bucket catches fire, but the water in it "+
            "manages to extinguish it...but not much else.\n");
         what->set_prop("water_inside",0);
         return;
      }
      else
         {
         tell_room(TO,"The bucket catches fire and is soon "+
            "consumed...\n");
         what->remove_object();
         return;
      }
   }
}

give_xp(object who)
{
   tell_room(TO,"Giving some xp...\n");
}
