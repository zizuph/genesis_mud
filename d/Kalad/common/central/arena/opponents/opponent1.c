/* 
 * /d/Kalad/common/central/arena/opponents/opponent1.c
 * Purpose    : Opponents to fight in the arena.
 * Located    : /d/Kalad/common/central/arena/arena1.c
 * Created By : Sarr 28.Jun.97
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

void
create_monster()
{
    set_name("eggteg");
    set_race_name("orc");
    set_adj("fat");
    add_adj("grotesque");
    set_short("fat grotesque orc");
    set_long("This is a short, fat orc with rubbery, warty green "+
    "skin. His huge belly bounces around as he moves. His teeth "+
    "are yellow and jagged when he smiles. This is most certainly "+
    "a foul creature.\n");
    set_alignment(-250);
    set_stats(({10,10,10,10,10,10}));
    set_skill(SS_DEFENSE,20);
    set_skill(SS_WEP_KNIFE,25);
    set_skill(SS_AWARENESS,50);
    set_cact_time(5);
    add_cact("say Me will cwabber you!");
    add_cact("say Me will cwush you like bug!");
    add_cact("say Me eat you when me done!");
    add_cact("grin");
    add_cact("say You fight puny!");
    set_title("the Foul");
}

void
arm_me()
{
    object what;
    seteuid(getuid());
    what = clone_object(CENTRAL(arena/eq/jagged_knife));
    what->move(TO);
    what = clone_object(CENTRAL(arena/eq/leather_tunic));
    what->move(TO);
    command("wear all");
    command("wield all");
}

void
do_die(object ob)
{
    E(ob)->defeat(ob,TO);
    ::do_die(ob);
}