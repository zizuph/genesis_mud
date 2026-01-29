#include <stdproperties.h>
#include <macros.h>
#include <time.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";


public int 
blockmembers()
{
      
    if (this_player()->query_skill(COUNCIL))
    {
        
        write("Welcome, "+this_player()->query_name()+"!\n");
        return 0;
    }
    
     if (this_player()->query_guild_name_lay() != GUILDNAME)
    {
        write("You are not a member of the Necromancers of Velsharoon!\n");
        return 1;
    }

  
    write("Only Necromancer council members may go further up!\n");
        return 1;
}




 
void
create_nov_room()
{
    
        set_short("In the center of the grand library");
        set_long("This room is dimly lit and exceptionally dusty, and the dry smell of decayed " +
             "parchments gives its purpose away, for this is indeed an ancient library. There " +
             "are no bookshelves here, but to the east, west and south you catch a " +
             "glance of row after row of shelves filled with tomes and scrolls. A " +
             "square section of the stone floor is covered with a rug which muffles " +
             "the sounds of approaching footsteps. Smoking braziers responsible for " +
             "the eerie glow stand at each corner of the room, emitting a " +
             "harsh-smelling incense.\n");
        
        
        
        
        
        add_item(({"dust"}),
        "Dust can be seen everywhere, you guess it mostly comes from the ancient " +
        "tomes the Necromancers are studying every day.\n");
        
        add_item(({"parchments"}),
        "You see parchments on the shelves to your west, east and south, although " +
        "the tomes look a lot more interesting.\n");
        
        add_item(({"library"}),
        "This is one of Velsharoon's fabled libraries, where he allows " +
        "his Necromancers to come and study magic of ancient times.\n");
        
        add_item(({"shelf", "shelves"}),
        "There are no shelves here, but you can see some to the west, east and south.\n");
        
        add_item(({"floor"}),
        "The floor is made from large grey flagstone squares with dust filling " +
        "up the small wells.\n");
        
        add_item(({"rug"}),
        "This is circular rug has the responsibility to keep the sounds of " +
        "footsteps on the cold stone floor to a minimum. The rug has a the " +
        "mark of Velsharoon on it.\n");
        
        
       
      //  if (TIME2FORMAT(time(), "ddd") == "Fri") 
      //  {
       	
       	 //clone_object(NOV_DIR +"obj/tome")->move(this_object());
       	 
      // 	}
        
        
        add_exit(NOV_DIR +"temple/scorr1", "north");
        add_exit(NOV_DIR +"temple/neast_lib", "east");
        add_exit(NOV_DIR +"temple/nwest_lib", "west");
        add_exit(NOV_DIR +"temple/nsouth_lib", "south");
        //add_exit(NOV_DIR +"temple/ncouncil", "up", blockmembers);
        
        setuid();
        seteuid(getuid());       
}
        
