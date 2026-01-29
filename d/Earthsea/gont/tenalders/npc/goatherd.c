/* coded by Amelia, 4/20/97 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include <stdproperties.h>

public void
create_earthsea_monster()
{
    set_name("goatherd");
    add_name("human");
    set_living_name("_sparrowhawk_");
    add_name(({"duny", "boy"}));
    set_adj(({"dark-haired", "young"}));
    set_long("A tall dark youth, whose fierce features "+
        "and eyes remind you of a hawk. His clothing and scruffy "+
        "appearance are those of a goatherd, yet his bearing is proud.\n");
    default_config_npc(30);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, "You feel the youth is "+
        "protected by unseen powers.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The boy raises "+
        "his hand in a gesture of defiance, shouting, Avert!\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_default_answer("The boy looks at you silently.\n");
    set_title("goatherd");
    set_act_time(60);
    set_chat_time(30);
}

/****************************************************************
 *  Hawk script
 *****************************************************************/

public void
look_up()
{
    command("emote looks up to the sky.");
}

public void
call_hawk()
{
    command("emote speaks a word in the language of the Making.");
}

public void
hawk_called()
{
    tell_room(environment(), "You hear the cry of a hawk, "+
        "as if in answer.\n");
}

public void
hawk_lands()
{
    tell_room(environment(), "Suddenly a large red-tailed "+
        "hawk stoops down from the sky, in a rush of wings.\n");
}

public void
hawk_alights()
{
    tell_room(environment(), "The hawk settles gracefully on "+
        "the youth's outstretched arm.\n");
    add_prop(LIVE_S_EXTRA_SHORT, " holding a hawk on his left arm");
    add_item("hawk",
        "As you look at the hawk, he stares back at you with fierce "+
        "yellow eyes.\n");
}

public void
pet_hawk()
{
    command("emote whispers to the hawk, stroking its "+
        "feathers.");
}

public void
send_away()
{
    command("emote says something to the hawk.");
}

public void
fly_away()
{
    command("emote lifts his arm, and the hawk flies off, "+
        "heading for the cliffs of High Fall.");
    remove_prop(LIVE_S_EXTRA_SHORT);
    remove_item("hawk");
}

public void
hawk_script()
{
    set_alarm(5.0, 0.0, look_up);
    set_alarm(10.0, 0.0, call_hawk);
    set_alarm(25.0, 0.0, hawk_called);
    set_alarm(35.0, 0.0, hawk_lands);
    set_alarm(41.0, 0.0, hawk_alights);
    set_alarm(55.0, 0.0, pet_hawk);
    set_alarm(65.0, 0.0, send_away);
    set_alarm(90.0, 0.0, fly_away);
}
