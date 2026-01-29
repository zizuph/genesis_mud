/*      An olive grove keeper
 
    coder(s):   Zima  11/21/93
 
    history:
 
    purpose:    tends to olive grove
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
    clone_object(WEAPON_DIR+"ogknife")->move(this);
    command("wear knife");
    clone_object(ARMOUR_DIR+"ogtunic")->move(this);
    command("wield tunic");
}
 
void
create_monster()
{
    if (!IS_CLONE) return;
    set_name(({"the olive grove keeper","olive grove keeper","keeper"}));
    set_adj("tall");
    set_race_name("human");
    set_short("olive grove keeper");
    set_long(break_string(
        "This tall agrarian tends to the trees of the olive grove, " +
        "harvesting his crop.  He is pruning the limbs of the trees " +
        "with a long knife.  From the look on his face, he probably "
        + "would prune something from you!\n",70));
 
    set_act_time(10);
    add_act("emote cuts some limbs from an olive tree.");
    add_act("sneer all");
    add_act("glare all");
    add_act("emote wipes his knife on his tunic, smiling at you.");
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
    set_alignment(-150);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
