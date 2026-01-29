/*
 * /d/Genesis/postmaster/mail_converter.c
 *
 * This object is meant to convert all existing mail-files to files that
 * can be used with the new format. For the new format, see the comment
 * headers in /d/Genesis/postmaster/mail_reader.c.
 *
 * Copyright (C) Stas van der Schaaf - June 24 1994
 *               Mercade @ Genesis
 *
 * Revision history:
 */

#pragma no_inherit
#pragma strict_types

inherit "/std/object";

#include <std.h>
#include <stdproperties.h>

#define OLD_MAIL_DIR       "/d/Genesis/postmaster/mail/"
#define NEW_MAIL_DIR       "/d/Genesis/postmaster/mail/"
#define MAIL_CONVERTER_LOG "/d/Genesis/postmaster/log/mail_converter"
#define MSG_DIR            "/d/Genesis/postmaster/messages/"
#define HASH_SIZE          30

#define OLD_MESSAGES       "messages"

#define MAIL_FROM          "from"
#define MAIL_SUBJ          "subj"
#define MAIL_DATE          "date"
#define MAIL_READ          "read"
#define MAIL_REPLY         "reply"
#define MAIL_LENGTH        "length"

#define INDEX_FROM         0
#define INDEX_SUBJ         1
#define INDEX_CC           2
#define INDEX_DATE         3
#define INDEX_BODY         4

#define MAIL_MAIL          "mail"
#define MAIL_ALIASES       "aliases"
#define MAIL_NEW_MAIL      "new_mail"
#define MAIL_AUTO_CC       "auto_cc"

#define MSG_TO             "to"
#define MSG_CC             "cc"
#define MSG_ADDRESS        "address"
#define MSG_BODY           "body"

#define FLAG_NO_MAIL       0
#define FLAG_READ_MAIL     1
#define FLAG_NEW_MAIL      2
#define FLAG_UNREAD_MAIL   3

#define MARKER             " *read*"
#define MAX_NO_MREAD       "++"
#define MAX_MESSAGES       200

#define FILE_NAME_OLD(n) \
    (OLD_MAIL_DIR + (n))
#define FILE_NAME_MAIL(n) \
    (NEW_MAIL_DIR + extract((n), 0, 0) + "/" + (n))
#define FILE_NAME_MESSAGE(t) \
    (MSG_DIR + "d" + ((t) % HASH_SIZE) + "/m" + (t))

#define DATES ([ "Jan" : 8765, "Feb" : 8796, "Mar" : 8824, "Apr" : 8855, \
		 "May" : 8885, "Jun" : 8916, "Jul" : 8581, "Aug" : 8612, \
		 "Sep" : 8643, "Oct" : 8673, "Nov" : 8706, "Dec" : 8734 ])

/*
 * Global variables
 */
static object  wizard    = 0;
static string *mailfiles = ({ });
static int     converted = 0;

/*
 * Function name: create_object
 * Description  : This function creates the object.
 */
nomask void
create_object()
{
    set_name("converter");
    set_pname("converters");
    set_adj("mail");
    set_short("mail converter");
    set_pshort("mail converters");
    set_long(break_string("This mail converter can be used to convert all " +
	"the mail-files of the players to mail-files that can be used in " +
	"the new mail system. The command that will start this mail " +
	"converter is <convert mail> and it might take a long time before " +
	"all files are converted. Set_alarm is used to stay below the " +
	"eval-cost limit. If you are not an archwizard or keeper, do not " +
	"even think about executing the command.", 75) + "\n");

    add_prop(OBJ_M_NO_DROP,     1);
    add_prop(OBJ_M_NO_GIVE,     1);
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_BUY,      1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_M_NO_TELEPORT, 1);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_S_WIZINFO,     "Just examine the mail converter.\n");

    setuid();
    seteuid(getuid());
}

/*
 * Function name: init
 * Description  : This function is used to add the commands attached to
 *                this mail converter to the livings that get close to it.
 */
nomask void
init()
{
    ::init();

    add_action("convert", "convert");
}

/*
 * Function name: get_time
 * Description  : Compute the first time that is available to save this
 *                message in, based on the date from the original
 *                message.
 * Arguments    : string date - the date to convert
 * Returns      : int         - the time to save with
 */
nomask static int
get_time(string date)
{
    string month = date[6..8];
    int    day;
    int    time;
    int    to_try;

    if (sscanf(date[10..], "%d", day) != 1)
    {
	time = 757382401; /* Januari 1st 1994 */
    }
    else
    {
	time = (((DATES[month] + day) * 86400) + 1);
    }

    /* We randomly assign a time() in the first 12 hours of the day.
     * Checking all times in the day sequentially just takes time.
     */
    to_try = time + random(43200);
    while(file_size(FILE_NAME_MESSAGE(to_try)) != -1)
    {
	to_try = time + random(43200);
    }

    return to_try;
}

/*
 * Function name: convert_one_message
 * Description  : This function actually converts the message into the
 *                the new format.
 * Arguments    : mixed to_change - the message to change.
 *                string name     - the name of the recipient.
 * Returns      : mapping         - the new message
 */
nomask static mapping
convert_one_message(mixed to_change, string name)
{
    mapping changed = ([ ]);
    mapping message = ([ ]);
    int     time    = get_time(to_change[INDEX_DATE]);
    string  cc      = "";
    string  marker;
    string  subject = to_change[INDEX_SUBJ][6..];
    int     length  = sizeof(explode(to_change[INDEX_BODY], "\n"));

    changed[MAIL_FROM]   = to_change[INDEX_FROM];
    changed[MAIL_SUBJ]   = to_change[INDEX_SUBJ][6..];
    changed[MAIL_DATE]   = time;
    changed[MAIL_READ]   = (sscanf(subject, ("%s" + MARKER), subject) == 1);
    changed[MAIL_SUBJ]   = subject;
    changed[MAIL_REPLY]  = (to_change[INDEX_SUBJ][0..5] == " Re:  ");
    changed[MAIL_LENGTH] = ((length >= 100) ? MAX_NO_MREAD :
	sprintf("%2d", length));

    if (strlen(to_change[INDEX_CC]))
    {
	cc = implode(map(explode(to_change[INDEX_CC][4..], ", "), "cap",
	    this_object()), ",");
    }

    message[MSG_BODY]    = to_change[INDEX_BODY];
    message[MSG_TO]      = capitalize(name);
    message[MSG_CC]      = cc;
    message[MSG_ADDRESS] = capitalize(name);

    save_map(message, FILE_NAME_MESSAGE(time));

    return changed;
}

/*
 * Function name: convert_one_file
 * Description  : Convert one old file to the new system. For each
 *                message in the file, all other recipients are located
 *                and added to the system. Therewith achieving that the
 *                benefits of the new system are used from the start.
 * Arguments    : string - the file to convert
 */
nomask static void
convert_one_file(string file)
{
    mapping mail     = restore_map(FILE_NAME_OLD(file));
    mixed   messages = mail[OLD_MESSAGES];
    int     index;
    int     new_mail = FLAG_READ_MAIL;

    if (sizeof(messages) == 0)
    {
	wizard->catch_msg("MAIL CONVERTER ->> Empty file: " + file + "\n");

	return;
    }

    for (index = 0; index < sizeof(messages); index++)
    {
	messages[index] = convert_one_message(messages[index],
	    capitalize(file));

	if (messages[index][MAIL_READ] == 0)
	{
	    new_mail = FLAG_NEW_MAIL;
	}
    }

    converted += sizeof(messages);
    wizard->catch_msg("MAIL CONVERTER ->> Converted: " + file + "\n");

    mail = ([ MAIL_MAIL     : messages,
	      MAIL_ALIASES  : ([ ]),
	      MAIL_NEW_MAIL : new_mail,
	      MAIL_AUTO_CC  : 0 ]);

    save_map(mail, FILE_NAME_MAIL(file));
}

/*
 * Function name: convert_mail
 * Description  : This function actually converts the mail reports to the
 *                responsible wizard about it. It uses set_alarm to keep
 *                away from the eval-cost limit.
 */
nomask static void
convert_mail()
{
    string name;

    if ((!objectp(wizard)) ||
	(!sizeof(mailfiles)))
    {
	return;
    }

    if (sscanf(mailfiles[0], "%s.o", name) != 1)
    {
	wizard->catch_msg("MAIL CONVERTER ->> strange filename: " +
	    mailfiles[0] + "\n");
    }
    else
    {
	convert_one_file(name);
    }

    if (sizeof(mailfiles) == 1)
    {
	wizard->catch_msg("MAIL CONVERTER ->> DONE CONVERTING.\n");
	mailfiles = 0;
	wizard = 0;
	converted = MAX_MESSAGES;
	return;
    }

    mailfiles = mailfiles[1..];
}

/*
 * Function name: convert_many
 * Description  : This function loops just until all messages are
 *                converted. It tries to convert as many messages as
 *                possible in one turn without slowing down the game
 *                too much.
 */
nomask static void
convert_many()
{
    while (converted < MAX_MESSAGES)
    {
	convert_mail();
    }

    wizard->catch_msg("MAIL CONVERTER ->> BATCH CONVERTED....\n");
    converted = 0;

    if (sizeof(mailfiles))
    {
	set_alarm(3.0, 0.0, "convert_many");
    }
}

/*
 * Function name: convert
 * Description  : This function is called what a player gives the command
 *                convert the mail. Some checks are made before the actual
 *                conversion takes place. Use common sense :-)
 * Arguments    : str - the command line argument
 * Returns      : int - 1/0 == success/failure
 */
nomask static int
convert(string str)
{
    string letter;

    if (environment() != this_player())
    {
	notify_fail("You do not have the mail converter on you.\n");
	return 0;
    }

    if ((!strlen(str)) || sscanf(str, "mail %s", letter) != 1)
    {
	notify_fail("Usage: convert mail <filespec>\n");
	return 0;
    }

    if (strlen(letter) != 1)
    {
	notify_fail("The filespec may only be one letter, ie. 'a' or 'm'.\n");
	return 0;
    }

    if (this_player() != this_interactive())
    {
	notify_fail("You need to use the mail converter alone.\n");
	return 0;
    }

    if (objectp(wizard))
    {
	notify_fail(capitalize(wizard->query_real_name()) +
	    " is already converting mail.\n");
	return 0;
    }

    if (SECURITY->query_wiz_level(this_player()->query_real_name()) <=
	WIZLEV_LORD)
    {
	write_file(MAIL_CONVERTER_LOG, ctime(time()) + " " +
	    capitalize(this_player()->query_real_name()) +
	    " tried to use the mail converter.\n");
	notify_fail(break_string("You have been warned. This attempt is " +
	    "logged. Report to Mercade for demotion within seven days.", 75) +
	    "\n");
	return 0;
    }

    write_file(MAIL_CONVERTER_LOG, ctime(time()) + " " +
	capitalize(this_player()->query_real_name()) +
	" used the mail converter.\n");

    wizard = this_player();
    mailfiles = get_dir(OLD_MAIL_DIR + letter + "*") - ({ ".", ".." });

    convert_many();

    return 1;
}

/*
 * Function name: remove_object
 * Description  : This function is a shadow of the remove_object function
 *                to ensure that the mail converter is not removed while
 *                it is converting mail.
 */
varargs nomask void
remove_object()
{
    if (objectp(wizard))
    {
	wizard->catch_msg("MAIL CONVERTER ->> Remove_object() called.\n");
	wizard->catch_msg("MAIL CONVERTER ->> Attempt rejected.\n");
	return;
    }

    ::remove_object();
}

/*
 * Function name: cap
 * Description  : Capitalizes the incoming string.
 * Arguments    : string - the string to capitalize.
 * Returns      : string - the capitalized string.
 */
nomask string
cap(string str)
{
    return capitalize(str);
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function returns 1 in order to indicate that it
 *                should not be shadowed ever.
 * Returns      : int - always 1
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
