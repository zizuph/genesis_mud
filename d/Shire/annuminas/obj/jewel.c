inherit "/std/object";
#include "/d/Shire/common/defs.h" 
#include <stdproperties.h>
#include <ss_types.h>

int urges(object victim);

int alarm_id;
object player;

#define MININT 30 + random(30)
#define MINWIS 40 + random(40)
#define MINDIS 25 + random(25)

void
create_object()
{
  set_name("jewel");
   add_name("_annuminas_jewel_");
  set_short("blue-black jewel");
  set_adj("blue");
  add_adj("black");
  add_adj("blue-black");
  set_long("@@my_long@@");

  add_prop(OBJ_I_WEIGHT,3500-random(501));
  add_prop(OBJ_I_VOLUME,1500-random(251));
  add_prop(OBJ_I_VALUE,1500+random(93));
}

string
my_long()
{

   write("This blue-black jewel is dark and sinister-looking.  A shimmer "+
   "of blue light crosses over its surface from time to time, almost like a "+
   "lightning strike.\n");



 if(present("_annuminas_jewel_",TP))
 {
   TP->catch_msg("As you look at the blue-black jewel, it looks into you as well.\n");
   TP->add_prop("_i_have_urges_",1);
    alarm_id = set_alarm(1.0,60.0,"urges",TP);
    return "";
   }
   if(TP->query_prop("_i_have_urges_"))
   TP->catch_msg("As you look at the blue-black jewel, it looks into you as well.\n");   

   return "";

}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

   if(!interactive(dest))
   return;

   if(dest->query_prop("_i_have_urges_"))
   {
    alarm_id = set_alarm(1.0,20.0,"urges",TP);
   /* Those that drop it to pick it up later get a special surprise! */
    dest->catch_msg("A voice cries in your head: How dare you abandon me?!?!?!?!?\n");
   return;
  }

}

void
leave_env(object dest, object old)
{

   remove_alarm(alarm_id);
   player = 0;
   ::leave_env(dest, old);

   return;

}


int
urges(object victim)
{

   int  smart, wis, dis, minint, minwis, mindis, spell, aware, animal;
   object LAST_ROOM, player;
   player = TP;
   LAST_ROOM = player->query_prop(LIVE_O_LAST_ROOM);
   minint = MININT;
   minwis = MINWIS;
   mindis = MINDIS;
   smart = player->query_stat(SS_INT);
   wis = player->query_stat(SS_WIS);
   dis = player->query_stat(SS_DIS);
   spell = player->query_skill(SS_SPELLCRAFT);
   aware = player->query_skill(SS_AWARENESS);
   animal = player->query_skill(SS_ANI_HANDL);

   if(environment(TO) != player)
   {
    remove_alarm(alarm_id);
    return 1;
   }

   player->catch_msg("A blue flash of lightning erupts from the surface of "+
   "the blue-black jewel.\n");

   if(!(smart > minint))
   {  
      if(player->query_mana() > 150)
      {
       player->catch_msg("You feel mentally drained.\n");
       player->add_mana(-150);
     }
   }

 if(!(wis > minwis))
 {
   say(QCTNAME(player)+ " begins to look lost.\n");
   player->catch_msg("You lose your direction.\n");
   player->move(LAST_ROOM,1);
  }

  if(!(dis > mindis))
  {
    player->catch_msg("You begin to panic.\n");
    player->add_panic(50);
  }

   if((spell + animal + aware) <  120)
   {
     player->catch_msg("You feel very weak, like you're dying.\n");
     say(QCTNAME(player)+ " looks on the verge of death.\n");
     player->heal_hp(-200);
     if(player->query_hp() <= 0)
      player->do_die(TO);
   }

   return 1;

}
