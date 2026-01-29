/*
 * Garden Tending Paralyze Object
 * 
 * With the right objects, someone can begin tending the garden. Tending
 * the garden involves performing various tasks with the gardening tools
 * found in the shed.
 *
 * Created by Petros, May 2011
 */

#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"

inherit "/std/paralyze";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         display_tend_message();


// Variables
private static string * base_allow_verbs = ({
    "look",
    "l",
    "last",
    "mwho",
    "team",
    "who",
});
public int              num_cycles = 0; // number of times we have successfully updated the health

// Each Garden Health Level actually has 20 health points. We split up the 20
// health points amongst the different tasks
// 0..4 - use hoe to loosen dirt
// 5..6 - gathering weeds
// 7..12 - pruning the bushes, shrubs, and trees
// 13..14 - gathering the branches
// 15..17 - watering the trees, bushes, and shrubs
// 18..19 - watering the furrows and herbs
//
// Tend Messages will be an mapping of arrays with each child array in the
// following formats:
//   ({ number of seconds, self message, room message, interim self message, ending self message })
public mapping tend_messages = ([
    "loosening" : ({ 12.0, "You take the gardening hoe and begin applying "
            + "it to the tough soil between the furrows. You twist the "
            + "hoe as you do so to loosen both the soil and separate out "
            + "the weeds from the ground.",
              "uses the hoe between the furrows to loosen the weeds.",
              "The soil loosens easily with your forceful application and "
            + "you begin to see the weeds come loose.",
              "The soil has now been loosened and some weeds have been "
            + "loosened out of the soil." }),
    "gather weeds" : ({ 10.0, "Seeing the weeds that have been loosened from "
            + "the soil, you kneel down and gather the weeds into a pile, "
            + "scooping them up into a basket.", "kneels down and gathers "
            + "the weeds into a pile and scoops them up into a basket.",
              "You continue to gather up the weeds from the different parts "
            + "of the garden.",
              "You complete gathering the loose weeds into your basket." }),
    "pruning" : ({ 15.0, "Taking the secateur, you look carefully at the bushes, "
            + "trees, and shrubs to identify branches and twigs that have "
            + "grown out of order. You begin pruning the bushes, trees, and "
            + "shrubs to help them grow in a more orderly fashion in this "
            + "part of the garden.", "starts pruning the bushes, shrubs, "
            + "and trees in this part of the garden.",
              "You have finished pruning away some of the more difficult "
            + "outgrowths and now begin to prune some of the more delicate "
            + "areas of the garden.",
              "You put the secateur away as you are satisfied that the "
            + "outgrowths have been sufficiently cared for." }),
    "gather branches" : ({ 10.0, "Taking your basket, you kneel down on the "
            + "ground and gather up the loose branches that have been pruned "
            + "away. You carefully break them into smaller sticks and place "
            + "them gingerly into the basket.",
              "gathers up the branches and breaks them down into smaller "
            + "sticks and places them in the basket.",
              "You finish gathering up the bigger branches and move onto "
            + "the smaller twigs that lie on the garden ground.",
              "You complete gathering the loose branches into your "
            + "basket." }),
    "water trees" : ({ 7.0, "You see that the trees, bushes, and shrubs are "
            + "a bit lacking in moisture. Taking your watering can, you "
            + "delicately pour just the right amount of moisture into the "
            + "ground.",
              "waters the trees, bushes, and shrubs.",
              "You see the moisture seeping into the ground as the soil "
            + "darkens.",
              "You finish watering the trees, bushes, and shrubs."  }),
    "water herbs" : ({ 6.0, "Some of the herbs look a bit dusty and dry. You "
            + "also notice that the furrows have not received all the moisture "
            + "to promote optimal growth. You take the watering can and pour "
            + "drops here and there to provide life-giving moisture where it "
            + "is needed.", "waters the "
            + "furrows and herbs.",
              "You are pleased to see the furrows taking the water "
            + "thirstily, and begin to work on moisturizing the "
            + "herbs with little applications of water.",
              "You finish watering the herbs and the furrows." })
]);
    
public void
create_paralyze()
{
    set_name("_elementalist_tend_paralyze_object");
    add_name( ({ "elementalist_tend_paralyze_object" }) );
    set_short("hidden tend paralyze object");
    set_long("This is the hidden tend paralyze object that is on a "
        + "person who is tending the garden.\n");
    set_fail_message("You are too busy tending the garden to do anything "
        + "else! You could always <stop tending> if you need to.\n");
    
    // Set up the abort stuff
    set_stop_verb("stop"); 
    set_stop_fun("stop_tending"); 
    set_stop_object(this_object());      
}

public string *
query_allowed_verbs()
{
    string * allow_verbs = ({ });

    allow_verbs += base_allow_verbs;
    allow_verbs += m_indices("/cmd/live/info"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/state"->query_cmdlist());
    
    return allow_verbs;
}

int
stop(string str)
{       
    // We want to allow some basic commands
    if (IN_ARRAY(query_verb(), query_allowed_verbs()))
    {
        return 0;
    }
    
    return ::stop(str);
}

public int
stop_tending(string str)
{
    if (!strlen(str) || (str != "tending" && str != "tend"))
    {
        // returning 1 ensures the paralyze stays.
        return 1;
    }
    
    object player = this_player();
    // Return 0 to remove the paralyze object
    write("You stop in the middle of tending the garden, leaving "
        + "the work for another time.\n");
    tell_room(environment(player), QCTNAME(player) + " stops tending "
        + "the garden.\n", ({ player }));
    return 0;
}

public object
get_environment_room()
{
    return environment(environment(this_object()));
}

public string
get_current_stage()
{
    int garden_health = get_environment_room()->query_garden_health() % 20;
    switch (garden_health)
    {
    case 0..4:
        return "loosening";
    
    case 5..6:
        return "gather weeds";
    
    case 7..12:
        return "pruning";
    
    case 13..14:
        return "gather branches";
    
    case 15..17:
        return "water trees";
    
    case 18..19:
        return "water herbs";
    }
    
    return 0;
}

public int
get_next_stage_health()
{
    int garden_health = environment(environment(this_object()))->query_garden_health();
    int stage_health = garden_health % 20;
    switch (stage_health)
    {
    case 0..4:
        return garden_health - stage_health + 6;
    
    case 5..6:
        return garden_health - stage_health + 12;
    
    case 7..12:
        return garden_health - stage_health + 14;
    
    case 13..14:
        return garden_health - stage_health + 17;
    
    case 15..17:
        return garden_health - stage_health + 19;
    
    case 18..19:
        return min(100, garden_health - stage_health + 24);
    }
    // should never get to the following line
    return garden_health;
}

public int
is_tool_ready_to_use(object tool)
{
    if (!objectp(tool))
    {
        return 0;
    }
    
    if (tool->id("_elementalist_garden_hoe"))
    {
        // check to make sure the hoe is sharp enough.
        if (tool->query_prop(OBJ_I_BROKEN) || (tool->query_dull() - tool->query_repair_dull()) > 3)
        {
            return 0;
        }
    }
    else if (tool->id("_elementalist_garden_secateur"))
    {
        // check to make sure the secateur is sharp enough.
        if (tool->query_prop(OBJ_I_BROKEN) || (tool->query_dull() - tool->query_repair_dull()) > 3)
        {
            return 0;
        }
    }
    else if (tool->id("watering can"))
    {
        // check to make sure that the watering can is full
        if (!tool->query_prop(OBJ_I_CONTAIN_WATER))
        {
            return 0;
        }
    }
    return 1;
}

public object *
get_candidate_tools()
{
    string toolname;
    object player = environment(this_object());
    string stage = get_current_stage();
    switch (stage)
    {
    case "loosening":
        toolname = "_elementalist_garden_hoe";
        break;
    
    case "gather weeds":
    case "gather branches":
        toolname = "_elementalist_garden_basket";
        break;
    
    case "pruning":
        toolname = "_elementalist_garden_secateur";
        break;
    
    case "water trees":
    case "water herbs":
        toolname = "watering can";
        break;
    }
    
    return filter(all_inventory(player), &->id(toolname));
}

public object
get_current_stage_tool()
{
    object * valid_tools = filter(get_candidate_tools(), is_tool_ready_to_use);
    if (!sizeof(valid_tools))
    {
        return 0;
    }
    
    // return the first valid tool
    return valid_tools[0];
}

public int
ready_for_current_stage()
{
    string stage = get_current_stage();
    object player = environment(this_object());
    object tool = get_current_stage_tool();
    int num_candidate_tools = sizeof(get_candidate_tools());
    switch (stage)
    {
    case "loosening":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("The garden's soil needs to be loosened and "
                + "weeds removed. You cannot do this without a gardening "
                + "hoe.\n");
            return 0;
        }
        else if (!objectp(tool))
        {
            player->catch_tell("You don't have any hoes that are sharp enough "
                + "to handle the loosening of the soil and weeds.\n");
            return 0;
        }
        break;
        
    case "gather weeds":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("The garden's path has a lot of weeds that "
                + "need to be gathered before you can continue to tend "
                + "the garden. You will need to obtain a basket to do "
                + "this.\n");
            return 0;
        }
        break;
    
    case "pruning":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("The garden's trees, bushes, and shrubs need "
                + "to be pruned. You need to have a pair of pruning shears, "
                + "also known as a secateur, in order to continue tending "
                + "the garden.\n");
            return 0;
        }
        else if (!objectp(tool))
        {
            player->catch_tell("You don't have any secateurs that are sharp enough "
                + "to cut through the branches and twigs on the trees, bushes, "
                + "and shrubs.\n");
            return 0;
        }            
        break;
    
    case "gather branches":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("Many branches remain on the ground that "
                + "need to be gathered up before one can continue to "
                + "tend the garden. You will need a basket to collect "
                + "the branches and sticks.\n");
            return 0;
        }
        break;
        
    case "water trees":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("The trees, bushes, and shrubs could use "
                + "a bit of watering. You cannot do this without a "
                + "filled watering can.\n");
            return 0;
        }
        else if (!objectp(tool))
        {
            player->catch_tell("The watering can you have doesn't contain "
                + "any water. You will need to fill it up before you can "
                + "tend the garden.\n");
            return 0;
        }        
        break;
    
    case "water herbs":
        if (num_candidate_tools == 0)
        {
            player->catch_tell("The herbs and furrows in the garden could use "
                + "a bit of watering. You cannot do this without a "
                + "filled watering can.\n");
            return 0;
        }
        else if (!objectp(tool))
        {
            player->catch_tell("The watering can you have doesn't contain "
                + "any water. You will need to fill it up before you can "
                + "tend the garden.\n");
            return 0;
        }
        break;
    }    
    
    return 1;
}

public void
update_tool_state_upon_completion()
{
    object tool = get_current_stage_tool();
    object player = environment(this_object());
    string stage = get_current_stage();
    switch (stage)
    {
    case "loosening":
    case "pruning":
        if (!random(10))
        {
            tool->set_dull(tool->query_dull() + 1);
        }
        break;
    
    case "water herbs":
        if (!random(5))
        {
            tool->remove_prop(OBJ_I_CONTAIN_WATER);
        }
        break;
    }    
}

public void
interim_tending_stage(string message)
{
    object player = environment(this_object());    
    player->catch_tell(message + "\n");
}

public void
ending_tending_stage(string message)
{
    object player = environment(this_object());    
    player->catch_tell(message + "\n");
}

public void
complete_tending_stage()
{
    object player = environment(this_object());

    // Update the tools depending on the stage
    update_tool_state_upon_completion();
    
    // Update the health to the next stage
    int next_health = get_next_stage_health();
    get_environment_room()->set_garden_health(next_health);
    ++num_cycles;
    if (next_health % 20 == 4 || next_health == 100)
    {
        // If we just tended the garden and got to the next
        // level, we just finish.
        player->catch_tell("You get off your knees and admire the work that "
            + "has been done in tending the garden.\n");   
        tell_room(environment(player), QCTNAME(player) + " gets off "
            + player->query_possessive() + " knees and admires the "
            + "result of tending the garden.\n",
            ({ player }));
        GUILD_MANAGER->add_guild_conduit(10); 
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
        
    set_alarm(0.0, 0.0, &display_tend_message());
}

public void
display_tend_message()
{
    object player = environment(this_object());
    if (!IS_PLAYER_OBJECT(player))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    object oldtp = this_player();
    set_this_player(player);
    if (ready_for_current_stage())
    {
        if (num_cycles == 0)
        {
            player->catch_tell("You begin to tend the garden.\n");
            tell_room(environment(player), QCTNAME(player) + " begins to "
                + "tend the garden.\n", ({ player }));
        }
        string stage = get_current_stage();
        mixed * current_stage_info = tend_messages[stage];
        float delay = current_stage_info[0] + itof(random(5)) - 2.0;
        string self_message = current_stage_info[1];
        string room_message = QCTNAME(player) + " " + current_stage_info[2];
        player->catch_tell("\n" + self_message + "\n\n");
        tell_room(environment(player), room_message + "\n", ({ player }));
        set_alarm(delay / 2.0, 0.0, &interim_tending_stage(current_stage_info[3]));
        set_alarm(delay - 1.0, 0.0, &ending_tending_stage(current_stage_info[4]));
        set_alarm(delay, 0.0, &complete_tending_stage());
    }
    else
    {
        if (num_cycles != 0)
        {
            player->catch_tell("You stop tending the garden.\n");
            tell_room(environment(player), QCTNAME(player) + " stops "
                + "tending the garden.\n", ({ player }));
        }
        set_alarm(0.0, 0.0, remove_object);
    }
    set_this_player(oldtp);
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (!IS_PLAYER_OBJECT(dest))
    {
        return;
    }
    
    set_alarm(0.0, 0.0, &display_tend_message());
}

