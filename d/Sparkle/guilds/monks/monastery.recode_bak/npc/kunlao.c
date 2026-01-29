/*
 *  20190703 Ckrik - created
 *
 */

#include <const.h>
#include <macros.h>
#include <ss_types.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

//-------------------------------------------------------------------

void create_monster()
{
    ::create_monster();
    set_name("kunlao");
    set_gender(G_MALE);
    set_race_name("human");
    set_adj(({ "bald", "musculebound" }));
    set_long("Tall and musculebound this human towers over most. " +
        "His bald head is polished to a gleaming shine and " +
        "you notice some rather thick calluses on his " +
        "knuckles. You surmise that this human must have " +
        "rather hard fists acquired through years of " +
        "disciplined training.\n");
    m_init();
    m_equip(({ 0, 20 + random (90) }));
    m_stature(220, 130);
    set_stats(({220, 250, 200, 180, 180, 200}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_ACROBAT, 70);
    set_skill(M_SKILL_STRIKE, 100);
    set_skill(M_SKILL_PLEXUS, 100);

    set_act_time (10);
    add_act (({ "emote sweeps the floor with a broom.",
              "emote whispers a brief prayer."}));
    add_act ("smile confidently " + VBFC_ME ("dg_get_present_living_str"));
}

//-------------------------------------------------------------------

