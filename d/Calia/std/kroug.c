
/* 
   Inherited into krougs that wish to use the kroug brain and various 
   kroug special attacks, and the possibility of avengers. 

   Coded by Maniac 

   History:
     12/1/18      added stats for monster krougs    Jaacar 
     27/5/02      fixed runtime error               Maniac
     21/2/02      fixed description reference bug   Maniac
     14/7/01      masked race_sound                 Maniac 
     28/5/01      arm_me called from here now       Maniac 
      3/8/00      emote updates                     Maniac
     29/1/00      moved in heartbeat management     Maniac
     27/12/98     afraid of magical weapons         Maniac
      5/12/98     krougs protect commander          Maniac
      27/8/08     fine tuned                        Maniac
      30/5/98     typo corrected                    Maniac
      10/5/97     commanders wield weapon if 
                  not stunned                       Maniac
      25/10/96    awareness graded                  Maniac
      29/7/96     fine tuning                       Maniac
      27/6/96     avenger function changed          Maniac
      13/6/96     slightly tougher                  Maniac
       9/5/96     updates for raids                 Maniac
       6/5/96     variable changes, arrive/leave changes     Maniac
      11/4/96      death notification modified      Maniac
      13-24/2/96    amendments                      Maniac
      23/1/96    avenger summoning amended          Maniac
      15/12/95   avenger summoning added            Maniac
      12/12/95   vandalism actions added            Maniac
      03/10/95   weapon snatch improved             Maniac
      22/9/95    skills beefed up                   Maniac
       4/9/95              Death cries              Maniac
       1/8/95              Created                  Maniac
*/

#pragma save_binary

inherit "/std/monster";
inherit "/d/Calia/std/kroug_util"; 

#include "/d/Calia/sys/kroug.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <const.h>
#include <filter_funs.h>
#include <files.h> 

#define ROOM_O_KROUG_HEARTBEAT_MANAGER "_room_o_kroug_heartbeat_manager"
#define KROUG_ULTRA_ID "_kroug_ultra_id"
#define KROUG_MONSTER_ID "_kroug_monster_id"

void kroug_heartbeat(); 

string *names = ({ });
int kroug_type, strength; 
int round = 0;
int kpr;

static int kroug_alarm; 

string *kroug_say_verbs = KROUG_SAY_VERBS; 
mixed kroug_adj1 = KROUG_ADJ1; 
mixed kroug_adj2 = KROUG_ADJ2; 
string *kroug_type_np = KROUG_TYPE_NP; 
string *kroug_type_phys = KROUG_TYPE_PHYS; 
string *kroug_type_train = KROUG_TYPE_TRAIN; 
string *kroug_move_desc = KROUG_MOVE_DESC; 



/*
 * Function:      arm_me 
 * Description:   All krougs should define the moving of weapons, 
 *                armour and other equipment by masking this function. 
 */ 
void
arm_me()
{
}


void
create_monster()
{
    this_object()->create_kroug();
    seteuid(getuid());
    KROUG_BRAIN->kroug_activated(this_object());
    kroug_alarm = 0; 
    arm_me(); 
}



/* Kroug may be told to wander at some point and will 
   do so if they are not fighting and there are no 
   good aligned livings in the vicinity. */ 
void
kroug_wander()
{
    object ev;
    mixed ex, qk;
    string *poss = ({ }); 
    int i;

    if (objectp(query_attack()) || 
        sizeof(query_good_npcs(ev = environment())) || 
        sizeof(query_players(ev))) 
        return;

    ex = ev->query_exit();  
    seteuid(getuid()); 
    for (i = 0; i < sizeof(ex); i += 3) { 
        qk = query_krougs(ex[i]->get_this_object()); 
        if (pointerp(qk) && (sizeof(qk) < 8)) 
             poss += ({ ex[i+1] }); 
    }

    if (sizeof(poss)) 
        this_object()->command(poss[random(sizeof(poss))]); 
}


/* Identify this as a smart kroug */
int
query_smart_kroug()
{
    return 1;
}


string
query_m_in()
{
    return (kroug_move_desc[random(sizeof(kroug_move_desc))] + " in."); 
}


string
query_m_out()
{
    return (kroug_move_desc[random(sizeof(kroug_move_desc))]); 
}


/* Krougs say things with specialised say verbs */
void
kroug_say(string str)
{
    command("emote " + kroug_say_verbs[random(sizeof(kroug_say_verbs))] +
            ": " + str);
}


/* 
 * Function name: race_sound 
 * Description  : This function returns the VBFC value for the sound a 
 *                particular living hears when this player speaks. 
 * Returns      : string - the race sound the receiver hears. 
 */ 
string 
race_sound() 
{ 
    return kroug_say_verbs[random(sizeof(kroug_say_verbs))]; 
} 


/* respond to very badly hurt */
void
argh()
{
        switch (random(16)) {
            case 0 : command("emote grits its teeth."); 
                     break;
            case 1 : command("emote grins, seeming to like the prospect " +
                             "of meeting death.");
                     break;
            case 2 : command("emote takes a look at its wounds and " +
                             "laughs fanatically.");
                     break;
            case 3 : command("emote staggers forward, then rights itself.");
                     break;
            case 4 : kroug_say("Heh, pain doesn't scare me!"); 
                     break;
            case 5 : command("emote spits on its wounds in an attempt " +
                             "to disinfect them.");
                     break;
            case 6 : command("emote appears to be ever so slightly shaken.");
                     break;
            case 7 : kroug_say("I'm not finished yet!");
                     break;
            case 8 : command("emote tries to clear its senses.");
                     break;
            case 9 : command("emote sways back and forth like a " +
                             "sapling in the wind."); 
                     break;
            case 10 : command("emote smiles masochistically.");
                      break;
            case 11 : command("emote tries to summon up its reserves.");  
                      break;
            case 12 : kroug_say("Heh, pain. Gotta love it!"); 
                      break;
            case 13 : kroug_say("I can take it! I can take it!");
                      break;
            case 14 : command("emote prepares to shuffle off its " +
                              "mortal coil.");
                      break;
            default : command("emote wipes the blood from its forehead."); 
                     break;
       }
}




/* Set the long description of this kroug */
void
set_kroug_long()
{
    string adj1, adj2;

    adj1 = kroug_adj1[random(sizeof(kroug_adj1))];
    adj2 = kroug_adj2[kroug_type][random(sizeof(kroug_adj2[kroug_type]))];

    this_object()->set_adj( ({adj2, adj1}) );
    this_object()->set_long("This " + adj2 + " " + adj1 + " kroug is " +
                      "one of the " + KROUG_DESC(kroug_type, 2) +
                      " in Kroug's army, being physically " +
                       kroug_type_phys[kroug_type] + " and " +
                       kroug_type_train[kroug_type] + ". " +
                       "As with all krougs, it has blistered, charred " +
                       "black skin and soulless eyes. Its hideous " +
                       "appearance is surpassed only by its total " +
                       "fearlessness and fanaticism.\n");
}


void
set_kroug_type(int type)
{
    kroug_type = type; 

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1); 
    add_prop(NPC_I_NO_LOOKS, 1);
    set_name("kroug");
    set_race_name("kroug");
    set_kroug_long();
    if (random(3))
        set_gender(G_MALE); 
    else 
        set_gender(G_FEMALE);

    switch (kroug_type) {
        case KROUG_REGULAR : 
                          set_base_stat(SS_STR, 50);
                          strength = 55;
                          set_base_stat(SS_DEX, 50);
                          set_base_stat(SS_CON, 50);
                          set_base_stat(SS_INT, 50);
                          set_base_stat(SS_WIS, 50);
                          set_base_stat(SS_DIS, 100);
                          set_skill(SS_WEP_CLUB, 40);
                          set_skill(SS_WEP_KNIFE, 40);
                          set_skill(SS_WEP_SWORD, 40);
                          set_skill(SS_WEP_AXE, 40);
                          set_skill(SS_WEP_POLEARM, 40);
                          set_skill(SS_DEFENSE, 40);
                          set_skill(SS_PARRY, 40);
                          set_skill(SS_2H_COMBAT, 40);
                          set_alignment(-150);
                          set_skill(SS_AWARENESS, 40); 
                          add_prop(LIVE_I_SEE_DARK, 2); 
                          kpr = 300;
                          break;
        case KROUG_TOUGH : set_base_stat(SS_STR, 75);
                          strength = 75;
                          set_base_stat(SS_DEX, 75);
                          set_base_stat(SS_CON, 75);
                          set_base_stat(SS_INT, 75);
                          set_base_stat(SS_WIS, 75);
                          set_base_stat(SS_DIS, 120);
                          set_skill(SS_WEP_CLUB, 60);
                          set_skill(SS_WEP_KNIFE, 60);
                          set_skill(SS_WEP_SWORD, 60);
                          set_skill(SS_WEP_AXE, 60);
                          set_skill(SS_WEP_POLEARM, 60);
                          set_skill(SS_DEFENSE, 60);
                          set_skill(SS_PARRY, 60);
                          set_skill(SS_2H_COMBAT, 60);
                          set_skill(SS_AWARENESS, 50); 
                          add_prop(LIVE_I_SEE_DARK, 3); 
                          set_alignment(-200);
                          kpr = 620;
                          break;
        case KROUG_ELITE : set_base_stat(SS_STR, 100);
                          strength = 95;
                          set_base_stat(SS_DEX, 100);
                          set_base_stat(SS_CON, 100);
                          set_base_stat(SS_INT, 100);
                          set_base_stat(SS_WIS, 100);
                          set_base_stat(SS_DIS, 130);
                          set_skill(SS_WEP_CLUB, 80);
                          set_skill(SS_WEP_KNIFE, 80);
                          set_skill(SS_WEP_SWORD, 80);
                          set_skill(SS_WEP_AXE, 80);
                          set_skill(SS_WEP_POLEARM, 80);
                          set_skill(SS_DEFENSE, 80);
                          set_skill(SS_PARRY, 80);
                          set_skill(SS_2H_COMBAT, 80);
                          set_alignment(-300);
                          set_skill(SS_AWARENESS, 60); 
                          add_prop(LIVE_I_SEE_DARK, 4); 
                          kpr = 1005;
                          break;
        case KROUG_ULTRA : set_base_stat(SS_STR, 175);
                          strength = 175;
                          set_base_stat(SS_DEX, 155);
                          set_base_stat(SS_CON, 155);
                          set_base_stat(SS_INT, 120);
                          set_base_stat(SS_WIS, 120);
                          set_base_stat(SS_DIS, 175);
                          set_skill(SS_WEP_CLUB, 90);
                          set_skill(SS_WEP_KNIFE, 90);
                          set_skill(SS_WEP_SWORD, 90);
                          set_skill(SS_WEP_AXE, 90);
                          set_skill(SS_WEP_POLEARM, 90);
                          set_skill(SS_DEFENSE, 90);
                          set_skill(SS_PARRY, 90);
                          set_skill(SS_2H_COMBAT, 90);
                          set_alignment(-400);
                          set_skill(SS_AWARENESS, 80); 
                          add_prop(LIVE_I_SEE_DARK, 5); 
                          kpr = 1400;
                          add_name(KROUG_ULTRA_ID); 
                          break;
        case KROUG_MONSTER : set_base_stat(SS_STR, 250);
                          strength = 250;
                          set_base_stat(SS_DEX, 230);
                          set_base_stat(SS_CON, 230);
                          set_base_stat(SS_INT, 195);
                          set_base_stat(SS_WIS, 195);
                          set_base_stat(SS_DIS, 250);
                          set_skill(SS_WEP_CLUB, 100);
                          set_skill(SS_WEP_KNIFE, 100);
                          set_skill(SS_WEP_SWORD, 100);
                          set_skill(SS_WEP_AXE, 100);
                          set_skill(SS_WEP_POLEARM, 100);
                          set_skill(SS_DEFENSE, 100);
                          set_skill(SS_PARRY, 100);
                          set_skill(SS_2H_COMBAT, 100);
                          set_alignment(-600);
                          set_skill(SS_AWARENESS, 100); 
                          add_prop(LIVE_I_SEE_DARK, 5); 
                          kpr = 1600;
                          add_name(KROUG_MONSTER_ID); 
                          break;
        default:          set_base_stat(SS_STR, 30);
                          strength = 35;
                          set_base_stat(SS_DEX, 30);
                          set_base_stat(SS_CON, 30);
                          set_base_stat(SS_INT, 30);
                          set_base_stat(SS_WIS, 30);
                          set_base_stat(SS_DIS, 100);
                          set_skill(SS_WEP_CLUB, 25);
                          set_skill(SS_WEP_KNIFE, 25);
                          set_skill(SS_WEP_SWORD, 25);
                          set_skill(SS_WEP_AXE, 25);
                          set_skill(SS_WEP_POLEARM, 25);
                          set_skill(SS_DEFENSE, 25);
                          set_skill(SS_PARRY, 25);
                          set_skill(SS_2H_COMBAT, 25);
                          set_skill(SS_AWARENESS, 25); 
                          add_prop(LIVE_I_SEE_DARK, 1); 
                          set_alignment(-75);
                          kpr = 150;
                          break;
    }
    add_gem_treasure(this_object());
} 


void
add_introduced(string name)
{
    name = lower_case(name);

    if (member_array(name, names) == -1)
        names += ({name});
}


/* How a kroug addresses a player depending on whether met or not */
string
query_kroug_address_player(object player)
{
    if (!player)
        return 0;

    if (CAN_SEE(this_object(), player) && 
        CAN_SEE_IN_ROOM(this_object()))
    { 
        if (member_array(player->query_real_name(), names) > -1)
            return capitalize(player->query_real_name());
        else 
            return player->query_nonmet_name();
    } 
    return "someone"; 
}


/* Tell kroug brain that an enemy died */
void
notify_you_killed_me(object attacked)
{
    KROUG_BRAIN->player_death_by_kroug(query_krougs(environment()), 
        capitalize(attacked->query_real_name())); 
}


void
random_death_cry()
{
    switch (random(24)) { 
        case 0 : command("emote gurgles horribly."); 
                 return;
        case 1 : command("emote goes: Aaarrrrrgggghhhhh!");
                 return;
        case 2 : command("emote dies but only after making a " +
                         "highly offensive gesture!");
                 return; 
        case 3 : command("emote sees its life flash before its eyes."); 
                 command(({"grumble", "moan", "whine", "puke"})[random(4)]); 
                 return;
        case 4 : command("emote dies with a fanatical grin on its face.");
                 return;
        case 5 : command("emote laughs fiercely as it dies!");
                 return;
        case 6 : command("emote screams: Kroug forever! And make sure you " +
                         "get the toe-rag who killed me, won't you!");
                 return;
        case 7 : command("emote sighs: Guess I was a bit overconfident " +
                         "there.");
                 return;
        case 8 : kroug_say("Even your death blow lacked style."); 
                 return;
        case 9 : command("emote spits: Jammy bastard!");
                 return;
        case 10 : command("emote gurgles: Heh, I don't feel so good!");
                  return;
        case 11 : command("emote does an immaculate impression of a " +
                          "dying kroug.");
                  return;
        case 12 : command("emote reluctantly parts company with various " +
                          "organs.");
                  return;
        case 13 : command("emote grunts: Best of three?");
                  return;
        case 14 : command("emote declares stonily: I'll be back.");
                  return;
        case 15 : command("emote screams: I suppose you think that's funny.");
                  return;
        case 16 : command("emote goes: Oommoppphhhh! Me vertebrae!");
                  return;
        case 17 : command("emote snarls: Yeah, right, well nobody's " +
                          "perfect!");
                  return;
        case 18 : command("emote turns a very odd colour.");
                  return;
        case 19 : command("emote throws up a foul smelling black liquid.");
                  return;
        case 20 : command("emote grumbles angrily at the injustice of " +
                          "it all!");
                  return;
        case 21 : command("emote grumbles: Story of my life.");
                  return;
        case 22 : kroug_say("At least I'll no longer inhabit the " +
                            "same world as you.");
                  command("cackle"); 
                  return;  
        default : command("emote gives an insane cackle to mark its death!");
                  return;
    }
}


/* Tell kroug brain that a kroug died */
void
do_die(object killer)
{
    if (!id("scout")) 
        KROUG_BRAIN->kroug_death(query_krougs(environment()), 
            capitalize(killer->query_real_name()), kroug_type); 
    random_death_cry();
    ::do_die(killer);
}


/* 
 * Possibility of an avenger, a spirit of a dead kroug, returning. 
 */
int
second_life(object killer)
{
     object av;

     if (!objectp(killer))
         return 0;

     seteuid(getuid(this_object())); 
     if (!KROUG_BRAIN->query_avenger_now(killer)) 
         return 0;

     av = clone_object(AVENGER);
     av->set_target(killer); 
     switch (kroug_type) {
         case KROUG_ELITE :
         case KROUG_MONSTER : 
         case KROUG_ULTRA : av->set_avenger_type(DEADLY_AVENGER);
                            break;
         case KROUG_TOUGH : av->set_avenger_type(RAGING_AVENGER);
                            break;
         case KROUG_REGULAR : av->set_avenger_type(FURIOUS_AVENGER);
                              break;
         default : av->set_avenger_type(WRATHFUL_AVENGER);
                   break;
     }
     av->activate_avenger();
     return 0;
}



/* special kroug unarmed attacks like punches and kicks */
void
kroug_attack()
{
    object player;
    string part;

    if (!(player = query_attack()))
        return;

    switch (random(4)) { 
        case 0 :  part = ({"nose", "bottom", "ear", "arm", "leg"})[random(5)];
                  tell_watcher(
                      QCTNAME(this_object()) +" leaps forward and sinks its " +
                      "teeth into " +QTNAME(player) + "'s " + part + ".\n", 
                       player);
                   player->catch_msg(QCTNAME(this_object()) + 
                      " leaps forward and sinks its teeth " +
                      "into your " + part + ".\n"); 
                 break;
        case 1 :  part = ({"eye", "jaw", "stomach", "crotch"})[random(4)];
                  tell_watcher(
                      QCTNAME(this_object()) + " punches " + QTNAME(player) + 
                      " in the " + part + ".\n", player);
                  player->catch_msg(QCTNAME(this_object()) + " punches you " +
                      "in the " + part + ".\n");
                 break;
        case 2:  part = ({"chest", "face", "throat", "shoulder"})[random(4)];
                 tell_watcher(
                    QCTNAME(this_object()) + " jump-kicks " + QTNAME(player) + 
                    " to the " + part + ".\n", player);
                 player->catch_msg(QCTNAME(this_object()) + " jump-kicks " +
                   "you to the " + part + ".\n", player);
                 break;
        default:  part = ({"solar plexus", "face" })[random(2)];
                 tell_watcher( 
                    QCTNAME(this_object()) + " swivels and elbows " + 
                    QTNAME(player) + " in the " + part + ".\n", 
                    player);
                 player->catch_msg(QCTNAME(this_object()) + " swivels and " +
                    "elbows you in the " + part + ".\n"); 
                 break;
        }
        player->hit_me(random(strength), W_BLUDGEON, 
                                         this_object(), -1); 
}


/* query the main weapon of the kroug */
object
query_main_weapon(object player)
{
    object weapon_left, weapon_right, weapon_both;

    if (objectp(weapon_both = player->query_weapon(W_BOTH)))
        return weapon_both; 

    weapon_left = player->query_weapon(W_LEFT);
    weapon_right = player->query_weapon(W_RIGHT);

    if (objectp(weapon_right)) {
        if (objectp(weapon_left)) {
            switch (random(2)) {
                case 0 : 
                    return weapon_right; 
                    break; 
                case 1 : 
                    return weapon_left; 
                    break; 
            } 
        } 
        return weapon_right; 
    }
    else if (objectp(weapon_left))
        return weapon_left; 

    return 0;
}


/* special kroug weapon attacks */
void
kroug_swipe()
{
    object player, weapon;
    string part, hit_type;
    int wt;

    if (!(player = query_attack()))
        return;

    weapon = this_object()->query_main_weapon(this_object());

    if (!objectp(weapon)) {
        kroug_attack();
        return;
    }
  
    part = ({"chest", "left leg", "right leg", "left arm", 
             "right arm", "stomach"})[random(6)];

    wt = weapon->query_wt();
    switch (weapon->query_wt()) {
        case W_POLEARM :
        case W_CLUB : hit_type = ({"battering", "thumping",
                                   "jarring"})[random(3)];
                      break;
        case W_SWORD : 
        case W_KNIFE : hit_type = ({"slicing", "cutting", 
                                    "jarring"})[random(3)];
                       break;
        default : kroug_attack();
                  return;
                  break;
     }
     tell_watcher( 
              QCTNAME(this_object()) + " hits " +
                QTNAME(player) + "'s " + part + " with a " + 
               hit_type + " side-swipe of its " + weapon->short() + 
               ".\n", player);
     player->catch_msg(QCTNAME(this_object()) + 
              " hits your " + part + " with a " + hit_type +
              " side-swipe of its " + weapon->short() + ".\n");
     player->hit_me(random(strength), W_BLUDGEON, 
                                      this_object(), -1); 
}


/* A stun attack that elite krougs and kroug commanders have */
void
kroug_stun()
{
    object player;
    string part;
    int delay; 

    if (!(player = query_attack()))
        return;
     
     if (player->query_prop(LIVE_I_ATTACK_DELAY))
         return;

     part = ({"knee-cap", "stomach", "chest", "forehead"})[random(4)];

     tell_watcher(QCTNAME(this_object()) + " stuns " + QTNAME(player) + 
               " with a well timed kick to the " + part + "!\n", 
               player); 
     player->catch_msg(QCTNAME(this_object()) + " stuns you " +
             "with a well timed kick to the " + part + "!\n"); 

     delay = (200 / player->query_average_stat()) * 5;
     if (delay < 10)
         delay = 10;
     else if (delay > 50)
         delay = 50;

     player->add_attack_delay(delay, 1); 
}


void
wield_snatched_weapon(object snatched_weapon)
{ 
    if (snatched_weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON) &&
        !snatched_weapon->query_prop(OBJ_I_BROKEN) && 
        !wildmatch("*Calia*", MASTER_OB(snatched_weapon))) {
        tell_room(environment(), QCTNAME(this_object()) + " glares " + 
                  "suspiciously at " + LANG_THESHORT(snatched_weapon) + 
                  ".\n", this_object()); 
        if (resolve_task(TASK_DIFFICULT, ({ TS_STR })) > 0) {
            tell_room(environment(), "With great effort, " +
                      QTNAME(this_object()) + " manages to " +
                      "break " + LANG_THESHORT(snatched_weapon) + 
                      ".\n", this_object());
            snatched_weapon->add_prop(OBJ_I_BROKEN, 1);  
            command("$drop " + OB_NAME(snatched_weapon)); 
            return; 
        } 
        else {
            tell_room(environment(), QCTNAME(this_object()) + 
                      " tries to break " + 
                      LANG_THESHORT(snatched_weapon) + 
                      " but fails.\n", this_object());
            return; 
        } 
    } 

    if (!sizeof(query_weapon(-1))) 
        command("$wield " + OB_NAME(snatched_weapon)); 
}


/* A snatch weapon special for the commander kroug */
object
snatch_weapon()
{
    object player, weapon;

    if (!(player = query_attack()))
        return 0;

    weapon = this_object()->query_main_weapon(player);

    if (!objectp(weapon) || !random(3)) {
        kroug_stun(); 
        return 0;
    }

    if (this_object()->resolve_task(TASK_DIFFICULT, ({TS_DEX, TS_STR, TS_INT}), 
                                    player, ({TS_STR, TS_WIS})) > 0) {
        if (weapon->move(this_object()) != 0) {
             kroug_stun();
             return 0; 
        }
        tell_watcher(QCTNAME(this_object()) +  " snatches " + 
             "the " + weapon->short() + " out of " + QTNAME(player) + "'s " +
             "hands!\n", player);
        player->catch_msg(QCTNAME(this_object()) + " snatches the " + 
             weapon->short() + " out of your hands!\n");
        return weapon; 
    }
    else {
        tell_watcher(QCTNAME(this_object()) + " tries to snatch " + 
             "the " + weapon->short() + " out of " + QTNAME(player) + "'s " +
             "hands but fails.\n", player);
        player->catch_msg(QCTNAME(this_object()) + " tries to snatch the " + 
             weapon->short() + " out of your hands but fails.\n");
        return 0; 
    }
}


int 
attacking_me(object l)
{
    return (l->query_attack() == this_object()); 
}


int
can_protect(object l)
{
    return (l->query_smart_kroug() && 
            !l->query_prop(LIVE_I_ATTACK_DELAY) &&
            !l->query_prop(LIVE_I_STUNNED)); 
            
}


/* Protect this kroug by getting other krougs to jump in front of it */ 
void
protect_me(object *en)
{
    object *kr; 

    if (!sizeof(kr = (filter(all_inventory(environment()), can_protect) -
                      ({ this_object() }))))
        return;

    kr[random(sizeof(kr))]->protect_kroug(this_object(), en); 
}


/* Protect another kroug by jumping in front of it */ 
void 
protect_kroug(object kr, object *enemies)
{
    int i, td; 
    object this = this_object(); 

    switch (random(7)) {
        case 0 : kroug_say("Here we go!");  
                 break; 
        case 1 : kroug_say("Oi! That's enough of that!");  
                 break; 
        case 2 : kroug_say("Over my dead body!"); 
                 break; 
        case 3 : command("steam");  
                 break; 
        case 4 : command("scream"); 
                 break; 
        case 5 : command("grumble"); 
                 break; 
        case 6 : command("snarl"); 
                 break; 
    } 

    switch (sizeof(enemies)) {
        case 1 : 
        case 2 : td = TASK_ROUTINE; 
                 break; 
        default : td = TASK_DIFFICULT; 
                  break; 
    } 

    if (resolve_task(td, ({ SS_DEFENCE })) < 0) {
        tell_room(environment(this), QCTNAME(this) + 
                  " fails to jump dutifully in front of " + 
                  QTNAME(kr) + ".\n", ({ this }));
        return; 
    } 

    tell_room(environment(this), QCTNAME(this) +
              " jumps dutifully in front of " + 
              QTNAME(kr) + ".\n", ({ this })); 

    for (i = 0; i < sizeof(enemies); i++) { 
        enemies[i]->attack_object(this); 
        tell_object(enemies[i], "You are now fighting " +
                    this->query_the_name(enemies[i]) + ".\n"); 
    }  

    switch (random(8)) {
        case 0 : kr->command("confused");  
                 break; 
        case 1 : kr->command("scratch");  
                 break; 
        case 2 : kr->command("peer " + OB_NAME(this)); 
                 break; 
        case 3 : kr->command("shrug"); 
                 break; 
        default : break; 
    }  
}


/* 
 *  Handle the special attack of the various krougs.
 *  Also gives kroug reactions to being severely hurt.
 */
int
special_attack(object victim)
{
    int hf;
    object w, *en; 

    round++;

    if ((kroug_type == KROUG_ULTRA) && 
        sizeof(en = filter(query_enemy(-1), attacking_me)))
            protect_me(en); 

    if ((kroug_type == KROUG_MONSTER) && 
        sizeof(en = filter(query_enemy(-1), attacking_me)))
            protect_me(en);
            
    if (query_prop(LIVE_I_ATTACK_DELAY) || query_prop(LIVE_I_STUNNED)) 
        return 0;

    if ((round % 6) == 0) {
        if (kroug_type == KROUG_ULTRA) {
            if (objectp(w = snatch_weapon()))
                wield_snatched_weapon(w); 
            return 0;
        }
        else if (kroug_type == KROUG_MONSTER) {
            if (objectp(w = snatch_weapon()))
                wield_snatched_weapon(w); 
            return 0;
        }
        else if (kroug_type == KROUG_ELITE) {
            kroug_stun();
            return 0; 
        }
        else if (kroug_type == KROUG_TOUGH) {
            kroug_swipe();
            return 0;
        }
        else 
            kroug_attack();
        return 0;
    }

    hf = ((query_hp() * 10) / query_max_hp());

    if (hf > 1)
        return 0;

    if (!random(4)) 
        argh();

    return 0;
}


void
attack_object(object ob)
{
     ::attack_object(ob);

     ob->reveal_me(0);

     round = random(4);

     switch (random(40)) {
         case 0 : kroug_say("And who said violence never achieves " +
                            "anything?");
                  return; 
                  break;
         case 1 : kroug_say("Another natural born loser."); 
                  return; 
                  break;
         case 2 : kroug_say("Here's to swift justice!");
                  return; 
                  break;
         case 3 : kroug_say("Stitch this!");
                  return; 
                  break;
         case 4 : kroug_say("Butcher the invader!");
                  return; 
                  break;
         case 5 : kroug_say("Muhahahahahah!"); 
                  return; 
                  break;
         case 6 : command("emote grins psychotically.");
                  return;
                  break;
         case 7 : kroug_say("Trespassers will be executed!"); 
                  return; 
                  break;
         case 8 : kroug_say("You must be a sucker for punishment.");
                  return; 
                  break;
         case 9 : kroug_say("It's party time!");
                  return; 
                  break;
         case 10 : command("emote scowls ferociously.");
                   return;
                   break;
         case 11 : kroug_say("More target practice.");
                   return;  
                   break;
         case 12 : kroug_say("Damn, this one doesn't look very appetising."); 
                   return; 
                   break;
         case 13 : kroug_say("How nice of you to visit!");
                   return;  
                   break;
         case 14 : kroug_say("Ah, some action!"); 
                   return; 
                   break;
         case 15 : kroug_say("You're late for an appointment with your maker.");
                   return; 
                   break;
         case 16 : kroug_say("Bring it!");
                   return; 
                   break;
         case 17 : kroug_say("Now you really asked for it!"); 
                   return; 
                   break;
         case 18 : kroug_say("Greetings."); 
                   return; 
                   break;
         case 19 : kroug_say("This is where the fun really starts!"); 
                   return; 
                   break;
         default : return;
                   break;
    }
}


/* random kroug graffiti */
string
kroug_graffiti()
{
     switch (random(12)) {
         case 0 : return "Kroug kicks Calian bottom.";
                  break;
         case 1 : return "Calians are a bunch of do-gooder clowns!";
                  break;
         case 2 : return "The crystalline palace is a looney bin!";
                  break;
         case 3 : return "KROUGS ROCK FOREVER YOU FOOLS HAHAHAH!!";
                  break;
         case 4 : return "Mount Kyrus is a glorified ant hill!";
                  break;
         case 5 : return "Die all you Calian sewer rats!";
                  break;
         case 6 : return "Kroug's boyz woz 'ere!";
                  break;
         case 7 : return "DIE CALIAN VERMIN!!";
                  break;
         case 8 : return "This place needs good interior decorators.";
                  break;
         case 9 : return "Krom needs more character development.";
                  break;
         case 10 : return "Caliana would make a fine secretary.";
                   break;
         default : return "Hurn is now more intellectually stimulating " +
                          "than when he was alive.";
                   break;
    }
}



/* vandalism function, allows krougs to carry out vandalism */
void
vandalism(mixed rv, object dest)
{
    string *ind;
    string *damage;
    string vandalising, dam_type, action_desc, item_desc_long, item_desc_item;
    mixed weapon_desc;

    if (!objectp(dest))
        return;

    ind = m_indexes(rv);     
    vandalising = ind[random(sizeof(ind))];

    damage = (rv[vandalising])[1];
    dam_type = damage[random(sizeof(damage))];

    weapon_desc = query_main_weapon(this_object())->short();
    if (!stringp(weapon_desc)) 
         weapon_desc = "";
    else
         weapon_desc = (" with its " + weapon_desc);  

    switch (dam_type) {
        case "smear" : 
             switch (random(5)) { 
                case 0 : action_desc = ("smears blood all over the " + 
                                    vandalising + ".");
                         item_desc_long = ("The " + vandalising  + 
                                    " has had blood smeared on it.");
                         item_desc_item = ("Someone has smeared blood " +
                                    "on it.");
                         break;
                case 1 :
                case 2 : 
                case 3 : 
                case 4 : 
                         action_desc = ("daubs some graffiti on the " +
                                     vandalising + ".");
                         item_desc_long = ("The " + vandalising + 
                                    " has had graffiti daubed on it.");
                         item_desc_item = ("Someone has daubed " +
                                    "graffiti on it: " + kroug_graffiti());
                         break;
              }
              break;
        case "scratch" : 
            switch (random(3)) {
                case 0 : action_desc = ("viciously scrapes the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been viciously scraped.");
                         item_desc_item = ("It has been viciously scraped.");
                         break;
                case 1 : action_desc = ("scratches up the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been scratched up.");
                         item_desc_item = ("It has been scratched up.");
                         break;
                default : action_desc = ("deeply scratches the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising  +
                                   " has been deeply scratched.");
                         item_desc_item = ("It has been deeply scratched.");
                         break;
             }
             break;
        case "dent" : 
            switch (random(3)) {
                case 0 : action_desc = ("badly dents the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been badly dented.");
                         item_desc_item = ("It has been badly dented.");
                         break;
                case 1 : action_desc = ("severely dents the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been severely dented.");
                         item_desc_item = ("It has been severely dented.");
                         break;
                default : action_desc = ("repeatedly dents the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising  +
                                   " has been repeatedly dented.");
                         item_desc_item = ("It has been repeatedly dented.");
                         break;
             }
             break;
        case "tear" : 
            switch (random(3)) {
                case 0 : action_desc = ("tears up the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been torn up.");
                         item_desc_item = ("It has been torn up.");
                         break;
                case 1 : action_desc = ("badly rips the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been badly ripped.");
                         item_desc_item = ("It has been badly ripped.");
                         break;
                default : action_desc = ("violently tears the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising  +
                                   " has been violently torn.");
                         item_desc_item = ("It has been violently torn.");
                         break;
            }
            break;
        case "break" : 
            switch (random(3)) {
                case 0 : action_desc = ("breaks the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been broken.");
                         item_desc_item = ("It has been broken.");
                         break;
                case 1 : action_desc = ("viciously damages the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been viciously damaged.");
                         item_desc_item = ("It has been viciously damaged.");
                         break;
                default : action_desc = ("bashes in the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising  +
                                   " has been bashed in.");
                         item_desc_item = ("It has been bashed in.");
                         break;
            }
            break;
        case "shatter" : 
            switch (random(3)) {
                case 0 : action_desc = ("smashes up the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been smashed up.");
                         item_desc_item = ("It has been smashed up.");
                         break;
                case 1 : action_desc = ("bashes the " + 
                                   vandalising + " right out of shape" + 
                                   weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising +
                                   " has been bashed right out of shape.");
                         item_desc_item = ("It has been bashed right out " +
                                    "of shape.");
                         break;
                default : action_desc = ("totally trashes the " + 
                                   vandalising + weapon_desc + "."); 
                         item_desc_long = ("The " + vandalising  +
                                   " has been totally trashed.");
                         item_desc_item = ("It has been totally trashed.");
                         break;
           }
          break;
     default : 
         return;
         break;
    }
    dest->living_vandalises(this_object(), vandalising, action_desc, 
                            item_desc_long, item_desc_item); 
}



/* Start up the kroug heartbeat alarm */
private void
start_kroug_heartbeat()
{
    if (kroug_alarm)
        return;
    kroug_alarm = set_alarm(1.0, 0.0, kroug_heartbeat);
}


int
is_kroug_heartbeat_manager(object room)
{
    return (room->query_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER) ==
                  this_object()); 
}


/* Set this kroug as the heartbeat manager for all krougs in 
   its environment */ 
void
set_kroug_heartbeat_manager(object env)
{
    env->add_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER, this_object()); 
    start_kroug_heartbeat(); 
}


private void
update_kroug_heartbeat_manager(object room)
{
    int i; 
    object *inv; 

    if (objectp(room->query_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER))) 
        return; 

    inv = all_inventory(room) - ({ this_object() }); 
    for (i = sizeof(inv) - 1; i > -1; i--)
        if (inv[i]->query_smart_kroug()) { 
            inv[i]->set_kroug_heartbeat_manager(room); 
            return; 
    } 
}


void
remove_object()
{ 
    object env = environment(); 

    if (!objectp(env))
    {
        ::remove_object();
        return;
    }

    env->remove_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER); 
    update_kroug_heartbeat_manager(env); 

    if (objectp(env = query_prop(LIVE_O_LAST_ROOM)))
        update_kroug_heartbeat_manager(env); 

    if (kroug_alarm) {
        remove_alarm(kroug_alarm); 
        kroug_alarm = 0; 
    }

    ::remove_object(); 
}


/* Entering an environment is when a kroug finds out whether it
   is possible to vandalise it or not. */
void
enter_env(object dest, object from)
{
    mixed tmp;
    int i; 

    ::enter_env(dest, from);

    if (!objectp(dest))
        return; 

    if (mappingp(tmp = dest->query_npc_remaining_vandalism()) &&
        m_sizeof(tmp))
        set_alarm(5.0, 0.0, &vandalism(tmp, dest));

    if (objectp(from) && is_kroug_heartbeat_manager(from)) {
        from->remove_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER); 
        if (kroug_alarm) {
            remove_alarm(kroug_alarm);
            kroug_alarm = 0; 
        } 
        set_alarm(0.0, 0.0, &update_kroug_heartbeat_manager(from)); 
    } 

    if (!objectp(dest->query_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER))) 
        set_kroug_heartbeat_manager(dest);
}


/* An actual npc vs npc combat round. */
void
npc_cr(object att, object def)
{
     int aa, av, da, dv, r;

     /* In case someone died. */ 
     if (!objectp(att) || !objectp(def)) 
         return; 

     /* Attack and defence average stat are the only details used,
        very crude approximation but it cuts cpu cost at least. */
     aa = att->query_average_stat();
     da = def->query_average_stat();

     /* attack value and defence value */
     av = 4 * random(aa + 10);
     dv = 4 * random(da + 10);

     if ((r = av - dv) <= 0) {
         tell_room(environment(att), QCTNAME(att) + " fails to thump " +
                                     QTNAME(def) + ".\n");
         return;
     }

     def->heal_hp(-r);

     tell_room(environment(att), (QCTNAME(att) + " thumps " +
                                  QTNAME(def) + ".\n"));
     if (def->query_hp() <= 0)
         def->do_die(att);
}


int
not_fighting(object ob)
{
     return !objectp(ob->query_attack());
}


void
npc_combat_round(object *att_npcs, object *def_npcs)
{
     int j;

     for (j = 0; j < sizeof(att_npcs); j++)
         npc_cr(att_npcs[j], def_npcs[0]);

     /* Calian npcs project a warning on attack usually */
     def_npcs[0]->do_warn(att_npcs[0]);
}


/* Carry out a kroug act and/or npc combat on each heartbeat */
void
kroug_heartbeat()
{
    int i, gn;
    object *krougs, *players, *good_npcs;
    /* krougs fighting with players */
    object *pf_krougs = ({ });
    /* krougs that may fight with good npcs */
    object *nf_krougs = ({ });
    /* good npcs that are fighting with players */
    object *pf_good_npcs = ({ });
    /* good npcs that may fight with krougs */
    object *nf_good_npcs = ({ });

    object env = environment(); 

    if (!is_kroug_heartbeat_manager(env)) {
        kroug_alarm = 0; 
        return; 
    }

    krougs = query_krougs(env);
    gn = sizeof(good_npcs = query_good_npcs(env)); 
    players = query_players(env); 

    if (!sizeof(players) && !gn) {
        kroug_alarm = 0;
        return;
    }

    for (i = 0; i < sizeof(krougs); i++) {
        if (objectp(krougs[i]->query_attack()))
            pf_krougs += ({krougs[i]});
        else if (!krougs[i]->id("scout"))
            nf_krougs += ({krougs[i]});
    }

    if (gn) {
        for (i = 0; i < sizeof(good_npcs); i++) {
            if (objectp(good_npcs[i]->query_attack()))
                pf_good_npcs += ({good_npcs[i]});
            else
                nf_good_npcs += ({good_npcs[i]});
        }
        if (sizeof(nf_good_npcs))
            npc_combat_round(nf_good_npcs, krougs);
    }

    /* Get idle krougs to attack, or if they can't to
       fight good npcs */
    if (sizeof(nf_krougs)) {
        if (sizeof(players))  {
            KROUG_BRAIN->kroug_attack(nf_krougs, players);
            if (gn) {
                nf_krougs = filter(nf_krougs, not_fighting);
                if (sizeof(nf_krougs))
                    npc_combat_round(nf_krougs, good_npcs);
            }
        }
        else {
            if (gn)
                npc_combat_round(nf_krougs, good_npcs);
        }
    }

    if (sizeof(pf_krougs))
        KROUG_BRAIN->kroug_act(pf_krougs, players);

    kroug_alarm = set_alarm(11.0, 0.0, kroug_heartbeat);
}


void
init_living()
{
    object obj, env = environment(); 

    ::init_living(); 

    if (!objectp(obj = env->query_prop(ROOM_O_KROUG_HEARTBEAT_MANAGER))) {
        set_kroug_heartbeat_manager(env); 
        obj = this_object(); 
    } 

    if (obj == this_object() && living(this_player()))
        start_kroug_heartbeat(); 
}


int
query_knight_prestige()
{
    return kpr;
}
