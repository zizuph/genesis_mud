/* 
 * /d/Kalad/common/wild/pass/npc/deep_rothe.c
 * Purpose    : A wild animal in the deep caves.
 * Located    : /d/Kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: Nikklaus, July'97:  Some cosmetic changes, dropped dis to
 *               that typical of kine, increased con for more hp and sturdiness,
 *               and switched inherit to appropriate standard for an animal.
 */ 

inherit "/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
/* by Antharanos */
#define A_BITE 0
#define A_LHOOF 1
#define A_RHOOF 2
#define A_HORNS 3
#define H_HEAD 0
#define H_BODY 1
create_monster()
{
    set_name("rothe");
    set_race_name("rothe");
    set_adj("deep");
    set_pshort("deep rothe");
    set_long("A small yet powerfully built creature, it stands only four "+
      "feet high at the shoulder but is nearly that many feet in width. It "+
      "is covered in a deep purple fur and possesses greenish-black horns.  All "+
      "in all it looks something like a musk oxen.\n");
    set_stats(({80,60,100,25,25,15}));
    set_skill(SS_DEFENCE,50);
    set_skill(SS_UNARM_COMBAT,30);
    set_act_time(6);
    add_act("emote makes a strange gesture with its head.");
    add_act("emote grunts.");
    set_gender(G_NEUTER);
    set_random_move(10);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(OBJ_I_WEIGHT,125000);
    add_prop(OBJ_I_VOLUME,125000);
    add_prop(OBJ_I_NO_INS,1);
    set_attack_unarmed(A_BITE, 25, 25, W_BLUDGEON, 20, "jaws");
    set_attack_unarmed(A_LHOOF, 35, 35, W_BLUDGEON, 30, "left hoof");
    set_attack_unarmed(A_RHOOF, 35, 35, W_BLUDGEON, 30, "right hoof");
    set_attack_unarmed(A_HORNS, 30, 30, W_IMPALE, 20, "curved horns");
    set_hitloc_unarmed(H_HEAD, ({ 20, 20, 25 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 25, 25, 35 }), 80, "body");
}
