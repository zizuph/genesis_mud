/* Chatting monster */

#include "/d/Krynn/common/defs.h"
inherit M_FILE

create_krynn_monster()
{
    set_name("joe");
    add_name("digger1");
    set_adj("grave");
    set_living_name("digger");
    set_short("grave digger");
    set_long("This is a very talkative grave digger.\n");
    set_race_name("digger");
    set_gender(0);

    default_config_mobile(10);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);

    set_act_time(5);
    add_act("kill digger");

    set_chat_time(2);
    add_chat("IT IS MY SHOVEL, NOT YOURS!!");
    add_chat("You were the last one to use the shovel.\n");
}

