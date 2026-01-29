
/* 
     Kroug acts between groups. Coded by Maniac for kroug brain. 

     History: 

     1996/1997/1998/1999/2000/2001  updates        Maniac 
     19/7/2001   changed to inheritable file       Maniac 
*/ 

#include <macros.h>
#include "defs.h"
#include CALIA_DOMAIN_DEFS
#include CALIA_FILE_DEFS
#include CALIA_KROUG_DEFS

/* 
 * Defines for inter-group act types, which index the global 
 * variables inter_group_act_count and inter_group_acts_left. 
 */ 
#define ONE_ONE 0
#define ONE_MANY 1
#define MANY_ONE 2
#define MINO_MAJO 3
#define MAJO_MINO 4
#define MANY_MANY 5

int *inter_group_act_count = ({ 0, 0, 0, 0, 0, 0 }); 
mixed inter_group_acts_left = 
          ({ ({ }), ({ }), ({ }), ({ }), ({ }), ({ }) }); 


/* 
 * Function:     set_inter_group_act_count 
 * Description:  Set the number of acts for a particular act type. 
 * Arguments:    int act_type      - the act type 
 *               int act_count     - the number of acts 
 */ 
private void 
set_inter_group_act_count(int act_type, int act_count) 
{ 
    inter_group_act_count[act_type] = act_count; 
} 


/* 
 * Function:     reset_inter_group_acts 
 * Description:  Reset the inter-group acts for a particular act type. 
 *               This sets up a list of indices for the acts in an array, 
 *               which is identified by the act type in the global two 
 *               dimensional array inter_group_acts_left. 
 * Arguments:    int act_type  -  the act type. 
 * Returns:      int * - the reset array of indices. 
 */ 
int * 
reset_inter_group_acts(int act_type) 
{ 
    int i, lim, *tmp; 

    lim = inter_group_act_count[act_type]; 
    tmp = ({ }); 

    for (i = 0; i < lim; i++) 
        tmp += ({ i }); 

    return (inter_group_acts_left[act_type] = tmp); 
} 


/* 
 * Function:     next_random_occ_act_index 
 * Description:  Gets a random index for the remaining inter group acts 
 *               of the specified act type, and removes it. 
 * Arguments:    int act_type - the act type. 
 * Returns:      int - the got index 
 */ 
int
next_random_inter_group_act_index(int act_type)
{
    int *tmp, i, ix; 

    if (!(tmp = inter_group_acts_left[act_type]) || 
        !sizeof(tmp)) 
    { 
        tmp = reset_inter_group_acts(act_type); 
    } 

    ix = tmp[i = random(sizeof(tmp))]; 
    inter_group_acts_left[act_type] = exclude_array(tmp, i, i); 

    return ix; 
}


/* 
 * Function:      init_inter_group_acts 
 * Description:   Initialises the number of inter-group acts 
 *                for each act type, and resets them. 
 */ 
void 
init_inter_group_acts() 
{ 
    set_inter_group_act_count(ONE_ONE, 4); 
    reset_inter_group_acts(ONE_ONE); 
    set_inter_group_act_count(ONE_MANY, 5); 
    reset_inter_group_acts(ONE_MANY); 
    set_inter_group_act_count(MANY_ONE, 5); 
    reset_inter_group_acts(MANY_ONE); 
    set_inter_group_act_count(MINO_MAJO, 5); 
    reset_inter_group_acts(MINO_MAJO); 
    set_inter_group_act_count(MAJO_MINO, 9); 
    reset_inter_group_acts(MAJO_MINO); 
    set_inter_group_act_count(MANY_MANY, 6); 
    reset_inter_group_acts(MANY_MANY); 
} 


string 
query_inter_group_act(int act_type, int index, object kroug, object *players)
{
    switch (act_type) 
    { 
        case ONE_ONE : 
            switch (index) 
            {
                case 0 : 
                    return "say So it comes down to just you and me, eh?"; 
                    break;
                case 1 : 
                    return 
                        ("say Don't get any illusions about who's going " + 
                         "to win this duel!"); 
                    break; 
                case 2 : 
                    return "emote grins in determined fashion.";  
                    break; 
                default : 
                    return "say I'm at my best one on one!"; 
                    break; 
            } 
            break; 
        case ONE_MANY : 
            switch (index) 
            { 
                case 0 : 
                    return "say I can take all of you out by myself!"; 
                    break; 
                case 1 : 
                    return "say Hah, all against one eh?"; 
                    break; 
                case 2 : 
                    return "say Your luck just ran out!"; 
                    break; 
                case 3 : 
                    return "emote grins desperately."; 
                    break; 
                default : 
                   return 
                       ("say So, it's just me then! You'll never " + 
                        "take me alive!"); 
                   break; 
            } 
            break; 
        case MANY_ONE : 
            switch (index) 
            { 
                case 0 : 
                    return "say Hah! Alone, eh? Obviously a hero!"; 
                    break; 
                case 1 : 
                    return "say Fancy yourself as a lone wolf do you?"; 
                    break; 
                case 2 : 
                    return 
                       ("say You're just one overconfident fool " + 
                        "against many warriors!"); 
                    break; 
                case 3 : 
                    return "emote cackles confidently."; 
                    break; 
                default : 
                    return "say We'll tear you apart, loner!"; 
                    break; 
            } 
            break; 
        case MINO_MAJO : 
            switch (index) 
            {
                case 0 : 
                    return 
                        "say You outnumber us, but we'll crush you!"; 
                    break; 
                case 1 : 
                    return 
                        ("say Think you " + LANG_WNUM(sizeof(players)) + 
                         " can take us out, do you?"); 
                    break; 
                case 2 : 
                    return "say We'll wipe all of you out!"; 
                    break; 
                case 3 : 
                    return 
                       ("say You can't overwhelm us with superior numbers!");
                    break;
                default : 
                    return "emote grins in determined fashion."; 
                    break;
             } 
             break; 
        case MAJO_MINO : 
            switch (index) 
            {
                case 0 : 
                    return "say You are outnumbered and will be crushed!"; 
                    break; 
                case 1 : 
                    return 
                        ("say Think you " + LANG_WNUM(sizeof(players)) + 
                         " can take us out, do you?");
                    break;
                case 2 : 
                    return "emote cackles confidently.";
                    break;
                case 3 : 
                    return 
                        ("say Prepare to meet whatever excuse " +
                         "for a god made you, invaders!");
                         break; 
                case 4 : 
                    return 
                        ("say We'll hack up your bodies and " +
                         "throw them to the vultures!"); 
                    break; 
                case 5 : 
                    return 
                        ("say You " + LANG_WNUM(sizeof(players)) + 
                         " will die horribly!"); 
                    break; 
                case 6 :
                    return "say Filthy trespassers on our lands!";
                    break;
                case 7 : 
                    return 
                        "say We'll keep one of you alive to torture!"; 
                    break;
                default : 
                    return "emote grins confidently.";
                    break;
            } 
            break; 
        case MANY_MANY : 
            switch (index) 
            { 
                case 0 : 
                    return "say Die you bunch of muckrakers!"; 
                    break; 
                case 1 : 
                    return "say We'll tear you apart!"; 
                    break; 
                case 2 : 
                    return "emote cackles in determined fashion."; 
                    break; 
                case 3 : 
                    return 
                        ("say We'll plant your pieces in the earth " + 
                         "and grow a new idiot patch!"); 
                    break; 
                case 4 : 
                    return 
                        ("say After we wipe out these idiots " + 
                         "we can turn them into a mixed grill!"); 
                    break; 
                default : 
                    return ("emote grins in determined fashion."); 
                    break; 
            } 
            break; 
    } 
}


/* Do an act related to the combat situation */ 
void 
combat_situation_act(object kroug, object *krougs, object *players) 
{ 
    int ps, ks, act_type; 

    if (!objectp(kroug) || !(ks = sizeof(krougs)) || 
        !(ps = sizeof(players))) 
        return; 

    if (ks == 1) 
    { 
        if (ps == 1) 
            act_type = ONE_ONE; 
        else 
            act_type = ONE_MANY; 
    } 
    else 
    { 
        if (ps == ks) 
            act_type == MANY_MANY; 
        else if (ps == 1) 
            act_type = MANY_ONE; 
        else if (ks < ps) 
            act_type = MINO_MAJO; 
        else 
            act_type = MAJO_MINO; 
    } 

    kroug->command(query_inter_group_act(act_type, 
                       next_random_inter_group_act_index(act_type), 
                       kroug, players)); 
} 
