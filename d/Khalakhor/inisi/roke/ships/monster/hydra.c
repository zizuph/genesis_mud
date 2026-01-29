/*
 * hydra.c
 *
 * Used in ships/island/i2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

/* wh||| a really incredibly cool hydra, created by the drunk wizard itself! */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "../../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>

/* Yeah you where drunk allright... 
   I just hope that I will be more drunk tonight though !
   / Lord Ged
   PS Please use the defines !!! DS
#define BEGIN_HEADS 3
*/

#define BEGIN_HEADS 7

int curr_hit_nr, unusablenr;

void
add_head()
{
    int t, remhit = 100, phit = 100 / (curr_hit_nr + 1);
    for (t = 0; t < curr_hit_nr; t++)
    {
        set_hitloc_unarmed(t, 75, phit, LANG_ORD2WORD(t + 1) + " head");
        remhit -= phit;
    }
    set_hitloc_unarmed(curr_hit_nr, 75, remhit, 
                       LANG_ORD2WORD(curr_hit_nr + 1) + " head");
    set_attack_unarmed(curr_hit_nr++, 50, 50, W_IMPALE, 50, "jaws");

    add_leftover(SHIPDIR + "monster/hydrahead", "head", curr_hit_nr -
                 unusablenr, "", 0, 1);
    add_leftover(SHIPDIR + "monster/badhead", "skull", unusablenr, "", 0, 1);
}

string
mylong()
{
    return "This is a nasty, green hydra with " + curr_hit_nr + " heads.\n";
}

void
create_creature()
{
    int i;

    unusablenr = 0;

    for (i = 0; i < BEGIN_HEADS; i++)
        add_head();

    set_gender(2);

    set_race_name("hydra");
    set_long("@@mylong");
    set_name("hydra");
    set_living_name("svenper");
    set_adj("green");

    set_stats(({50, 50, 130, 20, 20, 75}));

    add_item(({"heads", "head"}),
             "You try to look at the head, but it is too awful!.\n");

    refresh_living();
}


varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id,
       int target_hitloc = -1)
{
    object head;
    if ((dt == W_SLASH || dt == W_IMPALE) && !random(3))
    {
        attacker->catch_msg("You chop off one of the heads, and two new ones grows out in its place.\n");
        unusablenr += 2;
        seteuid(getuid());
        add_head();
        head = clone_object(SHIPDIR + "monster/badhead");
        head->leftover_init("skull", "hydra");
        head->move(ENV(TO));
    }
/* Bonus for unarmed==90, was part of the guru quest.
    else
        wcpen = wcpen * (1 + 3 * (attacker->query_skill(SS_UNARM_COMBAT) > 89));
*/

    return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}
