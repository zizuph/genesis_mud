
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define CAIRN "/d/Ansalon/estwilde/plains/cairn_entry"

#define LOC1 "/d/Krynn/solamn/vin_mount/room/road12"
#define LOC2 "/d/Krynn/solace/new_village/platform7"
#define LOC3 "/d/Krynn/que/plains/xak_link"
#define LOC4 "/d/Krynn/que/plains/gateway_link"
#define LOC5 "/d/Krynn/icewall/forest/forest_11"

string *random_loc = ({ LOC1, LOC2, LOC3, LOC4, LOC5 });

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{

    set_name("teregul");
    add_name("dwarf");
    set_race_name("ghost");
    set_adj("barrel-chested");
    set_adj("ethereal");
    set_long("This is the ghost of Teregul Stormbolt, " +
      "dwarven hero of the hill dwarf clans. While ethereal, "+
      "he still looks as impressive as what he did before " +
      "his death, although his face is lined with grief.\n");

    set_stats(({190,120,180,90,90,142}));
    set_skill(SS_DEFENSE,65);
    set_skill(SS_AWARENESS,75);
    set_introduce(1);
    set_alignment(1000);
    set_knight_prestige(-20);
    set_title("Stormbolt, Dwarven Hero of the Hill Dwarves");

    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
}

void
clone_colin()
{
    clone_object(LIVING + "neidar_colin")->move(ONE_OF(random_loc), 1);
}

void
quest_spool()
{
    command("say Greetings noble warrior...");
    set_alarm(0.3,0.0,&command("introduce myself"));
    set_alarm(0.5,0.0, &command("emote peers around his crypt thoughtfully."));
    set_alarm(1.0,0.0, &command("say So you avenged my daughter "+
	"and she is finally at rest? Then I am in your debt."));
    set_alarm(1.5,0.0, &command("emote strokes his ethereal beard."));
    set_alarm(2.0,0.0, &command("say In repayment, I shall impart to you " +
	"some knowledge you may find of value."));
    set_alarm(2.5, 0.0, &command("say After my daughters death, her betrothed, " +
	"the young Corin Windchaser, " +
	"swore he would not return to Iron Delving until Shale was dead. He left, " +
	"taking with him my great axe, forged during the Age of Dreams, one of " +
	"the most powerful weapons ever created."));
    set_alarm(3.3, 0.0, &command("say On my deathbed, grieved by the betrayal of " +
	"my brightest pupil and the death of my daughter, I made the new arms master, " +
	"Hofta Greymane, swear never to train the advanced axe and club techniques to " +
	"anyone until my axe returned to Iron Delving and Karyth was avenged."));
    set_alarm(3.7, 0.0, &command("say Seek out Corin Windchaser, and tell him his quest is " +
	"over! It won't be easy finding him, as he still wanders the continent, " +
	"searching for Shale Ironfist."));
    set_alarm(3.9,0.0, &command("say I now return to my rest. May your axe strike truly, " +
	"and your shield never break!"));
    set_alarm(4.0,0.0, &command("emote sinks back into his stone coffin."));
    set_alarm(4.1, 0.0, "clone_colin");
    set_alarm(4.2,0.0, &remove_object());
}
