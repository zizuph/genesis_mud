#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit DRAGONARMY_BASE_SH;

#define SW shadow_who

mixed
query_guild_trainer_occ()
{
    return DRAGONARMY_ROOM + "train_blue";
}

int
query_guild_tax_occ() 
{
    switch(query_dragonarmy_promotions())
    {
    case 4: return 24;
    case 3: return 20;
    case 2: return 18;
    case 1: return 16;
    default: return 14;
    }
}

string
query_dragonarmy_division()
{
    return WHITE_ARMY;
}

mixed
query_guild_skill_name(int type)
{
    if(type == SS_DRAGONARMY_ATTACK)
	return "slash";

    return 0;
}

void
remove_dragonarmy_startlocation_souls_skills()
{
#ifdef DRAGONARMY_WHITE_STARTLOC
    if (SW->query_default_start_location() == DRAGONARMY_WHITE_STARTLOC)
    {
	SW->set_default_start_location(SW->query_def_start());
    }
#endif

#ifdef DRAGONARMY_WHITE_SOUL
    SW->remove_cmdsoul(DRAGONARMY_WHITE_SOUL);
    SW->update_hooks();
#endif
}

void
delay_init_dragonarmy()
{
    setuid();
    seteuid(getuid());

    gTitles = WHITE_TITLES;

#ifdef DRAGONARMY_WHITE_SOUL
    SW->add_cmdsoul(DRAGONARMY_WHITE_SOUL);
    SW->update_hooks();
#endif

#ifdef DRAGONARMY_OCC_EMBLEM
    clone_object(DRAGONARMY_OCC_EMBLEM)->move(SW, 1);
#endif
}
