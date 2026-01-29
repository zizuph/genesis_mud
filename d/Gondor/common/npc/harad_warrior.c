#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_name("haradrim");
    add_name("man");
    add_name("southron");
    set_adj("tall");
    set_adj("dark-skinned");
    set_long(BSN("This is a tall and dark-skinned haradrim warrior, clad "
      + "in bright clothing and with golden earrings. He looks "
      + "hatefully at you, brandishing his sharp scimitar."));
    set_race_name("human");
    set_alignment( -200- random(24));
    default_config_npc(random(10)+58);
    set_base_stat(SS_CON,random(10)+62);

    set_skill(SS_WEP_SWORD, random(10)+70);
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_AWARENESS, 75);
    set_chat_time(16);
    add_chat("I'll take the scalps of every dunedain that I kill!");
    add_chat("If only the signal for our attack would come.");
    add_chat("I'm tired of waiting in this filthy camp!");
    add_chat("Why do we have to camp with the dirty orcs?");
    add_chat("We will plunder the houses of Minas Tirith soon!");
    set_cchat_time(5);
    add_cchat("Bleed to death, dirty hyena!");
    add_cchat("Your neck won't stand a chance to my scimitar!");
    add_cchat("Die screaming, dog!");
}

public void
arm_me()
{
    FIX_EUID
    clone_object(WEP_DIR + "haradscim")->move(TO);
    command("wield scimitar");
    clone_object(ARM_DIR + "haradcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "haradshield")->move(TO);
    command("wear shield");
}

/* for the Solamnians */
public int query_knight_prestige() { return 1300; }

