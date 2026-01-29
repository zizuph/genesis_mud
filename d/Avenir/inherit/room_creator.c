/*
 * File:     room_creator.c
 * Created:  Cirion, 1998.06.02
 * Purpose:  a inheritable module that enable an NPC
 *           to take suggestions from a player on the
 *           creation of new rooms. It will then generate
 *           the LPC code that makes up the room and
 *           place it in the specified location, for later
 *           review and approval of a wizard.
 *
 * Note:     this is an experimental object: I wanted to
 *           see how a player with no coding experience
 *           would do in the creation of an area in the
 *           Genesis environment.
 *
 * Caveat:   the LPC code that defines the room that this
 *           module creates is not complete. Most noticablly,
 *           there are no exits automatically added to the
 *           room, since I could not think of a good way to
 *           allow a player to specify the exits. This means
 *           that there will always be a minimum amount of
 *           work a wizard would need to do to make the room
 *           usable in the game. Apart from there, there are style
 *           and originality issues that need to be dealt with
 *           when reviewing the room and deciding if it is fit
 *           to be opened: namely, the fact that these room do not
 *           have any 'features' means that they are, by their
 *           nature, of the most generic sort. Since pointless
 *           areas are to be avoided, the reviewing wizard needs
 *           to decide how much should be added to the room to
 *           make it worth opening.
 *
 * Example:  an example of a creature that would use this:
 **************************************************************

inherit "/d/Avenir/inherit/room_creator";

void
create_monster ()
{
    set_name ("creator");
    set_short ("small creator");
    set_long ("It can create areas for you!\n");

    // path to which we will write out our generated rooms
    set_room_path ("/d/Avenir/cirion/tmp/");
    // path to which we will log room creations
    set_room_log_file ("/d/Avenir/cirion/tmp/roomlog");

    // reset all variables
    reset_room_creator ();

    // allow the player to obtain help by asking
    set_room_creation_ask_help ();
}

void
init_living ()
{
    ::init_living ();

    // initialize all the creator-specific commands
    init_room_creator ();
}

 **************************************************************
 *
 * Modification Log:
 *
 */
#include <composite.h>
#include <macros.h>

#define DEBUG(x) find_living("cirion")->catch_tell (str + "\n")

string room_short, room_long;
mixed room_items = ({});
mixed room_exits = ({});
mixed room_cmd_items = ({});
string comments;
string *room_includes = ({ "<stdproperties.h>", "<macros.h>" });
string room_inherit = "/std/room";
string room_file_name;

string room_path;
string room_file;
string log_file = "";
string indentation = "    ";
string quote = "\"";

// the minimum number of items we will allow
// a room to be created with
int min_items = 5;
int min_cmd_items = 1;

object composer = 0;

// Prototypes
void init_room_creator();
string query_room_log_file ();
string query_room_path();
string query_room_path ();
string query_room_file_name ();
void reset_room_creator();
void set_room_log_file (string str);
void set_room_path(string str);
int set_room_comment(string str);
int set_room_short(string str);
int set_room_long(string str);
int set_room_item(string str);
int set_room_cmd_item(string str);
string generate_room_header (object for_who);
varargs string generate_room_code(object for_who = this_player());
int write_room_code ();
int complete_room (string str);
int cancel_room (string str);


/*
 * Function name: init_room_creator
 * Description:   Initialize the commands of the
 *                room creator.
 * Arguments:
 * Returns:
 */
void
init_room_creator()
{
    // if our last creator has wandered off without
    // completing the room, reset it for this player.
    if (objectp (composer) && !present (composer, environment (this_object ())))
        reset_room_creator ();

    add_action (set_room_short, "rshort");
    add_action (set_room_long, "rlong");
    add_action (set_room_item, "ritem");
    add_action (set_room_cmd_item, "rcommand");
    add_action (set_room_comment, "rcomment");
    add_action (complete_room, "rdone");
    add_action (cancel_room, "rcancel");
}

/*
 * Function name: reset_room_creator
 * Description:   reset the internal variables used
 *                by the room creator.
 * Arguments:
 * Returns:
 */
void
reset_room_creator()
{
    room_short = "";
    room_long = "";
    comments = "";
    room_file_name = "";
    room_items = ({});
    room_exits = ({});
    room_cmd_items = ({});
    composer = 0;
}

/*
 * Function name: set_room_log_file
 * Description:   set the file name to which room creation
 *                events will be logged.
 * Arguments:     the fully-qualified path to the log file
 */
void
set_room_log_file (string str)
{
    log_file = str;
}

/*
 * Function name: query_room_log_file
 * Description:   return the file to which room
 *                creation events are logged.
 * Returns:       the path to the log file
 */
string
query_room_log_file ()
{
    return log_file;
}


/*
 * Function name: set_min_room_items
 * Description:   set the minimum number of add_items we can
 *                have specified before we will allow the
 *                room to be created.
 * Arguments:     the minimum number of items to allow
 */
void
set_min_room_items (int num)
{
    min_items = num;
}

/*
 * Function name: set_min_room_cmd_items
 * Description:   set the minimum number of add_cmd_items we can
 *                have specified before we will allow the
 *                room to be created.
 * Arguments:     the minimum number of cmd_items to allow
 */
void
set_min_room_cmd_items (int num)
{
    min_cmd_items = num;
}

/*
 * Function name: set_room_inlcudes
 * Description:   set the list of include files to include
 *                in the room.
 * Arguments:     an array of string comtaining the specification
 *                on include files.
 * Note:          the specification must include the '<', '>', or '"'
 *                characters that define the include file, since
 *                there is no way to guess if it is desired to
 *                include the absolute path, current path, or
 *                include path include files.
 */
void
set_room_includes (string *str)
{
    room_includes = str;
}

/*
 * Function name: set_room_creation_ask_help
 * Description:   enable the add_ask in the NPC that will
 *                have it give out information on how to create
 *                a room
 */
void
set_room_creation_ask_help ()
{

    this_object()->add_ask (({ "room", "room creation", "help", "how do I create a room",
        "creation", "area", "building", "building an area" }),
        VBFC_ME("ask_about_room_creation"));
}


/*
 * Function name: ask_about_room_creation
 * Description:   called when a player asks the NPC about
 *                room creation (when set_room_creation_ask_help
 *                has been enabled). This gives the NPC a series
 *                of commands that describe the room creation
 *                steps.
 * Returns:       ""
 */
string
ask_about_room_creation ()
{
    command ("say I can take suggestions from you about creating "
        + "a new area...");
    command ("say To specify what the brief description of the area "
        + "would be, do 'rshort <description>'.");
    command ("say To specify when the long, verbose description of "
        + "the area would be, do 'rlong <description>'.");
    command ("say To add items which you can examine within the "
        + "area (for example, a wall, a ceiling, a table), do "
        + "'ritem (item1, item2, ..., itemn) <description of item>'.");
    command ("say To add simple commands which can be used "
        + "in the room (like drinking from a pool), do "
        + "'rcommand (command1, command2, commandn) "
        + "(item1, item2, ..., itemn) <description of result>'.");
    command ("say To add you own comments to the reviewer of the "
        + "room, do 'rcomment <comments>'");
    command ("say Once you are done specifying the room, just "
        + "do 'rdone' and it will be submitted for approvel.");
    command ("say To cancel an area you have begun, just do 'rcancel'.");

    return "";
}

/*
 * Function name: set_room_path
 * Description:   sets the path into which submitted room
 *                code is generated
 * Arguments:     The directory name into which submitted
 *                room code should be placed.
 */
void
set_room_path(string str)
{
    room_path = str;
}

/*
 * Function name: query_room_path
 * Description:   return the directory into which submitted
 *                rooms are to be placed.
 * Returns:       the path
 */
string
query_room_path()
{
    return room_path;
}

/*
 * Function name: puncuate_str
 * Description:   support function to add puncuation to a
 *                string that does not already have any
 *                puncuation
 * Arguments:     The string to check for
 * Returns:       the puncuated string
 */
string
puncuate_str (string str)
{
    int test_char;

    test_char = str[strlen(str) - 1];

    // Is the last character of the string alpha? If so,
    // complete it with a period.
    if (test_char < 'z' && test_char > 'A')
        str += ".";

    return str;
}


/*
 * Function name: check_is_room_creator
 * Description:   check to see if the player passed
 *                in is the current creator of a room
 *                (since we will block all other creations
 *                until the current one is done).
 * Arguments:     who: the person to check for
 *                silent: 1 if you do not want the NPC to speak
 * Returns:       1 if who is the current creator, 0 otherwise
 */
varargs int
check_is_room_creator (object who, int silent = 0)
{
    if (!composer)
    {
        composer = who;
        return 1;
    }

    if (composer != who)
    {
        if (!silent)
            command ("say Sorry, someone else is currently "
                + "working on a room.");
        return 0;
    }
    else
        return 1;
}

/*
 * Function name: set_room_comment
 * Description:   command function to set the comment
 *                string in the room.
 * Arguments:     the argument the player typed
 * Returns:       1
 */
int
set_room_comment(string str)
{
    if (!check_is_room_creator (this_player ()))
        return 1;

    if(!strlen(str))
    {
        command("say The proper way to set the comments of the "
            + "area is 'rcomment '<comment>'.");
        command("say Note that the entire comment needs to be "
            + "specified on one line.");
        return 1;
    }

    if (strlen(str) < 5)
    {
        command("say That comment is too short.");
        return 1;
    }

    comments = str;
    command("say OK -- you have added your comment to the area.");
    return 1;
}

/*
 * Function name: set_room_short
 * Description:   command function to set the short description
 *                of the room.
 * Arguments:     the argument the player typed
 * Returns:       1
 */
int
set_room_short(string str)
{
    if (!check_is_room_creator (this_player ()))
        return 1;

    if(!strlen(str))
    {
        command("say The proper way to set the short description "
            + "of the room is 'rshort <short description of room>'.");
        command("say For example, 'rshort a long, dark hallway'");
        return 1;
    }

    if (strlen(str) > 60)
    {
        command("say That description is too long. To set the "
            + "long description of your room, use 'rlong <description>'.");
        return 1;
    }

    room_short = str;
    command("say OK -- the brief description of the area will be '"
        + room_short + "'.");
    return 1;
}

/*
 * Function name: set_room_long
 * Description:   command function to set the long description
 *                of the room
 * Arguments:     the argument the player typed
 * Returns:       1
 */
int
set_room_long(string str)
{
    if (!check_is_room_creator (this_player ()))
        return 1;

    if(!strlen(str))
    {
        command("say The proper way to set the verbose description "
            + "of the room is 'rlong <description of room>'.");
        command("say For example, 'rlong This is a long and narrow hallway, leading...'");
        command("say Note that the entire description needs to be "
            + "specified on one line.");
        return 1;
    }

    if (strlen(str) < 150)
    {
        command("say That description is too short.");
        return 1;
    }

    room_long = puncuate_str(str);
    command("say OK -- that is what the verbose description of "
        + "the room will read.");
    return 1;
}


/*
 * Function name: set_room_item_fail
 * Description:   the function that will make the npc
 *                give a description of the proper syntax
 *                for the 'ritem' command.
 */
void
set_room_item_fail()
{
    command("say The proper way to add an item or description to "
        + "the area is 'ritem (object1,object2,object3) description'.");
    command("say For example, 'ritem (wall,walls,stone) The stone walls are "
        + "made from heavy masonry.'");
}

/*
 * Function name: set_room_item
 * Description:   command function to add an item to the room
 * Arguments:     the argument the player typed
 * Returns:       1
 */
int
set_room_item(string str)
{
    string item_str, desc;
    string *items;

    if (!check_is_room_creator (this_player ()))
        return 1;

    if(!strlen(str))
    {
        command("Please specify the description of an item on the area.");
    }

    if(sscanf(str, "(%s) %s", item_str, desc) != 2)
    {
        set_room_item_fail ();
        return 1;
    }

    items = explode(item_str, ",");

    if(!sizeof(items))
    {
        set_room_item_fail ();
        return 1;
    }

    if (!strlen(desc))
    {
        set_room_item_fail ();
        return 1;
    }

    if (strlen(desc) < 10)
    {
        command ("say You need to better describe the item.");
    }

    room_items += ({ items, puncuate_str(desc) });

    command ("say OK -- you have added the items "
        + COMPOSITE_WORDS(items) + ".");
    return 1;
}

/*
 * Function name: set_room_cmd_item_fail
 * Description:   the function that will make the npc
 *                give a description of the proper syntax
 *                for the 'rcommand' command.
 */
void
set_room_cmd_item_fail()
{
    command("say The proper way to add a command to "
        + "the area is 'rcommand (command1,command2,...) "
        + "(object1,object2,object3) result'.");
    command("say For example, 'ritem (touch,feel) (wall,walls,stone) "
        + "The stone of the wall feels firm and impenetrable.'");
    command("say Note that commands are only superficial: They can "
        + "not have any real effect on anyone.");
}

/*
 * Function name: set_room_cmd_item
 * Description:   command function to add a cmd_item to the room
 * Arguments:     the argument the player typed
 * Returns:       1
 */
int
set_room_cmd_item(string str)
{
    string command_str, item_str, desc;
    string *items, *commands;

    if (!check_is_room_creator (this_player ()))
        return 1;

    if(!strlen(str))
    {
        command("Please specify the description of an command in the area.");
    }

    if(sscanf(str, "(%s) (%s) %s", command_str, item_str, desc) != 3)
    {
        set_room_cmd_item_fail ();
        return 1;
    }

    items = explode(item_str, ",");

    if(!sizeof(items))
    {
        set_room_cmd_item_fail ();
        return 1;
    }

    commands = explode(command_str, ",");

    if(!sizeof(commands))
    {
        set_room_cmd_item_fail ();
        return 1;
    }

    if (!strlen(desc))
    {
        set_room_cmd_item_fail ();
        return 1;
    }

    if (strlen(desc) < 10)
    {
        command ("say You need to better describe the result of the command.");
    }

    // note the ordering is the same as that for add_cmd_item(), NOT
    // the same as the syntax for this command was.
    room_cmd_items += ({ items, commands, puncuate_str(desc) });

    command ("say OK -- you have added the commands "
        + COMPOSITE_WORDS(commands) + ".");
    return 1;
}


/*
 * Function name: make_quoted_string
 * Description:   take a long string and break it up
 *                into different lines, while preserving
 *                LPC indentation and string continuation
 *                conventions and rules.
 * Arguments:     str - the string to break
 *                linebreak - 1 if we want to append an extra '\n'
 *                    to the end of the string (default = 1)
 *                breaklen - the length at which we will break
 *                    the string (using break_stirng ()).
 *                    (default = 50)
 * Returns:
 */
varargs string
make_quoted_string(string str, int linebreak = 1, int breaklen = 50)
{
    string newline;

    if (linebreak)
        newline = "\\n";
    else
        newline = "";

    // break it line by line
    str = break_string(str, breaklen);

    // now add the necessary quotes
    str = implode(explode(str, "\n"), " " + quote + "\n" + indentation
        + indentation + "+ \"");

    // surround the whole thing by quotes
    str = quote + str + newline + quote;

    return str;
}

/*
 * Function name: query_room_file_name
 * Description:   obtain the file name to which the room
 *                will be written. If one has not yet been
 *                set, then generate it based on the room's
 *                short description.
 * Returns:       the file name to which the room will be written
 * Note:          this always returns a non-existant file name:
 *                it checks to see if a test file name exists, and
 *                if it does, continues appending an increasing
 *                number to the end of the file name until it
 *                hits on a unique one.
 */
string
query_room_file_name ()
{
    string test_file;
    int index = 0;

    if (!room_file)
    {
        if (!room_short)
            return "";

        room_file = query_room_path () + implode(explode(room_short, " "), "_");

        // generate a unique file name so we do not
        // overwrite other files.
        test_file = room_file;
        while (file_size (test_file + ".c") > 0)
        {
            test_file = room_file + (++index);
        }
        room_file = test_file + ".c";

    }


    return room_file;

}

/*
 * Function name: generate_room_header
 * Description:   generate the header string from the code
 *                that makes up the room. Includes comments,
 *                inherit and includes.
 * Arguments:     for_who - the person who is creating the
 *                    room file (used for the comments).
 * Returns:       the header code for the room
 */
string
generate_room_header (object for_who)
{
    string str = "";
    string com = "";
    int i;
    // add the comments of the room
    if(strlen(comments))
    {
        com = break_string(comments, 45);
        com = implode(explode(com, "\n"), "\n *                ");
        com = " *                " + com + "\n";
    }

    str += "/*\n";
    str += " * File:          " + query_room_file_name () + "\n";
    str += " * Creator:       " + for_who->query_name () + "\n";
    str += " * Date:          " + ctime(time()) + "\n";
    str += " * Note:          This room was auto-generated using\n";
    str += " *                the room creator module inherited by\n";
    str += " *                " + file_name(this_object()) + "\n";
    str += " * Comments:      \n";
    str += com;
    str += " */\n";

    // now add the inherits and includes
    for (i=0; i<sizeof (room_includes); i++)
        str += "#include " + room_includes[i] + "\n";

    str += "inherit " + quote + room_inherit + quote + ";\n";

    str += "\n";

    return str;
}

/*
 * Function name: generate_room_code
 * Description:   generates LPC code that defines the room
 *                based on the player's specification. It will
 *                generate a very simple room (just the
 *                create_room () function with set_long(),
 *                set_short(), add_item(), and add_cmd_item()).
 * Arguments:     for_who - the player who is generating the room
 *                    code.
 * Returns:       the LPC code that defines the room
 */
varargs string
generate_room_code(object for_who = this_player())
{
    string code = "";
    int i;

    code += generate_room_header (for_who);

    code += "void\ncreate_room ()\n";
    code += "{\n";
    code += indentation + "set_short(" + make_quoted_string(room_short, 0) + ");\n";
    code += indentation + "set_long(" + make_quoted_string(room_long) + ");\n";
    code += "\n";

    // generate the room item description code
    for (i=0;i<sizeof(room_items);i+=2)
    {

        code += indentation + "add_item(({" + quote;
        code += implode(room_items[i], quote + "," + quote);
        code += quote + "}),\n";
        code += indentation + indentation + make_quoted_string (room_items[i+1]);
        code += ");\n";
    }

    // generate the room cmd item description code
    for (i=0;i<sizeof(room_cmd_items);i+=3)
    {
        code += indentation + "add_cmd_item(";
        // item
        code += "({" + quote;
        code += implode(room_cmd_items[i], quote + "," + quote);
        code += quote + "}),\n";
        // command
        code += indentation + indentation + "({" + quote;
        code += implode(room_cmd_items[i+1], quote + "," + quote);
        code += quote + "}),\n";
        // description
        code += indentation + indentation + make_quoted_string (room_cmd_items[i+2]);
        code += ");\n";
    }

    // finish off the create_room
    code += "\n\n}\n";

    return code;
}

/*
 * Function name: write_room_code
 * Description:   write out the LPC code that defines
 *                the room (based on the player's
 *                specification) to a file.
 * Returns:       1 if successful, 0 otherwise
 */
int
write_room_code ()
{
    string code;

    seteuid (getuid (this_object ()));

    code = generate_room_code ();

    return write_file (query_room_file_name (), code);
}

/*
 * Function name: complete_room
 * Description:   command function that allows a player
 *                to complete the specification of the
 *                room. This will check to see if there are
 *                enough information specified, and write out
 *                the code to a unique file.
 * Arguments:     the argument the player passed to the command
 * Returns:       1
 */
int
complete_room (string str)
{
    if (!check_is_room_creator (this_player ()))
        return 1;

    if (!strlen (room_short))
    {
        command ("say You still need to set the brief description of the "
            + "area with 'rshort'");
        return 1;
    }

    if (!strlen (room_long))
    {
        command ("say You still need to set the verbose description of the "
            + "area with 'rlong'");
        return 1;
    }

    if (sizeof (room_items) < (min_items * 2))
    {
        command ("say Your area must have at least " + min_items + " description"
            + (min_items > 1 ? "s of items." : " of an item."));
        command ("say You can add the descriptions of items with 'ritem'.");
        return 1;
    }


    if (sizeof (room_cmd_items) < (min_cmd_items * 3))
    {
        command ("say Your area must have at least " + min_cmd_items + " command"
            + (min_cmd_items > 1 ? "s" : "")
            + " specified.");
        command ("say You can add the commands with 'rcommand'.");
        return 1;
    }

    if (!strlen (comments))
    {
        command ("say You still need to add some comments for the powers that be.");
        command ("say You can add your comments on the area with 'rcomment'.");
        return 1;
    }

    if (write_room_code ()) // successfully wrote out the file
    {
        command ("say OK: I will have your proposal reviewed for approval.");

        // if we specified a log file, write to it
        if (strlen (query_room_log_file ()))
        {
            write_file (query_room_log_file (),
                ctime(time()) + " " + this_player()->query_name ()
                + " submitted a room to " + query_room_file_name () + "\n");
        }

        reset_room_creator ();
        return 1;
    }
    else // was not successful writing out the file
    {
        command ("say Sorry -- something went wrong. Please make a bug report.");

        // if we specified a log file, write to it
        if (strlen (query_room_log_file ()))
        {
            write_file (query_room_log_file (),
                ctime(time()) + " " + this_player()->query_name ()
                + " encountered an error when submitting"
                + " a room to " + query_room_file_name () + "\n");
        }

        reset_room_creator ();
        return 1;
    }

}

/*
 * Function name: cancel_room
 * Description:   cancel the creation of the room and
 *                reset all the variables.
 * Arguments:     the string the player passed to the command
 * Returns:       1
 */
int
cancel_room (string str)
{
    if (!composer)
    {
        command ("say But no area is currently being specified...");
        return 1;
    }

    if (!check_is_room_creator (this_player ()))
        return 1;

    reset_room_creator ();
    command ("say OK, you have cancelled your area specification.");
    return 1;
}

