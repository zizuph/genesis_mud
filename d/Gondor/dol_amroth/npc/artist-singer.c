/* -*- Mode: C -*-
 *
 * npc/artist-singer.c
 *
 * By Skippern 20(c)01
 *
 * A singer
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

/* Prototypes */
public void        cant_see_in_room();
       void        sing();

public void
create_dunadan()
{
    set_living_name("telsa");
    set_name("telsa");
    set_adj("singing");
    add_name( ({ "dunadan", "artist", "singer" }) );
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("soprano");
    set_dunedain_house("Hador");
    set_long("This is an artist working with marble, he have marble " +
	"dust in her hair.\n");
    default_config_npc(55);

    set_base_stat(SS_INT, 80);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    set_alignment(350);

    set_chat_time(600);
    add_chat("I can many songs.");

    set_act_time(100);
    add_act(&cant_see_in_room());
    add_act(&sing());
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings " + capitalize(name) +".");
    command("introduce me to "+name);
    command("say You like my voice?");
    command("smile");
}

public void
add_introduced(string name)
{
    object    pl;
//    if (!objectp(pl = find_player(name)) ||
//        pl->query_met(query_real_name()))
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

    command("say Let there be light.");
    command("light lamp posts");
    if (CAN_SEE_IN_ROOM(this_object()))
        command("say And thus it was light.");
    return;
}

void
sing()
{
    string song;

    if(!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    song = one_of_list( ({"earendil", "elbereth", "gilthoniel", "snowwhite", 
			  "felagund", "gil-galad", "thalion", "tinuviel" }) );

    command("sing "+song);
}

