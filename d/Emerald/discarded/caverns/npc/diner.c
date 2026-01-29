inherit "/std/monster.c";
#include "defs.h"
#define WEP CAVERNS_DIR+"arm/rnd_weapon"
#define ARM CAVERNS_DIR+"arm/rnd_cloak"

string face();
void
create_monster()
{
    if (!IS_CLONE)
	return;
    set_race_name("pirate");
    add_adj(face());
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_long("You have interrupted his dinner. He looks "+
      "quite upset.\n");
    set_stats(({ random(30)+60, random(30)+60, random (30)+60,
	20,20,100}));
    set_hp(5000);
    set_skill(SS_DEFENCE, random(20)+50);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_SWORD, random(20)+50);
    set_skill(SS_AWARENESS, random(40)+40);
    set_skill(SS_UNARM_COMBAT, 60);
    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me", "grin"}));
    init_living();
}

face()
{
    string *faces;
    faces = ({"dirty", "dingey", "piggish", "fat","wolfish",
      "lithe", "dangerous", "murderous", "bloodthirsty",
      "evil", "scarred", "foul-mouthed", "rude"});
    return faces[random(sizeof(faces))];
}

arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));
    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield rapier");
    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear cloak");
}

void
init_living()
{
    object apron;
    apron = present("dirty_apron", this_player());
    if(apron) {
	if(apron->query_worn()==this_player())
	    monster_aggressive=1;
    }
    else monster_aggressive=0;
    ::init_living();
}
