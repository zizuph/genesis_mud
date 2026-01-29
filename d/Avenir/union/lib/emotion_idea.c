/*
 * File:     emotion_idea.c
 * Created:  Cirion, 1998.05.02
 * Purpose:  A means for guild members to log new emotion
 *           ideas. It will present the player with a
 *           series of questions that will then construct
 *           the code for easy inclusion into the command soul.
 * Modification Log: 
 *          
 */
#define DELIMITER      "\n/* command definintions for emotions.\n" \
                       + " * Don't change this comment -- it is auto-generated, and\n" \
                       + " * is used by the emotion_idea module.\n" \
                       + " *\\n"

// we won't let out emotions file pass 15K
#define MAX_FILE_SIZE  15000

#define CODE(str)      (code += "str\n")

#define EMOTION_EMOTE_CMD      "_emotion_emote_cmd"
#define EMOTION_TARGET         "_emotion_target"
#define EMOTION_ADVERB         "_emotion_adverb"
#define EMOTION_1ST_PERSON     "_emotion_1st_person"
#define EMOTION_2ND_PERSON     "_emotion_2nd_person"
#define EMOTION_3RD_PERSON     "_emotion_3rd_person"
#define EMOTION_SEEN           "_emotion_seen"
#define EMOTION_SOULDESC       "_emotion_souldesc"
#define EMOTION_COMMENTS       "_emotion_comments"

#define TP                     this_player()

string emotion_file;


void emote_entry1();
void emote_entry2(string str);
void emote_entry3(string str);
void emote_entry4(string str);
void emote_entry5(string str);
void emote_entry6(string str);
void emote_entry7(string str);
void emote_entry8(string str);
void emote_entry9(string str);
void emote_entry10(string str);
int emotion_check_cancel(string str);

/*
 * Function name: create_emotion_file
 * Description:   create a default template for the emotion file
 * Returns:       1 if successful
 */
int
create_emotion_file()
{
    // check to see if the file exists!
    if((!emotion_file) || (file_size(emotion_file) > 0))
        return 0;

/* begin code template

inherit "/cmd/std/command_driver";
#include <cmdparse.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <stdproperties.h>

int
query_cmd_soul() 
{ 
    return 1; 
}

DELIMITER

mapping query_cmdlist()
{
    return command_map;
}


 * end code template */


}


void
reset_emotion_props(object who = this_player())
{
    who->remove_prop(EMOTION_EMOTE_CMD);
    who->remove_prop(EMOTION_TARGET);
    who->remove_prop(EMOTION_ADVERB);
    who->remove_prop(EMOTION_1ST_PERSON);
    who->remove_prop(EMOTION_2ND_PERSON);
    who->remove_prop(EMOTION_3RD_PERSON);
    who->remove_prop(EMOTION_SEEN);
    who->remove_prop(EMOTION_SOULDESC);
    who->remove_prop(EMOTION_COMMENTS);

}

/*
 * Function name: backup_emotion_file
 * Description:   the emotion file has gotten large: back it up
 *                to filename<n>.c, where <n> is the next unique
 *                suffix.
 * Arguments:     the name of the current emotion file (.c included)
 * Returns:       1 if successful
 */
int
backup_emotion_file(string file)
{
    int i;
    string basename;

    if(file_size(file) <= 0)
        return 0;

    i = 0;

    basename = implode(explode(file, ".c"), "");

    while(file_size(file) > 0)
    {
        i++;

        // find a unique, non-existant file name for the backup soul
        if(file_size(basename + i + ".c") > 0)
            continue;
        else
            // move the original soul to the backup soul.
            return rename(file, basename + i + ".c");
    }

    // sanity check
    return 0;
}

int
add_to_emotion_file(string command, string code)
{
    string   curr_file, *parts, prefix, suffix;

    if(file_size(emotion_file) > MAX_FILE_SIZE)
    {
        // file size has gotten too large -- reaname it
        // to a new file name and start with a fresh one.
        if(!backup_emotion_file(emotion_file))
            return 0;
    }

    if(file_size(emotion_file) <= 0)
    {
        // if the file does not exist, create a new one.
        if(!create_emotion_file())
            return 0;
    }

    curr_file = read_file(emotion_file);

    if((!curr_file) || (strlen(curr_file) <= 0))
        return 0;

    // break it up into two parts
    parts = explode(curr_file, DELIMITER);

    // did someone mess with the code?
    if(sizeof(parts) != 2)
        return 0;

    prefix = parts[0];
    suffix = parts[1];

    // add the function that has the code in it.
    prefix += "\n\npublic nomask int\nemote_" + command + "(string arg)\n{\n"
        + code + "\n}\n";

    // append the add_action to the end of the command list.
    suffix = implode(explode(suffix, "]);"), "    \"emote_" + command + "\""
        + " : \"" + command + "\",\n]);");

    curr_file = prefix + DELIMITER + suffix;

    // delete the old emotion file -- we will be writing a new one.
    if(!rm(emotion_file))
        return 0;

    write_file(emotion_file, curr_file);

}

/*
 * Function name: set_emotion_file
 * Description:   initialize the file name of the tempalte to
 *                when new emotions will be added.
 * Arguments:     the name of the file that will be the emotion soul
 * Returns:       void
 */
void
set_emotion_file(string str)
{
    emotion_file = str;
}

/*
 * Function name: string_parse
 * Description:   parse a certain string so it can be included in
 *                quotes in a soul.
 * Arguments:     the string to be parsed
 * Returns:       the result of the parsing.
 */
string
string_parse(string str)
{
    // turn " characters into \"
    str = implode(explode(str, "\""), "\\\"");
}

/*
 * Function name: strip_trailing_chars
 * Description:   stip off trailing non-alphanumeric characters
 *
 * Arguments:     the string to strip
 * Returns:       the resulting stipped string
 */
string
strip_trailing_chars(string str)
{
    if(!strlen(str))
        return str;

    // parse out trailing non-alpha characters
    while((str[(strlen(str)-1)] > 'z') || (str[(strlen(str)-1)] < 'a'))
    {
        str = str[0 .. (strlen(str)-1)];
    }
 
    return str;
}


void
emote_entry1()
{
    write("Enter the command you enter to execute the emotion: ");

    input_to(emote_entry2);
}

void
emote_entry2(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_EMOTE_CMD, str);

    write("Is the target of the emotion another living creature, an object, "
        + "or none ['living'/'object'/'none']: ");

    input_to(emote_entry3);
}


void
emote_entry3(string str)
{
    if(emotion_check_cancel(str))
        return;


    TP->add_prop(EMOTION_TARGET, str);

    write("Enter the default adverb you use with this "
        + "emotion. ['none' for no adverb, blank for no default adverb]: ");

    input_to(emote_entry4);
}

void
emote_entry4(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_ADVERB, str);

    write("Enter what you see when you perform the emotion. "
        + "For example: \"You smile <adverb> at the "
        + "<target>.\": ");

    input_to(emote_entry5);
}

void
emote_entry5(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_1ST_PERSON, str);

    write("Enter what others in the same room will see when you perform "
        + "this emotion. For example, \"<You> smiles <adverb> at <target>.\": ");

    input_to(emote_entry6);
}


void
emote_entry6(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_2ND_PERSON, str);


    write("Enter what the target sees when you perform this emotion. For example, "
        + "\"<You> smiles <adverb> at you.\": ");

    input_to(emote_entry7);
}


void
emote_entry7(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_3RD_PERSON, str);

    write("Will the target or other people in the room see the "
        + "result of your emotion if you are invisible or hidden "
        + "from their sight? ['yes'/'no']: ");

    input_to(emote_entry8);
}


void
emote_entry8(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_SEEN, str);

    write("Does this emotion affect your long description when someone "
        + "else examines you? For example, \"is smiling <adverb>.\": ");

    input_to(emote_entry9);
}



void
emote_entry9(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_SOULDESC, str);

    write("Enter any additional comments to the reviewer of "
        + "this emotion: ");

    input_to(emote_entry10);
}


void
emote_entry10(string str)
{
    if(emotion_check_cancel(str))
        return;

    TP->add_prop(EMOTION_COMMENTS, str);

}


int
emotion_check_cancel(string str)
{
    if(str == "quit" || str == "~q" || str == "abort" || str == "q")
    {
        write("Aborted entering your emotion idea.\n");
        reset_emotion_props();
        return 1;
    }
    else
        return 0;
}

mixed
check_valid_single_word(string str)
{
    if(!strlen(str))
        return "Invalid entry: please enter a word. "
        + "Type 'abort' to abort entering the emotion.\n";

    if(sizeof(explode(str, " ")))
        return "Invalid entry: the word must not contain spaces. "
        + "Type 'abort' to abort entering the emotion.\n";

    return 0;
}


void
emotion_help()
{
    write("When entering an emotion idea, you will be presented with "
        + "a series of questions about how the emotion will work. When "
        + "entering the description of the emotion, you will need to "
        + "use certain 'tags' that define the way the emotion will "
        + "behave. These tags are surrounded by <>'s, and are defined "
        + "as follows:\n "
        + "\n"
        + "   <his>      - lower case possessive of the actor\n"
        + "   <His>      - upper case possessive of the actor\n"
        + "   <you>      - lower case description / name of the actor\n"
        + "   <You>      - upper case description / name of the actor*\n"
        + "   <target>   - lower case description / name of the target living\n"
        + "   <Target>   - upper case description / name of the target living*\n"
        + "   <object>   - lower case description / name of the target object\n"
        + "   <Object>   - upper case description / name of the actor object*\n"
        + "   <adverb>   - lower case adverb used with the emotion\n"
        + "   <Adverb>   - upper case adverb used with the emotion\n "
        + "\n * proper names will always be shown in upper case. The only "
        + "   time there is a difference between upper case and lower case "
        + "   tags is when the living is referred to by its short description. "
        + "   for example, <You> and <you> will always show your upper case "
        + "   real name to those who know your name, but when the observer "
        + "   does not know your name, <You> will show \"The long-haired elf\", "
        + "   where as <you> will show \"the long-haried elf\".\n"
        + "\nFor example, if an emotion is defined with the following "
        + "tags: "
        + "\nYou see: You smile <adverb> at the <target>.\n "
        + "Target sees: <You> smiles <adverb> at you.\n "
        + "Others see: <You> smiles <adverb> at <target>.\n "
        + "\n\nThe actual emotion, when performed, will look like this:\n "
        + "\nYou see: You smile sadly at the pale elf.\n "
        + "Target sees: The brown-eyed human smile sadly at you.\n "
        + "Others see: The brown-eyed human smiles sadly at the pale elf.\n "
        + "\nIn all cases, if any observer knows the name of the actor or "
        + "the target, they will see the real name (upper case) of that person. "
        + "In the above example, if everyone knew everyone else, they would "
        + "instead see: \n\n"
        + "You see: You smile sadly at Mercade.\n "
        + "Target sees: Cirion smile sadly at you.\n "
        + "Others see: Cirion smiles sadly at Mercade.\n ");
}


string
replace_tags(string str)
{
    if(!strlen(str))
        return str;

    str = implode(explode(str, "<his>"), "\" + tp->query_possessive() + \"");
    str = implode(explode(str, "<His>"), "\" + capitalize(tp->query_possessive()) + \"");
    str = implode(explode(str, "<you>"), "\" + QTNAME(tp) + \"");
    str = implode(explode(str, "<You>"), "\" + QCTNAME(tp) + \"");
    str = implode(explode(str, "<target>"), "\" + QTNAME(target) + \"");
    str = implode(explode(str, "<Target>"), "\" + QCTNAME(target) + \"");
    str = implode(explode(str, "<object>"), "\" + QSHORT(ob) + \"");
    str = implode(explode(str, "<Object>"), "\" + QSHORT(ob) + \"");
    str = implode(explode(str, "<adverb>"), "\" + adverb + \"");
    str = implode(explode(str, "<Adverb>"), "\" + capitalize(adverb) + \"");

    return str;

}


varargs string
create_emotion_code_notarget(object who = this_player(), int noseen = 1, string adverb = "")
{

    string code = "";
    string emotion_name;

    emotion_name = who->query_prop(EMOTION_EMOTE_CMD);

    // function comment:
    code += "// emotion:      " + emotion_name + "\n";
    code += "// suggested by: " + who->query_name() + " on " + ctime(time()) + "\n";

    // function header:
    code += "int emote_" + emotion_name + " (string arg)\n";

    // function body:
    code += "{\n";

    // the simplest possible emotion: no adverb, no target
    if(!strlen(adverb))
    {

    code += "    if(strlen(arg))\n";
    code += "       {\n";
    code += "        notify_fail(\"Blink what?\n\");\n";
    code += "        return 0;\n";
    code += "        }\n";

    code += "    write(\"You blink.\\n\");\n";
    code += "    allbb(\" blinks.\");\n";
    code += "    SOULDESC(\"blinking\");\n";
    code += "    return 1;\n";

    }
    else
    {

    /*********************************************************************
     * Example code for an emotion with no target and an adverb:


int brood(string str)
{
    str = check_adverb_with_space(str, "deeply");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Brood how?\n");
	return 0;
    }

    TP->emote_adjust_union_virtue(US_DIGNITY, 2);

    write("You brood" + str + " over the matter at hand.\n");
    allbb(" broods" + str + " over some matter.");
    SOULDESC("brooding");
    return 1;
}


    ********************************************************************/


    }

    code += "\\n}\n";

    return code;
}




varargs string
create_emotion_code_livingtarget(object who = this_player(), int noseen = 1, string adverb = "")
{

}

varargs string
create_emotion_code_objecttarget(object who = this_player(), int noseen = 1, string adverb = "")
{

}



