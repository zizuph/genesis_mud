/* File         : /d/Khalakhor/std/npc/talamhdubh.c
 * Creator      : Teth@Genesis
 * Date         : Jan 27, 2002         
 * Purpose      : Khalakhor standard talamhdubh npc.   
 * Related Files: /std/monster.c
 *                /d/Khalakhor/std/monster.c
 * Comments     : What is a Talamhdubh? Literally, it means 
 *                "earth black". It is an original creation. I'll
 *                maintain to my grave that it is not inspired 
 *                whatsoever by the Balrog from LoTR or the Earth
 *                Elementals from Heroes of Might and Magic III.
 *                The talamhdubh is an ancient golem-type creature
 *                that is bred of earth and molten lava. However,
 *                it is intelligent and able to speak. These
 *                creatures are intended to be nasty.
 * Modifications: 
 * TODO         : Alter it so that it gives a pile of rubble as a corpse.
 *                Within that rubble, have gems. Re: the lightning cloud
 *                formed from the lethal evilfaced dracs.
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

inherit STDMONSTER;

public void
reset_khalakhor_talamhdubh()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_talamhdubh();
}


/* Function name:  create_khalakhor_talamhdubh
 * Description:    The constructor function
 *                 used to create the talamhdubh
 */
public void create_khalakhor_talamhdubh()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_talamhdubh to
 *                 create your talamhdubh.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_talamhdubh");
    set_race_name("talamhdubh");

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_QUICKNESS, 10);
    add_prop(LIVE_I_SEE_DARK, 15);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(OBJ_I_RES_ACID, 95);
    add_prop(OBJ_I_RES_EARTH, 95); 
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_DEATH, 50);
    add_prop(OBJ_I_RES_ELECTRICITY, 50);
    add_prop(OBJ_I_RES_LIFE, 10);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(OBJ_I_RES_WATER, 10);

    create_khalakhor_talamhdubh();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_talamhdubh
 * Description  : Check to see if this is a Khalakhor talamhdubh.
 * Arguments    : n/a
 * Returns      : 1 - if a talamhdubh
 */
public int
query_khalakhor_talamhdubh()
{
    return 1;
}
