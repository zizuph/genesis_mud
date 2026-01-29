
/* 
   Standard code for avengers, furious spirits of krougs that stay 
   on the mortal plane, courtessy of Kroug's magic. There are four 
   types: deadly (the most powerful), raging, furious, wrathful (the 
   least powerful). 
   Avengers are spirits, so they can follow their targets until they 
   kill the avenger, die or quit. 

   Coded by Maniac 18-19/12/95. 

   2/7/2001  check that target room allowed for "separate" spell   Maniac
   5/11/2000 set_exp_factor                                        Maniac
   11/9/2000 separate spell added                                  Maniac
   17/3/2000 disallows mercy, other updates                        Maniac
    8/7/97   doesn't follow to other domains                       Maniac
    16/12/96 hitlocs corrected                                     Maniac
    19/5/96  typo corrected                                        Maniac
    11/5/96   LIVE_I_UNDEAD added                                  Maniac
    23/1/96   ac improved                                          Maniac
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "/d/Calia/sys/kroug.h"
#include <filter_funs.h> 
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>
#include <const.h>

int avenger_type;
object target;

int round;
int *spell_casts; 
int kpr;


void
reinit_spell_casts()
{
   spell_casts = ({0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 8, 8 });
}


/* Set the player target of the avenger */
void
set_target(object ob)
{
    if (!objectp(ob) || !interactive(ob))
        return;
 
    target = ob;
    
    seteuid(getuid());
}


/* Set the long description of the avenger */
void
set_avenger_long()
{
    string str;
 
    str = ("An avenger, the malignant spirit of a dead kroug returned to " +
          "seek its slayer. Avengers are one of the more recent " +
          "manifestations of Kroug's foul use of magic, and one that is " +
          "sure to worsen the havoc that his armies wreak in Calia. " +
          "Avengers have an indistinct, wraith-like shape, and possess " + 
          "varying degrees of sorcerous ability. ");

    switch (avenger_type) {
        case DEADLY_AVENGER : str += ("This one casts a massive shadow - " +
               "it is some twelve feet tall, jet black in colour, eyes " +
               "burning with a deadly black fire.\n");
             break;
        case RAGING_AVENGER : str += ("This one is huge - " +
                "some ten feet tall, a blacker shade of purple in colour, " +
                "eyes burning with a raging purple fire.\n"); 
             break;
        case FURIOUS_AVENGER : str += ("This one is large - " +
                "some eight feet tall, a blacker shade of red in colour, " +
                "eyes burning with a furious red fire.\n");
             break;
        default : str += ("This one is man size, a blacker shade of frosty " +
                     "blue in colour, eyes burning with a " +
                     "wrathful blue fire.\n");
             break;
     }
     set_long(str);
}


void
set_avenger_hitlocs(int v) 
{
     set_hitloc_unarmed(0, v, 10, "right humerus");
     set_hitloc_unarmed(1, v, 10, "left humerus");
     set_hitloc_unarmed(2, v, 10, "right radius");
     set_hitloc_unarmed(4, v, 10, "left radius");
     set_hitloc_unarmed(8, v, 10, "right thighbone");
     set_hitloc_unarmed(16, v, 10, "left thighbone");
     set_hitloc_unarmed(32, v, 10, "skull");
     set_hitloc_unarmed(64, v, 10, "spine");
     set_hitloc_unarmed(128, v, 10, "rib cage");
     set_hitloc_unarmed(256, v, 10, "collar bone");
}

void
set_avenger_attacks(int v1, int v2)
{
     set_attack_unarmed(0, v1, v2, MAGIC_DT, 25, 
                          "ethereal assault");
     set_attack_unarmed(1, v1, v2, MAGIC_DT, 25, 
                         "black flames"); 
     set_attack_unarmed(2, v1, v2, MAGIC_DT, 25, 
                         "supernatural energy"); 
     set_attack_unarmed(3, v1, v2, MAGIC_DT, 25, 
                         "ghostly power"); 
}


void
set_avenger_type(int type)
{
    avenger_type = type;

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_UNDEAD, (12*(type+1))+4); 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_ATTACKED_BY_SMART_KROUG, 1);
    add_prop(CONT_I_WEIGHT, 20000); 
    add_prop(CONT_I_MAX_WEIGHT, 100000); 

    set_skill(SS_AWARENESS, 80);
    set_name("avenger");
    set_gender(G_NEUTER);
    set_race_name("avenger");
    set_avenger_long();
    reinit_spell_casts();
    round = 0;

    set_exp_factor(115); // spells and tracking 
    switch(avenger_type) {
        case DEADLY_AVENGER : 
             set_adj("deadly");
             set_base_stat(SS_STR, 115);
             set_base_stat(SS_DEX, 115);
             set_base_stat(SS_CON, 115);
             set_base_stat(SS_INT, 80);
             set_base_stat(SS_WIS, 80);
             set_base_stat(SS_DIS, 200);
             set_skill(SS_DEFENSE, 100);
             set_alignment(-550);
             set_hp(query_max_hp());
             set_avenger_hitlocs(60); 
             set_avenger_attacks(38, 38); 
             kpr = 1500;
             seteuid(getuid(this_object()));
             clone_object(MT_OB + "black_orb")->move(this_object());
             clone_object(MT_OB + "black_orb")->move(this_object());
             break;
        case RAGING_AVENGER : 
             set_adj("raging");
             set_base_stat(SS_STR, 90);
             set_base_stat(SS_DEX, 90);
             set_base_stat(SS_CON, 90);
             set_base_stat(SS_INT, 60);
             set_base_stat(SS_WIS, 60);
             set_base_stat(SS_DIS, 200);
             set_skill(SS_DEFENSE, 90);
             set_alignment(-450);
             set_hp(query_max_hp());
             set_avenger_hitlocs(49); 
             set_avenger_attacks(32, 38); 
             kpr = 900;
             seteuid(getuid(this_object()));
             clone_object(MT_OB + "purple_orb")->move(this_object());
             clone_object(MT_OB + "purple_orb")->move(this_object());
             break;
        case FURIOUS_AVENGER : 
             set_adj("furious");
             set_base_stat(SS_STR, 70);
             set_base_stat(SS_DEX, 70);
             set_base_stat(SS_CON, 70);
             set_base_stat(SS_INT, 50);
             set_base_stat(SS_WIS, 50);
             set_base_stat(SS_DIS, 200);
             set_skill(SS_DEFENSE, 80);
             set_alignment(-350);
             set_hp(query_max_hp());
             set_avenger_hitlocs(44); 
             set_avenger_attacks(25, 35); 
             kpr = 550;
             seteuid(getuid(this_object()));
             clone_object(MT_OB + "red_orb")->move(this_object());
             clone_object(MT_OB + "red_orb")->move(this_object());
             break;
        /* wrathful */
        default:         
             set_adj("wrathful");
             set_base_stat(SS_STR, 50);
             set_base_stat(SS_DEX, 50);
             set_base_stat(SS_CON, 50);
             set_base_stat(SS_INT, 40);
             set_base_stat(SS_WIS, 40);
             set_base_stat(SS_DIS, 200);
             set_skill(SS_DEFENSE, 60);
             set_alignment(-250);
             set_hp(query_max_hp());
             set_avenger_hitlocs(38); 
             set_avenger_attacks(20, 25); 
             kpr = 275;
             seteuid(getuid(this_object()));
             clone_object(MT_OB + "blue_orb")->move(this_object());
             clone_object(MT_OB + "blue_orb")->move(this_object());
             break;
      }
}


/* 
 * Function:      room_not_allow_avenger 
 * Description:   Should return whether an avenger will enter 
 *                the room or not (1 it not allowed, 0 if allowed). 
 * Arguments:     object room   -   the room 
 */ 
int 
room_not_allow_avenger(object room) 
{ 
    if (objectp(present("board", room))) 
        return 1; 
    return 0; 
} 


string
query_spell_power_string()
{
    switch (avenger_type) {
        case DEADLY_AVENGER : return "mighty";
                              break;
        case RAGING_AVENGER : return "powerful";
                              break;
        case FURIOUS_AVENGER : return "crackling";
                               break;
        default : return "charged";
                  break;
     }
}


int
query_spell_power()
{
    switch (avenger_type) {
        case DEADLY_AVENGER : return 10;
                              break;
        case RAGING_AVENGER : return 8;
                              break;
        case FURIOUS_AVENGER : return 6;
                               break;
        default : return 4;
                  break;
     }
}


void
mana_spell()
{
    string st;
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;

    st = LANG_ADDART(query_spell_power_string());
    pw = query_spell_power();

    eff = (pw * 5);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIGHT)) / 100;

    tell_object(player, query_The_name(player) + " emits " + st + 
                       " green beam of light at you! You feel drained.\n");

    tell_room(environment(player), QCTNAME(this_object()) + " emits " +
                       st + " green beam of light at " +
                       QTNAME(player) + ", who looks drained!\n", player);

    player->add_mana(-eff);
}


void
fatigue_spell()
{
    string st; 
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;

    st = LANG_ADDART(query_spell_power_string());
    pw = query_spell_power();

    eff = (pw * 2);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIGHT)) / 100;

    tell_object(player, query_The_name(player) + " arcs " + st + 
                " blue beam of light at you! You feel fatigued.\n");

    tell_room(environment(player), QCTNAME(this_object()) + " arcs " +
                       st + " blue beam of light at " +
                       QTNAME(player) + ", who looks fatigued!\n", player);

    player->add_fatigue(-eff);
}


void
health_spell()
{
    string st;
    int pw, eff;
    object player; 

    if (!objectp(player = query_attack()))
        return;

    st = LANG_ADDART(query_spell_power_string());
    pw = query_spell_power();

    eff = (pw * 17);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIGHT)) / 100;

    tell_object(player, query_The_name(player) + " fires " + st + 
                       " searing red beam of light at you. Ouch!\n");

    tell_room(environment(player), QCTNAME(this_object()) + " fires " +
                       st + " searing red beam of light at " +
                       QTNAME(player) + ". Ouch!\n", player);

    player->heal_hp(-eff);
}


/* 
 * Function:     separate_spell 
 * Description:  The avenger moves the target player into another room 
 *               and follows him there. 
 */ 
void 
separate_spell() 
{ 
    int eff, i; 
    object player; 
    string direction, *rooms, *dirs; 

    if (!objectp(player = query_attack())) 
        return; 

    if ((sizeof(FILTER_PLAYERS(all_inventory(environment(player)))) == 1) || 
        !sizeof(dirs = environment(player)->query_exit_cmds())) 
        return; 

    eff = (query_spell_power() * 10); 
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIFE)) / 100; 

    seteuid(getuid()); 
    rooms = environment(player)->query_exit_rooms(); 
    for (i = 0; i < sizeof(rooms); i++) 
    { 
        if (room_not_allow_avenger(rooms[i]->get_this_object())) 
        { 
            dirs[i] = 0; 
        } 
    } 
    if (!sizeof(dirs = filter(dirs, stringp))) 
    { 
        return; 
    } 
    direction = dirs[random(sizeof(dirs))]; 

    tell_object(player, query_The_name(player) + " gestures " + direction + 
                " to you.\n"); 

    tell_room(environment(player), QCTNAME(this_object()) + " gestures " + 
                       direction + " to " + QTNAME(player) + ".\n", player); 

    if (random(eff) > 27) 
    { 
        player->command("$" + direction); 
        if (environment(player) != environment(this_object())) 
            command("$" + direction); 
    } 
} 


void
weapon_spell()
{
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;
   
    if (!player->query_weapon(-1))
        return;

    pw = query_spell_power();

    eff = (pw * 10);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIFE)) / 100;

    tell_object(player, query_The_name(player) + " gestures angrily at " +
                       "you.\n");

    tell_room(environment(player), QCTNAME(this_object()) + " gestures " +
                       "angrily at " + QTNAME(player) + ".\n", player);

    if (random(eff) > 27)
        player->command("$unwield all");
}


void
armour_spell()
{
    int pw, eff;
    object player; 

    if (!objectp(player = query_attack()))
        return;

    if (!player->query_armour(-1))
        return;

    pw = query_spell_power();

    eff = (pw * 10);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIFE)) / 100;

    tell_object(player, query_The_name(player) + " gestures frantically at " +
                       "you!\n");

    tell_room(environment(player), QCTNAME(this_object()) + " gestures " +
                       "frantically at " + QTNAME(player) + "!\n", player);

    if (random(eff) > 27)
        player->command("$remove all");
}


void
icebolt_spell()
{
    string st;
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;

    pw = query_spell_power();

    eff = (pw * 17);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_COLD)) / 100;

    tell_object(player, query_The_name(player) + " slams " + 
                       "an ice bolt into you.\n");

    tell_room(environment(player), QCTNAME(this_object()) + " slams " +
                       "an ice bolt into " + QTNAME(player) + ".\n", 
                       player);

    player->heal_hp(-eff);
}


void
firebolt_spell()
{
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;

    pw = query_spell_power();

    eff = (pw * 17);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_FIRE)) / 100;

    tell_object(player, query_The_name(player) + " thunders " + 
                       "a fire bolt into you.\n");

    tell_room(environment(player), QCTNAME(this_object()) + " thunders " +
                       "a fire bolt into " + QTNAME(player) + ".\n", 
                       player);

    player->heal_hp(-eff);
}


void
panic_spell()
{
    string st;
    int pw, eff;
    object player;

    if (!objectp(player = query_attack()))
        return;

    st = LANG_ADDART(query_spell_power_string());
    pw = query_spell_power();

    eff = (pw * 20);
    eff -= (eff * player->query_magic_res(MAGIC_I_RES_LIGHT)) / 100;

    tell_object(player, query_The_name(player) + " directs " + 
                       st + " white beam of light at you!\n");

    tell_room(environment(player), QCTNAME(this_object()) + " directs " +
                       st + " white beam of light at " +
                       QTNAME(player) + "!\n", player);

    player->add_panic(eff);
}



void
avenger_emote()
{
    switch (random(23)) {
        case 1: command("emote dims to a darker hue.");
                return;
                break;
        case 2: command("emote screeches hideously.");
                return;
                break;
        case 3: command("emote breathes a sound like " +
                        "rock grinding against metal.");
                return;
                break;
        case 4: command("emote produces a deep, ominous growl.");
                return;
                break;
        case 5: command("emote grins horribly.");
                return;
                break;
        case 6: command("emote spits out a flicker of " +
                        "jaundiced light.");
                return;
                break;
        case 7: command("emote glares hatefully.");
                return;
                break;
        case 8: command("emote lets out an unearthly howl!");
                return;
                break;
        case 9: tell_room(environment(this_object()), "The sound here " +
                           "seems to fade out and die for a moment.\n");
                 return;
                 break;
        case 10: tell_room(environment(this_object()), "Black flames " +
                           "leap from " + QTNAME(this_object()) +"'s " +
                           "wraith-like form.\n");
                 return;
                 break;
        case 11: tell_room(environment(this_object()), "Supernatural " +
                           "energy flashes around " + QTNAME(this_object()) +
                           ".\n");
                 return;
                 break;
        case 12: tell_room(environment(this_object()), "Ghostly " +
                           "light bathes " + 
                           QTNAME(this_object()) + "'s dark form.\n");
                 return;
                 break;
        case 13: command("emote crackles with ethereal energy.");
                 return;
                 break;
        case 14: command("emote roars like an icy gust of wind.");
                 return;
                 break;
        case 15: command("emote snaps its phantom jaws at you.");
                 return;
                 break;
        case 16: command("emote raises its arms and " +
                         "chants in a creepy whisper."); 
                 return;
                 break;
        default: command("emote shakes wrathfully.");
                 return;
                 break;
    }
}



/* Handle the special attacks of the avenger, the spells basically */
int
special_attack(object ob)
{
    int i, sc, ch;

    round++;

    switch (avenger_type) {
        case DEADLY_AVENGER : ch = 4;
                              break;
        case RAGING_AVENGER : ch = 5;
                              break;
        case FURIOUS_AVENGER : ch = 6;
                               break;
        default : ch = 7;
                  break;
    }

    if ((round % ch) != 0) {
        if ((round % ch) == (ch / 2)) 
            avenger_emote();
        return 0;
    }

    if (!sizeof(spell_casts))
        reinit_spell_casts();

    i = random(sizeof(spell_casts));
    sc = spell_casts[i];
    spell_casts = exclude_array(spell_casts, i, i);

    switch (sc) { 
        case 0 : mana_spell(); 
                 return 0;
                 break;
        case 1 : fatigue_spell(); 
                 return 0;
                 break;
        case 2 : panic_spell();
                 return 0;
                 break;
        case 3 : firebolt_spell();
                 return 0;
                 break;
        case 4 : icebolt_spell();
                 return 0;
                 break;
        case 5 : health_spell();
                 return 0;
                 break;
        case 6 : weapon_spell();
                 return 0;
                 break;
        case 7 : armour_spell(); 
                 return 0; 
                 break; 
        default : 
                 separate_spell();
                 return 0;
                 break;
    }
}


/* The real work is done in set_avenger_type. */
void
create_creature()
{
}


string
query_mm_in()
{
    return "storms in with a deafening scream of hatred!";
}

string
query_mm_out()
{
    return "storms out with fury in its eyes!";
}


void
avenger_heartbeat()
{
     if (!objectp(target)) {
         if (!objectp(query_attack())) {
             tell_room(environment(this_object()), QCTNAME(this_object()) + 
                      " " + query_mm_out() + ".\n");
             remove_object();
             return;
         }
         set_alarm(15.0, 0.0, avenger_heartbeat);
         return;
     }

     if (environment(target)->query_domain() != "Calia") { 
         tell_room(environment(this_object()), QCTNAME(this_object()) + 
                   " " + query_mm_out() + ".\n");
         remove_object();
         return;
     } 

     if (target->query_linkdead() || 
         room_not_allow_avenger(environment(target))) {
         set_alarm(15.0, 0.0, avenger_heartbeat);
         return;
     }

     if (target->query_ghost()) {
         if (!objectp(query_attack())) {
             tell_room(environment(this_object()), QCTNAME(this_object()) + 
                      " " + query_mm_out() + ".\n");
             remove_object();
             return;
         }
         set_alarm(15.0, 0.0, avenger_heartbeat);
         return;
     }

     if (present(this_object(), environment(target)))  {
         if (objectp(query_attack())) {
             set_alarm(15.0, 0.0, avenger_heartbeat);
         }
         else {
             command("kill " + target->query_real_name());
             set_alarm(15.0, 0.0, avenger_heartbeat);
         }
         return;
     }

     move_living("X", environment(target));
     command("kill " + target->query_real_name());
     set_alarm(15.0, 0.0, avenger_heartbeat);
}


/* Tell kroug brain that an enemy died */
void
notify_you_killed_me(object attacked)
{
    seteuid(getuid());
    KROUG_BRAIN->player_death(this_object(), attacked);
}


void
activate_avenger()
{
    set_alarm(3.0, 0.0, avenger_heartbeat);
    KROUG_BRAIN->avenger_assigned(this_object(), target);
}

void
do_die(object killer)
{
    seteuid(getuid());
    KROUG_BRAIN->avenger_death(this_object(), killer); 
    ::do_die(killer);
}

int
query_knight_prestige()
{
    return kpr;
}

int
query_disallow_mercy()
{
    return 1;
}
