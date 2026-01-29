/* -*- Mode: C -*-
 *
 * npc/artist-painter.c
 *
 * By Skippern 20(c)01
 *
 * A painter that sells pictures.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define EMOTE_ARR  ({ "emote paints something on a piece of cloth.", "sigh", "ponder", \
                      "emote puts some paint on a piece of wook and draws his brush.", \
                      "ponder needs more sky.", "ponder too much sky." })

/* Prototypes */
public void        cant_see_in_room();
public void        do_my_act();

public void
create_dunadan()
{
    set_living_name("ian");
    set_name("ian");
    set_adj("dirty");
    add_adj("painting");
    add_name( ({ "dunadan", "artist", "painter" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("creatve painter");
    set_dunedain_house("Agarwaen");
    set_long("This is a famous painter.\n");
    default_config_npc(55);

    set_base_stat(SS_INT, 80);
    set_skill(SS_WEP_KNIFE, 15);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_APPR_OBJ, 75);
    set_skill(SS_APPR_VAL, 80);
    set_skill(SS_TRADING, 85);

    set_alignment(350);

    set_chat_time(600);
    add_chat("I hope I get this piece finished before the end of next month.");
    add_chat("Oh, there I was distracted again.");

    set_act_time(10);
    add_act(&cant_see_in_room());
}

public void
cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("say I better turn the lights on.");
    command("light lamp posts");
    command("scowl angr");
    command("say Damn this guards leaving this town.");
    return;
}

void
do_introduce(object pl, string name)
{
    command("emote looks up.");
    /*
    if (!present(pl, ENV(this_object())))
    {
	command("shrug");
	return;
    }
    */
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    if (IS_DUNADAN(pl))
        command("wellmet "+name);
    else if (pl->query_race() == "elf")
        command("elfhail "+name);
    else command("dsalute "+name);
    command("say Greetings, "+CAP(name)+".");
    command("introduce me to "+name);
    command("say Are you interested in a painting?");
}

public void
add_introduced(string who)
{
    object pl;
    /*
    if (!objectp(pl = find_player(who)) || 
	pl->query_met(query_real_name()))
        return;
    */
    set_alarm(5.0, 0.0, &do_introduce(pl, who));
}

public void
do_my_act()
{
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command(one_of_list(EMOTE_ARR));
}
