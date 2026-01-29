/* Sleeping human, by Nick */
/* Added prop to stop people giving the quest potatoes to this woman - Arman */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>

inherit M_FILE

create_krynn_monster()
{
    int i;

    set_name("woman");
    set_short("small woman");
    set_long("She is standing here waiting for someone. Perhaps her husband?\n");
    set_race_name("human");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, " doesn't accept gifts from you.\n");

    add_ask("mary","say Mary? You'll find her towards the north of Tantallon.",1);
    add_ask(({"potatoes","spiced potatoes"}),"say No thanks.",1);
    add_ask(({"husband","waiting","someone"}),"say The Highlord told me to wait "+
          "here. So here I wait!",1); 

    set_gender(1);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 10 + random(10));
    set_skill(SS_DEFENCE, 20);

    set_all_hitloc_unarmed(6);
    set_all_attack_unarmed(7, 8);

    set_alarm(1.0,0.0,"money");
}

money()
{
    object money;

    seteuid(getuid(TO));
    money = clone_object("/std/coins");
    money->set_name("coin");
    money->set_pname("coins");
    money->set_heap_size(random(300));
    money->set_typ(MONEY_TYPES[0]);
    money->move(TO);
}
