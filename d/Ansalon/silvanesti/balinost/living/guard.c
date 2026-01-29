#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/balinost/local.h"

#include <ss_types.h>
#include <macros.h>
inherit AM_FILE
inherit AUTO_TEAM

#define WEP "/d/Ansalon/silvanesti/balinost/objs/shortsword.c"

void
create_krynn_monster()
{
    set_name("guard");
    set_race_name("elf");
    set_adj("sturdy");
    set_long("This noble looking Silvanesti is typical of the "+
      "Balinost guard.\n");

    set_short("sturdy silvanesti guard");
    set_act_time(20);
    add_act("emote checks to make sure the point of his blade is sharp.");
    add_act("say I can't believe we're evacuating our home.");
    add_act("sigh");
    set_stats(({ 85, 85, 90, 40, 40, 90 }));

    set_hp(12000);
    set_alignment(450);
    set_knight_prestige(-200);
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 50);
    /* We need to make sure the user ids are correct before we
     * attempt to clone anything.
     */
    setuid();
    seteuid(getuid());

    /* Clone the weapon and move it to the monster */
    clone_object(WEP)->move(this_object(), 1);
    /* Wield the weapon */
    command("wield all");

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_cact_time(1);

    add_cact("assist");
    add_act("assist");
    add_cact("say You shall die by my blade!");
    /* Clone the armour and move it to the monster */
    /* Wear the armour */
}

