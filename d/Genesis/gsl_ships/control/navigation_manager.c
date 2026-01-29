/*
 * Navigation Manager
 *
 * This is used to access commonly used functions related to navigation.
 * It is a master object which should never be cloned.
 *
 * Code created by Tapakah, refactored by Petros
 */
#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <money.h>
#include <files.h>
#include "../navigation.h"
#include "../ships.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define NEWBIE_SHIP     "/d/Sparkle/area/sparkle/gsl_ships/newbie_ship.c"

// Global Variables
public string *     continent_names;

// Prototypes
public varargs object *    get_navigators          (int x, int y, object this_navigator = 0);
public varargs void        notify_navigators_at_xy (int x, int y, string message, object navigator = 0);
public string *            get_continent_by_xy     (int xcoord, int ycoord);
public string              get_domain_by_xy        (int xcoord, int ycoord);
public int                 route_has_point         (mixed *route, int xcoord, int ycoord);
public void                notify_port_arrival     (object ship, int pier_id);
public void                notify_port_departure   (object ship, int pier_id);

public void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function:    get_navigation_directions
 * Description: Given two locations, it returns the direction mapping for
 *              navigating from one to the other.
 */
public string *
get_navigation_directions (int * src_loc, int * dst_loc)
{
    int x_dist, y_dist;

    x_dist = src_loc[0] - dst_loc[0];
    y_dist = src_loc[1] - dst_loc[1];

    if(x_dist > 0)
    {
        if(y_dist > 0)
        {
            if(x_dist > y_dist*2)
            {
                return DIR_ESE;
            }
            else if(x_dist * 2 < y_dist)
            {
                return DIR_SSE;
            }
            else
            {
                return DIR_SE;
            }
        }
        else
        {
            if(x_dist > y_dist*2)
            {
                return DIR_ENE;
            }
            else if(x_dist * 2 < y_dist)
            {
                return DIR_NNE;
            }
            else
            {
                return DIR_NE;
            }
        }
    }
    else
    {
        if(y_dist > 0)
        {
            if(x_dist > y_dist*2)
            {
                return DIR_WSW;
            }
            else if(x_dist * 2 < y_dist)
            {
                return DIR_SSW;
            }
            else
            {
                return DIR_SW;
            }
        }
        else
        {
            if(x_dist > y_dist*2)
            {
                return DIR_WNW;
            }
            else if(x_dist * 2 < y_dist)
            {
                return DIR_NNW;
            }
            else
            {
                return DIR_NW;
            }
        }
    }
}

public mixed *
calculate_intermediate_stops (int *src_loc, int *dst_loc, int stops)
{
    int    x_dist_step, y_dist_step, s;
    mixed *intermediate_stops;

    x_dist_step = (dst_loc[0] - src_loc[0]) / (stops + 1);
    y_dist_step = (dst_loc[1] - src_loc[1]) / (stops + 1);

    intermediate_stops = ({ });
    for (int index = 0; index < stops; ++index)
    {
        intermediate_stops += ({ ({ src_loc[0] + x_dist_step * (index+1),
                                    src_loc[1] + y_dist_step * (index+1) }) });
    }
    
    return intermediate_stops;
}

public int *
get_harbor_entry (mapping h_exits, string *directions, string in_out)
{
    string * harbor_exit_directions;
    int n, n_mod, n_stop;

    harbor_exit_directions = m_indices(h_exits);
    if(in_out == "exit")
    {
        n = 0; n_mod =  1; n_stop =  8;
    }
    else
    {
        n = 7; n_mod = -1; n_stop = -1;
    }
    while(n != n_stop && !IN_ARRAY(directions[n], harbor_exit_directions))
    {
        n += n_mod;
    }

    if(n == n_stop)
    {
        return ({});
    }

    return h_exits[directions[n]];
}

varargs mixed *
get_direction (int *dest, int *src, int want_distance = 0)
{
    int x_dist, y_dist;
    float x_dist_f, y_dist_f;
    string direction;
    int distance;

    x_dist = dest[0] - src[0];
    y_dist = dest[1] - src[1];
    // wrap around the donut
    if (x_dist > X_OCEAN_SIZE / 2)
    {
        x_dist -= X_OCEAN_SIZE;
    }
    else if (x_dist < -X_OCEAN_SIZE / 2)
    {
        x_dist += X_OCEAN_SIZE;
    }
    if (y_dist > Y_OCEAN_SIZE / 2)
    {
        y_dist -= Y_OCEAN_SIZE;
    }
    else if (y_dist < -Y_OCEAN_SIZE / 2)
    {
        y_dist += Y_OCEAN_SIZE;
    }

    if (x_dist > 0)
    {
        if(x_dist > abs(y_dist) * 2)
        {
            direction = "east";
        }
        else if(x_dist * 2 < abs(y_dist))
        {
            direction = y_dist > 0 ? "south" : "north";
        }
        else
        {
            direction = y_dist > 0 ? "southeast" : "northeast";
        }
    }
    else
    {
        if(abs(x_dist) > abs(y_dist) * 2)
        {
            direction = "west";
        }
        else if(abs(x_dist) * 2 < abs(y_dist))
        {
            direction = y_dist > 0 ? "south" : "north";
        }
        else
        {
            direction = y_dist > 0 ? "southwest" : "northwest";
        }
    }
    if(want_distance)
    {
        x_dist_f = itof(x_dist);
        y_dist_f = itof(y_dist);
        return ({ sqrt(x_dist_f * x_dist_f + y_dist_f * y_dist_f), direction });
    }
    else
    {
        return ({ 0, direction });
    }
}

public mixed *
get_distance (int *point, int *rect)
{
    int x0, y0, x1, y1, x2, y2, x_dist, y_dist;

    x0 = point[0]; y0 = point[1];
    x1 = rect[0];  y1 = rect[2];
    x2 = rect[1];  y2 = rect[3];

    if (x0 > x1 && x0 < x2)
    {
        x_dist = 0;
        if (y0 > y1 && y0 < y2)
        {
            y_dist = 0;
        }
        else
        {
            y_dist = abs(y2-y0) > abs(y1-y0) ? (y1 - y0) : (y2 - y0);
        }
    }
    else
    {
        x_dist = abs(x2-x0) > abs(x1-x0) ? (x1 - x0) : (x2 - x0);
        if (y0 > y1 && y0 < y2)
        {
            y_dist = 0;
        }
        else
        {
            y_dist = abs(y2-y0) > abs(y1-y0) ? (y1 - y0) : (y2 - y0);
        }
    }
    return get_direction( ({ x0+x_dist, y0+y_dist }), point, 1);
}

public string
get_opposite_direction (string direction)
{
    return BASE_DIRECTIONS_AND_OPPOSITES[direction];
}

public varargs string
construct_lands_directions_desc (int x, int y, int max_distance = MAX_PEER_DISTANCE)
{
    string desc;
    string distance_desc;
    int *continent_coords, dist;
    mixed *distance;

    desc = "";
    foreach (string continent_name : continent_names)
    {
        continent_coords = CONTINENTS[continent_name][1..4];
        distance = get_distance( ({x, y}), continent_coords );
        dist = ftoi(distance[0]);
        if(dist < max_distance)
        {
            switch(dist)
            {
            case 0:
                distance_desc = "next to the ship";
                break;
            case 1..2:
                distance_desc = "nearby";
                break;
            case 3..5:
                distance_desc = "somewhere";
                break;
            default:
                distance_desc = "far away";
            }
            desc += "You see the shores of " + capitalize(continent_name) + " "
                + distance_desc + " in the " + distance[1] + "\n";
        }
    }
    return desc;
}

public void
place_object_in_sea (object navigator, int *coords)
{
    int x, y, ship_id;
    string direction_out;
    mixed *direction_in;
    int * current_location;
    
    x = coords[0];
    y = coords[1];

    if(x > X_OCEAN_SIZE || x < 0 || y > Y_OCEAN_SIZE || y < 0)
    {
        NF0("Invalid coordinates\n");
    }
    
    ship_id = navigator->get_ship_id();
    current_location = SHIP_MANAGER->get_ship_location(ship_id);
    direction_in = get_direction(current_location, ({x, y}));
    direction_out = get_opposite_direction(direction_in[1]);
    direction_in = " from the " + direction_in[1] + ".\n";
    direction_out = " to the " + direction_out + ".\n";
    notify_navigators_at_xy(current_location[0],
                            current_location[1],
                            navigator->query_mm_out()[..-3] + direction_out,
                            navigator);
    SHIP_DATABASE->set_ship_location(({ x, y }), ship_id);
    navigator->move(STDSEA);
    navigator->clear_continents_desc();
    notify_navigators_at_xy(x, y, navigator->query_mm_in()[..-3] + direction_in, 
                            navigator);
}

public varargs void
notify_navigators_at_xy (int x, int y, string message, object navigator = 0)
{
    object *navigators_here;

    navigators_here = get_navigators(x, y, navigator);
    navigators_here->relay_message(message);
}

public string
get_domain_by_xy (int xcoord, int ycoord)
{
    string * domain_data;

    domain_data = get_continent_by_xy(xcoord, ycoord);
    return sizeof(domain_data) ? domain_data[1] : "Genesis";
}

public string *
get_continent_by_xy (int xcoord, int ycoord)
{
    mixed * this_continent;
    foreach (string continent_name : continent_names) 
    {
        this_continent = CONTINENTS[continent_name];
        if (this_continent[1] <= xcoord 
            && this_continent[2] >= xcoord 
            && this_continent[3] <= ycoord 
            && this_continent[4] >= ycoord)
        {
            return ({ continent_name, this_continent[0] });
        }
    }
    
    return ({ });
}

varargs object *
get_navigators (int x, int y, object this_navigator = 0)
{
    object * navigators_here;
    mixed * rows;
    object ship;
    
    mixed * ship_ids = SHIP_DATABASE->query_ships_at_location(x, y);
    navigators_here = ({ });
    foreach (int ship_id : ship_ids)
    {
        mapping ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
        if (!mappingp(ship_row) || !objectp(ship = ship_row["instance"]))
        {
            continue;
        }
        if (!this_navigator || this_navigator != ship)
        {
            navigators_here += ({ ship });
        }
    }

    return navigators_here;
}


public int
route_has_point (mixed *route, int xcoord, int ycoord)
{
    foreach(int *point: route) 
    {        
        if (point[0] == xcoord && point[1] == ycoord)
        {
            return 1;
        }
    }
    return 0;
}

varargs string
examine_sea (object navigator, int distance_factor = 1)
{
    string desc, nav_desc, env_desc;
    int x, y, nh, num_nh, at_harbor, ship_id;
    mixed near_harbor;
    object *navigators_here, harbor_obj;
    mapping ship_row;
    
    desc = "\nYou peer outside the ship and you see water "
        + "all around you.";

    ship_id = navigator->get_ship_id();
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    x = ship_row["location"][0];
    y = ship_row["location"][1];

    navigators_here = get_navigators(x, y);
    navigators_here -= ({ navigator });
    num_nh = sizeof(navigators_here);
    near_harbor = navigator->query_is_near_harbor();
    if (strlen(near_harbor))
    {
        desc += "\nYou notice that you are in the vicinity of " 
            + near_harbor + ". ";
    }
    else if ((at_harbor = navigator->query_is_at_harbor()) != -1) 
    {
        mapping pier_row = PIER_DATABASE->query_row_by_id(at_harbor);
        harbor_obj = find_object(pier_row["filename"]);
        if (objectp(harbor_obj))
        {
            desc = "\nFrom the deck you can see out to the pier this "
                + "ship is currently docked at.\n\n";
            desc += harbor_obj->get_pier_description();
        }
    }
    desc += "\n";
    nav_desc = "";
    for(nh=0;nh<num_nh;nh++) 
    {
        if(nh)
          nav_desc = ", " + nav_desc;
        nav_desc += navigators_here[nh]->long();
    }
    if(nav_desc)
      desc += nav_desc;
    if(navigator->query_continents_desc() == "") 
    {
        env_desc = construct_lands_directions_desc(x, y, MAX_PEER_DISTANCE * distance_factor);
        navigator->set_continents_desc(env_desc);
    }
    desc += navigator->query_continents_desc();
    return desc;
}

public int
room_in_radius(int *src, int *dest, int max_radius)
{
    return 1;
}

public varargs void
arrive_into_harbor (object ship, int pier_id, string reason = "")
{
  int     ship_id, next_pier_id, route_length, ship_alarm;
    mapping pier, next_pier, ship_row;

    // First, we need to check whethre the ship has been paused
    // or stopped. We should not proceed if this is the case
    ship_id = ship->get_ship_id();
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (ship_row["enroute"] != 1)
    {
        return;
    }
    // We also need to check if there's a ship at the pier
    // Then, miss a beat, wait
    pier = PIER_DATABASE->query_row_by_id(pier_id);
    if(pier["filename"]->is_in_service()) {
      ship_alarm =
        ALARMS_MANAGER->set_place_regular_ship_in_sea_alarm(
          ship,
          ({SHIP_MANAGER->get_ship_location(ship_id)}),
          1,
          pier_id
        );
      SHIP_DATABASE->set_ship_alarm(ship_alarm, ship_id);
      return;
    }
    if(ship->query_is_at_harbor() == -1)
    {
        notify_port_arrival(ship, pier_id);
        ship->move(pier["filename"]);
        SHIP_DATABASE->set_ship_location(({ }) + pier["location"], ship_id);
        tell_room(pier["filename"], ship->query_mm_in());
    }

    ship_id = ship->get_ship_id();
    SHIP_MANAGER->set_ship_in_harbor(ship_id, pier_id);
    //  ship_time_counts[ship_id][data["ships"][ship_id]["current"]] = time();
    if(reason == "stop")
    {
        ship->unload_cargo();
        tell_room(pier["filename"], "The crew settles onboard the ship. It seems "
            + "it's going to stay here for a while.\n");
    }
    else if(reason == "disable")
    {
        ship->unload_cargo();
        tell_room(pier["filename"], "The ship leaves immediately for docks.\n");
    }
    else
    {
        next_pier = SHIP_DATABASE->query_next_pier(ship_id);
        ship->signal_arrival(pier["port"], next_pier["port"]);
    }
}

void
place_regular_ship_in_sea (object ship, mixed *route, int stop_n, int pier_id)
{
    int ship_alarm, j, s, ship_id;
    string route_show;
    mapping pier_row, ship_row;

    // First, we need to check whethre the ship has been paused
    // or stopped. We should not proceed if this is the case
    ship_id = ship->get_ship_id();
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (ship_row["enroute"] != 1)
    {
        return;
    }
        
    pier_row = PIER_DATABASE->query_row_by_id(pier_id);
    if(stop_n == sizeof(route))
    {
        send_debug_message("navigation_manager", "Arriving into harbor id "
            + pier_id);
        ship_alarm = ALARMS_MANAGER->set_arrive_into_harbor_alarm(ship, pier_id);
    }
    else
    {
        if (stop_n == sizeof(route) - 1 || stop_n == 0)
        {
            // Either the first or last point on the route
            ship->set_is_near_harbor(pier_row["port"]);
        }
        else
        {
            ship->set_is_near_harbor(0);
            ship->set_continents_desc();
        }
        place_object_in_sea(ship, route[stop_n]);
        ship_id = ship->get_ship_id();
        ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
        ship->signal_move();
        ship_alarm = ALARMS_MANAGER->set_place_regular_ship_in_sea_alarm(ship,
            route, stop_n + 1, pier_id);
    }
    SHIP_DATABASE->set_ship_alarm(ship_alarm, ship_id);
}

public int
has_active_alarm(int ship_id)
{
    mapping ship_row;
    
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(ship_row))
    {
        return 0;
    }
    
    if (ALARMS_MANAGER->retrieve_alarm(ship_row["alarm"]))
    {
        return 1;
    }
    return 0;
}

public mixed *
construct_navigation_route(int ship_id, int src_pier_id)
{
    mapping ship_row, src_pier, dest_pier;
    int    * src_location, * dest_location;
    mixed * entry1, * entry2;
    string * nav_directions;
    int pier_idx, next_idx;
    
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    src_pier = PIER_DATABASE->query_row_by_id(src_pier_id);
    pier_idx = member_array(src_pier["filename"], ship_row["piers"]); 
    if (!mappingp(ship_row) || !mappingp(src_pier) 
        || !sizeof(ship_row["piers"]) || pier_idx == -1)
    {
        return ({ });
    }
    next_idx = (pier_idx + 1) % sizeof(ship_row["piers"]);
    dest_pier = PIER_DATABASE->query_row_by_filename(ship_row["piers"][next_idx]);
    if (!mappingp(dest_pier))
    {
        return ({ });
    }
    src_location = src_pier["location"];
    dest_location = dest_pier["location"];

    // Stage 1 - exit from harbor
    nav_directions = get_navigation_directions(src_location, 
                                               dest_location);
    entry1 = get_harbor_entry(src_pier["directions"], nav_directions, 
                              "exit");
    entry2 = get_harbor_entry(dest_pier["directions"], nav_directions, 
                              "entry");
                              
    // Stage 2 - get the route
    mixed segment_route = ({ });
    if (pointerp(ship_row["points"])
        && pointerp(ship_row["points"][pier_idx]))
    {
        segment_route = ship_row["points"][pier_idx];
    }
    
    return ({}) + ({entry1}) +  segment_route + ({entry2});
}

public void
navigate_ship(object ship)
{
    mixed * route;
    mapping current_pier, next_pier;
    int ship_id;
    
    ship_id            = ship->get_ship_id();
    current_pier = SHIP_DATABASE->query_current_pier(ship_id);
    next_pier = SHIP_DATABASE->query_next_pier(ship_id);
    send_debug_message("navigation_manager", "Navigating ship from "
        + "pier " + current_pier["id"] + " to pier "
        + next_pier["id"]);
    
    ship->leave_harbor();
    notify_port_departure(ship, current_pier["id"]);
    route = construct_navigation_route(ship_id, current_pier["id"]);
    place_regular_ship_in_sea(ship, route, 0, next_pier["id"]);
}

public float
query_route_time(int ship_id, int src_pier_id)
{
    mapping ship_row, src_pier;
    mixed * route;
    
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    src_pier = PIER_DATABASE->query_row_by_id(src_pier_id);
    if (!mappingp(ship_row) || !mappingp(src_pier))
    {
        return 0;
    }
    
    route = construct_navigation_route(ship_id, src_pier_id);
    if (!sizeof(route))
    {
        return 0;
    }
    
    return itof(sizeof(route) + 1) * STOP_TIME_AT_SEA;
}


public float
query_wait_time(int ship_id, int pier_id)
{
    mapping ship_row, dest_pier, pier_row, current_pier;
    object ship, captain;
    int dest_idx, pier_idx;
    float route_time;
    mixed route;
       
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    dest_pier = PIER_DATABASE->query_row_by_id(pier_id);    
    if (!mappingp(ship_row) || !mappingp(dest_pier)
        || !SHIP_MANAGER->query_ship_is_running(ship_row)
        || !objectp(ship = ship_row["instance"])
        || ship->query_is_at_harbor() == pier_id)
    {
        return 0;
    }
    dest_idx = member_array(dest_pier["filename"], ship_row["piers"]);
    if (dest_idx == -1)
    {
        return 0;
    }
    
    route_time = 0.0;
    int numpiers = sizeof(ship_row["piers"]);
    for (int pier_idx = (ship_row["current"] + 1) % numpiers; pier_idx != dest_idx;
         pier_idx = (pier_idx + 1) % numpiers)
    {
        pier_row = PIER_DATABASE->query_row_by_filename(ship_row["piers"][pier_idx]);
        if (!mappingp(pier_row))
        {
            continue;
        }
        route_time += query_route_time(ship_id, pier_row["id"]) + STOP_TIME_AT_PORT;                      
    }
    
    current_pier = SHIP_DATABASE->query_current_pier(ship_id);
    if (ship->query_is_at_harbor() != -1
        && objectp(captain = ship->query_captain()))
    {
        float addition;
        if (floatp(addition = captain->query_time_until_departure()))
        {
            route_time += addition;
        }
        if (floatp(addition = query_route_time(ship_id, current_pier["id"])))
        {
            route_time += addition;
        }
    }
    else
    {
        route = construct_navigation_route(ship_id, current_pier["id"]);
        int route_length = sizeof(route);
        foreach (int * location : route)
        {
            --route_length;
            if (ship_row["location"][0] == location[0]
                && ship_row["location"][1] == location[1])
            {
                break;
            }
        }

        route_time += STOP_TIME_AT_SEA * itof(route_length);
        route_time += (ALARMS_MANAGER->retrieve_alarm(ship_row["alarm"]))[2];
    }
                
    return route_time;
}

public void
get_signal (object from, string signal) {

    if (objectp(from) && from->is_ship()) 
    {
        switch (signal) 
        {
        case "navigate":
            navigate_ship(from);
            break;
        }
    }
}

public string
get_ship_message_by_type (object ship, mixed *dist_dir, string message_type)
{
    string ship_desc;
    string message;
    string type_message;

    switch(message_type)
    {
    case "arrival":
        type_message = "approaching from the ";
        break;

    case "departure":
        type_message = "departing to the ";
        break;

    default:
        type_message = "passing by in the ";
    }

    ship_desc = LANG_ASHORT(ship);

    message = "You see " + ship_desc + " " 
        + (dist_dir[0] > 5.0 ? "from afar " : "") 
        + type_message + dist_dir[1] + ".\n";
    return message;
}

public void
notify_port_about_ship (int * rooms, object *ships, object ship, string message_type)
{
    string message;
    mixed  *ship_dist_dir;
    mapping pier;
    int * ship_location;
    object *silenced;

    /* Disabled for now */
    return;

    ship_location = SHIP_MANAGER->get_ship_location(ship->get_ship_id());
    foreach (int pier_id : rooms)
    {
        pier = PIER_DATABASE->query_row_by_id(pier_id);
        ship_dist_dir = get_direction(ship_location, pier["location"], 1);
        object pier_object = find_object(pier["filename"]);
	/* More than 2.0 distance ... no spam! /Mercade */
        if (!objectp(pier_object) || (ship_dist_dir[0] > 2.0))
        {
            continue;
        }
        silenced = pier_object->want_silence();
        message = get_ship_message_by_type(ship, ship_dist_dir, message_type);
        tell_room(pier_object, message, silenced);
    }
    
    foreach (object sh : ships)
    {
        ship_dist_dir = get_direction(ship_location,
            SHIP_MANAGER->get_ship_location(sh->get_ship_id()), 1);
        message = get_ship_message_by_type(ship, ship_dist_dir, message_type);
        sh->relay_message(message, 1, 1);
    }
}

/*
 * Function:    get_port_rooms
 * Description: Returns the piers that belong to this particular
 *              port. It can also use a max_radius around in case
 *              the port is particularly large
 * Returns:     array of row_ids to the piers
 */
public varargs int *
get_port_rooms(string port, int * src, int max_radius = 0)
{
    mixed * results;
    int * rooms;

    rooms = ({ });
    results = PIER_DATABASE->query_piers_in_port(port);
    foreach (mapping pier_row : results)
    {
        if (max_radius && !room_in_radius(src, pier_row["location"], max_radius))
        {
            continue;
        }
        rooms += ({ pier_row["id"] });
    }
    return rooms;
}

/*
 * Function:    get_ships_in_port
 * Description: Returns all the ships that are currently
 *              docked in the port specified
 */
public object *
get_ships_in_port(string port)
{
    mixed * piers_in_port, * all_ships;
    int * pier_ids;
    int * ship_ids = ({ });
    object * ships;
    object ship;
    
    piers_in_port = PIER_DATABASE->query_piers_in_port(port);
    pier_ids = ({ });
    foreach (mapping pier_row : piers_in_port)
    {
        mixed location = pier_row["location"];
        if (!pointerp(location) || sizeof(location) != 2)
        {
            continue;
        }
        ship_ids += SHIP_DATABASE->query_ships_at_location(location[0], location[1]);
    }
    
    ships = ({ });
    foreach (int ship_id : ship_ids)
    {
        mapping ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
        if (!mappingp(ship_row) || !objectp(ship = ship_row["instance"]))
        {
            continue;
        }
        ships += ({ ship });
    }
        
    return ships;
}

public void
notify_port_arrival(object ship, int pier_id)
{
    int * rooms;
    string port;
    object * ships;
    mapping pier_row;
    
    pier_row = PIER_DATABASE->query_row_by_id(pier_id);
    if (!mappingp(pier_row))
    {
        return;
    }
    port = pier_row["port"];
    rooms = get_port_rooms(port, pier_row["location"]);
    if(!sizeof(rooms))
    {
        return;
    }
    rooms -= ({ pier_id });
    ships = get_ships_in_port(port);
    ships -= ({ ship });
    notify_port_about_ship(rooms, ships, ship, "arrival");
}

public void
notify_port_departure (object ship, int pier_id)
{
    int *rooms;
    string port;
    object *ships;
    mapping pier_row;
    
    pier_row = PIER_DATABASE->query_row_by_id(pier_id);
    port = pier_row["port"];
    rooms = get_port_rooms(port, ({0,0}));
    rooms -= ({ pier_id });
    ships = get_ships_in_port(port);
    ships -= ({ ship });
    notify_port_about_ship(rooms, ships, ship, "departure");
}

public string
get_minimized_price(int cptotal)
{
    int * coins;
    string result;
    
    coins = MONEY_SPLIT(cptotal);
    result = "";
    if (!cptotal || !pointerp(coins))
    {
        return "" + cptotal + "cc";
    }
    
    if (coins[3])
    {
        result += "" + coins[3] + "pc ";
    }
    if (coins[2])
    {
        result += "" + coins[2] + "gc ";
    }
    if (coins[1])
    {
        result += "" + coins[1] + "sc ";
    }
    if (coins[0])
    {
        result += "" + coins[0] + "cc ";
    }
    
    return result;
}

public string
generate_timetable_for_port(string port_name, int exact)
{
    string * pierfiles, * port_piers;
    mixed * ships, * piers;
    string port_pier, price, line, state, time_wait, response;
    mapping current_pier, next_pier, next_pier_in_route;
    float wait_time;
    int ticket_price;
    object captain;
    
    piers = PIER_DATABASE->query_piers_in_port(port_name);
    response = "";
    pierfiles = ({ });
    foreach (mapping pier : piers)
    {
        pierfiles += ({ pier["filename"] });
    }
    ships = SHIP_DATABASE->query_rows( ([ ]) );
    foreach (mapping ship : ships)
    {
        string * pier_subset = ship["piers"] + ({ });
        pier_subset -= pierfiles;
        if (sizeof(pier_subset) == sizeof(ship["piers"]))
        {
            // If the sizes are the same, then this shipline
            // is not in this port
            continue;
        }
        port_piers = ({ }) + ship["piers"];
        port_piers -= pier_subset;
        port_pier = port_piers[0];
        mapping dest_pier = PIER_DATABASE->query_row_by_filename(port_pier);
        if(strlen(ship["ticket"]))
          ticket_price = ship["ticket"]->query_price();
        else
          ticket_price = 0;
        price = get_minimized_price(ticket_price);
        if (SHIP_MANAGER->query_ship_is_running(ship))
        {
            current_pier = SHIP_DATABASE->query_current_pier(ship["id"]);
            next_pier = SHIP_DATABASE->query_next_pier(ship["id"]);
            next_pier_in_route = PIER_MANAGER->query_next_pier_in_route(ship["id"], dest_pier["id"]);
            if (mappingp(next_pier_in_route))
            {
                line = next_pier_in_route["port"];
            }
            else
            {
                line = next_pier["port"];
            }
            if (ship["instance"]->query_is_at_harbor() != -1)
            {
                state = "Loading at " + current_pier["port"];  
            }
            else
            {
                state = "En route to " + next_pier["port"];
            }

            if (ship["instance"]->query_is_at_harbor() != -1
                && current_pier["port"] == port_name
                && objectp(captain = ship["instance"]->query_captain()))
            {
                wait_time = captain->query_time_until_departure();
                if (exact == 2)
                {
                    time_wait = "Departure in " 
                        + (wait_time ? ftoi(wait_time) : 0)
                        + " seconds.";
                }
                else if (exact == 1)
                {
                    time_wait = "Departure : ";
                    if (wait_time < (STOP_TIME_AT_PORT / 3.0))
                    {
                        time_wait += "Last Call";
                    }
                    else
                    {
                        time_wait += "First Call";
                    }
                }
            }
            else
            {
                wait_time = query_wait_time(ship["id"], dest_pier["id"]);
                if (exact == 2)
                {
                    time_wait = "Arrival in " 
                        + (wait_time ? ftoi(wait_time) : 0)
                        + " seconds.";
                }
                else if (exact == 1)
                {
                    time_wait = "Arrival : ";
                    if (wait_time > STOP_TIME_AT_PORT)
                    {
                        time_wait += "in a while";
                    }
                    else if (wait_time > STOP_TIME_AT_PORT / 3.0)
                    {
                        time_wait += "soon";
                    }
                    else
                    {
                        time_wait += "any moment";
                    }
                }                
            }            
        }
        else
        {
            continue;
        }
        
        if (objectp(ship["instance"])
            && IN_ARRAY(NEWBIE_SHIP, inherit_list(ship["instance"])))
        {
            line += " (N)";
        }
        
        if(exact)
        {
            response += sprintf("%-18s%-27s%-8s%-12s", line, state, 
                price, time_wait) + "\n";
        }
        else
        {
            response += sprintf("%-18s%-27s%-8s", line, state, price) + "\n";
        }
    }
    
    return response;
}

public string
generate_header_for_port(string port_name, int exact)
{
    string header;
    
    header = "|  Ships in the Port of " + port_name + "  |";
    header = sprintf("%|75s\n", 
                " ," + sprintf("%'-'" + (strlen(header) - 4) + "s", "") + ". ")
           + sprintf("%|75s\n", header)
           + sprintf("%|75s\n", 
                " `" + sprintf("%'-'" + (strlen(header) - 4) + "s", "") + "' ");
    if (exact)
    {
        header += sprintf("%-18s%-27s%-8s%-12s",
            "Destination", "Status", "Price", "Time") + "\n" 
          + sprintf("%'='75s\n", "");
    }
    else
    {
        header += sprintf("%-18s%-27s%-8s", 
            "Destination", "Status", "Price") + "\n"
          + sprintf("%'='75s\n", "");
    }
    
    return header;    
}

varargs string
query_timetable(string location, int exact = 0)
{    
    string * domain_list, * ports;
    string header, response, schedule;
    
    response = "";
    header = "Ships";        
    domain_list = map(SECURITY->query_domain_list(), lower_case);
    if (IN_ARRAY(lower_case(location), domain_list))
    {
        // The person is querying by the domain name. We want to
        // display all the schedules for each port separately
        ports = PIER_DATABASE->query_ports_for_domain(location);
        if (lower_case(location) == "sparkle")
        {
            string * genesis_ports = PIER_DATABASE->query_ports_for_domain("genesis");
            foreach (string genesis_port : genesis_ports)
            {
                if (!IN_ARRAY(genesis_port, ports))
                {
                    ports += ({ genesis_port });
                }
            }
        }
        foreach (string port_name : ports)
        {
            schedule = generate_timetable_for_port(port_name, exact);
            if (!strlen(schedule))
            {
                continue;
            }
            header = generate_header_for_port(port_name, exact);
            response += header + schedule + "\n";
        }
    }
    else
    {    
        // If it's not a domain, then it must be a port. 
        schedule = generate_timetable_for_port(location, exact);   
        if (strlen(schedule))
        {
            header = generate_header_for_port(location, exact);
            response += header + schedule + "\n";
        }
    }
    
    return "\n" + response;
}
