
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define CAIRN "/d/Ansalon/estwilde/plains/cairn_entry"

void
create_krynn_monster()
{

    set_name("karyth");
    set_race_name("dwarf");
    set_adj("ghostly");
    set_gender(1); /* Female */
    set_stats(({120,80,130,70,80,92}));
    set_skill(SS_DEFENSE,65);
    set_skill(SS_AWARENESS,75);
    set_introduce(1);
    set_alignment(1000);
    set_knight_prestige(-20);
    set_title("Stormbolt, Haunt of the Netherworld");

    add_prop(LIVE_I_UNDEAD, 40);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
      "do not dare attack this spirit!\n");
}

void
quest_spool()
{
    command("say Thank you so much for avenging me!");
    set_alarm(0.3,0.0,&command("introduce myself"));
    set_alarm(1.0,0.0, &command("emote smiles radiantly."));
    set_alarm(2.5,0.0, &command("say Now that Shale Ironfist "+
	"is dead, I can finally rest in peace."));
    set_alarm(3.5,0.0, &command("sigh relie"));
    set_alarm(4.0,0.0, &command("say I am truly in your debt, but " +
	"unfortunately there is nothing I can offer you in repayment " +
        "except my gratitude."));
    set_alarm(6.5, 0.0, &command("say I also must beg a favour of you. "+
	"My father died of grief after my death, and his spirit will " +
        "not rest until he knows I am at peace. Could you go to his cairn " +
        "and tell him that my earthly chains are now broken?"));
    set_alarm(9.0, 0.0, &command("say His cairn stands on the highest " +
        "hill in Estwilde. Its doors will open for you, but beware " +
        "of the traps that lie within! I must depart "+
        "now to Reorx's forge in the heavens. Axes high, warrior!"));
    set_alarm(11.0,0.0, &command("emote suddenly fades out of sight."));
    set_alarm(11.0, 0.0, &CAIRN->unlock_cairn_door());
    set_alarm(11.5,0.0, &remove_object());
}
