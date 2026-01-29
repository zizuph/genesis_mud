/*
 * Changelog:
 *  - Changed to use query_base_skill for guru quest. Reason is that
 *    bloodguards allowed draining of weapon skill.
 *    Petros, January 2009
 */

#pragma save_binary
#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include "/d/Krynn/clubs/warfare/defs.h"

inherit DRAGONARMY_BASE_SH;

#define SW shadow_who
#define ARMYMASTER  "/d/Krynn/common/warfare/armymaster"

mixed
query_guild_trainer_occ()
{
    return DRAGONARMY_ROOM + "train_blue";
}

int
query_guild_tax_occ() 
{
    int tax, pen, areas, total;

    switch(query_dragonarmy_promotions())
    {
    case 4: tax = 32; break;
    case 3: tax = 32; break;
    case 2: tax = 32; break;
    case 1: tax = 32; break;
    default: tax = 28;
    }

    if (ARMYMASTER->query_peace())
	return tax;

    total = sizeof(ARMYMASTER->query_areas());
    areas = sizeof(ARMYMASTER->query_areas_of_army("Blue Dragon Army"));
    pen = (total / 2) - areas;

    return tax + pen;
}

string
query_dragonarmy_division()
{
    return BLUE_ARMY;
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
#ifdef DRAGONARMY_BLUE_STARTLOC
    if (SW->query_default_start_location() == DRAGONARMY_BLUE_STARTLOC)
    {
	SW->set_default_start_location(SW->query_def_start());
    }
#endif

#ifdef DRAGONARMY_BLUE_SOUL
    SW->remove_cmdsoul(DRAGONARMY_BLUE_SOUL);
    SW->update_hooks();
#endif
}

void
delay_init_dragonarmy()
{
    setuid();
    seteuid(getuid());

    gTitles = BLUE_TITLES;

#ifdef DRAGONARMY_BLUE_SOUL
    SW->add_cmdsoul(DRAGONARMY_BLUE_SOUL);
    SW->update_hooks();
#endif

#ifdef DRAGONARMY_OCC_EMBLEM
    clone_object(DRAGONARMY_OCC_EMBLEM)->move(SW, 1);
#endif

    // Add to warfare system if not already a member.
    if(!IS_CLUB_MEMBER(SW))
    {
        CLUB_MANAGER->add_member(SW);
        CLUB_MANAGER->set_warfare_army(SW, "Blue Dragon Army");
        SW->catch_tell("You have been granted a dark steel chit " +
            "as token for supporting the Blue Dragonarmy in " +
            "the War of the Lance!\n");
    }

    // Clone the warfare club object
    if (!present("_warfare_club_object_", SW))
    {
        clone_object(WAR_OBJ)->move(SW, 1);
    }
}

/**************************************************************/
/************      guru quest support     *********************/
/**************************************************************/

void
reward_warfare_conquest(string area, string newarmy, string oldarmy)
{
    if (oldarmy == "Knights" &&
	newarmy == "Blue Dragon Army" &&
	SW->query_base_skill(SS_WEP_SWORD) == 90)
    {
	setuid();
	seteuid(getuid());
	SW->set_bit(3,0);
	SW->catch_tell("Well done! You may now get guru training.\n");
	log_file("dragonarmy_guru", extract(ctime(time()),4,15) +
	    ": " + SW->query_name() + " - BDA - " + area + "\n");
    }
}

// Dragon Following Support
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int result;
    object dragon;
    
    setuid();
    seteuid(getuid());
    result = SW->move_living(how, to_dest, dont_follow, no_glance);
    if (objectp(dragon = DRAGONS_MANAGER->query_summoned_strike_dragon(SW)))
    {
        dragon->follow_summoner();
    }
    
    return result;
}

