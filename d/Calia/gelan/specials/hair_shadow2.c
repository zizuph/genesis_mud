
/* 
    this is the Gelan hair shadow

    coder(s):   Maniac and Glykron 

    history:    28/7/01     compatibility with "double" 
                            emote soul added                 Maniac 
                31/10/98    updated to be more robust        Maniac 
                30/5/97     updated to save memory           Maniac 
                11.7.95     error traps and cmdsoul added    Maniac 
                13.9.94     destruct_shadow defined; calling 
                            remove_object in shadow removed 
                            player!                          Maniac 
                13.9.94     autoloading added                Maniac 
                18. 4.93    header added                     Glykron 

    purpose:    to allow a player to have hair via a subloc

    to do:      none
    bug:        none known
*/

inherit "/std/shadow";
#include <stdproperties.h>
#include <macros.h>
#include "specials.h"
#define HAIR_MASTER (GELAN_ROOMS + "hairdresser")

#define HAIRSTYLE_SUBLOC "hairstyle"
#define HAIRSTYLE_SHADOW (GELAN_SPECIALS + "hair_shadow")
#define HAIRSTYLE_CMDSOUL (GELAN_SPECIALS + "hair_cmdsoul")


/* 
 * Emote array, for compatibility with double emote soul. 
 */ 
static string *hair_emote_verbs = 
         ({ "hbrush", "hflutter", "hpull", "hrip", "hruffle", "hrun", 
            "hstand", "hstroke", "hthrash", "htoss", "htrim", "htwist", 
            "hwash" }); 

string hairstyle, length, colour, style;


void
set_hairstyle(string style)
{
    hairstyle = style;
}


string
query_hairstyle()
{
    return hairstyle;
}


void
set_hair_length(string l)
{
    length = l;
}


string
query_hair_length()
{
    return length;
}


void
set_hair_colour(string c)
{
    colour = c;
}


string 
query_hair_colour()
{
    return colour;
}


void
set_hair_style(string s)
{
    style = s;
}


string
query_hair_style()
{
    return style;
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

    if (subloc != HAIRSTYLE_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        str = "Your";
    else
        str = capitalize(me->query_possessive());

    return str + " hair is " + hairstyle + ".\n";
}


/* Use instead of remove_object() */
void
destruct_hair_shadow()
{
    if (member_array(HAIRSTYLE_CMDSOUL, 
                     shadow_who->query_cmdsoul_list()) > -1) 
    {
        shadow_who->remove_cmdsoul(HAIRSTYLE_CMDSOUL);
        shadow_who->update_hooks();
    }
    destruct();
}


/* Get rid of hairstyle autoshadow from player and destruct shadow */ 
void
shadow_autoshadow_destruct()
{
    shadow_who->remove_autoshadow(HAIRSTYLE_SHADOW);
    destruct_hair_shadow(); 
}


/* Add the cmdsoul to the player */
void
add_hair_commands()
{
    shadow_who->add_cmdsoul(HAIRSTYLE_CMDSOUL);
    shadow_who->update_hooks();
}


private void
configure_hair(string l, string c, string s)
{
    setuid(); 
    seteuid(getuid()); 
    length = HAIR_MASTER->query_hair_length(l);
    colour = HAIR_MASTER->query_hair_colour(c);
    style = HAIR_MASTER->query_hair_style(s);
    if ((!stringp(length)) || (!stringp(colour)) | (!stringp(style)))  
    {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    hairstyle = length + ", " + colour + " and " + style; 
    shadow_who->add_subloc(HAIRSTYLE_SUBLOC, this_object()); 
    add_hair_commands(); 
}


public void
autoload_shadow(mixed arg)
{
    string *args;

    ::autoload_shadow(arg);
    args = explode(arg, ",");

    if (!pointerp(args) || sizeof(args) != 3) 
    {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    set_alarm(0.1, 0.0, &configure_hair(args[0], args[1], args[2])); 
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
        return hair_emote_verbs; 

    return ( hair_emote_verbs + other_evs ); 
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
    if (member_array(verb, hair_emote_verbs) > -1) 
        return 1; 

    return shadow_who->is_double_emote_verb(verb); 
} 


/* 
 * Function:      get_emote_details 
 * Description:   This allows hair emotes to work with the "double" 
 *                emote soul. Given a verb e.g. "hpull" it 
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
 *                          the verb e.g. "hpull" 
 *                          the ending i.e. "!" or "." 
 *                0 returned means there was no such emote. 
 */ 
varargs mixed 
get_emote_details(string verb, string arg, object trg) 
{ 
    if (member_array(verb, hair_emote_verbs) > -1) 
        return call_other(HAIRSTYLE_CMDSOUL, verb, arg, 1, trg); 

    return shadow_who->get_emote_details(verb, arg, trg); 
} 
