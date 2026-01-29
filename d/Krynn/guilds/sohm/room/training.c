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
    set_short("Northern wing of the library - arcane forms training");
    set_long("You stand in the northern wing of the school of High Magic's " +
        "library. The marble floor of the room features a large six-point " +
        "star, with each point a different hue of colour. In the centre " +
        "of the star slowly spins an orb of black and white.\nIn this " +
        "room students can <learn> or <improve> their knowledge of " +
        "the arcane forms, as well as take on advanced specialisation " +
        "training in an arcane form through 'choose <form>'. " +
        "Students can also change their form specialisation here, " +
        "however will lose all skill levels above superior journeyman " +
        "from their previous form specialisation.\n");

    add_item(({"orb","spinning orb","slowly spinning orb",
        "black and white orb"}),"In the centre of the six-point star " +
        "an orb slowly spins. You cannot determine whether " +
        "it is black or white - your senses confuse it as one or the other " +
        "but never both - symbolising the spell forms of life and death. " +
        "These spell forms typically represent healers - long gone on " +
        "Krynn since the Cataclysm - and necromancy respectively. Neither " +
        "of which are spell forms trained at this school.\n"); 

    add_item(({"library","wing","northern wing"}),
        "This is the northern wing of the library, focused on the training " +
        "of the arcane forms. The room is dominated by a marble mural " +
        "of a multi-hued star in the centre " +
        "of the floor.\n");

    add_item(({"star","multi-hued star","six-point star",
        "large six-point star","point","points","mural","floor",
        "marble floor","hues","colours","colour"}),
        "In the centre of the floor is a marble mural of a six-point star. " +
        "Each point a different hue of colour, each representing a " +
        "different arcane form.\n" +
        "The hues of the six points are ochre, amber, celadon, cyan-blue, " +
        "rose and maroon.\n");

    add_item(({"ochre","ochre point","brown","brown ochre point"}),
        "The brown ochre point of the star represents the spell form " +
        "Abjuration. Abjurers " +
        "are the masters of spells that protect, ward, and banish.\n");

    add_item(({"amber","amber point"}),
        "The amber point of the star represents the spell form Divination. " +
        "Diviners focus on seeing the future and the hidden.\n");

    add_item(({"celadon","celadon point"}),
        "The grey-green celadon point of the star represents the spell " +
        "form Transmutation. Transmuters have spells that modify the " +
        "world around them, allowing them to change the properties of " +
        "themselves, their items, and their surroundings.\n");

    add_item(({"cyan-blue","cyan-blue point"}),
        "The cyan-blue point of the star represents the spell form " +
        "Illusion. Illusionists are creators of tricks and falsehoods, " +
        "and masters of deception.\n");

    add_item(({"rose","rose point"}),
        "The rose point of the star represents the spell form Enchantment. " +
        "Enchanters focus on mind altering spells - charming, beguiling " +
        "and dominating their foes with their magic.\n");

    add_item(({"maroon","maroon point"}),
       "The maroon point of the star represents the spell form " +
       "Conjuration. Conjurers are the masters of spells that create and " +
       "summon, as well as destructive magics.\n");

    add_exit(ROOM + "library","south",0);
    
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
    
    notify_fail("Here you can choose what 'form' spell skill you " +
                "specialise in. You can only specialise in one of each at " +
                "any one time, " +
                "however can change your specialty here.\n\n" +
                "Forms you can specialise in are 'transmutation', " +
                "'illusion', 'divination', " +
                "'enchantment', 'conjuration', or 'abjuration'.\n");

    if (!strlen(str))
    {
        return 0;
    }
    
    str = lower_case(str);
    string old_primary;
    switch (str)
    {
    case "transmutation":        
    case "illusion":
    case "divination":
    case "enchantment":
    case "conjuration":
    case "abjuration":
        old_primary = SOHM_MANAGER->query_specialisation_form(player);
        if (!strlen(old_primary))
        {
            write("You choose to specialise in the " + str + " spell form!\n");
            SOHM_MANAGER->set_specialisation_form(player, str);        
        }
        else if (old_primary != str)
        {
            int old_skillnum = SOHM_MANAGER->query_specialisation_form_skillnum(player);
            if (player->query_skill(old_skillnum) > 50) 
            {
                player->set_skill(old_skillnum, 50);            
                write("You choose to respecialise in the " + str + 
                    " spell form and discard the advanced training that you "
                    + "previously had in " + old_primary + " spells.\n");
            }
            else
            {
                write("You choose to refocus your studies upon the "
                    + str + " spell form.\n");
            }
            SOHM_MANAGER->set_specialisation_form(player, str);
        }
        else
        {
            write("You have already chosen " + str + " as your primary " +
                  "spell form.\n");
        }
        return 1;
        
    default:
    notify_fail("Here you can choose what 'form' spell skill you " +
                "specialise in. You can only specialise in one of " +
                "each at any one time, " +
                "however can change your specialty here.\n\n" +
                "Forms you can specialise in are 'transmutation', " +
                "'illusion', 'divination', " +
                "'enchantment', 'conjuration', or 'abjuration'.\n");
    }
    return 0;    
}

public void
set_up_skills()
{

    sk_add_train(SS_SPELLCRAFT, "understand spells", 0, 0, 75);
    /* Arcane focus can be trained up to confident veteran here */
    sk_add_train(SOHM_GUILD_SKILL, "memorise spells", "arcane focus", 50, 75);
    sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 70);
    sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 45);
   
    sk_add_train(SS_FORM_ABJURATION, "cast abjuration spells", 0, 0, 75);
    sk_add_train(SS_FORM_CONJURATION, "cast conjuration spells", 0, 0, 75);
    sk_add_train(SS_FORM_TRANSMUTATION, "cast transmutation spells", 0, 0, 75);
    sk_add_train(SS_FORM_ILLUSION, "cast illusion spells", 0, 0, 75);
    sk_add_train(SS_FORM_ENCHANTMENT, "cast enchantment spells", 0, 0, 75);
    sk_add_train(SS_FORM_DIVINATION, "cast divination spells", 0, 0, 75);

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
            + "school of High Magic can train here.\n");
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
    // Element and form specialisation can be trained to maximum 75.
    // Non-specialised can be learnt to 50.
    switch (snum)
    {
    case SS_FORM_ABJURATION:
    case SS_FORM_CONJURATION:
    case SS_FORM_TRANSMUTATION:
    case SS_FORM_ILLUSION:
    case SS_FORM_ENCHANTMENT:
    case SS_FORM_DIVINATION:
    case SS_FORM_ENCHANTMENT: 
        if (SOHM_MANAGER->query_specialisation_form_skillnum(player) != snum)
        {            
            return 50;
        }
        break;
    }
    
    return min(player_max, max_skill);
}

