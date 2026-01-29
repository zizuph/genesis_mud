/*
 * /d/Gondor/common/dwarf_guild/post.c
 *
 * The post office of the Dwarven race guild.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <const.h>
#include <files.h>
#include <macros.h>
#include <mail.h>
#include <std.h>
#include <stdproperties.h>
#include "dwarf.h"

int block_exit();
string mailbox_description();

void
create_room()
{
    set_short("the post office of the " + DWARVEN_RACE_GUILD_NAME);

    set_long("This cave is used as post-office of the " +
        DWARVEN_RACE_GUILD_NAME + ". You see several mailboxes here. " +
        "To the east is the exit to the private chambers of the members " +
        "of the guild and to the west you see the exit for the postman " +
        "to access the mailboxes when he arrives with new mail. For the " +
        "available commands, please check the mail reader.\n" +
        "If you want to get in touch with the guildmaster of the " +
        DWARVEN_RACE_GUILD_NAME + ", you can simply send your mail to " +
        "\"guildmaster\". Note that you can only do that from this post " +
        "office!\n");

#include "cavedesc.h" /* some add_items for the rocky cave ect. */

    add_item( ({ "mailbox", "mailboxes", "box", "boxes" }),
        mailbox_description);

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "start", "east");
    add_exit(DWARF_DIR + "start", "west", block_exit);

    add_prop(ROOM_I_INSIDE, 1);
}

/*
 * It is an exit, though no-one, can use it, not even wizards. There is no
 * room on the other end of the exit :-)
 */
int
block_exit()
{
    write("Only the postmaster may use the exit in the west of this cave " +
        "and you are neither a postmaster, nor a postmistress!\n");

    return 1;
}

string
mailbox_description()
{
    string desc = "In the middle of the cavern you see the mailboxes of " +
        "the members of the " + DWARVEN_RACE_GUILD_NAME + ". You can only " +
        "access your mailbox from the one side. The back is reserved for " +
        "the postman. ";
    string new;
    int    mail = MAIL_CHECKER->query_mail();

    /* no non-member should enter this room, but just in case... */
    if (!IS_MEMBER(this_player()))
    {
        return "In the middle of the cavern you see the mailboxes of " +
            "the members of the " + DWARVEN_RACE_GUILD_NAME + ". Since " +
            "you are not a member of this guild, you have no mailbox here.\n";
    }

    switch(mail)
    {
    case 2:
        new = "new ";
        break;

    case 3:
        new = "unread ";
        break;

    default:
        new = "";
    }

    if (mail > 0)
    {
        desc += "In your mailbox you see some " + new + "mail.";
    }
    else
    {
        desc += "Your mailbox is empty.";
    }

    return desc + "\n";
}

void
init()
{
    object reader;

    ::init();

    /* If the player does not already have a mailreader (ie he is not a
     * wizard), then we clone a reader.
     */
    if (!objectp(reader = present(READER_ID, this_player())))
    {
        FIX_EUID;
        reader = clone_object(MAIL_READER);
    }

    /* We set the alias to the reader and move it into the player.
     */
    reader->set_alias("guildmaster",
        SECURITY->query_guild_masters(DWARVEN_RACE_GUILD_SHORT));
    reader->move(this_player(), 1);
}

void
leave_inv(object obj, object to)
{
    object reader;

    ::leave_inv(obj, to);

    /* A wizard gets to keep his/her mailreader. */
    if (obj->query_wiz_level())
    {
        return;
    }

    /* There can only be one mail reader in the player. */
    present(READER_ID, obj)->remove_object();
}

/*
 * Function name: query_mail
 * Description  : This function is called when a player logs on to give him
 *                a message about the (new) mail in his mailbox at home.
 * Arguments    : silent - Set to 1 to not tell the player about the mail.
 * Returns      : 1/0    - mail or no mail.
 */
public int
query_mail(int silent)
{
    int    mail = MAIL_CHECKER->query_mail();
    string new;

    if (silent || !mail)
    {
        return mail;
    }

    switch(mail)
    {
    case 2:
        new = "NEW mail";
        break;
    case 3:
        new = "UNREAD mail";
        break;
    default:
        new = "Mail";
    }

    write(
"    .______________.\n" +
"    |\\            /|\n" +
"    | \\          / |    " + new + " awaits you in the post\n" +
"    |  \\________/  |    office of the " + DWARVEN_RACE_GUILD_NAME + ".\n" +
"    |______________|\n");

    return mail;
}
