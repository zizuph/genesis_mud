#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";


void
create_nov_room()
{
                   
    set_name("Laboratory");
    add_name( ({ "room", "hall", "corridor", "laboratory" }) );

    set_short("You are in the northwestern section of the great Laboratory of " +
    "The Necromancers of Vile Darkness");
    
    set_long("You are in the northwestern section of the great Laboratory of " +
    "The Necromancers of Vile Darkness. The walls are covered with shelves " +
    "filled with components and results of old experiments. You don't " +
    "know whether the experiments were a success or failure, it is " +
    "hard to tell really. The workbench is cluttered with the " +
    "paraphernalia used in the art of Alchemy. A skull hangs " +
    "on an attachment on the workbench. Next to it lies a " +
    "heap of broken and dirty glass tubes where liquids and " +
    "substances are leaking out on the floor leaving its permanent mark. As you look at the " +
    "floor it is hard to find a single spot that is not stained or " +
    "scorched from fires or explosions.\n");
    
    add_item(({"wall", "walls"}),
     "The stone walls are covered in a mixture of various substances " +
     "from the many experiments performed over the years.\n");
     
    add_item(({"shelf", "shelves"}),
     "The wooden shelves are stained and partly rotten, yet still " +
     "trusted to carry a huge amount of components.\n");
     
    add_item(({"components"}),
     "It is hard to make out what sort of components are placed on " +
     "the shelf, as they are all more or less mixed with each other.\n");
     
    add_item(({"results"}),
     "They are resulsts, but of what you have no idea.\n");
     
    add_item(({"paraphernalia"}),
     "You don't know who the paraphernalia belongs to, but " +
     "as long as you put them back it should be safe to use them.\n");
     
    add_item(({"heap"}),
     "You would rather create your own mess than look at someone elses.\n"); 
     
    add_item(({"broken tubes"}),
     "These tubes are broken, and as such rendered completely useless to you.\n"); 
     
    add_item(({"floor"}),
     "Stains and burn marks can be seen everywhere on this cold stone floor.\n");  
     
    add_item(({"vials"}),
     "These are glass vials, normally used to hold magical liquids " +
     "brewed in the laboratory.\n");
     
    add_item(({"skull", "stand"}),
     "This is a human skull. It's teeth are replaced with " +
     "a series of razor-sharp iron cutters that seems to be " +
     "very capable of cutting though wood if you should " +
     "desire to feed it some. It is attached to a stand on the workbench, and " +
     "a bowl is placed under it to collect whatever the remains of what " +
     "you would feed the skull with.\n");
     
     add_item(({"bowl"}),
     "This is a bowl made of stone. You see some tiny bits of " +
     "sawdust resting in its center.\n");
     
    add_item(({"glass-tubes"}),
     "There are the sort of glass-tubes that is normally used for distillation.\n");
     
    add_item(({"mortar", "mortars"}),
     "The mortars are used together with a pestle to pound, grind and mash anything put in it.\n");
     
    add_item(({"jars"}),
     "These jars are just waiting for you to fill them with body parts " +
     "or herbs for future use in your experiments.\n");
     
    add_item(({"heater"}),
     "You had better not use this heater for anything else than your " +
     "distillations. You remember the punishment you got from the " +
     "Arch Magus the last time you decided to bring in one of your " +
     "pet skeletons to set it on fire.\n");          
        
        

    add_exit(NOV_DIR + "temple/nclab",   "southeast");
    
    setuid();
    seteuid(getuid());  
    
    clone_object(NOV_DIR +"obj/labbench")->move(this_object());


}

