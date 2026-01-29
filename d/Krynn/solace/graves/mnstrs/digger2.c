/* An angery grave digger */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit M_FILE

void
create_krynn_monster()
{
    set_name("fred");
    add_name("digger2");
    set_adj("grave");
    add_adj("scruffy");
    set_living_name("digger");
    set_short("scruffy grave digger");
    set_long("He is very easily angered.\n");
    set_race_name("digger");
    set_gender(0);

    default_config_mobile(10);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);

    set_act_time(3);
    add_act("kick digger");
    add_act("kill digger");

    clone_object(OBJ + "steel_key")->move(TO);
}

