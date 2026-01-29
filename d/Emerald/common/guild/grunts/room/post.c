/* This is the Grunts post office. Much the same as any other, really.... */

inherit "/std/room";

#include "default.h"
#include <stdproperties.h>
#include "../guild.h"

#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER     "/secure/mail_checker"

/*
 * Function name:   create_room
 * Description:     define the basics of the room
 */
public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short("Grunts post office");
    set_long("   This is the Grunts' post office.\n"
       + "Although some goblins have finally learned to read and write, "
       + "you get the feeling this place isn't used much. The cobwebs "
       + "in the corners of the room reinforce that feeling.\n"
       + "\nCommands are:\n"
       + "    read           Read your mail.\n"
       + "    mail <name>    Mail to player 'name'.\n"
      + "    from           List all mail headers.\n\n");

    add_item(({"walls","wall"}),
	"There are torches fixed on two walls of the post office. " +
	"The walls are cold, and damp to touch. It seems to be made " +
	"of the usual volcanic rock like the rest of the caves. There are " +
	"cobwebs in most of the corners of the room.\n");
    
    add_item(({"cobweb","cobwebs","corner","corners"}),
	"The cobwebs in the corners of the room look quite thick - well," +
	"lets face it, no one ever comes in here, let alone clean up.\n");

    add_item(({"roof","ceiling"}),
	"The roof is made of the same rock as the walls, the familiar " +
	"volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock.\n");

    add_item(({"torch","torches"}),
	"The torches are fixed firmly to the wall, and cannot be taken.\n");
    
    add_exit(THIS_DIR + "shop", "west");

}

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
    object reader;
   
    ::init();
    reader=clone_object(MAILREADER);
    if (!reader) 
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

/*
 * Function name:   leave_inv
 * Description:     remove mailreader from players exiting the room
 */
public void
leave_inv(object ob,mixed to)
{
    object reader;
   
    ::leave_inv(ob,to);
    reader=present("mailread",ob);
    if (reader)
	reader->remove_object();
}

/*
 * Function name:   query_mail
 * Description:     check to see if a player has new mail
 */
public int
query_mail(int silent)
{
    string new, sp;
    int mail;

    mail = MAILCHECKER->query_mail();
    if (!mail)
	return 0;
    if (silent)
	return 1;
    new="";
    sp="    ";
    if (mail>1) 
    {
	new=" NEW";
	sp="";
    }
    write("\nThere is"+new+" mail for you in the Grunts post office.\n");
    return 1;
}
