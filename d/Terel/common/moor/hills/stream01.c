// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
// updated by Zizuph Mar 2023: Remove infinite fatigue recovery, limit it to
// 64, resetting after 5 minutes.

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define HIS(x) x->query_possessive()

#define STREAM_SPLASH "stream_splash"


int    drink_water(string arg);
int    water_animal(string arg);
int    splash_water(string arg);

create_room()
{
    set_short("stream");
    set_long(
        "The tumbling mountain stream babbles and gurgles musically " +
        "as it narrows into a small brook and down a gulley.  The water " +
        "level must have been higher at some point in time since the water " +
        "is bordered on both sides by frost-hardened mud and pine needles.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);
	add_prop(OBJ_I_CONTAIN_WATER,1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);	
    add_prop("_live_i_can_fish", ({"freshwater"}));

    add_item(({"stream", "water", "brook","gulley"}), 
        "The water is very clear and cold in the middle but rather " +
        "muddy near the edges of the stream.\n"
    );


    add_item(({"needle", "needles"}), 
        "They are pine needles indigenous to Terel.  They are different from " +
        "those you might find elsewhere in Genesis.\n"
    );

    add_item("mud", 
                   "It's just normal mud like you would find near " +
                   "any stream.\n");

    add_exit("stream02", "north", 0);


   set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                 }),
                 ({"brook","gulley", "mud","stream"}) , 
                  3 );

}


void 
init()
{
  ::init();
  add_action(drink_water, "drink");
  add_action(water_animal, "water");
  add_action(splash_water, "splash");
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

void dec_splash_counter(object player)
{
    player->dec_prop(STREAM_SPLASH, 1);
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

           int fatigue = 32;
           for (int i = 0; i < TP->query_prop(STREAM_SPLASH); i++)
           {
               fatigue /= 2;
           }
           if (fatigue > 0)
           {
               TP->set_fatigue(TP->query_fatigue() + fatigue);  
               TP->inc_prop(STREAM_SPLASH, 1);
               TP->command("shiver");
               set_alarm(300.0, 0.0, &dec_splash_counter(TP));
           }
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




