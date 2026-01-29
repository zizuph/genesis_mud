/* Tika in the Inn of last homes */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit M_FILE

create_krynn_monster()
{
    int i;

    add_prop(LIVE_I_ALWAYSKNOWN,1);

    set_name("tika");
    set_living_name("tika");
    set_long("She is running around cleaning the tables.\n");
    set_race_name("human");

    add_act(({"bow","say Hello"}));
    add_act(({"smile","say Oh isn't this beautiful?","whistle"}));
    add_act(({"dance","say I like to work"}));
    add_act("bounce");
    set_act_time(10);

    set_knight_prestige(-3);

    set_gender(1);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 15+random(5));
    set_alignment(170);

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

}

init_living()
{
ADA("kiss");
    ADA("hug");
}
kiss(str)
{
if (str == "tika")
command("blush");
return 0;
}

hug(str)
{
    if (str == "tika")
	call_out("player_hug", 2, TP);
    return 0;
}

player_hug(ob)
{
    object ob2;

    command("blush");

    if ((ob2 = present("tour2", ob)) && (!ob2->query_arr("tika"))) 
    {
	ob2->set_arr("tika");
	command("say Well thank you.");
	seteuid(getuid(TO));
	if (!clone_object(OBJ + "potatoes")->move(ob))
	{
	    command("say Wait, I will give you something.");
	    write("You get some spiced potatoes from Tika.\n");
	    say(QCTNAME(ob) + " gets some spiced potatoes from Tika.\n");
	}
    }
}
