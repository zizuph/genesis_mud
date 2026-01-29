/*
 * Practice Room of the Elemental Clerics - 3rd Floor
 * 
 * Created by Petros, March 2014
 */

#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit TEMPLE_ROOM_BASE;
inherit "/lib/skill_raise"; 
inherit "/d/Sparkle/area/city/library/room/library_lib";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";


// Defines

// Prototypes
public void     set_up_skills();

// Global Variables

public void
create_temple_room()
{
    set_short("Elemental Clerics Training and Practice Room");
    set_long("You have stumbled upon a small room where members of the "
             + "Elemental Clerics come to train various skills "
             + "that may assist them in their daily efforts. The room "
             + "is fairly sparse with wooden walls and floor panels. The "
             + "room itself holds only a few dummies to practice self "
             + "defence along with a pair of shelves holding a few "
             + "instruction manuals and practice tools. "
             + "If you are a Cleric of the Elementals you may <learn> "
             + "or <improve> skills here. An archway leads back to the "
             + "central stairwell to the south.\n\n");

    try_item( ({ "walls", "wall", "floors", "floor", "wood", "panels" }),
              "The walls and floors are made of simple wood panels. The wood is mainly composed of "
              + "dark mahogany as found in several of the deep forests in Calia.\n");

    try_item( ({ "dummies", "dummy" }),
              "The dummies are of very simple design and material. They are in the shape and form of "
              + "average sized humanoids and have a few markings of combat practice here and there.\n");

    try_item( ({ "shelf", "shelves", "instruction manual", "instruction manuals", 
                    "manual", "manuals." }),
        "Hanging from the walls there are a few light wooden shelves "
        + "with some instruction manuals on basic alchemy, herb usage, "
        + "and and other essential texts. You can <browse> the shelves "
        + "to see if you find anything to pique your interest. Next to "
        + "the books you see some simple tools as well.\n");

    try_item( ({ "tools", "scrolls", "implements", "tubes", "vials", 
                    "mortars", "mortar" }),
        "Among the tools you recognize scrolls for understanding spellcraft, "
        + "writing implements for practicing various languages and for "
        + "memorizing specific wordings and phrases. These tools are mixed "
        + "with tubes, vials and mortars to train one's understanding of "
        + "alchemy and herbalism.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "south"); 

    // Set up the room as a training room
    create_skill_raise();
    set_up_skills();

    // Set up the library shelves
    set_library_dir(ELEMENTALIST_DIR + "books/");
    set_approval_dir(ELEMENTALIST_DIR + "books/approval/");
    set_removed_dir(ELEMENTALIST_DIR + "books/removed/"); 
    create_genesis_library( ({ "elementalists" }), // shelves
                "" ); // subdirectory
}

public void
init()
{
    ::init();
    init_skill_raise(); 
    init_genesis_library();
}

public void
set_up_skills()
{
    // Even though the 4 elements are trainable up to 90, one can only
    // achieve 90 on one of them. See sk_query_max for more details.
    sk_add_train(SS_ELEMENT_AIR, "invoke air prayers", 0, 0, 100); // adv max 20
    sk_add_train(SS_ELEMENT_FIRE, "invoke fire prayers", 0, 0, 100); // adv max 20
    sk_add_train(SS_ELEMENT_WATER, "invoke water prayers", 0, 0, 100); // adv max 20
    sk_add_train(SS_ELEMENT_EARTH, "invoke earth prayers", 0, 0, 100); // adv max 20
    sk_add_train(SS_ELEMENT_LIFE, "invoke spirit prayers", 0, 0, 100); // adv max 20  
	sk_add_train(SS_SPELLCRAFT, "understand prayers", 0, 0, 100); // adv max 20	
	sk_add_train(SS_WEP_CLUB, "use a bludgeoning weapon", 0, 0, 50); // adv max 30
	sk_add_train(SS_PARRY, "parry blows with a bludgeoning weapon", 0, 0, 45); // adv max 0
	sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 80); // adv max 20
	
	sk_add_train(SS_LOC_SENSE, "be aware of your location", 0, 0, 70); // adv max 20
	sk_add_train(SS_AWARENESS, "be aware of your surroundings", 0, 0, 70); // adv max 20
	sk_add_train(SS_HERBALISM, "cultivate herbs", 0, 0, 80); // adv max 20
    sk_add_train(SS_FORM_ABJURATION, "invoke abjuration prayers", 0, 0, 80); // adv max 20
    sk_add_train(SS_FORM_CONJURATION, "invoke conjuration prayers", 0, 0, 80); // adv max 20
    sk_add_train(SS_FORM_DIVINATION, "invoke divination prayers", 0, 0, 80); // adv max 20
    
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
    if (!who->is_elemental_cleric())
    {
        who->catch_msg("Only those who are members of the Elemental Clerics of "
            + "Calia may train here.\n");
        return 0;
    }

    if (GUILD_MANAGER->query_is_punish_train_banned(who))
    {
        who->catch_tell("As you attempt to practice here, a cleric calmly "
                        + "walks over and informs you that the Elemental "
                        + "Clerics Council has banned you from training "
                        + "at these facilities.\n");
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
sk_query_max(int snum, int silent, object player)
{
    if (!objectp(player))
    {
        player = this_player();
        if (!objectp(player))
        {
            // Just in case it's still not an object.
            return 0;
        }
    }
 
    int max_skill = ::sk_query_max(snum, silent);

    setuid();
    seteuid(getuid());
    string prev_obj_file = MASTER_OB(previous_object());
    if (prev_obj_file != "/d/Genesis/specials/guilds/guild_tester_soul"
        && !player->is_elemental_cleric())
    {
        return 0;
    }
        
    int player_max = max_skill;
    // Primary Skill can be trained to maximum. Non Primary Element
    // Skills can only be trained to 70.
    // Spellcraft can be trained to 90 with no guru quest completed,
    // 100 with guru quest completed.
    // SS_FORM_* & Parry can be trained higher in Air/Water/Spirit branches.
    // Location Sense, Awareness, Herbalism, Parry and Defence 
    // can only be trained higher if a member of the racial guild
    switch (snum)
    {
	    case SS_ELEMENT_FIRE:  	
	    case SS_ELEMENT_WATER:
	    case SS_ELEMENT_AIR:
	    case SS_ELEMENT_EARTH:
	    case SS_ELEMENT_LIFE:
	        if (GUILD_MANAGER->query_primary_element_skillnum(player) != snum)
	        {
	        	return 70;
		    }
	        break;
	
	    case SS_SPELLCRAFT:
	    	if (!(player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT)))
	    	{
	    		return 90;
	    	}
	    	break;
	    	
	    case SS_LOC_SENSE:
	        if (!player->is_elemental_racial_cleric())
	            return 60;
	        break;
	    case SS_AWARENESS:
	        if (!player->is_elemental_racial_cleric())
	            return 60;
	        break;
	    case SS_HERBALISM:
	        if (!player->is_elemental_racial_cleric())
	            return 60;
	        break;
	    case SS_PARRY:
	        if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_AIR)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 40;
	    		else
	    			return 45;
	    	}
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_WATER)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 40;
	    		else
	    			return 45;
	    	}
	        if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_LIFE)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 40;
	    		else
	    			return 45;
	    	}
	    	else
	    	{
	    		return 40;
	        }
	        break;
	    case SS_DEFENCE:
	        if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_FIRE)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 70;
	    		else
	    			return 75;
	    	}
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_AIR)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 70;
	    		else
	    			return 75;
	    	}
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_WATER)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 70;
	    		else
	    			return 80;
	    	}
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_FIRE)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 70;
	    		else
	    			return 80;
	    	}
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_LIFE)
	    	{
	    		if (!player->is_elemental_racial_cleric())
	    			return 70;
	    		else
	    			return 75;
	    	}
	        else
	        {
	            return 70;
	        }
	        break;
	    case SS_FORM_ABJURATION:
	    case SS_FORM_CONJURATION:
	    case SS_FORM_DIVINATION:
	    	if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_AIR)
	    	{
	    		return 80;
	    	}
	    	else if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_WATER)
	    	{
	    		return 80;
	    	}
	    	else if (GUILD_MANAGER->query_primary_element_skillnum(player) ==
	    		SS_ELEMENT_LIFE)
	    	{
	    		return 80;
	    	}
	    	else
	    	{
	    		return 60;
	        }
	        break;
    }
    
    return min(player_max, max_skill);
}

/*
 * Function name: library_read_book
 * Description:   Display the text of a book to the reader
 * Arguments:     string text_filename - The filename of the book file to use
 *                string book_name     - The title of the book
 *                int mread            - true if more should be used
 * Returns:       nothing
 */
public void
library_read_book(string text_filename, string book_name, int mread)
{
    setuid();
    seteuid(getuid());

    write("You pick up the book titled \"" 
        + implode(map(explode(book_name, " "), capitalize), " ")
        + "\" from the bookshelf and begin to read it:\n\n");        
    display_library_action(" picks up a book from the bookshelf and "
                        + "begins to read it.\n");
        
    if (mread || (file_size(text_filename) > 4000))
    {
        this_player()->more(generate_scroll_text(read_file(text_filename, 4), "Property of the Elemental Guilds of Calia"));
    }
    else
    {
        write(generate_scroll_text(read_file(text_filename, 4), "Property of the Elemental Guilds of Calia"));
    }
}
