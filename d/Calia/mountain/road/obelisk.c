
/* 
   Code inherited by rooms containing obelisks that allows one to
   place one's hand on the obelisk impression and possibly to connect
   minds with people doing the same things at the other obelisks.
   It is also possible to chip/chisel the stone to get a chipping 
   for use in the polymorph quest.  

   Coded by Maniac.

   History:
           5/9/95   Chip/chiselling added                 Maniac
           3/5/95                  Created                Maniac
*/

#pragma save_binary
#pragma no_clone

#include <macros.h>
#include <wa_types.h>
#include "/d/Calia/mountain/defs.h"
#include OBELISK_QUEST
#include POLYMORPH_QUEST

void remove_result(object tp);

mixed hand_in_impression;


/* 
 * both_hands_busy,
 * returns 1 if both hands are holding weapon(s)
 */
int
both_hands_busy(object tp)
{
    if (tp->query_weapon(W_BOTH) ||
        (tp->query_weapon(W_RIGHT) && tp->query_weapon(W_LEFT)))
        return 1;
    else
        return 0;
}


/* 
 * connected, 
 * Returns whether player is connected in mind with other players
 * at the other stones
 */ 
int
connected(object tp)
{
     seteuid(getuid());
     return (MOUNTAIN_SPECIAL + "obelisk_control")->query_connected(tp);
}



/* 
 * try_make_connection,
 * Try to make mental connection between players at the various stones,
 * return 1 for success, 0 for failure.
 */
void
try_make_connection(object tp)
{
     seteuid(getuid());
     (MOUNTAIN_SPECIAL + "obelisk_control")->add_player_at_obelisk(tp);
}


/* 
 * break_connection
 * informs obelisk control object that person has removed hand from 
 * obelisk. Will break up the multi-mind if there was one.
 */
void
break_connection(object tp)
{
    seteuid(getuid());
    (MOUNTAIN_SPECIAL + "obelisk_control")->remove_player_at_obelisk(tp);
} 


/* 
 * obq_block
 * Function used for input from player when connected via obelisks to
 * other minds. 
 */
int
obq_block(string str)
{
    string v;
    object tp = this_player();

    if (!connected(tp)) 
         return 0;


    v = query_verb(); 
    if (v == "disconnect") {
        remove_result(tp);
        return 1;
    }
    else if (v == "think") {
        if (!stringp(str)) {
            tell_object(tp, "Think what to the multi-mind?\n");
            return 1;
        } 
        else { 
            seteuid(getuid());
            (MOUNTAIN_SPECIAL + "obelisk_control")->do_think(tp, str);  
            return 1;
        } 
    }
    else if (tp->query_wiz_level()) { 
        tell_object(tp, "Since you are a wizard you can still do other " + 
                        "commands.\n"); 
        return 0;
    } 
    else {
        tell_object(tp, "That is not possible while all your concentration " +
                "is going into being part of the multi-mind. You may " +
                "`think' thoughts to the multi-mind, or `disconnect'.\n");
        return 1;
    } 
}


/* 
 * remove_result,
 * Function to handle the result of removing a hand from obelisk
 * impression.
 */
void
remove_result(object tp)
{
    if (!objectp(tp) || (hand_in_impression != tp)) 
        return;

    hand_in_impression = 0; 
    tell_room(this_object(), QCTNAME(tp) + " removes " + 
              tp->query_possessive() + " hand from an impression " +
              "on the obelisk.\n", tp);
    tp->catch_msg("You remove your hand from the impression on the " +
                  "obelisk.\n");
    break_connection(tp);
}



/* 
 * place_result,
 * Function to handle the result of placing a hand in obelisk impression.
 */
void
place_result(object tp)
{
    if (!objectp(tp) || objectp(hand_in_impression)) 
        return;
    hand_in_impression = tp; 

    tell_room(environment(tp), QCTNAME(tp) + " places a " + 
              "hand in an impression on the obelisk.\n", tp);
    tp->catch_msg("You place a hand in the impression on the " +
                  "obelisk.\n");
    try_make_connection(tp);
}


/* obq_place, 
   Function to handle action of placing hand in obelisk impression. 
*/
int
obq_place(string str)
{
    string s1, s2, nf;
    int hand, impression;
    object tp = this_player(); 

    nf = "Place";
    hand = 0;
    impression = 0;

    if (!str) {
        notify_fail(nf + " what in what?\n"); 
        return 0;
    }

    if (sscanf(str, "%s in %s", s1, s2) != 2) {
        notify_fail(nf + " what in what?\n"); 
        return 0;
    }

    if ((s1 == "hand") || (s1 == "my hand")) hand = 1;
    if ((s2 == "impression") || (s2 == "impression on obelisk") ||
        (s2 == "obelisk impression")) impression = 1;

    if (!hand) 
        nf += " what in";
    else
        nf += " hand in";

    if (!impression)
        nf += " what?\n";
    else
        nf += " impression?\n";
     
    if (!(impression && hand)) {
        notify_fail(nf);
        return 0;
    }

    if (objectp(hand_in_impression)) {
        if (hand_in_impression == tp) { 
            notify_fail("You already have your hand in the impression!\n"); 
            return 0;
        } 
        notify_fail(hand_in_impression->query_The_name(tp) + 
                   " already has " + tp->query_possessive() + 
                   " hand in the impression, so you can't do that.\n");
        return 0;
    }

    if (both_hands_busy(tp)) {
        notify_fail("But both your hands are occupied at the moment.\n");
        return 0;
    }

    place_result(tp);
    return 1;
}



/* 
 * obq_remove, 
 * Function to handle action of removing hand from obelisk impression. 
 */
int
obq_remove(string str)
{
    string s1, s2, nf;
    int hand, impression;

    nf = "Remove";
    hand = 0;
    impression = 0;

    if (!str) {
        notify_fail(nf + " what from what?\n"); 
        return 0;
    }

    if (sscanf(str, "%s from %s", s1, s2) != 2) {
        notify_fail(nf + " what from what?\n"); 
        return 0;
    }

    if ((s1 == "hand") || (s1 == "my hand")) hand = 1;
    if ((s2 == "impression") || (s2 == "impression on obelisk") ||
        (s2 == "obelisk impression")) impression = 1;

    if (!hand) 
        nf += " what from";
    else
        nf += " hand from";

    if (!impression)
        nf += " what?\n";
    else
        nf += " impression?\n";
     
    if (!(impression && hand)) {
        notify_fail(nf);
        return 0;
    }

    if (this_player() != hand_in_impression) { 
        notify_fail("But you do not have your hand in the impression!\n");
        return 0;
    }

    remove_result(this_player());
    return 1;
}



/* Chip at obelisk to get a chipping of magical stone for the 
   polymorph quest. */
int
pq_chip(string str)
{
    object tp = this_player();

    if (!tp)
        return 0;

    if ((str != "stone") && (str != "obelisk")) { 
        notify_fail("Chip what?\n");
        return 0;
    }

    if (!present("chisel", tp)) {
        notify_fail("You don't have anything that you can chip the stone " +
                    "effectively with.\n");
        return 0;
    }

    if (present(CHIPPING_NAME, tp)) {
        notify_fail("You already have a chipping of magical stone, why " +
                    "get another?\n");
        return 0;
    }

    tp->catch_msg("You chip away at the obelisk with your chisel and " +
                  "obtain a chipping of magical stone.\n");
    tell_room(environment(tp), QCTNAME(tp) + " chips away at the obelisk " +
              "with " + tp->query_possessive() + " chisel and " +
              "obtains a chipping of magical stone.\n", tp);
    clone_object(MOUNTAIN_OBJ+"chipping")->move(tp);
    return 1;
}

