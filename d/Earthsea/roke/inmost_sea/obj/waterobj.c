/* Water object, Jakob 95-07-17 
* Assisted by Napture.
*
* Revision log: Jakob 95-07-25
*               - Added check for property
*                 _breath_under_water
*               - Implemented task system.
*/

inherit "/std/object";
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#pragma strict_types

/* Variables */
int damageloop, totalloop;

public void
create_object()
{
   set_name("waterobj");
   set_short("waterobj");
   set_long("This object will be cloned to mortals that " +
      "enters underwater areas. They will loose hp " +
      "as they don't get air. \n");
   add_prop(OBJ_M_NO_GET, 1);
   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_GIVE, 1);
   add_prop(OBJ_I_INVIS, 1);
   add_prop(OBJ_S_WIZINFO, "Will slowly drown a player in water");
}



public void
breath_damage(object ob)
{
   int swim, damage;
   string msg;
   
   if(((E(ob))->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER))
      {
      this_object()->remove_object();
      write ("You take a huge breath of the fresh air. " + 
         "Ahhh, wonderful. You begin to breath normally " +
         "again.\n");
      return;
   }
   if(ob->query_prop(MAGIC_I_BREATH_WATER) <= 0 )
      {
      switch (damageloop)
      {
         case 0: damage = 0;
         msg = "You are running out of air.\n";
         break;
         case 1: damage = -100;
         msg = "You can hardly breath.\n";
         break;
         case 2: damage = -500;
         msg = "The air is gone, get up!\n";
         break;
         default: damage = -100 * damageloop * damageloop;
         msg = "The lack of air is burning like fire in your lungs!\n";
         break;
      }
      
      /* We make an exponential raise in the difficulty to stay under 
         * water for the player.
      */
      if (this_player()->resolve_task(TASK_ROUTINE + 50 * 
               2 * totalloop,
            ({TS_CON, SS_SWIM})) > 0)
      {
         /* The player succeed in keeping breath, no damage made. */
         
         write("You manage to keep your breath.\n");     
         
      }
      else
         {
         
         write(msg);
         say(QCTNAME(ob) + " seems to run out of air...\n");
         swim = ob->query_skill(SS_SWIM);
         
         /* A person with swiming ability 10 gets the following hp
         * loss:-0, -100, -500, -900, -1600, -2500, -3600, -4900 ..
         *
         * A typical player with swim 50 gets:
         * loss:-0, -20, -100, -180, -320, -500, -720, -980 ..
         */
         
         damageloop++;
         ob->heal_hp((damage*10/((1) > (swim) ? (1) : (swim))));
         ob->do_die();
      }
      
      /* Even if we have the property _breath_under_water set to 1
         * we will be in this loop until we leave this environment, 
      * chance exists that we lose the property.
      */
   }
   totalloop++;
   set_alarm(15.0, 0.0, &breath_damage(ob));
}


public void
enter_env(object dest,object old)
{
   ::enter_env(dest, old);
   set_alarm(15.0, 0.0, &breath_damage(dest));
   damageloop = 0;
   totalloop = 0;
}


