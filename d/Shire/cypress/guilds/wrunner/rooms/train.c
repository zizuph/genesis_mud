/*
 * Training room of the Wild Elves Guild
 * By Finwe, May 2001
 */
 
#pragma strict_types

#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

inherit "/d/Shire/cypress/guilds/wrunner/base_common_inside";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";


void set_up_skills();

void
create_room()
{
    set_short("An exquisite training room");
    set_long("This is the training room of the Wild Elves. " +
        "Here, they learn battle tactics and skills necessary " +
        "to survive in their travels. Light from the windows and " +
        "from the lamps fill the room. A silver plaque is " +
        "attached to the wall.\n");

    set_add_column_walls(" Large windows are set into the " +
        "south and west walls. They fill the room with light.");
    set_add_column_windows("The windows are set into the north " +
	    "and west walls.");
    add_item(({"west window", "western window"}),
         "A winding path leads southwest towards the house.\n");
    add_item(({"north window", "northern window"}),
         "Beautiful gardens surround the building. Ancient trees " +
         "shade the building.\n");
    add_item("plaque",
        "The plaque is attached to a wall next to the east door. " +
        "It is made of silver and on it is something written " +
        "in fine elvish lettering.\n");
    add_cmd_item("plaque","read","@@read_sign@@");
    set_add_column_bldg();

    create_skill_raise();
    create_guild_support();
    set_up_skills();

    add_exit(ROOM_DIR + "hall", "east");
}

void
init() 
{
    ::init();
    init_skill_raise();
    init_guild_support();
}


void
set_up_skills() {
    string me;
    /* 
     * Add skill that can be trained. Do not add all skills, 
     * and vary a bit 
     */
    me = "buy and sell stuff better";
    sk_add_train(SS_TRADING,({ me, me }),     0,0,50);

    me = "speak to others better";
    sk_add_train(SS_LANGUAGE,({ me, me }),    0,0,40);

    me = "be heedful of the surroundings";
    sk_add_train(SS_AWARENESS,({ me, me }),    0,0,50);

    me = "track things in the wild";
    sk_add_train(SS_TRACKING,({ me, me }),   0,0,40);

    me = "move about in a stealthful manner";
    sk_add_train(SS_SNEAK,({ me, me }),         0,0,45);

    me = "hide in the surroundings";
    sk_add_train(SS_HIDE,({ me, me }),          0,0,45);

    me = "journey through the lands more easily";
    sk_add_train(SS_CLIMB,({ me, me }),             0,0,30);

    me = "handle swords better";
    sk_add_train(SS_WEP_SWORD,({ me, me }),         0,0,30);

    me = "polearms better";
    sk_add_train(SS_WEP_POLEARM,({ me, me }),       0,0,30);

    me = "navigate rivers better";
    sk_add_train(SS_SWIM,({ me, me }),              0,0,30);

    me = "conjure things better";
    sk_add_train(SS_FORM_CONJURATION,({ me, me }),  0,0,20);

    me = "use nature spells better";
    sk_add_train(SS_ELEMENT_LIFE,({ me, me }),      0,0,20);

    me = "find and identify herbs";
    sk_add_train(SS_HERBALISM,({ me, me }),         0,0,40);
/*
    me = "use fire spells better";
    sk_add_train(SS_ELEMENT_FIRE,({ me, me }), 0,0,20);
*/

   }

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}

string
read_sign()
{
    return "\n\n"+
    "       +---------------------------------------------------+\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       |   Wild Elves are admired for their skills and     |\n"+
    "       |   battle tactics. These are what they may learn:  |\n"+
    "       |                                                   |\n"+
    "       |   Trading . . . . . . . . Superior Journeyman     |\n"+
    "       |   Awareness . . . . . . . Superior Journeyman     |\n"+
    "       |   Sneak . . . . . . . . . Confident Journeyman    |\n"+
    "       |   Hide. . . . . . . . . . Confident Journeyman    |\n"+
    "       |   Language. . . . . . . . Superior Acolyte        |\n"+ 
    "       |   Tracking. . . . . . . . Superior Acolyte        |\n"+
    "       |   Herbalism . . . . . . . Superior Acolyte        |\n"+
    "       |   Climb . . . . . . . . . Superior Layman         |\n"+
    "       |   Polearm . . . . . . . . Superior Layman         |\n"+
    "       |   Sword . . . . . . . . . Superior Layman         |\n"+
    "       |   Swim. . . . . . . . . . Superior Layman         |\n"+
    "       |   Conjuration Spells. . . Superior Amateur        |\n"+
    "       |   Life Spells . . . . . . Superior Amateur        |\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       +---------------------------------------------------+\n\n";
}


/*
* Function name: gs_hook_start_meditate
* Description  : Gives a nice description when someone starts to meditate.
*/
nomask public void
gs_hook_start_meditate()
{
    write("You step forward to a column. Suddenly the tree glows " +
        "and surrounds you with an earthly light. You seem to " +
        "be transported to a peaceful hilltop bathed in perfect " +
        "light. Your mind clears on the relaxing hilltop as all " +
        "your worries seem to melt away and you merge your essence " +
        "with Mother Earth.\n\n"+
        "In this state you may 'estimate' your preferences and " +
        "'set' them to different values if you desire. To return " +
        "to the world, simply 'rise' and you will be returned " +
        "to the guild house.\n");
    say(QCTNAME(TP) + " steps forward to a column. It suddenly " +
        "begins glowing and encompases " +HIM_HER(TP)+" with an " +
        "earthly light.\n");
}

/*
* Function name: gs_hook_rise
* Description  : Gives a nice description when someone is done meditating.
*/
nomask public void
gs_hook_rise()
{
    write("Having purified your mind and feeling relaxed, " +
        "you suddenly leave the hilltop and are back in the " +
        "guild house. The column's light fades.\n");
    say("Looking quite relaxed indeed, " + QTNAME(this_player()) + 
        " steps out of the light. The column's light suddenly " +
        "fades.\n");
}

/*
* Function name: gs_hook_already_meditate
* Description  : Gives a nice message when someone tries to meditate
*                when (s)he is already mediating.
*/
nomask public int
gs_hook_already_meditate()
{
    write("It is not possible to come to become more relaxed in " +
        "this current state. Since you are relaxing on the hilltop, " +
        "you can now 'estimate' your different preferences " +
        "for concentration and 'set' them to new values. When " +
        "you are finished, just 'rise' to return to the guild house.\n");
   return 1;
}

/*
* Function name: gs_hook_catch_error
* Description  : Gives a friendly error message when someone gives the
*                wrong command while meditating.
*/
nomask public int
gs_hook_catch_error(string str)
{
   write("That is not possible while relaxing on the hilltop.\n");
   return 1;
}



int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}
