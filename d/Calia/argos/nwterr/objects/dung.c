/*
** Sheep Dung Object
**
** What it does: when in the inventory of a player, it periodically
**               tells the room that the person stinks
**
** How Player gets it: it is added to a player whenever he steps in
**                     certain rooms in the sheep pasture...
**                     ie. he steps in it and it gets on his feet.
**                     argos/nwterr/past*.c
** How the player gets rid of it: He can "wash feet" in the shepherds
**                                house...argos/nwterr/pastd.c
**                                OR it dries up and falls off after a
**                                   while.
** Why is this here?? Just for chuckles!! ;)
**
** HISTORY
** Date        Action
** ----------- ------------------------------
** 8/28/94     Created
**
**/
inherit "/std/object";
 
#include <stdproperties.h>
#include <macros.h>
 
void
remove_stink (object ThisPlayer)
{
   object Dung;
 
   Dung = present("DUNG_OBJ",ThisPlayer);
   if (Dung) {
      Dung->remove_object();
      set_this_player(ThisPlayer);
      write("The dung on your feet dries up and falls off.\n");
      write("The awful smell dissipates.\n");
   }
}
 
void
stink(object ThisPlayer)
{
   object ThisRoom;
 
   /* make sure the object passed is really a player object */
   if (!(ThisPlayer->query_prop(LIVE_I_IS))) return;
   if (ThisPlayer->query_npc()) return; /* don't add to NPCs */
 
   /* get the player's room to tell everyone he stinks!! */
   ThisRoom = environment(ThisPlayer);
   set_this_player(ThisPlayer);
   write("The stench of dung on your feet overwhelms you!\n");
   tell_room(ThisRoom,    /* which room to send message */
             "The stench of dung on " + QNAME(ThisPlayer) +
             " overwhelms you!\n",
             ThisPlayer);  /* tell all except this player..he gets own msg */
 
}
 
void
enter_env (object Destination, object FromRoom) {
   object Player;
 
   /* execute the standard enter_env function */
   ::enter_env(Destination, FromRoom);
 
 
   /* only do this for living players */
   Player=this_player();
   if (!(Player->query_prop(LIVE_I_IS))) return;
   if (Player->query_npc()) return;   /* don't add to NPCs */
 
 
   /* set the message alarms */
   /* write stink message every 20 seconds starting in 5 seconds */
   set_alarm(5.0, 20.0, "stink", Player);
 
   /*
   ** after 7.5 mins, remove the object
   */
   set_alarm(450.0, 0.0, "remove_stink", Player);
}
 
create_object()
{
  set_name("DUNG_OBJ");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  set_no_show(1); /* invisible to player */
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
}
