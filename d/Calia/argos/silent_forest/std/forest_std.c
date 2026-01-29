/*
 * forest_std.c
 *
 * Stanard file for all forest locations in the Silent Forest.
 *
 * Copyright (C): Tianar, Jul 2003
 *
*/
#pragma strict_types

// I N C L U D E D   F I L E S
#include "ldefs.h"

inherit "/d/Calia/std/room_tell_room";
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include </d/Krynn/common/herbsearch.h>

// G L O B A L   V A R S
int stump_size, loccliff, no_exits;
string creek_dir = "", cliff_dir = "", exit_desc;

// P R O T O T Y P E S
public string show_me_mist();
public string show_me_forest();

// P R I V A T E   F U N C T I O N S

// P U B L I C   F U N C T I O N S


/*
 *  FUNCTION : reset_herb_room
 *  Arguments: none
 *  Returns  : nothing
 * 
 *  Resets the room so that it can be searched again for herbs
 *
*/
void
reset_herb_room()
{
    set_searched(0);
}


/*
 * Function name: reset_room
 * Description  : This function should be redefined to make the room reset
 *                every half hour or so. If you redefine it, you do not 
 *                have to call enable_reset() since we call it as part of 
 *                our service ;-) Note that this service is only valid for 
 *                rooms.
 */
void
reset_room()
{
    reset_herb_room();
}

/*
 *  FUNCTION: make_me_forest
 *  Arguments: extra_long    - string - Addition to long-desc.
 *             location_type - int - forest 1/creek 2/lake 3/shrine 4.
 *             add_cliff     - int - add description of cliffs.
 *  Returns  :
 * 
 * Set up this location as a forest. Add descriptions to room.
 *
*/
public void
make_me_forest(string extra_long, int location_type, int add_cliff)
{
    string long_desc, stump_desc;

    loccliff = add_cliff;
    
    if (location_type == MM_FOREST)
    {
        // Maybe a stump in forest locations. 4-8 equals a stump.
        stump_size = random(9);
        
        // Long description
        switch (random(2))
        {
        case 0:
            long_desc = "Slim streaks of sunlight shimmer down " +
                "through the forest canopy above, piercing into " +
                "the thick silent mist that covers everything on " +
                "the ground. Rising up through the ghostly glare " +
                "of the mist, black trees reach for the near total " +
                "darkness of the forest canopy some ten meters " +
                "above you.";
            break;
            
        case 1:
            long_desc = "Every sound is muffled by the thick white " +
                "mist that covers everything on the ground. Slim " +
                "streaks of sunlight pierce into the mist, causing " +
                "it to glow with a pale ghostly light, a stark " +
                "contrast to the black trunks of the trees that " +
                "reach up through the mist to join the darkness of " +
                "the forest canopy above.";
            break;
        }
        set_tell_time(250);
        add_tell("One of the old trees goes 'Creak, creeek' "+
          "as the wind forces it to sway slowly.\n");
        add_tell("Suddenly everything is very quiet.\n");
		add_tell("It is silent.\n");
		add_tell("Everything is silent.\n");

		if (!query_prop(OBJ_S_SEARCH_FUN))
		{
			add_prop(OBJ_S_SEARCH_FUN, "herb_search");
            add_prop(OBJ_I_SEARCH_TIME, 4);
			set_search_places(({"here","forest","ground"}));
			
			add_herb_file(HERBDIR + "wildfeather"); /* Fatigue healing */
            if(random(100) > 60)
			  add_herb_file(HERBDIR + "athly"); /* Mana */
			if(random(100) > 60)
			  add_herb_file(HERBDIR + "streyroot"); /* Poison */
			if(random(100) > 60)
			  add_herb_file(HERBDIR + "strim"); /* Health */
            if(random(100) > 60)
			  add_herb_file("/d/Krynn/common/herbs/chicory"); /* Fatigue healing */			
		}
    }    

    else
    if (location_type == MM_CREEK)
    {
        // No stumps in creek locations.
        stump_size = 0;
        
        // Long description
        long_desc = "A gently trickling sound of running water " +
            "reach up from the white mist around you, a strange " +
            "reminder of the silence of the rest of the forest. " +
            "Piercing the mist from the darkness above, slim " +
            "streaks of sunlight illuminate the mist in a pale " +
            "white glow. Reaching upwards like towering black " +
            "giants, the trees claw out of the mist to join the " +
            "forest canopy high above.";
        add_item(({"water", "running water", "creek"}), "Crouching " +
            "down into the mist, you notice a small creek slushing " +
            "gently by. No more than a meter wide and not very " +
            "deep, it brings clear water through this pale forest " +
            "towards the " + creek_dir + ". The pale glow of the " +
            "mist, makes the water quite clear and through the " +
            "transparent water you easily spot the bottom of the " +
            "creek.\n");
    }
    
    else
    if (location_type == MM_LAKE)
    {
        // No stumps in lake location.
        stump_size = 0;
        
        // Long description
        long_desc = "";
    }
    
    else
    if (location_type == MM_SHRINE)
    {
        // Always a stump in Shrine location.
        stump_size = random(5) + 4;
        
        // Long description
        long_desc = "";
    }
    
    if (add_cliff == ADDCLIFF)
    {
        add_item(({"cliffs", "cliff", "cliffside"}), "Towering " +
            "suddenly out of the ghostly light of the forest, a " +
            "tall cliffside rises towards the " + cliff_dir +
            ". Glistening softly in the light from the mist, the " +
            "moist of the air clings to the rocks. The cliffside " +
            "rises steeply, almost vertically into the air and " +
            "seems to rise above the trees.\n");
    }
    
    if (stump_size >= 4)
    {
        stump_desc = " Out of the white mist a huge black stump has " +
            "appeared a few meters from you. It towers above you " +
            "like a " + stump_size + " meter tall giant.";
        add_item(({"stump", "black stump", "huge stump",
            "huge black stump"}), "Not quite like the other black " +
            "giants, you feel this huge stump is somewhat out of " +
            "place in the middle of the forest. It reaches out of " +
            "the pale mist with a huge trunk that seem wider than " +
            "the other trees of the forest. The trunk also seems " +
            "more crooked and slumped and appears to bend over " +
            "you, its branches clawing into the air above your " +
            "head. Unlike the other trees, it ends " + stump_size +
            " meters above you, a few meters below the darkness of " +
            "the canopy. In most places, the bark has been peeled " +
            "off, leaving a naked black trunk.\n");
        add_item(({"trunk", "naked trunk", "naked black trunk"}),
            "As you reach out to touch the thick naked stump, the " +
            "forest seems even more silent than normal. You feel " +
            "nothing out of the ordinary but you notice a few " +
            "small holes in the trunk, probably carved by birds " +
            "years ago.\n");
        add_item(({"branch", "branches"}), "Reaching like clawing " +
            "arms, several branches reach out from the huge black " +
            "trunk. Reaching up you can easily grasp one of them " +
            "and it seems capable of holding some weight.\n");
        add_item(({"hole", "holes"}), "Upon closer examination you " +
            "notice the holes lead to hollow inside the black " +
            "trunk, but you are unable to sense how big it is " +
            "through the utter darkness inside the trunk. The " +
            "holes seem to have been made years ago, probably by " +
            "birds or other animals carving nests into the trunks.\n");
    }
    else
    {
        stump_desc = "";
    }
    
    // General forest description
    set_long(long_desc + " " + extra_long + "\n");
    set_short("In a silent forest");
    
    // It is easy to hide here.
    TO->add_prop("ROOM_I_HIDE", 5);
    
    add_item(({"mist", "white mist"}), "@@show_me_mist@@");
    add_item(({"tree", "trees", "black tree", "black trees", "giants",
        "black giants"}), "Like silent black giants, the trees " +
        "around you reach up through the white mist, clawing for " +
        "the darkness of the forest canopy about ten meters above. " +
        "Here and there a few strands of sunlight reach through " +
        "the dark tree canopy to pierce into the ghostly white " +
        "mist. Similar to pine trees, they all have black stems " +
        "and broad cones." + stump_desc + "\n");
    add_item(({"canopy", "forest canopy"}), "Only pierced here and " +
        "there by slim streaks of sunlight, the trees create a " +
        "canopy that covers the forest in a roof of near total " +
        "darkness. It is not possible to see the sky above the " +
        "trees.\n");
    add_item(({"underbrush", "ground", "plants", "bushes"}),
        "Covered entirely in milky whiteness the ground and most " +
        "of the underbrush is shrouded in a dense mist. Crouching " +
        "down, you notice several bushes and small plants reaching " +
        "up towards the light above the white mist. Sturdy plants " +
        "that seem able to survive with little light and still " +
        "manage to survive buried in the mist. Touching the barely " +
        "visible ground, you feel a soft mossy surface. Pressing " +
        "down, you feel the ground beneath the soft surface quite " +
        "firm and fully capable of supporting your weight.\n");
    add_item(({"streaks", "streak"}), "Here and there slim streaks " +
        "of bright sunlight reach down through the darkness of the " +
        "forest canopy above, piercing into the ghostly whiteness " +
        "of the mist on the ground. Where the streaks of light " +
        "burrow into the mist, a soft glow emanates, giving off a " +
        "ghostly light to the forest.\n");
    add_item("forest", "@@show_me_forest@@");
}

/*
 *  FUNCTION: set_creek_dir
 *  Arguments: cdir - string - direction the creek flows.
 *  Returns  :
 * 
 * Give the direction the creek flows. This is added to the desc
 * of the creek.
 *
*/
public void
set_creek_dir(string cdir)
{
    creek_dir = cdir;
}

/*
 *  FUNCTION: set_cliff_dir
 *  Arguments: cdir - string - direction of the cliff.
 *  Returns  :
 * 
 * Give the direction to the cliffs. This is added to the desc
 * of the cliffs.
 *
*/
public void
set_cliff_dir(string cdir)
{
    cliff_dir = cdir;
}

/*
 *  FUNCTION: set_exit_desc
 *  Arguments: noex  - int    - number of exits.
 *             edesc - string - description of possible exits.
 *  Returns  :
 * 
 * Give the description of all exits to this location. This is
 * given to players with high location sense when they examine
 * the forest.
 *
*/
public void
set_exit_desc(int no_ex, string edesc)
{
    exit_desc = edesc;
    no_exits = no_ex;
}

/*
 *  FUNCTION: show_me_mist
 *  Arguments:
 *  Returns  : string - description of mist.
 * 
 * Description of the mist. It depends on players height, and
 * whether the player has any boots worn or not.
 *
*/
public string
show_me_mist()
{
    int pl_size = TP->query_prop("_cont_i_height");
    int tv = 0, max;
    string some_most, waist_chest_head, feet_boots;
    string boot_desc = "", ret_desc;
    object *pl_boots;
    
    pl_boots = TP->query_clothing(TS_RFOOT);
    max = sizeof(pl_boots);
    
    if (max)
    {
        while ((tv <= max) && (boot_desc == ""))
        {
            if (pl_boots[tv]->query_name() == "boots")
            {
                boot_desc = pl_boots[tv]->query_short();
            }
        
            tv++;
        }
    }

    if (pl_size <= MIST_HEIGHT_HEAD)
    {
        some_most = "most";
        waist_chest_head = "neck";
    }
    
    else
    if (pl_size <= MIST_HEIGHT_CHEST)
    {
        some_most = "most";
        waist_chest_head = "chest";
    }
    
    else
    {
        some_most = "some";
        waist_chest_head = "waist";
    }

    if (boot_desc == "")
    {
        feet_boots = "feet";
    }
    else
    {
        feet_boots = boot_desc;
    }
    
    return "Floating silently about, the mist covers the " +
        "underbrush of this dark forest in a ghostly whiteness. " +
        "Damp and cold to the touch, the mist covers " + some_most +
        " of your body from your " + waist_chest_head + " and " +
        "down, making your " + feet_boots + " disappear entirely " +
        "in the dense whiteness. Here and there, small bushes or " +
        "large stalks of plants reach up from the ground, pale " +
        "white-green in colour. The mist glows brightly where slim " +
        "streaks of light break through the darkness of the forest " +
        "canopy above.\n";
}

/*
 *  FUNCTION: show_me_forest
 *  Arguments:
 *  Returns  : string - description of forest.
 * 
 * Return description of forest, based on players locationsense skill.
 *
*/
public string
show_me_forest()
{
    int skill = TP->query_skill(SS_LOC_SENSE);
    string desc, add_desc;
    
    desc = "Silence embraces this cold damp forest, where black " +
        "trees rise out of a meter thick ghostly white mist which " +
        "covers the ground. Only here and there slim streaks of " +
        "sunlight reach down through the forest canopy above.";
               
    if (skill < 40)
    {
        add_desc = "\n";
    }
    else
    {
        if (no_exits == 1)
        {
            add_desc = " Between the trees, your keen sense " +
                "notices one direction in which travel is easy " +
                "away from here. It leads " + exit_desc + ".\n";
        }
        else
        {
            add_desc = " Between the trees, your keen sense " +
                "notices several directions in which travel is " +
                "easy away from here. They lead " + exit_desc +
                ".\n";
        }
    }
    
    return desc + add_desc;
}

/*
 *  Functions for climbing trees, trunks, cliffs and function for
 *  drinking water from creek/lakes follow below. Add the appropriate
 *  actions in the local room.
 *  
 *  public int climb_tree(string what);
 *  public int drink_water(string what);
 *
 *  add_action(climb_tree, "climb");
 *  add_action(drink_water, "drink");
 *
*/

/*
 *  FUNCTION: climb_tree
 *  Arguments: string - what to climb.
 *  Returns  : int - 0/1. Was command executed here?
 * 
 * Climb function. Actually handles both climb tree, trunk and cliff.
 *
*/
public int
climb_tree(string what)
{
    string cmd;
    
    if (!what)
    {
        NF("Climb what?\n");
        return 0;
    }

    if (parse_command(what, TO, "[a] [black] [pine] %s", cmd))
    {
        if (cmd == "tree")
        {
            if (TP->resolve_task(TASK_ROUTINE, (( SS_DEX, SS_CLIMB ))) > 0)
            {
                write("With some difficulty you climb the black " +
                    "pine tree towards the darkness of the tree " +
                    "canopy. Finally reaching the top, you are " +
                    "greeted by brilliant sunlight. Looking around " +
                    "you see the small forest surrounded by tall " +
                    "cliffs to all sides. The forest seems to " +
                    "slope downwards towards the east and south " +
                    "and climbs up in the opposite directions. You " +
                    "watch the splendid view for a few moments, " +
                    "then climb back down again.\n");
                say(QCTNAME(TP) + " climbs one of the black trees " +
                    "all the way to the top.\nAfter a few moments " +
                    "of watching, " + HE(TP) + " climbs down again.\n");
                return 1;
            }
            else
            {
                write("It quickly becomes clear to you that these " +
                    "black trees are difficult to climb. You are " +
                    "forced to give up and return to the ground.\n");
                say(QCTNAME(TP) + " starts climbing one of the " +
                    "black trees, but stops and quickly returns to " +
                    "the ground again.\n");
                return 1;
            }
        }
        
        else
        if (cmd == "stump" && stump_size > 3)
        {
            if (TP->resolve_task(TASK_SIMPLE, (( SS_DEX, SS_CLIMB ))) > 0)
            {
                write("You laborously climb the dead black stump " +
                    "to its top. Looking around gives you a new " +
                    "perspective of the forest around you, but you " +
                    "otherwise learn nothing new. Shortly after " +
                    "you climb back down again.\n");
                say(QCTNAME(TP) + " climbs the dead black stump to " +
                    "its top, looks around and climbs back down " +
                    "again.\n");
                return 1;
            }
            else
            {
                write("It quickly becomes clear to you that the " +
                    "black stump is difficult to climb. You are " +
                    "forced to give up and return to the ground.\n");
                say(QCTNAME(TP) + " starts climbing the dead black " +
                    "stump, but stops and quickly returns to the " +
                    "ground again.\n");
                return 1;
            }
        }
    }

    if (loccliff)
    {
        if (what == "cliff" || what == "cliffside" ||
            what == "the cliff" || what == "the cliffside")
        {
            write("You look around shortly for good hand and " +
                "footholds and start climbing. You quickly give " +
                "up, though. The cliffside is much too steep and " +
                "slippery to be climbable from here.\n");
            say(QCTNAME(TP) + " walks to the cliffside and " +
                "attempts to climb it. " + capitalize(HE(TP)) +
                " quickly gives up. The cliff seems very steep and " +
                "slippery.\n");
            return 1;
        }
    }
    
    NF("Climb what?\n");
    return 0;
}

/*
 *  FUNCTION: drink_water
 *  Arguments: string - what to drink
 *  Returns  : int - 0/1. Was command executed here?
 * 
 * Handles attempts to drink from creek/lake locations.
 *
*/
public int
drink_water(string what)
{
    if ((what == "water") || (what == "from water"))
    {
        if (TP->drink_soft(TP->drink_max() / 25,0))
        {
            write("Kneeling down in the thick mist, you drink from " +
                "the clear water and feel refreshed.\n");
            say(QCTNAME(TP) + " kneels down in the thick mist and " +
                "drinks something.\n");
        }
        else
        {
            write("Kneeling down in the thick mist, you wet your " +
                "lips, but you are not thirsty enough to drink " +
                "deep from the water.\n");
        }
        return 1;
    }

    NF("Drink what?\n");
    return 0;
}

/*
 *  FUNCTION: init
 *  Arguments:
 *  Returns  :
 * 
 * It is always possible to climb something in the forest.
 * Add the command here.
 *
*/
public void
init()
{
    add_action(climb_tree, "climb");
    
    ::init();
}



