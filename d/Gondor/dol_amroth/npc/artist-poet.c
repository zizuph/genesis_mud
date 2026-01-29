/* -*- Mode: C -*-
 *
 * npc/artist-poet.c
 *
 * By Skippern 20(c)01
 *
 * A poet that is going to read poems.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include "poets.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

/* Prototypes */
public void        cant_see_in_room();
public void        read_a_poem();
public void        close_grate();

public void
create_dunadan()
{
    set_living_name("algorn");
    set_name("algorn");
    set_adj("ryme-talking");
    add_name( ({ "dunadan", "artist", "poet" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("poet");
    set_dunedain_house("Haladin");
    set_long("This poet is very good skilled in performance and poetry, " +
	     "just listen to him for a while.\n");
    default_config_npc(50);

    set_base_stat(SS_WIS, 65);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);
    set_skill(SS_LANGUAGE, 100);

    set_alignment(350);

    set_chat_time(600);
    add_chat("I know many poems, will you like to hear any?");
    add_chat("Maybe I should write another poem?");

    set_act_time(75);
    add_act(&read_a_poem());
    add_act(&read_a_poem());
    add_act(&read_a_poem());
    add_act(&read_a_poem());
    add_act(&cant_see_in_room());
    add_act(&close_grate());
    add_act(&close_grate());
    add_act(&close_grate());
    add_act(&close_grate());
    add_act(&close_grate());
}

public void
cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("say I better turn the lights on.");
    command("light lamp posts");
    if (!CAN_SEE_IN_ROOM(this_object()))
        command("say Whats happening?");
    else command("say Better!");
    return;
}

public void
close_grate()
{
    if (!CAN_SEE_IN_ROOM(this_object()))
	cant_see_in_room();

    command("close grate");
    return;
}

void do_bow() { command("bow"); }

public void
a_poem()
{
    command("emote reads with greate pato in his voice.");
    say("\n"+one_of_list(RAND_POETS)+"\n");
    set_alarm(1.0, 0.0, &do_bow());
}

public void
read_a_poem()
{
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command("say I would like to read a poem for you:");
    set_alarm(1.0, 0.0, &a_poem());
}

void
do_introduce(object pl, string who)
{
    command("smile happ");
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    if (IS_DUNADAN(pl))
        command("wellmet "+who);
    else if (pl->query_race() == "elf")
        command("elfhail "+who);
    else command("dsalute "+who);
    command("say Hello "+CAP(who)+".");
    command("introduce me to "+who);
    command("say Interested in poems?");
}

public void
add_introduced(string who)
{
    object pl;

    set_alarm(3.0, 0.0, &do_introduce(pl, who));
}












