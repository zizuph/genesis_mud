inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/basic_special";

#include <wa_types.h>

public void
create_earthsea_monster()
{
    set_name("bob");
    default_config_npc(150);
    set_special_attack_percent(100);
    add_special_attack(&basic_special(this_object(), 40, MAGIC_DT),
        100, "flaskattack");
    set_target_message(
        " flings his flask into the air and a splash of holy water hits you."
    );
    set_watcher_message(
        " flings his flask into the air and splashes holy water at"
    );
    set_result_messages(([
        1 : "The water stings as it hits your skin.",
        15 : "You are burnt lightly by the holy water.",
        35 : "Your skin sizzles as the water hits.",
        50 : "You are seriously damaged by the holy water."
    ]));
}
