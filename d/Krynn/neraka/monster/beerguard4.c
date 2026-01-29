/* Beerguard 4 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
inherit M_FILE

void
create_krynn_monster() {
    int i;

    set_name("guard");
    add_name("drunk");
    add_name("human");
    set_adj("drunk");
    set_race_name("human");
    set_long(BS(
	"It looks like if he spends most of his time leaning on the bar. " +
	"He has a red nose and his eyes match the nose. You notice that he " +
	"doesn't seem armed. Perhaps he has sold all his equipment to get " +
	"money to buy beer. However, this man can't guard much today.",SL));

    for (i = 0; i < 6; i++)
        set_base_stat(i,10 + random(5));
    set_alignment(-150);
    set_knight_prestige(150);
    set_gender(0);

    add_item("nose","That is one of the biggest noses you have ever seen.\n");
    add_item("eyes","They are almost as red as the mans nose.\n");

    set_act_time(30);
    add_act("say Have you got a spare beer, kiddo?");
    add_act("say I could use a drink.");
    add_act(({"sniff", "say Nobody likes me :("}));

    NEVERKNOWN;
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_all_attack_unarmed(15, 15);
    set_all_hitloc_unarmed(7);

}
