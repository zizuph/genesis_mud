#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/b_pin"
#define PEARL "/d/Genesis/gems/obj/pearl"

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("sailor");
    set_short("drunken sailor");
    set_race_name("human");
    set_long("You look upon the muscular figure of one of " +
      "the many sailors who roam the streets of Flotsam. This " +
      "well-tanned human is in a gawdy garb typical of those " +
      "who sail the Courrain ocean. He also looks like he has " +
      "had one drink too many. His Captain will not be pleased " +
      "at his condition if he manages to get himself back to his " +
      "ship. \n");
    set_stats(({65,55,45,35,35,45}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 30);

    set_alignment(300);
    set_knight_prestige(-80);

    set_act_time(15);
    add_act("hiccup");
    add_act("burp");
    add_act("shout Drinks on the house! hehe...");
    add_act("shout A toast to thee my bestest buddy!");

    add_ask(({"captain","ship"}),
      "say Arg, my captain is one of the foulest bastards "+
      "to sail the sea! But his ship is quite a beauty... "+
      "its the only thing he treats like a lady.",1);
    add_ask(({"drinks","drink"}),
      "say Eh? What did you call my mother?", 1);

}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
    if(random(3) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}
