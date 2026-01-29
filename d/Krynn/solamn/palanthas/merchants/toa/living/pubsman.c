/* 
 * Pubsman of the Tower of Arms of Palanthas
 *
 * Mortis 09.2014
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../../../local.h"

inherit CITIZEN;

#define MONEY 1000 + random(1600)

/* Prototypes */
void arm_me();

void
create_krynn_monster()
{
    set_name("jips");
    set_living_name("jips");
    set_race_name("human");
    set_adj("fat");
    add_adj(({"grey", "smocked", "grey-smocked"}));
    add_name(({"jips", "pubsman", "proprietor"}));
    set_title("Perisunder, Pubsman of the Draft Pub");
    set_short("fat grey-smocked male human");
    set_long("The pubsman is stocky with a big beer gut. He's clean with "
    + "slicked back greying hair and wears a grey smock over his clothes.\n");
    set_gender(G_MALE);
    set_stats(({120,60,105,75,80,35}));
    set_skill(SS_AWARENESS, 56);
    set_size_descs("short", "fat");
    set_appearance(5);
    
    add_prop(OBJ_M_HAS_MONEY, MONEY);
    set_introduce(1);
    set_act_time(12);
    add_act("say Come on in, men.");
    add_act("say Whatcha need?");
    add_act("emote nods as he smiles knowingly.");
    add_act("emote smells the air wondering if someone farted.");
    add_act("smell");
    add_act("emote whistles a ditty as he prepares an order.");
    add_act("time");
    
    add_ask(({"ale", "food", "price", "list"}), "It's clean and good, and "
    + "your commander will never know you were here if you know what I mean, "
    + "heh heh heh heh heh.\n");

    add_ask(({"city", "palanthas"}), "The pubsman replies:  The city of "
    + "Palanthas is a great palce to be. Its pristine marble, well "
    + "architected streets, and beautifully designed buildings just reek of "
    + "old world charm you won't find anywhere else.\n");

    set_alarm(2.0,0.0,&arm_me());
}

void
arm_me()
{
    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(63))->move(TO);
    MONEY_MAKE_SC(400 + random(15))->move(TO);
}