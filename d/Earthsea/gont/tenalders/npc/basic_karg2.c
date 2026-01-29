inherit "/d/Earthsea/std/monster.c";
inherit "/d/Earthsea/lib/width_height";

#include "karg.h"

#include "/sys/macros.h"
#include "/sys/money.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "defs.h"

inherit AUTO_TEAM;

void create_karg();
int set_levels(int level);
int check_player();



void
create_karg()
{
    string desc, d1, d2;

    ::create_earthsea_monster();

    d1 = desc1[random(sizeof(desc1))];
    d2 = desc2[random(sizeof(desc2))];
    desc = d1 + " " + d2 + " warrior";
    set_name("warrior");
    add_name("karg");
    set_gender(G_MALE);
    set_race_name("human");
    set_height("tall");
    set_width("normal");
    set_adj(d1);
    add_adj(d2);
    set_short(desc);
    set_long(break_string("A "+ desc + ". One of the ruthless "+
	"band of Karg invaders. Fair of skin with long yellow hair, "+
	"these fierce warriors are very tough opponents.\n", 70));

    set_aggressive("@@check_player");
    set_act_time(50);
    add_act("emote frowns savagely.");
    add_cact("shout Wuluah! Atwah!");
    add_cact("emote yells a warcry!");
}

int
set_levels(int level)
{
    int *x = allocate(6);

    int skill, i;

    i = sizeof(x);
    // set stat levels using formula
    while (i--)
    {
	x[i] = levels[level] + random(23);
    }

    TO->set_stats(({ x[0], x[1], x[2], x[3], x[4], x[5] }));

    TO->set_alignment(-1 * (random(levels[level])) / 5);
    TO->set_hp(query_max_hp());
    TO->set_all_hitloc_unarmed(1);


    // set stat levels using formula and levels from karg.h

    for (i = 0; i < sizeof(x); i++)
    {
	if (level < 4)
	    x[i] = levels[level] + random(5);
	else
	    x[i] = (levels[level] / 3) * 2 + random(20);
    }

    TO->set_skill(SS_DEFENCE, x[0]);
    TO->set_skill(SS_WEP_AXE, x[1]);
    TO->set_skill(SS_WEP_CLUB, x[1]);
    TO->set_skill(SS_PARRY, x[2]);
    TO->set_skill(SS_BLIND_COMBAT, x[3]);
    TO->set_skill(SS_WEP_SWORD, x[4]);
    TO->set_skill(SS_WEP_POLEARM, x[5]);
    TO->set_skill(SS_AWARENESS, x[5]);
    return 1;
}

int
query_knight_prestige()
{
    return random(25);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

int
attacked_by(object player)
{
    object *other_kargs;
    int i;

    other_kargs = TO->query_team_others();
    if (sizeof(other_kargs))
    {
	for ( i = 0; i < sizeof(other_kargs); i++)
	{
	    (other_kargs[i])->command("kill "+
	      lower_case(player->query_name()));
	}
	other_kargs[0]->command("shout Quit hitting on my buddy here!");
    }
    return 0;
}

int
check_player()
{
    object tp = this_player();

    // don't autoattack newbies
    if (tp->query_average_stat() > 50)
	return 1;

    return 0;
}
