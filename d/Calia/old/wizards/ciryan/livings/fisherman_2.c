
inherit "/std/monster";

#include <defs.h>
#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>

void
create_monster()
{
set_name("fisherman");
set_adj("old");
add_name("man");
set_race_name("human");
set_short("old fisherman");
set_long("This is a old man about sixty years old. He has a wrinkled"+
         " weatherbeaten face from many years of hard work out on the"+
         " sea, and white hair and beard. He is short and skinny, with"+
         " an arched back making him look even smaller. Right now he"+
         " is working with some fishing nets spread out on the beach.\n");
set_stats(({20,25,35,15,30,30}));
set_skill(SS_WEP_KNIFE,40);
set_skill(SS_DEFENCE,30);
set_skill(SS_PARRY,30);

set_act_time(15);
add_act("emote grumbles unhappily over something.");
add_act("emote smiles wisely.");
add_act("emote crouches with pain.");
add_act("emote rises and limps around a little before he gets back to work.");

set_chat_time(15);
add_chat("What i dont know about the sea is not worth to know!");
add_chat("The sea-life is hard and demanding.");
add_chat("I remember long time ago when we caught a shark as big"+
        " as this boat.");
add_act("emote face brightens up.");
set_default_answer("The fisherman says: I don't know anything about that.\n");
}

dress_me()
{
object wep,arm;
seteuid(geteuid(TO));
wep=clone_object(CIR_OBJ+"fisher_knife.c");
wep->move(TO);
arm=clone_object(CIR_OBJ+"trousers.c");
arm->move(TO);
command("wield all");
command("wear all");
command("emote looks at you suspiciously.");
}
