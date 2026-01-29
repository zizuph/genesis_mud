/*
 * Hargnak post office
 * Varian - June 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Gondor/rhovanion/mirkwood/goblins/post.c";

void

create_room()

{
    set_short("Post office in Hargnak");
    set_long("You have entered a wide, stone building which appears to " +
        "be a postal outlet for the village of Hargnak. You can see that a " +
        "large, stone table has been placed in the center of the room with a " +
        "crude, wooden sign hanging above it. Tucked up against the northern " +
        "wall, you see a dirty, iron cage which appears to be filled with " +
        "dozens of squeaking rats. Hanging from the ceiling, you see several " +
        "oil lamps providing light. A square opening in the southern wall " +
        "will take you back out into the middle of Hargnak.\n");
  
    add_item(({"building", "office", "post office"}),
        "This wide, stone building which appears to " +
        "be a postal outlet for the village of Hargnak. You can see that " +
        "a large table has been placed in the center of the room with a " +
        "rough, wooden sign hanging above it. Tucked up against the northern " +
        "wall, you see a dirty, iron cage which appears to be filled with " +
        "dozens of squeaking rats. Hanging from the ceiling, you see several " +
        "oil lamps providing light. A square opening in the southern wall " +
        "will take you back out into the middle of Hargnak.\n");
    add_item(({"table", "large table", "stone table"}),
        "This large stone table has a couple of wooden stools surrounding " +
        "it, offering a place for people to sit while they either read or " +
        "compose their mail. In the middle of the table, a couple of ink " +
        "bottles and quills rest beside some loose sheets of paper.\n", );
    add_item(({"ink", "ink bottle", "ink bottles"}),
        "These ink bottles are apparently here for people to use when " +
        "writing their letters. There are quills and spare sheets of " +
        "paper nearby.\n", );
    add_item(({"quill", "quills"}),
        "There are several quills here, although most of them appear to be "+
        "broken. However, there are enough good ones left that you can " +
        "compose a quick letter if you wish to.\n", );
    add_item(({"paper", "papers"}),
        "This paper is perhaps a bit torn and a bit dirty, but, still " +
        "clear enough for you to write a legible message upon.\n", );
    add_item(({"lamp", "lamps", "oil lamp", "oil lamps"}),
        "Hanging from the ceiling are several oil lamps, they seem to be " +
        "kept perpetually lit in order to provide enough light for you " +
        "compose a letter or two.\n", );
    add_item(({"stool", "stools"}),
        "These stools are solidly built out of wood and are scattered " +
        "haphazardly around the stone table. It seems that people will " +
        "occasionally use them when composing their mail.\n", );
    add_item(({"sign", "wooden sign", "crude sign"}),
        "This sign has some instructions if you would like to read it.\n", );
    add_item(({"rat", "rats", "rat cage", "iron cage", "dirty cage", "cage", "north wall"}),
        "This iron cage is extremely dirty and is filled with squeaking rats " +
        "who seem to be climbing all over each other. Apparently, the " +
        "Hargnak post office will allow you to hire a rat to send messages " +
        "when you are farther away from a post office.\n", );
    add_item(({"east wall"}),
        "The east wall of this building is very plain and unadorned, " +
        "apparently made of roughly cut chunks of stone.\n", );
    add_item(({"west wall"}),
        "The east wall of this building is very plain and unadorned, " +
        "apparently made of roughly cut chunks of stone.\n", );
    add_item(({"south wall"}),
        "The south wall of the post office has a large square opening which " +
        "leads back out into the middle of Hargnak.\n", );
    add_item(({"window", "windows"}),
        "Windows? What windows? There are no windows in this post office.\n", );
    add_item(({"opening", "square opening"}),
        "This square opening has no door of any sort, it just provides " +
        "access from the village into the post office.\n", );
    add_item(({"ceiling", "up"}),
        "The ceiling of this post office appears to be made of large " +
        "stones, cunningly set in such a way that they have not collapsed. " +
        "Yet.\n", );
    add_item(({"floor", "down", "dirt"}),
        "The floor of this post office is simply hard-packed dirt, there " +
        "is nothing particularily interesting about it.\n", );
    add_item(({"wall", "walls", "stone wall", "stone walls"}),
        "There are four stone walls here. Did you want to examine one of " +
        "them in particular?\n", );
    
    create_post();
    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(GOBLINS_DIR + "hargnak2", "south", "@@village@@");
}

int
village()
{
    write("\n\nYou leave the post office and step back outside into the " +
        "village of Hargnak.\n\n");
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
        notify_fail("Read what? The sign?\n");
        return 0;
    }
    
    if((str != "sign") && (str != "plaque"))
    
    { 
        notify_fail("Read what? The sign?\n");
        return 0;
    }
    
    write("As there are many people busy reading and writing their mails " +
        "here, please be considerate and keep your conversations to a " +
        "minimum.\n\n"+
        "Rats for sale\n");
    SAYBB(" reads the crude wooden sign.");
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
