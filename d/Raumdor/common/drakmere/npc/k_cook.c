inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_monster()
{
    ::create_monster();
    set_name("dandar");
    add_name("cook");
    set_race_name("human");
    set_adj("plump");
    add_adj("old");
    set_short("plump old cook");
    set_long("This plump old man is covered in flour. He has a big "+
    "black moustache that he smoothes with his fingers as he regards "+
    "you couriously.\n");
    set_stats(({40,50,60,80,80,40}));
    set_act_time(5);
    add_act("say Hallow thar!");
    add_act("say I cook the best food around!");
    add_act("emote checks the ovens.");
    add_act("emote whistles while he cooks");
    add_act("smile curious all");
    add_act("say Howdy all!");
    add_act("emote fills some pots and pans with water.");
    set_title("Cook of the Keep of Drakmere");
}

void
do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,1);
    ::do_die(who);
}
