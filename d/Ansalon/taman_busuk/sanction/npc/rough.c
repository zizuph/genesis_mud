#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit AM_FILE

#define WEP "/d/Ansalon/taman_busuk/neraka/wep/knobkerrie"

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("roughian");
    set_short("hard-eyed roughian");
    set_race_name("human");
    set_long("This roughian is one of the many immoral locals who lurk " +
      "in the shadows of the slums, always on the lookout for an " +
      "easy prey. His eyes look hardened, and you do not doubt he " +
      "would offer no mercy if he caught you alone at the end of " +
      "a dark alley.\n");
    set_stats(({65,55,45,35,35,45}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 30);

    set_alignment(-300);
    set_knight_prestige(20);

    set_act_time(0);
    add_act("emote gazes around suspiciously.");
    add_act("emote looks at you with a calculating glance.");
    add_act("emote whispers something to someone.");
    add_act("smile dark");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
}
