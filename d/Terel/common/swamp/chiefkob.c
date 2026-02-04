/*
 a kobold chief for the swamp redhawk 921103
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define WEP_DIR "/d/Terel/common/swamp/"

create_monster()
{
    if (!IS_CLONE)
        return;

set_name("kobold");
add_name("chief");
set_adj("dominant");
add_adj("rude");
    set_long(break_string(
  "A kobold chief that looks a bit more intelligent than the other kobolds. " +
 " \n", 70));
set_adj("dirty");
set_race_name("kobold");
    set_gender(0);
set_alignment(-10);

set_stats(({50,40,30,10,10,10}));
set_hp(5000);
set_skill(SS_DEFENCE, 50 + random(5));
set_skill(SS_UNARM_COMBAT, 35 + random(5));
set_skill(SS_PARRY, 55 + random(5));
set_skill(SS_WEP_SWORD, 50 + random(5));

set_all_hitloc_unarmed(15);
set_all_attack_unarmed(15, 15);


    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {

    seteuid(getuid(this_object()));

clone_object(WEP_DIR + "dirty_sword") -> move(this_object());

    command("wield weapons");
    command("smile");
}
