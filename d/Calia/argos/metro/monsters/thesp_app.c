/* ARGOS City - Apprentice of the Thespian Guild
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
string *intro_resp_cmd=(({"introduce myself","emote bows humbly."}));
#include "defs.h"
#include "citizen.h"
#include "names.c"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+"thbroom")->move(this);
    clone_object(ARMOUR_DIR+"app_thesp_robe")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    string Name=random_name();
    string Adj1=(MaleAdj[(random(sizeof(MaleAdj)))]);
    string Adj2="young";
 
    if (!IS_CLONE) return;
    set_name(Name);
    add_name(({(lower_case(Name)),"thespian","argosian"}));
    set_title("Apprentice Thespian");
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    set_alignment(50);
    set_long(
        "He is a "+Adj1+" "+Adj2+" apprentice of the Thespian Guild, "+
        "learning the skills needed to act on the stage of the "+
        "Amphitheatre. He is sweeping the ground, which seems a little "+
        "strange. It must be part of his training.\n");
 
 
    set_act_time(5);
    add_act("emote sweeps the ground with his broom.");
    add_act("emote sweeps the ground with his broom.");
    add_act("emote sweeps the ground with his broom.");
    add_act("emote stops sweeping to rest a moment.");
    add_act("emote glances at you suspiciously.");
    add_act("emote stares at you puzzled.");
 
    set_cact_time(3);
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say may your head be chopped off!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({20,20,20,20,20,20}));
    set_skill(SS_PARRY, 20);
    set_skill(SS_WEP_POLEARM, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
