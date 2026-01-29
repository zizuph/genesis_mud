/*
*Solace's Town Fountain
*Created By Leia
*June 03, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

/* Navarre August 21st 2006, added option for "the fountain" per bug report. */
/* Navarre March 11th 2007, changed add_exp to add_exp_quest, since add_exp is obsolete */

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

string
determine_adj()
{
    if(TO->query_prop(DIRTY))
        return "disgusting";
    else
	    return "wondrous";
}

string
determine_short()
{
    if(TO->query_prop(DIRTY))
        return "large disgusting fountain";
    else
	    return "large wondrous fountain";
}

string
determine_long()
{
    if(TO->query_prop(DIRTY))
	    return "This is a tall fountain, built in the likeness of a great vallenwood tree. Water falls from the branches and leaves into a large basin, before circulating to fall again. The fountain is very large, and at present is being used as both a bath tub and a latrine by the nearby armies.\n";
    else
	    return "This is a tall fountain, built in the likeness of a great vallenwood tree. Water falls from the branches and leaves into a large basin, before circulating to fall again. The water is clear, crisp, and looks as though it would be good to the taste.\n";
}

void
create_object()
{
    add_prop(DIRTY, 1);
    set_name("fountain");
    set_adj("large");
    set_adj(determine_adj());
    set_short("@@determine_short@@");
    set_long("@@determine_long@@");
    add_prop(OBJ_I_WEIGHT, 2000000); 	
    add_prop(OBJ_I_VOLUME, 5000000);
    add_prop(OBJ_M_NO_GET, "You and whose muscles are going to pick up this fountain?!\n");
}

void
init()
{
	::init();
	add_action("drink_water", "drink");
	add_action("empty_potion", "empty");
	add_action("dump_mix", "dump");
}

int
drink_water(string str)
{
    NF("Drink what?\n");

    if ((str == "from water") || (str == "water") || 
        (str == "from fountain") || (str == "water from fountain") ||
        (str == "from liquid") || (str == "from the fountain") ||
        (str == "water from the fountain"))
    {
        if (TO->query_prop(DIRTY))
        {
	        if (TP->drink_soft(TP->drink_max() / 16,0))
	        {
                  say(QCTNAME(TP) + " grimaces as " + HE(TP) + " takes a drink from the fountain.\n");
                  write("You drink some water from the fountain and barely keep it down. This tastes disgusting.\n");
                
                  if(TP->query_prop(DRINK_4))
                  {
                    write("Suddenly you don't feel so good. Your face turns green and you wretch all over the ground, expelling the foul liquid you just drank!\n");
	            say(QCTNAME(TP) + "'s face turns green. " + HE(TP) + " wretches violently, expelling a foul liquid all over the ground!\n");
                    TP->remove_prop(DRINK_4);
                    TP->remove_prop(DRINK_3);
                    TP->remove_prop(DRINK_2);
                    TP->remove_prop(DRINK_1);
                  }
                  
                  if(TP->query_prop(DRINK_3))
                  {
                    TP->remove_prop(DRINK_3);
                    TP->add_prop(DRINK_4, 1);
		  }
                
                  if(TP->query_prop(DRINK_2))
                  {
                    TP->remove_prop(DRINK_2);
                    TP->add_prop(DRINK_3, 1);
		  }
                
                  if(TP->query_prop(DRINK_1))
                  {
                    TP->remove_prop(DRINK_1);
                    TP->add_prop(DRINK_2, 1);
		  }
                  else
                    TP->add_prop(DRINK_1, 1);
                    return 1;
                }
                else
                  write("You couldn't drink anymore of this stuff if you tried.\n");
                return 1;
        }
        else
        {
	    if (TP->drink_soft(TP->drink_max() / 16,0))
	    {
	        say(QCTNAME(TP) + " takes a long, deep drink of the refreshing water, gasping for air when " + HE(TP) + " raises " + HIS(TP) + " head.\n");
		    write("You take a long, deep drink from this cool, refreshing water and find yourself gasping for air when you raise your head.\n");
		    return 1;
	    }
	    
            else
            {
              write("Unfortunately, you can't drink anymore of this AMAZING water.\n");
              return 1;
            }
         }
    return 0;
  }
}

int
empty_potion(string str, object room, object potion)
{
    str = lower_case(str);
    room = environment(TO);
     
    /* Check to see if they're trying to pour it into the fountain. */
    if((str != "potion into fountain") && (str != "potion into the fountain"))
    {
        write("Empty what into what? Do you want to empty something into the fountain?\n");
        return 1;
    }
    
    /* If it's actually aimed at the fountain... */
    else
    {
        /* Check if the potion is in the inventory */
        if(!present(P_NAME, TP))
        {
            write("Empty what?\n");
            return 1;
        }
        
        /* Define the potion for later removal */
        potion = present(P_NAME, this_player());
    
        /* Check if the fountain/room (The dirty in question is also a room property for purposes
           at the beginning of the quest.) is dirty */
        if(!TO->query_prop(DIRTY))
        {
            write("But the fountain is already clean!\n");
            return 1;
        } 
        
        /* This checks to see if the player has made the potion and that they've done it this log in. */
        if(TP->query_prop(OFF_LEAF) & TP->query_prop(OFF_WATER) & TP->query_prop(OFF_ANG) & TP->query_prop(OFF_FIR) & TP->query_prop(OFF_SAS))
        {
            /* Check to see if they've done the evil aligned version. */
            if(TP->test_bit("krynn", GROUP, E_BIT))
            {
                write("You've already dirtied the fountain, and now you want to clean it?! That's what I call redundant.\n");
                return 1;
            }
            
            /* Check if the player has done the good aligned version. */
            if(TP->test_bit("krynn", GROUP, G_BIT))
            {
                write("You empty the potion into the fountain. Almost instantaneously, the water becomes clear and drinkable.\n");
                /* Remove the props, remove the object */
                TO->remove_prop(DIRTY);
                room->remove_prop(DIRTY);
                TO->set_name("fountain");
                TO->set_adj("large");
                TO->set_adj(determine_adj());
                TO->set_short(determine_short());
                TO->set_long(determine_long());                
                TP->remove_prop(OFF_LEAF);
                TP->remove_prop(OFF_WATER);
                TP->remove_prop(OFF_ANG);
                TP->remove_prop(OFF_FIR);
                TP->remove_prop(OFF_SAS);
                potion->remove_object();
                /* Bad player! You can't do the quest twice! */
                write("Thank you for cleansing the fountain again, however there is no reward on your second attempt.\n");
                return 1;
            }
        
            /* Do the quest stuff. */
            else
            {
                write("You empty the potion into the fountain. Almost instantaneously, the water becomes clear and drinkable.\n");
                /* Remove the props, set bit, add experience, remove object */
                TO->remove_prop(DIRTY);
                room->remove_prop(DIRTY);
                TO->set_name("fountain");
                TO->set_adj("large");
                TO->set_adj(determine_adj());
                TO->set_short(determine_short());
                TO->set_long(determine_long());                
                TP->remove_prop(OFF_LEAF);
                TP->remove_prop(OFF_WATER);
                TP->remove_prop(OFF_ANG);
                TP->remove_prop(OFF_FIR);
                TP->remove_prop(OFF_SAS);
                TP->set_bit(GROUP, G_BIT);
                write("You feel a little more experienced!\n");
                TP->add_exp_quest(F_EXP);
                TP->adjust_alignment(F_ALIGN);
                potion->remove_object();
                K_QUEST_LOG("quest","Good Solace Fountain", TP, 3000);
                return 1;
            }

        }
        
        /* In case the player didn't make the potion himself. */
        else
        {
            write("But you did not create this potion! How do you know it is the right one for the job?!\n");
            return 1;
        }
    }
}

int
dump_mix(string str, object room, object mix)
{
    str = lower_case(str);
    room = environment(TO);
     
    /* Check to see if they're trying to dump it into the fountain. */
    if((str != "mix into fountain") && (str != "mix into the fountain"))
    {
        write("Empty what into what? Do you want to dump something into the fountain?\n");
        return 1;
    }
    
    /* If it's actually aimed at the fountain... */
    else
    {
        /* Check if the mix is in the inventory */
        if(!present(M_NAME, TP))
        {
            write("Dump what?\n");
            return 1;
        }
        
        /* Define the mix for later removal */
        mix = present(M_NAME, this_player());
    
        /* Check if the fountain/room (The dirty in question is also a room property for purposes
           at the beginning of the quest.) is dirty */
        if(TO->query_prop(DIRTY))
        {
            write("But the fountain is already dirty!\n");
            return 1;
        } 
        
        /* This checks to see if the player has made the mix and that they've done it this log in. */
        if(TP->query_prop(OFF_DUNG) & TP->query_prop(OFF_BEER) & TP->query_prop(OFF_CRO) & TP->query_prop(OFF_CUR) & TP->query_prop(OFF_POI))
        {
            /* Check to see if they've done the good aligned version. */
            if(TP->test_bit("krynn", GROUP, G_BIT))
            {
                write("You've already cleaned the fountain, and now you want to dirty it?! Are you nuts?!\n");
                return 1;
            }
            
            /* Check if the player has done the evil version. */
            if(TP->test_bit("krynn", GROUP, E_BIT))
            {
                write("You dump the mix into the fountain. Almost instantaneously, the water becomes filthy and disgusting.\n");
                /* Remove the props, remove the object */
                TO->add_prop(DIRTY);
                room->add_prop(DIRTY);
                TO->set_name("fountain");
                TO->set_adj("large");
                TO->set_adj(determine_adj());
                TO->set_short(determine_short());
                TO->set_long(determine_long());
                TP->remove_prop(OFF_DUNG);
                TP->remove_prop(OFF_BEER);
                TP->remove_prop(OFF_CRO);
                TP->remove_prop(OFF_CUR);
                TP->remove_prop(OFF_POI);
                mix->remove_object();
                /* Bad player! You can't do the quest twice! */
                write("Thank you for dirtying the fountain again, however there is no reward on your second attempt.\n");
                return 1;
            }
        
            /* Do the quest stuff. */
            else
            {
                write("You dump the mix into the fountain. Almost instantaneously, the water becomes filthy and disgusting.\n");
                /* Remove the props, set bit, add experience, remove object */
                TO->add_prop(DIRTY, 1);
                room->add_prop(DIRTY, 1);
                TO->set_name("fountain");
                TO->set_adj("large");
                TO->set_adj(determine_adj());
                TO->set_short(determine_short());
                TO->set_long(determine_long());                
                TP->remove_prop(OFF_DUNG);
                TP->remove_prop(OFF_BEER);
                TP->remove_prop(OFF_CRO);
                TP->remove_prop(OFF_CUR);
                TP->remove_prop(OFF_POI);
                TP->set_bit(GROUP, E_BIT);
                write("You feel a little more experienced!\n");
                TP->add_exp_quest(F_EXP);
                TP->adjust_alignment(-(F_ALIGN));
                mix->remove_object();
                K_QUEST_LOG("quest","Evil Solace Fountain", TP, 3000);
                return 1;
            }

        }
        
        /* In case the player didn't make the mix himself. */
        else
        {
            write("But you did not create this mix! How do you know it is the right one for the job?!\n");
            return 1;
        }
    }
}
