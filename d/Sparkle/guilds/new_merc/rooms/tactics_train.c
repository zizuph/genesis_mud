/*
 *  /d/Sparkle/guilds/new_merc/rooms/tactics_train.c
 *
 *  Within the training grounds of the Mercenary Guild just northwest
 *  of the Lodge. Normally, only guild members are allowed in here
 *  (though I might make a backdoor for sneaky players!) This is
 *  the room which trains all non-weapon specific aspects of combat.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>


/* Prototypes */
public void        create_merc_room();
public void        set_up_skills();
public void        add_outdoor_tells();
public void        init();
public int         try_skills(string str);

/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("just northwest of the lodge in the training yard of the"
      + " Mercenary Guild");
    set_long("The training yard of the Mercenary Guild spreads out here"
      + " to the northwest of the old lodge. Many trainers are working"
      + " with various pupils on the tactics required to survive in"
      + " different combat situations, most of which can be learned"
      + " here if you are a member of the guild. It is possible to"
      + " <learn> or <improve> various skills here if the instructors"
      + " are willing to teach you. The training yard extends a ways"
      + " both to the east and south.\n\n");

    try_item( ({ "individual", "rugged individual", "individuals",
                 "rugged individuals", "trainer", "trainers",
                 "weapon trainer", "weapon trainers",
                 "instructor", "instructors" }),
        "The trainers here seem adept at all manner of fighting styles"
      + " and methods. You see some working with blindfolds, while"
      + " others are displaying the art of parrying incoming attacks."
      + " Many are using the stumps which prevail throughout the area"
      + " to faciliate their training purposes.\n");
    try_item( ({ "fence", "fences" }),
        "The fences which border the training yard are visible in the"
      + " distance to the east and south.\n");
    try_item( ({ "north", "clearcut", "clear-cut" }),
        "A clearcut strewn with numerous stumps spreads out between"
      + " this lawn and the river, which is to the north.\n");
    try_item( ({ "lawn", "wide lawn", "yard", "training yard",
                 "mercenary training yard", "training ground",
                 "training grounds" }),
        "These training grounds make up the entirety of the clear-"
      + "cut to the north and west of the lodge. Here, things seem to"
      + " be focused on tactics, but there are other types of training"
      + " going on to the east and south.\n");
    try_item( ({ "south", "east" }),
        "The training grounds extend a ways further in that"
      + " direction.\n");
    try_item( ({ "bridge" }),
        "The bridge is not visible from here.\n");
    try_item( ({ "stump", "stumps" }),
        "The stumps are everywhere - this was clearly once a large"
      + " forest. Much of the training is happening on and around the"
      + " stumps, which the instructors are using as natural terrain"
      + " to faciliate various methods on uneven ground.\n");
    try_item( ({ "pupil", "pupils", "student", "students",
                 "mercenary students", "mercenary student",
                 "student mercenary", "student mercenaries" }),
        "Student mercenaries are all over the training yard working with"
      + " various trainers on this or that form of tactical combat"
      + " prowess.\n");

    add_river_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("wep_train", "east");
    add_exit("adapt_train", "south");

    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "You wander through the many stumps of the training ground"
      + " to the edge of the river. Finding nothing of interest, you"
      + " return to the path.\n");
    set_no_exit_msg( ({ "west", "southwest" }),
        "Wandering further westward, the clearcut ends, and you decide"
      + " to return to where you were.\n");
    set_no_exit_msg( ({ "southeast" }),
        "The lodge blocks your path in that direction.\n");

    /* configure the training */
    set_up_skills();

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
public void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_DEFENCE, "defend yourself", "defence", 80, 75);
    sk_add_train(SS_PARRY, "parry incoming attacks", "parry", 80, 75);
    sk_add_train(SS_BLIND_COMBAT, "fight without seeing",
        "blindfighting", 95, 70);
    sk_add_train(SS_2H_COMBAT, "handle two weapons at once",
        "two-handed combat", 100, 75);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed",
        "unarmed combat", 90, 70);
    sk_add_train(SS_MERC_TACTICS_SKILL, "use Mercenary Tactics",
        "mercenary tactics", 80, 100);
} /* set_up_skills */


/*
 * Function name:        add_outdoor_tells
 * Description  :        mask the inherited one to provide unique
 *                       tells for this room
 */
public void
add_outdoor_tells()
{
    add_tell("A shout sounds nearby as a trainer leaps from a stump,"
      + " brandishing a " + one_of_list( ({ "large axe", "blunted sword",
        "sharp dagger", "heavy mace", "long spear" }) ) + " and forcing "
      + one_of_list( ({ "his", "her" }) ) + " pupil to yield.\n");
    add_tell("The clang of steel on steel sounds from nearby.\n");
    add_tell("The sound of the river echoes out of a sudden stillness"
      + " on the training yard.\n");
    add_tell("Two combatants brush past you, each trying to best the"
      + " other in a sparring match.\n");
} /* add_outdoor_tells */


/*
 * Function name:        init
 * Description  :        set up the commands for skill improvement
 */
public void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
    add_action(try_skills, "learn");
    add_action(try_skills, "improve");
} /* init */


/*
 * Function name:        try_skills
 * Description  :        We only want to allow skill training if the
 *                       trainers can see the player, and if the
 *                       player is actually a guild member.
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        1 - no training possible
 *                       0 - allow training.
 */
public int
try_skills(string str)
{
    if (this_player()->query_prop(OBJ_I_INVIS) ||
        this_player()->query_prop(OBJ_I_HIDE))
    {
        write("Train with what, your shadow? You'll need to let the"
          + " trainers see you if you want to train.\n");
        return 1;
    }


    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
        write("The trainers look at you, and draw their weapons. One"
          + " says: You are not one of us! Who let you in here?\n");
        return 1;
    }

    return 0;
} /* try_skills */