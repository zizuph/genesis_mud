/* ARGOS - metro - smith - in the forge
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/5/95   Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"emote wipes the sweat from his brow.",
   "introduce myself","emote smiles heartily."}));
#include "defs.h"
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    clone_object(WEAPON_DIR+"czsword")->move(this);
    clone_object(WEAPON_DIR+"fohammer")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Sideras");
    set_name(({"sideras","smith","citizen","blacksmith"}));
    set_title("Blacksmith of Argos");
    set_adj(({"sweaty","muscular"}));
    set_race_name("human");
    set_long(
        "He is the the smith who works in the forge, his well-built "+
        "body covered in sweat from the heat.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    set_act_time(5);
    add_act("emote places the sword in the hot coals.");
    add_act("emote dips the sword in the barrel of water.");
    add_act("emote beats the sword with his hammer.");
    add_act("emote beats the sword with this hammer.");
    add_act("say Do you have anything you would like waxed or sharpened?");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({50,50,50,50,50,50}));
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_WEP_SWORD, 60);
    set_hp(15000);
    set_alignment(20);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
