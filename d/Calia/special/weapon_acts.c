
/* 
    Weapon acts for krougs, part of the kroug brain. 

    Coded by Maniac, 2/3/96 

    History: 

    1996/1997/1998/1999/2000/2001  updates        Maniac 
    21/7/2001   changed to inheritable file       Maniac 
*/ 

#include <macros.h>
#include "defs.h"
#include CALIA_DOMAIN_DEFS
#include CALIA_FILE_DEFS
#include CALIA_KROUG_DEFS

int *weapon_emote_record = ({ }); 


void
check_weapon_emote_record()
{
    if (!sizeof(weapon_emote_record))
        weapon_emote_record = ({ 0, 1, 2, 3, 4, 5, 6 }); 
}


void
weapon_emote(object kroug, object player)
{
    object weapon; 
    string ws; 
    int we; 

    if ((!kroug) || (!player)) 
        return; 

    if (!objectp(weapon = kroug->query_main_weapon(kroug))) 
        return;

    ws = weapon->short();

    check_weapon_emote_record();

    we = weapon_emote_record[random(sizeof(weapon_emote_record))]; 
    weapon_emote_record -= ({ we }); 

    switch (we) 
    {
       case 0 : 
           player->catch_tell(kroug->query_The_name(player) + 
               " tweaks your nose with its " + ws + "!\n"); 
           tell_room(environment(player), QCTNAME(kroug) + " tweaks " + 
               QTNAME(player) + "'s nose with its " + 
               ws + "!\n", player); 
           if (!random(2))
               kroug->command("emote giggles inanely."); 
           break;
       case 1 : 
           player->catch_tell(kroug->query_The_name(player) + 
               " slaps you on the " +
               "backside with its " + ws + "!\n"); 
           tell_room(environment(player), QCTNAME(kroug) + 
               " slaps " + QTNAME(player) + " on the " +
               "backside with its " + ws + "!\n", player); 
           if (!random(2)) 
               kroug->command("emote doubles over laughing."); 
           break;
       case 2 : 
           player->catch_tell(kroug->query_The_name(player) + 
               " twiddles your ears with its " + ws + "!\n");
           tell_room(environment(player), QCTNAME(kroug) + " twiddles " + 
               QTNAME(player) + "'s ears with its " + ws + "!\n", player); 
           if (!random(2)) 
               kroug->command("emote laughs exuberantly.");
           break;
       case 3 : 
           player->catch_tell(kroug->query_The_name(player) + 
               " makes an extremely " + 
               "rude gesture at you with its " + ws + "!\n"); 
           tell_room(environment(player), QCTNAME(kroug) + " makes " + 
               "an extremely rude gesture at " + QTNAME(player) + 
               " with its " + ws + "!\n", player); 
           if (!random(2)) 
               kroug->command("emote grins obnoxiously."); 
           break; 
       case 4 : 
           kroug->command("emote throws its " + ws + " up in the air."); 
           player->catch_tell(kroug->query_The_name(player) + 
               " tries to throttle you.\n"); 
           tell_room(environment(player), QCTNAME(kroug) + 
               " tries to throttle " + QTNAME(player) + ".\n", player); 
           kroug->command("emote catches the descending weapon."); 
           break; 
       case 5 : 
           player->catch_tell(kroug->query_The_name(player) + 
               " prods you savagely in the ribs with " + 
               "its " + ws + ".\n"); 
           tell_room(environment(player), QCTNAME(kroug) + " prods " + 
               QTNAME(player) + " savagely " + 
               "in the ribs with its " + ws + ".\n", player); 
           if (!random(2)) 
               kroug->command("emote chortles amusedly."); 
           break; 
       default : 
           player->catch_tell(kroug->query_The_name(player) + 
               " bounces around waving " + 
               "its " + ws + " angrily at you!\n"); 
           tell_room(environment(player), QCTNAME(kroug) + " bounces " + 
               "around waving its " + ws + " angrily at " + 
               QTNAME(player) + "!\n", player); 
           break; 
    } 
}


/* Kroug makes a comment on the weapon being used by a player */
void
weapon_comment(object kroug, object player)
{
    string pn, comment;
    object weapon;
    int wep_rate;

    if ((!kroug) || (!player))
        return;

    pn = kroug->query_kroug_address_player(player);
    weapon = kroug->query_main_weapon(player); 

    if (!objectp(weapon)) 
        switch (random(3)) {
            case 0 : comment = "What kind of an idiot fights without " +
                               "a weapon anyway, " + pn + "?";
                     break;
            case 1 : comment = "With your bare hands, eh, " + pn + "?";
                     break;
            default : comment = "Only common tavern brawlers like yourself " +
                               "would fight bare-fisted, " + pn + "!";
                     break;
       }
    else {
        wep_rate = weapon->query_pen() + weapon->query_hit(); 
        if (wep_rate >= 80)
            switch (random(3)) { 
                case 0 : comment = ("That " + weapon->short() + " is " +
                           "too good for the likes of you, " + pn + "."); 
                          break;
                case 1 : comment = ("My oh my, " + LANG_ASHORT(weapon) + 
                            ". You really don't deserve it!"); 
                         break;
                default: 
                         comment = ("For evil's sake put that " +  
                            weapon->short() + " down, it's " +
                            "dangerous!"); 
                         break;
             }
        else if (wep_rate >= 55)
             switch (random(3)) { 
                 case 0 : comment = ("I'm going to have that lovely " + 
                         weapon->short() + ", just you wait and see!");
                         break;
                 case 1 : comment = ("Gimme that " + weapon->short() + 
                          "! And no, I don't mean ram it down my " +
                          "throat!"); 
                         break;
                 default : 
                        comment = ("Nice " + weapon->short() + 
                           ", would you like to make a " +
                           "donation to our armoury?");
                        break;
            }
        else if (wep_rate >= 35)
            switch (random(3)) { 
                case 0 : comment = ("Hand over your " + weapon->short() + 
                                     " and stand still!"); 
                         break;
                case 1 : comment = ("Drop your " + weapon->short() + 
                                    " and shut your eyes!"); 
                         break;
                default : comment = ("Insert that " + weapon->short() +  
                                    " in your left ear and twist!");  
                          break;
            }
        else
            comment = ("What a pathetic " + weapon->short() + 
                       ", it's not even worth looting!"); 
    }
    kroug->kroug_say(comment);
}
