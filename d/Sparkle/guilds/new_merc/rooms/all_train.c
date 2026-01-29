/*
 *  /d/Sparkle/guilds/new_merc/adapt_train.c
 *
 *  This room is never to be accessible by mortal feet. The purpose is
 *  for it to be a hidden object that grants a potential of 100 in
 *  every mudlib skill to guild members so that in the event they use
 *  their adaptability to reach 100, they will not suffer skill decay.
 *  However, they will *never* be able to actually train these levels.
 *  All adaptability levels are granted using set_skill_extra(), and
 *  the levels contained in the player's merc datafile.
 *
 *  Created January 2009, by Cooper Sherry (Gorboth)
 *
 *
 *  2021-03-28 - Cotillion
 *  - This room is no longer actually needed
 */
#pragma strict_types

inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <macros.h>
#include "../merc_defs.h"

/* Prototypes */
public void        create_room();
public void        set_up_skills();
public void        init();
// public varargs int sk_query_max(int snum, int silent);




/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("Mercenary Hidden Training Room");
    set_long("This is the " + GUILD_NAME + " adaptation training room."
      + " It is not accessible by players. The purpose of this room is"
      + " to prevent skill decay to skills that have been enhanced"
      + " with the <adapt> skill of the Mercenary guild.\n");

    setuid();
    seteuid(getuid());

    /* configure the trainer */
    set_up_skills();
} /* create_room */


/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
public void
set_up_skills()
{
    int     *v_skills = MERC_MASTER->query_skillnum_index();

    create_skill_raise();
  
    /*
    foreach (int v_skill: v_skills)
    {
        sk_add_train(v_skill,
            "use " + SS_SKILL_DESC[v_skill][0],
            SS_SKILL_DESC[v_skill][0],
            SS_SKILL_DESC[v_skill][1],
            100);
    }
    */
} /* set_up_skills */


/*
 * Function name:        init
 * Description  :        add the skill-raise actions to the player
 */
public void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
} /* init */


#ifdef ROOM_ENABLED
/*
 * Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 *
 * The mask of this function is to control the skill level players in
 * the Army are able to train to, and the level to which skill decay
 * will be applied.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    object *obs,
           *otmp;
    int     guild_lvl,
            enhance_lvl;

    /* Get the list of trainer objects */
    obs = ({});
    otmp = this_player()->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_player()->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_player()->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_player()->query_guild_trainer_craft();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    obs -= ({ 0 });
    obs -= ({ MASTER_OB(this_object()) });

    guild_lvl = applyv(max, map(obs, &->sk_query_max(snum)));
    MERC_MASTER->check_enhance_map(this_player());
    enhance_lvl = MERC_MASTER->get_info(
                      this_player(), "skill_enhance")[snum];

    return min((guild_lvl + enhance_lvl), 100);
} /* sk_query_max */
#endif
