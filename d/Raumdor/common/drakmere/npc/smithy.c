/* Sarr */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

void
create_monster()
{
    ::create_monster();
    set_name("takar");
    add_name("smith");
    set_race_name("human");
    set_adj("strong");
    add_adj("black");
    set_short("stout smith");
    set_long("He looks down at you with dark black eyes. He has many "+
    "scars, his skin is black, and his muscles are massive. He holds "+
    "an iron hammer in his hand.\n");
    set_stats(({120,80,160,50,60,100}));
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENCE,70);
    set_act_time(5);
    add_act("say Welcome Travellers!");
    add_act("say Beware of the Forest! Stick to the road!");
    add_act("say Rumours say that the King was killed by a demon!");
    add_act("emote hammers on his anvil.");
    set_default_answer("The smith says: What was that?\n");
    add_ask(({"khiraa","Khiraa"}),"The Cult of the Dead, in the ancient "+
    "tongue. Lord Gylar was head of it, untill he died in the Great "+
    "Battle.\n");
    add_ask(({"king","King"}),"The smith weeps.\n");
    set_title("The Smith");
    equip(DRAKMERE_WEP_DIR + "hammer");
}

void
do_die(object who)
{
    who->inc_prop(IS_ENEMY_OF_DRAKMERE,1);
    ::do_die(who);
}
