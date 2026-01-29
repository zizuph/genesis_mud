/*
 * Post Office for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <mail.h>
#include "defs.h"

inherit SCHOOL_ROOM_BASE;

// Defines
#define MAILREADER      "/secure/mail_reader"
#define ADDED_READER    "_has_academy_reader"

public void
create_school_room()
{
    set_short("Academy Post Office");
    set_long("You stand in the Post Office of the Academy of Elemental "
        + "Arts. Here members of the Academy can correspond with "
        + "the rest of the world via mail. Upon entering, you were "
        + "directed to your own booth, where you have access to read "
        + "and write mail. An unnatural silence fills the room, despite "
        + "its proximity to the assembly hall to the southeast. You figure "
        + "that something must be muting the commotion that you would "
        + "expect.\n\n"
        + "Post Office Commands are:\n"
        + "   read            Read your mail.\n"
        + "   mail <name>     Mail to player 'name'.\n"
        + "   from            List all headers.\n"
        + "\n");
    
    try_item( ({ "post", "post office", "academy post office" }),
                "This post office is rather bare except for "
              + "the various personal mailboxes set throughout "
              + "the room.\n");

    try_item( ({ "mailbox", "personal mailbox", "mailboxes", 
                 "personal mailboxes", "other members", "booth",
                 "booths" }),
                "You look around and see other members of the "
              + "Academy who are scanning their mailboxes. Some "
              + "are in the process of writing correspondences to "
              + "their loved ones. Everything seems to be rather "
              + "private, though, so you can't really read "
              + "the contents of other people's mail.\n");

    try_item( ({ "hall", "assembly hall", "southeast", "southeast exit" }),
                "The assembly hall from which you came lies to the "
              + "southeast.\n");

    try_item( ({ "commotion" }),
                "It seems oddly muted. You could write or read your mail "
              + "in peace, undisturbed by the others in the assembly "
              + "hall.\n");    
    
    add_exit(ACADEMIC_SCHOOL + "boardroom", "southeast");
}

/*
 * Function:    enter_inv
 * Description: This function is called whenever a player enters
 *              the room. It clones the mail reader and moves it
 *              into their inventory. That's all a post office
 *              really is.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
    {
        return;
    }
    
    if (present(READER_ID, ob))
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    object reader = clone_object(MAILREADER);
    if(!objectp(reader))
    {
    	write("The post office doesn't seem to be functioning correctly. "
    	    + "Please contact your guildmaster for assistance.\n");
    	return;
    }
    
    reader->move(ob);
    ob->add_prop(ADDED_READER, 1);
}

/*
 * Function:    leave_inv
 * Description: When a person leaves the post office, the mail reader that
 *              was added when entering the post office.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!interactive(ob))
    {
        return;
    }
    
    object reader;
    if (objectp(reader = present(READER_ID, ob))
        && ob->query_prop(ADDED_READER))
    {
        reader->remove_object();
    }
    
    ob->remove_prop(ADDED_READER);
}
