/* Stralle @ Genesis 010705
 *
 * Cloned into a player when issuing the council command honour
 * to bestow a temporary title to the player
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include <macros.h>
#include "../guild.h"

int gTime;
string gTitle;

void
set_time(int days)
{
    gTime = time() + 86400 * days;
}

void
set_title(string title)
{
    gTitle = title;
}

void
create_object()
{
    set_name("_pot_honour_ob");
    set_long("This is not supposed to be seen. In the unlikely event " +
        "that you do, please pretend that you did not.\n");
    
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

void
enter_env(object dest, object old)
{
    object shadow;

    ::enter_env(dest, old);

    if (time() >= gTime)
    {
        set_alarm(0.0, 0.0, &remove_object());
        find_player("stralle")->catch_tell("[honour] Removing.\n");
        return;
    }
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(GUILDDIR + "obj/honour_shadow");
    shadow->set_title(gTitle);
    if (!shadow->shadow_me(dest))
    {
        /* Bring out the sledgehammer */
        SECURITY->do_debug("destroy", shadow);
        dest->catch_tell("Please contact " +
            COMPOSITE_WORDS(map(GUILDMASTERS, capitalize)) +
            " to work out a wrongness in the fabric of space caused by " +
            "_pot_honour_shadow.\n");
    }
}

string
query_auto_load()
{
    return MASTER + ":|:|" + gTitle + "|:|" + gTime + "|:|";
}

void
init_arg(string arg)
{
    string foobar, str; 
    int t;
    
    find_player("stralle")->catch_tell("init_recover: str = \"" +
       arg + "\"\n");

    sscanf(arg, "|:|%s|:|%d|:|", str, t);

    set_title(str);
    gTime = t;
}
