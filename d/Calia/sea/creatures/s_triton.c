
 /* A swimming Triton for the Calian Sea

    coder(s):    Jaacar

    history:    8.2.96    created          Jaacar

 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <cmdparse.h>
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER

#define A_TAIL  0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

create_creature()
{
    set_name("triton");
    set_short("massive triton");
    set_adj("massive");
    set_race_name("triton");
    set_long("He is a strikingly beautiful creature with long "+
        "black hair. He is human in appearance above the waist, "+
        "but has a large fish-like tail instead of legs. He is "+
        "covered in dark green scales, and has long, sharp claws "+
        "on his webbed fingers. His smile reveals what look like "+
        "very sharp fish teeth.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_alignment(200);
    set_gender(0);
    set_random_move(15);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (THAL),(THALL),(THALM),(THALC),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4))}));
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 75000);
    set_skill(SS_WEP_POLEARM, 85);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_stats(({(random(80)+40),(random(60)+40),(random(60)+40),
        80,80,(random(40)+20)}));
	set_attack_unarmed(A_TAIL,15,25,W_IMPALE,100,"tail");
    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 25, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
}

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

void
equip_me()
{
    object this;

    this = this_object();
    seteuid(getuid(this));
    clone_object("/d/Calia/sea/weapons/gold_trident")->move(this);
    clone_object("/d/Calia/sea/armours/triton_armour")->move(this);
    MONEY_MAKE_GC(5)->move(this);
    command("wield trident");
    command("wear armour");
}


void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("tritons", environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("mermaids", environment()), attacker);
}
