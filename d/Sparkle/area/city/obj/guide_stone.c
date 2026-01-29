/*
 * Standard Guide Stone
 *
 * One can simply set the destination(s) for the guide stone,
 * and it will guide whoever holds it towards that location.
 * It does this by using a series of shortest path calculations
 *
 * Created by Petros, June 2009
 */

#pragma strict_types
#include <macros.h>
#include <files.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/d/Sparkle/area/city/lib/pathfind";

// Global Variables
public mixed        destination;
public mixed        cached_path;
public int          alarm_id;
public object *     targets = ({ });

// Prototypes
public string       query_destination();
public void         set_destination(mixed dest);
public object *     query_targets();
public object *     query_target_destinations();
public void         add_target(mixed target);
public void         remove_target(mixed target);


public void
create_object()
{
    set_name("stone");
    add_adj("round");
    add_adj("rune-covered");
    set_long("@@describe_long@@");

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_target("/d/Sparkle/area/sparkle/room/town/newbie-pier_1");
    set_destination("/d/Sparkle/area/sparkle/room/town/newbie-pier_1");
}

public string
convert_domain_name(string domain)
{
    // Special cases for domains that are essentially the same, but
    // have different names
    switch (domain)
    {
    case "Genesis":
        domain = "Sparkle";
        break;
    
    case "Ansalon":
        domain = "Krynn";
        break;
    
    case "Gondor":
        domain = "Shire";
        break;
    
    case "Raumdor":
        domain = "Kalad";
        break;
    }
    
    return domain;
}

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int 
is_valid_room(string str)
{
    object destination_room, current_room;
    string current_domain, destination_domain;
    
    if (!objectp(current_room = safely_load_master_file(str))
        || !objectp(destination_room = safely_load_master_file(query_destination()))
        || !IS_ROOM_OBJECT(current_room)
        || !IS_ROOM_OBJECT(destination_room))
    {
        return 0;
    }    

    // For whatever reason, Gondor actually links their workroom to actual
    // rooms in the game. This causes the pathfind to lead players to
    // rooms paths that shouldn't be possible.
    if (wildmatch("/d/Gondor/workroom*", str))
    {
        return 0;
    }
    
    current_domain = convert_domain_name(current_room->query_domain());
    destination_domain = convert_domain_name(destination_room->query_domain());
        
    if (current_domain == destination_domain)
    {
        return 1;
    }
    
    return 0;
}

public void
set_destination(mixed dest)
{
    destination = dest;
}

/*
 * Function:    query_destination
 * Description: Returns the filename of the room that holds the destination.
 *              The "destination" variable can contain either a room or
 *              an object that is being tracked. We parse this in this
 *              function and return the room so that the pathfind can
 *              work properly.
 */
public string
query_destination()
{
    object room;
    if (objectp(destination))
    {
        while (objectp(room = environment(destination)))
        {
            if (IS_ROOM_OBJECT(room))
            {
                break;
            }
        }
    }
    else if (stringp(destination))
    {
        room = find_object(destination);
    }
    
    if (objectp(room) && IS_ROOM_OBJECT(room))
    {
        return MASTER_OB(room);
    }
    return 0;
}

public string
retrieve_route_to_destination()
{
    string current_room, destination_room;
    mixed route;
       
    current_room = MASTER_OB(environment(this_player()));
    
    // We check if the current path already contains the route.
    int path_index;
    if (sizeof(cached_path)
        && (path_index = member_array(current_room, cached_path)) >= 0
        && IN_ARRAY(destination_room, cached_path))
    {
        route = cached_path[(path_index - 1)..];
    }
    else
    {
        catch(route = find_path(current_room, query_destination()));
        cached_path = route;
    }
    
    if (sizeof(route))
    {
        return route;
    }
    
    return 0;
}

public void
hook_route_not_found(object player)
{
    player->catch_tell("The " + short() + " remains completely "
        + "still as you stare at it. You wonder why it is not responding to "
        + "your attention.\n");
}

public void
hook_display_next_direction(object player, string next_dir)
{
    player->catch_tell("The light from the runes on the " + short() 
        + " bursts brightly for a moment and you suddenly sense the "
        + short() + " urging you to go " 
        + next_dir + ".\n");
}

public void
hook_invalid_route(object player)
{
    player->catch_tell("The light from the runes wink out and you "
        + "don't sense anything useful from the " + short() + ".\n");
}

public void
hook_destination_reached(object player)
{
    player->catch_tell("The " + short() + " is vibrating excitedly and "
        + "you sense that it believes it belongs where you stand.\n");
}

public void
describe_route(object player)
{
    mixed route = retrieve_route_to_destination();
    if (!sizeof(route))
    {
        hook_route_not_found(player);
        return;
    }
        
    string next_dir = route[0];    
    if (strlen(next_dir))
    {
        hook_display_next_direction(player, next_dir);
    }
    else
    {
        hook_invalid_route(player);
    }
}

public void
hook_activate_what()
{
    notify_fail("Activate what?\n");
}

public void
hook_activate_no_destination()
{
    write("You activate the runes on the " + short() + " but it remains "
        + "completely still.\n");
}

public void
hook_activate_waiting()
{
    write("You activate the " + short() + " and the runes on it begin "
        + "to glow. The entire object gets very warm. You wait "
        + "expectantly...\n");
}

public int
activate_stone(string str)
{
    hook_activate_what();
    if (!strlen(str))
    {
        return 0;
    }
    
    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (target != this_object())
    {
        return 0;
    }
    
    remove_alarm(alarm_id);
    
    string current_destination = query_destination();
    if (!strlen(current_destination))
    {
        hook_activate_no_destination();
        return 1;
    }
    
    if (current_destination == MASTER_OB(environment(this_player())))
    {
        hook_destination_reached(this_player());
        return 1;
    }

    // We add an alarm so that players don't script it too easily.
    alarm_id = set_alarm(1.0, 0.0, &describe_route(this_player()));
    hook_activate_waiting();
    
    return 1; 
}

/*
 * Function:    add_target
 * Description: A stone can hold multiple targets at once. A person who
 *              uses the stone can then <choose> or select another target
 *              that they would like. This function is called to add
 *              a new target to the stone's list of available targets.
 */
public void         
add_target(mixed target)
{
    if (objectp(target))
    {
        targets += ({ target });
    }
    else if (stringp(target))
    {
        target = safely_load_master_file(target);
        targets += ({ target });
    }
    targets -= ({ 0 });
}

/*
 * Function:    remove_target
 * Description: A stone can hold multiple targets at once. A person who
 *              uses the stone can then <choose> or select another target
 *              that they would like. This function is called to remove
 *              a target from the stone's list of available targets.
 */
public void
remove_target(mixed target)
{
    if (objectp(target))
    {
        targets -= ({ target });
    }
    else if (stringp(target))
    {
        target = safely_load_master_file(target);
        targets -= ({ target });
    }
    targets -= ({ 0 });    
}

/*
 * Function:    remove_target
 * Description: A stone can hold multiple targets at once. A person who
 *              uses the stone can then <choose> or select another target
 *              that they would like. This function is called to remove
 *              all targets from the stone's list of available targets.
 */
public void
clear_targets()
{
    targets = ({ });
}

/*
 * Function:    find_surrounding_room
 * Description: This function returns the room that surrounds the object.
 */
public object
find_surrounding_room(object target)
{
    if (IS_ROOM_OBJECT(target))
    {
        return target;
    }

    object surrounding_room = environment(target);
    while (objectp(surrounding_room) && !IS_ROOM_OBJECT(surrounding_room))
    {
        surrounding_room = environment(surrounding_room);
    }
    
    return surrounding_room;
}

/*
 * Function:    query_targets
 * Description: A stone can hold multiple targets at once. A person who
 *              uses the stone can then <choose> or select another target
 *              that they would like. This function is called to retrieve
 *              the full list of available targets.
 */
public object *
query_targets()
{
    targets -= ({ 0 });
    object * valid_targets = ({ });
    foreach (object target : targets)
    {
        if (!objectp(target))
        {
            continue;
        }
        
        valid_targets += ({ target });
    }
    
    targets = valid_targets;
    return valid_targets;
}

/*
 * Function:    query_target_destinations
 * Description: The pathfind can only work with rooms. So given a list of
 *              valid objects, this functions translates this to a list of rooms 
 *              that can then be used by the pathfind algorithm.
 */
public object *
query_target_destinations()
{
    object * valid_targets = query_targets();
    object * target_destinations = ({ });
    foreach (object target : targets)
    {
        object surrounding_room = find_surrounding_room(target);
        // We purposefully add even invalid objects because the index for choosing
        // the target needs to be the same as what is available from this function.
        // ie. The array from query_targets needs to be the same size as the array
        // returned by this function.
        target_destinations += ({ surrounding_room });
    }
    return target_destinations;
}

public void
hook_choose_target_success()
{
    write("The " + short() + " hums and you see the runes rearrange "
        + "themselves magically. You sense that it's been retuned "
        + "to find the destination that you chose.\n");
}

public void
hook_choose_target_already_chosen()
{
    write("The " + short() + " is already tuned to that destination!\n");
}

/*
 * Function:    choose_target
 * Description: This allows a player to choose which target they want
 *              to go to.
 */
public int
choose_target(string str)
{
    int index;
    object * valid_targets = query_target_destinations();
    if (!strlen(str)
        || !sscanf(str, "%d", index)
        || index < 1
        || index > sizeof(valid_targets))
    {
        notify_fail("Choose which destination? Select a proper number.\n");
        return 0;
    }
    
    if (valid_targets[index - 1] == destination)
    {
        hook_choose_target_already_chosen();
        return 1;
    }
    
    set_destination(MASTER_OB(valid_targets[index - 1]));
    hook_choose_target_success();
    return 1;    
}

/* 
 * Function:    in_same_area
 * Description: Checks to see if the current room is in the same area
 *              as the destination room.
 */
public int
in_same_area(object destination_room)
{
    if (!objectp(destination_room)
        || !IS_ROOM_OBJECT(destination_room))
    {
        return 0;
    }    
    string * general_areas = ({
        "/d/Ansalon/balifor/flotsam/",
        "/d/Ansalon/balifor/flotsam_forest/",
        "/d/Ansalon/balifor/port_balifor/",
        "/d/Ansalon/balifor/steppe/",
        "/d/Ansalon/estwilde/iron_delving/",
        "/d/Ansalon/estwilde/plains/",
        "/d/Ansalon/goodlund/bloodsea/",
        "/d/Ansalon/goodlund/kendermore/",
        "/d/Ansalon/goodlund/nethosak/",
        "/d/Ansalon/silvanesti/kurinost/",
        "/d/Ansalon/taman_busuk/mountains/",
        "/d/Ansalon/taman_busuk/neraka/",
        "/d/Ansalon/taman_busuk/sanction/",
        "/d/Avenir/common/bazaar/",
        "/d/Avenir/common/city/",
        "/d/Avenir/common/dark/",
        "/d/Avenir/common/holm/",
        "/d/Avenir/common/outpost/",
        "/d/Avenir/common/park/",
        "/d/Avenir/common/port/",
        "/d/Avenir/common/village/",
        "/d/Avenir/union/room/",
        "/d/Calia/argos/dephtemp/",
        "/d/Calia/argos/krcamp/",
        "/d/Calia/argos/metro/",
        "/d/Calia/argos/nwterr/",
        "/d/Calia/argos/silent_forest/",
        "/d/Calia/argos/swterr/",
        "/d/Calia/sea/thalassia/",
        "/d/Cirath/ridge/desert/",
        "/d/Earthsea/gont/beach/",
        "/d/Earthsea/gont/gont_city/",
        "/d/Earthsea/gont/tenalders/",
        "/d/Earthsea/roke/thwil/",
        "/d/Emerald/blackwall/delrimmon/",
        "/d/Emerald/north_shore/outpost/",
        "/d/Faerun/swordcoast/waterdeep/",
        "/d/Genesis/ateam/aoe/museum/",
        "/d/Gondor/anorien/druedain/",
        "/d/Gondor/ithilien/poros/",
        "/d/Gondor/ithilien/road/",
        "/d/Gondor/morgul/city/",
        "/d/Kalad/common/caravan/",
        "/d/Kalad/common/central/",
        "/d/Kalad/common/noble/",
        "/d/Kalad/common/port/",
        "/d/Kalad/common/raum/",
        "/d/Kalad/common/trade/",
        "/d/Kalad/common/wild/",
        "/d/Khalakhor/inisi/roke/",
        "/d/Khalakhor/se_speir/lohrayn/ashlagh/",
        "/d/Khalakhor/se_speir/plains/",
        "/d/Khalakhor/se_speir/port/",
        "/d/Khalakhor/se_speir/claryn/tabor/",
        "/d/Krynn/que/plains/",
        "/d/Krynn/solamn/palan/",
        "/d/Shire/common/trollsh/",
        "/d/Genesis/start/dwarf/",
        "/d/Genesis/start/elf/",
        "/d/Genesis/start/hobbit/",
        "/d/Genesis/start/human/town/",
        "/d/Genesis/start/human/wild2/",
        "/d/Terel/common/town/mansion/",
    });
    object current_room = environment(this_player());
    string current_file, destination_file;
    current_file = MASTER_OB(current_room);
    destination_file = MASTER_OB(destination_room);
    
    foreach (string area : general_areas)
    {
        int bMatchCurrent = wildmatch(area + "*", current_file);
        int bMatchDestination = wildmatch(area + "*", destination_file);
        if (!bMatchCurrent && !bMatchDestination)
        {
            // In case neither matches, we look for the next one
            continue;
        }
        
        if (bMatchCurrent && bMatchDestination)
        {
            // If both match, we have a winner!
            return 1;
        }
        else
        {
            // If only one matches but not the other, we count it
            // as not a match.
            return 0;
        }
    }
    // If not matched any of the areas, we just check for
    // for the first three components.
    string current_prefix = implode(explode(current_file, "/")[..3], "/");
    string destination_prefix = implode(explode(destination_file, "/")[..3], "/");
    if (current_prefix == destination_prefix)
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function:    in_same_domain
 * Description: Checks to see if the current room is in the same domain as the
 *              destination room.
 */
public int
in_same_domain(object destination_room)
{
    if (!objectp(destination_room)
        || !IS_ROOM_OBJECT(destination_room))
    {
        return 0;
    }    
    object current_room = environment(this_player());

    string current_domain, destination_domain;
    current_domain = convert_domain_name(current_room->query_domain());
    destination_domain = convert_domain_name(destination_room->query_domain());
        
    if (current_domain == destination_domain)
    {
        return 1;
    }
    
    return 0;    
}

/* 
 * Function:    discard_stone
 * Description: allows someone to discard this particular stone.
 */
public int
discard_stone(string str)
{
    notify_fail("What do you wish to discard?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    object target = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(target)
        || target != this_object())
    {
        return 0;
    }
    
    write("You discard the " + short() + " and it turns to dust.\n");
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public void
init()
{
    ::init();
    add_action("activate_stone", "activate");
    add_action("choose_target", "choose");  
    add_action("discard_stone", "discard");
}

public string
describe_long()
{
    string description = "You hold in your hand a " + short() + ". The runes are carved or "
        + "burnt into its surface, and take up a majority of the surface "
        + "area of the object. You have heard legends of objects like this "
        + "that have the power to guide adventurers to certain locations. "
        + "You could try to <activate> the " + short() + " and see if it "
        + "responds to you.\n"
        + "\n";
    // Describe the targets that are still available.
    object * valid_targets = query_targets();
    if (!sizeof(valid_targets))
    {
        description += "The " + short() + " doesn't currently "
            + "contain any destination information.\n";
        return description;
    }
    
    description += "These are the objects that your " + short()
        + " has been tuned to:\n";
    // We tell the players how many targets they can reach    
    for (int index = 0; index < sizeof(valid_targets); ++index)    
    {
        object target = find_surrounding_room(valid_targets[index]);
        string strSameDomain = "";
        if (in_same_domain(target))
        {
            strSameDomain = "*";
            if (in_same_area(target))
            {
                strSameDomain += "*";
            }
        }
        if (destination == MASTER_OB(target))
        {
            description += sprintf("--> %3d. %s %s\n", 
                (index + 1), capitalize(target->short()), strSameDomain);            
        }
        else
        {
            description += sprintf("    %3d. %s %s\n", 
                (index + 1), capitalize(target->short()), strSameDomain);
        }
    }
    
    description += "Legend:\n";
    description += "  *   indicates the object is in the domain you stand "
        + "\n";
    description += "  **  indicates that the object in the same area you "
        + "stand\n";
    description += "  --> indicates the currently selected target.\n";
    description += "\n" + "You can <choose> the number of the object "
        + "you wish to locate.\n";
    return description;
}

