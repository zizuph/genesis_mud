#pragma save_binary

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include <wa_types.h>

#define HANGING_TIME random(120) + 300

//   Prototypes
void remove_snare_object();
void timeout();
void checks();
void hurt_me(object player);

static int Hang_time, Check_time;
static object Victim;

void
create_object()
{
   set_name("trickster_hang_object");
   set_short("you should never see this");
   set_long("Trickster snaring object\n");
   set_no_show();
   remove_prop(OBJ_I_WEIGHT);
   remove_prop(OBJ_I_VOLUME);
   remove_prop(OBJ_I_VALUE);
   add_prop(OBJ_M_NO_GET,"@@myget@@");
}

string
myget()
{
   return query_verb() + " what?\n";
}

void
init()
{
   string *exits;
   int i;
   
   ::init();
   if (TP != Victim)
      {
      add_action("cut","cut");
      return;
   }
   exits = ENV(Victim)->query_exit_cmds();
   for (i = 0; i < sizeof(exits); i++)
   {
      add_action("no_go",exits[i]);
   }
   add_action("no_go","sneak");
   add_action("cut","cut");
}

void
hang(object player)
{
   object original_room;
   
   Victim = player;
   Victim->add_prop(LIVE_S_EXTRA_SHORT, " is hanging upside-down from a rope");
   Hang_time = set_alarm(itof(HANGING_TIME),0.0,&timeout());
   Check_time = set_alarm(20.0,20.0,checks);
   return;
}

void
remove_snare_object()
{
   remove_object();
}

void
remove_object()
{
   remove_alarm(Check_time);
   remove_alarm(Hang_time);
   Victim->remove_prop(LIVE_S_EXTRA_SHORT);
   ::remove_object();
}

void
timeout()
{
   tell_room(ENV(TO), "The rope suspending "+QTNAME(Victim)+" in the "+
      "air finally gives, sending "+HIM_HER(Victim)+" sprawling to the "+
      "ground and landing on "+HIS_HER(Victim)+" head!\n\nOuch!!\n",Victim);
   write("The rope finally gives way and you fall to the ground head "+
      "first!!!\n\nOuch!!\n");
   hurt_me(Victim);
   remove_snare_object();
}

int
no_go(string str)
{
   write("You are stuck hanging from a rope and can not " +
      "move till you figure out how to free yourself!\n");
   tell_room(ENV(TO), QCTNAME(Victim)+" struggles madly to free "+
      HIM_HER(Victim)+"self from the rope which binds "+HIM_HER(Victim)+
      ".\n",Victim);
   return 1;
}

int
cut(string str)
{
   int i;
   object *weapons = TP->query_weapon(-1);
   
   if (str != "rope")
      {
      if (TP == Victim)
         notify_fail("Cut the rope to free yourself maybe?\n");
      else
         notify_fail("Cut what?\n");
      return 0;
   }
   for (i = 0 ; i < sizeof(weapons) ; i++)
   {
      if (weapons[i]->query_dt() & W_SLASH)
         {
         if (TP == Victim)
            {
            write("You manage to cut yourself free from the rope, causing you "+
               "to fall and land directly on your head!\n\nOuch!!\n");
            tell_room(ENV(TO), QCTNAME(Victim)+" manages to cut "+
               HIM_HER(Victim)+ "self free from the rope. Causing "+
               HIM_HER(Victim)+ " to fall on their head!!\n\nOuch, "+
               "that's got to hurt!\n",Victim);
          }
         else
            {
            TP->catch_msg("You manage to cut "+QTNAME(Victim)+" free "+
               "from the rope that was holding "+HIM_HER(Victim)+".\n");
            Victim->catch_msg(QCTNAME(TP)+" cuts you free from "+
               "the rope which was holding you, causing you to land "+
               "on your head!\n\nOuch!!! That hurt!\n");
            tell_room(ENV(TO), QCTNAME(TP)+" cuts down "+
               QTNAME(Victim)+" from the rope which was holding "+
               HIM_HER(Victim)+" in the air.\n", ({Victim,TP}));
          }
         hurt_me(Victim);
         remove_snare_object();
         return 1;
         
        }
   }
   if (TP == Victim)
      notify_fail("You'll need something sharper than that if you "+
         "wish to cut yourself free from the rope.\n");
   else
      notify_fail("You'll need something sharper than that to cut the rope.\n");
   return 0;
}

void
checks()
{
   // If the victim is attacked the trap is removed, this isn't a death trap
   if (Victim->query_attack() != 0)
      {
      write("The rope gives under the stress of the fighting and you "+
         "manage to free yourself and drop to the ground head first!!\n\nOuch!!\n");
      tell_room(ENV(TO), "The rope holding "+QTNAME(Victim)+" gives "+
         "dropping "+HIM_HER(Victim)+" to the ground.\n",Victim);
      hurt_me(Victim);
      remove_snare_object();
      return;
   }
   //  If the person some how moved we remove the trap
   if (ENV(Victim) != ENV(TO))
      {
      write("Somehow you were able to escape from your trap and have "+
         "freed yourself.\n");
      tell_room(ENV(TO),QCTNAME(Victim)+" manged to escape from the "+
         "snare trap which was holding "+HIM_HER(Victim)+".\n",Victim);
      hurt_me(Victim);
      remove_snare_object();
      return;
   }
}

void
hurt_me(object player)
{
   int hurt = 100;
   
   //   We don't want anyone to die from our trap
   if (player->query_hp() - hurt < 0)
      player->heal_hp(-(player->query_hp()/3));
   else
      player->heal_hp(-hurt);
}
