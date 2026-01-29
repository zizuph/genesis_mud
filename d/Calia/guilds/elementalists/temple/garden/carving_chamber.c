/*
 * Carving Chamber of the Elemental Guilds of Calia
 * 
 * This carving room is the first step to becoming a true Elemental
 * Worshipper of Calia. It contains the tools that you need to build
 * the tools of power for each of the 4 Prime Elements.
 *
 * The steps to becoming a Worshipper are as follows:
 * 1. Pray to the Elementals
 * 2. Ask for someone from the OCC or EW Council to vouch for you
 * 3. Pray to the Elementals again to receive instructions
 * 4. Construct the tools in this chamber
 * 5. Get accepted into the guild
 * 6. Carve the words of power into the tools
 * 7. Pray to the Elementals again to receive confirmation that you
 *    are done.
 *
 * Created by Petros, March 2014
 * Adapted from Code from the Worshippers East Chamber by Jacaar
 * Added Child Cleric Mandala construction, Jaacar - July 2016
 * Added Master Cleric Mandala carving, Jaacar - August 2016
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include "defs.h"

inherit GARDEN_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define WAND           (ELEMENTALIST_OBJS + "power_tool_wand")
#define DAGGER         (ELEMENTALIST_OBJS + "power_tool_dagger")
#define CHALICE        (ELEMENTALIST_OBJS + "power_tool_chalice")
#define PENTACLE       (ELEMENTALIST_OBJS + "power_tool_pentacle")
#define CHILD_MANDALA  (ELEMENTALIST_OBJS + "child_mandala")
#define FIRE_MANDALA   (ELEMENTALIST_OBJS + "fire_mandala")
#define AIR_MANDALA    (ELEMENTALIST_OBJS + "air_mandala")
#define WATER_MANDALA  (ELEMENTALIST_OBJS + "water_mandala")
#define EARTH_MANDALA  (ELEMENTALIST_OBJS + "earth_mandala")
#define SPIRIT_MANDALA (ELEMENTALIST_OBJS + "spirit_mandala")

// Prototypes
void next_step(int tool, int loop, object player);
void mandala_next_step(int loop, object player);
void mandala_carve_next_step(int loop, object player, string symbol, string carving);

// Global Variables
public int         construct_id;
public string      comp_short;
public object      component;

public void
create_garden_room()
{
    set_short("A small chamber");
    set_long("This small chamber has a wooden table with a "+
        "bench in front of it. On the table are several tools. "+
        "In the corner of the chamber you see a small forge, and a "+
        "pool filled with water. The adobe walls are covered by a "+
        "roof of grass and straw, which have become blackened near "+
        "the area surrounding the forge. The ground is a uniformly green, "+
        "evenly cut grass. The only exit is back to the east.\n");

    add_item(({"wooden table","table"}),"The table is not very "+
        "large, but roomy enough for one person to sit at to "+
        "use the tools that are on it.\n");

    add_item(({"wall","walls"}),"The adobe walls are made from "+
        "the same stones you have seen throughout the temple. "+
        "They are blackened near the area surrounding the forge.\n");
        
    add_item("bench","The bench is large enough for one person "+
        "to sit on, and made of the same wood as the table. It "+
        "appears to be well used.\n");

    add_item(({"tool","tools","several tools"}),"You see various "+
        "polished tools on the table. Among them you recognize "+
        "a fine chisel, a carving knife, a paintbrush, a hammer, "+
        "a cast, a cleaning cloth, a cleaning brush, a buffing "+
        "cloth, and some inks.\n");

    add_item(({"chisel","fine chisel"}),"The fine chisel seems to be made "+
        "from a strong metal and has a small wooden handle.\n");

    add_item(({"knife","carving knife"}),"The carving knife looks "+
        "very sharp indeed. There is strange writing you do not "+
        "recognize on the hilt of the blade.\n");

    add_item(({"paintbrush"}),"The paintbrush has a wooden handle "+
        "with bristles on one end that come to a small round point.\n");
        
    add_item(({"hammer"}),"It is a small hammer with a wooden handle "+
        "and a metal head.\n");
        
    add_item(({"cast"}),"This cast is made of sturdy iron and is "+
        "round in shape.\n");
    
    add_item(({"cloth"}),"Did you want to examine the buffing "+
        "cloth or cleaning cloth?\n");
        
    add_item(({"cleaning cloth"}),"The cleaning cloth is made "+
        "of cotton.\n");
    
    add_item(({"brush","cleaning brush"}),"The cleaning brush has a "+
        "small wooden base that you can hold on to and hundreds of "+
        "short, stiff bristles protruding from the bottom of the base.\n");
    
    add_item(({"buffing cloth"}),"The buffing cloth is made of a "+
        "very soft and smooth material and looks like it would be "+
        "good for buffing and polishing objects.\n");
        
    add_item(({"ink","inks","some inks","ink well","ink wells"}),
        "There are various inks on the table, each in their own well.\n");

    add_item(({"forge","small forge"}),"The forge is simply a small "+
        "stone pit with a burning hot flame in it. Atop of it you "+
        "see a small metal bowl which appears to have silver, gold, "+
        "copper, and platinum stains in it.\n");

    add_item(({"bowl","small bowl","metal bowl","small metal bowl"}),"It is "+
        "a small metal bowl. It is heavily stained with copper, "+
        "gold, silver, and platinum on the inside.\n");

    add_item(({"pool","water"}),"The pool is constructed from small "+
        "stones placed in a circular form. The water appears to be "+
        "clean and fresh.\n");

    add_item("grass","Every blade of grass here is the same shade "+
        "of green, and exactly the same height.\n");

    add_exit(ELEMENTALIST_GARDEN + "garden_06a", "east");
}

public void
init()
{
    ::init();
    add_action("construct","construct");
    add_action("construct", "forge");
    add_action("recover","recover");
    add_action("recover","restore");
    add_action("carve","carve");
    add_action("destroy","destroy");
}

/*
 * function name: destroy
 * description  : Allows players to attempt to destroy a tool
 *                cancelling the power of it.
 * arguments    : string str - what to try destroy.
 * returns      : 0 - failure.
 *                1 - success.
 */
public int
destroy(string str)
{
    if (!strlen(str))
    {
        notify_fail("Destroy what?\n");
        return 0;
    }

    str = lower_case(str);
    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (!objectp(target) || !target->is_elemental_power_tool())
    {
        notify_fail("You cannot destroy " + str + "! You can only "
                    + "destroy Elemental power tools here.\n");
        return 0;
    }

    write("You throw your " + target->short() + " into the forge and "
          + "watch it melt into nothingness.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
              + " throws something into the forge.\n", this_player());
    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                       + " destroys " + this_player()->query_possessive()
                       + " " + target->short() + ".", CONSTRUCTION_LOG);
    target->remove_object();
    return 1;
}

/*
 * Function:    player_carve_count
 * Description: Returns the number of times that the player
 *              has actually carved.
 */
public int
player_carve_count(object player)
{
    setuid();
    seteuid(getuid());
    int carve_value;
    
    carve_value = (GUILD_MANAGER->is_fire_carved(player)
        + GUILD_MANAGER->is_air_carved(player)
        + GUILD_MANAGER->is_water_carved(player)
        + GUILD_MANAGER->is_earth_carved(player));
    
    if (IS_CLERIC(player))
        carve_value += GUILD_MANAGER->is_spirit_carved(player);
    
    return carve_value;    
}

/*
 * Function:    max_carve_count
 * Description: Returns the maximum number of carvings
 *              that the player can do based on his
 *              guild stat.
 */
public int
max_carve_count(object player)
{
    int max_carve_count;
    
    if (IS_WORSHIPPER(player))
        max_carve_count = min(4, player->query_base_stat(SS_LAYMAN) / 20);
        
    if (IS_CLERIC(player))
    {
    	// If they aren't a child cleric, they can carve, otherwise not allowed yet
    	if (!(GUILD_MANAGER->query_is_child_cleric(this_player())))
            max_carve_count = 1;
        else
            max_carve_count = 0;
    }
    
    return max_carve_count;
}

public int
can_carve_power_tool()
{
    // Checks
    // 1. If the player can carve based on achievements in the guild
    // 2. If the player has been given permission by the council. The
    //    Council check doesn't look like it's active recently.

    /* Is the player able to carve again? carve_count() returns */
    /* the number of times they have carved, carve_count(1) */
    /* returns the number of times they _can_ carve. */
    
    if (IS_WORSHIPPER(this_player()))
    {
        int carve_count = player_carve_count(this_player());
        if (carve_count >= 4)
        {
            notify_fail("You've already completed carving all of your tools!\n");
            return 0;
        }
    
        if (carve_count >= max_carve_count(this_player()))
        {
            notify_fail("You are not yet ready to carve upon one of your "
                        + "Elemental Tools.\n");
            return 0;
        }
    
        return 1;
    }
    
    if (IS_CLERIC(this_player()))
    {
        int carve_count = player_carve_count(this_player());
        if (carve_count >= 1)
        {
            notify_fail("You've already completed carving your mandala!\n");
            return 0;
        }
        return 1;
    }
    return 0;
}

/*
 * function name: carve
 * description  : Allows players to attempt to carve a word
 *                of power into an elemental tool.
 * arguments    : string str - what to try carving.
 * returns      : 0 - failure.
 *                1 - success.
 */
public int
carve(string str)
{
    setuid();
    seteuid(getuid());
    if (!IS_MEMBER(this_player()))
    {
        return 0;
    }

    if (!can_carve_power_tool())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Carve what? Some word perhaps?\n");
        return 0;
    }

    str = lower_case(str);
    object tool;
    int bHasCarved = 0;
    switch (str)
    {
    case "ergon": // fire wand
        tool = present("_elemental_guild_wand", this_player());
        bHasCarved = GUILD_MANAGER->is_fire_carved(this_player());
        break;
    case "egsousia": // air dagger
        tool = present("_elemental_guild_dagger", this_player());
        bHasCarved = GUILD_MANAGER->is_air_carved(this_player());
        break;
    case "meizon": // water chalice
        tool = present("_elemental_guild_chalice", this_player());
        bHasCarved = GUILD_MANAGER->is_water_carved(this_player());
        break;
    case "ischuroteros": // earth pentacle
        tool = present("_elemental_guild_pentacle", this_player());
        bHasCarved = GUILD_MANAGER->is_earth_carved(this_player());
        break;
    case "fotia": // fire mandala
        tool = present("_elemental_guild_mandala", this_player());
        bHasCarved = GUILD_MANAGER->is_fire_carved(this_player());
        break;
    case "aeras": // air mandala
        tool = present("_elemental_guild_mandala", this_player());
        bHasCarved = GUILD_MANAGER->is_air_carved(this_player());
        break;
    case "nero": // water mandala
        tool = present("_elemental_guild_mandala", this_player());
        bHasCarved = GUILD_MANAGER->is_water_carved(this_player());
        break;
    case "gi": // earth mandala
        tool = present("_elemental_guild_mandala", this_player());
        bHasCarved = GUILD_MANAGER->is_earth_carved(this_player());
        break;
    case "pnevma": // spirit mandala
        tool = present("_elemental_guild_mandala", this_player());
        bHasCarved = GUILD_MANAGER->is_spirit_carved(this_player());
        break;
    default:
        notify_fail("You don't seem to have any idea how to even "
                    + "begin carving " + str + " into something.\n");
        return 0;
    }

    if (!objectp(tool))
    {
        notify_fail("You can't seem to find the right Elemental power "
                    + "tool for you to carve " + capitalize(str)
                    + " on.\n");
        return 0;
    }

    if (bHasCarved)
    {
        notify_fail("You have already carved your " + tool->short()
                    + "!\n");
        return 0;
    }

    if (IS_WORSHIPPER(this_player()))
    {
    	switch (str)
	    {
		    case "ergon": // fire wand
		        GUILD_MANAGER->set_fire_carving(this_player());
		        break;
		    case "egsousia": // air dagger
		        GUILD_MANAGER->set_air_carving(this_player());
		        break;
		    case "meizon": // water chalice
		        GUILD_MANAGER->set_water_carving(this_player());
		        break;
		    case "ischuroteros": // earth pentacle
		        GUILD_MANAGER->set_earth_carving(this_player());
		        break;
		}
	}
	
	if (IS_CLERIC(this_player()))
	{
		switch(str)
		{
			case "fotia": // fire mandala
				if (GUILD_MANAGER->query_primary_element(this_player()) == "fire")
				    GUILD_MANAGER->set_fire_carving(this_player());
				else
		        {
		        	notify_fail("You have not selected Lord Pyros as your "+
		        	    "patron elemental.\n");
		        	return 0;
		        }
		        break;
		    case "aeras": // air mandala
		    	if (GUILD_MANAGER->query_primary_element(this_player()) == "air")
		        	GUILD_MANAGER->set_air_carving(this_player());
		        else
		        {
		        	notify_fail("You have not selected Lady Aeria as your "+
		        	    "patron elemental.\n");
		        	return 0;
		        }
		        break;
		    case "nero": // water mandala
		    	if (GUILD_MANAGER->query_primary_element(this_player()) == "water")
		        	GUILD_MANAGER->set_water_carving(this_player());
		        else
		        {
		        	notify_fail("You have not selected Lord Diabrecho as your "+
		        	    "patron elemental.\n");
		        	return 0;
		        }
		        break;
		    case "gi": // earth mandala
		    	if (GUILD_MANAGER->query_primary_element(this_player()) == "earth")
		        	GUILD_MANAGER->set_earth_carving(this_player());
		        else
		        {
		        	notify_fail("You have not selected Lady Gu as your "+
		        	    "patron elemental.\n");
		        	return 0;
		        }
		        break;
		    case "pnevma": // spirit mandala
		    	if (GUILD_MANAGER->query_primary_element(this_player()) == "life")
		        	GUILD_MANAGER->set_spirit_carving(this_player());
		        else
		        {
		        	notify_fail("You have not selected Psuchae as your "+
		        	    "patron elemental.\n");
		        	return 0;
		        }
		        break;
		}
    }
    
    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                       + " carves '" + capitalize(str) + "' into " 
                       + this_player()->query_possessive()
                       + " " + tool->short() + ".", CONSTRUCTION_LOG);
                       
    // If they aren't a Cleric, they just carve their name
    if (!IS_CLERIC(this_player()))
    {
    	write("You take a fine chisel from the table and carve "
	          + capitalize(str) + " into the " + tool->short() + ", then "
	          + "return the chisel to the table.\n");
	    tell_room(environment(this_player()), QCTNAME(this_player())
	              + " takes a tool from the table and carves something "
	              + "into " + this_player()->query_possessive() + tool->short()
	              + ", then returns the tool to the table.\n", this_player());
	}
	
	// If they are a Cleric, there is a small routine to carve their name
	else
	{
		string symbol = GUILD_MANAGER->query_primary_element(this_player());
    	mandala_carve_next_step(1, this_player(),symbol,str);
	}
	
    return 1;
}

/*
 * Function:    recover
 * Description: Recover an elemental power tool that the player has
 *              lost or destroyed previously.
 */
public int
recover(string str)
{
    object tool;
    setuid();
    seteuid(getuid());
    
    if (!IS_MEMBER(this_player()))
    {
        notify_fail("You are not a member of this guild!\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Recover what? Are you missing an Elemental power tool?\n");
        return 0;
    }

    str = lower_case(str);
    if (str == "wand")
    {
        if (present("_elemental_guild_wand", this_player()))
        {
            write("You already possess the Fire Wand!\n");
            return 1;
        }
        tool = clone_object(WAND);
        tool->move(this_player(), 1);
        write("A " + tool->short() + " materializes in your hands.\n");
        send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                           + " recovers " + this_player()->query_possessive()
                           + " " + tool->short() + ".", CONSTRUCTION_LOG);
        return 1;
    }
    if (str == "dagger")
    {
        if (present("_elemental_guild_dagger", this_player()))
        {
            write("You already possess the Air Dagger!\n");
            return 1;
        }
        tool = clone_object(DAGGER);
        tool->move(this_player(), 1);
        write("A " + tool->short() + " materializes in your hands.\n");
        send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                           + " recovers " + this_player()->query_possessive()
                           + " " + tool->short() + ".", CONSTRUCTION_LOG);
        return 1;
    }
    if (str == "chalice")
    {
        if (present("_elemental_guild_chalice", this_player()))
        {
            write("You already possess the Water Chalice!\n");
            return 1;
        }
        tool = clone_object(CHALICE);
        tool->move(this_player(), 1);
        write("A " + tool->short() + " materializes in your hands.\n");
        send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                           + " recovers " + this_player()->query_possessive()
                           + " " + tool->short() + ".", CONSTRUCTION_LOG);
        return 1;
    }
    if (str == "pentacle")
    {
        if (present("_elemental_guild_pentacle", this_player()))
        {
            write("You already possess the Earth Pentacle!\n");
            return 1;
        }
        tool = clone_object(PENTACLE);
        tool->move(this_player(), 1);
        write("A " + tool->short() + " materializes in your hands.\n");
        send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                           + " recovers " + this_player()->query_possessive()
                           + " " + tool->short() + ".", CONSTRUCTION_LOG);
        return 1;
    }
    
    if (str == "mandala")
    {
        if (!IS_CLERIC(this_player()))
        {
            notify_fail("Recover what? Are you missing an Elemental power tool?\n");
            return 0;
        }
        
        if (present("_elemental_guild_mandala", this_player()))
        {
            write("You already possess the Sacred Mandala!\n");
            return 1;
        }
        
        string element = GUILD_MANAGER->query_primary_element(this_player());
        switch(element)
        {
            case "fire":
                tool = clone_object(FIRE_MANDALA);
                break;
            case "air":
                tool = clone_object(AIR_MANDALA);
                break;
            case "water":
                tool = clone_object(WATER_MANDALA);
                break;
            case "earth":
                tool = clone_object(EARTH_MANDALA);
                break;
            case "life":
                tool = clone_object(SPIRIT_MANDALA);
                break;
            default:
                tool = clone_object(CHILD_MANDALA);
                break;
        }
                
        tool->move(this_player(), 1);
        write("A " + tool->short() + " materializes in your hands.\n");
        send_debug_message("cleric", capitalize(this_player()->query_real_name())
                           + " recovers " + this_player()->query_possessive()
                           + " " + tool->short() + ".", CONSTRUCTION_LOG);
        return 1;
    }

    notify_fail("Recover what? Are you missing an Elemental power tool?\n");
    return 0;
}

public int
construct(string str)
{
    object * temp;

    setuid();
    seteuid(getuid());

    if (IS_MEMBER(this_player()))
    {
        if (!(GUILD_MANAGER->query_is_child_cleric(this_player())))
        {
        	if (!(TP->query_wiz_level()))
			{
	            write("You don't need to construct anything! Try <recover> if you "
	                  + "have lost one of your Tools.\n");
	            return 1;
	        }
        }
    }

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what with what?\n");
        return 0;
    }

    str = lower_case(str);
    string tool_name, component_name;
    if (sscanf(str, "%s with %s", tool_name, component_name) != 2)
    {
        notify_fail(capitalize(query_verb()) + " what with what?\n");
        return 0;
    }

    if (tool_name != "chalice" && tool_name != "dagger" && tool_name != "wand" && tool_name != "pentacle"
        && tool_name != "mandala")
    {
        notify_fail("You cannot " + lower_case(query_verb()) + " that here.\n");
        return 0;
    }

    if (!sizeof(temp = FIND_STR_IN_OBJECT(component_name, this_player())))
    {
        notify_fail(capitalize(query_verb()) + " " + tool_name + " with what?\n");
        return 0;
    }

    if (sizeof(temp) > 1)
    {
        notify_fail("You can't " + lower_case(query_verb()) + " " 
                    + LANG_ADDART(tool_name) + " with more than " 
                    + "one thing! Try again with just one item.\n");
        return 0;
    }

    if (sizeof(get_alarm(construct_id)))
    {
        write("Someone else is already using the tools. You will "+
            "have to try again in a few minutes.\n");
        return 1;
    }

    object tool;
    component = temp[0];
    switch (tool_name)
    {
    case "wand":
        tool = present("_elemental_guild_wand", this_player());
        if (objectp(tool))
        {
            write("You already possess the " + tool->short() 
                  + "! There is no need to construct it again!\n");
            return 1;
        }
        if ((!component->id("stick") &&
            !component->id("staff")) ||
            !present("copper coin", this_player()))
        {
            write("You do not have the necessary components to construct "
                  + "the Fire Wand.\n");
            return 1;
        }
        next_step(0, 1, this_player());
        return 1;
        
    case "dagger":
        tool = present("_elemental_guild_dagger", this_player());
        if (objectp(tool))
        {
            write("You already possess the " + tool->short() 
                  + "! There is no need to construct it again!\n");
            return 1;
        }
        if ((!component->id("dagger") &&
             !component->id("knife")) ||
            !present("silver coin", this_player()))
        {
            write("You do not have the necessary components to "
                  + "construct the Air Dagger.\n");
            return 1;
        }
        if (component->query_weapon_hits())
        {
            write("That " + component->short() + " is not pure!  " +
                "You must use a pure " + component->short() + ".\n");
            return 1;
        }
        next_step(1, 1, this_player());
        return 1;

    case "chalice":
        tool = present("_elemental_guild_chalice", this_player());
        if (objectp(tool))
        {
            write("You already possess the " + tool->short() 
                  + "! There is no need to construct it again!\n");
            return 1;
        }
        if ((!component->id("glass") &&
            !component->id("goblet") &&
            !component->id("chalice")) ||
            !present("gold coin", this_player()))
        {
            write("You do not have the necessary components to construct "
                  + "the Water Chalice.\n");
            return 1;
        }
        next_step(2, 1, this_player());
        return 1;

    case "pentacle":
        tool = present("_elemental_guild_pentacle", this_player());
        if (objectp(tool))
        {
            write("You already possess the " + tool->short() 
                  + "! There is no need to construct it again!\n");
            return 1;
        }
        if ((!component->id("plate") &&
             !component->id("bowl")) ||
            !present("platinum coin", this_player()))
        {
            write("You do not have the necessary components to "
                  + "construct the Earth Pentacle.\n");
            return 1;
        }
        next_step(3, 1, this_player());
        return 1;
    
    case "mandala":
        tool = present("_elemental_guild_mandala", this_player());
        if (objectp(tool))
        {
            write("You already possess the " + tool->short() 
                  + "! There is no need to construct it again!\n");
            return 1;
        }
        if ((!component->id("sporos") || (!present("silver coin", this_player()))))
        {
            write("You do not have the necessary components to "
                  + "construct the Sacred Mandala.\n");
            return 1;
        }
        mandala_next_step(1, this_player());
        return 1;
    }

    write("You cannot construct that here.\n");
    return 1;
}

public void
next_step(int tool, int loop, object player)
{
    object sac_coin;
    string coin_name;
    switch (loop)
    {
        case 1:
            coin_name = ({"copper","silver","gold","platinum"})[tool];
            sac_coin=present(coin_name + " coin", player);
            sac_coin->set_heap_size(sac_coin->num_heap() -1);
            tell_object(player, "You light a fire in the forge.\n");
            tell_room(this_object(), QCTNAME(player)+" lights "+
                "a fire in the small forge.\n",player);
            tell_object(player, "You place the " + coin_name +
                " coin into a metal bowl to melt.\n");
            tell_room(this_object(), QCTNAME(player)+" places "+
                "a "+coin_name+" coin into a metal bowl.\n",player);
            comp_short = component->short();
            component->add_prop(OBJ_M_NO_DROP, "You are in the middle of " +
                "working on the " + comp_short + ", you can't " +
                "put it down now.\n");
            break;
        case 2:
            tell_object(player, "You begin to prepare the "+comp_short+
                " using the tools from the table.\n");
            tell_room(this_object(), QCTNAME(player)+" begins "+
                "working on a "+comp_short+".\n",player);
            break;
        case 3:
            tell_object(player,"You finish your work on the "+
                comp_short+" and dip it into the forge to coat "+
                "it in metal.\n");
            tell_room(this_object(), QCTNAME(player)+" dips "+
                "the finished "+comp_short+" into the metal "+
                "bowl on the forge.\n",player);
            break;
        case 4:
            switch (tool)
            {
                case 0:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Pyros' and '"+
                        capitalize(player->query_real_name())+
                        "' onto the "+
                        "shaft.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                    "into a wand.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Fire Wand.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged wand.\n",player);
                    component->remove_object();
                    clone_object(WAND)->move(player,1);
                    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                                       + " forges " + this_player()->query_possessive()
                                       + " Fire Wand.", CONSTRUCTION_LOG);
                    break;
                case 1:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Aeria' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "hilt.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "onto a dagger.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Air Dagger.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged dagger.\n",player);
                    component->remove_object();
                    clone_object(DAGGER)->move(player,1);
                    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                                       + " forges " + this_player()->query_possessive()
                                       + " Air Dagger.", CONSTRUCTION_LOG);
                    break;
                case 2:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Diabrecho' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "rim.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "into a chalice.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Water Chalice.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged chalice.\n",player);
                    component->remove_object();
                    clone_object(CHALICE)->move(player,1);
                    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                                       + " forges " + this_player()->query_possessive()
                                       + " Water Chalice.", CONSTRUCTION_LOG);
                    break;
                case 3:
                    tell_object(player, "You take a fine chisel from the "+
                        "table and carve 'Gu' and '"+
                        capitalize(player->query_real_name())+"' onto the "+
                        "outer rim.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " takes a tool from the table and carves something "+
                        "into a pentacle.\n",player);
                    tell_object(player, "You have finished construction "+
                        "of the Earth Pentacle.\n");
                    tell_room(this_object(),QCTNAME(player)+
                        " holds aloft a newly forged pentacle.\n",player);
                    component->remove_object();
                    clone_object(PENTACLE)->move(player,1);
                    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                                       + " forges " + this_player()->query_possessive()
                                       + " Earth Pentacle.", CONSTRUCTION_LOG);
                    break;
            }
            break;
    }

    if (loop == 4)
        return;

    loop++;
    construct_id = set_alarm(5.0, 0.0, &next_step(tool, loop, player));
    return;
}

public void
mandala_next_step(int loop, object player)
{
    object sac_coin;
    string coin_name;
    switch (loop)
    {
        case 1: // Clean the tools
            tell_object(player,"You clean the paintbrush, hammer, "+
                "cast, cleaning cloth, cleaning brush, buffing cloth "+
                "and a silver coin in the pool.\n");
            tell_room(this_object(), QCTNAME(player)+" cleans the "+
                "paintbrush, hammer, cast, cleaning cloth, cleaning "+
                "brush, buffing cloth and a silver coin in the pool.\n",player);
            break;
        case 2: // Melt the coin and cast the metal
            coin_name = "silver";
            sac_coin=present(coin_name + " coin", player);
            sac_coin->set_heap_size(sac_coin->num_heap() -1);
            tell_object(player, "You light a fire in the forge.\n");
            tell_room(this_object(), QCTNAME(player)+" lights "+
                "a fire in the small forge.\n",player);
            tell_object(player, "You place the " + coin_name +
                " coin into a metal bowl to melt.\n");
            tell_room(this_object(), QCTNAME(player)+" places "+
                "a "+coin_name+" coin into a metal bowl.\n",player);
            tell_object(player, "You pour the " + coin_name +
                " from the metal bowl into the cast.\n");
            tell_room(this_object(), QCTNAME(player)+" pours "+
                "the "+coin_name+" from the metal bowl into the "+
                "cast.\n",player);            
            break;
        case 3: // Cool the cast and remove object
            tell_object(player, "You place the cast into the "+
                "pool to cool.\n");
            tell_room(this_object(), QCTNAME(player)+" places "+
                "the cast into the pool to cool.\n",player);
            tell_room(this_object(),"Steam rises rises from the "+
                "pool as the cast cools down rapidly.\n",0);
            tell_object(player, "You retrive the cast from the "+
                "pool, open it and remove the metal object "+
                "that was inside.\n");
            tell_room(this_object(), QCTNAME(player)+" retrieves "+
                "the cast from the pool, opens it and removes "+
                "the silver object that was inside.\n",player);
            break;
        case 4: // Clean object 
            tell_object(player,"You brush the metal object "+
                "vigorously with the cleaning brush, removing "+
                "any excess bits of metal that are sticking "+
                "out from the otherwise round object.\n");
            tell_room(this_object(), QCTNAME(player)+" brushes "+
                "the metal object vigorously with the cleaning "+
                "brush.\n",player);
            tell_object(player,"You clean the metal object "+
                "with the cleaning cloth, removing "+
                "any dirt or charred bits of metal from it.\n");
            tell_room(this_object(), QCTNAME(player)+" cleans "+
                "the metal object with the cleaning cloth.\n",player);
            break;
        case 5: // Smooth object 
            tell_object(player,"You smooth the surface of the "+
                "now silver metal object with the buffing cloth, "+
                "buffing out any impurities.\n");
            tell_room(this_object(), QCTNAME(player)+" smooths "+
                "the surface of the now silver metal object with "+
                "the buffing cloth.\n",player);
            break;
        case 6: // Place Sporos 
            comp_short = capitalize(component->short());
            component->add_prop(OBJ_M_NO_DROP, "You have already "+
                "placed the " + comp_short + " into the object so "+
                "you can't put it down now.\n");
            tell_object(player,"You finish your work on the "+
                "object. You pick up the hammer and gently "+
                "hammer the "+comp_short+" into the centre of "+
                "the silver object.\n");
            tell_room(this_object(), QCTNAME(player)+" picks up "+
                "a hammer and gently hammers "+HIS+" "+comp_short+
                " into the centre of the silver object.\n",player);            
            break;
        case 7: // Prepare inks
            tell_object(player,"You begin to prepare the inks "+
                "that you will require for painting.\n");
            tell_room(this_object(), QCTNAME(player)+" begins "+
                "to prepare the inks "+HE+" requires.\n",player);
            break;
        case 8: // Draw Kyklos 
            tell_object(player,"You finish preparing the inks, "+
                "pick up the paintbrush, dip it into the ink "+
                "and draw the Kyklos on the silver object.\n");
            tell_room(this_object(), QCTNAME(player)+" finishes "+
                "preparing the inks, picks up a paintbrush, dips "+
                "it into the ink and draws what appears to be a "+
                "circle on the object.\n",player);
            break;
        case 9: // Draw Plateia 
            tell_object(player,"You complete drawing the Kyklos, "+
                "dip your paintbrush into another one of the inks "+
                "and draw the Plateia on the silver object, "+
                "ensuring the corners touch the Kyklos.\n");
            tell_room(this_object(), QCTNAME(player)+" dips "+
                "the paintbrush into another one of the inks and "+
                "carefully draws what appears to be a square on "+
                "the object.\n",player);
            break;
        case 10: // Carve name 
            tell_object(player,"With the drawing complete, you "+
                "put down the paintbrush, pick up the chisel and "+
                "carve your name into the outer edge of the silver "+
                "object using ancient runes.\n");
            tell_room(this_object(), QCTNAME(player)+" puts down "+
                "the paintbrush, picks up a chisel and carves some "+
                "kind of runes into the outer edge of the silver "+
                "object.\n",player);
            break;    
        case 11: // Purify symbol
            tell_object(player, "Having completed the carving, you "+
                "now submerge the silver object into the pool once "+
                "again.\n");
            tell_room(this_object(),QCTNAME(player)+
                " submerges the silver object into the pool once "+
                "again.\n",player);
            tell_object(player, "As your hand becomes fully immersed "+
                "in the water, you feel the silver object vibrate "+
                "rapidly. Ripples start to form on the surface of the "+
                "pool from the vibration. The vibration calms quickly, "+
                "then disappears all together, as do the ripples.\n");
            tell_room(this_object(),"As "+QCPNAME(player)+
                " hand becomes fully immersed in the water, you see "+
                "ripples starting to form on the surface of the pool. "+
                "After a few moments the ripples disappear.\n",player);
            tell_object(player, "You have finished construction "+
                "of the Sacred Mandala.\n");
            tell_room(this_object(),QCTNAME(player)+
                " holds aloft a newly forged silver object.\n",player);
            component->remove_object();
            clone_object(CHILD_MANDALA)->move(player,1);
            send_debug_message("cleric", capitalize(this_player()->query_real_name())
                               + " forges " + this_player()->query_possessive()
                               + " Child Mandala.", CONSTRUCTION_LOG);
            break;
    }

    if (loop == 11)
        return;

    loop++;
    construct_id = set_alarm(5.0, 0.0, &mandala_next_step(loop, player));
    return;
}

public void
mandala_carve_next_step(int loop, object player, string symbol, string carving)
{
    switch (loop)
    {
        case 1: // Clean the tools
            tell_object(player,"You clean the paintbrush, cleaning cloth, "+
                "cleaning brush, buffing cloth and chisel in the pool.\n");
            tell_room(this_object(), QCTNAME(player)+" cleans the "+
                "paintbrush, cleaning cloth, cleaning brush, buffing cloth "+
                "and the chisel in the pool.\n",player);
            break;
        case 2: // Clean mandala 
            tell_object(player,"You brush the mandala "+
                "vigorously with the cleaning brush, removing "+
                "any dirt from it.\n");
            tell_room(this_object(), QCTNAME(player)+" brushes "+
                HIS+ " mandala vigorously with the cleaning "+
                "brush.\n",player);
            tell_object(player,"You clean the mandala "+
                "with the cleaning cloth, removing "+
                "any final bits of dirt from it.\n");
            tell_room(this_object(), QCTNAME(player)+" cleans "+
                HIS+ " mandala with the cleaning cloth.\n",player);
            break;
        case 3: // Smooth object 
            tell_object(player,"You smooth the surface of the "+
                "mandala with the buffing cloth, "+
                "buffing out any impurities.\n");
            tell_room(this_object(), QCTNAME(player)+" smooths "+
                "the surface of "+HIS+" mandala with "+
                "the buffing cloth.\n",player);
            break;
        case 4: // Prepare inks
            tell_object(player,"You begin to prepare the inks "+
                "that you will require for painting.\n");
            tell_room(this_object(), QCTNAME(player)+" begins "+
                "to prepare the inks "+HE+" requires.\n",player);
            break;
        case 5: // Draw Diety pattern 
            tell_object(player,"You finish preparing the inks, "+
                "pick up the paintbrush, dip it into the ink "+
                "and draw the pattern of "+symbol+" on the mandala, ensuring to "+
                "start at the Sporos and work your way outwards.\n");
            tell_room(this_object(), QCTNAME(player)+" finishes "+
                "preparing the inks, picks up a paintbrush, dips "+
                "it into the ink and draws a symbol "+
                "on "+HIS+" mandala.\n",player);
            break;
        case 6: // Carve name 
            tell_object(player,"With the drawing complete, you "+
                "put down the paintbrush, pick up the chisel and "+
                "carve "+carving+" into the outer edge of the mandala "+
                "using ancient runes.\n");
            tell_room(this_object(), QCTNAME(player)+" puts down "+
                "the paintbrush, picks up a chisel and carves some "+
                "kind of runes into the outer edge of "+HIS+
                " mandala.\n",player);
            break;    
        case 7: // Purify symbol
            tell_object(player, "Having completed the carving, you "+
                "now submerge the mandala into the pool once "+
                "again.\n");
            tell_room(this_object(),QCTNAME(player)+
                " submerges "+HIS+" mandala into the pool once "+
                "again.\n",player);
            tell_object(player, "As your hand becomes fully immersed "+
                "in the water, you feel the mandala vibrate "+
                "rapidly. Ripples start to form on the surface of the "+
                "pool from the vibration. The vibration calms quickly, "+
                "then disappears all together, as do the ripples.\n");
            tell_room(this_object(),"As "+QCPNAME(player)+
                " hand becomes fully immersed in the water, you see "+
                "ripples starting to form on the surface of the pool. "+
                "After a few moments the ripples disappear.\n",player);
            tell_object(player, "You have finished construction "+
                "of the Sacred Mandala.\n");
            tell_room(this_object(),QCTNAME(player)+
                " holds aloft "+HIS+" newly carved mandala.\n",player);
            present("_elemental_guild_mandala",player)->remove_object();
            switch(symbol)
            {
            	case "fire":
            		clone_object(FIRE_MANDALA)->move(player,1);
            		break;
            	case "water":
            		clone_object(WATER_MANDALA)->move(player,1);
            		break;
            	case "air":
            		clone_object(AIR_MANDALA)->move(player,1);
            		break;
            	case "earth":
            		clone_object(EARTH_MANDALA)->move(player,1);
            		break;
            	case "life":
            		clone_object(SPIRIT_MANDALA)->move(player,1);
            		break;
            }
            send_debug_message("cleric", capitalize(this_player()->query_real_name())
                               + " carves " + this_player()->query_possessive()
                               + " Master Mandala.", CONSTRUCTION_LOG);
            break;
    }

    if (loop == 7)
        return;

    loop++;
    construct_id = set_alarm(5.0, 0.0, &mandala_carve_next_step(loop, player, symbol, carving));
    return;
}
