#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/poolbottom/local.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit M_FILE

#define THEOBALD_KEY EOBJ + "theobald_key"

void
create_krynn_monster()
{
    int i;

    set_name("servant");
    set_short("ethereal servant");
    set_pshort("ethereal servant");
    set_race_name("spirit");
    set_long("This ethereal spirit is a conjured servant, often summoned by " +
        "Magi to do mundane tasks such as cleaning and maintenance.\n");
    set_adj("undead");

    for (i = 0; i < 6; i++)
	set_stats(({60,60,60,60,60,100}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_AWARENESS, 40);

    set_knight_prestige(20);

    set_alignment(-10);

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 567900);
    add_prop(CONT_I_WEIGHT, 578400);
    add_prop(LIVE_I_NO_BODY, 1);
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(THEOBALD_KEY)->move(TO,1);
}



