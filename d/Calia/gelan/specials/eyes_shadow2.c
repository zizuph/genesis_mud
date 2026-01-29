
/* 
    This is the Gelan eye shadow, which saves and presents eye
    information about the player. Eyes are based on ideas and 
    descriptions by Prokop. Eyes are "sold" by the Gelan 
    hairdresser Bigoudi Angora. 

    Coded by Maniac, 18/6/96. 
 
    History: 
    Compatibility with guild eye shadows added, Maniac, 13/7/96
    gelan unique eyes id function added, Maniac, 8/11/97
    Support for one-eyed players added, Maniac, 15/7/98
    Made more robust when configuring eyes, Maniac, 31/10/98
    Compatibility with "double" emote sould added, Maniac, 22/7/01
 */

inherit "/std/shadow";
#include <stdproperties.h>
#include <macros.h>
#include "specials.h"
#include "eyes.h"
#include "/d/Genesis/cmd/emotes.h"

#define EYES_MASTER (GELAN_ROOMS + "hairdresser") 


/* 
 * Emote array, for compatibility with double emote soul. 
 */ 
static string *eye_emote_verbs = 
         ({ "eyeblink", "eyebli", "eyecry", "eyedeath", "eyedea", "eyegaze", 
             "eyegaz", "eyeglare", "eyegla", "eyehid", "eyehide", 
             "eyeloo", "eyelook", "eyelower", "eyelow", "eyepeer", 
             "eyepee", "eyepok", "eyepoke", "eyepop", "eyeroll", 
             "eyerol", "eyerub", "eyestare", "eyesta", "eyesparkle", 
             "eyespa", "eyetwinkle", "eyetwi", "eyeshut", "eyeshu", 
             "eyewater", "eyewat", "eyewink", "eyewin" }); 

int num; 
string edesc, colour, type; 


object
query_gelan_eyes_shadow()
{
    return this_object();
}


void
set_eyes(string str)
{
    edesc = str; 
}


string
query_eyes()
{
    string e;
 
    if (stringp(e = shadow_who->query_eyes())) 
        return e; 

    return edesc;
}


void
set_eyes_colour(string c)
{
    colour = c;
}


string
query_eyes_colour()
{
    string c; 

    if (stringp(c = shadow_who->query_eyes_colour())) 
        return c;

    return colour;
}


void
set_eyes_type(string t)
{
    type = t;
}


string 
query_eyes_type()
{
    string t; 

    if (stringp(t = shadow_who->query_eyes_type())) 
        return t;

    return type;
}


/* Set the number of eyes that the player has, could be one */ 
void
set_eyes_number(int n)
{
    num = n; 
}


int
query_eyes_number()
{
    return num; 
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != EYES_SUBLOC || stringp(shadow_who->query_eyes())) 
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        str = "You have";
    else
        str = (capitalize(me->query_pronoun()) + " has");

    return (str + (num == 1 ? " one " : " ") + query_eyes() + 
                  (num == 1 ? " eye" : " eyes") + ".\n");
}


/* Use instead of remove_object() */
void
destruct_eyes_shadow()
{
    if (member_array(EYES_CMDSOUL, shadow_who->query_cmdsoul_list()) > -1) 
    {
        shadow_who->remove_cmdsoul(EYES_CMDSOUL);
        shadow_who->update_hooks();
    }
    if (!stringp(shadow_who->query_eyes())) 
        shadow_who->remove_subloc(EYES_SUBLOC); 
    destruct();
}


/* Get rid of eyes autoshadow from player and destruct shadow */ 
void
shadow_autoshadow_destruct()
{
    shadow_who->remove_autoshadow(EYES_SHADOW);
    destruct_eyes_shadow(); 
}


/* Add the cmdsoul to the player */ 
void
add_eyes_commands()
{
    shadow_who->add_cmdsoul(EYES_CMDSOUL);
    shadow_who->update_hooks();
}


void
add_eyes_subloc()
{
    shadow_who->add_subloc(EYES_SUBLOC, this_object()); 
}


private void
configure_eyes(string t, string c, string n)
{
    seteuid(getuid()); 
    type = EYES_MASTER->query_eye_type(t);
    colour = EYES_MASTER->query_eye_colour(c);

    if (!stringp(colour) || !stringp(type)) 
    {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    if (stringp(n)) 
    { 
        sscanf(n, "%d", num); 
        if (num < 1 || num > 2) 
            num = 2; 
    } 
    else 
        num = 2; 

    set_eyes(type + " " + colour); 
    add_eyes_subloc(); 
    add_eyes_commands(); 
}


public void
autoload_shadow(mixed arg)
{
    string *args, n;

    ::autoload_shadow(arg);
    args = explode(arg, ",");

    if (!args || sizeof(args) < 2) 
    {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    if (sizeof(args) == 3)
        n = args[2]; 
    else
        n = 0; 

    set_alarm(0.0, 0.0, &configure_eyes(args[0], args[1], n)); 
}


public varargs int 
shadow_me(mixed to_shadow)
{
    int r;

    if (r = ::shadow_me(to_shadow)) 
        add_eyes_subloc(); 

    return r;
}


/* 
 * Function:     query_double_emote_verbs 
 * Description:  Should return an array of double emote verbs 
 *               including those made possible by this shadow. 
 * Returns:      string *  -  possible double emote verbs. 
 */ 
string *
query_double_emote_verbs()
{
    string *other_evs; 

    other_evs = shadow_who->query_double_emote_verbs(); 

    if (!pointerp(other_evs)) 
       other_evs = ({ }); 

    return ( eye_emote_verbs + other_evs ); 
}


/* 
 * Function:     is_double_emote_verb 
 * Description:  Should return whether the specified verb is a double 
 *               emote compatible verb. 
 * Returns:      int - 1 if the verb is a double emote verb, 0 otherwise. 
 */ 
int 
is_double_emote_verb(string verb) 
{ 
    if (member_array(verb, eye_emote_verbs) > -1) 
        return 1; 

    return shadow_who->is_double_emote_verb(verb); 
} 


/* 
 * Function:      get_emote_details 
 * Description:   This allows eye emotes to work with the "double" 
 *                emote soul. Given a verb e.g. "eyetwinkle" it 
 *                should return the results of the parsed emote in 
 *                the standard form of the double emote soul. 
 * Arguments:     string verb - the verb.  
 *                string arg  - the argument of the verb. 
 *                object trg  - target of 1st double emote if this is 
 *                              the 2nd. 
 * Returns:       mixed - an emote record containing seven elements: 
 *                          the actor object 
 *                          the target object 
 *                          the adverb 
 *                          whether emote is still noticed if actor unseen 
 *                          the emote sentence, an array 
 *                          the verb e.g. "grin" 
 *                          the ending i.e. "!" or "." 
 *                0 returned means there was no such emote. 
 */ 
varargs mixed 
get_emote_details(string verb, string arg, object trg) 
{
    switch (verb) 
    { 
        case "eyeblink" : 
        case "eyebli" : 
            return call_other(EYES_CMDSOUL, "eyeblink", arg, 1, trg); 
            break; 

        case "eyecry" : 
            return call_other(EYES_CMDSOUL, "eyecry", arg, 1, trg); 
            break; 

        case "eyedeath" : 
        case "eyedea" : 
            return call_other(EYES_CMDSOUL, "eyedeath", arg, 1, trg); 
            break; 

        case "eyegaze" : 
        case "eyegaz" : 
            return call_other(EYES_CMDSOUL, "eyegaze", arg, 1, trg); 
            break; 

        case "eyegla" : 
        case "eyeglare" : 
            return call_other(EYES_CMDSOUL, "eyeglare", arg, 1, trg); 
            break; 

        case "eyehid" : 
        case "eyehide" : 
            return call_other(EYES_CMDSOUL, "eyehide", arg, 1, trg); 
            break; 

        case "eyeloo" : 
        case "eyelook" : 
            return call_other(EYES_CMDSOUL, "eyelook", arg, 1, trg); 
            break; 

        case "eyelow" : 
        case "eyelower" : 
            return call_other(EYES_CMDSOUL, "eyelower", arg, 1, trg); 
            break; 

        case "eyepee" : 
        case "eyepeer" : 
            return call_other(EYES_CMDSOUL, "eyepeer", arg, 1, trg); 
            break; 

        case "eyepok" : 
        case "eyepoke" : 
            return call_other(EYES_CMDSOUL, "eyepoke", arg, 1, trg); 
            break; 

        case "eyepop" : 
            return call_other(EYES_CMDSOUL, "eyepop", arg, 1, trg); 
            break; 

        case "eyerol" : 
        case "eyeroll" : 
            return call_other(EYES_CMDSOUL, "eyeroll", arg, 1, trg); 
            break; 

        case "eyerub" : 
            return call_other(EYES_CMDSOUL, "eyerub", arg, 1, trg); 
            break; 

        case "eyesta" : 
        case "eyestare" : 
            return call_other(EYES_CMDSOUL, "eyestare", arg, 1, trg); 
            break; 

        case "eyespa" : 
        case "eyesparkle" : 
            return call_other(EYES_CMDSOUL, "eyesparkle", arg, 1, trg); 
            break; 

        case "eyetwi" : 
        case "eyetwinkle" : 
            return call_other(EYES_CMDSOUL, "eyetwinkle", arg, 1, trg); 
            break; 

        case "eyeshu" : 
        case "eyeshut" : 
            return call_other(EYES_CMDSOUL, "eyeshut", arg, 1, trg); 
            break; 

        case "eyewat" : 
        case "eyewater" : 
            return call_other(EYES_CMDSOUL, "eyewater", arg, 1, trg); 
            break; 

        case "eyewin" : 
        case "eyewink" : 
            return call_other(EYES_CMDSOUL, "eyewink", arg, 1, trg); 
            break; 
    } 
    return shadow_who->get_emote_details(verb, arg, trg); 
}
