/*
   Wayreth. Courtyard in front of the towers.

   yard04.c
   --------

   Coded ........: 95/05/31
   By ...........: Jeremiah

   Latest update : 10/2016
   By ...........: Arman
   Reason........: Recoded for new WoHS

*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <composite.h>

inherit "/lib/skill_raise";
inherit WAYOUTROOM;

#define NPC "/d/Krynn/wayreth/npc/"
object gTrainer;
public mixed prevent_teleport();

/*
 * Prototypes
 */
public void     set_up_skills();

void
reset_wayreth_room()
{
   if (!gTrainer)
    {
        gTrainer = clone_object(NPC + "minion_trainer");
        gTrainer->move(TO);
    }
   return;
}

void
create_wayreth_room()
{
   set_short("West courtyard");
   set_long("This is the western courtyard in the complex " +
      "that surrounds the Tower of High Sorcery. To the west " +
      "is a guard tower, while the Tower itself stands to the " +
      "east. The main courtyard can be returned to by going around " +
      "the tower, as you are now behind it. There is no entrance here. " +
      "The ground is covered with a black tile, a gridded solid " +
      "sheet.\n");
   add_item(({"black tile","tile","sheet","solid sheet",
      "gridded sheet","gridded solid sheet","tiles","black tiles"}),
      "This layer of black tiles covers the ground, and they " +
      "are embedded firmly. They make walking in the courtyard " +
      "quite a relaxing affair.\n");
   add_item("guard tower", "This tower stands empty, and is composed " +
      "of a dusky black rock.\n");
   add_item(({"dusky black rock","dusky rock","black rock","rock"}),
      "A closer examination reveals nothing special about it.\n");
   add_item("courtyard","You are standing in it.\n");
   add_item(({"Tower","tower","Tower of High Sorcery"}), "The Tower " +
      "of High Sorcery stands to the east from here. It has " +
      "walls of polished obsidian. No windows can be seen in its " +
      "smooth surface.\n");
   add_item(({"walls","walls of polished obsidian","surface",
      "smooth surface"}),"The walls of the Tower are a glossy " +
      "black, and seem to be enchanted with magic.\n");

   reset_wayreth_room();

   create_skill_raise();
   set_up_skills();

   add_prop(ROOM_I_NO_ATTACK, 1);

   add_exit(WTOWER + "wall_tower03", "west", 0);
   add_exit(WTOWER + "yard02", "northeast", "@@around_tower");
   add_exit(WTOWER + "yard02", "southeast", "@@around_tower");

   add_prop(ROOM_M_NO_TELEPORT, prevent_teleport);
   add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the walls surrounding the Tower of High Magic. There will be no violence " +
       "allowed on these grounds.\n");
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(this_player()->query_is_wohs())
	return 0;

    return "Something prevents you from teleporting there.";
}

int
around_tower()
{
   write("You follow the dark wall in a semi-circle around the " +
      "Tower of High Sorcery and arrive on the other side.\n");
   return 0;
}

public void
init()
{
    ::init(); 
    init_skill_raise(); 
}

set_up_skills()
{
    sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 60);
    sk_add_train(SS_WEP_KNIFE, "fighting with a dagger", 0, 0, 60);
}

/*
 * Function name: sk_hook_allow_train
 * Description:   Function called when player tries to do the improve command
 *                Will determine if a player can train skills here.
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                string - The string from sk_improve
 *                verb   - improve or learn typically
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    setuid();
    seteuid(getuid());
    // Only allow those who are members to train here.
    if (who->query_guild_name_occ() != WOHS_GUILD_NAME)
    {
        who->catch_msg("Only Wizards of High Sorcery can train here.\n");
        return 0;
    }
        
    return 1;
}
