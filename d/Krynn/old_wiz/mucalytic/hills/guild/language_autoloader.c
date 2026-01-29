/* Autooad the language soul. ~mucalytic/hills/guild/language_autoloader */

inherit "/std/object";

#include "../defs.h"
#include "/sys/stdproperties.h"

void create_object()
{
    set_name("sign_language");
    set_long("This object means that the player is a member of the "+
        LANGUAGE_GUILD+".\n");

    set_no_show();

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

void init()
{
    ::init();

    set_alarm(1.0, 0.0, "add_soul");
}

void add_soul()
{
    int i;
    object player;
    string *souls;

    player = E(TO);

    souls = player->query_cmdsoul_list();

    for (i = 0; i < sizeof(souls); i++)
        player->remove_cmdsoul(souls[i]);

    player->add_cmdsoul(GUILD + "language_soul");

    for (i = 0; i < sizeof(souls); i++)
        player->add_cmdsoul(souls[i]);

    player->update_hooks();
}

string show_subloc(string subloc, object me, object for_obj)
{
    if(me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return("You are a member of the "+LANGUAGE_GUILD+".\n");

    if(for_obj == me)
        return("You are a member of the "+LANGUAGE_GUILD+".\n");
    else
        if(for_obj->query_member_guild(LANGUAGE_GUILD))
            return(C(PRONOUN(me))+" is also a member of the "+LANGUAGE_GUILD+".\n");
}

void enter_env(object to, object from)
{
    to->add_subloc("language_autoloader", TO);

    ::enter_env(to, from);
}

void leave_env(object from, object to)
{
    from->remove_subloc("language_autoloader");

    ::leave_env(from, to);
}

string query_auto_load()
{
    return GUILD + "language_autoloader:";
}
