/*
 * File:     emote_maker.c
 * Created:  Cirion, 1998.11.16
 * Purpose:  Soul to create emotion souls (very spiritual).
 * Modification Log:
 *
 */
#pragma strict_types

#include <std.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/cmd/std/tracer_tool_base";

// quote character for code readability
#define QT "\""
#define NEWLINE "\n"

// default indention length
#define INDENT "    "

#define EMAKE_TRUE_VALUE "true"

mapping emake_flags;

/*
 * Example usages:
    emake -verb grin -adverb evilly -first CNAME grin ADVERB/CNAME grin ADVERB at %l
    -second FIRST grins ADVERB/FIRST grins ADVERB at %l -subloc grinning ADVERB -living true
    -soul /d/Avenir/cirion/test_soul.c -visual

    emake -verb sigh -adverb sadly -first YOU VERB ADVERB

    emake -verb float -adverb victoriously -first /YOU VERB ADVERB over the demise of TARGET.

    emake -verb bounce -adverb joyfully -first YOU VERB around ADVERB.NEWLINEPOSSESSIVE eyes sparkle with joy.
 *
 */

/*
 * Function name: get_soul_id
 * Description:   Give the identifier of the soul
 * Returns:       The soul's name
 */
public string
get_soul_id()
{
    return "Cirion's Soulmaker";
}

/*
 * Function name: query_tool_soul
 * Description:   Show that this is a wizard tool soul
 * Returns:       1
 */
public int
query_tool_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description:   Return the list of commands that can be
 *                used, and the functions that they should call.
 * Returns:       a mapping of the form ([ "command" : "function" ])
 */
public mapping
query_cmdlist()
{
    return ([
           "emake" : "emake",
           "help": "help",
          ]);
}

/* 
 * Function name: help
 * Description:   Give help for the emake command
 */
int
help(string str)
{
    if(str != "emake")
        return 0;

    write("Flages for the emake command:\n"
        + "  -help:                       Show this help text\n"
        + "  -first:                      Actor's text\n"
        + "  -second:                     Target's text\n"
        + "  -third:                      Onlooker's text\n"
        + "  -adverb:                     Default adverb for emote\n"
        + "  -verb:                       The verb which will be displayed\n"
        + "  -verb_cmd:                   The command to use the emote (default: verb\n"
        + "                               flag)\n"
        + "  -debug [true/false]:         Show debugging information\n"
        + "  -verbal [true/false]:        If true, emote will not work when\n"
        + "                               LIVE_M_MOUTH_BLOCKED\n"
        + "  -preview [true/false]:       Preview the code for the emote\n"
        + "  -visual [true/false]:        If true, emote will not be displayed to those\n"
        + "                               who cannot see actor\n"
        + "  -chaff:                      Prepositions & articles optionally used in emote\n"
        + "                               sentence\n"
        + "  -living [true/false/either]: If true, target must be living, if false, target\n"
        + "                               must be nonliving\n"
        + "  -subloc:                     The sublock the emotion will add to the actor\n"
        + "  -onetarget:                  Constrain emotion to one target only\n"
        + "  -noload:                     Do not reload the soul after emotion is added\n"
        + "  -noadd:                      Do not add the soul to youself (default: false)\n"
        + "  -remove:                     Delete the soul once it has been created an tested\n"
        + "  -comment:                    Comment to add at the top of the emotion\n"
        + "  -soul:                       The path to the soul to add\n"
        + "                               (default: ~/emote_soul.c)\n"
        + "  -check:                      Code to use to check to see if a single target is\n"
        + "                               a valid recipient of the emotion (e.g.,\n"
        + "                               -check tp->query_race() == \"hobbit\"\n"
        + "  -check_fail:                 notify_fail if the target fails -check\n"
        + "  -test:                       Clone NPCs to test the new emotion\n\n");

    write("Includes for the emake command:\n"
        + "  YOU:         Actor's name\n"
        + "  TARGET:      Target's name\n"
        + "  ADVERB:      Adverb for emotion\n"
        + "  VERB:        Verb for emotion\n"
        + "  PRONOUN:     Actor's pronoun (he, she, it)\n"
        + "  POSSESSIVE:  Actor's possessive (his, her, its)\n"
        + "  OBJECTIVE:   Actor's objective (him, her, it)\n"
        + "  TPRONOUN:    Target's pronoun (he, she, it)\n"
        + "  TPOSSESSIVE: Target's possessive (his, her, its)\n"
        + "  TOBJECTIVE:  Target's objective (him, her, it)\n\n");

    write("Example usage:\n"
        + "  emake -verb smile -adverb happily -first YOU VERB ADVERB.\n"
        + "  emake -verb growl -adverb bestially -onetarget -living -first YOU VERB ADVERB./YOU VERB ADVERB at TARGET\n"
        + "  emake -verb\n"
        + "  emake -verb\n"
        + "  emake -verb\n");

    return 1;

}


/*
 * Function name: error_code
 * Description:   Simple function to set the notify_fail() and
 *                return 0. Used like: return error_code("can't find file.");
 * Arguments:     str - the error string to set
 *                write_out - if 1, also write the message
 * Returns:       0, always
 */
varargs int
error_code(string str, int write_out = 0)
{
    string fail_msg;

    fail_msg = query_verb() + " error: " + str + "\n";

    notify_fail(fail_msg);

    if(write_out) // also write it out
        write(fail_msg);

    return 0;
}


/*
 * Function name: enquote
 * Description:   Function to wrap the specified text
 *                in quotes.
 * Arguments:     str - the text to wrap
 * Returns:       "str"
 */
string
enquote(string str)
{
    if(!strlen(str))
        return str;

    return QT + str + QT;
}

/*
 * Function name: string_position
 * Description:   Locate the position of a find string within
 *                source text.
 * Arguments:     source - the text to search in
 *                find - the string to locate
 *                instance - look for the nth instance of find
 *                start - character at which to start scanning in the
 *                    source block
 * Returns:       the position of the instance-th instance of
 *                find in source (after the start-th character)
 */
varargs int
string_position(string source, string find, int instance = 1, int start = 0)
{
    string *str_array;
    int     pos = 0, n;

    // check to see if we really have a source string
    if(strlen(source) == 0)
        return -1;

    // sanity checking
    if(start >= strlen(source))
        throw("string_position() error: start (" + start + ") specified is greater than "
            + "string length (" + strlen(source) + ").\n");

    // if we specified to start later in the source text block,
    // cut down the text up until the point we want.
    source = source[start .. strlen(source)-1];

    str_array = explode(source, find);

    if(sizeof(str_array) <= instance) // find string not found
        return -1;

    // else find existed, and the nth instance
    for(n=0; n<instance; n++)
    {
        pos += strlen(str_array[n]);

        // since "find" was parsed out, also add on its length after the first iteration
        if(n) 
            pos += strlen(find);
    }

    return pos + start;
}

/*
 * Function name: insert_string
 * Description:   Insert a string into a source block of text
 * Arguments:     str - the source text
 *                insert - the string to insert
 *                where - the position in which to insert the string
 * Returns:       the new string
 */
string
insert_string(string str, string insert, int where)
{
    return str[0 .. where + 1] + insert + str[where + 2 .. strlen(str) - 1];
}

/*
 * Function name: create_new_soul
 * Description:   Create a new command soul file to
 *                which to write the emotion code.
 * Arguments:     path - the path of the file to create
 * Returns:       1 if success
 */
public int
create_new_soul(string path)
{
    string code = "";

    path += ".c";

    code += "/*" + "\n";
    code += " * File: " + path + "\n";
    code += " * Created: " + this_player()->query_name() + ", " + ctime(time()) + "\n";
    code += " * Purpose: Command soul" + "\n";
    code += " * Note: This file was auto-created by Cirion's Soulmaker tool" + "\n";
    code += " *     (" + file_name(this_object()) + ")" + "\n";
    code += " */" + "\n";

    code += "#include <macros.h>" + "\n";
    code += "#include <std.h>" + "\n";
    code += "#include <stdproperties.h>" + "\n";
    code += "inherit " + QT + "/cmd/std/command_driver" + QT + ";" + "\n";

    code += "\n";

    code += "/* Commands */" + "\n";
    code += "mapping query_cmdlist()" + "\n";
    code += "{" + "\n";
    code += INDENT + "return ([" + "\n";
    code += INDENT + "]);" + "\n";
    code += "" + "\n";
    code += "}" + "\n";
    code += "" + "\n";
    code += "/* Id and autoload */" + "\n";
    code += "string get_soul_id() " + "\n";
    code += "{ " + "\n";
    code += INDENT + "return " + QT + "Generic Emotion Soul" + QT + ";" + "\n"; 
    code += "}" + "\n";
    code += "" + "\n";
    code += "/* It is a real command soul */" + "\n";
    code += "int query_cmd_soul() " + "\n";
    code += "{ " + "\n";
    code += INDENT + "return 1; " + "\n";
    code += "}" + "\n";
    code += "\n";
    
    if(!(write_file(path, code)))
        return error_code("could not write to file: " + path);

    write(query_verb() + ": created new soul file at: " + path + "\n");
    return 1;
}

/*
 * Function name: query_emotion_soul
 * Description:   Check the specified string for a command
 *                soul file location.
 * Arguments:     str - the string to check
 * Returns:       the path to a command soul (default to
 *                "/d/dom/wiz/emote_soul" if no str is specified)
 */
public varargs string
query_emotion_soul(string str)
{
    int len, i;
    string check, ret;

    if(!strlen(str)) // return the default emotion soul
    {
        check = SECURITY->query_wiz_path(this_player()->query_real_name())
            + "/emote_soul";
        ret = check;

        // if we are using the default soul, make sure it
        // is less than 50K.
        while(file_size(ret + ".c") > (50 * 1000))
        {
            i++;
            ret = check + i;
        }

        return ret;
    }

    if(string_position(str, "/") < 0) // if there was no "/" in the name ...
        str = this_player()->query_path() + "/" + str; // ... default to the current path

    len = strlen(str);
    if(str[len-2 .. len-1] == ".c") // parse out the trailing ".c"
        str = str[0 .. len-3];

    return str;
}

/*
 * Function name: test_load_soul
 * Description:   Try to reload the command soul to which
 *                we appended the new emotion.
 * Arguments:     soul_path - the path to the soul to which to load
 * Returns:       1 if success
 */
private int
test_load_soul(string soul_path)
{
    int    len;

    soul_path = query_emotion_soul(soul_path); // return the default soul if none is specified

    len = strlen(soul_path);

    if(soul_path[len-2 .. len-1] != ".c")
        soul_path += ".c"; // append .c if it does not alreayd exist

    if(file_size(soul_path) <= 0)
        return error_code("error in loading soul: " + soul_path + " does not exist.");

    len = strlen(soul_path);
    soul_path = soul_path[0 .. len-3]; // now get rid of the ".c" so we can load it

    if(find_object(soul_path)) // the soul is currently loaded ...
        SECURITY->do_debug("destroy", find_object(soul_path));

    if(find_object(soul_path)) // still_loaded!
        error_code("could not destruct " + soul_path, 1);

    // try to load it, return 1 for success, 0 for error
    if(catch(soul_path->teleldensanka()))
        return error_code("error when reloading " + soul_path);

    if(!find_object(soul_path)) // still_loaded!
        error_code("could not reload " + soul_path, 1);

    return 1;
}

/*
 * Function name: insert_verb_in_init
 * Description:   Insert the very in the init() function
 *                of the command soul (or create and init()
 *                function if none was found).
 * Arguments:     verb - the verb to insert
 *                soul - the soul path to insert it into
 * Returns:       1 if success
 */
varargs int
insert_verb_in_init(string verb, string soul = "")
{
    string file, insert, verb_cmd;
    int    pos;

    verb_cmd = emake_flags["verb_cmd"];
    if(!strlen(verb_cmd)) // no -verb_cmd flag -- default to verb
        verb_cmd = verb;

    file = read_file(soul);
    if(!strlen(file))
        return error_code("file: " + soul + " had no content");

    if((pos = string_position(file, "query_cmdlist(", 1)) <= 0) // find the function...
        return error_code("could not locate query_cmdlist() function in " + soul);

    if((pos = string_position(file, "([", 1, pos)) <= 0) // ...now get the next instance of "(["
        return error_code("could not locate '([' in " + soul);

    insert = "\n" + INDENT + INDENT + QT + verb_cmd + QT
        + " : " + QT + verb_cmd + "_emote" + QT + ",";

    file = insert_string(file, insert, pos);

    if(!rm(soul))
        return error_code("could not delete " + soul);

    if(!write_file(soul, file))
        return error_code("could not write to " + soul);

    return 1;
}

/*
 * Function name: append_code_to_soul
 * Description:   Append the code for the emotion to
 *                the command soul.
 * Arguments:     code - the generated code to append
 *                soul - the soul file
 * Returns:       1 if success
 */
varargs int
append_code_to_soul(string code, string soul = "")
{
    if(!strlen(soul))
        soul = query_emotion_soul();

    if(file_size(soul + ".c") <= 0) // if the file does not exist
        if(!create_new_soul(soul)) // ... make a new soul ...
            return 0; // ... and return if we fail

    soul += ".c";

    if(!insert_verb_in_init(emake_flags["verb"], soul)) // put the verb in the command list
        return 0; // insert_verb sets the norify_fail

    if(!(write_file(soul, code))) // write the code to the soul
        return error_code("could not write to file: " + soul);


    return 1;
}

/*
 * Function name: replace_string
 * Description:   Replace all instances of one string
 *                with another in a block of source text.
 * Arguments:     source - the block of source text
 *                from - the string to replace
 *                to - the replacement string
 * Returns:       The string with 'from' replaced by 'to'
 */
string
replace_string(string source, string from, string to)
{
    // won't work if we have a '$' character in 'from',
    // but that is a pathological case we won't waste time
    // handling. Thanks to Mercade for this function.
    return extract(implode(explode(source + "$", from), to), 0, -2);
}

/*
 * Function name: replace_tags
 * Description:   Replace the emotion soul tags in the text
 *                that the user specified.
 * Arguments:     str - the string in which to replace the tags
 *                for_who - contextual usage of the source string (1 for
 *                    first person, 2 for second person, 3 for third person).
 *                for_target - 1 if this usage is for a target, 0 otherwise
 *                verb - the verb we are using
 *                verb_second - the third person singular form of the verb
 * Returns:       The string with the tags replaced
 */
varargs string
replace_tags(string str, int for_who = 1, int for_target = 0,
        string verb = "", string verb_second = "")
{
    if(emake_flags["debug"] == EMAKE_TRUE_VALUE) // write out a debugging message
        write(" - " + str + "\n");

    if(!strlen(verb_second))
        verb_second = LANG_PWORD(verb); // default to the "plural" of the verb (which is an OK guess)

    // adverbs need to have their preceeding space stripped out, since
    // we will be using parse_adverb_with_space() in the auto-generated
    // code. Putting this here is sort of a kludge, but it is the
    // easiest way around the problem.
    str = replace_string(str, " ADVERB", "ADVERB");

    str = replace_string(str, "ADVERB", enquote(" + adverb + "));

    str = replace_string(str, "NEWLINE", "\\n");

    switch(for_who)
    {
        case 3: // third person is viewing
            str = replace_string(str, "VERB", verb_second);
            str = replace_string(str, "YOU ADVERB", "YOUADVERB"); // get rid of space between YOU and ADVERB
            str = replace_string(str, " TARGET", "TARGET");

            if(for_target)
                str = replace_string(str, "YOU ", ""); // not used for third person

            str = replace_string(str, "YOU", ""); // not used for third person

            str = replace_string(str, "TPOSSESSIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_possessive() + "));
            str = replace_string(str, "TOBJECTIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_objective() + "));
            str = replace_string(str, "TPRONOUN", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_pronoun() + "));

            str = replace_string(str, "POSSESSIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_possessive() + "));
            str = replace_string(str, "OBJECTIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_objective() + "));
            str = replace_string(str, "PRONOUN", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_pronoun() + "));

            str = replace_string(str, "TARGET", QT + ", oblist, " + QT);
            break;

        case 2: // second person is viewing
            str = replace_string(str, "VERB", verb_second);
            str = replace_string(str, "YOU", ""); // not used for second person

            str = replace_string(str, "TPOSSESSIVE", "your");
            str = replace_string(str, "TOBJECTIVE", "you");
            str = replace_string(str, "TPRONOUN", "you");

            str = replace_string(str, "POSSESSIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_possessive() + "));
            str = replace_string(str, "OBJECTIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_objective() + "));
            str = replace_string(str, "PRONOUN", enquote(NEWLINE
                 + INDENT + INDENT + "+ tp->query_pronoun() + "));

            str = replace_string(str, "TARGET", "you");
            break;

        case 1: // first person (fall through to default)
        default:
            str = replace_string(str, "VERB", verb);
            str = replace_string(str, "YOU", "You");
            str = replace_string(str, " TARGET", "TARGET");

            str = replace_string(str, "TPOSSESSIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_possessive() + "));
            str = replace_string(str, "TOBJECTIVE", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_objective() + "));
            str = replace_string(str, "TPRONOUN", enquote(NEWLINE
                 + INDENT + INDENT + "+ recipient->query_pronoun() + "));

            str = replace_string(str, "POSSESSIVE", "your");
            str = replace_string(str, "OBJECTIVE", "you");
            str = replace_string(str, "PRONOUN", "you");

            str = replace_string(str, "TARGET", QT + ", oblist, " + QT);
            break;
    }

    if(emake_flags["debug"] == EMAKE_TRUE_VALUE) // write out a debugging message
        write(" -> " + str + "\n");

    return str;
}

/*
 * Function name: generate_emote_code
 * Description:   Generate LPC code that uses /std/command_driver
 *                to create an emotion.
 * Arguments:     lots
 * Returns:       1 if successful
 */
int
generate_emote_code(string verb, string adverb, string soul,
    string first, string second, string third,
    string subloc, string visual, string chaff, string onetarget)
{
    string code = "", verb_all, verb_all2act, verb_target, verb_cmd;
    string first_notarget, first_target, second_notarget, second_target,
        third_notarget, third_target;
    string *tmp_array;
    int     second_person_enabled, first_person_enabled;
    string  comment;

    if(!strlen(first))
        return error_code("you must specify the -first flag.");

    if(!strlen(verb))
        return error_code("you must specify the -verb flag.");

    verb_cmd = emake_flags["verb_cmd"];
    if(!strlen(verb_cmd)) // no -verb_cmd flag -- default to verb
        verb_cmd = verb;


    if( !(strlen(adverb)) &&
        ((string_position(first, "ADVERB") >= 0) 
        || (string_position(second, "ADVERB") >= 0) 
        || (string_position(third, "ADVERB") >= 0)) )
        return error_code("tag ADVERB found in emotion string, but "
            + "flag -adverb was not specified.");

    // we specified that the verb is visual-only (i.e., won't be
    // seen if hidden or invisible, won't reveal)
    if((visual != "false") && (strlen(visual)))
    {
        verb_all = "allbb";
        verb_all2act = "all2act";
        verb_target = "target";
    }
    else
    {
        verb_all = "all";
        verb_all2act = "all2actbb";
        verb_target = "targetbb";
    }


    // now parse the emotion string specifications into target/notarget
    // strings.
    tmp_array = explode(first, "/");
    first_notarget = tmp_array[0];
    if(sizeof(tmp_array) > 2) // too many "/" characters
        return error_code("too many '/' characters in emotion specification.");
    else if(sizeof(tmp_array) < 2) // no target in emote specification
        first_target = "";
    else
        first_target = tmp_array[1];

    if(!strlen(second))
        second = first;
    tmp_array = explode(second, "/");
    second_notarget = tmp_array[0];
    if(sizeof(tmp_array) > 2) // too many "/" characters
        return error_code("too many '/' characters in emotion specification.");
    else if(sizeof(tmp_array) < 2) // no target in emote specification
        second_target = "";
    else
        second_target = tmp_array[1];

    // no second person specified: default to interpretation of first person
    if(!strlen(second_notarget))
        second_notarget = first_notarget;
    if(!strlen(second_target))
        second_target = first_target;

    if(!strlen(third))
        third = second;
    tmp_array = explode(third, "/");
    third_notarget = tmp_array[0];
    if(sizeof(tmp_array) > 2) // too many "/" characters
        return error_code("too many '/' characters in emotion specification.");
    else if(sizeof(tmp_array) < 2) // no target in emote specification
        third_target = "";
    else
        third_target = tmp_array[1];

    // no third person specified: default to interpretation of second
    if(!strlen(third_notarget))
        third_notarget = second_notarget;
    if(!strlen(third_target))
        third_target = second_target;


    // now replace all the tags we embedded in the emote specification
    first_notarget = replace_tags(first_notarget, 1, 0, verb);
    first_target = replace_tags(first_target, 1, 1, verb);
    second_notarget = replace_tags(second_notarget, 2, 0, verb);
    second_target = replace_tags(second_target, 2, 1, verb);

    third_notarget = replace_tags(third_notarget, 3, 0, verb);
    third_target = replace_tags(third_target, 3, 1, verb);

    chaff += " the"; // there is no reason why we would not want to allow 'the'
    // turn a string "to at the" into "[to] [at] [the]" for
    // use with parse_this()
    chaff = "[" + replace_string(chaff, " ", "] [") + "]";

    code += "\n";
    code += "// emotion " + QT + verb + QT + " added by\n";
    code += "// Cirion's Soulmaker on " + ctime(time()) + "\n";
    code += "public int\n";

    code += verb_cmd + "_emote(string arg)\n";
    code += "{\n";

    code += INDENT + "object *oblist, recipient, tp;" + "\n";
    code += INDENT + "string *how, adverb, tmp;" + "\n";
    code += NEWLINE;

    comment = emake_flags["comment"];
    if(strlen(comment))
    {
        code += INDENT + "// " + comment + NEWLINE;
        code += NEWLINE;
    }

    code += INDENT + "tp = this_player();" + "\n";
    code += INDENT + "how = parse_adverb_with_space(arg, " + QT + adverb + QT + " , 0);" + "\n";
    code += INDENT + "adverb = how[1];" + "\n";
    code += NEWLINE;

    // we specified the 'verbal' flag -- check for LIVE_M_MOUTH_BLOCKED
    // prop
    if(emake_flags["verbal"] == EMAKE_TRUE_VALUE)
    {
        code += INDENT + "if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))" + "\n";
        code += INDENT + "{" + "\n";
        code += INDENT + INDENT + "if(stringp(tmp))\n";
        code += INDENT + INDENT + INDENT + "notify_fail(tmp + " + QT + "\\n" + QT + ");\n";
        code += INDENT + INDENT + "else\n";
        code += INDENT + INDENT + INDENT + "notify_fail(" + QT + "You cannot seem to use your mouth.\\n" + QT + ");\n";
        code += INDENT + INDENT + "return 0;" + "\n";
        code += INDENT + "}" + "\n";
        code += NEWLINE;
    }

    // code to check if the target is valid
    if(emake_flags["check"])
    {
        code += INDENT + "if (!(" + emake_flags["check"] + "))" + "\n";
        code += INDENT + "{" + "\n";

        if(emake_flags["check_fail"])
            code += INDENT + INDENT + "notify_fail(" + QT
                + emake_flags["check_fail"] + "\\n" + QT + ");" + "\n";
        else
            code += INDENT + INDENT + "notify_fail(" + QT
                + "The target is not valid.\\n" + QT + ");" + "\n";

        code += INDENT + INDENT + "return 0;" + "\n";
        code += INDENT + "}" + "\n";
    }
    code += NEWLINE;

    code += INDENT + "if (!stringp(how[0]))" + "\n";
    code += INDENT + "{" + "\n";

    // if we did not specify a target nodescription for the first person,
    // then we do not want the emotion to be done when no targets are given.
    first_person_enabled = strlen(first_notarget);

    if(!first_person_enabled)
    {
        code += INDENT + INDENT + "notify_fail(" + QT + capitalize(verb) + " [how] [who/what]?\\n" + QT + ");" + "\n";
        code += INDENT + INDENT + "return 0;" + "\n";
    }
    else // if(!first_person_enabled)
    {
        first_notarget = enquote(first_notarget + "\\n");
        code += INDENT + INDENT + "write(" + first_notarget + ");" + "\n";
        third_notarget = enquote(third_notarget);
        code += INDENT + INDENT + verb_all + "(" + third_notarget + ", adverb);" + "\n";
        code += INDENT + INDENT + "return 1;" + "\n";
    }

    code += INDENT + "}" + "\n";
    code += NEWLINE;


    // if we did not specify a target description for the first person,
    // then we do not want the emotion to accept any targets.
    second_person_enabled = strlen(first_target);

    if(!second_person_enabled)
    {
        code += INDENT + "notify_fail(" + QT + capitalize(verb) + " [how]?\\n" + QT + ");" + "\n";
        code += INDENT + "return 0;" + "\n";
    }
    else // if(!second_person_enabled)
    {
        if(emake_flags["living"] == "true") // we specified that we only want to do this on livings
            code += INDENT + "oblist = parse_this(how[0], " + QT + chaff + " %l" + QT + ");" + "\n";
        else
            code += INDENT + "oblist = parse_this(how[0], " + QT + chaff + " %i" + QT + ");" + "\n";

        code += NEWLINE;

        code += INDENT + "if (!sizeof(oblist))" + "\n";
        code += INDENT + "{" + "\n";
        code += INDENT + INDENT + "notify_fail(" + QT + capitalize(verb) + " [how] [who/what]?\\n" + QT + ");" + "\n";
        code += INDENT + INDENT + "return 0;" + "\n";
        code += INDENT + "}" + "\n";
        code += NEWLINE;

        // we only want to allow the emotion for one target or a nonliving
        if((emake_flags["onetarget"] == "true") || (emake_flags["living"] == "false"))
        {
            code += INDENT + "if (sizeof(oblist) > 1)" + "\n";
            code += INDENT + "{" + "\n";
            code += INDENT + INDENT + "notify_fail(" + QT + "You may only do that to a single target.\\n" + QT + ");" + "\n";
            code += INDENT + INDENT + "return 0;" + "\n";
            code += INDENT + "}" + "\n";
        }
        code += NEWLINE;

        code += INDENT + "recipient = oblist[0];" + "\n";
        code += NEWLINE;

        if(emake_flags["living"] == "false") // only non-living recipients
        {
            code += INDENT + "if (living(recipient))" + "\n";
            code += INDENT + "{" + "\n";
            code += INDENT + INDENT + "notify_fail(" + QT + "You cannot do that to a living being.\\n" + QT + ");" + "\n";
            code += INDENT + INDENT + "return 0;" + "\n";
            code += INDENT + "}" + "\n";
        }

        code += INDENT + "actor(" + QT + first_target + QT + ");" + "\n";
        code += INDENT + verb_target + "(" + QT + second_target + QT + ", oblist, adverb);" + "\n";
        code += INDENT + verb_all2act + "(" + QT + third_target + QT + ", adverb);" + "\n";
        code += INDENT + "return 1;" + "\n";

    } // if(!second_person_enabled)

    code += "}\n";

    // sometimes we accidently put in a blank string -- this is
    // the simplest way to get rid of that.
    code = replace_string(code, "\"\" + ", "");

    // there is a bug somewhere that causes added emotions
    // to end in "....". Until I can fix it, this should
    // patch it.
    //    code = replace_string(code, "..", "");
    //    code = replace_string(code, "..", "");

    if(emake_flags["preview"] == "true")
        write(code); // just show a preview of the emotion code
    else // otherwise add it to the soul file
    {
        if(!append_code_to_soul(code, soul))
            return 0;
    }

    return 1;
}

/*
 * Function name: query_default_flags
 * Description:   Returns the default values for the command line
 *                flags should the user not explicitely set them/
 * Returns:       a mapping of the default flags
 */
mapping
query_default_flags()
{
    mapping def_flags =
        ([  "living" : "either",
            "visual" : "false",
            "chaff"  : "to at",
            "verbal" : "false" ]);

    return def_flags;
}

/*
 * Function name: npc_test_soul
 * Description:   Clone two npcs to test the new commands
 *                in the soul. This is a bit CPU-consumptive, but it is
 *                worth it to iron out visual typos that tend to crop
 *                up in emotions (which lead to headaches down the road).
 * Arguments:     soul - the path to which the soul had been added
 * Returns:       void
 */
void
npc_test_soul(string soul)
{
    object npc1, npc2, old_tp;
    string verb, verb_func, verb_cmd;

    setuid();
    seteuid(getuid(this_object()));

    verb_cmd = emake_flags["verb_cmd"];
    if(!strlen(verb_cmd)) // no -verb_cmd flag -- default to verb
        verb_cmd = emake_flags["verb"];

    old_tp = this_player(); // remember this_player(), since we will be changing it
    verb = emake_flags["verb"];
    verb_func = verb_cmd + "_emote";

    npc1 = clone_object("/std/monster");
    npc1->set_name("gob");
    npc1->add_name("goblin");
    npc1->add_prop(LIVE_I_NEVERKNOWN, 1);
    npc1->set_short("smelly male goblin");
    npc1->set_race("goblin");
    npc1->set_adj(({ "smelly", "male" }));
    npc1->set_gender(G_MALE);
    npc1->add_cmdsoul(soul);
    npc1->update_hooks();
    npc1->move(environment(old_tp));

    npc2 = clone_object("/std/monster");
    npc2->set_name("elfin");
    npc2->add_name("elf");
    npc2->add_prop(LIVE_I_NEVERKNOWN, 1);
    npc2->set_short("ivory-skinned, long-legged female elf");
    npc2->set_race("elf");
    npc2->set_adj(({ "ivory-skinned", "long-legged", "female" }));
    npc2->set_gender(G_FEMALE);
    npc2->add_cmdsoul(soul);
    npc2->update_hooks();
    npc2->move(environment(old_tp));

    set_this_player(old_tp);
    call_other(soul, verb_func);
    call_other(soul, verb_func, "smelly male goblin");

    old_tp->command(verb_cmd);
    old_tp->command(verb_cmd + " gob");
    old_tp->command(verb_cmd + " elfin");

    // test permutations of the soul with the NPCs
    npc2->command(verb_cmd);
    npc2->command(verb_cmd + " " + old_tp->query_real_name());
    npc2->command(verb_cmd + " gob");

    npc1->command(verb_cmd);
    npc1->command(verb_cmd + " " + old_tp->query_real_name());
    npc1->command(verb_cmd + " elfin");

    // reset this_player to the original one
    set_this_player(old_tp);

    // clean up the temp NPCs
    npc1->remove_object();
    npc2->remove_object();

}

/*
 * Function name: emake
 * Description:   Command to take the specified flags and create
 *                code for an emotion.
 * Arguments:     the command line flags
 * Returns:       1 if success, 0 if failure
 */
int
emake(string arguments)
{
    string *args, *arr;
    string arg, cmd, value, soul, vb;
    int    i;

    vb = query_verb();

    if(!strlen(arguments))
        return error_code("no command line flags specified. See 'help "
            + vb + "' for usage.");

    args = explode(arguments, " -"); // parse flags based on ' -' chars
    args[0] = args[0][1 .. (strlen(args[0])-1)]; // get rid of leading '-' in first flag

    emake_flags = query_default_flags(); // initialize the default flags

    // loop through the arguments array and make flags mapping
    for(i=0;i<sizeof(args);i++) 
    {
        arg = args[i];
        arr = explode(arg, " ");
        cmd = arr[0];
        if(sizeof(arr) == 1)
            value = EMAKE_TRUE_VALUE; // default value for stand-alone flag is "true"
        else
        {
            arr = exclude_array(arr, 0, 0); // get rid of the first element
            value = implode(arr, " "); // turn it back into a space-seperated string
        }

        emake_flags += ([ cmd : value ]); // add it to the command list
    }

    // help requested?
    if(emake_flags["help"] == EMAKE_TRUE_VALUE)
        return help("emake");

    // now we have a mapping of all the flags we specified:
    // create the emotion. generate_emotion_code() will handle
    // any notify_fail's should it fail.
    if(!generate_emote_code(emake_flags["verb"], emake_flags["adverb"], emake_flags["soul"],
        emake_flags["first"], emake_flags["second"], emake_flags["third"],
        emake_flags["subloc"], emake_flags["visual"], emake_flags["chaff"], emake_flags["onetarget"]))
        return 0;

    soul = query_emotion_soul(emake_flags["soul"]); // get the soul file

    if(emake_flags["noload"] != "true") // if we did not specify the "noload" flag ...
        if(!test_load_soul(soul)) // ... try to reload the soul ...
            return error_code("emotion added, but could "
                + "not reload the soul"); // ... and return an error if we fail

    // verify that the soul is added to the wizard, unless they
    // specified the "noadd" flag
    if(!emake_flags["noadd"])
        if(member_array(soul, this_player()->query_cmdsoul_list()) == -1)
            if(this_player()->add_cmdsoul(soul)) // add the soul
                write(vb + ": added command soul: " + soul + " to your soul list.\n");

    this_player()->update_hooks(); // rebuild the wizards command list

    if(emake_flags["test"] == EMAKE_TRUE_VALUE) // we said we want to test the emotion
        npc_test_soul(soul); // clone two npcs and test all the permutations of the emote

    if(emake_flags["remove"] == EMAKE_TRUE_VALUE) // we want to delete the soul after we are done
    {
        this_player()->remove_cmdsoul(soul);
        this_player()->update_hooks();
        if(!rm(soul + ".c")) // delete the actual file as well
            write("Failed to delete file: " + soul + ".c\n");
        else
            write("Deleted file: " + soul + ".c\n");
    }

    write(vb + ": done.\n");
    emake_flags = ([ ]); // clear out the global mapping
    return 1;
}

