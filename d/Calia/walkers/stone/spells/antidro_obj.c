
 /* Antidro Object to block an exit
  * by Jaacar
  * November 7th, 1998
  */

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include STONE_HEADER

string blocked_exit = "";

public void set_blocked_exit(string exit);
public string query_blocked_exit();
public void set_remove_time(int i);
varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("antidro");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    remove_spell_effect_object();
    return 1;
}

public void
init()
{
    ::init();
    if (strlen(blocked_exit))
    {
        add_action("try_to_exit", blocked_exit);
    }
}

public void
create_object()
{
    set_name("flames");
    add_name("wall of stone");
    set_short("wall of stone");
    set_long("@@stone_long");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "prayer"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This wall of stone does not seem to "+
        "be able to be penetrated.\n", 40}));
    add_prop(MAGIC_I_RES_IDENTIFY, 40);
    add_prop(MAGIC_I_RES_EARTH, 40);
}

int
is_walker(object pl)
{
    return (pl->query_guild_name_occ() == GUILD_NAME);
}

public string
query_blocked_exit()
{
    return blocked_exit;
}

public void
set_blocked_exit(string exit)
{
    blocked_exit = exit;
}

public int
try_to_exit()
{
    if (this_player()->query_wiz_level())
    {
        write("Your body passes magically through the wall of stone.\n");
        say(QCTNAME(this_player())+" passes magically through the wall of stone.\n");
        return 0;
    }
    if (is_walker(this_player()))
    {
        write("Your body passes magically through the wall of stone.\n");
        say(QCTNAME(this_player())+" passes magically through the wall of stone.\n");
        return 0;
    }
    if (TP->query_magic_res(MAGIC_I_RES_EARTH) > 40)
    {
        write("Your body passes magically through the wall of stone.\n");
        say(QCTNAME(this_player())+" passes magically through the wall of stone.\n");
        return 0;
    }
    write("You attempt to leave through the "+blocked_exit+" exit, but "+
        "as you approach the stone wall you see no way around it.\n");
    say(QCTNAME(this_player())+" appears as though "+this_player()->query_pronoun()+
        " is going to leave through the "+blocked_exit+" but can't seem to find "+
        "any way through the wall of stone.\n");
    return 1;
}

public void
remove_object()
{
    tell_room(environment(this_object()),"The wall of stone suddenly "+
        "turns to dust and blows away in a gentle breeze.\n");
    dispel_spell_effect(spell_target);
    ::remove_object();
}

public void
set_remove_time(int i)
{
    set_alarm(itof(i), 0.0, remove_object);
}

public string
stone_long()
{
    string description;
    description = "It appears to be a large wall of stone ";
    description += "blocking the "+blocked_exit+" exit.\n";
    return description;
}
