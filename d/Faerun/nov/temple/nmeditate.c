#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit "/lib/guild_support";
inherit NOV_DIR +"temple/std_room";

 
void
create_nov_room()
{
    
                   
    set_name("In the chamber of dark prayers");
    add_name( ({ "room", "hall" }) );


    set_short("In the chamber of dark prayers");
    set_long("Silence! This is the room where people come to focus " +
    "their thoughts. It is said that the most skilled Necromancers " +
    "are able to get a direct link into the vile dark energies. You " +
    "sense this room is standing out from the others by its especially " +
    "strong smell of death and decay. On the east wall you see a mural " +
    "showing a horde of skeleton warriors lead to battle by a " +
    "single necromancer easily overthrowing a stronghold, skeletons " +
    "using the fallen as a ladder climbing over the walls.\n");
    
    add_item(({"mural"}),
     "You admire the mural in detail.\n");

    
    add_exit(NOV_DIR +"temple/ncentral",   "east");
    


    
  
        
    
}

void gs_hook_start_meditate()
{
  write("You sit down to meditate. First you cannot see "+
        "anything but darkness, but as you focus deeper and deeper, you "+
        "slowly fall into a trance. You sense that you can change something "+
        "in your mind. You find yourself able to <set> your preferences. Just <rise> "+
        "from your trance when you have finished. You may also <restrict> yourself if you want to.\n");

}

void gs_hook_rise()
{
  write("As if ascending from a great depth, you return to the surface "+
        "of your consciousness. You feel strong and renewed as "+
        "you rise from the floor.\n");
}


void
init()
{
    ::init();

    init_guild_support();

}

