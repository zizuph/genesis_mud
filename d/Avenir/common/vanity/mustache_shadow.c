// /d/Avenir/common/vanity/mustache_shadow.c
// Created by Lilith, March 2022
//      Borrowed heavily from the Gelan hairstyle 
//      code by Maniac and Glykron for consistency 
//      of player experience. 

inherit "/std/shadow";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Avenir/common/vanity/vanity.h"

#define BARBERSHOP (VANITY + "barber_shop")

#define MUSTACHE_SHADOW    VANITY +"mustache_shadow"
#define MUSTACHE_SOUL      VANITY +"mustache_cmdsoul"
#define MUSTACHE_SUBLOC    "vanity_mustache"

/* 
 * Emote array, for compatibility with double emote soul. 
 */ 
static string *mustache_emote_verbs = 
         ({ "mbrush", "mclean", "mgroom", "mpluck", "mrun", "mscratch", 
            "mstroke", "mtrim", "mtug", "mtwirl", "mwash" }); 

string mustachestyle, mstyle, mustache, length, colour, style;


void
set_mustachestyle(string mstyle)
{
    mustachestyle = mstyle;
}

string
query_mustachestyle()
{
    return mustachestyle;
}

void
set_mustache_colour(string c)
{
    colour = c;
}

string 
query_mustache_colour()
{
    return colour;
}

void
set_mustache_length(string l)
{
    length = l;
}

string
query_mustache_length()
{
    return length;
}

void
set_mustache_style(string s)
{
    style = s;
}

string
query_mustache_style()
{
    return style;
}

void
set_mustache(string style)
{
    mustache = length +" "+ colour +" "+ style;
} 

string
query_mustache()
{
    return mustache;
}



/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		          me      - I
 *		          for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != MUSTACHE_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        str = "You have a";
    else
        str = capitalize(me->query_pronoun()) +" has a";

    return str +" "+ mustachestyle +".\n";
}


/* Use instead of remove_object() */
void
destruct_mustache_shadow()
{
    if (member_array(MUSTACHE_SOUL, 
        shadow_who->query_cmdsoul_list()) > -1) 
    {
        shadow_who->remove_cmdsoul(MUSTACHE_SOUL);
        shadow_who->update_hooks();
    }
    destruct();
}


/* Get rid of mustache autoshadow from player and destruct shadow */ 
void
shadow_autoshadow_destruct()
{
    shadow_who->remove_autoshadow(MUSTACHE_SHADOW);
    destruct_mustache_shadow(); 
}


/* Add the cmdsoul to the player */
void
add_mustache_commands()
{
    shadow_who->add_cmdsoul(MUSTACHE_SOUL);
    shadow_who->update_hooks();
}


private void
configure_mustache(string l, string c, string s)
{
    setuid(); 
    seteuid(getuid()); 
    length = BARBERSHOP->query_f_hair_length(l);
    colour = BARBERSHOP->query_f_hair_colour(c);
    style = BARBERSHOP->query_mustache_style(s);
    if ((!stringp(length)) || (!stringp(colour)) | (!stringp(style)))  
    {
        set_alarm(1.0, 0.0, shadow_autoshadow_destruct);
        return;
    }

    mustache = length + " " + colour + " " + style; 
    mustachestyle = length + " " + colour + " " + style; 
    shadow_who->add_subloc(MUSTACHE_SUBLOC, this_object()); 
    add_mustache_commands(); 
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

    set_alarm(0.1, 0.0, &configure_mustache(args[0], args[1], args[2])); 
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
        return mustache_emote_verbs; 

    return ( mustache_emote_verbs + other_evs ); 
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
    if (member_array(verb, mustache_emote_verbs) > -1) 
        return 1; 

    return shadow_who->is_double_emote_verb(verb); 
} 


/* 
 * Function:      get_emote_details 
 * Description:   This allows mustache emotes to work with the "double" 
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
    if (member_array(verb, mustache_emote_verbs) > -1) 
        return call_other(MUSTACHE_SOUL, verb, arg, 1, trg); 

    return shadow_who->get_emote_details(verb, arg, trg); 
} 
