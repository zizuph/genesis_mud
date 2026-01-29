/*
 * File:     shisa.c
 * Created:  Cirion 1998.10.22
 * Purpose:  misc. trainer of the monks
 * Cloned:   /d/Earthsea/monk/room/training_other 
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

string * messages = ( {} );

void
create_monk ()
{
    set_name ("shisa");
    set_race_name ("gnome");
    set_adj (({ "tiny", "concerned" }));
    set_long ("This gnome is holding a clipboard and is constantly "
		+ "scanning the floor of the room.\n");

    init_monk ();
    set_gender(G_MALE);
    set_height_weight(2.2, 136);


    set_skill (SS_UNARM_COMBAT, 40);
    set_skill (SS_DEFENCE, 10);
    set_skill (MONK_SKILL_FOCUS, 25);
    set_skill (MONK_SKILL_STRIKE, 25);
    set_skill (MONK_SKILL_PLEXUS, 25);
    set_skill (SS_AWARENESS, 90);
    set_skill (SS_BLIND_COMBAT, 90);

    // give him some silver coins
    equip_monk (({ 0, 19 + random (90) }));

    set_act_time(10);
    add_act("emote frowns.");
    add_act("emote knits his brows and looks concerned.");
    add_act("emote paces up and down the room.");
    add_act("emote writes down something on his clipboard.");
    add_act("emote scratches his head with his pen.");

	add_ask (({ "clipboard", "inventory", "stuff" }),
		VBFC_ME ("ask_about_clipboard"), 1);


}

public void 
note_message (string message)
{
	command ("emote writes something down on his clipboard.");
	messages += ({ message });

	while (sizeof (messages) > 400)
		messages -= ({ messages [0] });
}

public string
ask_about_clipboard ()
{
	if (!m_query_council_or_elder (this_player (), 1))
	{
		command ("emote holds his clipboard close to his body.");
		return "say I'mAdraidYouAreNotAuthorizedToHave"
			+ "ThatInformation.";
	}
	else if (sizeof (messages) <= 0)
	{
		return "say Sorry, I don't have anything written down now!";
	}
	else
	{
		this_player ()->catch_msg (QCTNAME (TO)
			+ " shows you his clipboard:\n");
		this_player ()->more (implode (messages, "\n"));
		return "sigh";
	}

}

