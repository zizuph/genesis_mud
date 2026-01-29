/* dwarf - a small fella /Ashlar 3 May 97 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#include <stdproperties.h>
#include <const.h>
#include <ss_types.h>

void
create_krynn_monster()
{
	set_name("dwarf");
    set_race_name("dwarf");
    set_adj("wrinkled");
    set_gender(G_MALE);
    set_short("wrinkled dwarf");
    set_long("This fellow is wrinkled and looks quite jolly - as long as " +
        "you don't offend him, for instance by saying something rude " +
        "about his mine.\n");

    set_stats(({35,20,38,20,25,35}));
    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_DEFENCE, 40);

    set_act_time(10);
    add_act("emote peers at you suspiciously.");
    add_act("emote strokes his beard.");
    add_act("say Hi ho hi ho");

    add_prop(CONT_I_HEIGHT, 135);

    clone_object(AOBJ + "lump")->move(TO,1);
}

