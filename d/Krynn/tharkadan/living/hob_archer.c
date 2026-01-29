#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

#define BOW       WEP + "bow"
#define ARROW     WEP + "poison_arrow"
#define QUIVER    TOBJ + "quiver"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("hobgoblin");
    add_name("tracker");
    set_short("hobgoblin tracker");
    set_race_name("hobgoblin");
    set_long("This angular-faced fanged horror is one of the many " +
      "hobgoblins that have been attracted to the Highlords armies. " +
      "This one is particularly skilled at tracking, and is currently " +
      "part of a patrol seeking out prisoners from Pax Tharkas who have " +
      "escaped.\n");

    set_stats(({70,75,70,66,66,100}));
    set_hp(10000);

    set_skill(SS_WEP_MISSILE, 65);
    set_skill(SS_DEFENCE, 55);
    set_skill(SS_PARRY, 55);
    set_skill(SS_TRACKING, 65);
    set_skill(SS_AWARENESS, 75);

    set_default_answer("The hobgoblin tracker is either too busy " +
        "looking for escapee tracks or too worried about getting " +
        "in trouble from the draconian patrol leader to answer " +
        "your questions.\n");

    set_alignment(-200);
    set_knight_prestige(85);

    set_act_time(5);
    add_act("emote searches the trail for tracks.");
    add_act("emote looks up at the mountains searchingly.");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(BOW)->move(this_object(),1);
    command("wield all");

    object quiver = clone_object(QUIVER);
    quiver->move(this_object(),1);
    clone_object(ARROW)->move(quiver,1);
    clone_object(ARROW)->move(quiver,1);
    command("wear all");

}
