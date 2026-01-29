/*
 * Cave/dragon's lair
 * By Nerull, August 2009
 * 
 */

#include "defs.h"
#include <macros.h>

#define ALLOW_PASS   "_i_am_allowed_lair"

inherit DRAGON_BASE;

string extra_line = "";

int not_accept_tablet = 0;

void
create_room()
{
    set_short("At the rocky base of a tall mountain");
    set_long(dragon_lair_desc3(extra_line));

    set_groove();
   
    reset_room();

    
    
    add_exit(DRAGON_DIR + "rooms/d2", "south");
    
}

void
reset_tablet()
{
	
	 not_accept_tablet = 0;
	 return;
}


int
do_insert(string str)
{
	
	    object dragon_tablet;
	
	
	    if (str != "tablet into socket")
	    	{
	    		
	    		write("Insert tablet into socket, perhaps?\n");
	    		return 1;
	    	} 
	
	    if (objectp(dragon_tablet = present("_dragon_tablet1", this_player())))
       {
               
               if(not_accept_tablet == 1)
               	{
               		
               		write("The red-painted jade tablet is repelled by the socket by some uknown force.\n");
                  return 0;
                }
                  
           write("You put the red-painted jade tablet into the small square socket in the north"+
           "wall.\nThe red-painted jade tablet clicks into place and stays there for a brief "+
           "moment, before it slowly fades away into nothingness.\n");

           tell_room(environment(this_player()), QCTNAME(this_player())+" puts a red-painted jade tablet"+
           "into the small square socket in the north wall.\nThe red-painted jade tablet clicks into place"+
           "and stays there for a brief moment, before it slowly fades away into nothingness.\n", this_player());
            
           dragon_tablet->remove_object();
           
           not_accept_tablet = 1;
           
           set_alarm(600.0,0.0, &reset_tablet());
           
           write("\nSuddenly, you are teleported elsewhere by a magical force!\n\n");
           
           this_player()->add_prop(ALLOW_PASS, 1);
           tell_room(DRAGON_DIR + "rooms/d4", this_player()->query_name() + " slowly materializes!\n", this_player());        
           tell_room(environment(this_object()), this_player()->query_name() + " suddenly fades away and is no longer here.", this_player());
           this_player()->move_living("M", DRAGON_DIR + "rooms/d4", 1);           
           
           
          
           return 1;
       }
       
    write("You dont have the propher tablet for the socket.\n");
    return 1;
}
	

void
init()
{
    ::init();


    add_action(do_insert, "insert");
    
   
}


void
reset_room()
{
}
