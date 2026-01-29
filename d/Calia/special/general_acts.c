
/* 
     General kroug acts. 
     Coded by Maniac for kroug brain. 

     History: 

     1996/1997/1998/1999/2000/2001       updates            Maniac 
     16/7/01       separated as inherit for kroug brain     Maniac 
     4/5/02        added more chats                         Maniac
*/ 

#include <macros.h>
#include "defs.h"
#include CALIA_DOMAIN_DEFS
#include CALIA_FILE_DEFS
#include CALIA_KROUG_DEFS


int general_act_count; 

int *general_acts_left; 


/* 
 * Function:     set_general_act_count 
 * Description:  Set the number of general acts. 
 * Arguments:    int act_count     - the number of general acts.  
 */ 
private void 
set_general_act_count(int act_count) 
{ 
    general_act_count = act_count; 
} 


/* 
 * Function:     reset_general_acts 
 * Description:  Reset the general acts. 
 *               This sets up a list of indices for the acts in an array. 
 * Returns:      int * - the reset array of indices. 
 */ 
int * 
reset_general_acts()
{
    int i; 

    general_acts_left = ({ }); 

    for (i = 0; i < general_act_count; i++) 
        general_acts_left += ({ i }); 

    return general_acts_left; 
}


/* 
 * Function:     next_random_general_act_index 
 * Description:  Gets a random index for the remaining general acts, 
 *               and removes it. 
 * Returns:      int - the got index 
 */ 
int
next_random_general_act_index()
{
    int i, ix; 

    if (!general_acts_left || !sizeof(general_acts_left)) 
    { 
        reset_general_acts(); 
    } 

    ix = general_acts_left[i = random(sizeof(general_acts_left))]; 
    general_acts_left = exclude_array(general_acts_left, i, i); 

    return ix; 
}



/* 
 * Function:      init_general_acts 
 * Description:   Initialises the number of general acts and resets 
 *                them. 
 */ 
void
init_general_acts()
{
    set_general_act_count(30); 
    reset_general_acts(); 
}


string
query_general_act(int index, object kroug, object player)
{
     string pn; 

     pn = OB_NAME(player); 

     switch (index) 
     { 
         case 0 : 
             return ("snarl " + pn); 
             break; 
         case 1 : 
             return ("spit " + pn); 
             break; 
         case 2 : 
             return ("puke " + pn); 
             break; 
         case 3 : 
             return ("slap " + pn); 
             break; 
         case 4 : 
             return ("glare " + pn); 
             break; 
         case 5 : 
             return 
                 ("say It really is about time we " + 
                 "re-conquered this country."); 
             break; 
         case 6 : 
             return 
                 ("say I'd like to ransack the palace, " + 
                 "the decor in there is shocking."); 
             break; 
         case 7 : 
             return ("kick " + pn); 
             break; 
         case 8 : 
             return 
                 ("emote gloats like an expectant vulture."); 
             break; 
         case 9 : 
             return 
                 ("emote glares at you with a psychotic " + 
                 "look in its soulless eyes."); 
             break; 
         case 10 : 
             return 
                 ("emote surveys you with a look of perplexed disgust."); 
             break; 
         case 11 : 
             return 
                 ("emote lets out a loud, fierce and hateful battle cry!"); 
             break; 
         case 12 : 
             return ("emote jeers disdainfully."); 
             break; 
         case 13 : 
             return 
                 ("emote curses Caliana colourfully, " + 
                  "pauses for thought and curses her again."); 
             break; 
         case 14 : 
             return 
                ("say Calian blood tastes like dry " + 
                 "wine, especially those full bodied " + 
                 "vintages from their elite guards."); 
             break; 
         case 15 : 
             return 
                ("emote takes a deep breath and screams " + 
                "a barrage of obscenities at you!"); 
             break; 
         case 16 : 
             return 
                 ("say Decapitation with a rusty scimitar, " + 
                 "that's _way_ too lenient."); 
             break; 
         case 17 : 
             return "emote looks around suspiciously."; 
             break; 
         case 18 : 
             return
                 ("emote sarcastically blurts a colourful " + 
                 "stream of dubious accusations at you!"); 
             break; 
         case 19 : 
             return 
                 ("say I never expected you to survive this long, " + 
                 kroug->query_kroug_address_player(player) + "!"); 
             break; 
         case 20 : 
             return 
                 ("say What a subversive character you are " + 
                 kroug->query_kroug_address_player(player) + ", " + 
                 "giving us no alternative but to kill " + 
                 "you. Sheesh!"); 
             break; 
         case 21 : 
             return 
                 ("emote screams praise to the spirit of never-ending strife!"); 
             break; 
         case 22 : 
             return 
                 ("say I dedicate this next corpse to those " + 
                  "who are completely faithful and unrepentant about it!"); 
             break; 
         case 23 : 
             return 
                 ("say I'd ask you to remove that foolish " + 
                 "expression, but it's already found a perfect home!"); 
             break; 
         case 24 : 
             return ("say Hey you were almost fighting there for a second!"); 
             break; 
         case 25 : 
             return ("emote nominates you for an outstanding idiocy award."); 
             break; 
         case 26 : 
             return ("knee " + pn); 
             break; 
         case 27 : 
             return ("say That goon-infested palace is coming down " + 
                     "in a heap of cheap masonry next time we pay " +
                     "a visit."); 
             break; 
         case 28 : 
             return ("emote doesn't look in the least bit doubtful."); 
             break; 
         default: 
             return ("scowl " + pn); 
             break; 
     }
}



/* Kroug does a general act, maybe to a particular player */
void
general_act(object kroug, object player)
{
    if ((!objectp(kroug)) || (!objectp(player)))
        return;

    kroug->command(query_general_act(
                       next_random_general_act_index(), 
                       kroug, player)); 
}

