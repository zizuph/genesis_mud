
/* 
   Code included into kroug rooms to allow them to vandalise things.
   As with all code in Calia, this is Calian property, not to be copied.
   Code to be inherited into rooms to allow vandalism of various kinds.  
   This code will only make sense if you don't have too many details of
   the vandalisable items in your long descriptions. Such details
   may look inconsistent with the modifications that come with vandalism. 

   Types of vandalism, in order of severity : 
       smear - an item for which the spreading a liquid substance on its
               surface may take place, for instance graffiti on a painting. 
       scratch - an item with a fairly hard surface that can be scratched
       dent  - an item with a strong structure that may nevertheless be 
               dented
       tear - an item that may be torn, like a tapestry, or a scroll 
       break - an item that may be broken so that it will not perform its
               usual function, e.g. a chair, but not as bad as shattering.
       shatter - an item that may be shattered into small fragments. 

       Note: vandalism should only be carried out on things that are
             considered singular entities. It gets complicated when one
             tries to deal with vandalism of multiple objects at a time.
    
   To do: add a "repair" verb to allow players to pay for repairs. 

   Coded by Maniac 7/12/95 
*/


#include <macros.h>
#include <money.h>
#include <composite.h>

/* Control object, the object responsible for the added descs. 
   Need to keep the handling of the vandalism unique. */
#define GRAFFITI_OB "/d/Calia/special/graffiti_ob"

#define NPC_INTERVAL_BETWEEN_VANDALISM 5

string *poss_v_verbs = ({"smear", "scratch", "dent",  
                        "tear", "break", "shatter" });



/*  Record of the things that can possibly be vandalised in this room, 
    including the cost of repair in cc.
    Example: ([ "painting" : ({ "A painting of Maniac.\n", 
                               ({ "tear", "smear" }), 35 }) ]); */ 
mapping possible_vandalism = ([ ]);


/* Record of the things that can still be vandalised in this room */
mapping remaining_vandalism = ([ ]);


/* Record of removed items for later restoration */
mixed removed_items = ({ });

/* Record of all the descriptions of vandalism so far in this room */
mapping vandalism = ([ ]);


/* Is it possible to have artisans repair stuff here. */
int
query_can_repair_here()
{
    return 1;
}


/* Cost to repair a particular item. */
int 
query_cost_of_repair(string str)
{
    mixed e;

    if (!(e = possible_vandalism[str])) 
        return 0;

    if (pointerp(e) && (sizeof(e) >= 3))
        return e[2];
    else
        return 0;
}


/* Make it possible to vandalise an existing item in a certain way. */
int
add_item_possible_vandalism(string item_name, string basic_desc, 
                            string *damage, int cost)
{
    mixed f;

    f = damage - poss_v_verbs;
    if (sizeof(f))
        return 0;

    if (!item_id(item_name)) 
        return 0;

    if (pointerp(possible_vandalism[item_name]))
        possible_vandalism = m_delete(possible_vandalism, item_name);

    if (pointerp(remaining_vandalism[item_name]))
        remaining_vandalism = m_delete(remaining_vandalism, item_name);

    possible_vandalism += ([ item_name : ({ basic_desc, damage, cost}) ]);
    remaining_vandalism += ([ item_name : ({ basic_desc, damage, cost}) ]);
    return 1;
}


/* Return possible vandalism item details */
mapping
query_possible_vandalism()
{
    return possible_vandalism;
}


/* Return remaining possible vandalism details */
mapping
query_remaining_vandalism()
{
    return remaining_vandalism;
}


int last_npc_vandalism = 0;


/* Return possible remaining vandalism for an npc */
mapping
query_npc_remaining_vandalism()
{
    int t = time();

    if ((t - last_npc_vandalism) <= NPC_INTERVAL_BETWEEN_VANDALISM)
        return ([ ]);

    last_npc_vandalism = t;
    return remaining_vandalism;
}


string
generate_v_desc()
{
    return (implode(m_values(vandalism), " ") + "\n");
}


/* An act of vandalism takes place. */
int
living_vandalises(object l, string item_name, string action_desc,
                  string item_desc_long, string item_desc_item)
{
    string n;
    mixed ite;
    int i, done;

    if (!objectp(l)) 
        n = "Gilbert";
    else
        n = QCTNAME(l); 


    if (!remaining_vandalism[item_name])
        return 0;

    done = 0;
    for (i = 0; i < sizeof(removed_items); i++) 
       if (member_array(item_name, removed_items[i][0]) > -1)
           done = 1;  

    if (done)
        return 0;
    
    if (!item_id(item_name))
        return 0;

    ite = query_item();
 
    i = 0; 
    while (member_array(item_name, ite[i][0]) == -1)
        i++;

    /* update record of removed items */
    removed_items += ({ite[i]});
    remove_item(item_name); 
    remaining_vandalism = m_delete(remaining_vandalism, item_name);

    /* record vandalism description */
    vandalism += ([ item_name : item_desc_long ]);

    /* add the new item description */
    add_item(ite[i][0], (possible_vandalism[item_name])[0] + " " + 
                         item_desc_item + "\n");

    GRAFFITI_OB->load_me();
    change_my_desc(generate_v_desc(), find_object(GRAFFITI_OB)); 
    tell_room(this_object(), n + " " + action_desc + "\n", l);
    return 1;
}


/* Action to repair something that has been vandalised in the room */
int
do_repair(string str)
{
    mixed e;
    string *r;
    object tp = this_player();
    int c, i, n;

    if (!query_can_repair_here()) {
        notify_fail("Artisans are not available here, alas.\n");
        return 0;
    }

    r = m_indexes(vandalism);

    if (!sizeof(r)) {
        notify_fail("There is nothing to repair here, nothing is " +
                    "vandalised!\n");
        return 0;
    }

    if (!stringp(str) || (member_array(str, r) == -1)) { 
         notify_fail("You may repair any of the following: " +
                     COMPOSITE_WORDS(r) + ".\n"); 
         return 0;
    }

    c = query_cost_of_repair(str); 

    if (c < 1)
        c = 1;

    if (!MONEY_ADD(tp, -c)) {
        notify_fail("You don't seem to have the money for that repair!\n");
        return 0;
    }

    vandalism = m_delete(vandalism, str); 
    if (m_sizeof(vandalism) == 0)
        remove_my_desc(find_object(GRAFFITI_OB));
    else
        change_my_desc(generate_v_desc(), find_object(GRAFFITI_OB)); 

    e = possible_vandalism[str];
    remaining_vandalism += ([ str : e ]);    
    remove_item(str);
    for (i = 0; i < sizeof(removed_items); i++) 
       if (member_array(str, removed_items[i][0]) > -1) {
           n = i;
           add_item(removed_items[i][0], removed_items[i][1]);
       }
    
    removed_items = exclude_array(removed_items, n, n);
 
    tp->catch_msg("You call the artisans in. The repair costs you " + c 
                  + " cc.\n");
    tell_room(this_object(), QCTNAME(tp) + " calls the artisans in, " +
             "who repair the " + str + " for " + c + " cc.\n", tp); 

    return 1;
}


void
init_vandalism()
{
    add_action(do_repair, "repair");
    add_action(do_repair, "fix");
    add_action(do_repair, "mend");
}

