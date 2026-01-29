
/* 
   Central kroug `brain' accessed by all Krougs in the foothills around 
   Mt Kyrus., Gives a pre-arranged `personality' for krougs, which take 
   the form of various spontaneous actions and reactions to various 
   circumstances, mostly in combat. 

   This file also sends out kill information to whatever kroug raid object 
   is in operation (if any). 

   Coded by Maniac. 

   History: 
          14/7/01     started inheriting acts                Maniac
          27/5/01     new emotes added                       Maniac
           3/2/00     moved in some of old kroug room        Maniac
          27/6/96     better handling of avengers            Maniac
          25/5/96     addition of actions for krougs         Maniac
          12/5/96     new raid interface code installed      Maniac
          11/4/96     notifications modified                 Maniac
           2/3/96     included weapon_emotes.c               Maniac
          16/2/96     upgraded occ insults and moved them 
                      into separate file                     Maniac
          13/2/96     updated, raid code to be separated     Maniac
          13/10/95    Bugs corrected                         Maniac
          28/9/95    extra functions added                   Maniac
          19/9/95    some control added for kroug raids      Maniac
          11/9/95    check for incognito                     Maniac
          15/8/95    First modifications complete            Maniac
           8/8/95    Created                                 Maniac
*/

#pragma save_binary

#include "defs.h"
#include CALIA_DOMAIN_DEFS
#include CALIA_FILE_DEFS
#include CALIA_KROUG_DEFS
#include CALIA_GUILD_RECORD_DEFS
#include CALIA_PALACE_DEFS

inherit KROUG_GUILD_ACTS;
inherit KROUG_GENERAL_ACTS;
inherit KROUG_INTER_GROUP_ACTS;
inherit KROUG_WEAPON_ACTS;

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <std.h>

#define FOOTHILL_DIR "/d/Calia/mountain/foothill/"

int avenger_total = 0;
int avenger_counter = 0;

int last_shout_time = 0;
string *warned = ({ });
int *events = ({ });

string raid_path;

string *kroug_rooms = ({ });

#include "group_emotes.c"

/* Decide on the kroug rooms on creation */
void
create()
{
     int *poss_weak_rooms = ({5, 6, 7, 8, 15, 16, 17, 18, 25, 26, 27,
	 28, 29, 30, 36, 37, 38, 40, 46, 47, 48, 52, 53, 54}); 
     int *poss_med_rooms = ({61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
	 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
	 87, 88, 89, 90});
     int *poss_el1_rooms = ({ 92, 97, 102, 107, 113, 118 }); 
     int *poss_el2_rooms = ({ 94, 98, 103, 109, 115, 120 }); 
     int *poss_el3_rooms = ({ 96, 100, 105, 111, 117 });
     int *poss_com_rooms = ({ 119 });

     int i, n, c;

     raid_path = ""; 
     kroug_rooms = ({ });

     /* weak rooms */
     for (i = 0; i < 24; i++) {
         n = random(sizeof(poss_weak_rooms));  
         kroug_rooms += ({ sprintf("%sfh%02d", FOOTHILL_DIR,  poss_weak_rooms[n]) });
         poss_weak_rooms -= ({poss_weak_rooms[n]});
     }
     
    /* medium rooms */
     for (i = 0; i < 30; i++) {
         n = random(sizeof(poss_med_rooms));  
         kroug_rooms += ({ (FOOTHILL_DIR + "fh" + poss_med_rooms[n]) });
         poss_med_rooms -= ({poss_med_rooms[n]});
     }
     /* Elite rooms */
     for (i = 0; i < 6; i++) {
         n = random(sizeof(poss_el1_rooms));  
         kroug_rooms += ({ (FOOTHILL_DIR + "fh" + poss_el1_rooms[n]) });
         poss_el1_rooms -= ({poss_el1_rooms[n]}); 
     }
     for (i = 0; i < 6; i++) {
         n = random(sizeof(poss_el2_rooms));  
         kroug_rooms += ({ (FOOTHILL_DIR + "fh" + poss_el2_rooms[n]) });
         poss_el2_rooms -= ({poss_el2_rooms[n]}); 
     }
     for (i = 0; i < 5; i++) {
         n = random(sizeof(poss_el3_rooms));  
         kroug_rooms += ({ (FOOTHILL_DIR + "fh" + poss_el3_rooms[n]) });
         poss_el3_rooms -= ({poss_el3_rooms[n]}); 
     }
     /* commander room */
     n = random(sizeof(poss_com_rooms));
     kroug_rooms += ({ (FOOTHILL_DIR + "fh" + poss_com_rooms[n]) });
     poss_com_rooms -= ({ poss_com_rooms[n] }); 

     setuid();
     seteuid(getuid());
     init_occ_acts(); 
     init_general_acts(); 
     init_inter_group_acts(); 
}


void
set_raid_path(string p)
{
    if (objectp(this_interactive()))
        return;
    raid_path = p; 
}


void
set_raid_inactive()
{
    if (objectp(this_interactive()))
        return;
    raid_path = ""; 
}


string *
query_kroug_rooms()
{
    return kroug_rooms; 
}



/* Reset check - rooms call this function to see if they should
   contain krougs on this reboot */
int
reset_check(string filename)
{
     int i;

     if (member_array(filename, kroug_rooms) == -1)
         return 0;
     else
         return 1;
}


/* query_avenger_now, function to return whether an avenger should
   appear for the latest kroug */
int
query_avenger_now(object tp)
{
    int cr;

    if (!interactive(tp)) 
        return 0;

    avenger_total++; 
    avenger_counter++;

    if (strlen(raid_path)) 
        cr = 3;
    else
        cr = 5;

    if ((avenger_counter >= (cr * cr)) || 
        ((avenger_counter % cr) == 0) && (!random(cr))) {
        avenger_counter = 0; 
        return 1;
    }
    else
        return 0;
}


void
avenger_death(object av, object pl)
{
     if (!objectp(av) || !objectp(pl))
         return;

     if (strlen(raid_path)) 
         tell_room(raid_path->query_raid_room(), 
             (pl->query_name() + " just killed " + QNAME(av) + "!\n"));
}


void
avenger_assigned(object av, object pl)
{
     if (!objectp(av) || !objectp(pl))
         return;

     if (strlen(raid_path)) 
          tell_room(raid_path->query_raid_room(), 
              (QCNAME(av) + " locked on to " + pl->query_name() + "!\n"));
}


/* Avenger just killed a player */ 
void
player_death(object av, object pl)
{
     if (!objectp(av) || !objectp(pl))
         return;

     if (strlen(raid_path)) { 
         tell_room(raid_path->query_raid_room(), 
           (QCNAME(av) + " just killed " + pl->query_name() + "!\n"));
         raid_path->casualty(pl->query_name()); 
     }
}


/* Returns a command for a random reaction to a kroug's death
   depending on how powerful that kroug was */
string
random_react_kroug_death(int kt)
{
    if ((kt == KROUG_WEAK) || (kt == KROUG_REGULAR))  
        switch(random(10)) {
             case 0 : return "emote swears savagely.";
                      break;
             case 1 : return "emote snarls: Curse you!";
                      break;
             case 2 : 
                    return "emote growls: I will avenge you!";
                    break;
             case 3 : return "stomp";
                      break;
             default : return "";
                      break;
        }
    else if (kt == KROUG_TOUGH) 
        switch(random(12)) {
             case 0 : return "emote swears furiously.";
                      break;
             case 1 : return "emote snarls: You will pay for that!";
                      break;
             case 2 : return "emote growls: Got lucky there, swine!";
                      break;
             case 3 : return "emote screams in anger!";
                      break;
             case 4 : return "steam";
                      break;
             case 5 : return "spit";
                      break;
             default : return "";
                      break;
        }
    else 
        switch(random(9)) {
             case 0 : return "emote screams in fury!";
                      break;
             case 1 : return "despair";
                      break;
             case 2 : return "emote howls in rage!";
                      break;
             case 3 : return "emote jumps up and down in fury!";
                      break;
             case 4 : return "emote screams: No! NO! NOOO!";
                      break;
             case 5 : return "emote widens its eyes in shock.";
                      break;
             default : return "";
                      break;
        }
}



/* Control of the reaction to the death of a fellow kroug in this room */
void
kroug_react_kroug_death(object *krougs, string killer_name, int kt)
{
    int ks, i, ps;
    object *react_krougs;
    string kd;

    if (strlen(raid_path)) 
        raid_path->kroug_death(killer_name, kt);  

    if (!(ks = sizeof(krougs = filter(krougs, objectp))))
        return;

    if (ks < 3)
        react_krougs = krougs; 
    else
        react_krougs = krougs[0 .. 1];

    ks = sizeof(react_krougs);

    for (i = 0; i < ks; i++) 
        react_krougs[i]->command(random_react_kroug_death(kt)); 
}


string
random_react_player_death()
{
    switch (random(10)) {
        case 0 : return "bounce madly";
                 break;
        case 1 : return "cheer wildly";
                 break;
        case 2 : return "emote howls in exaltation!";
                 break;
        case 3 : return "emote punches the air with delight.";
                 break;
        case 4 : return "emote snarls: HUAAGGHH!! Got the scum!";
                 break;
        case 5 : return "emote sneers: Hah! I'll feast on the corpse!";
                 break;
        case 6 : return "emote cheers: That'll teach you to mess with us!";
                 break;
        case 7 : return "emote celebrates fanatically.";
                 break;
        case 8 : return "shout YES!";
                 break;
        default: return "shout Nailed you, you vermin!";
                 break;
    }
}


/* Control of the reaction to the death of a fellow kroug in this room */
void
kroug_react_player_death(object *krougs, string player_name)
{
    int ks, i; 

    if (strlen(raid_path)) 
         raid_path->casualty(player_name); 

    if (!(ks = sizeof(krougs = filter(krougs, objectp)))) 
        return; 

    for (i = 0; i < ks; i++) 
        krougs[i]->command(random_react_player_death()); 
}


/* Called from a kroug when it dies */ 
void
kroug_death(object *krougs, string killer_name, int kroug_type)
{
    set_alarm(0.5, 0.0, 
        &kroug_react_kroug_death(krougs, killer_name, kroug_type)); 
}


/* Called from a kroug when it kills a player */ 
void
player_death_by_kroug(object *krougs, string player_name)
{
    set_alarm(0.5, 0.0, 
        &kroug_react_player_death(krougs, player_name)); 
}


/* Decide whether to attack a player (Give really little 'uns a warning */
int
kroug_attack_player(object kroug, object player, int num)
{
    string pn = kroug->query_kroug_address_player(player);

    if ((player->query_average_stat() < MIN_AVG_STAT_TO_ATTACK) &&
        (member_array(player->query_real_name(), warned) == -1))
       { 
          if (num == 0)
            switch (random(3)) {
               case 0 : kroug->kroug_say("Oi, " + pn + ", " +
                              "get going before I decide to rip " +
                              "your miserable head off!");
                        break;
               case 1 : kroug->kroug_say("Go away " + pn + ", you little " +
                                      "idiot, or we'll get angry with you.");
                        break;
               default : kroug->kroug_say("Get going, and fast, " + pn + 
                                          ", or we'll snuff you out!");
                        break;
             }
          return 0;
       }
    return (kroug->command("kill " + player->query_real_name())); 
}


/* Krougs attack players */
void
kroug_attack(object *krougs, object *players)
{
    int i, j, sp, sk;

    sk = sizeof(krougs);
    if (!sk)
        return;

    sp = sizeof(players);
    if (!sp)
        return;

    for (i = 0; i < sk; i++) {
       j = sp-1;
       while ((j >= 0) &&
              !kroug_attack_player(krougs[i], players[j], i))
           j--;
    }

    for (j = 0; j < sp; j++) 
        if ((players[j]->query_average_stat() < MIN_AVG_STAT_TO_ATTACK) &&
            (member_array(players[j], warned) == -1))
            warned += ({players[j]->query_real_name()});
}


/* Krougs attack a new player */
void
new_attack(object *krougs, object *players)
{
    int i, j, sp, sk;

    sk = sizeof(krougs);
    if (!sk)
        return;

    sp = sizeof(players);
    if (!sp)
        return;

    j = random(sp);
    for (i = 0; i < sk; i++) 
         kroug_attack_player(krougs[i], players[j], i);

    for (j = 0; j < sp; j++) 
        if ((players[j]->query_average_stat() < MIN_AVG_STAT_TO_ATTACK) &&
            (member_array(players[j], warned) == -1))
            warned += ({players[j]->query_real_name()});
}



string
random_react_player_leave()
{
    switch (random(5)) {
        case 0 : return "shout Come back here you WIMP!"; 
                 break;
        case 1 : return "shout Hah! You utter coward!";
                 break;
        case 2 : return "shout You're an excuse for a fighter!";
                 break;
        case 3 : return "shout Frightened rabbit!";
                 break;
        default : return "shout Oi! We have some unfinished business here!";
                 break;
     }
}


/* Krougs react to an enemy leaving the room */
void
kroug_shout(object *krougs, object player)
{
    int ks = sizeof(krougs);
    object react_kroug;
    int i, t;

    if (!objectp(player)) 
        return;

    if ((player->query_average_stat() < MIN_AVG_STAT_TO_ATTACK) &&
        (member_array(player->query_real_name(), warned) > -1))
        warned -= ({player->query_real_name()});

    if (player->query_ghost()) 
        return;

    t = time();
    if ((t - last_shout_time) < 5)
        return;

    if (!ks)
        return;
     
    last_shout_time = t;

    react_kroug = krougs[0]; 
    if (!CAN_SEE(react_kroug, player))
        return;

    if (member_array(player, react_kroug->query_enemy(-1)) > -1) 
        react_kroug->command(random_react_player_leave()); 
}


/* Kroug comments on one of the stats of a player */
void
stat_comment(object kroug, object player)
{
    string pn, comment;
    int i, s, *comment_stats, *stats;

    if ((!kroug) || (!player))
        return;

    pn = kroug->query_kroug_address_player(player);
    
    stats = allocate(SS_NO_EXP_STATS);
    comment_stats = ({ });

    stats[SS_STR] = player->query_stat(SS_STR);
    stats[SS_DEX] = player->query_stat(SS_DEX);
    stats[SS_CON] = player->query_stat(SS_CON);
    stats[SS_INT] = player->query_stat(SS_INT);
    stats[SS_DIS] = player->query_stat(SS_DIS);
    stats[SS_WIS] = player->query_stat(SS_WIS);

    i = 0;

    while (i < SS_NO_EXP_STATS) {
        if ((stats[i] > 95) ||
            (stats[i] < 50))
            comment_stats += ({i});
        i++;
    }
    
    s = sizeof(comment_stats); 
    if (!s) 
        return; 

    i = comment_stats[random(s)]; 

    switch (i) { 
        case SS_INT : if (stats[i] < 50) 
                          comment = pn + ", you look unbelievably " + 
                                    "stupid. Unfortunately " + 
                                    "there aren't any spare brains " + 
                                    "around, or we'd try to help."; 
                      else 
                          comment = pn + ", you look cleverer than " +
                                    "the average mountain goat."; 
                      break; 
        case SS_WIS : if (stats[i] < 50) 
                          comment = pn + ", you're just knowledgeable " +
                                    "enough to know the meaning of " + 
                                    "ignorance!"; 
                      else 
                          comment = pn + ", kicking wise-ass is fun."; 
                      break; 
        case SS_STR : if (stats[i] < 50) 
                          comment = pn + ", I've seen more muscle on a " + 
                                    "sawdust-fed chicken!"; 
                      else 
                          comment = pn + ", be grateful for those " + 
                                    "muscles, everyone needs one redeeming " + 
                                    "quality!"; 
                      break; 
        case SS_DEX : if (stats[i] < 50) 
                          comment = pn + ", if you get any more clumsy " + 
                                    "we won't even have to take a swing!"; 
                      else 
                          comment = pn + ", your balance and poise are " + 
                                    "perfect for morris dancing."; 
                      break; 
        case SS_CON : if (stats[i] < 50) 
                          comment = pn + ", don't breathe so hard, it's " + 
                                    "wearing you out!"; 
                      else 
                          comment = pn + ", you look tough, in " + 
                                    "the same sense as a stunned buffalo."; 
                      break; 
        case SS_DIS : if (stats[i] < 50) 
                          comment = pn + ", you are an utter coward, " + 
                                   "I can smell it."; 
                      else 
                          comment = pn + ", fortune favours the brave, " + 
                                    "I'll stick a pin in you and blow " +
                                    "all your luck!"; 
                      break; 
        default : return; 
                  break; 
    } 
    kroug->kroug_say(comment); 
}



/* Kroug comments on the health of the player it is fighting */
void
health_comment(object kroug, object player)
{
    string pn, comment;
    int h, m, p;

    if ((!kroug) || (!player))
        return;

    pn = kroug->query_kroug_address_player(player);

    h = player->query_hp();
    m = player->query_max_hp();
    p = (10 * h) / m;

    if (p >= 9) {
        comment = pn + ", start dying, it's going to happen sooner or " +
                  "later anyway!";
        kroug->kroug_say(comment);
    }
    else if (p < 4) {
        comment = pn + ", it won't be long before you're dead now!";
        kroug->kroug_say(comment);
    }
}


/* Align comment: remark relevant to marked alignments */
void
align_comment(object kroug, object player)
{
    string pn, comment;
    int al;

    if ((!kroug) || (!player))
        return;

    pn = kroug->query_kroug_address_player(player);

    al = player->query_alignment();

    comment = "";

    if (al < -500) { 
         switch (random(4)) {
             case 0 : comment = pn + ", I will show you " +
                               "what real cruelty is, not like " +
                               "your watered-down version!"; 
                      break;
             case 1 : comment = "Kneel to the greater evil, " +
                                "blackhearted " + pn + ".";
                      break;
             case 2 : comment = "Learn what real evil is, " +
                                pn + "!";
                      break;
             default : comment = pn + ", you will meet the devil " +
                                "you have courted all your life soon.";
                      break;
          }
          kroug->kroug_say(comment); 
     }
     else if (al > 500) {
         switch (random(5)) {
             case 0 : comment = pn + ", your moral purity is sickening."; 
                      break;
             case 1 : comment = pn + ", if you start preaching ethics " +
                                "to me I'll tear out your tongue!";
                      break;
             case 2 : comment = "I love to carve up snotty do-gooders " +
                                "like you, " + pn + ".";
                      break;
             case 3 : comment = "Why don't you just wear a halo and " +
                                "have done with it, " + pn + "?";
                      break;
             default : comment = "You followers of the righteous " +
                                 "path are utter losers, " + pn + ".";
                      break;
         }
         kroug->kroug_say(comment); 
     }
}



/* Reset the event array 
     0 - do nothing
     1 - general act
     2 - combat situation act
     3 - guild comment
     4 - weapon comment
     5 - alignment comment
     6 - stat comment
     7 - health comment
     8 - weapon emote
     9 - group emote
     10- new attack
*/
void
reset_events()
{
    events = ({0, 0, 0, 0, 0, 0,                    /* 6 */ 
               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,     /* 11 */
               2, 2,                                /* 2 */ 
               3, 3, 3,                             /* 3 */
               4,                                   /* 1 */
               5,                                   /* 1 */
               6,                                   /* 1 */
               7,                                   /* 1 */           
               8, 8,                                /* 2 */ 
               9, 9,                                /* 2 */
               10, 10, 10 });                       /* 3 */
}



/* Central control of the kroug acts, this is called by the kroug
   heart beat in kroug rooms when there are both players and
   krougs in them.
*/
void
kroug_act(object *krougs, object *players)
{
    int number, s, i;
    object kroug, player;

    if ((!sizeof(krougs)) || (!sizeof(players)))
        return;

    kroug = krougs[random(sizeof(krougs))];
    player = players[random(sizeof(players))];
    if (!CAN_SEE(kroug, player))
        return;

    s = sizeof(events);

    if (!s) {
        reset_events();
        s = sizeof(events);
    }

    i = random(s);
    number = events[i];
    events = exclude_array(events, i, i);

    if (number == 0) 
        return; /* i.e. do nothing */
    else if (number == 1)
        general_act(kroug, player); 
    else if (number == 2)
        combat_situation_act(kroug, krougs, players);  
    else if (number == 3)
        guild_comment(kroug, player);
    else if (number == 4)
        weapon_comment(kroug, player);
    else if (number == 5)
        align_comment(kroug, player);
    else if (number == 6)
        stat_comment(kroug, player);
    else if (number == 7)
        health_comment(kroug, kroug->query_attack());
    else if (number == 8) 
        weapon_emote(kroug, player); 
    else if (number == 9) 
        group_emote(krougs, players); 
    else if (number == 10) 
        new_attack(krougs, players); 
}

