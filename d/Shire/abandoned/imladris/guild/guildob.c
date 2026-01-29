/*
 * guildob.c
 *
 * The 'guild' object for the Sula Imladris.
 *
 * Sir Rogon, 1993
 *
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "guild.h"

static int initiated;	/* Keep track if the object is initated or not */

void
create_object()
{
    set_name("_sula_imladris_");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_NO_DROP, "You remember to greet the Healers.\n");
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    setuid(); seteuid(getuid(TO));
    set_no_show();
    initiated = 0;
}

string
query_auto_load()
{
    return MASTER + ":";
}

void
init()
{
    if (!IS_CLONE)
	return;
    if (!initiated)
	call_out("initiate", 2, TP);
}

int
new_sula(object newbie)
{
    string name, str;
    object sh;

    name = newbie->query_real_name();

    if (present("_sula_imladris_", newbie) ||
	!query_ip_number(newbie) ||
	file_size(PL_BAN + name + ".o") != -1 ||
	newbie->query_prevent_shadow())
	return 0;

    str = read_file(PL_SAVE + "new/newbie.o");
    write_file(PL_SAVE +  name + ".o", str);
    sh = clone_object(GUILD_SHADOW);
    if(!sh) {
	write("Shadow corrupt.\n");
	return 0;
    }
    if(sh->shadow_me(newbie,GUILD_TYPE, GUILD_STYLE, GUILD_NAME)!=1) {
	write("Somehting went wrong. Can't shadow!\n");
	return 0;
    }
    if (newbie->query_wiz_level())
	write("You must now perform \"cmdsoul " + GUILD_SOUL + "\" and \"newhooks\" in order to get the proper soul commands as well.\n");
    TO->move(newbie, 1);
    TP->set_bit(1, 0);
    return 1;
}

void
initiate(object me)
{
    string name;

    name = me->query_real_name();
    if (!query_ip_number(me) ||
	 file_size(PL_BAN  + name + ".o") != -1 ||
	 file_size(PL_SAVE + name + ".o") == -1 )
    {
	write("You are thrown out of the guild!\n");
	remove_object();
	return;
    }
    me->init_spell_souls();
    initiated = 1;
    log_file("init.guild", ctime(time())+":"+CAP(name)+" initiated.\n");
    cat(INTRO_FILE);
}
