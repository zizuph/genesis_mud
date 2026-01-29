/* Travelling Merchant - standing on the road through SWTERR next to his wagon
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/12/94  Created
** Zima           12/14/94 Made him killable; added cact's
*/
inherit "/std/monster";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
string *intro_resp_cmd=(({
   "introduce myself",
   "say It would be a pleasure to do business with me, yes?",
   "smile greedily"}));
#include NPC_INTRO_CODE
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Aplestos");
    add_name(({"aplestos","human","merchant"}));
    set_adj("gritty");
    set_adj("bearded");
    set_race_name("merchant");
    set_title("Merchant of Argos");
    set_long(
        "This gritty, bearded man is a travelling merchant, dragging " +
        "his wares around in a wagon, buying and selling mostly junk. " +
        "He is wearing a tattered gray tunic, decorated with tiny shells " +
        "and bright beads. You guess he probably has nothing you want, " +
        "but it wouldn't hurt to find out.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles greedily.");
    add_act("say have you anything you would like to sell?");
    add_act("say I have very fine wares...perhaps you buy, yes?");
    add_act("say have you been to the black temple?");
    add_act("say strangers have been known to get lost around here.");
    add_act("emote studies you with greed in his eyes.");
    add_act("emote leans against the wagon.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("emote locks his wagon.");
    add_cact("say may the Tritheon curse you and all your kind!");
    add_cact("emote begins to pray in terror.");
    add_cact("emote wipes the blood from his face.");
 
    set_stats(({60,60,60,60,60,60}));
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(query_max_hp());
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
string random_thanks() {
   /* random thank you message merchant says at each transaction */
   string *randthanks;
   randthanks = ({
                "It is a pleasure dealing with me, yes?",
                "And may the Tritheon bring you great wealth.",
                "A mutually beneficial transaction, no?",
                "You have gotten a bargain, no?",
                "Perhaps you will come again, yes?",
                "You have a deal, though I shall loose money on this one.",
                "You have something else, yes?"
                });
   return randthanks[random(sizeof(randthanks))];
}
 
void say_random_thanks() {
   this_object()->command("say "+random_thanks());
}
