 
/* mine/obj/d_death is cloned by mine/npc/daemonlord.c */
 
/* This is an interesting phantom object that moves onto the killer */
/* when the Daemonlord is killed. It is just to see how the player  */
/* reacts to it, to see if any others can be added in the future.   */
/*              Mylos, 25.7.94                                      */
 
inherit "/std/object";
 
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"
 
void death_decay(mixed args);
 
void
create_object()
{
   set_short(0);
   set_name("haunt_obj");
   add_prop(OBJ_I_NO_DROP, 1);
   set_no_show();
 
   seteuid(getuid());
   set_alarm( 40.0,0.0,"death_decay", ({ this_player(),1 }) );
}
 
void
death_decay(mixed args)
{
   object player;
   int time;
 
   if (sizeof(args) != 2)
      return;
   player = args[0];
   time = args[1];
 
   switch(time)
   {
      case 1:
      tell_room(ENV(player),"An image from Hell appears before your eyes, "+
        "the bedraggled clothing of a dead Daemonlord. It wavers then "+
        "fades away.\n");
      break;
 
      case 2:
      player->catch_msg("The image of a dead Daemonlord floats in front "+
        "of you and says 'You killed me! You shall pay in the eternal "+
        "after life for this crime, I swear it!'.\n");
      tell_room(ENV(player), "An image of a dead Daemonlord floats in "+
        "front of "+QTNAME(player)+" and says 'You killed me! You shall "+
        "pay in the eternal afterlife for this crime, I swear it!'\n", player);
      break;
 
      case 3:
      tell_room(ENV(player), "You hear a moaning from the depths of Hell, "+
        "a shade wronged by a mortal.\n");
      remove_object();
      break;
 
      default:
      return;
   }
   set_alarm( 40.0,0.0,"death_decay", ({ this_player(),time + 1 }) );
}
 
