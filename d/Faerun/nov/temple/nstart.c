#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
                   
    set_name("In the chamber of resting");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("In the chamber of resting");
    set_long("Ahh! The room where you wake up every morning ready to " +
    "practice every sin you can. On the shelf here you recognize several " +
    "cages of small animals that you enjoy torturing just before " +
    "retiring from a long and eventful day. Several beds are arranged " +
    "here and you can't help but admiring the magic that is taking place " +
    "here to allow this much furniture in such a small room. Newly arrived " +
    "Necromancers may <claim> a bed here.\n");
    
     add_item(({"bed", "beds"}),
     "The beds are made of white bones, if you didn't know better you would think " +
     "they were extremely uncomfortable.\n");
     
     add_item(({"shelf"}),
     "The shelf is made of sturdy oak tree making it able to support heavy weight.\n");
     
     add_item(({"animals", "cage", "cages"}),
     "You see a variety of animals placed in different cages, all fearing the next torture by your hand.\n");
     

     add_exit(NOV_DIR + "temple/ncentral",   "north");
     
    setuid();
    seteuid(getuid());  
    
    clone_object(NOV_DIR +"obj/rcloset")->move(this_object());

}

int
do_start(string str)
{
        

        if(str != "bed")
    {
        write("Claim bed, perhaps?\n");
        return 1;
    }
    
    if (this_player()->query_guild_name_lay() != GUILDNAME)
    {
    	write("Only Necromancers of Velsharoon may claim a bed here.\n");
    	return 1;
    }

        
        this_player()->set_default_start_location(file_name(this_object()));
        write("You claim a bed as your own and from now you will start here when entering the game.\n");
        return 1;

}


void
do_torturea(string str)
{

       if (str != "animals")
       {
       	   return;
       	}
       	
       	
       	
      switch(random(5))
        {
            case 0:
                write("With a broad smile you punch a needle through " +
                "the leg of one of colourful birds in the cage.\n");
                
                tell_room(environment(this_object()), "With a broad smile, "+QCTNAME(this_player())+" punches " +
                "a needle through the leg of one of the colourful birds in the cage.\n",({this_player()}));
                
                break;
            case 1:
                write("A satisfactory grin shows on your face as you " +
                "pull off the tail of one of the white mice in the cage.\n");
                
                tell_room(environment(this_object()), "A satisfactory grin shows " +
                "on "+QCTNAME(this_player())+"'s face as "+this_player()->query_pronoun()+" pull " +
                "off the tail of one of the white mice in the cage.\n",({this_player()}));
                break;
            case 2:
                write("With a broad smile you punch a needle through " +
                "the leg of one of colourful birds in the cage.\n");
                
                tell_room(environment(this_object()), "With a broad smile, "+QCTNAME(this_player())+" punches " +
                "a needle through the leg of one of the colourful birds in the cage.\n",({this_player()}));
                break;
            case 3:
                write("With a broad smile you punch a needle through " +
                "the leg of one of colourful birds in the cage.\n");
                
                tell_room(environment(this_object()), "With a broad smile, "+QCTNAME(this_player())+" punches " +
                "a needle through the leg of one of the colourful birds in the cage.\n",({this_player()}));
                break;
            case 4:
                write("With a broad smile you punch a needle through " +
                "the leg of one of colourful birds in the cage.\n");
                
                tell_room(environment(this_object()), "With a broad smile, "+QCTNAME(this_player())+" punches " +
                "a needle through the leg of one of the colourful birds in the cage.\n",({this_player()}));
                break;
        }

       	
     
      
      
      
      return;
}

void init()
{
 add_action(do_start,"claim");
 add_action(do_torturea, "torture");
 ::init();
}
