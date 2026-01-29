#pragma save_binary

inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"
#include "trickster.h"

#define ROOM_IS_BUSY "_this_room_is_occupied"

int   delay_time;

void
create_room()
{
   set_short(".");
   set_long(".\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, -10);
   add_prop(ROOM_M_NO_TELEPORT,
      "You can't seem to gain the concentration needed to do that " +
      "while sliding down this tunnel.\n");
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   if (!living(ob))
      return;
   ob->catch_msg("You let out a scream as you jump down the hole!\n");
   add_prop(ROOM_IS_BUSY, 1);
   delay_time = set_alarm(3.3,0.0,"start_sliding",ob);
}

void
start_sliding(object player)
{
   remove_alarm(delay_time);
   player->catch_msg("\n\n\n");
   switch(random(4))
   {
      case 0:
      player->catch_msg("You start to feel queasy as you quicky gain " +
         "speed down the dark tunnel.\n");
      player->command("$gag");
      break;
      case 1:
      player->catch_msg("You feel like you left your stomache behind at that "+
         "last dip in the tunnel.\n");
      break;
      case 2:
      player->catch_msg("You start to sweat perfusely as the sheer speed of " +
         "your descent is making you quite nervous.\n");
      break;
      case 3:
      player->catch_msg("As you slide faster and faster you scream in delight " +
         "enjoying your little trip down this dark tunnel.\n");
      break;
   }
   player->catch_msg("\n\n\n");
   delay_time = set_alarm(5.0,0.0,"continue_sliding",player);
}

void
continue_sliding(object player)
{
   remove_alarm(delay_time);
   switch(random(5))
   {
      case 0:
      player->catch_msg("A sudden turn in the tunnel causes you to bang " +
         "your head on one of the walls.\n\nOuch!!!\n");
      break;
      case 1:
      player->catch_msg("You start to slide from wall to wall in the tunnel " +
         "quickly losing control of yourself.\nYou begin to sprial " +
         "uncontrollably down the tunnel, causing you to become sick!\n");
      player->command("$puke");
      break;
      case 2:
      player->catch_msg("Not able to bear the speed of your descent, " +
         "you close your eyes and pray that this trip will soon be at an end.\n");
      break;
      case 3:
      player->catch_msg("You desparately try to slow yourself down " +
         "by trying to grab on to the walls of the tunnels as you slide by, " +
         "but are unable to get a grip since they are so slipperly.\n");
      break;
      case 4:
      player->catch_msg("You think to yourself this is the must fun " +
         "I've had in ages, as you slingshot around a bend in the tunnel.\n");
      break;
   }
   player->catch_msg("\n\n\n");
   delay_time = set_alarm(7.3,0.0,"more_sliding",player);
}

void
more_sliding(object player)
{
   remove_alarm(delay_time);
   switch(random(4))
   {
      case 0:
      player->catch_msg("You bump into yet another wall on your journey, " +
         "adding to the countless bruises that you'll surely recieve by " +
         "the time this ride is over.\n");
      break;
      case 1:
      player->catch_msg("You feel like you left your stomache behind " +
         "after that last dip in the tunnel.\n");
      player->command("$gag");
      break;
      case 2:
      player->catch_msg("You shout:  Wheeeeeeeeeeeeeeeee!!!!\n" +
         "Enjoying this part of the tunnel throughly.\n");
      break;
      case 3:
      player->catch_msg("I'n a mad panic, you desparately grab at " +
         "anything you can see in the dark as it goes by.  In hopes " +
         "that you can slow yourself.\n");
      break;
   }
   player->catch_msg("\n\n\n");
   delay_time = set_alarm(4.0,0.0,"end_sliding",player);
}

void
end_sliding(object player)
{
   remove_alarm(delay_time);
   player->catch_msg("The tunnel starts to grow brighter, as light " +
      "begins to blind your eyes, you think your wild journey is near " +
      "an end.\n");
   player->catch_msg("\n\n\n");
   delay_time = set_alarm(2.2,0.0,"delay_move",player);
}

void
delay_move(object player)
{
   remove_alarm(delay_time);
   player->move_living("M", TRICK_DIR + "back_way");
   remove_prop(ROOM_IS_BUSY);
}
