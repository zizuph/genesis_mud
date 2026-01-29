/*
 * drow/lay/shadow.c
 *
 * This is the Shadow for the Drow layman guild.
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include "guild.h"

inherit "/std/guild/guild_lay_sh";

private static string title_string;

public int 
query_guild_tax_lay(void)
{ 
    return GUILD_TAX; 
}

public string
query_guild_style_lay(void)
{
    return GUILD_STYLE;
}

public string
query_guild_name_lay(void)
{
    return GUILD_NAME;
}

public string 
query_guild_title_lay(void)
{
    return title_string;
}

public void
set_guild_title_lay(string str)
{
    title_string = str;
}

private void
slow_init_lay_shadow(void)
{
    object gobject;

    shadow_who->add_cmdsoul(GUILD_SOUL);
    shadow_who->update_hooks();

    if (!objectp(gobject))
    {
	gobject = clone_object(GUILD_OBJECT);
	gobject->move(shadow_who, 1);
    }
}

public void
init_race_shadow(string arg)
{
    /* This has to be alarmed or bad things happen. */
    set_alarm(2.0, 0.0, &slow_init_lay_shadow());
    /* Reset the title of the player. */
    title_string = GSERVER->query_member_title(shadow_who);
}

public void
remove_object(void)
{
    GSERVER->update_last_active(shadow_who);
    ::remove_object();
}

/* Frontend to remove_guild_race to handle specific items. */
/* XXX Remember to add in a bit to reset startlocations as necesary */
public void
remove_guild_lay_drow(void)
{
    object gobject = present(GOBJECT_NAME, shadow_who);

    /* Clear stat and remove cmdsoul */
    shadow_who->clear_guild_stat(SS_LAYMAN);
    shadow_who->remove_cmdsoul(GUILD_SOUL);
    shadow_who->update_hooks();

    /* Remove the guild object, if present. */
    if (objectp(gobject))
	gobject->remove_object();

    /* Clear member from server. */
    GSERVER->check_deleted_player(shadow_who);

    /* Follow the chain to remove the shadow. */
    remove_guild_lay();
}

/* This gets called between the allow_join function
 * and the init_race_shadow one, so take care. */
public int
query_guild_keep_player(object player)
{
    string house, rank;

    /* Has the player switched races? */
    if (player->query_race_name() != "elf")
    {
	remove_guild_lay_drow();
	return 0;  /* Should not be reached. */
    }

    return 1;
}

/* We do not currently do anything more here. */
public int
query_guild_not_allow_join_lay(object player, string type, string style,
    				string name)
{
    setuid();
    seteuid(getuid());

    if (::query_guild_not_allow_join_lay(player, type, style, name))
	return 1;

    return 0;
}
