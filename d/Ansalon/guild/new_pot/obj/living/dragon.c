/* Stralle @ Genesis 040225
 */

#pragma strict_types

inherit "/d/Ansalon/guild/dragonarmy/dragons/dragon";

#include "../../guild.h"

void
set_summoner(object ob)
{
    summoner = ob;
    set_colour("black");
    switch (ob->query_priest_level())
    {
        case GUILD_LEVEL_PRIEST:
            size = 0;
            set_age("young");
            break;
        case GUILD_LEVEL_HIGH_PRIEST:
            if (GUILD_ADMIN->query_council_seat("leader") == 
                ob->query_real_name() ||
                GUILD_ADMIN->query_council_seat("inquisitor") ==
                ob->query_real_name())
            {
                size = 2;
                set_age("ancient");
            }
            else
            {
                size = 1;
                set_age("adult");
            }
            
            break;
        default:
            size = 0;
            set_age("young");
            break;
    }
}

void
check_back()
{
    if (!back)
    {
        setuid();
        seteuid(getuid());
        back = clone_object(GUILDDIROBJ + "dragon_back");
        back->set_dragon(this_object());
    }
}
