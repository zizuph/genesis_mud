/*      A vineyardsman
 
    coder(s):   Zima  11/21/93
 
    history:
 
    purpose:    tends to vineyard
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
    clone_object(WEAPON_DIR+"vmknife")->move(this);
    command("wear knife");
    clone_object(ARMOUR_DIR+"vmtunic")->move(this);
    command("wield tunic");
}
 
void
create_monster()
{
    if (!IS_CLONE) return;
    set_name(({"the vineyardsman","vineyardsman","keeper"}));
    set_adj("tall");
    set_race_name("human");
    set_short("vineyardsman");
    set_pshort("vineyardsmen");
    set_long(break_string(
        "A local agrarian who tends to the vineyards, growing and " +
        "picking sweet grapes.  He is wearing a grape-stained tunic " +
        "and is cutting away some weeds near the grapevines.\n",70));
 
    set_act_time(10);
    add_act("emote chops up some weeds with his knife.");
    add_act("smile");
    add_act("yawn");
    add_act("emote examines a bunch of grapes hanging on the vines.");
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
    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(7500);
    set_alignment(150);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    equip_me();
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
