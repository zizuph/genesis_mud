/*
a ghost for the mansion graveyard 921022 Redhawk
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

create_monster()
{

set_name("ghost");
set_short("ghost");
    set_long(break_string(
 "Its a ghost or at least you think it is, its a bit hard to tell it looks " +
 "like the ghost is floating in mid air \n", 70));
set_adj("evil");
    set_gender(0);
set_alignment(-50);

set_race_name("ghost");
add_prop(LIVE_I_UNDEAD, 20);
set_stats(({20,20,20,20,25,25}));
set_hp(3333);
set_skill(SS_DEFENCE, 40 + random(5));
set_skill(SS_UNARM_COMBAT, 35 + random(5));
set_skill(SS_PARRY, 40 + random(5));

set_all_hitloc_unarmed(15);
set_all_attack_unarmed(50, 50);

    set_chat_time(20);
add_chat("go further and you end up like me");
add_chat("your soul will be doomed to walk on the earth for eternity");

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {

    seteuid(getuid(this_object()));


    command("sigh","grin");
}
