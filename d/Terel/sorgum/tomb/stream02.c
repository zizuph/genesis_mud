 /*
    Modified: 29 Apr 2003, by Bleys
        Added a missing space in do_pick() to avoid mortals seeing
            "Frankpicks a mushroom."

    Modified: 13 May 2003, by Bleys
        - fixed a typo in do_pick ("not work picking")
        - changed do_pick() to use Goldberry's standardize ylpoe
            instead of Sorgum's original herb configured on the fly.

*/
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <herb.h>
#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>

#define SHROOM_LIMIT   10



#define HIS(x) x->query_possessive()
#define TOMBDIR   "/d/Terel/sorgum/tomb/"

int    drink_water(string arg);
int    water_animal(string arg);
int    splash_water(string arg);

int shrooms;

init()
{
     ::init();
  add_action("do_pick", "pick");
  add_action(drink_water, "drink");
  add_action(water_animal, "water");
  add_action(splash_water, "splash");
}

reset_room()
{
    shrooms = 1 + random(SHROOM_LIMIT);
}

create_room()
{
    set_short("stream");
    set_long(
        "A moss-covered fallen tree lies here propped up at an angle by " +
        "its limbs which are stuck into the muddly clay bottom of the " +
        "brook.  Mushrooms have sprung up among the moss and the " +
        "soft decaying bark of the felled tree.  A small creek forks off " +
        "of the brook to the northwest and the brook continues north.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);

    add_item(({"mushroom", "mushrooms", "shrooms"}), "@@my_shrooms");
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "stream01", "south", 0);    
    add_exit(TOMBDIR + "stream03", "north", 0);
    add_exit(TOMBDIR + "creek", "northwest", 0);
    reset_room();
}


string
my_shrooms()
{
     if (shrooms > 0) 
          return "There are some big ones mixed in with tiny ones.\n";
     else  
          return "The mushrooms are so tiny they look like bark.\n";
}

do_pick(string str)
{
     object ob;
     int stren;

     notify_fail("Pick what?\n");
     if ((str == "mushroom") || (str == "mushrooms")) {

          if (shrooms <= 0) {
               write("The mushrooms are so tiny, you decide they are not " +
                         "worth picking after all.\n");
               return 1;
          }

          shrooms--;
          seteuid(getuid(TO));
          ob = clone_object(TER_HERB + "ylpoe");
/*
          ob = clone_object(TOMBDIR + "shroom");
          stren = 20 + random(20);
          ob->set_herb_value(10 * stren);
          ob->set_effect(HERB_HEALING, "mana", stren);
*/
          ob->move(TP);
          write("You pick a mushroom.\n");
          say(QCTNAME(TP) + " picks a mushroom.\n");
          return 1;
     }
     return 0;
}
         
                
int
drink_water(string arg)
{
  
  int amount= TP->drink_max() / 20;

  notify_fail("Drink water from what?\n");
  if (!arg) return 0;
  
  if (arg=="water")
    {
      notify_fail("Drink water from the stream?\n");
      return 0;
    }
  
   if (parse_command( arg, TO, 
                     "[the] 'water' 'from' / 'at' [the] 'stream'"))
    {

      if (! TP->drink_soft(amount)) 
        {
          write ("You cup your hands under the water, but you are "+
                 "too full to drink any more!\n");
            say ("Water overflows from "+QCTNAME(TP)+"'s cupped hands.\n");
          //top it off anyway.
          TP->drink_soft(TP->drink_max() - TP->query_soaked());  
        }
        else
          {
        write ("You cup your hands in the stream and drink "+
               "of the ice cold mountain water.\n");
        say(QCTNAME(TP)+ " cups "+HIS(TP)+ " hands in the stream "+
            "and drinks the ice cold mountain water.\n");
          }
        return 1;
    }
}




int
splash_water(string arg)
{
  
  int amount = TP->query_max_fatigue();

  notify_fail("splash what?\n");
  if (!arg) return 0;
  
  if (arg=="water")
    {
      notify_fail("Splash water on what, your face perhaps?\n");
      return 0;
    }
  
   if (parse_command( arg, TO, "[the] 'water' 'on' / [the] 'face'"))
    {

      if (TP->query_fatigue() < amount) 
        {
           write ("You lean over and splash your face with a handful of ice cold mountain water. "+
             "The frigid water leaves you feeling invigorated after your weary travels.\n");
           say(QCTNAME(TP)+ " leans over the stream and splashes water on "+HIS(TP)+ " face.\n");

           TP->set_fatigue(TP->query_fatigue() + 10);  
           TP->command("shiver");
        return 1;
        }
        else
          {
           write ("You lean over and splash your face with a handful of ice cold mountain water.\n");
           say(QCTNAME(TP)+ " leans over the stream and splashes water on "+HIS(TP)+ " face.\n");        
          }
        return 1;
    }
}


/*********************************************************************/
int
water_animal(string arg)
{
object animal;
int i, amount;

if (!arg) 
{return 0;
}

if (parse_command( arg, 
                   TO, 
                   "[the] %o [from] [at] [the] [stream]", 
                   animal))
  {
        say (QCTNAME(TP)+" leads "+HIS(TP)+" "+animal->short()+
             " to the stream and waters "+animal->query_objective()+".\n");
        write ("You lead your " +animal->short()+
               " to the stream and water "+animal->query_objective()+".\n");

          amount=animal->drink_max() / 20;

          for (i=0;i<20;i++) 
            {
              animal->drink_soft(amount);
            }
          animal->drink_soft ( animal->drink_max() - animal->query_soaked());

          return 1;

        }
      else
        {
      notify_fail("Water what, where? \n");
      return 0;
    }
}


          
