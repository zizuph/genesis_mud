/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>



inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";

int    drink_water(string arg);
int    water_animal(string arg);
int    do_buy(string str);

object dola;


init()
{
     ::init();
  add_action(drink_water, "drink");
  add_action(water_animal, "water");
  add_action(do_buy, "buy");
  start_room_tells();
}

#define HIS(x) x->query_possessive()


public void
reset_room()
{
    if (!dola) {
        seteuid(getuid());
        dola = clone_object(MOUNTAIN_DIR +"stronghld/npc/stable_keep");
        dola->move(TO);
    }
}



public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Stable");
    set_long("The stronghold stables look well kept. " +
       "Several stalls line either side of the walls. At " +
       "end of the stalls you notice a large stone water " +
       "trough along with a closed metal feed box. To the " +
       "south leads back to the main " +
       "passageway.\n");

    add_item(({"feed box","box"}),
       "The feed box looks like it is used to store food " +
       "for the animals.\n");

    add_item(({"stalls","stall"}),
       "The horse stalls are well kept. Fresh hay is stewn " +
       "about the floor of each stall, providing a warm " + 
       "comfortable flooring for the horses. Each stall " +
       "is equipped with a feed and watering trough.\n");

    add_item(("floor","hay"),"The floor within the stalls " +
       "are covered with hay.\n");

    add_item(({"ceiling","walls"}),
       "The ceiling and walls are cavernlike, carved from solid " +
       "rock by the dwarves. Iron braziers hang from the ceiling " +
       "providing light to the room.\n");

    add_item(({"hook","scoop","metal scoop"}),
       "An iron hook hangs just above the metal feed bin. A metal " +
       "scoop hangs from the hook.\n");

    add_item(({"stack of bags","bags","stack"}),
       "A large stack of paper bags is stacked neatly on the " +
       "metal feed box.\n");


    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the barracks.\n");

    add_item(({"water","trough","stone trough","water trough"}),
       "A stone water trough. Water from " +
       "the ceiling collects at the middle then follows a " +
       "manmade vein leading from the ceiling down the wall " +
       "ending just above the trough. The overflow from the " +
       "trough drains from one side through a small crack in " +
       "the floor.\n");

    add_cmd_item(({"feed box","box"}),({"open","unlock"}),
       "You cant seem to do that on your own. Perhaps, you should " +
       "speak with the stable keep about purchasing some feed " +
       "instead.\n");

    add_cmd_item(({"scoop","metal scoop","bags","stack of bags",
                   "hook"}),({"get","pick","take"}),
                   "Looking for a job as a stable keep are we?\n");

    set_tell_time(200 + random(200));
    add_tell("You notice the soft sound of water trickling down from " +
       "the wall into a stone water trough at the end of the stables.\n");


    add_exit(MOUNTAIN_DIR + "stronghld/fortb","south",0,1);

    
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
      notify_fail("Drink water from the trickle?\n");
      return 0;
    }
  
   if (parse_command( arg, TO, 
                     "[the] 'water' 'from' / 'at' [the] 'trickle'"))
    {

      if (! TP->drink_soft(amount)) 
        {
          write ("You cup your hands under the steady trickle of water " +
                  ", but you are too full to drink any more!\n");
            say ("Water overflows from "+QCTNAME(TP)+"'s cupped hands.\n");
          //top it off anyway.
          TP->drink_soft(TP->drink_max() - TP->query_soaked());  
        }
        else
          {
        write ("You cup your hands under the steady trickle of water " +
               "and drink the ice cold mountain water.\n");
        say(QCTNAME(TP)+ " cups "+HIS(TP)+ " hands under the steady trickle "+
            "of water and drinks the ice cold mountain water.\n");
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
                   "[the] %o [from] [at] [the] [trough]", 
                   animal))
  {
        say (QCTNAME(TP)+" leads "+HIS(TP)+" "+animal->short()+
             " to the trough and waters "+animal->query_objective()+".\n");
        write ("You lead your " +animal->short()+
               " to the trough and water "+animal->query_objective()+".\n");

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



int
do_buy(string str)
{
object oats;
int i,j,food, num_oats=1;

if (!str)
  {
    notify_fail ("Buy what?\n");
    return 0;
  }

if (!dola) 
  {
    notify_fail ("The stable keep is not here!\n");
    return 0;
  }

         if (TP->query_race_name() == "goblin")
           {
             dola->command("shout A goblin!!");
             dola->command("panic");
             return 1;
           }

//buying oats: player can either type "buy oats" or "buy 20 oats"

if (
    (parse_command(str,ENV(TP),
                       "%d 'oats'",
                       num_oats)) 
    ||
    
    (str=="oats")
    )
  {

    if (num_oats>10)
      {
        dola->command("say 10 bags at a time is about all I can handle!");
        return 1;
      }

    if (TOTAL_MONEY(TP)<(288*num_oats))
      {
        notify_fail("You don't have enough money!\n");
        return 0;
      }
    for (i=0;i<num_oats;i++)
      {
        oats=clone_object(CALATHIN_DIR+"obj/oats.c");

        if (!oats->move(TP))
          {
            if (!MONEY_ADD(TP,-288))
              return 0;
      }
    else
      {
        notify_fail("You decide the little bag of oats is too much to "+
                    "carry around.");
        return 0;
      }
        
      }
    dola->command("emote opens the metal feed box.");
    dola->command("emote takes a metal scoop off a hook on the wall, "+
                   "and paper bags from a stack.");
    dola->command("emote whips the paper bags through the air, opening "+
                   "and filling them with a snap.");
    dola->command("emote delivers the oats with a smile, then "+
                   "replaces the scoop to its hook with a "+
                   "practiced flourish.");

    if (num_oats==1)
      dola->command("say Just one bag today then?");

    return 1;
        
  }
}



