#ifndef TUTORIAL_DIR
#define        TUTORIAL_DIR    ("/d/Sparkle/area/tutorial/")
#endif

#define        PRE_DIR         (TUTORIAL_DIR + "pre_creation/")
#define        TEXT_DIR        (TUTORIAL_DIR + "text/")
#define        OBJ_DIR         (TUTORIAL_DIR + "obj/")
#define        LIB_DIR         (TUTORIAL_DIR + "lib/")
#define        TOWN_DIR        (TUTORIAL_DIR + "town/")
#define        SAVE_DIR        (TUTORIAL_DIR + "data/")
#define        NPC_DIR         (TUTORIAL_DIR + "npc/")
#define        WEP_DIR         (TUTORIAL_DIR + "wep/")
#define        ARM_DIR         (TUTORIAL_DIR + "arm/")
#define        LOG_DIR         (TUTORIAL_DIR + "log/")
#define        FARM_DIR        (TUTORIAL_DIR + "farm/")
#define        HERB_DIR        (TUTORIAL_DIR + "herbs/")
#define        WOODS_DIR       (TUTORIAL_DIR + "woods/")
#define        CASTLE_DIR      (TUTORIAL_DIR + "castle/")
#define        CLIFFS_DIR      (TUTORIAL_DIR + "cliffs/")
#define        REVIEW_DIR      (TUTORIAL_DIR + "review/")

#define        TUTORIAL_MASTER    (OBJ_DIR + "tutorial_master")
#define        SAVE_FILE          (SAVE_DIR + "tutorial_save")
#define        TUTORIAL_QUEST_LOG (LOG_DIR + "quests")
#define        SD_ROOM            (TUTORIAL_DIR + "silverdell_room")
#define        ASH_ROOM           (TUTORIAL_DIR + "ash_room")
#define        OPENED_DOOR_PROP     "_tutorial_i_opened_door"
#define        UNLOCKED_DOOR_PROP   "_tutorial_i_unlocked_door"
#define        OPENED_GATE_PROP     "_tutorial_i_opened_gate"
#define        LAIR_PROP            "_tutorial_s_lair"
#define        LOFT_PROP            "_tutorial_s_loft"
#define        TUTORIAL_ITEM_PROP   "_tutorial_i_item"
#define        TUTORIAL_QUIT_PROP   "_tutorial_i_quit"

/*
 * Definitions of Bit Assignments for progress through the tutorial.
 * Note: Bits 0-46 are assigned to tutorial chapters.
 */
#define        GEM_BIT         47  /* Got the gigantic lion reward    */
#define        MUDSLIDE_BIT    48  /* Tied the rope by the mudslide   */
#define        GRAPPLE_BIT     49  /* Tied grappling hook             */
#define        HETZEL_BIT      50  /* Hetzel gave gem                 */
#define        STANLEY_BIT     51  /* Stanley gave sword              */
#define        SAVIOR_BIT      52  /* Savior Status set               */
#define        DESTROYER_BIT   53  /* Destroyer Status set            */
#define        GARLIC_BIT      54  /* Brought back the garlic         */
#define        BUNNY_BIT       55  /* Removed bunny curse             */
#define        NOTE_BIT        56  /* Received note from Farmers Wife */
#define        POTION_BIT      57  /* Received potion from Bibbiss    */
#define        POTION2_BIT     58  /* Gave potion to Farmers Wife     */
#define        CARROT_BIT      59  /* Sent to get carrot              */
#define        CARROT2_BIT     60  /* Given enchanted carrot          */
#define        INSTRUCT_BIT    61  /* Taught how to make rope         */
#define        KILLER_BIT      62  /* Killed the farmers daughter     */
#define        STATUE_BIT      63  /* Moved Krolocks statue           */
#define        FRAGMENT_BIT    64  /* Found the statue slot           */
#define        KROLOCK_BIT     65  /* Defeated Krolock in battle      */
#define        OFFER_BIT       66  /* Krolock offered the quest       */
#define        BEGINNER_BIT    67  /* Beginning info about main quest */
#define        RACE_BIT        68  /* Allows race change sequence     */

/* Definitions for querying & manipulating bits in code */
#define   CHECK_TUTORIAL_BIT(x)   (TUTORIAL_MASTER->query_tutorial( \
                                   this_player()->query_real_name(), (x)))
#define   SET_TUTORIAL_BIT(x)     (TUTORIAL_MASTER->set_tutorial( \
                                   this_player()->query_real_name(), (x)))
#define   CLEAR_TUTORIAL_BIT(x)   (TUTORIAL_MASTER->clear_tutorial( \
                                   this_player()->query_real_name(), (x)))

#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n")

/* Definitions used to determine the sign chapter titles */
#define CHAPTER_TITLES \
    ({ "Welcome!", \
       "Moving Around", \
       "Looking At Things", \
       "Room Descriptions", \
       "Deeper Room Descriptions", \
       "Getting And Using Things", \
       "Finding Secrets - The Search Command", \
       "Working on Quests", \
       "Statistics", \
       "The Expanded Tutorial and Lars' Gift", \
       "NPCs and Conversation", \
       "What To Do First", \
       "Adventurer Guilds - Meditation", \
       "Adventurer Guilds - Skills", \
       "Skill Training", \
       "Experience - Gaining Levels", \
       "Food and Fatigue", \
       "Drinks and Intoxication", \
       "Introductions and the Who List", \
       "The Help Command and the Rules", \
       "Magic and Spellcasting", \
       "Shops - Buying and Selling", \
       "Using Weapons", \
       "Using Armours", \
       "Logging Out and Linkdeath", \
       "Money and Banks", \
       "Mail", \
       "Roleplay and Emotions", \
       "Bulletin Boards", \
       "Quests and Brutality", \
       "Start Locations", \
       "Save, Armageddon, and Recovery", \
       "Death", \
       "Health and Wimpying", \
       "What to Do Next - Earning Money", \
       "Dealing with Quest NPCs", \
       "Combat!", \
       "The Options Commands", \
       "Herbs", \
       "Light and Darkness", \
       "Corpses and Leftovers", \
       "Teaming", \
       "Feedback for Wizards", \
       "Completing the Tutorial", \
       "Alignment: Good vs. Evil", \
       "Quicktyper Commands", \
       "Grinding - A Necessary Evil?", \
       "Occupational and other Guilds", \
       "Guild Benefits - Racks", \
       "Guild Benefits - Special Attacks", \
    })




