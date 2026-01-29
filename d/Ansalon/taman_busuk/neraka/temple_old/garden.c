/* Ashlar, 1 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;
inherit "/lib/skill_raise";

#define KRHERB "/d/Krynn/common/herbs/"

object gardener;
int levlim;

void set_up_skills();

void
reset_neraka_room()
{
    if (!objectp(gardener))
        gardener = clone_npc(NNPC + "alister");
}

string
long_descr()
{
    return "You stand in a large cavern below the temple. This is the " +
    "Queen's Gardens, where strange and dangerous plants are cultivated " +
    "by magical means. Light spells along the high ceiling of the cavern " +
    "gives it the appearance of daylight in places, while other spots " +
    "are in darkness.\n";
}

void
create_neraka_room()
{
    set_short("the south end of a corridor");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"strange cavern","cavern"}),
    "It is oddly lit, and seems to be full of plants.\n");
    add_item("ground",
    "The ground is soggy and marsh-like, with small ponds at places.\n");
    add_item("ponds",
    "Small ponds are placed at intervals around the cavern. They contain " +
    "murky brown water.\n");
    add_item("water",
    "The water here is murky brown.\n");

    set_up_herbs(({KRHERB + "greenslime", KRHERB + "bkd_sedge",
    KRHERB + "skullcap", KRHERB + "mandrake"}),
    ({"ground"}));

    reset_room();

    create_skill_raise();
    set_up_skills();

    add_exit(NTEMPLE + "d12", "northeast");
}

public void
init()
{
    init_skill_raise();
    ::init();
}

void
set_up_skills()
{
//    sk_add_train(SS_HERBALISM, "find and identify plants", 0, 0, 55 );
    sk_add_train(SS_HERBALISM, "find and identify plants", 0, 0, 60 );
    sk_add_train(SS_APPR_OBJ,  "appraise objects", 0, 0, 50);
    sk_add_train(SS_APPR_VAL,  "appraise values", 0, 0, 50);
}

int
sk_improve(string sk)
{
    if (sk)
    {
        if (!MEMBER(TP))
        {
            write("Only Priests of Takhisis can improve their skills here.\n");
            return 1;
        }
    }

    if (!P(gardener, TO))
    {
        write("There is noone here to train you.\n");
        return 1;
    }

    return ::sk_improve(sk);
}

int
sk_query_max(int snum)
{
    int mxtrain;
    mixed skval;

    if (!MEMBER(TP))
	return 0;
    mxtrain = MAX_SKILL_LEVEL[snum][TP->query_priest_level()];

    skval = sk_trains[snum];
    if (skval[2] <= mxtrain)
    {
        mxtrain = skval[2];
        levlim = 0;
    }
    else
        levlim = 1;

    if (sizeof(skval) > 2)
        return mxtrain;
    else
        return 0;
}

int
sk_hook_improved_max(string skill)
{
    NF("You cannot raise this skill any further here, you have to " +
	"seek knowledge elsewhere.\n");
    if (levlim)
	NF("Your position in the guild does not allow further " +
	    "training of this skill.\n");
    return 0;
}
