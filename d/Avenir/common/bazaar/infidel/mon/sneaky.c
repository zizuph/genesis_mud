// Infidel that sneaks around bazaar
// creator(s): Ilyian, October 1995
// purpose: Holds the key to the hideout
//
// 	Lucius Apr 2009: Added monster_home to help prevent
// 		getting stuck.
//
#pragma strict_types

inherit "/d/Avenir/inherit/monster";

#include "../infidel.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

string sneak_away();

void
create_monster()
{
    ::create_monster();

    set_name("amestio");
    set_living_name("amestio");
    add_name(({"infidel", "avenir_infidel_id"}));
    set_adj("frightened");
    set_race_name("human");
    set_gender(G_MALE);
    set_short("frightened human");
    set_long("This is a small and wiry human, who looks "
      +"like he is trying to avoid being seen.\n");

    set_stats(({ 70,65,85,90,57,84 }));

    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 60 + random (30));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_HIDE, 40);
    set_skill(SS_SNEAK, 40);
    set_skill(SS_UNARM_COMBAT, 76);
    set_skill(SS_BLIND_COMBAT, 50 );

    NEVERKNOWN;

    set_restrain_path("/d/Avenir/common/bazaar/extr");
    set_monster_home("/d/Avenir/common/bazaar/extr/str4");

    set_act_time(2);
    add_act("@@sneak_away");

    MAKE_INFIDEL;
}

void
arm_me()
{
    int i = random(3) + 2;

    while(i--)
	clone_object(OBJ+"globe")->move(TO);

    clone_object(OBJ+"infidel_key")->move(TO);
    command("wimpy at death's door");
}

string
sneak_away()
{
    string *directions = ENV(TO)->query_exit_cmds();

    if (sizeof(directions))
	command("sneak "+ directions[random(sizeof(directions))]);

    return "";
}

int
special_attack(object enemy)
{
    string *strs;

    if (!random(3) || !present("globe") ||
	query_hp() > query_max_hp() / 2)
    {
	return 0;
    }

    command("break globe");
    strs = ENV(TO)->query_exit_cmds();
    if (sizeof(strs))
	command(one_of_list(strs));

    return 1;
}

void
init_living()
{
    ::init_living();

    // don't get stuck in no attack rooms
    if (environment()->query_prop(ROOM_M_NO_ATTACK))
	set_alarm(3.0, 0.0, run_away);
}

