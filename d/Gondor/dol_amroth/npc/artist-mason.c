/* -*- Mode: C -*-
 *
 * npc/artist-mason.c
 *
 * By Skippern 20(c)01
 *
 * A mason that is going to be hammering on a marble block on a pier.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define RAND_EMOTE   ({ "sigh", "smile" })

/* Globale variables */
private object     marble, *ob;


/* Prototypes */
public void        cant_see_in_room();
       void        hammer();
       void        whipe();
       void        new_block();
       void        do_emote();

public void
create_dunadan()
{
    set_living_name("wilhelma");
    set_name("wilhelma");
    add_name( ({ "dunadan", "artist", "mason" }) );
    set_adj("dusty");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("artistic mason");
    set_dunedain_house("Beor");
    set_long("This is an artist working with marble, she have marble " +
	"dust in her hair.\n");
    default_config_npc(55);

    set_base_stat(SS_INT, 80);
    set_skill(SS_WEP_CLUB, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_APPR_OBJ, 75);
    set_skill(SS_APPR_VAL, 80);
    set_skill(SS_TRADING, 75);

    set_alignment(350);

    set_chat_time(600);
    add_chat("I hope I get this piece finished before the end of next month.");
    add_chat("Oh, there I was distracted again.");

    set_act_time(10);
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&hammer());
    add_act(&whipe());
    add_act(&do_emote());
    add_act(&cant_see_in_room());

    new_block();
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings " + capitalize(name) +".");
    command("introduce me to "+name);
    command("say Might I interest you in a statue?");
}

public void
add_introduced(string name)
{
    object    pl;
  
    //    if (!objectp(pl = find_player(name)) ||
    //       pl->query_met(query_real_name()))
    //        return;
  
    if (!CAN_SEE_IN_ROOM(this_object()))
	cant_see_in_room();
    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

public void
cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("say I better turn the lights on.");
    command("light lamp posts");
    return;
}

void
do_emote()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command(one_of_list(RAND_EMOTE));
    return;
}

void
hammer()
{
    if(!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    if(!objectp(marble))
    {
        command("say I'll get a new block of marble.");
	command("emote whistles loudly.");
	set_alarm(3.0, 0.0, &new_block());
	return;
    }

    command("emote hammers on the marble block.");
    marble->chip();
}

public void
whipe()
{
    if(!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command("emote whipes some sweat from her forehead.");
}

void
new_block()
{
    tell_room(environment(this_object()), "A wheeled chart enters from " +
	      "northwest, dumps off a marble block and leaves back " +
	      "where it came from.\n", 0, this_object());

    marble = clone_object(DOL_OBJ + "marble");
    marble->move(environment(this_object()), 1);
}







