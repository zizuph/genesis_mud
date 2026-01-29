/*
   Wayreth.

   norm_skills.c
   -------------

   Coded ........: 01/97
   By ...........: Kentari

   Latest update : 07/97
   By ...........: Kentari

   Latest update : 10/2016
   By .......... : Arman - updated for recode of WoHS

*/

#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit "/lib/skill_raise";
inherit TOWERROOM;

/*
 * Prototypes
 */
public void
set_up_skills();


public void
reset_tower_room()
{
    return;
}


void
create_tower_room()
{
   set_short("elemental spell training room");
   AI(({"shelves","shelf"}),
	"Holding almost all of the books in this room, the shelves " +
	"are made of some black material, possibly a wood or maybe " +
	"a metal.\n");
   AI(({"books","texts","volumes","books of power","magical books"}),
	"There are so many volumes of books that you don't know where " +
	"to begin looking. For some reason, you can't read the bindings " +
	"that are shown and are too cautious to touch an unknown book " +
	"that might be magical.\n");
   set_long("Shelves line the walls of this room, each completely " +
	    "filled with hundreds " +
	    "of magical books of power and texts aiding in the learning " +
	    "of the arcane arts. There are so many volumes that you feel " +
	    "it would be unwise to try and search for knowledge on your " +
	    "own, and an aide has been given the duty to help you in your " +
	    "studies.\nIn this room Wizards can <learn> or <improve> their "+
            "knowledge of the elements, as well as take on advanced "+
            "specialisation training in one elemental spell skill through " +
            "'choose <element>'. Wizards can also change their element " +
            "specialisation here, however will lose all skill levels " +
            "above superior journeyman from their previous element " +
            "specialisation.\n");

    reset_tower_room();
    create_skill_raise();
    set_up_skills();

    add_exit(WTOWER + "training", "south", 0);
}

public void
init()
{
    ::init(); 
    init_skill_raise(); 
    add_action("choose", "choose");
}

public int
choose(string str)
{
    object player = this_player();
    if (!WOHS_IS_MEMBER(player))
    {
        return 0;
    }
    
    notify_fail("Here you can choose what 'elemental' spell skill you " +
                "specialise in. You can only specialise in one of each at " +
                "any one time, Elemental spell skills you can specialise " +
                "in are 'fire', 'water', 'air' or 'earth'.\n");

    if (!strlen(str))
    {
        return 0;
    }
    
    str = lower_case(str);
    string old_primary;
    switch (str)
    {
    case "fire":        
    case "water":
    case "air":
    case "earth":
    {
        old_primary = WOHS_MANAGER->query_specialisation_element(player);
        if (!strlen(old_primary))
        {
            write("You choose to specialise in " + str + " magic!\n");
            WOHS_MANAGER->set_specialisation_element(player, str);        
        }
        else if (old_primary != str)
        {
            int old_skillnum = WOHS_MANAGER->query_specialisation_element_skillnum(player);
            if (player->query_skill(old_skillnum) > 75) 
            {
                player->set_skill(old_skillnum, 75);            
                write("You choose to respecialise in " + str + 
                    " magic and discard the advanced training that you "
                    + "previously had in " + old_primary + " spells.\n");
            }
            else
            {
                write("You choose to respecialise in " + str + " magic!\n");
            }
            WOHS_MANAGER->set_specialisation_element(player, str);
        }
        else
        {
            write("You have already chosen the element of " + str + 
                  " as your specialty.\n");
        }
        return 1;
      }
        
    default:
    notify_fail("Here you can choose what 'elemental' spell skill you " +
                "specialise in. You can only specialise in one of each " +
                "at any one time, " +
                "however can change your specialty here.\n\n" +
                "Elemental spell skills you can specialise in are 'fire', " +
                "'water', 'air' or 'earth'.\n");
    }
    return 0;    
}

public void
set_up_skills()
{

    sk_add_train(SS_ELEMENT_AIR, "cast air spells", 0, 0, 100);
    sk_add_train(SS_ELEMENT_FIRE, "cast fire spells", 0, 0, 100);
    sk_add_train(SS_ELEMENT_WATER, "cast water spells", 0, 0, 100);
    sk_add_train(SS_ELEMENT_EARTH, "cast earth spells", 0, 0, 100);

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
    if (!WOHS_MANAGER->query_is_member(who))
    {
        who->catch_msg("Only those who are Wizards of High Sorcery can train here.\n");
        return 0;
    }
        
    return 1;
}

/* 
 * Function:     sk_query_max
 * Description:  give the max we can teach of a skill
 * Arguments:    int snum   - the skill number to check
 *               int silent - don't tell anything to the player if true
 * Returns:      int - the maximum you can train the skill to 
 */ 
public varargs int
sk_query_max(int snum, int silent)
{
    object player = this_player(); 
 
    int max_skill = ::sk_query_max(snum, silent);

    setuid();
    seteuid(getuid());
    string prev_obj_file = MASTER_OB(previous_object());
    if (!objectp(player))
    {
        return 0;
    }
    
    if (prev_obj_file != "/d/Genesis/specials/guilds/guild_tester_soul"
        && !WOHS_MANAGER->query_is_member(player))
    {
        return 0;
    }

    int player_max = max_skill;
    // Element specialisation can be trained to maximum 100.
    // Non-specialised can be learnt to 75.
    switch (snum)
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
    case SS_ELEMENT_AIR:
    case SS_ELEMENT_EARTH:
        if (WOHS_MANAGER->query_specialisation_element_skillnum(player) != snum)
        {            
            return 75;
        }
        break;
    }
    
    return min(player_max, max_skill);
}

