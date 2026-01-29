/*
 *     /d/Gondor/rohan/isengard/master.c
 *
 *     Master file to steer change in Isengard.
 *     Optionally, this change is to be independent of the Ring
 *     Quest progress, so Isengard could be destroyed even if the
 *     Ring Quest fails, or Isengard could escape destruction even 
 *     if the Ring Quest succeeds.
 *
 *     Copyright (c) 1996 by Christian Markus and Brian Smaakjaer
 *     Copyright (c) 1997 by Christian Markus
 *
 *     The chronology of the War in Rohan in 3019 TA:
 *     Midsummer 3018 - ~15 Sep 3018: Gandalf prisoner in Orthanc,
 *             Saruman reveals himself as enemy of Rohan.
 *     25 Feb: First Battle of the Isen, death of Theodred, Theoden's
 *             son. 
 *      2 Mar: Theoden rides from Edoras.
 *             Second Battle of the Isen, Erkenbrand defeated.
 *             Ents reach Isengard.
 *             Saruman's army marches out of Isengard.
 *      3 Mar: Theoden arrives at Helm's Deep.
 *             Ents attack Isengard.
 *             Saruman lays siege to the fortress.
 *      4 Mar: Theoden rides from Helm's Deep, Saruman's army
 *             defeated.
 *      5 Mar: Theoden arrives at Orthanc.
 *      ? ???: Treebard permits Saruman to depart from Orthanc.
 *      ? ???: Elessar arrives at Orthanc.
 *      
 *     The following stages are distinguished:
 *     Stage 'Peace':   The period until Saruman declares himself to
 *                      Gandalf on Midsummer's Day 3018. 
 *                      Isengard peacefully, no open preparations for
 *                      war. Orcs and smithies hidden.
 *     Stage 'Hostile': The period until the First Battle of the
 *                      Isen. War preparations inside Isengard.
 *     Stage 'War':     Open war against Rohan.
 *                      Orcs in the valley of the Isen and on both
 *                      sides of the Fords of the Isen. 
 *     Stage 'Battle':  Battle of the Hornburg, starting with the
 *                      armies of Saruman marching out of Isengard.
 *                      Isengard denuded of orcs and dunlendings.
 *     Stage 'Victory': Isengard conquered by the Ents. Saruman
 *                      captive in Orthanc.
 *     Stage 'Defeat':  Saruman victorious, Rohirrim defeated.
 *
 *     Modification log:
 *     16-Jul-1997, Olorin: set_isen_stage(), update_isen_stage(),
 *                          isen_stage_desc()
 */
#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "defs.h"

#define SAVE_FILE (ISEN_DIR + "master")
/* 
 * War in Rohan time definitions:
 *                           from                      stage begins on
 *                           common/lib/rohan_time.h   year month  day
 */
#define ROHAN_STAGE_DATE  ({ ROHAN_STAGE_PEACE,     ({ 3017,    9,  22 }), \
			     ROHAN_STAGE_HOSTILE,   ({ 3018,    7,   1 }), \
	    	       ROHAN_STAGE_GANDALF_ESCAPED, ({ 3018,    9,  20 }), \
			     ROHAN_STAGE_WAR,       ({ 3019,    2,  25 }), \
			     ROHAN_STAGE_BATTLE,    ({ 3019,    3,   2 }), \
			     ROHAN_STAGE_DEFEAT,    ({ 3019,    3,   4 }), \
			     })

/*
 *     Prototypes:
 */
private void    update_isen_stage();
public string   long_desc();
public string   isen_stage_desc(int stage = -1);
public string   exa_clock();

/*
 *     Global variables:
 */
private int     Isen_Stage;

private static  mixed   Rohan_Dates = ROHAN_STAGE_DATE;
static  object  RQ_Master,
                Clock;

/*
 * Function name: create_gondor
 * Description:   room creator
 */
public void
create_gondor()
{
    restore_object(SAVE_FILE);

    RING_QUEST_MASTER->load_me();
    RQ_Master = find_object(RING_QUEST_MASTER);
    CLOCK->load_me();
    Clock = find_object(CLOCK);

    update_isen_stage();

    set_short("Isengard control room");
    set_long(long_desc);

    add_exit(ISEN_DIR   + "isengate",            "gates",  0, 0);
    add_exit(MORDOR_DOM + "ringquest/rq_master", "quest",  0, 0);
    add_exit(GONDOR_DIR + "workroom",            "gondor", 0, 0);

    add_item(({"clock", "time", }), exa_clock);
}

public string
long_desc()
{
    return 
	"This is the master object for steering the development "
      + "of the War in Isengard and Rohan. There is a clock giving "
      + "information on the state of affairs in Middle Earth.\n"
      + isen_stage_desc() + "\n";
}

/*
 * Function name: update_isen_stage
 * Description:   Adjust the value of Isen_Stage according to the date.
 */
private void
update_isen_stage()
{
    int     days,
            step, s,
            stage;

    if (!objectp(Clock))
	Clock = find_object(CLOCK);
	
    days = Clock->query_third_age_days();

    for (step = 0, s = sizeof(Rohan_Dates); step < s; step += 2)
    {
	if ((Isen_Stage < Rohan_Dates[step]) &&
	    (days >= Clock->query_third_age_days
	    (Rohan_Dates[step+1][0], 
	     Rohan_Dates[step+1][1], 
	     Rohan_Dates[step+1][2])) )
	{
	    Isen_Stage = Rohan_Dates[step];
	    if ((Rohan_Dates[step] == ROHAN_STAGE_DEFEAT) && random(2))
		Isen_Stage = ROHAN_STAGE_VICTORY;
	    log_file("rq_stage", "Rohan Stage updated to " +
		Rohan_Dates[step] + " at " + Clock->query_time() +
		" of " + Clock->query_date() + ". (" +
		ctime(time()) + ").\n");
	    save_object(SAVE_FILE);
	}
    }
}

/*
 * Function name: query_isen_stage
 * Description:   Returns the current value of Isen_Stage
 * Returns:       value of Isen_Stage
 */
public int
query_isen_stage()
{
    update_isen_stage();
    return Isen_Stage;
}

/*
 * Function name: set_isen_stage
 * Description:   Set the value of Isen_Stage
 *                Can only be increased.
 * Argument:      New value.
 * Returns:       1/0
 */
public int
set_isen_stage(int new_stage)
{
    int     step = 0;
    object  p_obj;
    string  msg = "",
            name;

    if (new_stage <= Isen_Stage)
	return 0;

    while (objectp(p_obj = previous_object(--step)))
    {
	msg += "\t(" + (-step) + ") ";
	if (interactive(p_obj))
	    msg += CAP(p_obj->query_real_name());
	else if (strlen(name = p_obj->query_name()))
	    msg += name + " (" + file_name(p_obj) + ")";
	else
	    msg += file_name(p_obj);
	msg += "\n";
    }
		
    if (!objectp(Clock))
	Clock = find_object(CLOCK);
    log_file("rq_stage", "Rohan Stage set by\n" + msg + 
	     "from " + Isen_Stage + " to " + new_stage + 
	     " on " + Clock->query_date() + ". (" +
	     ctime(time()) + ").\n");

    Isen_Stage = new_stage;
    save_object(SAVE_FILE);
    return 1;
}

/*
 * Function name: isen_stage_desc
 * Description:   describes the present stage of the War in Rohan
 * Argument:      the stage
 * Returns:       the description
 */
public string
isen_stage_desc(int stage = -1)
{
    string  text;

    if (stage < 0)
    {
	update_isen_stage();
	stage = Isen_Stage;
    }

    switch (stage)
    {
    case ROHAN_STAGE_PEACE .. ROHAN_STAGE_PEACE_END:
	return "There is peace in Rohan and in Isengard.";
	break;
    case ROHAN_STAGE_HOSTILE .. ROHAN_STAGE_HOSTILE_END:
	text = "Isengard is preparing for war";
	if (stage < ROHAN_STAGE_GANDALF_ESCAPED)
	    text += ", and Gandalf is prisoner of Saruman.";
	else
	    text += ". Gandalf has escaped from his captivity.";
	return text;
	break;
    case ROHAN_STAGE_WAR .. ROHAN_STAGE_WAR_END:
	return "There is war in Rohan at the fords of the Isen.";
	break;
    case ROHAN_STAGE_BATTLE .. ROHAN_STAGE_BATTLE_END:
	return "Theoden King has ridden to war to Helm's Deep.";
	break;
    case ROHAN_STAGE_DEFEAT:
	return "Saruman has conquered the Rohirrim.";
	break;
    case ROHAN_STAGE_VICTORY:
	return "The Rohirrim and the Ents have conquered Saruman and Isengard.";
	break;
    default:
	return "Stage number " + stage + " is undefined!";
	break;
    }
}

/*
 * Function name: exa_clock
 * Description:   VBFC for the description of the clock in this room.
 * Returns:       the description
 */
string
exa_clock()
{
    return RING_QUEST_MASTER->exa_clock();
}

public int
reset_isen_stage()
{
    int     step;
    object  p_obj;
    string  name,
            msg = "";

    if (previous_object() != Clock)
    {
        msg += "\n";
        while (objectp(p_obj = previous_object(--step)))
        {
            msg += "\t(" + (-step) + ") ";
            if (interactive(p_obj))
                msg += CAP(p_obj->query_real_name());
            else if (strlen(name = p_obj->query_name()))
                msg += name + " (" + file_name(p_obj) + ")";
            else
                msg += file_name(p_obj);
            msg += "\n";
        }
    }
    else
        msg += " the ME clock";

    // Reset the stage:
    if (Isen_Stage < ROHAN_STAGE_DEFEAT)
        return 0;
    Isen_Stage = ROHAN_STAGE_PEACE;
    save_object(SAVE_FILE);
    log_file("rq_stage", "Rohan Stage reset by" + msg + 
             " on " + Clock->query_date() + ". (" +
             ctime(time()) + ").\n");

    update_isen_stage();

    return 1;
}

