// head of the tribesman clan
// has heal and mesmorize ability
// staff used in emotes but add emote saying staff vanishes to his do_die (we don't want to make thi
// and put it in mortal hands )

inherit "/std/monster.c";

#include "/d/Wiz/triana/defs.h"
#include <language.h>
#include "money.h";


void
create_monster()
{
    set_name("tribesman");
    add_name("chief");
    add_name("tribeman");
    add_name("man");
    set_short("chief tribesman");
    set_race_name("human");
    set_gender(G_MALE);
    set_alignment(900);
    set_adj("tall");
    add_adj("chief");

    set_alignment(660);
    set_stats( ({ 135, 175, 155, 145, 145, 130 }) );
    set_hp(query_max_hp());


    set_cact_time(4);
    add_cact("@@heal_me");
	add_cact("@@specials");
}

string
heal_me()
{
    heal_hp(random(500) + 300);
    command("emote calls on his gods to cleanse him of his wounds.");
    command("emote is partially healed");
    return "";
}

specials()
{
	object me;
	string how;
	int damage, swing_type;
	string *part = ({"knee", "elbow", "fist", "foot", "staff"});
	string *area = ({"stomach", "chest", "head", "legs", "arms"});
	me = this_object();

	damage = random(150) - enemy->query_skill(SS_DEFENCE);
	swing_type = random(4);

	if (damage < 0)
	damage = random(80);

	how = bumping;
	if (damage > 10);
	how = "grazeing";
	if (damage > 35);
	how = "hurting";
	if (damage > 70)
	how = "bashing");
	if (damage > 100)
	how = "smashing";
	if (damage > 190)
	how = "crushing";
}

