/* created by Aridor 04/19/94 */
/* Copied and altered by Macker for the diologue dracs in Icewall */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit KAPAK;

void
create_kapak()
{
    int i, j = random(6) + 1;
              /* j is the level of the draconian */

    for(i=0; i<6; i++)
        set_base_stat(i, j * 4 + random(10) + 16);
    set_skill(SS_DEFENCE,     j * 4 + random(5) + 10);
    set_skill(SS_PARRY,       j * 3 + random(5) + 10);
    set_skill(SS_WEP_SWORD,   j * 3 + random(5) + 10);
    set_skill(SS_WEP_KNIFE,   j * 3 + random(5) + 10);
    set_skill(SS_WEP_CLUB,    j * 3 + random(5) + 10);
    set_skill(SS_WEP_POLEARM, j * 3 + random(5) + 10);
    set_skill(SS_WEP_JAVELIN, j * 3 + random(5) + 10);
    set_skill(SS_WEP_AXE,     j * 3 + random(5) + 10);

	set_act_time(3 + random(3));
    add_act("say Let's crush the Ice Folk Villagers!");
    add_act("say The fools of Tarsis won't know what hit them.");
    add_act("say That damned ice bear killed a draconian patrol!");
    add_act("say Where has Feal-thas gone?");
/*
    add_act("say Yeah, and let's steal that damn bell they keep ringing.");
    add_act("say Ordheus is mine!");
    add_act("say I'm gonna have lots of fun with that cute little " +
	"squire that works in the library.");
*/
    add_act("cackle");
	add_act("agree");

    set_cact_time(10);
    add_cact("say You really think you can defeat me?\n");
    add_cact("say Ahhh, now I can test my battle skill.\n");
    add_cact("say I didn't even feel that!\n");
    add_cact("say Is that all you can do?\n");
    add_cact("say Don't take it personally but I'll kill you.\n");
    add_cact("grin");

    set_color("white");

}



