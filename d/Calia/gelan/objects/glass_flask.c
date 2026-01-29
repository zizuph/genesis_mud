/* 
 *  Glass flask for mixing potions up in the Alchemist quest of Gelan.
 *  Check the quest doc and alchemist's notebook if you want to make 
 *  complete sense out of this! 
 * 
 *  Created 20.3.95 by Maniac. 
 *  Modified 31.5.95 by Maniac
 *  More comments added, 13/12/97, Maniac
 *  More features added, 7/4/98, Maniac
 */


inherit "/std/object";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>

#include "object.h"
#include ALCHEMIST_QUEST



#define POUR_NF "Pour how many measures of what into the glass flask? " + \
                "e.g. pour 1 grumblejuice flask.\n"
#define EMPTY_NF "Empty what? The glass flask?\n"
#define DRINK_NF "Drink potion from glass flask?\n"

#define AN_ALL_INV(o) all_inventory(o) + all_inventory(environment(o))


mixed this_potion; /* An array holding a sequence of agents and quantities */ 

int next_measure;  /* The index for the next measure poured into the flask */ 


/* 
 *  Each of the agents that can be used to mix potions in this glask flask
 *  has a short-hand name that Raspatoon uses in his notebook. The short-hand 
 *  is also used in the this_potion array.  
 */ 
mapping agents = (["frogspawn": "fn",
                   "bordume": "bm", 
                   "hethilyne": "hy",
                   "nyrjocams": "ny",
                   "slotducs": "st", 
                   "archotics": "ah",
                   "yukrofyll": "yk",
                   "norseato": "ne", 
                   "zludgenib": "zg", 
                   "hyphaphoori": "ha", 
                   "mubellus": "mb",
                   "yuilgbus": "yg", 
                   "sloydacs": "sa",
                   "testitra": "ta",
                   "frazzolli": "fo",
                   "bartilobyn": "bb",
                   "znorktone": "zk", 
                   "nargrincu": "ng",
                   "hrulisome": "hu",
                   "masspreg": "mp",
                   "barazine": "bz",
                   "frazzelli": "fe",
                   "mirmotj": "mj",
                  ]);

string 
agent_names()
{
    return COMPOSITE_WORDS(m_indexes(agents));
}

string
*query_agents()
{
    return (m_indexes(agents));
}


/* 
 * g_change_cures: 
 * The sequence of agents and quantities for each cure of a gender change. 
 * The variable this_potion must match the appropriate one of these when 
 * the potion is drunk from this flask. 
 */  
mapping g_change_cures =
([
    "fm" :  ({ ({2, "yg"}), ({1, "bm"}), ({3, "zk"}), ({4, "fe"}) }),
    "fn" :  ({ ({1, "yg"}), ({1, "bm"}), ({2, "zk"}), ({4, "fe"}) }), 
    "mf" :  ({ ({1, "bm"}), ({2, "zk"}), ({4, "fe"}), ({2, "ne"}) }),
    "mn" :  ({ ({1, "bm"}), ({4, "zk"}), ({4, "fe"}), ({1, "ne"}) }),
    "nm" :  ({ ({3, "ha"}), ({1, "bm"}), ({2, "zk"}), ({4, "fe"}) }),
    "nf" :  ({ ({1, "bm"}), ({2, "zk"}), ({5, "fe"}), ({1, "mp"}) })
]);

/* 
 * cap_reduction_cures: 
 * The sequence of agents and quantities for each cure of a reduction 
 * in capabilities (a stat). The variable this_potion must match the 
 * appropriate one of these when the potion is drunk from this flask. 
 */  
mapping cap_reduction_cures =
([
    "str" : ({ ({1, "mp"}), ({1, "ne"}), ({4, "fe"}), ({3, "yg"}) }),
    "dex" : ({ ({1, "ne"}), ({4, "fe"}), ({2, "yg"}), ({2, "st"}) }),
    "con" : ({ ({1, "st"}), ({1, "ne"}), ({4, "fe"}), ({2, "yg"}) }),
    "int" : ({ ({1, "mp"}), ({1, "ne"}), ({5, "fe"}), ({2, "yg"}) }),
    "wis" : ({ ({1, "ne"}), ({4, "fe"}), ({2, "yg"}), ({2, "bm"}) }),
    "dis" : ({ ({1, "ne"}), ({5, "fe"}), ({2, "yg"}), ({1, "st"}) })
]);

/* 
 * cap_reduction_cures: 
 * The sequence of agents and quantities for curing stuttering for 
 * each race. The variable this_potion must match the appropriate 
 * one of these when the potion is drunk from this flask. 
 */  
mapping stutter_cures = 
([
   "dwarf" : ({ ({1, "mp"}), ({2, "zk"}), ({1, "ha"}), ({6, "st"}) }),
   "elf" : ({ ({3, "zk"}), ({1, "ha"}), ({4, "st"}), ({2, "bm"}) }),
   "gnome" : ({ ({2, "zk"}), ({1, "ha"}), ({4, "st"}), ({1, "bm"}) }), 
   "goblin" : ({ ({3, "fe"}), ({2, "zk"}), ({1, "ha"}), ({4, "st"}) }),
   "hobbit" : ({ ({1, "yg"}), ({2, "zk"}), ({1, "ha"}), ({4, "st"}) }), 
   "human" : ({ ({2, "zk"}), ({2, "ha"}), ({4, "st"}), ({2, "yg"}) })
]); 


void
reset_potion()
{
    this_potion = ({ ({0, ""}), ({0, ""}), ({0, ""}), ({0, ""}) });
    next_measure = 0;
}


/* Abbreviation for liquid names */
string
liquid_abrv(string l_name)
{
    return extract(l_name, 0, 0) + 
           extract(l_name, strlen(l_name)-1, strlen(l_name)-1);
}


/* 
 * Function stat_string: 
 * string for weakened stat of a particular player. 
 * Used to access the mapping cap_reduction_cures.
 * Returns "void" if no stats weakened.
 */
string
stat_string(object tp)
{
    int w_stat;

    if (!tp->has_weaken_stat_shadow()) return "void";
    w_stat = tp->query_weakened_stat();
    if (w_stat == -1) return "void";
    return SD_STAT_DESC[w_stat];  
}


/* Function: g_change_string
 * string for gender change of a particular player.
 * Used to access the mapping g_change_cures.
 * Returns "void" if player hasn't had gender change.
 */
string
g_change_string(object tp)
{
    int orig_gen, new_gen;
    if (!tp->has_g_change_shadow()) return "void";
    new_gen = tp->query_new_gender();
    if (new_gen == -1) return "void";
    orig_gen = tp->query_orig_gender();

    return extract(tp->qgs(orig_gen), 0, 0) + 
           extract(tp->qgs(new_gen), 0, 0); 
}


/* 
 * Function: race_if_stuttered
 * Returns race of player who has stutter problem,
 * returns "void" if player has no stutter problem. 
 */
string
race_if_stuttered(object tp)
{
    if (present(STUTTER_NAME, tp))
        return tp->query_race();
    else
        return "void";
}


/* 
 * Function: contains_potion. 
 * Called from is_usable_potion and is_right_potion_for_player.   
 * Returns 1 if the "a", the array of possible potions, contains 
 * a particular potion "e". 
 */ 
int
contains_potion(mixed a, mixed e)
{
    int i, j, marker;

    for (i = 0; i < sizeof(a); i++) {
       marker = 1;
       for (j = 0; j < 4; j++) 
           if ((a[i][j][0] != e[j][0]) ||
               (a[i][j][1] != e[j][1]))
              marker = 0;
       if (marker == 1) return 1;
    }

    return 0;
}



/* 
 * Function: is_usable_potion.  
 * Returns 1 if potion is a valid one that may be used as a cure
 * for _something_, not necessarily the right one for this player.
 */
int
is_usable_potion()
{
    mixed g, c, s;

    g = m_values(g_change_cures);
    if (contains_potion(g, this_potion))
        return 1;

    c = m_values(cap_reduction_cures);
    if (contains_potion(c, this_potion))
        return 1;

    s = m_values(stutter_cures);
    if (contains_potion(s, this_potion))
        return 1;

    return 0;
}


/* Returns 1 if potion is right one for player to solve his/her
   side-effect. Mark potion as being right for player object,
   i.e. right_player = tp;
*/
int
is_right_potion_for_player(object tp)
{
    string index;

    index = stat_string(tp);
    if (index != "void") 
        if (contains_potion(({cap_reduction_cures[index]}), this_potion)) 
            return 1;
        else
            return 0;
    index = g_change_string(tp);
    if (index != "void")
        if (contains_potion(({g_change_cures[index]}), this_potion))
            return 1;
        else
            return 0;
    index = race_if_stuttered(tp);
    if (index != "void")
        if (contains_potion(({stutter_cures[index]}), this_potion))
            return 1;
        else
            return 0; 
    return 0;
}


/* Reset flask in alchemist's lab if this one is removed */ 
void
remove_object()
{
    seteuid(getuid());
    (GELAN_ROOMS + "alchemist_lab")->reset_flask();
    if (environment(this_object())->query_prop(ROOM_I_IS))
        tell_room(environment(this_object()), "The " + short() +
                  " breaks as it hits the ground.\n");
    ::remove_object();
}


/* Reset flask if it's dropped */ 
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!living(dest))
        set_alarm(1.0, 0.0, "remove_object");
}


void
create_object()
{
    set_name("flask");
    add_name(AQ_FLASK_NAME);
    set_adj("glass");
    set_short("glass flask");
    set_long("@@flask_long");
   
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);

    reset_potion();
}


/* Long description of the glass flask */
string
flask_long()
{
    string str = "A small glass flask, the kind that Raspatoon " +
                 "uses to mix his potions. ";

    if (next_measure == 0) 
        return str + "It is currently empty.\n";
    else if (next_measure == 1)
        return str + "It currently contains some liquid.\n"; 
    else 
        return str + "It currently contains a mixture of " +
                     "some liquids.\n";
}


/* Hurt someone as damage from explosion */
void
hurt(object *people)
{
    int i;
    string nm;

    if (!sizeof(people)) return;
 
    for (i = 0; i < sizeof(people); i++) {
        people[i]->catch_msg("You are severely hurt!\n");
        people[i]->heal_hp(-(AQ_EXPLOSION_DAMAGE_BASE + 
                             random(AQ_EXPLOSION_DAMAGE_BASE)));
        if (people[i]->query_hp() < 1) { 
             nm = people[i]->query_name();
             people[i]->do_die(this_object());
             log_file("alchemist_quest", nm + 
                       " killed by explosion.\n");
        }
    }
}


/* 
 * Explode the potion, doing damage to anyone in the room at the time.
 */
void
do_explode()
{
     object e = environment(this_object());
     object aroom, r; 

     if (living(e)) {
         tell_object(e, "The " + short() + " explodes!\n");
         tell_room(environment(e), "The " + short() + " held by " +
                   QTNAME(e) + " explodes!\n", e);
     }
     else
         tell_room(e, "The " + short() + " explodes!\n"); 

     hurt(FILTER_LIVE(all_inventory(environment(e))));

     seteuid(getuid()); 
     tell_room(aroom = (GELAN_ROOMS+"alchemist")->get_this_object(), 
               "You hear an explosion from the laboratory.\n"); 
    
     if (objectp(r = present("raspatoon", aroom))) {
         switch (random(5)) {
             case 0 : r->command("chuckle"); 
                      r->command("shout Having fun in there?"); 
                      break;
             case 1 : r->command("grumble"); 
                      r->command("shout Mind you don't break anything valuable."); 
                      break;
             case 2 : r->command("grimace"); 
                      r->command("shout I know how that feels.");
                      break;
             case 3 : r->command("ponder"); 
                      r->command("shout Better luck next time!"); 
                      break;
             default : 
                      r->command("wince"); 
                      r->command("shout That sounded painful.");  
                      break;
         }
     } 

     remove_object(); 
}



/* Empty away contents of the flask. */
int
do_empty(string str)
{
    object tp = this_player();
    int m, s;
    string a, agent;
    object o;

    if (!str) {
        notify_fail(EMPTY_NF);
        return 0;
    }

    if (!parse_command(str, AN_ALL_INV(tp), "%o", o) 
        || (o != this_object()))  {
        notify_fail(EMPTY_NF);
        return 0;
    }

    if (environment(this_object()) != tp)  {
        notify_fail("You do not have the " + short() + ".\n");
        return 0;
    }

    if (next_measure == 0) {
        notify_fail("But the " + short() + " is empty!\n");
        return 0;
    }

    tell_room(environment(tp), QCTNAME(tp) + " empties " + 
              "away the contents of the " +  short() +
              ".\n", tp);
    tell_object(tp, "You empty away the contents of the " + 
                    short() + ".\n");

    reset_potion();
    return 1;
}



/* 
   Poison player for mixing and drinking a potion that was not
   the right one.
*/
void
do_poisoning(object tp)
{
    object p;

    if (!living(tp)) return;

    tell_object(tp, "That was not the right potion for you!\n");
    seteuid(getuid());
    p = clone_object(GELAN_OBJECTS + "potion_poison");
    p->move(tp);
    p->start_poison();  
}



/* Remove side-effects from a player */
void
remove_side_effect(object tp)
{
    object s;

    tell_object(tp, "Aha! Looks like you drank the right potion!\n");

    if (tp->has_weaken_stat_shadow()) 
        tp->destruct_weaken_stat_shadow();
    else if (tp->has_g_change_shadow()) 
        tp->trans_back();
    else if (s = present(STUTTER_NAME, tp))
        s->remove_object();
}


/* Pour a liquid into the flask */
int
do_pour(string str)
{
    object tp = this_player();
    int m, s;
    string a, agent;
    object o;

    if (!str) {
        notify_fail(POUR_NF);
        return 0;
    }

    if (!parse_command(str, AN_ALL_INV(tp), 
                      "%d [measures] / [measure] [of] %w [into] %o", m, a, o)
        || (o != this_object()))  {
        notify_fail(POUR_NF);
        return 0;
    }

    if (environment(this_object()) != tp)  {
        notify_fail("You do not have the " + short() + ".\n");
        return 0;
    }

    agent = lower_case(a);
         
    if (!agents[agent] ||
        (file_name(environment(tp)) != GELAN_ROOMS + "alchemist_lab")) {
        notify_fail("You can't find any " + a + " here.\n");
        return 0;
    }
     
    if (tp->query_skill(SS_LANGUAGE) < AQ_LANGUAGES_MIN) {
        notify_fail("You have no idea what " + a + " is!\n");
        return 0;
    } 


    tell_room(environment(tp), QCTNAME(tp) + " pours " + m + 
              (m == 1 ? " measure " : " measures ") +  
              "of some liquid into the " +  short() +
              ".\n", tp);
    tp->catch_msg("You pour " + m + (m == 1 ? " measure " : " measures ") +
              "of " + a + " into the " + short() + ".\n");

    /* 
     * Explode the flask if too many chemicals are poured in it 
     */ 
    if (next_measure > 3) {
         do_explode(); 
         return 1;
    }

    /* 
     * If someone is pouring in a bit more of that they last 
     * poured in, e.g. 2 measures of zn just after 2 measures of 
     * zn, update the last measure, otherwise add the next measure. 
     */ 
    if (next_measure && (agents[agent] == this_potion[next_measure-1][1])) 
        this_potion[next_measure-1][0] += m;  
    else 
    {
        this_potion[next_measure] = ({ m, agents[agent] });
        next_measure++;    
    } 


    if (next_measure > 3) {
        if (is_usable_potion())
            return 1;  
        do_explode();
        return 1;
    }


    return 1;
}



/* 
 * Drink contents of the flask 
 * This will cause poisoning if the mixed potion is not the 
 * correct cure for their side-effect. 
 */
int
do_drink(string str)
{
    object tp = this_player();
    int m, s;
    string a, agent;
    object o;

    if (!str) {
        notify_fail(DRINK_NF);
        return 0;
    }

    if (!parse_command(str, AN_ALL_INV(tp), 
                      "[potion] [from] %o", o)
        || (o != this_object()))  {
        notify_fail(DRINK_NF);
        return 0;
    }

    if (environment(this_object()) != tp)  {
        notify_fail("You do not have the " + short() + ".\n");
        return 0;
    }

    if (next_measure == 0) {
        notify_fail("But the " + short() + " is empty!\n");
        return 0;
    }
     
    tell_room(environment(tp), QCTNAME(tp) + " drinks the " + 
              "contents of the " +  short() +
              ".\n", tp);
    tp->catch_msg("You drink the contents of " +  
              "the " + short() + ".\n");

    if (!is_right_potion_for_player(tp)) {
         do_poisoning(tp); 
         reset_potion();
         return 1;
    }

    reset_potion();

    remove_side_effect(tp);
    tp->add_prop(AQ_CURE_SUCCESS, 1);

    if (tp->test_bit(AQ_DOM, AQ_GROUP, AQ_BIT)) 
        return 1;

    tp->set_bit(AQ_GROUP, AQ_BIT);
    tp->add_exp(AQ_XP); 
    tp->command("save");
    tp->catch_msg("You feel more experienced!\n");
    log_file("alchemist_quest", tp->query_name() + " solved " +
             "alchemist quest: " + ctime(time()) + ".\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(do_pour, "pour");
    add_action(do_empty, "empty");
    add_action(do_drink, "drink");
}

