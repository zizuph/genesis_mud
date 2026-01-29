/* created by Aridor 04/19/94 */
/* Copied and altered by Macker for the diologue dracs in Icewall */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit BOZAK;


void
create_bozak()
{

    int i, j = random(4) + 3; /* j is the level of the draconian */

    for(i=0; i<6; i++)
        set_base_stat(i, j * 13 + random(10) + 1);
    set_skill(SS_DEFENCE,     j * 9 + random(5) + 5);
    set_skill(SS_PARRY,       j * 8 + random(5) + 5);
    set_skill(SS_WEP_SWORD,   j * 8 + random(5) + 5);
    set_skill(SS_WEP_KNIFE,   j * 8 + random(5) + 5);
    set_skill(SS_WEP_CLUB,    j * 8 + random(5) + 5);
    set_skill(SS_WEP_JAVELIN, j * 8 + random(5) + 5);
    set_skill(SS_WEP_POLEARM, j * 8 + random(5) + 5);
    set_skill(SS_WEP_AXE,     j * 8 + random(5) + 5);


    set_act_time(3 + random(2));
    add_act("say I think we should rid Krynn of Elves! Such tender " +
        "meat, though...");
    add_act("say I don't know why we were chosen to patrol this " +
        "wasteland!");
    add_act("say It's so cold here, I wish we faced the wrath of " +
        "Takhisis if only for a little warmth!");
    add_act("say The minotaurs that were brought here at least " +
        "have fur to keep them warm!");
    add_act("say The white dragon is a coward.");
/*
add_act("say I think we should get rid of those pathetic "
+ "conclave knights first. "
+ "Who needs a bunch of PRETEND Knights, anyway?");
add_act("say Have you seen Kith Kanan's Legion of Wildrunners? "
+ "They remind me of chickens running around with their "
+ "heads chopped off.");
    add_act("say I think we ought to kill that bronze dragon. That would cut off their primary transportation.");
	add_act("say No more mistakes! The last time an attack on Vingaard " +
		"was a failure, Takhisis cracked a dragon egg!");
*/
	
    add_act("grin");
    add_act("twiddle");
    set_cact_time(10);
    add_cact("say You really think you can defeat me?\n");
    add_cact("say Ahhh, now I can test my battle skill.\n");
    add_cact("say I didn't even feel that!\n");
    add_cact("say Is that all you can do?\n");
    add_cact("say Don't take it personally but I'll kill you.\n");
    add_cact("grin");

    set_color("white");

}


