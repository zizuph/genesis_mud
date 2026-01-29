/*
 * ferret_kitchen.c
 * Kitchen within the Ferret Shack, has a quest item.
 * T
 * Ares, July 2004
 *
 * Navarre July 3rd 2006, Fixed Typo.
 * Mirandus February 19th, 2015 - Updated strings for quest
 */

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <ss_types.h>
#include <money.h>
#include "../defs.h"

inherit "/d/Ansalon/taman_busuk/sanction/std/i_room_base";

int did_quest4;
int did_quest5;
int did_quest6;
int do_explore(string str);
int do_open(string str);
int do_reach(string str);

void
reset_sanction_room()
{
   
   did_quest4 = 0;
   did_quest5 = 0;
   did_quest6 = 0;
      
}

void
create_sanction_room()
{
    set_short("A small kitchen within the ferret breeding shack");
    set_long("This is the run-down kitchen within the shack. There is dirt and "+
        "grime everywhere, obviously nobody tends to it. A wood stove "+
        "sits in the far corner with a stack of wood right next to it. Cupboards "+
        "line the northern wall and a broom closet sits in the opposite corner "+
        "of the wood stove. A kitchen table with four chairs sits in the middle "+
        "of the room on top of a large dirty area rug. A window on the eastern wall "+
        "gives the lovely view of the lava flow. \n");
    
    add_item(({"dirt", "grime"}),
        "Dirt is everywhere. Grime is on top of the dirt. On top of the "+
        "grime is dust, but not as much as there is dirt and grime. \n");
        
    add_item(({"dust"}),
        "Dust is on everything! The hot air of Sanction sticks the dust "+
        "on everything it touches, making it hard to remove even the "+
        "smallest layer of dust. \n");
        
    add_item(({"stove", "wood stove"}),
        "This wood stove serves two purposes. It cooks the food and heats the house. "+
        "A stack of wood about two feet high stands right next to it. You can see a shiny "
		+"object behind the stove. If you reach far enough you could probably reach for it.\n");
    
    add_item(({"wood", "stack of wood", "pile of wood", "wood pile"}),
        "A stack of wood about two feet high and six feet wide. "+
        "When the ferrets are allowed "+
        "out of their cages this is a hot spot, as there are many places to "+
        "hide things and to hide themselves. There is probably a lot "+
        "of shiny objects if you explore the pile of wood. \n");
    
    add_item(({"cupboards", "cupboard"}),
        "Long cupboards line the walls. The doors have been taken off. "+
        "The cupboards have various dishes and other kitchenware.\n");
        
    add_item(({"dishes", "kitchenware", "cups", "plates"}),
        "Everything from glasses and cups to plates and strainers can be found "+
        "in these cupboards. You'd explore further but you don't want to break "+
        "anything. \n");
    
    add_item(({"closet", "broom closet"}),
        "A six foot high burgundy broom closet sits in the corner. It has a "+
        "door that you could open if you wish. It is very dark behind the broom "+
        "closet. \n");
    
    add_item(({"table", "chairs", "table and chairs"}),
        "A very nice wooden kitchen table with four chairs sits in the middle "+
        "of the room. The quality of the table itself puts the rest of the house "+
        "to shame. It sits on a large dirty area rug.\n");
        
    add_item(({"window", "wall", "eastern wall"}),
        "A large window is in the eastern wall. From this viewpoint, you can see "+
        "the southern Lord of Doom in all it's greatness. Also, a lovely view of the "+
        "river of lava that flows beside the house. \n");
        
    add_item(({"rug", "area rug"}),
         "A large dirty area rug sits underneath the table. It has collected "+
         "not only dirt, but lots of ferret fur as well. \n");
         
    add_item(({"fur", "ferret fur"}),
        "The fur is everywhere! Ferrets sure do shed a lot! How can anyone have "+
        "a meal in this house without getting some hair in it? \n");
    
    add_item(({"corner"}),
        "Out of the four corners in the room, two are bare, the far corner has "+
        "a wood stove and the other one has a broom closet in front of it. \n");
        
    add_item(({"far corner"}),
        "The wood stove blocks the corner, but you can see a shiny object "+
        "behind the stove. If you reach far enough you could probably reach for it. \n");

     add_exit(ROOM_DIR + "ferret_breeder_room", "front");
     add_exit(ROOM_DIR + "ferret_backroom", "backroom");
     
     reset_sanction_room();

     
}

void
init()
{
    ::init();
    add_action(do_explore,"explore");
    add_action(do_open,"open");
    add_action(do_reach,"reach");

}


int
do_explore(string str)
{
    notify_fail("Explore what?\n");
    if((!str) || (!strlen(str)) || (str != "the pile of wood")
		&& (str != "pile of wood") && (str != "wood") && (str != "pile"))
        return 0;

    if(did_quest4)
    {
        write("There is still nothing in the wood. \n");
        return 1;
    }

    did_quest4=1;

    write("You get on your hands and knees and begin to pull on the logs "+
        "piece by piece. After all that work you don't find a single thing. "
		+"You stack the logs as nice as they were before you started. \n");
    say(QCTNAME(TP)+" pulls the logs apart, and after finding a whole lot of "+
        "nothing, begins to stack the logs as they were before.\n");

    reset_euid();

    return 1;
}

int
do_open(string str)
{
    notify_fail("Open what?\n");
    if((!str) || (!strlen(str)) || (str != "broom closet")
		&& (str != "closet"))
        return 0;

    if(did_quest5)
    {
        write("It is already open. \n");
        return 1;
    }

    did_quest5=1;

    write("You open the broom closet to find an empty compartment. Odd that "+
        "there are no brooms in this closet. The inside of this closet is "+
        "probably the cleanest place in this house! Seeing nothing of "+
        "interest, you close the door.\n");
    say(QCTNAME(TP)+" opens the broom closet, then closes it again.\n");

    reset_euid();

    return 1;
}

int
do_reach(string str)
{
    notify_fail("Reach for what?\n");
    if((!str) || (!strlen(str)) || (str != "for shiny object")
		&& (str!= "for shiny object") && (str != "for object")
		&& (str != "object") && (str != "shiny object"))
        return 0;

    if(did_quest6)
    {
        write("There's nothing more of interest down there. \n");
        return 1;
    }

    did_quest6=1;

    write("You reach behind the stove and pick up a shiny object.\n");
    say(QCTNAME(TP)+" searches behind the wood stove.\n");

    reset_euid();
    
    clone_object(OBJ_DIR + "shiny_object")->move(this_player(),1);

    return 1;
}

