/* ARGOS City - Member of the Thespian Guild
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/11/95  Created
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"introduce myself","emote bows with a dramatic "+
                          "flair."}));
#include "defs.h"
#include "citizen.h"
#include "names.c"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+"czstaff")->move(this);
    clone_object(ARMOUR_DIR+"thesp_robe")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    string Name=random_name();
    string Adj1=(MaleAdj[(random(sizeof(MaleAdj)))]);
    string Adj2=(NeuterAdj[(random(sizeof(NeuterAdj)))]);
 
    if (!IS_CLONE) return;
    set_name(Name);
    add_name(({(lower_case(Name)),"thespian","argosian"}));
    set_title("Master Thespian");
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    set_alignment(50);
    set_long(
        "He is a "+Adj1+" "+Adj2+" member of the Thespian Guild, "+
        "one of the actors who performs on the stage at the "+
        "Amphitheatre.\n");
 
 
    set_act_time(5);
    add_act("say We'll never get to act until this insurrection is over.");
    add_act("say It's too dangerous to go outside and look for herbs.");
    add_act("say Visitors are in town now and they'll never see our drama.");
    add_act("say There is no need to practice while all is on hold.");
    add_act("emote glances at you suspiciously.");
    add_act("emote stares at you puzzled.");
 
    set_cact_time(3);
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say may your head be chopped off!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({50,50,50,50,50,50}));
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 50);
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
