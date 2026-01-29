/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typo)
 */

inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";
#include "/d/Raumdor/defs.h"


void
create_monster()
{
    ::create_monster();
    set_name("shindar");
    add_name("merchant");
    set_race_name("human");
    set_adj("cloaked");
    add_adj("old");
    set_short("old cloaked merchant");
    set_long("This old man is wraped in a dull grey cloak. His gnarled "+
    "hands rest on an old cane. He looks at you from within his hood "+
    "with beady black eyes. He is waiting to trade with you.\n");
    set_stats(({40,50,60,80,80,40}));
    set_skill(SS_WEP_POLEARM,100);
    set_act_time(5);
    add_act("say Welcome Travellers!");
    add_act("say Want to trade?");
    add_act("say Beware of the Forest! Stick to the road!");
    add_act("say Rumours say that the King was killed by a demon!");
    add_act("say Dark rumours say that the Khiraa is alive and doing "+
    "evil things!");
    set_default_answer("The old cloaked human says: What was that?\n");
    add_ask(({"khiraa","Khiraa"}),"The Cult of the Dead, in the ancient "+
    "tongue. Lord Gylar was head of it, until he died in the Great "+
    "Battle.\n");
    add_ask(({"king","King"}),"The old cloaked human weeps.\n");
    set_title("Store Owner");
}

void
do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,1);
    ::do_die(who);
}
