#pragma save_binary

inherit "/std/room.c";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <money.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"


/*
 * The Minstrel Guild Headquarters:  A practice cubicle.
 * A standard training room for the Minstrels.
 * 
 * Thanks to Styles for the function set_up_skills().
 * Jorl 2/93
 */
  
create_room()
{
    create_skill_raise();
    
    set_short("A Practice Cubicle");
    set_long(BS("This practice cubicle, like the others in the training "
    + "hall, is sound-proofed.  This is so your practice session doesn't "
    + "disturb anyone else.  You can pay the guild to train you in "
    + "various skills.\n"));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GUILD+"training", "east");
    
    set_up_skills();
}

int
query_occupied()
{
    object  *room_list;
    int	    i;
    
    room_list = all_inventory(TO());
    for (i=0;i<sizeof(room_list);i++)
    {
	if (interactive(room_list[i]))
	    return 1;
    }
    return 0;
}

init()
{
    add_action("no_shout", "shout");
    add_action("no_shout", "scream");
    init_skill_raise();
    ::init();
}

/* 
 * This allows for the training of skills for our guild.
 * SET_UP_SKILLS() was adapted from adv_guild Sparkle; 
 * written by Styles.
 */


set_up_skills()
{
    string me, ot;
/*       
    me = "understand languages"; ot = me; 
    sk_add_train(SS_LANGUAGE, ({me, ot}), "languages", 100, 60, SS_INT, 200);
    
    me = "sing the songs of power"; ot = me;
    sk_add_train(SG_VOCAL, ({me, ot}), "singing", 50, 100, SS_DIS, 200);
    
    me = "read music"; ot = me;
    sk_add_train(SG_READ_MUSIC, ({me, ot}), "read music", 50, 100, SS_INT, 200);
    
    me = "tune and repair instruments"; ot = me;
    sk_add_train(SG_TUNE_REPAIR, ({me, ot}), "instrument repair", 50, 100, SS_WIS, 200);
    
    me = "play instruments of every description"; ot = me;
    sk_add_train(SG_INSTRUMENTAL, ({me, ot}), "playing", 50, 100, SS_DEX, 200);
*/
    
    me = "sing the songs of power"; ot = me;
    sk_add_train(SG_VOCAL, ({me, ot}), "singing", 50, 60, SS_DIS, 200);
    
    me = "read music"; ot = me;
    sk_add_train(SG_READ_MUSIC, ({me, ot}), "read music", 50, 60, SS_INT, 200);
    
    me = "tune and repair instruments"; ot = me;
    sk_add_train(SG_TUNE_REPAIR, ({me, ot}), "instrument repair", 50, 60, SS_WIS, 200);
    
    me = "play instruments of every description"; ot = me;
    sk_add_train(SG_INSTRUMENTAL, ({me, ot}), "playing", 50, 60, SS_DEX, 200);
    
}

/* This makes it impossible to be heard in the next room.*/ 

no_shout()
{  
    TP()->catch_msg("This room is sound-proof; you cannot be heard!\n");
    return 1;	
}

public object
this_room()
{
    return this_object();
}
