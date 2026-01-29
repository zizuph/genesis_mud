
 /* Pichno Object to block an exit
  * by Jaacar
  * November, 1997
  */

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include WIND_HEADER

string blocked_exit = "";

public void set_blocked_exit(string exit);
public string query_blocked_exit();
public void set_remove_time(int i);
varargs public int dispel_spell_effect(object dispeller);

public int
start()
{
    set_spell_effect_desc("pincho");

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
    set_name("debris");
    add_name("wall of debris");
    set_short("wall of debris");
    set_long("@@debris_long");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "prayer"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This wall of debris does not seem to "+
        "be able to be penetrated unless you are protected by the forces "+
        "of air and electricity.\n", 40}));
    add_prop(MAGIC_I_RES_IDENTIFY, 40);
    add_prop(MAGIC_I_RES_AIR, 40);
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
        write("You walk unharmed through the wall of debris.\n");
        say(QCTNAME(this_player())+" walks through the wall of debris "+
            "unhindered and unharmed.\n");
        return 0;
    }
    if (is_walker(this_player()))
    {
        write("You quickly step through the debris unhindered and unharmed.\n");
        say(QCTNAME(this_player())+" steps through the debris, uneffected by them.\n");
        return 0;
    }
    if (TP->query_magic_res(MAGIC_I_RES_ELECTRICITY) > 40)
    {
        write("You boldy step through the debris unhindered and unharmed.\n");
        say(QCTNAME(this_player())+" boldy steps through the debris unharmed.\n");
        return 0;
    }
    write("You attempt to leave through the "+blocked_exit+" exit, but "+
        "as you approach the debris you sense you would be badly hurt "+
        "and decide it would not be wise to do so.\n");
    say(QCTNAME(this_player())+" appears as though "+this_player()->query_pronoun()+
        " is going to leave through the "+blocked_exit+" exit but decides against "+
        "it at the last second.\n");
    return 1;
}

public void
remove_object()
{
    tell_room(environment(this_object()),"The wall of debris dies down, "+
        "leaving no trace of itself.\n");
    dispel_spell_effect(spell_target);
    ::remove_object();
}

public void
set_remove_time(int i)
{
    set_alarm(itof(i), 0.0, remove_object);
}

public string
debris_long()
{
    string description;
    description = "It appears to be a large wall of debris ";
    description += "blocking the "+blocked_exit+" exit.\n";
    return description;
}
