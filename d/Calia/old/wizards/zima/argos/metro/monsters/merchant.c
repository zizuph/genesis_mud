/* ARGOS - metro - shop keeper (Katasemas)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/5/95   Created
** Maniac        11/9/95   Polymorph quest additions
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Calia/mountain/special/polymorph_quest.h"

int jewel_alarm; 


string *intro_resp_cmd=(({
   "introduce myself","say See anything you like? I'll make you a bargain!",
   "smile greedily"}));
#include "defs.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    command("wear all");
    command("wield all");
}
 

/* Reply to enquiry about sapphire of draining. */
string
reply()
{
    object tp = this_player();
    int price;

    if (!tp)
        return "";

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT))
         return "say I don't know what you're talking about.";

    if (present(CORPSE_NAME, tp))
        return ("say I don't know what you're talking about.");

    if (present(JEWEL_NAME, tp))
        return ("say What would you want with another one?");

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) 
         if (jewel_alarm)
             return ("say I had a sapphire of draining not so long ago, " +
                       "but I've sold it for a good price I'm afraid.");
         else {
             price = (tp->query_average_stat() * 50);
             return ("say It so happens that I have a sapphire of draining " +
                "in my possession. It was very difficult to obtain, so I'm " +
                "expecting to get a great price for it. For you, " +
                price + " copper. If you are interested, you may try " +
                "to <purchase> it.");
         }

    return ("peer " + tp->query_real_name());
}



/* Attempt to purchase sapphire of draining */
int
purchase()
{
    object tp = this_player();
    int price;

    if (!tp)
        return 0;

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT))
         return 0;

    if (present(CORPSE_NAME, tp))
        return 0;

    if (present(JEWEL_NAME, tp)) {
        command("say Why would you want to purchase another one?");
        return 1;
    }

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON))
         if (jewel_alarm) {
             command("say I had a sapphire of draining not so long ago, " +
                       "but I've sold it for a good price I'm afraid.");
             return 1;
         }
         else {
             price = (tp->query_average_stat() * 50);
             if (MONEY_ADD(tp, -price)) {
                 seteuid(getuid());
                 /* Moving it because it's OBJ_M_NO_GIVE. */
                 tp->catch_msg("You pay the large sum to " + 
                                QTNAME(this_object()) + ".\n");
                 tell_room(environment(this_object()), QCTNAME(tp) + 
                     " pays a large sum to " + QTNAME(this_object()) + 
                     ".\n", tp);
                 clone_object(PQ_JEWEL)->move(tp);
                 tell_room(environment(this_object()), QCTNAME(this_object()) + 
                     " obtains a mysterious jewel from a hiding place and " +
                     "gives it to " + QTNAME(tp) + ".\n", tp);
                 tp->catch_msg(QCTNAME(this_object()) + " obtains a " +
                     "mysterious jewel from a hiding place and gives it to " +
                     "you.\n");
                 jewel_alarm = set_alarm(3600.0, 0.0, "another_jewel");
                 command("emote smiles wealthily.");
                 return 1;
             }
             else {
                 command("say It looks like you can't afford my price."); 
                 return 1;
             }
         }
    return 0;
}


void
another_jewel()
{
    jewel_alarm = 0;
}


void create_monster() {
    if (!IS_CLONE) return;
    set_name("Katasemas");
    add_name(({"katasemas","merchant","shopkeeper"}));
    set_title("Merchant of Argos");
    set_adj(({"skinny","bald"}));
    set_race_name("human");
    set_long(
        "He is the proprietor of the Emporium of Argos, a gaunt aging "+
        "man with gray eyes that gleam with shrewdness and greed. " +
        "He looks very eager to do business with you.\n");
 
    jewel_alarm = 0;
    set_act_time(5);
    add_act("greet all");
    add_act("emote smiles greedily");
    add_act("say Have you anything you would like to sell?");
    add_act("say I have very fine wares...perhaps you buy, yes?");
    add_act("say Have you visited Alexis in the park?");
    add_act("emote studies you with greed in his eyes.");
    add_act("emote counts on his fingers as he looks over his inventory.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say it's outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({50,50,50,50,50,50}));
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(15000);
    set_alignment(-60);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);

    add_ask(({"jewel", "sapphire", "sapphire of draining",
              "magic jewel", "magic sapphire", "magical jewel", 
              "magical sapphire"}),
              VBFC_ME("reply"), 1);
}
 

void 
init_living()
{
    ::init_living();
    add_action("purchase", "purchase"); 
}

