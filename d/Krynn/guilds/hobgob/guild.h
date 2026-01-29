/* Guild.h */

#define GUILD_NAME    "Raiders of Throtyl"
#define GUILD_STYLE   "fighter"
#define GUILD_TAX     11

#define GUILD_DIR   "/d/Krynn/guilds/hobgob/"

#define GUILD_SHADOW  GUILD_DIR + "lay_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "cmdsoul"
#define GUILD_EMBLEM  GUILD_DIR + "emblem"
#define GUILD_POST    GUILD_DIR + "post"
#define HELP_DIR      GUILD_DIR + "help/"

#define LOOT_MANAGER  (GUILD_DIR + "loot_manager")

#define JOINED        "hobgob/joined_hobgobs"
#define LEFT          "hobgob/left_hobgobs" 

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"
#define MEMBER(ob) ob->query_guild_member(GUILD_NAME)

/* The skill number for the guild's special skill. */
#define SS_GUILD_SPECIAL_SKILL   108550
#define SS_RAIDERS_LOOT_VALUE    108551

#define RAIDERS_STAT_FORMULA(x)  (x)->exp_to_stat((x)->query_skill(SS_RAIDERS_LOOT_VALUE))
#define RAIDERS_PROGRESSION_MOD  7

#define GUILD_STARTLOC           GUILD_DIR + "start"

#define HOBGOB_ELIGIBLE_RACES ({"human", "orc", "goblin", \
    "hobgoblin","ogre", "drow"})

#define DEBUG(x)  find_player("arman")->catch_msg("[hobgob] " + x + "\n")

#define HOBGOB_TITLES  ({ \
    "Hobgoblin Whelp of Throtyl Pass", \
    "Hobgoblin Whelp of Throtyl Pass", \
    "Lowly Underling of Throtyl Pass", \
    "Shifty Desperado of Throtyl Pass", \
    "Shifty Desperado of Throtyl Pass", \
    "Shameless Looter of Throtyl Pass", \
    "Shameless Looter of Throtyl Pass", \
    "Villanous Brigand of Throtyl Pass", \
    "Villanous Brigand of Throtyl Pass", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Warchief of the Throtyl Raiders", \
    "Warchief of the Throtyl Raiders", \
    "Warchief of the Throtyl Raiders", \
    "Senior Warchief of the Throtyl Raiders", \
    "Senior Warchief of the Throtyl Raiders", \
    "Feared Warchief of the Throtyl Raiders", \
    "Feared Warchief of the Throtyl Raiders", \
    "Mighty Chieftain of the Hobgoblins, Tyrant of Throtyl", \
    "Mighty Chieftain of the Hobgoblins, Tyrant of Throtyl", \
    "Unrivaled Chieftain of the Hobgoblins, Overlord of the Goblin Hordes", })

#define GOB_TITLES  ({ \
    "Goblin Whelp of Throtyl Pass", \
    "Goblin Whelp of Throtyl Pass", \
    "Lowly Underling of Throtyl Pass", \
    "Shifty Desperado of Throtyl Pass", \
    "Shifty Desperado of Throtyl Pass", \
    "Shameless Looter of Throtyl Pass", \
    "Shameless Looter of Throtyl Pass", \
    "Villanous Brigand of Throtyl Pass", \
    "Villanous Brigand of Throtyl Pass", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Vicious Grunt of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Swift Forerunner of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Violent Marauder of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Infamous Warrior of the Throtyl Raiders", \
    "Warchief of the Goblin Hordes", \
    "Warchief of the Goblin Hordes", \
    "Warchief of the Goblin Hordes", \
    "Shrewd Warchief of the Goblin Hordes", \
    "Shrewd Warchief of the Goblin Hordes", \
    "Menacing Warchief of the Goblin Hordes", \
    "Menacing Warchief of the Goblin Hordes", \
    "Fierce Chieftain of the Goblin Hordes, Tyrant of Throtyl", \
    "Fierce Chieftain of the Goblin Hordes, Tyrant of Throtyl", \
    "Unrivaled Chieftain of the Goblin Hordes, Tyrant of Throtyl", })

#define MONST_TITLES  ({"Boorish Peon of Throtyl Pass", \
  "Boorish Peon of Throtyl Pass", \
  "Bloodthirsty Underling of the Throtyl Raiders", \
  "Brutish Desperado of Throtyl Pass", \
  "Brutish Desperado of Throtyl Pass", \
  "Shameless Looter of Throtyl Pass", \
  "Shameless Looter of Throtyl Pass", \
  "Villanous Brigand of Throtyl Pass", \
  "Villanous Brigand of Throtyl Pass", \
  "Vicious Monstrosity of the Throtyl Raiders", \
  "Vicious Monstrosity of the Throtyl Raiders", \
  "Vicious Monstrosity of the Throtyl Raiders", \
  "Monstrous Forerunner of the Throtyl Raiders", \
  "Monstrous Forerunner of the Throtyl Raiders", \
  "Monstrous Forerunner of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Abomination of the Throtyl Raiders", \
  "Abomination of the Throtyl Raiders", \
  "Abomination of the Throtyl Raiders", \
  "Tyrant of the Throtyl Raiders", \
  "Tyrant of the Throtyl Raiders", \
  "Overlord of the Throtyl Raiders", \
  "Overlord of the Throtyl Raiders", \
  "Mighty Overlord of the Throtyl Raiders", \
  "Mighty Overlord of the Throtyl Raiders", \
  "Unrivaled Overlord of the Monstrous Legions of Throtyl, Scourge of the Plains", })

#define HUMAN_TITLES  ({"Contemptible Scoundrel of Throtyl Pass", \
  "Contemptible Scoundrel of Throtyl Pass", \
  "Bloodthirsty Underling of the Throtyl Raiders", \
  "Brutish Desperado of Throtyl Pass", \
  "Brutish Desperado of Throtyl Pass", \
  "Shameless Looter of Throtyl Pass", \
  "Shameless Looter of Throtyl Pass", \
  "Villanous Brigand of Throtyl Pass", \
  "Villanous Brigand of Throtyl Pass", \
  "Vicious Blackguard of the Throtyl Raiders", \
  "Vicious Blackguard of the Throtyl Raiders", \
  "Vicious Blackguard of the Throtyl Raiders", \
  "Swift Forerunner of the Throtyl Raiders", \
  "Swift Forerunner of the Throtyl Raiders", \
  "Swift Forerunner of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Violent Marauder of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Infamous Warrior of the Throtyl Raiders", \
  "Merciless Captain of the Throtyl Raiders", \
  "Merciless Captain of the Throtyl Raiders", \
  "Merciless Captain of the Throtyl Raiders", \
  "Tyrant of the Throtyl Raiders", \
  "Tyrant of the Throtyl Raiders", \
  "Overlord of the Throtyl Raiders", \
  "Overlord of the Throtyl Raiders", \
  "Ruthless Overlord of the Throtyl Raiders", \
  "Ruthless Overlord of the Throtyl Raiders", \
  "Unrivaled Overlord of the Hordes of Throtyl, Scourge of the Plains", })
