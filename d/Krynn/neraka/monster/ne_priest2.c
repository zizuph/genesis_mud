/* Priest 2, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>

inherit M_FILE

create_krynn_monster()
{
    int i;

    set_name("torak");
    set_adj("young");
    add_name("priest");
    set_living_name("torak");
    set_short("young priest");
    set_long("He is sitting at a table studying a book.\n");
    set_race_name("human");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 12 + random(10));
    set_skill(SS_DEFENCE, 20);
    set_knight_prestige(200);
    set_alignment(-120);

    add_act("emote mumbles something.");
    add_act("emote shifts his legs.");
    set_act_time(14);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(13, 17);


/*
    clone_object(OBJ + "yp_book")->move(TO);
*/
}
