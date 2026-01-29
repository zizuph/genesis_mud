inherit "/std/shadow";

#include <macros.h>
#include <cmdparse.h>
#include "../guild.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

#define TDIR                ("/d/Ansalon/goodlund/nethosak/chislev_temple/")
#define REFLECTION_ROOM     (BISLAND + "basement01")
#define LOREMASTER_ROOM     (ROOMS + "joinroom")
#define DRUID_ROOM          (TDIR + "temple_clearing")
#define SACRED_ROOM         (TDIR + "temple8")

#define TASK_RECEIVED       ("0x00")
#define DRUID_FOUND         ("0x01")
#define PRAY_CHISLEV        ("0x02")
#define DRYAD_CLEANSED      ("0x03")
#define BOW_RETRIEVED       ("0x04")

#define GURU_STAGES         ({  TASK_RECEIVED, DRUID_FOUND, PRAY_CHISLEV,      \
                                DRYAD_CLEANSED, BOW_RETRIEVED  })

public string           quest_stage;
public object           dryad_bow;

/*
 * Function name:   init_guru_shadow
 * Description:     Initialize the guru shadow
 * Arguments:       None
 * Returns:         Nothing
 */
void
init_guru_shadow()
{
    quest_stage = TASK_RECEIVED;
} /* init_guru_shadow */

/*
 * Function name:   remove_guru_shadow
 * Description:     Removes the guru shadow
 * Arguments:       None
 * Returns:         Nothing
 */
void
remove_guru_shadow()
{
    remove_shadow();
} /* remove_guru_shadow */

public void
set_guru_stage(string stage)
{
    quest_stage = stage;
}

public void
description_stages(int stage, object *targets)
{
    switch(stage)
    {
        case 1:
        targets->command("emote speaks in a calm demeanor: You have come "
        + "seeking the wisdom of Zivilyn and the guidance of Chislev. When you "
        + "are ready to proceed, we can 'begin the ritual'.");
            break;
        case 2:
        switch(quest_stage)
        {
            case TASK_RECEIVED:
            case DRUID_FOUND:
            targets->catch_msg("This is the location that the Loremaster "
            + "mentioned in his story, you would need to find the druids to "
            + "make sense of what to do here first.\n");
                break;
            case PRAY_CHISLEV:
            if (present("_archer_guru_quest_seed_", shadow_who))
            {
                targets->catch_msg("Here you may 'plant' the seed for it to "
                + "flourish.\n");
            }
                break;
        }
            break;
        case 3:
        if (file_name(environment(targets[0])) == SACRED_ROOM)
        {
            targets->catch_msg("As you enter the druid sanctuary, the " 
            + "statue in the north end of the chamber comes to life. The "
            + "elven statue extends her right arm in an elegant fashion, "
            + "and upon her palm rests a shimmering seed.\n\nA soothing voice "
            + "reaches your ears:\n   You must carry this seedling to the "
            + "pools of reflection, so that it may flourish. There you may "
            + "find what you seek.\n\nThe statue returns to normal as you "
            + "retrieve the seed.\n");
            
            setuid();
            seteuid(getuid());            
            object seedling;
            
            seedling = clone_object(GURU_SEEDLING);
            seedling->move(shadow_who, 1);
            set_guru_stage(PRAY_CHISLEV);
        }
            break;
        case 4:
        targets->command("say to " + OB_NAME(shadow_who) + " You have "
        + "succeeded where I have failed, and gained a splendid bow along the "
        + "way. Thank you for sharing this moment with me and finally abating "
        + "my curiosity.");
        
        targets->command("say to " + OB_NAME(shadow_who) + " As a token of "
        + "my appreciation, let me offer my blessing.");
        
        targets->command("emote chants in a faint tone as he places his "
        + "hand upon the dryad bow.");
        dryad_bow->set_hasted(1);
        
        set_alarm(0.0, 0.0, &remove_guru_shadow());
            break;
        case 5:
        targets->catch_msg("You have nothing more to learn from the "
        + "Loremaster.\n");
            break;
    }
}

/*
 * Function name:   move_living
 * Description:     Posts a move command for a living object somewhere. If you
 *                  have a special exit like 'climb tree' you might want to
 *                  use set_dircmd() and set it to 'tree' in the room to allow
 *                  teammembers to follow their leader.
 * Arguments:       how:      The direction of travel, like "north".
 *                            "X" for teleportation, team does not follow.
 *                            "M" if you write messages yourself.
 *                  to_dest:  Destination
 *                  dont_follow: A flag to indicate group shall not follow this
 *                               move if this_object() is leader
 *                  no_glance: Don't look after move.
 *
 * Returns:         Result code of move:
 *                        0: Success.
 *                        3: Can't take it out of it's container.
 *                        4: The object can't be inserted into bags etc.
 *                        5: The destination doesn't allow insertions of objects
 *                        7: Other (Error message printed inside move() func)
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    if (MASTER_OB(environment(shadow_who)) == REFLECTION_ROOM)
    {
        if (quest_stage == DRYAD_CLEANSED)
        {
            shadow_who->catch_msg("A soft voice echoes in your mind:\nYou "
            + "have cleansed me from corruption and freed my soul, but plan "
            + "to leave me in this dark abyss to rot away?\n\nThe willow "
            + "sprout glows softly from the center of the pool.\n");
            return 7;
        }
    }
    
    if (MASTER_OB(environment(shadow_who)) == DRUID_ROOM)
    {
        object *ob = filter(all_inventory(shadow_who),
                    &operator(==)(,"_druid_guru_ritual_") @ &->query_name());
        
        if (sizeof(ob))
            ob->remove_object();
    }
    
    return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
} /* move_living */

/*
 * Function name:   enter_env
 * Description:     When we enter an interactive environment, add a subloc to
 *                  indicate that the person is writing something.
 * Arguments:       (object) to - the object we are entering.
 *                  (object) from - the object we come from.
 * Returns:         Nothing
 */
void
enter_env(object to, object from)
{
    shadow_who->enter_env(to, from);
    
    switch(file_name(to))
    {
        case SACRED_ROOM:
        if (quest_stage == PRAY_CHISLEV)
        {
            set_alarm(1.0, 0.0, &description_stages(3, ({ shadow_who })));
        }
            break;
        
        case DRUID_ROOM:
        if (member_array(quest_stage, GURU_STAGES) > 1)
            return;
        
        object *druid, ritual;
        if (!sizeof(druid = FIND_STR_IN_ARR("_chislev_druid",
            all_inventory(environment(shadow_who)))))
            return;
        
        quest_stage = DRUID_FOUND;
        
        set_alarm(1.0, 0.0, &description_stages(1, druid));
        
        setuid();
        seteuid(getuid());
    
        ritual = clone_object(DRUID_RITUAL);
        ritual->move(shadow_who, 1);
        ritual->set_druid(druid[0]);
        
            break;
        
        case REFLECTION_ROOM:
        if (member_array(quest_stage, GURU_STAGES) < 3)
            set_alarm(1.0, 0.0, &description_stages(2, ({ shadow_who })));
            break;
        
        case LOREMASTER_ROOM:
        if (quest_stage != BOW_RETRIEVED)
        {
            set_alarm(1.0, 0.0, &description_stages(5, ({ shadow_who })));
        }
        else
        {
            object *loremaster = FIND_STR_IN_ARR("quillean",
                    all_inventory(environment(shadow_who)));
            
            if (!sizeof(loremaster) || !objectp(dryad_bow) ||
                !present(dryad_bow, shadow_who))
                return;
            
            set_alarm(1.0, 0.0, &description_stages(4, loremaster));
        }
            break;
            
    }
} /* enter_env */

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    shadow_who->enter_inv(ob, from);
    
    if (MASTER_OB(ob) == DRYAD_BOW)
    {
        set_guru_stage(BOW_RETRIEVED);
        dryad_bow = ob;
    }
} /* enter_inv */

/*
 * Function name: notify_you_killed_me
 * Description  : This routine is called in the killer when it causes the death
 *                of the victim. It can be used for additional processing.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Arguments    : object victim - the victim we caused to perish.
 */
void
notify_you_killed_me(object victim)
{
    if (MASTER_OB(victim) == GURU_DRYAD)
    {
        shadow_who->set_bit(GROUP, Q_BIT);
        set_guru_stage(DRYAD_CLEANSED);
    }
} /* notify_you_killed_me */