/* The seeker_base, used for the seekers of Haven.
 * 
 * To create a new seeker write a file that looks
 * something like this:
 *
 * include "../local.h"
 * inherit SEEKERBASE;
 * 
 * void
 * create_seeker()
 * {
 *     set_level(3);
 *     add_act("say Have you seen a blue crystal staff?");
 * }
 */

/* 
 * Modifications:
 * Changed from a copy of dwarf_base to accurately represent a seeker,
 *     Tibbit, 16 February 1998
 */

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include "../local.h"

inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void setup_seeker();
int i, level;

//Seeker-specific adjs, Tibbit, 16 Feb 1998
string *adj_list = ({ "tall","short", "skinny","overweight" });
string *adj_list2 = ({ "fanatic","quiet","serious","devoted" });
string adj1, adj2;

int
query_level()
{
    return level;
}

void
set_level(int i)
{
    level = i;
    setup_seeker();
}

void
create_seeker()
{
    if (!level)
      set_level(random(5) + 1);
}

void
setup_seeker()
{
    /* The stats and skills need to be adjusted for the seekers */
    int i;

    //Stats & skills adjusted for Seeker, Tibbit, 16 Feb 1998
    set_base_stat(0, 15 + (query_level() * 5 / 2) +
        0);
    set_base_stat(1, 15 + (query_level() * 5));
    set_base_stat(2, 15 + (query_level() * 5 / 2) +
        0);
    set_base_stat(3, 15 + (query_level() * 5));
    set_base_stat(4, 15 + (query_level() * 5));
    set_base_stat(5, 15 + (query_level() * 5 / 2) +
        0);
    set_skill(SS_DEFENCE, 12 + random(3 * level));
    set_skill(SS_AWARENESS, 12 + random(3 * level));
    set_skill(SS_BLIND_COMBAT, 10 + random(3 * level));
    set_skill(SS_UNARM_COMBAT, 10 + random(3 * level));
}

void
create_krynn_monster()
{
    /* Are there female seekers at all??? */
    //No. :)   Tibbit, 16 Feb 1998
    set_gender(0);

    set_name("human");
    set_race_name("human");
    add_name("seeker");
    set_alignment(random(300));
    adj1 = adj_list[random(sizeof(adj_list))];
	 adj2 = adj_list2[random(sizeof(adj_list2))];

    set_adj(({ adj1, adj2 }));
    set_long("@@long_desc");
    set_short("@@short_desc");

    /* The add_acts need to be adjusted to the Seekers */
    set_act_time(15);
    add_act("smile piously");
    add_act("smile relig");
    add_act("say We seek the new gods.");
    add_act("say The new gods will redeem us.");
    add_act("say The old gods have left us, but the new shall remain.");
    add_act("frown");
    add_act("emote urges everyone to seek the new gods.");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    create_seeker();

    seteuid(getuid(TO));
    set_alarm(0.5, 0.0, "arm_me");
}

void
arm_me()
{
    reset_euid();
    //Seekers carry no weapons.

    clone_object(HARM+"robe")->move(TO);
    command("wear all");

}

string
long_desc()
{
    return "This "+short()+" is one of the Seekers of Haven who are "+
        "the ruling authority of the town.  These religious men "+
        "seek the new gods, preaching the belief that the old "+
        "gods forsake Krynn during the Cataclysm.\n";
}

string
short_desc()
{
    return adj1 + " "+ adj2 + (query_gender() == 1 ? " female" : " male") +
      " human";
}

