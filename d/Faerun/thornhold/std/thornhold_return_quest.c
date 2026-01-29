#pragma no_clone
inherit "/d/Faerun/lib/quest_helper";
#include "/d/Faerun/sys/qbits.h"
#include "/d/Faerun/defs.h"

//#define QUEST_LOG_FILE(s, i)

#define QUEST_GROUP  THORNHOLD_QUEST_GROUP
#define QUEST_BIT    THORNHOLD_QUEST_BIT
#define QUEST_FILE   "/d/Faerun/thornhold/data/thornhold_return_quest"

#define THIMBLE_EXP   THORNHOLD_QUEST_1_EXP
#define INGOT_EXP     THORNHOLD_QUEST_2_EXP
#define GEAR_EXP      THORNHOLD_QUEST_3_EXP
#define LOUPE_EXP     THORNHOLD_QUEST_4_EXP
#define SPICE_EXP     THORNHOLD_QUEST_5_EXP
#define FULL_EXP      THORNHOLD_QUEST_EXP

#define THIMBLE_STEP 0
#define INGOT_STEP   1
#define GEAR_STEP    2
#define LOUPE_STEP   3
#define SPICE_STEP   4
#define FULL_STEP    5

public void
create_object()
{
    quest_group = QUEST_GROUP;
    quest_bit   = QUEST_BIT;
    quest_file  = QUEST_FILE;
    ::create_object();
}

public int
check_thimble(object qp)
{
    return check_quest_step(qp, THIMBLE_STEP);
}

public void
award_thimble(object qp)
{
    if(!check_thimble(qp))
        qp->add_exp_quest(THIMBLE_EXP);
    set_quest_step(qp, THIMBLE_STEP);
    QUEST_LOG_FILE("Return thimble to tailor", THIMBLE_EXP);
}

public int
check_ingot(object qp)
{
    return check_quest_step(qp, INGOT_STEP);
}

public void
award_ingot(object qp)
{
    if(!check_ingot(qp))
        qp->add_exp_quest(INGOT_EXP);
    set_quest_step(qp, INGOT_STEP);
    QUEST_LOG_FILE("Delivered ingot to arms merchant", INGOT_EXP);
}

public int
check_gear(object qp)
{
    return check_quest_step(qp, GEAR_STEP);
}

public void
award_gear(object qp)
{
    if(!check_gear(qp))
        qp->add_exp_quest(GEAR_EXP);
    set_quest_step(qp, GEAR_STEP);
    QUEST_LOG_FILE("Delivered gear to tinkerer", GEAR_EXP);
}

public int
check_loupe(object qp)
{
    return check_quest_step(qp, LOUPE_STEP);
}

public void
award_loupe(object qp)
{
    if(!check_loupe(qp))
        qp->add_exp_quest(LOUPE_EXP);
    set_quest_step(qp, LOUPE_STEP);
    QUEST_LOG_FILE("Delivered loupe to gem merchant", LOUPE_EXP);
}

public int
check_spice(object qp)
{
    return check_quest_step(qp, SPICE_STEP);
}

public void
award_spice(object qp)
{
    if(!check_spice(qp))
        qp->add_exp_quest(SPICE_EXP);
    set_quest_step(qp, SPICE_STEP);
    QUEST_LOG_FILE("Delivered ingot to arms merchant", SPICE_EXP);
}

public int
check_none(object qp)
{
    int steps = 0;
    steps += check_quest_step(qp, THIMBLE_STEP);
    steps += check_quest_step(qp, INGOT_STEP);
    steps += check_quest_step(qp, GEAR_STEP);
    steps += check_quest_step(qp, LOUPE_STEP);
    steps += check_quest_step(qp, SPICE_STEP);
    steps += check_quest_step(qp, FULL_STEP);

    if(steps == 0)
        return 1;
    return 0;
}

/* 
 *  This will return true only if all the steps are complete and the award is not yet awarded
 */
public int
check_full(object qp)
{
    int steps = 0;
    steps += check_quest_step(qp, THIMBLE_STEP);
    steps += check_quest_step(qp, INGOT_STEP);
    steps += check_quest_step(qp, GEAR_STEP);
    steps += check_quest_step(qp, LOUPE_STEP);
    steps += check_quest_step(qp, SPICE_STEP);
    steps += check_quest_step(qp, FULL_STEP);

    if(steps == 5)
        return 1;
        
    return 0;
}

public int
check_done(object qp)
{
    return check_quest_step(qp, FULL_STEP);
}

public void
award_full(object qp)
{
    if(!check_quest_step(qp, FULL_STEP))
        qp->add_exp_quest(FULL_EXP);
    complete_quest(qp);
    QUEST_LOG_FILE("Finished thornhold quest", FULL_EXP);
}
