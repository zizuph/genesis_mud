/* A small mythological woodland creature; easy prey for newbies
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           2/17/95    Created
** Zima           2/21/95    Rewritten as humanoid; with 2 goat legs (not 4)
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
#define weapon ({"satclub","satsword","satstaff"})
#define color ({"white","black","gray","brown","red"})
 
void equip_me() {
    object this=this_object();
    object wep,sflute,sring,sshield,scloak,sbelt,sloin,heap;
    string wepname;
	
    heap = MONEY_MAKE_GC(2);
    heap->move(this_object());
 
    wepname=weapon[(random(sizeof(weapon)))];
    wep=clone_object(WEAPON_DIR+wepname);
    sflute=clone_object(OBJ_DIR+"sflute");
    sring=clone_object(ARMOUR_DIR+"satring");
	sshield=clone_object(ARMOUR_DIR+"satshield");
	scloak=clone_object(ARMOUR_DIR+"satcloak");
	sbelt=clone_object(ARMOUR_DIR+"satbelt");
	sloin=clone_object(ARMOUR_DIR+"satloin");
    wep->move(this);
    sflute->move(this);
	sring->move(this);
	sshield->move(this);
	scloak->move(this);
	sbelt->move(this);
	sloin->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    string hair   = color[(random(sizeof(color)))];
    string fleece = color[(random(sizeof(color)))];
    string adj1   = hair+"-haired";
    string adj2   = fleece+"-fleeced";
 
    set_name("satyr");
    add_adj(({adj1,adj2}));
    set_short(adj1+" "+adj2+" satyr");
    set_race_name("satyr");
    set_long(
        "It is a mysterious forest creature which has the upper body of "+
        "a human with the legs of a goat covered in curly "+fleece+" fleece. "+
        "Two small horns portrude through its "+hair+" hair, and it "+
        "stares at you with sinister elven eyes. It is holding a small "+
        "reed flute in one hand.\n");
 
    add_prop(ATTACK_TEAM,"_satyr_attack_team");
    set_stats(({30,30,30,30,30,30}));
 
    set_hp(1000);
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_WEP_SWORD, 25);
    set_skill(SS_WEP_POLEARM, 25);
    set_skill(SS_WEP_CLUB, 25);
 
    set_alignment(-3);
    set_act_time(10);
    add_act("emote paws the ground with its right hoof.");
    add_act("emote snickers sinisterly.");
    add_act("emote giggles inanely.");
    add_act("emote chuckles deviously.");
    add_act("emote plays an enchanting melody on its flute.");
    add_act("emote tosses its flute up in the air and catches it.");
    add_act("emote jumps up in the air playfully.");
    add_act("emote crosses its arms.");
    add_act("emote scratches its head.");
 
    set_cact_time(5);
    add_cact("emote charges with its horns.");
    add_cact("emote kicks violently with its hooves.");
    add_cact("emote glares with murder in its eyes.");
    add_cact("emote hisses loudly.");
 
    add_prop(CONT_I_WEIGHT,  30000);
    add_prop(CONT_I_VOLUME,  30000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
