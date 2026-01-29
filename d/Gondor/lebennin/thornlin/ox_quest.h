/*
 *  /d/Gondor/lebennin/thornlin/ox_quest.h
 *
 *  Boromir, June 1995
 */

#define TH_OBJ_DIR	"/d/Gondor/lebennin/thornlin/obj/"

/*
 * pathname to the three horns
 */
#define THORNLIN_OX_DAMAGED_HORN_FILE	TH_OBJ_DIR + "horn_damaged"
#define THORNLIN_OX_HORN_FILE		TH_OBJ_DIR + "horn"
#define THORNLIN_OX_HUNTING_HORN_FILE	TH_OBJ_DIR + "hunting_horn"

/*
 * unique names for all three statues
 */
#define THORNLIN_OX_DAMAGED_HORN	"_thornlin_ox_damaged_horn"
#define THORNLIN_OX_HORN		"_thornlin_ox_horn"
#define THORNLIN_OX_HUNTING_HORN	"_thornlin_ox_hunting_horn"

/*
 * player solved the quest correctly
 */
#define THORNLIN_I_SOLVED_OX_QUEST	"_thornlin_i_solved_ox_quest"

/*
 * prop set by Hunthor when player receives the task
 * this prop should only be checked in Hunthor, as the player
 * should be able to solve the quest w/o receiving the task
 * from Hunthor first!
 */
#define THORNLIN_I_SENT_TO_THORNLIN	"_thornlin_i_sent_to_thornlin"

#define I_ASKED_HORN    "_live_i_asked_about_horn"
#define I_ASKED_HAMMER  "_live_i_asked_about_hammer"
#define I_KILLED_OX	"_live_i_killed_ox"

