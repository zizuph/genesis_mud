/*
 * Train hall of the Dunedain
 *
 * Modified from /d/Gondor/common/guild/lib/ranger_train.c
 *
 * Olorin, 14-nov-1994
 *
 * Revision History:
 *     Gorboth, 27-Oct-1997: Changed the room description to reflect
 *              the recent addition of mudlib support for <list guilds>.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";
inherit "/lib/guild_support.c"; 

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

#define HIS(x)		((x)->query_possessive())

static object  Trainer;

public void
create_gondor() 
{ 
    set_short("a vaulted chamber in the House of the Dunedain");
    set_long(BSN(
        "In this vaulted chamber members of the Houses of the Dunedain "
      + "can meditate to learn about themselves. In a corner there is "
      + "a thick carpet where they can sit down while meditating. "
      + "One may <list guilds>, and if the "
      + "Master of Arts is present, the dunedain can also improve their "
      + "skills here."));

    add_exit(GUILD_DIR + "rooms/hallw_s2", "north", 0, 0);

    ceiling();
    walls(1);
    floor(1);

    add_item(({"carpet", }), BSN(
        "A thick and valuable carpet. The dunedain use it to sit down upon "
      + "it while meditating."));

    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    FIX_EUID;
    reset_room();
}

public void
reset_room()
{
    Trainer = clone_npc(Trainer, GUILD_DIR + "npc/trainer");
}

public void
init() 
{
    ::init();

    init_guild_support();
}

int
gs_hook_already_meditate()
{
    write(BSN("You are already meditating. If you wish to finish "+
        "your meditation, simply 'rise' from the floor."));
    return 1;
}

void
gs_hook_start_meditate()
{ 
    write(BSN("You sit down on the thick carpet and close your eyes. "
      + "Employing the knowledge of body and mind that the dunedain "
      + "learned from the Noldor in the First Age, your spirit "
      + "disentangles itself from the confines of the material world "
      + "and reaches beyond the limits of Arda. "
      + "You find yourself able to <estimate> your different "
      + "preferences and <set> them at your own desire. "
      + "Just <rise> when you want your spirit to return to your body."));
    say(QCTNAME(TP) + " sits down on the carpet and closes "+HIS(TP)+" eyes.\n");
}

void
gs_hook_rise() 
{
    write(BSN("As you decide to return to the material world, your "
      + "spirit enters your body again and you feel that you can "
      + "control your body again. You feel enlightened and filled "
      + "with new insights about yourself as you rise from the carpet."));
    say(QCTNAME(TP) + " rises from the carpet.\n");
}

public int
sk_query_max(int skill, int silent)
{
    switch(skill)
    {
        case SS_HERBALISM:
        case SS_WEP_AXE:
        case SS_TRADING:
        case SS_SPELLCRAFT:
            return 50;
            break;
        default:
            return 0;
            break;
    }
}

