/* created by Aridor 04/19/94 */
/* Copied and altered by Macker for the diologue dracs in Icewall */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit BAAZ;

void
create_baaz()
{
    int i, j = random(4) + 1; /* j is the level of the draconian */

    for(i=0; i<6; i++)
        set_base_stat(i, j * 3 + random(10) + 16);
    set_skill(SS_DEFENCE,     j + random(5) + 3);
    set_skill(SS_PARRY,       j + random(5) + 3);
    set_skill(SS_WEP_SWORD,   j + random(5) + 3);
    set_skill(SS_WEP_KNIFE,   j + random(5) + 3);
    set_skill(SS_WEP_CLUB,    j + random(5) + 3);
    set_skill(SS_WEP_POLEARM, j + random(5) + 3);
    set_skill(SS_WEP_JAVELIN, j + random(5) + 3);
    set_skill(SS_WEP_AXE,     j + random(5) + 3);


    set_act_time(3 + random(3));
    add_act("snicker");
    add_act("say Those Ice Folk villagers are barbarians...dead " +
        "barbarians when I'm done with them!");
    add_act("say Those Thanoi are perfect recruits for the Dark " +
        "Queen.");
    add_act("say That old cleric in the camp is useless. I bet " +
        "he's all bones by now, hardly fit for a meal.");
    add_act("say I hope Feal-thas knows what he's doing!");
/*
    add_act("say And when we're done, we'll trash the entire keep with all that junk in the recycling bin.");
	add_act("say I can't wait to put a dress on the statue of Huma. " +
		"Oh yeah, and lipstick too!");
    add_act("say Let's tie up Gunthar and feed him to a dragon.");
	add_act("say Now that we know where the secret entrance " +
		"to Vingaard is, it'll be just as easy as that little barbarian " +
		"we destroyed last week. What was that place called? Que something, right?");
*/

    set_cact_time(10);
    add_cact("say You really think you can defeat me?\n");
    add_cact("say Ahhh, now I can test my battle skill.\n");
    add_cact("say I didn't even feel that!\n");
    add_cact("say Is that all you can do?\n");
    add_cact("say Don't take it personally but I'll kill you.\n");
    add_cact("grin");

    set_color("white");

}

