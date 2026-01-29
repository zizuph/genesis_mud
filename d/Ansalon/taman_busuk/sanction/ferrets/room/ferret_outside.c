/*
 * ferret_outside.c
 * Outside the ferret shack, has two quest items.
 * 
 * Ares, July 2004
 *
 * Navarre July 3rd, Fixed typo ware changed to wear 
 * Mirandus February 19th, 2015 - Updated strings for quest
 */


#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

inherit "/d/Ansalon/taman_busuk/sanction/std/o_room_base";

int did_quest7;
int did_quest8;
int do_dig(string str);
int do_weed(string str);

void
reset_sanction_room()
{
    did_quest7 = 0;
    did_quest8 = 0;
}

create_sanction_room()
{
    set_short("The backyard behind the ferret shack");
    set_long("This is the backyard, if you can call it that. Instead of green "+
    "grass there's a lava flow. A barrier made of stone protects the house from "+
    "any rogue lava. The rundown house has stood for a good ten years already "+
    "so lava shouldn't be a worry. The house sits smack in the middle of two Dragonarmy "+
    "encampments. By the steps to the door are several small crosses "+
    "sticking up from the dirt. \n");
    
    add_item(({"barrier", "barrier of stone"}),
    "This barrier was constructed a long time ago to protect the house from any "+
    "lava that might deviate from it's normal flow. The barrier is strong and "+
    "unmoving and does it's job very well. \n");
    
    add_item(({"lava", "lava flow"}),
    "Lava flows down from each of the Lords of Doom. This paticular flow comes "+
    "from the southern volcano, Mount Duerghast. \n");
    
    add_item(({"house"}),
    "A very neglected house, but a well-built house. \n");
    
    add_item(({"dragonarmy", "camp", "encampments", "dragonarmy encampments"}),
    "To the east you can see the camp of the Highlord Kitiara. She commands "+
    "some of the best sword fighters in all of Krynn. To the northwest is "+
    "the camp of the Red Dragon Army. Controlled by the Emperor of Krynn "+
    "himself, they are the largest and most powerful Dragon Army of them "+
    "all. \n");
    
    add_item(({"Mount Duerghast", "volcano"}),
    "Mount Duerghast is south of here. A very ancient volcano, it's lava flow "+
    "is what makes the city of Sanction glow at night. \n");
    
    add_item(({"crosses", "cross"}),
    "There are fourteen crosses here. Each one placed there to honour a ferret "+
    "who passed away some time ago. Each cross has a name on it. \n");
   
    add_item(({"step", "steps"}),
    "These wooden steps lead up to the shack. A bunch of weeds have somehow "+
    "found a home under these steps. You catch a glimpse of a long rock "+
    "through the weeds. \n");
    
    add_item(({"name", "names"}),
    "There are seven crosses here, but between age and wear, they are "+
    "unreadable. \n");
    
     add_item(({"dirt"}),
    "The owner of the shack has placed fresh dirt all along the front of his house. "+
    "This is where the ferrets rest in peace. There is a small mound of it "+
    "to the right of the steps.\n");
    
    add_item(({"mound"}),
    "A small mound of dirt is raised up about four inches from the ground. "+
    "It looks like it could be a gravesite for a small rodent. Perhaps you "+
    "could 'dig up' the dirt to see what exactly it is? \n");
    
    add_item(({"rock", "long rock"}),
    "There is a long rock under the wooden steps. You'd get a better look at "+
    "it if it weren't for those pesky weeds. \n");
    
    add_item(({"weeds"}),
    "Weeds do grow everywhere. Some have found simple life in this little "+
    "plot of dirt, even in the extreme heat. If you wanted to help you could "
	+"probably weed them\n");
    
     add_exit(ROOM_DIR + "ferret_backroom", "backroom");
     
     reset_sanction_room();
}

void
init()
{
    ::init();
    add_action(do_dig,"dig");
    add_action(do_weed,"weed");
}

int
do_dig(string str)
{
    notify_fail("Dig what?\n");
    if((!str) || (!strlen(str)) || (str != "up mound")
		&& (str != "mound") && (str != "dirt") && (str != "up dirt"))
        return 0;

    if(did_quest7)
    {
        write("You dig up the mound of dirt but find nothing.\n");
        say(QCTNAME(TP)+" digs up the mound of dirt but finds nothing. \n");
        return 1;
    }

    did_quest7=1;

    write("With your hands, you dig up the fresh mound of dirt and "+
        "find a box in the small grave.\n");
    say(QCTNAME(TP)+" digs up the dirt and finds a small box.\n");

    reset_euid();

    clone_object(OBJ_DIR + "coffin")->move(TO);

    return 1;
}

int
do_weed(string str)
{
    notify_fail("Weed what? The weeds?\n");
    if((!str) || (!strlen(str)) || (str != "weeds")
		&& (str != "the weeds"))
        return 0;

    if(did_quest8)
    {
        write("You've already done this before, no need to do it again.\n");
        say(QCTNAME(TP)+" has already done this before, no need to do it again. \n");
        return 1;
    }

    did_quest8=1;

    write("You begin to weed the weeds underneath the steps and eventually "+
        "you find a long gravestone rock. \n");
    say(QCTNAME(TP)+" weeds through the weeds and finds something. \n");

    reset_euid();

    clone_object(OBJ_DIR + "rock")->move(TO);

    return 1;
}

    