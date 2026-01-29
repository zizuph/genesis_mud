#include "local.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Genesis/ship/captain";

void create_captain()
{
    set_name("thigpin");
    add_name("captain");
    set_race_name("human");
    set_adj(({"travel-worn", "gaunt"}));
    set_gender(G_MALE);
    set_title("the First Mate of the Swift Sunset");
    default_config_npc(60);
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_I_RES_MAGIC, 200);

    set_act_time(100);
    add_act("say You know, I'd like to keep my cheeks dry today.");
    add_act("emote sings to himself: Come out upon my seas, curse missed "
        + "opportunities...");
    add_act("say Don't worry even if things end up a bit too heavy, we'll all" 
        + " float on alright.");
    set_ticket(TICKET);
    set_price(PRICE);
}
