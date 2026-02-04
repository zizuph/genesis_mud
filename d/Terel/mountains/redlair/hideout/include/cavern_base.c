/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cavern_base.c
 *
 * Tomas May 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Terel/include/herb_arrs.h"

inherit "/d/Terel/std/room_tell.c";
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define  DEFAULT   MOUNTAIN_DIR + "redlair/hideout/"


object pebble;

int picked_shroom = 0;
public void reset_shrooms();
int    drink_water(string arg);
int    water_animal(string arg);


/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    add_action(drink_water, "drink");
    add_action(water_animal, "water");
    start_room_tells();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells mud and mildew.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{

    ::create_room();
    set_short("in a large cavern");
    set_long("@@change_long@@");   // check for the desc. below. 

    set_tell_time(500 + random(200));

    add_item(({"stalagmites", "stalagmite"}),
             "They vary in size and are a bit lighter in colour than the " +
             "ground from which they come.\n");

    add_item(({"stalactites", "stalactite"}),
             "Hanging down from the ceiling, they have a rough texture. " +
             "Some of them drip water onto the cavern floor.\n");    

    add_item(({"darkness"}),
             "A dark black void. You cant see anything beyond.\n");
    add_item(({"luminous mushrooms","lumininous mushroom","mushroom",
                  "mushrooms","luminiscent mushroom","luminiscent mushrooms"}),
               "The luminiscent mushrooms grow on either side of " +
               "the riverbank providing an erie glow throughout the cavern.\n");
    add_item(({"river","riverbank","water","bank"}),
               "The underground river runs " +
               "through the middle of the cavern twisting and turning " +
               "around stalagmites and large boulders. The water " +
               "is clear allowing you to see to the bottom in most " +
               "areas. Small plants grow just below the surface of the " +
               "water along the riverbank and on the edges of the rocks.\n");
    add_item(({"plant","plants"}),"Small plants and moss grow about the " +
               "rocks and along the edges of the riverbank just under " +
               "the water.\n");
    add_item(({"rocks","rock","boulder","boulders"}),
               "Many various sized rocks, pebbles and boulders can " +
               "be seen about the cavern.\n");
    add_item(("ceiling"),"The jagged ceiling raises high above you. Its " +
               "stalactites remind you of sharp teeth.\n");

    add_cmd_item(({"river","water"}),
                 ({"cross","wade across","swim across","swim"}),
                   "You decide against getting wet since there " +
                   "isn't much on the otherside.\n");
    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");

    add_cmd_item(({"mushrooms","mushroom"}),
                 ({"pick","gather","get"}),
                   "@@get_mushroom");
    INSIDE;

    // Add herbs to the room.
    set_up_herbs( ({ ONE_OF_LIST(SUBT_HERBS),
                     ONE_OF_LIST(SUBT_HERBS),
                     ONE_OF_LIST(DARK_HERBS),
                  }),
                  ({"bank","stream","river",
                    "plants","riverbank","riverbed"}) , 3 );
}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}


get_mushroom()      // pick the shrooms.
{
   if (picked_shroom == 1)
   {
       NF("You find no mushrooms to pick.\n");
       return 0;
   }

   picked_shroom = 1;  // Remove the mushrooms.
   write("You pick one of the mushrooms from the riverbank.\n" +
         "The mushroom immediately stops glowing and crumbles to " +
         "dust. The light " +
         "within the cavern flickers slightly then dies out as the " +
         "mushrooms disappear within the muddy riverbank.\n");
   say(QCTNAME(TP) + " picks a mushroom from the riverbank.\n" +
         "The light flickers within the cavern then dies as " +
         "the luminous mushrooms disappear within the muddy " +
         "riverbank.\n");
   add_item(({"luminous mushrooms","lumininous mushroom","mushroom",
              "luminiscent mushroom","luminiscent mushrooms","mushrooms"}),
             "You dont see any mushrooms here.\n");
   DARK;            // add darkness to the room.

// For our amusement, lets log who picks the mushrooms:
   write_file(MOUNTAIN_DIR + "redlair/hideout/log/ipicked_shroom",
      TP->query_name()+" " + ctime(time()) + "\n");

   set_alarm(300.0, 10.0, reset_shrooms);  // in 300 seconds reset the mushrooms.
   return 1;
}


public void
reset_shrooms()
{
    if (picked_shroom == 1)   // shrooms were picked.
    {
       tell_room(ETO, "Several small luminous mushrooms " +
          "push through the muddy riverbank providing an erie " +
          "glow throughout the cavern.\n");
       add_prop(ROOM_I_LIGHT, 1);  // Add light to the room.
       add_item(({"luminous mushrooms","lumininous mushroom",
                  "mushroom","mushrooms"}),
                  "The luminiscent mushrooms grow on either side of " +
                  "the riverbank providing an erie glow throughout " +
                  "the cavern.\n");
       picked_shroom = 0;    // add shrooms again.
    }
    return;
}


string
change_long()
{
    if( picked_shroom == 0 )   // we add light to the long desc.
    {
       return "The large cavern spans several hundred feet across. " +
       "Its vaulted ceiling raises high above you. A moderate sized " +
       "underground river runs through the middle of the cavern. " +
       "Its muddy riverbank contains several small luminous mushrooms " +
       "which provide an erie glow throughout the cavern. ";
     }

     if( picked_shroom == 1 )  // someone picked the shrooms. No light.
     {
       return "The large cavern spans several hundred feet across. " +
       "Its vaulted ceiling raises high above you. A moderate sized " +
       "underground river runs through the middle of the cavern. ";
              
     }

}


int
drink_water(string arg)
{
  
  int amount= TP->drink_max() / 20;

  notify_fail("Drink water from what, the river?\n");
  if (!arg) return 0;
  
  if (arg=="water")
    {
      notify_fail("Drink water from the river?\n");
      return 0;
    }
  
   if (parse_command( arg, TO, 
                     "[the] 'water' 'from' / 'at' [the] 'river'"))
    {

      if (! TP->drink_soft(amount)) 
        {
          write ("You cup your hands under the flowing river gathering " +
                 "the water, but you are too full to drink any more!\n");
            say ("Water overflows from "+QCTNAME(TP)+"'s cupped hands.\n");
          //top it off anyway.
          TP->drink_soft(TP->drink_max() - TP->query_soaked());  
        }
        else
          {
        write ("You cup your hands under the flowing river " +
               "and drink the cool refreshing water.\n");
        say(QCTNAME(TP)+ " cups "+HIS_HER+ " hands under the flowing river "+
            "and drinks the cool refreshing water.\n");
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
                   "[the] %o [from] [at] [the] [river]", 
                   animal))
  {
        say (QCTNAME(TP)+" leads "+HIS_HER+" "+animal->short()+
             " to the river and waters "+animal->query_objective()+".\n");
        write ("You lead your " +animal->short()+
               " to the river and water "+animal->query_objective()+".\n");

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
      notify_fail("Water what, where the river? \n");
      return 0;
    }
}


