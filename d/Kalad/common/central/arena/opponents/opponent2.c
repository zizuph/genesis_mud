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
    set_name("sore");
    set_race_name("goblin");
    set_adj("menacing");
    add_adj("red-eyed");
    set_short("red-eyed menacing goblin");
    set_long("This is a goblin with large, ugly muscles. His blazing "+
    "red eyes burn with bloodlust. You face a fearsome foe.\n");
    set_alignment(-390);
    set_stats(({10,10,10,10,10,10}));
    set_skill(SS_DEFENSE,30);
    set_skill(SS_WEP_CLUB,35);
    set_skill(SS_AWARENESS,50);
    set_cact_time(5);
    add_cact("say You die!");
    add_cact("say DIE DIE DIE DIE!");
    add_cact("say You die now!");
    add_cact("scream");
    add_cact("say Die, yes, you will!");
    set_title("the Killer");
}

void
arm_me()
{
    object what;
    seteuid(getuid());
    what = clone_object(CENTRAL(arena/eq/iron_club));
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