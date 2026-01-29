/*
 * /d/Emerald/telberin/arts/minstrel_hall.c
 *
 * by Arman as part of the Minstrel recode, Nov 2019.
 */

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell";
inherit "/lib/skill_raise";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <money.h>
#include "/d/Terel/guilds/minstrels/guild_defs.h"

#define MIN_TRAINER "/d/Terel/guilds/minstrels/living/minstrel_trainer"

/* prototypes */
public void    create_emerald_room();
public void    reset_room();
public void    set_up_skills();

object trainer;

/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    create_skill_raise();

    set_short("the Outer Hall of the Minstrel's Guild");
    set_em_long("You stand within the grand Outer Hall of the "
        + "Minstrel's Guild of Telberin. Unparalleled as a school of music, "
        + "the Minstrel's Guild is exclusive in who it allows access to it's "
        + "halls, let alone those it grants training to in the ancient "
        + "Bardic traditions.\n");

    add_item( ({"outer hall", "hall", "grand outer hall", "halls"}),
        "This is the Outer Hall of the Minstrel's Guild of Telberin. Grand "
        + "and inspiring, renown performers travel from far and wide "
        + "to spend time here musing on their musical works or seeking "
        + "sponsorship for training to become a Master Bard of Telan-Ri.\n");

    add_item( ({"school", "school of music", "guild", "minstrel guild" }),
        "You stand within the Minstrel's Guild of Telberin, one of the "
        + "greatest schools of music in the realms and the halls where "
        + "the acclaimed Bards of Telan-Ri are trained.\n");

    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall4", "north");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall8", "east");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild_hall6", "west");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();

    // Set up the room as a training room
    create_skill_raise();
    set_up_skills();
} /* create_emerald_room */

/*
 * Function name:        reset_room
 * Description  :        
 */

public void
reset_room()
{
    if(!objectp(trainer))
    {
        trainer = clone_object(MIN_TRAINER);
        trainer->move(this_object(), 1);
    }

} /* reset_room */

init()
{
    init_skill_raise();
    ::init();
}

public void
set_up_skills()
{
    string me, ot;
       
    me = "understand languages"; ot = me; 
    sk_add_train(SS_LANGUAGE, ({me, ot}), "languages", 100, 60, SS_INT, 200);
    
    me = "entwine magic with music"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({me, ot}), "spellcraft", 100, 60, SS_INT, 200); 
}

/*
 * Function name: sk_hook_allow_train
 * Description:   Function called when player tries to do the improve command
 *                Will determine if a player can train skills here.
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                string - The string from sk_improve
 *                verb   - improve or learn typically
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int 
sk_hook_allow_train(object who, string str, string verb)
{  
    if(!objectp(trainer))      
    {
        who->catch_msg("There is no one here currently to train you.\n");
        return 0;
    }

    if(!MEMBER(who))      
    {
        who->catch_msg("Only lay minstrels can train with the Bards "
            + "here in the Outer Halls.\n");
        return 0;
    }

    return 1;
}
