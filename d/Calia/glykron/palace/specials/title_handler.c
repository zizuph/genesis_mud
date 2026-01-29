
/* 
   Title handling code for the Calian guild. 
   Allows Calians some actual choice in choosing a _second_ alternative
   title to the standard guild title. Calians may choose unique composite 
   noun titles like "Crystalblade", "Whitesword", from a range of possible
   beginning and ending elements that are somewhat Calian in nature. Titles 
   may not be changed often: a period of at least two weeks must elapse 
   before one may change one's special title again. This is to ensure that 
   people are not capricious with them.

   Coded by Maniac, 23/12/95
   Revised, 1/6/96, Maniac 
   Revised, 15/7/96, Maniac
   Revised, 14/3/97, Maniac
   Revised, 4/2/98, Maniac
*/

#pragma save_binary
#include <composite.h>
#include <std.h>
#include <const.h>
#include "defs.h"
#define MIN_DURATION_BETWEEN_TITLE_SET 1209600    /* two weeks */


/* possible to have second adjective exclusions in these */ 
static mapping 
     mte1 = 
  ([ 
    "bright" :  ({ "blade" }), 
    "crystal" : ({ "spirit" }), 
    "dark" : ({ "heart" }), 
    "fire" : ({ }), 
    "flame" : ({ }), 
    "frost" : ({ "son", "daughter" }), 
    "golden" : ({ "strike", "spirit" }), 
    "grey" : ({ "strike", "spirit" }), 
    "grim" : ({ "mane", "flower" }), 
    "ice" : ({ "son", "daughter" }), 
    "marble" : ({ "strike", "spirit", "son", "daughter" }), 
    "mist" : ({ "sting", "strike" }), 
    "moon" : ({ "sting", "mane", "star", "strike" }), 
    "night" : ({ "strike", "sting" }), 
    "rainbow" : ({ "son", "daughter", "spirit", "strike" }), 
    "silver" : ({ "blade", "spirit" }),  
    "sea" : ({ "claw", "blade", "sword", "spear", "thorn","sting", "strike" }), 
    "sky" : ({ "strike" }), 
    "snow" : ({ "son", "daughter", "strike", "sword", 
                "blade", "claw", "spear" }),
    "steel" : ({ "spirit" }), 
    "stone" : ({ "star" }), 
    "sun" : ({ "star", "son", "daughter", "flower", "strike" }), 
    "white" : ({ "spirit", "son", "daughter" }), 
    "black" : ({ "spirit", "son", "daughter", "maiden", 
                 "heart", "lady", "flower" }), 
    ]);

/* possible to have gender exclusions in these */ 
static mapping 
      mte2 = ([ "blade" : ({ }), 
               "claw" : ({ }),
               "daughter" : ({ G_MALE, G_NEUTER }),
               "flower" : ({ }),
               "heart" : ({ }),
               "lady" : ({ G_MALE, G_NEUTER }), 
               "mane" : ({ }), 
               "maiden" : ({ G_MALE, G_NEUTER }),  
               "son" : ({ G_FEMALE, G_NEUTER }), 
               "sword" : ({ }),
               "spear" : ({ }), 
               "spirit" : ({ }), 
               "star" : ({ }), 
               "strike" : ({ }), 
               "sting" : ({ }), 
               "thorn" : ({ }), 
               "warrior" : ({ }), 
               "wolf" : ({ }), ]);

mapping calian_special_title = ([ ]);

static string *ind = ({ });
static string *te1 = ({ }); 
static string *te2 = ({ }); 

static int curr_check = 0;


/* title_check called by alarm from create */
void
title_check()
{
    int i, j;
   
    j = curr_check + 20;
    if (j > sizeof(ind))
        j = sizeof(ind);

    for (i = curr_check; i < j; i++) 
        if (!SECURITY->exist_player(lower_case(ind[i])))
            this_object()->remove_calian_special_title(ind[i]);

    if (j == sizeof(ind))
        return;

    curr_check = j;
    set_alarm(5.0, 0.0, title_check);
}


/* Restore the Calian special titles and get rid of any titles of 
   players who no longer exist. */
void
create()
{
    int i;

    setuid();
    seteuid(getuid());
    restore_object(GLYKRON_TEXTS+"calian_title_save");

    ind = m_indexes(calian_special_title);

    te1 = sort_array(m_indexes(mte1)); 
    te2 = sort_array(m_indexes(mte2)); 

    set_alarm(5.0, 0.0, title_check);
}




/* Return description of possible title elements */
string 
query_el_desc()
{
    return ("Set 1: " + COMPOSITE_WORDS(te1) + ".\n" +
            "Set 2: " + COMPOSITE_WORDS(te2) + ".\n");
}



/* Query whether a title is a valid one. */
int
query_valid_title(string s1, string s2)
{
    mixed e1, e2; 
    int i;

    if (!stringp(s1) || !stringp(s2)) 
        return 0;

    e1 = mte1[s1]; 
    e2 = mte2[s2]; 

    if (!e1 || !e2) 
        return 0;

    /* Check the adjectives are a valid combination */ 
    if (member_array(s2, e1) > -1) 
        return 0;

    /* Check the gender is correct  */ 
    for (i = 0; i < sizeof(e2); i++)  
        if (this_player()->query_gender() == e2[i])  
            return 0; 

    return 1;
}


/* Query whether a title has already been taken by another Calian */
int
query_title_taken(string s1, string s2)
{
    int i;
    mixed v;

    s1 = lower_case(s1);
    s2 = lower_case(s2);
    v = m_indexes(calian_special_title);
    for (i = 0; i < sizeof(v); i++)
        if ((calian_special_title[(v[i])][0] == s1) && 
            (calian_special_title[(v[i])][1] == s2))  { 
            if (SECURITY->query_wiz_level(v[i])) 
                /* wizards needn't of course have a special title */
                this_object()->remove_calian_special_title(v[i]);
            else
                return 1;
        }
    return 0;
}


/* 
 * Return special title elements for a particular Calian, 
 * e.g. ({ "crystal", "sword", Time })  
 */ 
mixed
query_calian_title_el(string name)
{
    name = capitalize(lower_case(name)); 

    return calian_special_title[name];  
}


/* 
   Remove a Calian special title, usually carried out when a Calian  
   leaves the guild. 
*/
int
remove_calian_special_title(string name)
{
    name = capitalize(lower_case(name));
    calian_special_title = m_delete(calian_special_title, name);
    save_object(GLYKRON_TEXTS+"calian_title_save");
    return 1;
}


/* Set the special title for a given Calian */
int
set_calian_special_title(string name, string s1, string s2)
{
    name = capitalize(lower_case(name));
    s1 = lower_case(s1);
    s2 = lower_case(s2);
    calian_special_title = m_delete(calian_special_title, name);
    calian_special_title += ([ name : ({s1, s2, time() }) ]); 
    save_object(GLYKRON_TEXTS+"calian_title_save");
    find_player(lower_case(name))->setup_calian_special_title(); 
    return 1;
}

/* Query whether a enough time has elapsed (since the last title setting
   of the given player) for a Calian to set his/her special title. */
int
query_time_to_set_title(string name)
{
    mixed e;

    name = capitalize(lower_case(name));
    e = calian_special_title[name];

    if (!e) 
        return 1;

    if ((time() - e[2]) < MIN_DURATION_BETWEEN_TITLE_SET) 
        return 0;

    return 1;
}

