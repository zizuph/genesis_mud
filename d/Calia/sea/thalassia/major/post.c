
/* 	Post Office of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/


#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

#define MAILREADER "/secure/mail_reader"

string messages;

int
query_prevent_snoop()
{
    return 1;
}

void
create_water_room()
{
    set_short("Post Office of Thalassia");
    set_long("You have entered the post office of this city. "+
        "You see many different booths that allow you to read "+
        "and write mail in privacy. On the wall is a poster "+
        "which reads:\n"+
        "The commands are:\n"+
        "   read             Read your mail.\n"+
        "   mail <name>      Mail to player 'name'.\n"+
        "   from             List all headers.\n"+
        "\n"+
        "There is a door to the east that leads back out to "+
        "the Major Zone of the city.\n");
    add_item("door","The door is open and leads back out to "+
        "the Major Zone of the city.\n");
    add_item(({"booth","booths"}),"The booths are seperated by "+
        "small walls so that each person has privacy while reading "+
        "and writing their mails. Inside each of the booths you see "+
        "a pencil and some vellum.\n");
    add_item("pencil","Upon closer inspection you see that the "+
        "pencils are actually wax pencils, a good instrument to "+
        "use for writing in this underwater post office.\n");
    add_item("vellum","After a small bit of investigation you notice "+
        "that the vellum has some type of coating on it, making it "+
        "waterproof. This is a good thing since you are underwater in "+
        "a post office afterall.\n");
    add_item(({"wall","small wall","walls","small walls"}),"The small "+
        "walls are made out of carved marble, and seperate the booths, "+
        "giving their occupants privacy from each other.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);
    add_swim_exit(THALM+"major14","east",0,1);
}

void
init()
{
    object reader;

    ::init();
    reader = clone_object(MAILREADER);
    if(!reader)
    {
        write("There appears to be no booths empty at this time.\n");
        return;
    }
    reader->move(this_player());
}

void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob);

    if (reader = present("mailread", ob)) 
        reader->remove_object();
}
