/*
 * Weanting post office
 * Varian - March 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Gondor/common/lib/post.c";

void

create_room()

{
    set_short("Post office in Weanting");
    set_long("You have entered a small building in Weanting which seems to serve as a " +
        "post office for the woodsmen of Mirkwood forest. There are several small " +
        "desks which all offer a quiet place to sit while you either compose or read " +
        "any of your mail. You also notice that on the northern wall, a bronze " +
        "plaque has been mounted. Against the western wall, there are " +
        "a number of pigeons in their cages, available for hire if you might " +
        "need their service. In the eastern wall, there are several windows which " +
        "allow light into the post office and a door which leads back out into " +
        "the village.\n");
  
    add_item(({"building", "office", "post office"}),
        "You have entered a small building in Weanting which seems to serve as a " +
        "post office for the woodsmen of Mirkwood forest. There are several small " +
        "desks which all offer a quiet place to sit while you either compose or read " +
        "any of your mail. You also notice that on the northern wall, a bronze " +
        "plaque has been mounted. Against the western wall, there are " +
        "a number of pigeons in their cages, available for hire if you might " +
        "need their service. In the eastern wall, there are several windows which " +
        "allow light into the post office and a door which leads back out into " +
        "the village.\n", );
    add_item(({"desk", "small desk", "desks", "small desks"}),
        "There are many small desks here, each containing available ink, paper and " +
        "with a small oil lamp sitting atop it. You could choose to sit down at any " +
        "of these desks for a comfortable place to read or compose any of your mail.\n", );
    add_item(({"ink", "ink bottle", "ink bottles"}),
        "Each of the small desks here has an ink bottle sitting on top of it, clearly " +
        "to allow an individual to take the quill and compose a letter.\n", );
    add_item(({"quill", "quills"}),
        "There is a quill that goes with every ink bottle, they are used to write " +
        "on the paper.\n", );
    add_item(({"paper", "papers"}),
        "Every one of the small desks has some paper for you to write on should you " +
        "wish to compose a letter.\n", );
    add_item(({"lamp", "lamps", "oil lamp", "oil lamps"}),
        "There are several oil lamps, one sitting on top of each of the small desks. " +
        "All of the lamps are lit, providing enough light to easily read or write by.\n", );
    add_item(({"chair", "chairs"}),
        "There are several chairs, one for each desk actually. They are just regular " +
        "chairs, nothing special, just a place to sit while you read or write.\n", );
    add_item(({"plaque", "bronze", "north wall"}),
        "There is a bronze plaque which has been hung on the northern wall. There are " +
        "some instructions written on it, if you wanted to read it.\n", );
    add_item(({"pigeon", "pigeons", "pigeon cages", "pigeon cage", "cage", "cages", "west wall"}),
        "There are many pigeon cages stacked up against the western wall, most of them containing " +
        "a pigeon for hire. Hiring these pigeons will help you contact other people in the realms " +
        "without being inside a post office.\n", );
    add_item(({"east wall"}),
        "The east wall has the door and several windows, all looking back out into the " +
        "village of Weanting.\n", );
    add_item(({"south wall"}),
        "The south wall of the post office is just a plain wooden wall, there is nothing " +
        "of interest to examine here.\n", );
    add_item(({"window", "windows"}),
        "There are several windows here in the east wall, helping the post office feel " +
        "a little bit more open and brighter. Looking through the windows, you can see " +
        "the village of Weanting outside.\n", );
    add_item(({"door", "wooden door"}),
        "This wooden door leads back outside into the middle of Weanting.\n", );
    add_item(({"ceiling", "up", "beam", "beams", "wooden beam", "wooden beams"}),
        "The ceiling of the general store is of fairly simple construction, with " +
        "several wooden beams spanning the distance between the walls.\n", );
    add_item(({"floor", "down", "plank", "planks", "wooden plank", "wooden planks"}),
        "The floor of the post office has been constructed with wide wooden planks " +
        "which have been well worn with traffic. The floor appears to be well " +
        "maintained and in good condition.\n", );
    add_item(({"wall", "walls", "wooden wall", "wooden walls"}),
        "There are four walls here, all made of wood. Did you want to examine one of " +
        "them in particular?\n", );
    
    create_post();
    add_prop(ROOM_I_INSIDE,1);
    
    add_exit("/d/Gondor/rhovanion/mirkwood/woodsmen/weanting2", "east", "@@village@@");
}

int
village()
{
    write("\n\nYou leave the post office and step back outside into the village of " +
        "Weanting.\n\n");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_read","read");
}

int
do_read(string str)

{
    
    if(!str)
    {
        notify_fail("Read what? The plaque?\n");
        return 0;
    }
    
    if((str != "sign") && (str != "plaque"))
    
    { 
        notify_fail("Read what? The plaque?\n");
        return 0;
    }
    
    write("As there are many people busy reading and writing their mails here, please " +
        "be considerate and keep your conversations to a minimum.\n\n"+
        "Pigeons - 1 Silver\n");
    SAYBB(" reads the plaque on the northern wall.");
    return 1;
}

/*
enter_inv(ob, from)
{
    object reader;
    object vote_room;
    string *masters;

    ::enter_inv(ob, from);

    if (!living(ob))
        return;
    if (present("mailreader", ob)) return;
    reader=clone_object("/secure/mail_reader");
    reader->move(ob, 1);
}

leave_inv(ob, to)
{
    object reader;
  
    ::leave_inv(ob, to);
    reader = present("mailreader", ob);
    if (reader) reader->remove_object();
}
*/
