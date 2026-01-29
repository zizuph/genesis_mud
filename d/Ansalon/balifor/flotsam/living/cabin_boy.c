#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/sm_knife"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("boy");
    set_adj("cabin");
    set_short("cabin boy");
    set_long("This is the cabin boy for the pirate vessel " +
      "the Golden Lion. He looks rather young, but excited " +
      "to be at sea.\n");

    set_stats(({15,20,18,12,12,12}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(0);

    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 5);

    set_act_time(3);
    add_act("say Those street kids! I'd bet my life they'd rat on me for a copper!");
    add_act("say Hull Nightstar is the greatest pirate " +
      "to ever live!");
    add_act("say Satania scares me. Some whisper he is a " +
      "dark elf, having been thrown out of Silvanesti for " +
      "some evil deed.");
    add_act("say Getting a place on this ship cost me an " +
      "arm and a leg...");

    add_ask(({"hull nightstar","Hull","hull","Hull Nightstar"}),
      "say Hull Nightstar is the captain of this ship. Some " +
      "say he is one of the few captains to sail through the " +
      "great storms of the Bloodsea. Others say he is crazy, " +
      "and does crazy things at a whim.",1);
    add_ask(({"satania","Satania"}),
      "say Shhh! Don't ask about him too loudly! If he hears " +
      "you, he may get suspicious and think you are trying to " +
      "cross him, and no one crosses Satania and stays alive " +
      "for long.",1);
    add_ask(({"fermammon","Fermammon","apprenticeship",
	"magicians apprentice","magician"}),
      "say I was once an apprentice to a powerful magician " +
      "who lived outside of Flotsam, Fermammon the Wise. " +
      "I ran away from him because he found out I had stolen " +
      "an object from him.",1);
    add_ask("object","say I stole a wand from him. Figured " +
      "I might be able to trade it in town",1);
    add_ask(({"wand","town"}),
      "say I traded it to someone in town for a knife. " +
      "Figured it be more useful on the high seas.",1);
    add_ask(({"who","someone","trade"}),
      "say Ha! As if I'd tell you who I traded it to! None " +
      "of your business.",1);
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
}
