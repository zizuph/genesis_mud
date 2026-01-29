
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define OFFICE "/d/Ansalon/kalaman/room/office"

void
create_krynn_monster()
{

    set_name("t'nahcrem");
    add_name("merchant");
    set_race_name("human");
    set_adj("ragged");
    set_short("ragged merchant");
    set_stats(({120,80,130,70,80,92}));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENSE,65);
    set_skill(SS_AWARENESS,75);
    set_skill(SS_PARRY,45);
    set_introduce(1);
    set_alignment(1000);
    set_knight_prestige(-20);
    set_title("the Dispossessed Merchant of Ergoth");
}

void
quest_spool()
{
    command("say Thank you so much for freeing me!");
    set_alarm(0.5,0.0, &command("emote sobs in relief."));
    set_alarm(1.0,0.0, &command("say I owe you my life... "+
	"his bastardness Ariakas was going to leave me there until "+
	"I told him where my stash of..."));
    set_alarm(1.5,0.0, &command("peer nervous"));
    set_alarm(2.0,0.0, &command("say Best if I say no more " +
	"about that."));
    set_alarm(2.5, 0.0, &command("say Anyway, I must get out of "+
	"Sanction swiftly... come visit me at my Kalaman office, and "+
	"I shall reward you richly!"));
    set_alarm(3.0,0.0,&command("introduce myself"));
    set_alarm(3.3, 0.0, &command("nod slight"));
    set_alarm(3.7,0.0, &command("emote hobbles off towards the docks."));
    set_alarm(3.9, 0.0, &OFFICE->reset_kalaman_room());
    set_alarm(4.0,0.0, &remove_object());
}
