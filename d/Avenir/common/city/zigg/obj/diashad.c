/*
 * - diashad.c
 *
 * Shadow to handle the quest-aspect of finding the diadem.
 */
#pragma strict_types

inherit "/std/shadow";

#include "zigg.h"
#include <stdproperties.h>

#define SOLVER	(ZIG_RL3 + "makeovers")

private static int timer;
private static object questor;
private static string *rooms = ({
    ZIG_RLG + "room[12]",
    ZIG_RL3 + "room[8]",
    ZIG_RL3 + "garden",
    ZIG_RL3 + "stairs",
    ZIG_RL3 + "candy",
    ZIG_RL3 + "bank",
    ZIG_RL3 + "post",
    ZIG_RL3 + "clips",
    ZIG_RL3 + "fetish",
    ZIG_RL3 + "perfumery",
});

#if 0
public void
test_move(void)
{
    int ran;
    object where;
    string room = one_of_list(rooms);

    /* Is this a series of rooms? */
    if (sscanf(room, "%s[%d]", room, ran) == 2)
	room += (random(ran) + 1);

    write("DIASHAD:  room == "+ room +"\n");

    if (file_size(room + ".c") < 1)
    {
	write("FAILURE:  file_size < 1\n");
	return;
    }

    if (!objectp(where = room->get_this_object()))
    {
	write("FAILURE:  couldn't load room.\n");
	return;
    }
    write("SUCCESS.\n");
}
#endif

private void
move_me_now(void)
{
    int ran;
    object where;
    string room = one_of_list(rooms);

    /* Is this a series of rooms? */
    if (sscanf("%s[%d]", room, ran) == 2)
	room += (random(ran) + 1);

    /* Hope we don't infinite recurse... */
    if (file_size(room + ".c") < 1)
	return move_me_now();

    /* Cross your fingers... */
    if (!objectp(where = room->get_this_object()))
	return move_me_now();

    /* Move us. */
    if (shadow_who->move(where))
	shadow_who->move(where, 1);

//tell_object(questor, "DIADEM:  I am located: "+ room +"\n");    
}

/*
 * Remove diadem and shadow if player went to sleep.
 */
private void
check_awake(void)
{
    if (objectp(questor))
	return;

    remove_alarm(timer);
    remove_object();
}

/*
 * Sets our questor and starts the alarm to see if they are awake.
 */
public void
set_questor(object who)
{
    questor = who;
    move_me_now();
    timer = set_alarm(3600.0, 3600.0, check_awake);
}

/*
 * We can only be found by our questor.
 */
public int
check_seen(object who)
{
    if (who != questor)
	return 0;

    if (!CAN_SEE_TRUE(who))
	return 0;

    return 1;
}

/*
 * Appear invisible as long as the shadow is active.
 */
public mixed
query_prop(string prop)
{
    if (prop == OBJ_I_INVIS)
	return 1;

    return shadow_who->query_prop(prop);
}

/*
 * Dest this shadow when picked up by questor.
 */
public varargs int
move(mixed dest, mixed subloc)
{
    shadow_who->move(dest, subloc);

    if (dest == questor)
    {
	set_alarm(0.0, 0.0, remove_shadow);
	SOLVER->set_solved(questor, ZQN_RYNAL);
    }
}

/* Just in case functions... */
public object
query_diadem_shadow(void)	{ return this_object(); }

public void
remove_diadem_shadow(void)	{ remove_shadow(); }
