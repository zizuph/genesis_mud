/*
 * The flowerpot->thermite->melted safe was Sorgum's idea but he 
 * never finished it.
 *   Modified by Lilith, Dec 2021: cleaned it up and got it working.
 *               Lilith, Feb 2022: updated fail message with syntax help.
 *
 *  Purpose: This the main quest object for the Cottage Chest Quest.
 *           It handles the melting of the lock, cloning the new  
 *           chest, and giving the quest experience. 
 *
 */

inherit "/std/container";
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"
#include <stdproperties.h>
#include <macros.h>   
#include "../local.h"

int on_safe = 0;
object safe;

void
do_quest_reward(object me)
{

    if (!me->test_bit("Terel", COTTAGE_CHEST_GROUP, COTTAGE_CHEST_BIT)) 
	{ 
        // Reward 500 experience
        me->set_bit(COTTAGE_CHEST_GROUP, COTTAGE_CHEST_BIT);
        me->add_exp_quest(COTTAGE_CHEST_EXP);	
        me->catch_msg("You feel a bit more experienced!\n");
		write_file(QUEST_LOG, TP->query_cap_name() + " melted the "+
        "lock (cottage chest quest) and got "+ COTTAGE_CHEST_EXP +
		"qexp "+ ctime(time()) + "\n");
	}
	
	me->catch_msg("What a rush! You've melted the lock and "+
        "cracked open the steel chest!\n");

}

void
init()
{
     add_action("mix",    "mix");
     add_action("mix",    "grind");
     add_action("ignite", "ignite");
     add_action("ignite", "spark");
     add_action("set",    "set");
     add_action("set",    "place");
     ::init();
}

void
create_container()
{
    set_name("pot");
    set_short("flower pot");
    set_pshort("flower pots");
	set_long("This is a clay flower pot with a small hole in the " +
		  "bottom. You can <mix> soil and other things up in it.\n");
	set_adj(({"clay", "flower"}));
	 
	add_prop(OBJ_I_VALUE, 10 + random(20));

	add_prop(CONT_I_WEIGHT, 1000);
	add_prop(CONT_I_MAX_WEIGHT, 8000);
	add_prop(CONT_I_VOLUME, 2000);
	add_prop(CONT_I_MAX_VOLUME, 8000);
	add_prop(CONT_I_TRANSP, 1);
	add_prop(CONT_I_RIGID, 1);
	
	seteuid(getuid(this_object()));
}

int
mix(string str)
{
     int ok = 0;
     int flake_count = 0;
     int al_count = 0;
     int extra_objs = 0;

	 // what's in there?
     foreach (object ob : all_inventory(TO)) 
	 {
        if (ob->id("is_ironoxide"))
          flake_count++;
        else if (ob->id("is_aluminum"))
           al_count++;
        else extra_objs++;
     }
	 
     say(QCTNAME(TP) + " mixes something in the flower pot.\n");

     // mixing this in is bad!
     if (present("gunpower"))
     {
       write("You mix everything together, setting off a chemical "+
         "reaction that suddenly explodes!\n");
       say(QCTNAME(TP) + " sets off a chemical reaction that causes "+
          "a small explosion!\n");	   
       TP->heal_hp(-(TP->query_hp() / 7)); // hurts, but not too much
       set_alarm(1.0, 0.0, &remove_object());
	   return 1;
     }	 
     // too much stuff in there makes goo. 
     if (extra_objs > 2) 
     {
	   write("You mix the contents together and produce " +
		 "a mess in the flower pot.\n");
       all_inventory()->remove_object();
       clone_object("/d/Terel/common/moor/obj/goo")->move(TO, 1);
	   return 1;
     }
     // The right ingredients are mixed together.     
     if ((flake_count == 3 && al_count == 1)) 
     {
        ok = 1;
	    write("You mix the ingredients together carefully and " +
		    "produce a new compound.\nNow all you need to do is "+
			"find a good spot to <place> it.\n");
        all_inventory()->remove_object();			
	    clone_object(OBJDIR + "thermit")->move(TO, 1);
	  return 1;
     }
	 
     else 
     {
       // missing something needed to make the thermit
	   if (!ok)
       {		   
         write("There is not much to mix, but you mix it up anyway.\n");
         return 1;
	   }		 
	 }
     
     return 1;
}

int      
set(string str)
{
     object *objlist;

     safe = present("_cottage_safe", environment(TP));
     if (!safe) 
		 safe = present("_cottage_safe", environment(TO));
  
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) +" what on what?\n");
        return 0;
    }		
    if (parse_command(str, ({ }),
        " [flower] 'pot' 'on' [the] [steel] 'chest'", str))
    {  
	  if (safe) 
      {
	       write("You place the flower pot on the chest.\n");
	       say(QCTNAME(TP) + " places the flower pot on the chest.\n");
		   write("Now all you need to do is find a way to <ignite> it "+
			  "without burning yourself up.\n");
	       on_safe = 1;
		   return 1;
	  }
	  else 
      {
	       write("There is no chest here.\n");
           return 1;
	  }
	}
    else
    {
        write("You place the flower pot there but it doesn't seem "+
           "to be the right spot so you pick it up again.\n");
        return 1;
    }
     	
   write("Place the flower pot on what?\n");    
   return 1;
}
 

int
ignite(string str)
{
     object ribbon, thermit, gunpowder, cracked_safe;

     string self;
     int i;

    if (!str)
    {
        notify_fail("Ignite what?\n");
		return 0;
	}
    if (parse_command(str, ({ }),
        " [the] [metal] [magnesium] 'ribbon'", str))
    {
        ribbon = present("_mag_ribbon");
        if (!ribbon) 
	    {
            write("You need something to <ignite> the mixture with, "+
            "something that will burn long enough for you to step "+
		    "away so you don't go up in flames.\n");
	        return 1;
        }

        write("You ignite the ribbon and it burns so brilliantly "+
        "it hurts your eyes to look at it.\n");

        say(QCTNAME(TP) +" causes something to burn so brilliantly " +
	    "it hurts your eyes to look at it.\n");
     
        gunpowder = present("_safe_gunpowder");
        if (gunpowder) 
        {
            write("The black powder in the pot ignites and explodes!\n");
	        say("The black powder in the pot ignites and explodes!\n");
	        write("You are hurt by the explosion!\n");
	        say(QCTNAME(TP) + " is hurt by the explosion!\n");
	        TP->heal_hp(-(TP->query_max_hp() / 4));
	        TO->remove_object();  
	        return 1;
        }

        thermit = present("_cottage_thermite");
        if (ribbon && thermit) 
	    {
	        say("The ribbon ignites the thermite in the pot " +
	        "and it burns VERY hot. The molten mixture seeps " +
            "through the hole in the bottom of the pot...\n");
	        write("The ribbon ignites the thermite in the pot " +
	        "and it burns VERY hot. The molten mixture seeps " +
            "through the hole in the bottom of the pot...\n");  
			
            if (on_safe) 
            {
				all_inventory()->remove_object();
	            tell_room(ENV(TP), "The thermite slags the surface of "+
                "the trunk and melts a large hole in it!\n");
		        cracked_safe = clone_object(OBJDIR + "cracked_safe");
		        cracked_safe->move(environment(TP));
				// pot isn't destroyed, so reset it.
				on_safe = 0;
				do_quest_reward(TP);
                // removal of old safe handled by new safe.
                remove_object();
                return 1;		        
            }				    
            else 
            {
			    // remove contents of the pot
                all_inventory()->remove_object();
                if (environment(TO) == TP) 
		        {		  			
		           write("The burning mixture seeps on to you and " +
			       "melts your flesh!  You are severly burned!\n");
		           say("You smell buring flesh as the thermit seeps "+
		           "onto " + QCTNAME(TP) + " and MELTS them!\n");
		           TP->heal_hp(-(TP->query_max_hp() / 2));
		           TP->do_die(TO);
                           remove_object();
				   return 1;
		        }
		        else 
		        {
		            tell_room("...and slags a hole in the floor.\n");
                            remove_object();
                            return 1;
		        }
	        } 
        }
	return 1;
    }
    // leave whatever is there in the pot, just dest the ribbon.
    tell_room("The mixture in the flower pot ignites, but the fire "+
        "almost immediately fizzles out.\n");
    ribbon->remove_object();
    return 1;
     
}     
