/* created by Aridor 05/19/94 */

inherit "/d/Krynn/common/monster/kender_base";

#include "/ss_types.h"
#include "../local.h"
#include <macros.h>

void
create_kender()
{
    int i;

    switch(random(4))
    {
    case 0: set_adj("sneaky");
            break;
    case 1: set_adj("bouncy");
            break;
    case 2: set_adj("playful");
            break;
    case 3: set_adj("small");
            break;
    }

    for(i = 0; i < 6; i++)
        set_base_stat(i,random(20)+20);
    set_hp(2000);
    set_skill(SS_DEFENCE, 20 + random(10));
    set_skill(SS_PARRY, 20 + random(10));
    set_skill(SS_WEP_KNIFE, 40 + random(5));

    set_long("This kender is enjoying himself thoroughly.\n");

    add_act("smile");
    add_act("bounce");
    add_act("jump");
    add_act("laugh");
    add_act("giggle");
    add_act("say As soon as I have mapped this area, I'll open a "
          +  "cartographer's shop!");

    set_cact_time(10);
    add_cact("smile");
    add_cact("wield all");

    if (IS_CLONE)
      set_alarm(1.0,0.0,"fill_pockets");
}

void
fill_pockets()
{
    seteuid(getuid(TO));
    my_stuff = ({});
    my_stuff += ({ clone_object(OBJ + "map")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "feather")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "stone")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "kknife")->move(TO) });
/* some more objects in here! and some randomness, please! */

}

