/*
 * Training room for the School of High Magic, based on Petros'
 * Academics code.  Arman, January 2016
 *
 */

#pragma strict_types

#include "/d/Krynn/solace/poolbottom/local.h"
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

inherit POOLBOTTOM_IN;
inherit "/lib/skill_raise"; 

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public string * beta_testers = ({ "armanjr"});

// Prototypes
public void     set_up_skills();

public void
reset_poolbottom_room()
{

}

public void
create_poolbottom_room()
{
    set_short("Southern wing of the library - elemental spell training");
    set_long("You stand in the southern wing of the school of High Magic's "+
        "library. Four statues stand in niches in the back wall of the " +
        "wing, each statue representing one of the four elements - fire, "+
        "water, earth, and air.\n"+
        "In this room students can <learn> or <improve> their knowledge of "+
        "the elements, as well as take on advanced specialisation training "+
        "in one elemental spell skill through 'choose <element>'. " +
        "Students can also change their element specialisation here, " +
        "however will lose all skill levels " +
        "above superior journeyman from their previous element " +
        "specialisation.\n");
 
    add_item(({"statues","niches","statue","back wall","four elements"}),
        "At the back wall of this room are four niches, a statue in each.\n" +
        "The first niche holds a statue of a flame - representing " +
        "the fire element. \nThe second niche holds " +
        "a statue of a rising wave - representing the water element. \n" +
        "The third niche holds " +
        "a statue of a rune-covered mountain - representing the earth " +
        "element. \nThe fourth niche holds a statue creatively " +
        "characterising a gust of wind - representing the " +
        "air element.\n");

    add_item(({"statue of a flame","statue of flame","flame statue","flame",
        "fire element","fire statue","first niche"}),
        "Gazing at the statue of a flame gives you insights into the " +
        "fire element - it is the rawest and most unsophisticated of the " +
        "elements, explosive and destructive unless tamed and held in " +
        "control at every moment. Self control and discipline " +
        "of beings is a reflection of the element of fire.\n");

    add_item(({"statue of a rising wave","statue of rising wave",
        "rising wave statue","second niche",
        "rising wave","water element","water statue","wave statue"}),
        "Gazing at the statue of a rising wave gives you insights into " +
        "the water element - " +
        "it is the element of the flexible and yet unyielding, the home of " +
        "the potion makers, and linked to the trait of constitution.\n");

    add_item(({"statue of a rune-covered mountain","third niche",
        "statue of rune-covered mountain","statue of mountain",
        "mountain statue","earth element","earth statue"}),
        "Gazing at the statue of a runed-covered mountain gives you " +
        "insights into the earth element - it is the element that " +
        "governs the inanimate and solid, with " +
        "strength being the trait that is connected to earth.\n");

    add_item(({"statue characterising a gust of wind",
        "statue of a gust of wind","wind statue","fourth niche",
        "gust of wind statue","air element","air statue"}),
        "Gazing at the statue characterising a gust of wind gives you " +
        "insights into the " +
        "air element - it is the light and quick-moving element. It governs " +
        "communication, and is linked to the trait of dexterity.\n");

    add_exit(ROOM + "library","north",0);
    
    // Set up the room as a training room
    create_skill_raise();
    set_up_skills();
    
    reset_poolbottom_room();
  
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
    if (!IS_MEMBER(player))
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
        old_primary = SOHM_MANAGER->query_specialisation_element(player);
        if (!strlen(old_primary))
        {
            write("You choose to specialise in " + str + " magic!\n");
            SOHM_MANAGER->set_specialisation_element(player, str);        
        }
        else if (old_primary != str)
        {
            int old_skillnum = SOHM_MANAGER->query_specialisation_element_skillnum(player);
            if (player->query_skill(old_skillnum) > 50) 
            {
                player->set_skill(old_skillnum, 50);            
                write("You choose to respecialise in " + str + 
                    " magic and discard the advanced training that you "
                    + "previously had in " + old_primary + " spells.\n");
            }
            else
            {
                write("You choose to respecialise in " + str + " magic!\n");
            }
            SOHM_MANAGER->set_specialisation_element(player, str);
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

    sk_add_train(SS_ELEMENT_AIR, "cast air spells", 0, 0, 75);
    sk_add_train(SS_ELEMENT_FIRE, "cast fire spells", 0, 0, 75);
    sk_add_train(SS_ELEMENT_WATER, "cast water spells", 0, 0, 75);
    sk_add_train(SS_ELEMENT_EARTH, "cast earth spells", 0, 0, 75);

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
    if (!SOHM_MANAGER->query_is_member(who))
    {
        who->catch_msg("Only those who are currently enrolled in the "
            + "School of High Magic can train here.\n");
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
        && !SOHM_MANAGER->query_is_member(player))
    {
        return 0;
    }

    int player_max = max_skill;
    // Element specialisation can be trained to maximum 75.
    // Non-specialised can be learnt to 50.
    switch (snum)
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
    case SS_ELEMENT_AIR:
    case SS_ELEMENT_EARTH:
        if (SOHM_MANAGER->query_specialisation_element_skillnum(player) != snum)
        {            
            return 50;
        }
        break;
    }
    
    return min(player_max, max_skill);
}

