/*
 * brownshort.c
 *
 * Owner of Snowhouse in Last.
 * Thanks to Khail of Khalakhor
 * Shinto, March 98
 */
#pragma strict_type

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public string
reply_kobold()
{
    command("say Oh you've come to help?");
    command("say If you follow the road west out of town "+
            "you will come to a fork.");
    command("say Take the northwest path and then the northeast.");
    command("say Thats the area they seem to be concentrated in.");
    command("say And thanks for coming!");
    command("thank all");
    return "";
}

public string
reply_giants()
{
    command("say The frost giants come down from the far north");
    command("say I tend to find a nice hole to hide in while the "+
                   "fighters of the town deal with them.");
    return "";
}

public string
reply_goblin()
{
    command("say Goblins are foul!  I really cannot stand goblins!");
    command("say They live up north and northwest, three seperate tribes.");
    command("say The Black Fang, Grim Claw, and Red Talon clans.");
    return "";
}

public string
reply_dragon()
{
    command("say Siralan, the great White, luckily for me, I'm so "+
                    "small he usually never even notices me. ");
    return "";
}

public string
reply_calathin()
{
    command("say Calathin lies southwest from here, "+
        "another small trading town likes ours. Head west till you "+
        "reach the cornerstone, then make your way south through "+
        "the Silver forest.");
    return "";
}



/*
 * Function name: create_monster
 * Description  : Turns this object into a landlord.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_monster()
{
    if (!IS_CLONE) 
	return;

    set_name("brownshort");

    set_living_name("brownshort");
    set_race_name("halfling");
    set_title("Littlehand, Owner of the Snowhouse of Last");
    add_name("owner");
    add_name("hobbit");
    set_adj("plump");
    add_adj("cheerful");
    set_long("A jovial sight, the well-mannered halfling greets you "+
                   "with a smile and bids you farewell with a wave and a "+
                   "wink. He's ready to take your order any time your ready.\n");

    default_config_npc(40);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);

    add_ask(({"siralan","Siralan","white","White","the White","dragon"}), 
                      reply_dragon, 1);
    add_ask(({"giants","giant","frost giants"}), reply_giants, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);
    add_ask(({"kobold","kobolds"}), reply_kobold, 1);

    enable_intro();
    set_alignment(400);
}
void
do_die(object killer)
{
    object kill_logger = find_object(LAST_DIR+"obj/kill_logger");
    kill_logger->add_killer(killer->query_name());
    ::do_die(killer);
}
public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}


