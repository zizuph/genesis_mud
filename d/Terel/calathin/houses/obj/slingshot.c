inherit "/std/object";
#include "/d/Terel/include/Terel.h"
#include <ss_types.h>

#define EV environment(TP)

int sling_hit(string str);
object stoned_player;
object rock;

void
create_object()
{
   set_name("slingshot");
   add_name("tomas:slingshot");
   add_adj("wooden");
   set_short("wooden slingshot");
   set_long("A wooden slingshot. If you had a rock you could " +
      "probably hit someone with the slingshot.\n");
   
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_I_VOLUME,50);
   add_prop(OBJ_I_VALUE,20);
   
   seteuid(getuid(TO));
}

void
init()
{
   ::init();
   add_action(sling_hit, "hit");
}

int 
sling_hit(string str)
{
   int hitcheck, number;
   
   if(!(present("slingshot", TP)))
   {
      notify_fail("You'll need to get the slingshot if you " +
      "hope to be able to hit someone with it.\n");
      return 0;
   }
   
   if(!(present("rock", TP)) && !(present("stone", TP)) &&
     !(present("pebble", TP)))
   {
      notify_fail("You'll need a rock if you want to " +
      "use the slingshot.\n");
      return 0;
   }
   
   rock=(present("rock", TP)) || (present("stone", TP)) ||
     (present("pebble", TP));
   
   if(!str)
   {
      notify_fail("Hit who?\n");
      return 0;
   }
   stoned_player=present(str,EV);
   hitcheck=random(4);
   number = (TP->query_skill(SS_WEP_MISSILE));
   if(!stoned_player)
   {
      notify_fail("Hit who?\n");
      return 0;
   }
   if(str == TP->query_real_name())
   {
      notify_fail("You really want to hit yourself with a rock?\n");
      return 0;
   }
   
   if(hitcheck < 3) 
   {
      write("You load a rock into the slingshot and launch it " + 
      "at " + stoned_player->query_the_name(TP) + ".\n");

      tell_room(EV,QCTNAME(TP) + " loads a rock into " +
      TP->query_possessive() + " slingshot and launches it at " +
      QTNAME(stoned_player) + ".\n", ({stoned_player,TP}),TP);

      tell_room(EV,QCTNAME(TP) + " hits " + 
      stoned_player->query_the_name(TP) + " with a rock " +
      "launched from " + TP->query_possessive() + 
      " slingshot.\n", ({stoned_player,TP}),TP);

      write("You hit " + stoned_player->query_the_name(TP) +
      " with the rock launched from your slingshot!\n");

      stoned_player->catch_msg(QCTNAME(TP)+" launches a " +
      "rock at you from " + TP->query_possessive() +
      " slingshot.\nOuch! You're hit by the rock!\n");

      rock->remove_object();

      return 1;
   }
   write("You launch a rock from your slingshot at " 
      + stoned_player->query_the_name(TP) +
      ", but it misses " + stoned_player->query_objective() +
      ".\n");

   tell_room(EV,QCTNAME(TP) +" launches a rock from " +
   TP->query_possessive() + " slingshot at " + 
   QTNAME(stoned_player)+", but misses.\n"
      ,({stoned_player,TP}),TP);

   stoned_player->catch_msg(QCTNAME(TP) +" launches a rock " +
   "at you from " + TP->query_possessive() + " slingshot!\n" +
   "The rock misses you and hits the ground.\n");

   rock->move(EV);

   return 1;
}
