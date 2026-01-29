/*      This is to be inherited into kroug npcs.

    coder(s):   Glykron
    history:
                 1. 9.93    created                         Glykron

    purpose:    to liven the kroug npcs

    quests:     none
    special:    none

    to do:      lots
    bug:        none known
*/

#include <filter_funs.h>
#include <cmdparse.h>
#include "defs.h"
#include MAP_HEADER
#include RANDOM_HEADER
#include CALIAN_HEADER
#pragma save_binary

inherit CALIA_NPC;

object *met_list;

void
create_kroug()
{
    set_race_name("kroug");
}

void
create_calia_npc()
{
/*
    object this;

    this = THIS;
    clone_object(GUILD_SHADOW)->shadow_me(this, GUILD_TYPE, GUILD_STYLE,
        GUILD_NAME);
    clone_object(MEDALLION)->move(this);
    call_out("add_calian_soul", 1);
    met_list = ({ });
    trig_new("%s 'introduces' %s", "introduce");
*/
    create_kroug();
}

/*
void
add_calian_soul()
{
    add_cmdsoul(CALIAN_SOUL);
    update_hooks();
}
*/

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("krougs", environment()), attacker);
}

/*
int
is_kroug_and_unmet(object living)
{
    return living->query_race_name() == "kroug" &&
        member_array(living, met_list) == -1;
}

int
introduce(string subj, string dummy)
{
    object this, *kroug_and_unmet;

    this = THIS;
    kroug_and_unmet = filter(FILTER_LIVE(all_inventory(environment(this))),
        "is_kroug_and_unmet", this);

    if (!sizeof(unmet))
        return 0;

    met_list += unmet;
    call_out("command", 1, "introduce me");
    return 0;
}
*/