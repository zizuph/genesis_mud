/*
 * File:    post
 * Creator: Cirion, 1998.06.14
 * Purpose: post office for the monks guild
 */
#pragma save_binary

#include "defs.h"

#define MAILCHECKER   "/secure/mail_checker"
#define MAILREADER    "/secure/mail_reader"
#define MAILREADER_ID "_reader_"

inherit ROOMBASE;
inherit "/d/Genesis/lib/post";

void
create_room ()
{
    set_short("quiet room");
    set_long("Standing in the center of this circular room is "
        + "a small desk of pine. Inscribed on the smooth stone "
        + "floor is a circle painted gold, within which is "
        + "written letters. A square window in the north wall "
        + "provides light for the room, along with a small "
        + "iron lamp that rests on the desk.\n");
    add_item(({"desk","pine desk","pine","table"}),
        "The small desk is simply build from pine. The "
        + "front of the desk contains many small cubbyholes, "
        + "within which correspondences can be placed. "
        + "Sitting on the desk is a small bottle of ink and "
        + "a glass cube, serving as a rest for a feather "
        + "quill.\n");
    add_item(({"stand","glass stand"}),
        "The small cubic stand is made from thick, opaque "
        + "glass.\n");
    add_item(({"quill","pen","feather"}),
        "The feather is used for composing letters.\n");
    add_item(({"glass","window"}),
        "The leaded glass of the window lets in plenty of "
        + "sunlight. Its frame is made from thin slats of "
        + "wood, and it is criss-crossed by shafts of iron "
        + "to hold the glass in place.\n");
    add_item(({"lamp","lantern"}),
        "The small iron lamp is intricate. Its light shines "
        + "from small, clover shaped holes of its tapered "
        + "hood, and shines down in the desk in dappled "
        + "patterns.\n");
    add_item(({"hole","holes","cubby","cubbyhole","cubbyholes"}),
        "Inset into the front of the desk are numerous "
        + "cubbyholes, within which correspondences are "
        + "placed, and into which outgoing mail is put when "
        + "it is sent.\n");
    add_item(({"letters","letter"}),
        "They appear to form words that should be read.\n");
    add_item(({"circle","gold circle","gold leaf"}),
        "A modest display of wealth, a circle of gold leaf "
        + "has been painted upon the floor, and within it, "
        + "words are written.\n");
    add_cmd_item(({"letter","letters","floor","ground","words"}), 
        ({"read"}),
        "In silence shall we be cradled.\n"
        + VBFC_SAY("looks down at the floor and reads the words "
        + "written there.\n"));
    add_cmd_item(({"sun","sunlight","light"}), ({"feel"}),
        "The sun feels warm on your face.\n"
        + VBFC_SAY("basks in the sunlight coming in through the "
        + "window.\n"));
    add_cmd_item(({"lamp","lantern"}), ({"get","take"}),
        "It seems to be firmly bolted to the table.\n"
        + VBFC_SAY("tried to take the lantern from the table, but "
        + "finds that it is bolted down.\n"));


    WIZINFO("This is the post office for the monks guild.\n");

    // where, command
    add_exit("hall_upper_north", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You enter a small, silent chamber.\n");
}

void
init()
{
    ::init();

    // initialize the standard PO actions
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

/*
 * Function name: mail_message
 * Description:   Called when a player logs in, this informs
 *                them of new or unread mail.
 * Arguments:
 * Returns:
 */
void
mail_message(string new)
{
    string mail = "mail";
    string msg;

    if(!strlen(new))
    {
        mail = "Mail";
        new = "";
    }

    msg = new + " " + mail + " awaits you in the monestary post office.\n";

    write(m_pretty_text(msg, 0)); // write a pretty description of the mail message
}

/*
 * Function name: query_mail
 * Description  : This function is called when a player logs on to give him
 *                a message about the (new) mail in his mailbox.
 * Arguments    : silent - Set to 1 to not tell the player about the mail.
 * Returns      : 0 - no mail
 *                1 - mail, all read
 *                2 - new mail
 *                3 - unread mail
 */
public int
query_mail(int silent)
{
    int     mail = MAILCHECKER->query_mail();
    string  new;
 
    if(silent || mail < 2)
        return mail;
 
    switch(mail)
    {
        case 2:
            new = "   New mail";
            break;
 
        default:
            new = "Unread mail";
            break;
    }
 
    mail_message(new);
 
    return mail;
}

