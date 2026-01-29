/* Village Militaman
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/97    Created
*/
#include "defs.h"
inherit ARGOSNPC;
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "maleadj.h"
 
void create_monster() {
    if (!IS_CLONE) return;
    string adj=MALE_ADJ[(random(sizeof(MALE_ADJ)))];
    set_name("militiaman");
    add_name("guard");
    set_adj(adj);
    set_race_name("human");
    set_short(adj+" militiaman");
    set_pshort(adj+" militiamen");
    set_long(
        "He is a member of the village militia, recently armed and trained "+
        "by the Argoisan military. Assigned to guard the village, he looks "+
        "a little inexperienced but determined.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ARGOS_ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(15);
    add_act("emote glances down the streets.");
    add_act("emote nods his head slightly at you.");
    add_act("emote straightens his body stiffly.");
    add_act("emote stares stoically straight ahead.");
    add_act("emote glances at you suspiciously.");
 
    set_cact_time(5);
    add_cact("shout Its foreigners like you who cause all this trouble!");
    add_cact("shout You'll never make it out of the village alive!");
    add_cact("emote glares at you murderingly.");
    add_cact("shout Pray to your false gods that your death will be swift!");
    add_cact("shout May the Light burn you to a crisp!");
    add_cact("shout May the Light have mercy on your damned soul!");
 
    set_stats(({ 80, 80, 80, 40, 40, 80})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);
    set_hp(15000);
    set_alignment(300);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
 
    set_intro_resp(({"emote nods at you in acknowledgement."}));
    set_equip_dir(CHORIO_DIR);
    set_equip(({"armours/mmail","armours/mhelmet","weapons/msword"}));
}
