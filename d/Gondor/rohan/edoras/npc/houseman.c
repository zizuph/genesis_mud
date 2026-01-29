inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_monster()
{
    set_name(({"houseowner","man"}));
    set_race_name("human");
    set_short("rohirrim man");
    set_long(BSN("This is the owner of the house. He has golden hair with "
        + "streaks of gray."));
    set_stats(({30, 20, 30, 20, 20, 10}));
    set_alignment(150);
    set_skill(SS_WEP_KNIFE,20);
    set_chat_time(20);
    add_chat("I dont like that Grima, he is bad news.");
    add_chat("Oh well, I hope the King knows what he is doing.");
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me"}));
}

void
arm_me()
{
    FIX_EUID

    clone_object(EDORAS_DIR + "obj/fknife")->move(TO);
    command("wield knife");

    clone_object(EDORAS_DIR + "obj/leather")->move(TO);
    command("wear armour");
}
 /* solamnian prestige */
query_knight_prestige() {return (-5);}
