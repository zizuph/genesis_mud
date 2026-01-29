/* Mary in Tantallon by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit M_FILE

create_krynn_monster() 
{
    int i;

    ALWAYSKNOWN;

    set_name("mary");
    set_living_name("mary");
    set_long("She is working but you can't see with what.\n");
    set_race_name("human");

    add_act("say Would you please leave?");
    add_act("say This is hard work!");
    set_act_time(40);

    set_gender(1);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 10+random(5));
    set_alignment(170);
    set_knight_prestige(-1);

    set_all_attack_unarmed(7, 8);
    set_all_hitloc_unarmed(2);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

}

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

      set_alarm(1.0,0.0,"command", "thank " + from->query_real_name());
    if (ob->id("potatoes"))
    {
	if (ob = present("tour2", TP))
	    ob->set_arr("mary");
    }
}

