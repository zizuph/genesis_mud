
 /*  Test Occ Shadow     */
 /*  April 7th, 1998     */
 /*  Jaacar              */

#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"


static int prot;

public string *titles = ({"Title 1",
                          "Title 2",
                          "Title 3"});

string 
query_guild_style_occ() 
{ 
    return GUILD_STYLE;
}

string 
query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}

int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

void
greet()
{
    object who;
    object *members;
    
    seteuid(getuid());
    who = query_shadow_who();
    tell_object(shadow_who,"Welcome, "+query_guid_title_occ()+"!\n");
    setuid();
    seteuid(getuid());
    who->add_cmdsoul(TESTSOUL);
    who->update_hooks();
    members = filter(users(), &->is_member());
    if (!sizeof(members))
        return;
    map(members, &->catch_msg("A voice echoes through your "+
        "mind announcing that "+capitalize(shadow_who->query_real_name())+
        ", "+query_guild_title_occ()+" has entered the realms.\n"));

}

int
is_member()
{
    return 1;
}

int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow();
    set_alarm(1.5, 0.0, &greet());
}

int
query_guild_keep_player(object ob)
{
    return 1;
}

string
query_guild_title_occ()
{
    int stat;
    object who;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);

    seteuid(getuid());

    return titles[(MIN(2,(stat/3)))];
}

mixed
query_guild_trainer_occ()
{
    return ({ TEST_TRAINER });
}

