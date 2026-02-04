inherit "/std/room";
inherit "/d/Terel/std/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>
#include "/d/Terel/include/herb_arrs.h"

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define HIS(x) x->query_possessive()
#define TOMBDIR   "/d/Terel/sorgum/tomb/"

int    drink_water(string arg);
int    water_animal(string arg);
int    splash_water(string arg);

object traveller;


init()
{
     ::init();
  add_action(drink_water, "drink");
  add_action(water_animal, "water");
  add_action(splash_water, "splash");
}



create_room()
{
    set_short("stream");
    set_long(
        "The currents of the brook flow around the fallen tree and " +
        "continue downstream.  This area is on a subtle incline which " +
        "accelerates the currents of the cold water over smooth " +
        "stones beneath the surface.  The stream ends in a small " +
        "waterfall to the north of here.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);

    add_item(({"fallen_tree", "tree"}), 
        "The once majestic tree now lies fallow and bare.\n"
    );                                      
                                            
    add_item(({"waterfall", "fall"}), 
        "The waterfall cascades over a boulder and into a pool.\n"
    );

    add_item(({"water", "stream", "brook"}),
        "The turbulent water is very clear and cold.\n"
    );    
    
    add_item(({"stone", "stones"}), 
        "The stones are light colored and have been worn smooth by the " +
        "water.  They are set into the soft clay of the stream bed.\n"
    );    
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "stream_falls", "north", 0);    
    add_exit(TOMBDIR + "stream02", "south", 0);


    set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(RIVER_HERBS),
                     ONE_OF_LIST(RIVER_HERBS),
                  }),
                  ({"brook", "stream", "tree"}) , 
                   3 );

   
    reset_room();
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


void
reset_room()
{    
  
    if(!traveller)
    {
       traveller = clone_object("/d/Terel/sorgum/tomb/traveller");
       traveller->move(TO);
    }
}


          



