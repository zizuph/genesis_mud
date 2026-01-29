/* 
   The polymorph demon in the polymorph quest.
   Takes the form of a precious item until someone tries to pick
   it up, then turns into a vicious monster and attacks them. 
   Can be three types of monster, a black blob (spits acid), an ice 
   dragon (breathes ice) and a fire demon (breathes fire).
   The special attacks cause critical damage (1/6 of the player's hp
   no matter what it is), which can only be lowered by having magical
   resistance to acid, water and fire.
   Can only be defeated if drained of its transformational energy,
   by a sapphire of draining set in a magical shield. It then
   returns to its original, weak form.
   NPC_I_NO_FEAR is set to 1 in this npc, it is basically a psychotic
   type of demon that doesn't fear anything. I didn't want to set its 
   dis stat to 300 either!

   Coded by Maniac, 1-7 Sept 1995
 
   Modified, damage formula changed, 26/9/95, Maniac
   Extra check in do_die(), 21/11/96, Maniac
   changes in race handling, 3/2/97, Maniac
   changes to some descriptions, 6/4/98, Maniac
*/


#pragma save_binary

inherit "/std/creature";
inherit "/std/act/chat";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <const.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "monster.h"
#include POLYMORPH_QUEST

#define STATE_SWORD 0
#define STATE_CROWN 1
#define STATE_COIN 2
#define STATE_ORIGINAL 3
#define STATE_ACID 4
#define STATE_ICE 5
#define STATE_FIRE 6

#define F_PQ_DAMAGE(tp) ((tp->query_max_hp() * 2) / 9)

/* Descriptive results of the various degrees of attack:
   0% damage of max first, 100% damage of max last */
static string 
*acid_results = 
                ({ "completely unaffected!",
                   "very slightly burned.",
                   "slightly burned.",
                   "somewhat burned.",
                   "burned.",
                   "badly burned.",
                   "very badly burned.",
                   "extremely badly burned!",
                   "hideously burned!",
                   "somewhat dissolved!",
                   "almost dissolved!" });

static string 
*ice_results =
                ({ "completely unaffected!",
                   "very slightly chilled.",
                   "slightly chilled.",
                   "somewhat chilled.",
                   "badly chilled.",
                   "somewhat frostbitten.",
                   "frostbitten.",
                   "badly frostbitten!",
                   "terribly frostbitten!",
                   "nearly frozen solid!",
                   "practically frozen solid!" });

static string
*fire_results =
                ({ "completely unaffected!",
                   "very slightly charred.",
                   "slightly charred.",
                   "somewhat charred.",
                   "charred.",
                   "badly charred.",
                   "somewhat roasted.",
                   "roasted!",
                   "badly roasted!",
                   "roasted severely!",
                   "nearly burned to a crisp! "});
         

int state;
int round;
int attack_alarm;
int transform_energy;
string *drainers = ({ });


/* Can only be hurt if it's in its original state */ 
void
heal_hp(int hp)
{
    if (state == STATE_ORIGINAL)
        ::heal_hp(hp);
    else
        return;
}


/* Masked short function to give short for current state */
string
short_description()
{
     switch (state) {
         case STATE_SWORD  : return "magnificent magical sword"; 
                             break;
         case STATE_CROWN : return "glittering golden crown";
                            break;
         case STATE_COIN : return "platinum coin";
                            break;
         case STATE_ORIGINAL : return "flailing tentacled monstrosity"; 
                               break;
         case STATE_ACID : return "black gelatinous blob"; 
                           break;
         case STATE_ICE : return "huge ice dragon";
                          break;
         case STATE_FIRE : return "fearsome flaming demon";
                           break;
    }
}


/* Masked long function to give long for current state */
string
long_description()
{
     switch (state) {
         case STATE_SWORD  : 
              return ("A magnificent magical sword, jewelled and shining " +
                 "like a star. Its blade looks sharp and positively hums " +
                 "with power.\nIt looks like it is in prime condition.\n");
              break;

         case STATE_CROWN : 
              return ("A glittering crown that looks like it is made of pure " +
                      "gold, set with rubies and emeralds.\n");
              break;
 
         case STATE_COIN : 
              return ("It is a platinum coin, it looks like good money.\n");
              break;

         case STATE_ORIGINAL : 
              return ("A diminutive slimy tentacled form writhes and " +
                      "flails on the ground before you. A number of " +
                      "its startled eyes peer at you " +
                      "from among the tentacles on its spherical body. " +
                      "This must be the demon's true form. For the first time " +
                      "it seems rather nervous about its prospects.\n");
              break;

         case STATE_ACID : 
              return ("This creature is amorphous, just a blob that seems " +
                      "to be made of some kind of black jelly that has a " +
                      "rubbery, resilient quality that makes it extremely " +
                      "hard to damage. It appears to have no internal or " +
                      "external organs.\n");  
              break;

         case STATE_ICE : 
              return ("A monstrous ice dragon, almost mountainous in " +
                      "size, with white scales like mithril shields and " +
                      "great outspread wings like the sails of a galleon. " +
                      "Its barrel-sized eyes regard you frostily.\n");
              break;

         case STATE_FIRE : 
              return ("A fearsome flaming demon of towering humanoid stature, " +
                      "wreathed in hot flames that dance around " +
                      "the lines of its powerful limbs. Smoke curls from " +
                      "its nostrils as it regards you lustily with its " +
                      "smouldering black eyes.\n");
    }
}


void
transform(int new_state)
{
     string old_short = short();

     if (new_state == state)
         return;

     remove_adj(query_adj(1));

     switch (new_state) {
         case STATE_SWORD  : 
              remove_name(query_names());
              set_name("sword");
              set_race_name("sword");
              set_adj(({"magnificent", "magical"})); 
              add_prop(CONT_I_WEIGHT, 8000);
              add_prop(CONT_I_VOLUME, 8000);
              state = STATE_SWORD;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!!\n\n");
              break;

         case STATE_CROWN : 
              remove_name(query_names());
              set_name("crown");
              set_race_name("crown");
              set_adj(({"glittering", "golden"}));
              add_prop(CONT_I_WEIGHT, 5000);
              add_prop(CONT_I_VOLUME, 5000);
              state = STATE_CROWN;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;

         case STATE_COIN : 
              remove_name(query_names());
              set_name("coin");
              set_race_name("coin");
              set_adj("platinum");
              add_prop(CONT_I_WEIGHT, 20);
              add_prop(CONT_I_VOLUME, 1);
              state = STATE_COIN;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;

         case STATE_ORIGINAL : 
              remove_name(query_names());
              set_name("monstrosity");
              add_name("demon"); 
              set_race_name("monstrosity");
              set_adj(({"flailing", "tentacled"})); 
              remove_hitloc(0);
              remove_hitloc(1);
              remove_attack(0);
              remove_attack(1);
              set_attack_unarmed(0,20,20,W_IMPALE,40,"bite");
              set_attack_unarmed(1,20,20,W_SLASH,60, "tentacles");
              set_hitloc_unarmed(0,({8,8,8,8}), 30, "body");
              set_hitloc_unarmed(1,({8,8,8,8}), 70, "tentacles");
              add_prop(CONT_I_WEIGHT, 20000);
              add_prop(CONT_I_VOLUME, 20000);
              state = STATE_ORIGINAL;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;

         case STATE_ACID : 
              remove_name(query_names());
              set_name("blob");
              set_race_name("blob");
              set_adj(({"black", "gelatinous"})); 
              remove_hitloc(0);
              remove_hitloc(1);
              remove_attack(0);
              remove_attack(1);
              set_attack_unarmed(0,20,20,W_BLUDGEON,100,"touch");
              set_hitloc_unarmed(0,({100,100,100,100}),100,"body");
              add_prop(CONT_I_WEIGHT, 80000);
              add_prop(CONT_I_VOLUME, 80000);
              state = STATE_ACID;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;

         case STATE_ICE : 
              remove_name(query_names());
              set_name("dragon");
              set_race_name("dragon");
              set_adj(({"huge", "ice"}));
              remove_hitloc(0);
              remove_hitloc(1);
              remove_attack(0);
              remove_attack(1);
              set_attack_unarmed(0,20,20,W_IMPALE,30,"jaws");
              set_attack_unarmed(1,20,20,W_SLASH,70,"talons");
              set_hitloc_unarmed(0,({100,100,100,100}),70,"body");
              set_hitloc_unarmed(1,({100,100,100,100}),30,"head");
              add_prop(CONT_I_WEIGHT, 500000);
              add_prop(CONT_I_VOLUME, 500000);
              state = STATE_ICE;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;

         case STATE_FIRE : 
              remove_name(query_names());
              set_name("demon");
              set_race_name("demon");
              set_adj(({"fearsome", "fiery"}));
              remove_hitloc(0);
              remove_hitloc(1);
              remove_attack(0);
              remove_attack(1);
              set_attack_unarmed(0,20,20,W_BLUDGEON,30,"fists");
              set_attack_unarmed(1,20,20,W_BLUDGEON,70,"kick");
              set_hitloc_unarmed(0,({100,100,100,100}),70,"body");
              set_hitloc_unarmed(1,({100,100,100,100}),30,"head");
              add_prop(CONT_I_WEIGHT, 200000);
              add_prop(CONT_I_VOLUME, 200000);
              state = STATE_FIRE;
              tell_room(environment(this_object()), "\nThe " + old_short +
                        " transforms into a " + short() + "!\n\n");
              break;
    }
}



int
random_animate_state()
{
    switch (random(3)) {
        case 0 : return STATE_ACID;
                 break;
        case 1 : return STATE_ICE;
                 break;
        default : return STATE_FIRE;
                  break;
   }
}


int
next_animate_state()
{
    switch (state) {
        case STATE_ACID : return STATE_ICE;
                          break;
        case STATE_ICE : return STATE_FIRE;
                 break;
        default : return STATE_ACID;
                  break;
   }
}


/* Transform into a monster and attack the player */ 
void
transform_and_attack(object tp)
{
    int to_state;

    remove_alarm(attack_alarm);
    attack_alarm = 0;

    if (!objectp(tp))
        return;

    if (!present(tp, environment(this_object())))
        return;

    set_alarm(10.0, 0.0, "pqd_heart_beat");

    round = 0;
    to_state = random_animate_state();

    transform(to_state);
    command("kill " + tp->query_real_name());
    tp->add_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON, 1);
}



int
random_inanimate_state()
{
    switch (random(3)) {
        case 0 : return STATE_SWORD;
                 break;
        case 1 : return STATE_CROWN;
                 break;
        default : return STATE_COIN;
                  break;
    }
}



/* Stop fighting all enemies, and vice-versa */
void
stop_fighting_all()
{
    int i;
    object *enemies = query_enemy(-1);

    for (i = 0; i < sizeof(enemies); i++) 
        if (objectp(enemies[i])) {
            enemies[i]->stop_fight(this_object()); 
            this_object()->stop_fight(enemies[i]);
        }
}



/* sapphire set in shield drains transformation energy from demon */
void
energy_drain(object tp)
{
    if (!objectp(tp))
        return;

    if (!present(tp, environment(this_object())))
        return; 

    if ((present(SHIELD_NAME, tp)->query_worn()) == tp) {
        tp->catch_msg("The " + short() + " screams as " +
                      "the sapphire in your magical shield hits " +
                      "it with an energy-draining beam.\n");  
        tell_room(environment(this_object()), "The " + short() + " screams " +
                  "as the sapphire in " + QTNAME(tp) + "'s magical " +
                  "shield hits it with an energy-draining beam.\n", tp);
        transform_energy--;
        if (transform_energy == 0) {
            tell_room(environment(this_object()), "Having no energy " +
                   "left, the demon returns to its original form!\n");
            transform(STATE_ORIGINAL);
        }
    }

    if (member_array(tp->query_real_name(), drainers) == -1)
        drainers += ({tp->query_real_name()});
}



/* Blob spits acid at player */
void
acid_attack(object tp)
{
    int r, p_dam, dam, i, pq_attack_damage; 
    
    if (!objectp(tp))
        return;

    if (!present(tp, environment(this_object())))
        return;

    tp->catch_msg("The " + short() + " spits acid at you!\n");
    tell_room(environment(this_object()), "The " + short() + 
              " spits acid at " + QTNAME(tp) + "!\n", tp);

    pq_attack_damage = F_PQ_DAMAGE(tp);
    r = tp->query_magic_res(MAGIC_I_RES_ACID);
    p_dam = (100 - r);
    dam = (p_dam * pq_attack_damage) / 100;
    i = (p_dam / 10);
    tp->heal_hp(-dam);
    tp->catch_msg("You are " + acid_results[i] + "\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " is " +
              acid_results[i] + "\n", tp); 

    if (!present(ACID_NAME, tp)) {
        seteuid(getuid());
        clone_object(MOUNTAIN_OBJ+"acid_drop")->move(tp);
    }

    if (tp->query_hp() == 0)
        tp->do_die(this_object());
}


/* Ice dragon breathes on player */
void 
ice_attack(object tp)
{
    int r, p_dam, dam, i, pq_attack_damage; 

    if (!objectp(tp))
        return;

    if (!present(tp, environment(this_object())))
        return;

    tp->catch_msg("The " + short() + " blasts you with its icy breath!\n");
    tell_room(environment(this_object()), "The " + short() + 
              " blasts " + QTNAME(tp) + " with its icy breath!\n", tp);

    pq_attack_damage = F_PQ_DAMAGE(tp);
    r = tp->query_magic_res(MAGIC_I_RES_COLD);
    p_dam = (100 - r);
    dam = (p_dam * pq_attack_damage) / 100;
    i = (p_dam / 10);
    tp->heal_hp(-dam);
    tp->catch_msg("You are " + ice_results[i] + "\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " is " +
              ice_results[i] + "\n", tp); 

    if (!present(ICICLE_NAME, tp)) {
        seteuid(getuid());
        clone_object(MOUNTAIN_OBJ+"icicle")->move(tp);
    }

    if (tp->query_hp() == 0)
        tp->do_die(this_object());
}


/* Fire demon flames player */
void
fire_attack(object tp)
{
    int r, p_dam, dam, i, pq_attack_damage; 

    if (!objectp(tp))
        return;

    if (!present(tp, environment(this_object())))
        return;

    tp->catch_msg("The " + short() + " engulfs you in an intense flame!\n");
    tell_room(environment(this_object()), "The " + short() + 
              " engulfs " + QTNAME(tp) + " in an intense flame!\n", tp);

    pq_attack_damage = F_PQ_DAMAGE(tp);
    r = tp->query_magic_res(MAGIC_I_RES_FIRE);
    p_dam = (100 - r);
    dam = (p_dam * pq_attack_damage) / 100;
    i = (p_dam / 10);
    tp->heal_hp(-dam);
    tp->catch_msg("You are " + fire_results[i] + "\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " is " +
              fire_results[i] + "\n", tp); 

    if (!present(CHARCOAL_NAME, tp)) {
        seteuid(getuid());
        clone_object(MOUNTAIN_OBJ+"charcoal")->move(tp);
    }

    if (tp->query_hp() == 0)
        tp->do_die(this_object());
}



void
demon_act()
{
    switch (random(3)) {
        case 0 : this_object()->act1(); 
                 break;
        case 1 : this_object()->act2();
                 break;
        case 2 : this_object()->act3();
                 break;
    }
}


/* 
   This is the heart beat, carries out special attacks, sees to 
   the effects of the magical shield, and does transformations.
   Transforms back to inanimate object if enemies gone, calling stop_fight
   in all concerned.
*/
void
pqd_heart_beat()
{
    object tp = query_attack();
    int to_state;

    round++;

    /* If no more transform energy, just emote */
    if (transform_energy == 0) {
        if (!objectp(tp)) {
             tell_room(environment(this_object()), "The " + short() + 
                                " disappears in a puff of magic!\n");
             remove_object();
        }
        demon_act();
        set_alarm(itof(random(10) + 9), 0.0, "pqd_heart_beat");
        return;
    }

    /* If not fighting anyone, change back into something inanimate */
    if (!objectp(tp)) {
         stop_fighting_all();
         transform(random_inanimate_state());
         return;
    }

    /* Set alarm for loss of transformation energy if shield present */
    if (((present(SHIELD_NAME, tp)->query_worn()) == tp) && 
        (transform_energy > 0))
        set_alarmv(5.0, 0.0, "energy_drain", ({tp}));
    else
        set_alarm(itof(random(4)+3), 0.0, "demon_act");

    /* Time for a special attack if the round count is odd */
    if ((round % 2) == 1) 
        switch (state) { 
            case STATE_ORIGINAL : 
                    return;
                    break;
            case STATE_ACID :
                    acid_attack(tp);
                    set_alarm(itof(random(12) + 7), 0.0, "pqd_heart_beat");
                    return;
                    break;
            case STATE_ICE :
                    ice_attack(tp);
                    set_alarm(itof(random(12) + 7), 0.0, "pqd_heart_beat");
                    return;
                    break;
            case STATE_FIRE:
                    fire_attack(tp);
                    set_alarm(itof(random(12) + 7), 0.0, "pqd_heart_beat");
                    return;
                    break;
            default:
                    return;
                    break;
         }

     to_state = next_animate_state();
     transform(to_state);
     set_alarm(itof(random(12) + 7), 0.0, "pqd_heart_beat");
}



/* 
   If someone other than a fairly weak player tries to get it while it is 
   in inanimate shape, it transforms and attacks them. 
*/
string
my_no_get()
{
    string s = short();
    object tp = this_player();

    if (!objectp(tp))
        return ("The " + s + " cannot be taken.\n");

    if ((state == STATE_ORIGINAL) ||
        (state == STATE_ACID) ||
        (state == STATE_ICE) ||
        (state == STATE_FIRE))
        return ("The " + s + " cannot be taken.\n");

    /* Now we know it's in inanimate state */
    if (tp->query_average_stat() < 45)
        return ("As you reach out to get the " + short() + " some " +
                "sixth sense tells you that it would not be a good " +
                "idea. You decide against it.\n");  

    if ((state == STATE_SWORD) || 
        (state == STATE_COIN) ||
        (state == STATE_CROWN))  
        if (!attack_alarm)
            attack_alarm = set_alarmv(1.0, 0.0, "transform_and_attack", ({tp}));

    return ("The " + s + " cannot be taken.\n");
}



mixed
my_no_attack()
{
    if ((state == STATE_SWORD) || 
        (state == STATE_COIN) ||
        (state == STATE_CROWN))  
        return "You find no such living creature.\n";

    if (objectp(this_player()) && (this_player() == query_attack()))
        return 0;

    return ("You try with all your might to attack it, but " +
            "the telepathic power of the demon prevents you!\n");
}



void
act1()
{
     switch (state) {
         case STATE_SWORD  : return; 
                             break;
         case STATE_CROWN : return;
                            break;
         case STATE_COIN : return;
                            break;
         case STATE_ORIGINAL : 
                           command("emote writhes nervously."); 
                           return;
                           break;
         case STATE_ACID : 
                           command("emote slithers forward."); 
                           return;
                           break;
         case STATE_ICE : 
                          command("emote stretches its enormous wings.");
                          return;
                          break;
         case STATE_FIRE : 
                          command("emote roars like a furnace.");
                          return;
                          break;
    }
}




void
act2()
{
     switch (state) {
         case STATE_SWORD  : return; 
                             break;
         case STATE_CROWN : return;
                            break;
         case STATE_COIN : return;
                            break;
         case STATE_ORIGINAL : 
                           command("emote gulps."); 
                           return;
                           break;
         case STATE_ACID : 
                           command("emote makes a gurgling sound.");
                           return;
                           break;
         case STATE_ICE : 
                          command("emote rakes the earth angrily " +
                                       "with its huge talons."); 
                          return;
                          break;
         case STATE_FIRE : 
                          command("emote snorts fire from its nostrils.");
                          return;
                          break;
    }
}


void
act3()
{
     switch (state) {
         case STATE_SWORD  : return; 
                             break;
         case STATE_CROWN : return;
                            break;
         case STATE_COIN : return;
                            break;
         case STATE_ORIGINAL : 
                           command("emote looks for escape routes in several " +
                                   "directions at once with its eyes."); 
                           return;
                           break;
         case STATE_ACID : 
                           command("emote dissolves some of the ground " +
                                   "around it.");
                           return;
                           break;
         case STATE_ICE : 
                          command("emote grins evilly, showing you a " +
                                  "set of sharp knife-sized teeth.");
                          return;
                          break;
         case STATE_FIRE : 
                          command("emote bellows savagely and its flames intensify.");
                          return;
                          break;
    }
}


void
create_creature()
{
    set_long("@@long_description@@");
    set_short("@@short_description@@");
    set_stats(({100,100,100,100,100,100}));
    state = STATE_ORIGINAL; 
    set_hp(10000);
    set_gender(G_NEUTER);
    set_alignment(-1000);

    state = -1;
    transform(random_inanimate_state());
    round = 0;
    transform_energy = 6;

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1); 
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_M_NO_ATTACK, "@@my_no_attack");
    add_prop(OBJ_M_NO_GET, "@@my_no_get");
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(MAGIC_AM_MAGIC, ({90, "transmutation"}));
    add_prop(OBJ_S_WIZINFO, ("This is a polymorph demon from the " +
                            "polymorph quest in Calia, a demon that " +
                            "can transmute into various inanimate and " +
                            "animate forms. If you would like " +
                            "to know more and don't have read access in " +
                            "Calia, contact the liege of the domain.\n"));

    set_skill(SS_AWARENESS, 100); 
}


void
do_die(object killer)
{
     int i;
     object corpse;

     if (query_hp() > 0)
         return;

     seteuid(getuid()); 
     corpse = clone_object(MOUNTAIN_OBJ+"polymorph_corpse");
     for (i = 0; i < sizeof(drainers); i++)  
         corpse->add_valid_slayer(drainers[i]);
     corpse->move(environment(this_object())); 
     tell_room(environment(this_object()), "The " + short() + " dies with " +
                         "a long terrifying wail!\n");
     ::do_die(killer);
}

