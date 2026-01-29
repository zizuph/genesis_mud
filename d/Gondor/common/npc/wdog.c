 /*
  * A wild dog, coded for Emyn Arnen in Ithilien
  *
  * Olorin              Jul 1993
  */
inherit "/d/Gondor/common/npc/wolf";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_creature()
{
    ::create_creature();

    set_name("dog");
    set_race_name("dog");
    set_short("large wild dog");
    set_pshort("wild dogs");
    remove_adj(({"grey", "hungry", }));
    set_adj(({"large", "wild", }));

    set_aggressive(1);
    set_attack_chance(75);
    set_long(BSN("This is a wild dog, large and ferocious. He is lean and "
      + "scrawny and has thick, black fur and sharp fangs."));

    set_stats(({30+random(20), 40+random(25), 40+random(10), 30, 5, 65}));
    set_alignment(-100-random(150));

    set_skill(SS_DEFENCE, 25);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_SWIM, 80);
    set_skill(SS_HIDE, 50);
    set_skill(SS_SNEAK, 50);

    set_jump_rate(30);

    set_random_move(1);
    set_restrain_path(ITH_DIR + "emyn-arnen");
    seq_clear("do_first");
    seq_addfirst("do_first",({"stare","emote peers hungrily at you.","growl"}));

    set_m_out("quickly trots");
    set_m_in("stealthily trots into view");

    set_act_time(5);
    add_act("hide");
}

mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    return "sneak "+exit;
}
