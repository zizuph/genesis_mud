
/* 
 *  Original code by Amelia. 
 *  Modifications by Maniac 9/9/96 
 * 
 *  An oyster for the mermaid quest in Calia. These may be found 
 *  by searching in the oyster_room in sector_0_0_2. 
 *  In some of these one may find a white pearl, 
 *  In one search per reset a black pearl (set from the oyster room). 
 *  One can discard these so as not to leave loads lieing around :)
 */ 

inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <language.h>
#include <cmdparse.h>

#include "defs.h"

#include SEA_QUESTS

int black = 0; 
int prised_open = 0; 


string 
oyster_long() 
{ 
    return ("An oyster with a hard grey outer shell." + 
            (environment() == this_player() ? " If " + 
            "you have no use for it you can <discard> it.\n" : 
            "\n")); 
} 


void 
create_receptacle() 
{ 
    set_name("oyster"); 
    add_name("grey oyster"); 
    add_name(MERMQ_OYSTER_ID); 
    set_adj("grey"); 
    set_short("grey oyster"); 
    set_pshort("grey oysters"); 

    set_long(oyster_long); 

    set_cf(this_object()); 

    add_prop(CONT_I_WEIGHT, 20); 
    add_prop(CONT_I_MAX_WEIGHT, 65); 
    add_prop(CONT_I_VOLUME, 35); 
    add_prop(CONT_I_MAX_VOLUME, 65); 
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(CONT_I_CLOSED, 1); 
} 


int 
edged(object wep) 
{ 
    return (wep->query_dt() & W_SLASH); 
} 


int 
discard(string str) 
{ 
    object *oys, tp; 
    string n; 

    if (!stringp(str)) { 
        notify_fail("Discard what?\n"); 
        return 0; 
    } 

    tp = this_player(); 

    oys = FIND_STR_IN_ARR(str, filter(all_inventory(tp), &->id(MERMQ_OYSTER_ID))); 

    if (!sizeof(oys))  { 
        notify_fail("Discard what?\n"); 
        return 0; 
    } 

    if (sizeof(oys) == 1) 
        n = "oyster"; 
    else 
        n = "oysters"; 

    tp->catch_msg("You crush and discard " + LANG_WNUM(sizeof(oys)) + 
                  " grey " + n + ".\n"); 
    tell_room(environment(tp), QCTNAME(tp) + " crushes and discards " + 
                 LANG_WNUM(sizeof(oys)) + " grey " + n + ".\n", tp); 

    if (sizeof(oys) > 1) 
        (oys - ({ this_object() }))->remove_object(); 
    remove_object(); 
    return 1; 
} 


/* 
 * Called when someone tries to open this receptacle 
 * You need to be wielding something bladed to open it. 
 */ 
int 
open(string str) 
{ 
    object meat, pearl, tp; 

    if (prised_open) 
        return 0; 

    tp = this_player(); 

    if (!objectp(tp)) 
        return 0; 

    if (!sizeof(filter(tp->query_weapon(-1), edged))) { 
       tell_object(tp, "The shell is hard and sealed shut. You need to " + 
                       "be wielding something bladed to open it.\n"); 
       return 3; 
    } 

    seteuid(getuid(this_object())); 

    meat = clone_object(SEA_OBJECTS+"oyster_meat");
    meat->move(this_object(), 1); 

    if (black)
        pearl = clone_object(SEA_OBJECTS + "black_pearl"); 
    else if (!random(4)) 
        pearl = clone_object(SEA_OBJECTS + "pearl"); 

    if (objectp(pearl)) 
        pearl->move(this_object(), 1); 

    tp->catch_msg("You prise open the " + short() + ".\n"); 
    tell_room(environment(tp), QCTNAME(tp) + " prises open the " + 
                               short() + ".\n", tp); 
    prised_open = 1; 
    return 1;
}


int
no_eat(string str)
{
    if (str == "oyster") 
        notify_fail("You can't eat an oyster with the shell on.\n");
    return 0;
}


int
add_black_pearl()
{
    black = 1;
}


/* 
 * We want players to discard these oysters one by one. Having lots 
 * of receptacles in one's inventory is bad for memory and also causes
 * parsing problems apparently. 
 */ 
int
do_search(string str)
{
    if (wildmatch("*oyster*", str) || 
        wildmatch("*oyster", str) || 
        wildmatch("oyster*", str) || 
        (str == "oyster")) { 
        tell_object(this_player(), 
                  "Perhaps you should discard " +
                  "the oyster you have first?\n"); 
        return 1;
    } 
    return 0;
}


void
init()
{
    ::init(); 
    add_action(do_search, "search"); 
    add_action(no_eat, "eat"); 
    add_action(discard, "discard"); 
}

