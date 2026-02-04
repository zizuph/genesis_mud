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


init()
{
     ::init();
  add_action(drink_water, "drink");
  add_action(water_animal, "water");
}


create_room()
{
    set_short("stream falls");
    set_long(
        "The stream widens here and opens into a small waterfall.  The " +
        "clear frigid water cascades over smooth stones set into the " +
        "soft clay of the stream bed and settles into a deep pool.  " +
        "A boulder juts out into the pool making long casts into the " +
        "turbulent water at the foot of the falls.\n");


    add_prop(OBJ_I_CONTAIN_WATER,1);

    add_item(({"waterfall", "fall", "falls"}), 
        "The frigid waterfall froths over the smooth stones beneath the " +
        "water.  The current forms small eddys that swirl and create " +
        "a fine mist that lingers above the water.\n"
    );

    add_item(({"boulder", "rock"}), 
        "The large boulder is right at the foot of the falls.  The surface " +
        "of the boulder has been worn very clean and smooth by the water.\n"
    );   
 

    add_item(({"water"}), 
        "The turbulent water is very clear and cold.\n"
    ); 

    add_item(({"stone", "stones"}), 
        "The stones are light colored and have been worn smooth by the " +
        "water.  They are set into the soft clay of the stream bed.\n"
    );     

    add_item("stream", 
        "The stream is very clear and cold.  The babbling of the stream " +
        "sounds almost like whispered speech.\n"
    );
    
    add_item(({"pool", "deep pool"}), 
        "Athough the water is crystal clear, the turbulence and currents " +
        "created by the waterfall prevent you from seeing the bottom " +
        "of the pool.\n"
    );

    add_item("clay", "It's soft and grayish.\n"); 


   set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                 }),
                 ({"brook","gulley", "clay","stream"}) , 
                  3 );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "stream03", "south", 0);
    add_exit(TOMBDIR + "path01", "northeast", 0);
    add_exit(TOMBDIR + "stream_hollow", "west", 0);        
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


