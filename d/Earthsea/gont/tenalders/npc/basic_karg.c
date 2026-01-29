#pragma strict_types

inherit "/d/Earthsea/std/monster";
/* The karg captains need this */
inherit "/d/Earthsea/lib/team_protect";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Krynn/open/auto_teaming";

#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

#define DESC1 ({"brawny", "tough", "mean", \
    "vicious", "lean", "barbaric", "square-jawed", \
    "ruthless", "tall", "massive", "muscular", \
    "savage", "ferocious", "predatory", \
    "frowning", "aggressive", "bad-tempered", "evil", \
    "proud", "fierce"})
#define DESC2 ({"yellow-haired", "long-haired", \
    "blue-eyed", "hawk-eyed", "Roman-nosed", \
    "bearded", "mustachioed", "tattooed", \
    "long-haired", "grizzled", "weathered", \
    "scarred", "hairy", "barrel-chested", \
    "white-skinned"})
#define LEVELS ({ 25, 30, 45, 65, 95, 110, 120 })

public void create_karg() { }

public nomask void
create_earthsea_monster()
{
    string d1 = DESC1[random(sizeof(DESC1))],
        d2 = DESC2[random(sizeof(DESC2))];
    set_name("warrior");
    add_name("karg");
    add_name("__es_basic_karg__");
    set_pick_up_team("__es_basic_karg__");
    set_race_name("human");
    set_height("tall");
    set_width("normal");
    set_adj(d1);
    add_adj(d2);
    set_short(d1 + " " + d2 + " warrior");
    set_long("@@my_long");
    set_aggressive("@@check_player");
    set_act_time(50);
    set_cact_time(120);
    add_act("emote frowns savagely.");
    add_cact("shout Wuluah! Atwah!");
    add_cact("emote yells a warcry!");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    create_karg();
}

public string
my_long()
{
    object attacker, tp = this_player(), to = this_object();
    string desc = query_The_name(to);

    if(objectp(attacker = query_attack()))
    {
        if(attacker == tp)
        {
            desc += " dodges and weaves out of your way determined " +
                "to get beyond your defences.\n";
        } else {
            desc += " is busy dodging and weaving out of " +
                LANG_POSS(attacker->query_the_name(tp)) + " blows.\n";
        }
    } else {
        desc += " is one of the ruthless band of Karg invaders.\n";
    }

    return desc;
}

public void
set_levels(int level)
{
    int *x = allocate(6), skill, i = sizeof(x);

    // set stat levels using formula
    while(i--)
    {
        x[i] = LEVELS[level] + random(23);
    }

    set_stats(({ x[0], x[1], x[2], x[3], x[4], x[5] }));
    set_hp(query_max_hp());
    set_all_hitloc_unarmed(1);

    // set stat levels using formula and levels from karg.h
    for(i = 0; i < sizeof(x); i++)
    {
        if(level < 4)
        {
            x[i] = LEVELS[level] + random(5);
        } else {
            x[i] = (LEVELS[level] / 3) * 2 + random(20);
        }
    }

    set_skill(SS_DEFENCE, x[0]);
    set_skill(SS_WEP_AXE, x[1]);
    set_skill(SS_WEP_CLUB, x[1]);
    set_skill(SS_PARRY, x[2]);
    set_skill(SS_BLIND_COMBAT, x[3]);
    set_skill(SS_WEP_SWORD, x[4]);
    set_skill(SS_WEP_POLEARM, x[5]);
    set_skill(SS_AWARENESS, x[5]);
}

public int
query_knight_prestige()
{
    return random(25);
}

public void
init_living()
{
    ::init_living();
    init_team_pickup();
}

public int
check_player()
{
    object tp = this_player();

    if(tp->query_wiz_level())
    {
        return 0;
    }

    // don't autoattack newbies
    if(tp->query_average_stat() > 50)
        return 1;

    return 0;
}

public void
attacked_by(object player)
{
    int i;
    object *other_kargs = query_team_others();
    ::attacked_by(player);
    for (i = 0; i < sizeof(other_kargs); i++)
    {
	if (!objectp(other_kargs[i]->query_attack()))
	{
	    other_kargs[i]->command("$kill " + 
                lower_case(player->query_name()));
	}
    }
}
