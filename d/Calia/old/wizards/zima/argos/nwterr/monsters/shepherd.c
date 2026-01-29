/*      A shepherd
 
    coder(s):   Zima  11/21/93
 
    history:
 
    purpose:    tend sheep
    objects:    none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/
inherit "/std/monster";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
 
void
equip_me()
{
    object this;
    string type;
 
    seteuid(getuid());
 
    this = THIS;
    clone_object(WEAPON_DIR+"staff")->move(this);
    command("wield staff");
    clone_object(ARMOUR_DIR+"shtunic")->move(this);
    command("wear tunic");
}
 
void
create_monster()
{
    if (!IS_CLONE) return;
    set_name(({"the shepherd","shepherd"}));
    set_adj("dirty");
    set_race_name("human");
    set_short("shepherd");
    set_long(break_string(
        "A simple agrarian who spends his life tending to his flock.  " +
         "He is wearing a long, dirty white tunic, soiled with his daily " +
        "activities.  He doesn't smell so good.\n",70));
    /* add team support so he attacks anyone who attacks his sheep */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);

 
    set_act_time(10);
    add_act("emote leans on his staff.");
    add_act("giggle");
    add_act("whistle");
    add_act("emote scans the horizon for wolves.");
    add_act("north");
    add_act("south");
    add_act("east");
    add_act("west");
 
    set_base_stat(SS_INT, 20);
    set_base_stat(SS_WIS, 20);
    set_base_stat(SS_DIS, 20);
    set_base_stat(SS_STR, 20);
    set_base_stat(SS_DEX, 20);
    set_base_stat(SS_CON, 20);
    set_base_stat(SS_OCCUP, 20);
    set_skill(SS_WEP_POLEARM, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(7500);
    set_alignment(15);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    equip_me();
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
