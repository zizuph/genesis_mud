/* An old  servant in the Temple of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/10/95    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"slvtunic")->move(this);
    clone_object(WEAPON_DIR+"woodspn")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"old servant","servant","woman","human","old woman"}));
    set_adj("servant");
    set_adj("old");
    set_race_name("woman");
    set_short("old servant woman");
    set_long(
        "She is an old woman with short gray hair and stern brown "+
        "eyes. She is dressed in the tunic of a servant of the temple.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_gender(1); /* female */
    set_act_time(7);
    add_act("say This mess must be cleaned up by tonight!");
    add_act("say Food tasted better before we had these new pots.");
    add_act("say Our guests will enjoy my bachlava, "+
            "its an old family recipe.");
    add_act("say are you hear to bring the meat for the banquet?");
    add_act("emote checks on the food in the pots.");
    add_act("emote stirs a pot with her wooden spoon.");
    add_act("emote puts her hands on her hips and gives you a mean look.");
    add_act("say You are in the way here, move along.");
    add_act("emote sighs tiredly.");
 
    set_cact_time(3);
    add_cact("say What have I done to you?");
    add_cact("say May Arxes protect me!");
    add_cact("emote holds a hand over her face to deflect the blows.");
    add_cact("emote cries in terror.");
    add_cact("emote sobs I'll never see my children again!");
 
    set_stats(({ 10, 10, 10, 10, 10, 10})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_CLUB, 10);
    set_skill(SS_PARRY, 10);
    set_skill(SS_DEFENCE, 10);
    set_hp(10000);
    set_alignment(150);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
