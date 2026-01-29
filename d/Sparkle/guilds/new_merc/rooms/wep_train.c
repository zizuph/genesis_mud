/*
 *  /d/Sparkle/guilds/new_merc/rooms/wep_train.c
 *
 *  Within the training grounds of the Mercenary Guild just north
 *  of the Lodge. Normally, only guild members are allowed in here
 *  (though I might make a backdoor for sneaky players!) This is
 *  the room which trains all weapon types for the guild.
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
    set_short("just north of the lodge in the training yard of the"
      + " Mercenary Guild");
    set_long("A wide lawn spreads out here between the lodge and the"
      + " river which is a short distance to the north. Numerous"
      + " Mercenaries are training here in the art of all manner of"
      + " weaponry. A number of rugged individuals stand at the ready,"
      + " willing to offer their mastery of the various weapon"
      + " types for a fee. If you are a Mercenary, you may try to"
      + " <learn> or <improve> skills here.\n\n");

    try_item( ({ "individual", "rugged individual", "individuals",
                 "rugged individuals", "trainer", "trainers",
                 "weapon trainer", "weapon trainers",
                 "instructor", "instructors" }),
        "The weapon trainers are numerous. Some keep a confident grip"
      + " on axes of various shapes and sizes, while others are"
      + " armed with spears, swords, daggers, and clubs. It is clear"
      + " that the Mercenaries value knowledge of all forms of combat,"
      + " and are willing to share that knowledge for a price.\n");
    try_item( ({ "east" }),
        "A fence of criss-crossed sharpened poles is directly to"
      + " the east, separating these training grounds from the"
      + " rest of the camp.\n");
    try_item( ({ "north", "clearcut", "clear-cut" }),
        "A clearcut strewn with numerous stumps spreads out between"
      + " this lawn and the river, which is to the north.\n");
    try_item( ({ "east", "fence", "guarded fence" }),
        "A fence of criss-crossed sharpened poles has been placed along"
      + " the access route between the mill and the lodge where the"
      + " path travels east from here. It doesn't look as if anyone"
      + " who is not welcome will be able to get past that blockade"
      + " very easily.\n");
    try_item( ({ "pole", "poles", "sharpened pole", "sharpened poles",
                 "criss-crossed poles", "criss-crossed sharpened poles",
                 "blockade", "route", "access route" }),
        "The fence clearly means business. No one is going through"
      + " that without first getting permission.\n");
    try_item( ({ "lawn", "wide lawn", "yard", "training yard",
                 "mercenary training yard", "training ground",
                 "training grounds" }),
        "These training grounds extend a ways to the north toward"
      + " the river and then curve around the lodge west and to the"
      + " south, where it appears as if various other types of"
      + " training might be available.\n");
    try_item( ({ "south" }),
        "The old logging lodge which houses the Mercenaries rises"
      + " directly south from here.\n");
    try_item( ({ "bridge" }),
        "The bridge is not visible from here.\n");
    try_item( ({ "stump", "stumps" }),
        "The stumps are everywhere - this was clearly once a large"
      + " forest. Much of the training is happening on and around the"
      + " stumps, which the instructors are using as natural terrain"
      + " to faciliate various methods on uneven ground.\n");
    try_item( ({ "weapon", "weapons", "weaponry" }),
        "The Mercenaries seem to work with just about any weapon"
      + " type. You see all forms represented.\n");
    try_item( ({ "west" }),
        "To the west, the training yard extends toward the forest.\n");
    try_item( ({ "form", "forms", "all forms", "sword", "swords",
                 "axe", "axes", "club", "clubs", "polearm", "polearms",
                 "knife", "knives" }),
        "Swords, axes, clubs, polearms, knives ... yep, they all seem"
      + " to be present in the mix of things here.\n");
    try_item( ({ "north face", "north face of the lodge", "wall",
                 "wall of the lodge", "lodge wall" }),
        "A door is set in the wall of the lodge here.\n");

    add_river_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("path4", "east");
    add_exit("tactics_train", "west");
    add_exit("lumber_pile", "northeast", 0, 1, 1);

    set_no_exit_msg( ({ "north", "northwest" }),
        "You wander through the many stumps of the training ground"
      + " to the edge of the river. Finding nothing of interest, you"
      + " return to the path.\n");
    set_no_exit_msg( ({ "southeast", "south", "southwest" }),
        "The lodge blocks your path in that direction.\n");

    /* configure the training */
    set_up_skills();

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "kitchen_n");
} /* create_merc_room */


/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
public void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_WEP_SWORD, "handle a sword", "sword", 95, 75);
    sk_add_train(SS_WEP_AXE, "handle an axe", "axe", 70, 75);
    sk_add_train(SS_WEP_KNIFE, "handle a knife", "knife", 46, 70);
    sk_add_train(SS_WEP_POLEARM, "handle an polearm", "polearm", 80, 75);
    sk_add_train(SS_WEP_CLUB, "handle a club", "club", 50, 75);
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