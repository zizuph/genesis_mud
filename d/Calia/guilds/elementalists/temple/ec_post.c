/*
 * Post Office of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <mail.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define MAILREADER         "/secure/mail_reader"
#define ADDED_READER       "_has_mail_reader"
#define OLD_ALIASES        "_old_mailreader_aliases"
#define SCOP_COUNCIL_CODE  "/d/Calia/guilds/scop/specials/council_code"
#define MAILCHECKER        "/secure/mail_checker"

// Prototypes

public void
create_temple_room()
{
    set_short("Inside the temple post office");
    set_long("Here you find the post office of the Elemental Temple of "
        + "Calia. Members of the Clerics Council can correspond "
        + "with the rest of the world via mail. Upon entering, you were "
        + "directed to your own booth, where you have access to read and "
        + "write mail. The east exit allows you to find your way back "
        + "to the Council Chambers.\n\n"
        + "Post Office Commands are:\n"
        + "   read              Read your mail.\n"
        + "   mail <name>       Mail to player 'name'.\n"
        + "   mail council      Mail the Elemental Council.\n"
//        + "   mail worshippers  Mail the Elemental Worshippers Council.\n"
        + "   mail guildmaster  Mail the Elemental Clerics Guildmaster.\n"
        + "   from              List all headers.\n"
        + "\n");
    
    try_item( ({ "post", "post office", "temple post office" }),
                "This post office is rather bare except for "
              + "the various personal mailboxes set throughout "
              + "the room.\n");

    try_item( ({ "mailbox", "personal mailbox", "mailboxes", 
                 "personal mailboxes", "other members", "booth",
                 "booths" }),
                "You look around and see others scanning their own "
              + "mailboxes. Some are in the process of writing "
              + "correspondences to their loved ones. Everything "
              + "seems to be rather private, though, so you can't "
              + "really read the contents of other people's mail.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "cleric_councilroom", "east");
}

private void
add_mail_aliases(object reader)
{
    // Add the aliases for the Guildmaster and Council
    string * guildmasters = SECURITY->query_guild_masters("worshipper");
    if (sizeof(guildmasters))
    {
        reader->set_alias("guildmaster", guildmasters);
    }
    string * councilmembers = GUILD_MANAGER->query_ec_council();
    // We also want to add SCoP Elders to this list.
    string * scop_council_list = SCOP_COUNCIL_CODE->query_council_members();
    if (sizeof(scop_council_list))
    {
        foreach (string playername : scop_council_list)
        {
            councilmembers += ({ playername });
        }
    }
    if (sizeof(councilmembers))
    {
        reader->set_alias("council", councilmembers);
    }
//    string * ewcouncilmembers = GUILD_MANAGER->query_ew_council();
//    if (sizeof(ewcouncilmembers))
//    {
//        reader->set_alias("worshippers", ewcouncilmembers);
//    }
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
    
    setuid();
    seteuid(getuid());
    object reader;
    if (reader = present(READER_ID, ob))
    {
        mapping aliases = reader->query_aliases();
        // Save existing aliases to restore.
        ob->add_prop(OLD_ALIASES, aliases);

        add_mail_aliases(reader);
        return;
    }
    
    reader = clone_object(MAILREADER);
    if(!objectp(reader))
    {
    	write("The post office doesn't seem to be functioning correctly. "
    	    + "Please contact the Liege of Calia for assistance.\n");
    	return;
    }

    add_mail_aliases(reader);
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
    if (objectp(reader = present(READER_ID, ob)))
    {
        if (ob->query_prop(ADDED_READER))
        {
            reader->remove_object();
        }
        else
        {
            // Remove the added aliases by setting them to empty
            reader->set_alias("council", ({ }));
            reader->set_alias("guildmaster", ({ }));
            // Restore the aliases
            mapping aliases = ob->query_prop(OLD_ALIASES);
            if (mappingp(aliases))
            {
                foreach (string aliasname, string * values : aliases)
                {
                    reader->set_alias(aliasname, values);
                }
            }
        }
    }
    
    ob->remove_prop(ADDED_READER);
    ob->remove_prop(OLD_ALIASES);
}
