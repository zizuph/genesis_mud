/**********************************************************************
 * - pit.c                                                          - *
 * -                                                                - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Khalakhor/sys/basic.h"

int
stoke_fire(string str)
{
   if((str == "the fire") || (str == "fire") || (str == "logs") || (str == "the logs"))
      {
      write("You pick up a strong iron poker and stoke up the "+
        "fire in the pit. "+
        "\nThe fire sparks and burns more brightly.\n"+
        "You return the strong iron poker.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" picks up a strong iron poker and begins to stoke "+
        "the fire in the pit.\n"+
        "The fire sparks and burns brightly now.\n");
      say(QCTNAME(this_player())+" returns the iron poker.\n");
      return 1;
      }
   else
  {
   notify_fail("Stoke what? Stoke the fire perhaps?\n");
   return 0;
  }

}
int
log_fire(string str)
{
     if((str == "log on fire") || (str == "log on the fire") || (str == "wood on fire") || (str =="wood on the fire"))
     {
       write("You take a log from the pile next to the pit and toss it in. "+
         "\nFlames burst forth wildly then calm leaving the fire burning "+
         "brightly.\n");
      
          /* This what others in room see. */
       say(QCTNAME(this_player())+" takes a log from the pile next to the pit and tosses "+
         "it in the pit.\n"+
         "Flames burst forth wildly then calm leaving the fire buring "+
         "brightly.\n");
      return 1;
      }
   else
  {
   notify_fail("Put what? Put log on fire perhaps?\n");
   return 0;
  }

}
int
warm_it(string str)
{
   if((str == "face"))
          {
      write("You press your face forward to warm your cheeks "+
        "from the heat of the fire.\n"+
        "Ahh nice and warm.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" puts "+HIS(this_player())+" face closer to the fire.\n");
      return 1;
           }
   if((str == "hands"))
          {
      write("You place your hands near the fire and rub them "+
        "together trying to warm them.\n"+
        "The warmth from the fire feels good on your skin.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" places "+HIS(this_player())+" hands very close "+
        "to the fire and begins to rub them together.\n");
      return 1;
           }
   if((str == "legs"))
          {
       write("You step very close to the fire and rub along your "+
       "legs to warm them up.\n"+
       "The heat of the fire feels warm on your skin.\n");
      
          /* This what others in room see. */
        say(QCTNAME(this_player())+" steps up to the fire and starts "+
        "to rub "+HIS(this_player())+" legs, which appears to warm them.\n");
        return 1;
           }
   if((str == "ears"))
       {
       write("You lean your head forward. You then turn from side to side "+
         "rubbing your ears to warm them before the hot fire.\n");
   
       /* This what others in room see. */
       say(QCTNAME(this_player())+" learns forward to the fire and "+
         "turns "+HIS(this_player())+" head from side to side while rubbing "+
         ""+HIS(this_player())+" ears.\n");
       return 1;
           }
   if((str == "feet"))
       {
       write("You put your feet closer to the fire rubbing them, hoping "+
         "the fire will warm them up.\n");
      
          /* This what others in room see. */
       say(QCTNAME(this_player())+" puts "+HIS(this_player())+" feet closer to "+
         "the fire and rubs them.\n");
       return 1;
       }
   if((str == "body"))
       {
       write("You step up to the fire and feel the heat soothe your bones.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" steps up to the fire for a long moment.\n");
      return 1;
      }
   if((str == "bottom"))
       {
       write("You step up to the fire and stick your bottom towards it.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" steps up to the fire sticking "+HIS(this_player())+" bottom "+
        "towards it.\n");
      return 1;
      } 
   else
  {
   notify_fail("Warm what? Your body perhaps?\n");
   return 0;
  }
}
int
extinguish_fire(string str)
{
   if((str == "the fire") || (str == "fire"))
      {
      write("You try to extinguish the fire in the pit but fail.\n");
      
          /* This what others in room see. */
      say(QCTNAME(this_player())+" tries to extinguish the fire in the pit but fails.\n");
      return 1;
      }
   else
  {
   notify_fail("Extinguish what? Extinguish the fire perhaps?\n");
   return 0;
  }

}
public void
init_fire()
{

    add_action(stoke_fire, "stoke");
    add_action(log_fire, "put");
    add_action(warm_it, "warm");
    add_action(extinguish_fire, "extinguish");

}
