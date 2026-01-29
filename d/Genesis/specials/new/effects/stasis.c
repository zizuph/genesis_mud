inherit "/std/room";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>

// Definitions
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

// Variables
static mapping  locations   = ([
    "Icewall":({ -168.0,8.0,"Icewall Glacier", "/d/Krynn/icewall/plains/fishing/fishing_2"}),
    "Mithas":({-170.0,10.0,"the island of Mithas","/d/Ansalon/goodlund/nethosak/forest/room/swamp1"}),
]);
static mapping  stasis      = ([]);
static status   split_group = 0;
static float    interval    = 5.0;              // Interval for moving coords
static float    movement    = interval * 5.0;   // KM / RL (interval) sec
static float    radius      = 6371.0;           // The radius of the earth

// Prototypes
static nomask varargs   status move_actor_to_origin(object *actors, object origin);
public nomask status    move_actor_to_stasis(object *actors, object origin, object location);
static nomask status    dismantle_instance(object origin);
static nomask status    viable_origin(object *actors, object origin);
static nomask status    viable_location(object *actors, object location);
static nomask status    move_actor_to_location(object *actors, object origin, object location);
static nomask string    query_room_domain(object room);
static nomask float     rad2deg(float degree);
static nomask float     deg2rad(float radian);
static nomask float     haversine_distance(...);
static nomask float *   intermediate_distance(...);
static nomask float     distance_km(...);
static nomask int       degree_direction(...);
static nomask string    cardinal_direction(...);
static nomask float *   coords_from_room(object room);
static nomask void      move_coords(object *actors);
static nomask status    update_transport_location(object *actors, object origin, object location);

public void
hook_location_changed(object *actors, object old_loc, object new_loc)
{
}

public void
hook_coords_moved(object *actors, float *old, float *new)
{
    actors->catch_msg("You travel " + applyv(cardinal_direction, old + new) + ".\n");
}

public void
hook_moved_to_location(object *actors, object origin, object location)
{
    tell_room(location, COMPOSITE_LIVE(actors) + " arrives through a rift in "
    + "the void.\n", actors, actors[0]);
}

public void
hook_moved_to_stasis(object *actors, object origin, object location)
{
    tell_room(origin, COMPOSITE_LIVE(actors) + " leaves through a rift in "
    + "the void.\n", actors, actors[0]);
}

public void
hook_moved_to_origin(object *actors, object origin)
{
    tell_room(origin, COMPOSITE_LIVE(actors) + " arrives through a rift in "
    + "the void.\n", actors, actors[0]);
}

public void
hook_no_transport_locations(object actor)
{
    actor->catch_msg("You would not even know where to begin your journey.\n");
}

public void
hook_transport_location_not_found(object actor, string str, string *list)
{
    actor->catch_msg("Where is " + str + "? The locations you know only "
    + "extend to " + COMPOSITE_WORDS(list) + "\n");
}

public void
hook_non_viable_location(object *actors, object location)
{
    actors->catch_msg("You seem unable to travel there.\n");
}

public void
hook_non_viable_origin(object *actors, object origin)
{
    actors->catch_msg("You seem unable to travel from here.\n");
}

public void
hook_non_movable_actor(object *actors, object origin, object location)
{
    object *travel = FILTER_LIVE(actors - ({ 0 }));
    object *missing = filter(travel, &operator(!=)(,location) @ &environment());
    if (sizeof(missing))
    {
        travel -= missing;
        missing->catch_msg("Something prevented you from travelling to the "
        + "desired location.\n");
        travel->catch_msg("Something prevented " + COMPOSITE_LIVE(missing)
        + " from travelling to the desired location.\n");
    } else
        actors->catch_msg("Something went horribly wrong.\n");
}

public void
set_stasis_split_group(status split)
{
    split_group = split;
}

public status
query_stasis_split_group()
{
    return split_group;
}

public void
create_stasis_room()
{
    set_short("An endless void");
    set_long("You are traversing an endless void.\n");
    
    add_item(({"endless void", "void"}),
        "This is a seemingly endless void.\n");
}

public varargs nomask string
short(object for_obj)
{
    string desc = "";
    object *destinations;
    destinations = ({ query_room_domain(stasis["location"]) }) - ({ "", 0 });
    
    if (sizeof(destinations))
        desc += " - bound for " + COMPOSITE_WORDS(destinations);
    
    return ::short(for_obj) + desc;
}

public nomask void
create_room()
{
    set_stasis_split_group(0);
    create_stasis_room();
    
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(OBJ_I_NO_MAGIC, 1);
    
    remove_prop(CONT_I_VOLUME);
    remove_prop(CONT_I_MAX_VOLUME);
    remove_prop(CONT_I_WEIGHT);
    remove_prop(CONT_I_TRANSP);
    remove_prop(CONT_I_MAX_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    
    setuid();
    seteuid(getuid());
}

/********************** Coordinates **********************/
static nomask float rad2deg(float degree)
{
    return degree * 57.29577951;
}
 
static nomask float deg2rad(float radian)
{
    return radian * 0.01745329252;
}

static nomask float haversine_distance(...)
{
    float *coord = map(argv, &deg2rad());
    // haversine formula
    float dlat = coord[2] - coord[0];
    float dlon = coord[3] - coord[1];
    float ans = pow(sin(dlat / 2.0), 2.0) +
                pow(sin(dlon / 2.0), 2.0) *
                cos(coord[0]) * cos(coord[2]);
    return 2.0 * asin(sqrt(ans));
}
 
static nomask float * intermediate_distance(...)
{
    float a, b, d, f, x, y, z, lat, lon;
    float *coord = map(argv, &deg2rad());
    d = applyv(haversine_distance, argv);
    f = min(1.0, max(0.0, movement / (d * radius)));
    a = sin((1.0 - f) * d) / sin(d);
    b = sin(f * d) / sin(d);
    x = a * cos(coord[0]) * cos(coord[1]) +
        b * cos(coord[2]) * cos(coord[3]);
    y = a * cos(coord[0]) * sin(coord[1]) +
        b * cos(coord[2]) * sin(coord[3]);
    z = a * sin(coord[0]) + b * sin(coord[2]);
    lat = atan2(z, sqrt(pow(x, 2.0) + pow(y, 2.0)));
    lon = atan2(y, x);
 
    return map(({ lat, lon }), &rad2deg());
}
 
static nomask float distance_km(...)
{
    return applyv(haversine_distance, argv) * radius;
}
 
static nomask int degree_direction(...)
{
    float *coord = map(argv, &deg2rad());
    float dlon = coord[3] - coord[1];
    float y = sin(dlon) * cos(coord[2]);
    float x = cos(coord[0]) * sin(coord[2]) -
              sin(coord[0]) * cos(coord[2]) * cos(dlon);
    return ftoi(rad2deg(atan2(y, x)) + 360.0) % 360;
}
 
static nomask string cardinal_direction(...)
{
    string *cardinal = ({
        "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest", "north"
    });
   
    // Correct by 22.5 degrees, or 23 in integer value
    int direction = applyv(degree_direction, argv) - 23;
    if (direction < 0)
        direction += 360;
   
    return "" + cardinal[direction / 45];
}

static float *
domain_centre(object room)
{
    string dname = query_room_domain(room);
    float *centre = ({});
    
    switch(dname)
    {
        case "Ansalon":
        case "Krynn":
            centre = ({ -172.0, 0.5 });
            break;
        default:
            centre = ({ 0.0, 0.0 });
            break;
    }
    
    return centre;
}

static nomask float *
coords_from_room(object room)
{
    string name = MASTER_OB(room);
    mixed *list = m_values(locations);
    int size = sizeof(list);
    while(--size)
    {
        if (sizeof(({ name }) & list[size]))
            return ({ list[size][0], list[size][1] }); 
    }
    
    return domain_centre(room);
}

static nomask void
move_coords(object *actors)
{
    float *new, *old, *end;
    new = applyv(intermediate_distance, stasis["coords"]);
    old = stasis["coords"][0..1];
    end = stasis["coords"][2..3];
    
    stasis["history"] += ({ old });
    stasis["coords"] = new + end;
    hook_coords_moved(actors, old, new);
}

/*********************************************************/

static nomask status
all_moved(object *live, object destination)
{
    live = FILTER_LIVE(live - ({ 0 }));
    if (!objectp(destination) || !sizeof(live))
        return 0;
    
    int *moved = map(live, &->move_living("M", destination, 1, 0));
    return reduce(&operator(+)(,), moved) == 0;
}

static nomask status
viable_origin(object *actors, object origin)
{
    if (origin->query_prop(ROOM_M_NO_TELEPORT_FROM) ||
        origin->query_prop(ROOM_M_NO_TELEPORT) ||
        origin->query_prop(OBJ_I_NO_MAGIC))
        return 0;

    int *combat = map(actors, &->query_relaxed_from_combat());
    if (reduce(&operator(+)(,), combat) < sizeof(actors))
        return 0;
    
    return 1;
}

static nomask status
viable_location(object *actors, object location)
{
    if (!objectp(location))
        return 0;
    
    if (location->query_prop(ROOM_M_NO_TELEPORT_TO) ||
        location->query_prop(ROOM_M_NO_TELEPORT) ||
        location->query_prop(OBJ_I_NO_MAGIC))
        return 0;
        
    // Check for guilds?

    return 1;
}

static nomask status
dismantle_instance(object origin)
{
    set_alarm(0.5, 0.0, remove_object);

    object *live = FILTER_LIVE(all_inventory());
    if (sizeof(live))
        move_actor_to_origin(live, origin);
    
    if (member_array("actors", m_indexes(stasis)) < 0)
        stasis["actors"] = ({});
    
    stasis["actors"] -= ({ 0 });
    foreach(object ob: stasis["actors"])
    {
        // Linkdead people get their LD room changed when instance vanishes
        if (ob->query_linkdead())
        {
            object linkdead_origin = origin;
            
            if (objectp(stasis["origin"]))
                linkdead_origin = stasis["origin"];
            
            if (ob->query_prop(PLAYER_S_LD_IN_ROOM) == file_name(this_object()))
                ob->add_prop(PLAYER_S_LD_IN_ROOM, 
                (objectp(linkdead_origin) ? file_name(linkdead_origin) : 0));
        }
        
        remove_alarm(stasis["alarm"]);
        m_delkey(stasis, ob);
    }
    
    return 0;
}

static nomask status
move_actor_to_location(object *actors, object origin, object location)
{
    actors = filter(actors, &operator(==)(this_object()) @ &environment());
    
    if (!viable_location(actors, location))
    {
        hook_non_viable_location(actors, location);
        move_actor_to_origin(actors, origin);
        return dismantle_instance(origin);
    }
    
    if (!all_moved(actors, location))
    {
        hook_non_movable_actor(actors, origin, location);
        
        if (!query_stasis_split_group())
            move_actor_to_origin(actors, origin);
        
        return dismantle_instance(origin);
    }
    
    hook_moved_to_location(actors, origin, location);
    return !dismantle_instance(origin);
}

static nomask varargs status
move_actor_to_origin(object *actors, object origin)
{
    object *moved = ({});
    
    actors = FILTER_LIVE(actors - ({ 0 }));
    
    if (!sizeof(actors))
        return 0;
    
    for(int i = 0; i < sizeof(actors); i++)
    {
        object actor = actors[i], tmp_origin = origin;
        
        if (objectp(stasis["origin"]))
            tmp_origin = stasis["origin"];
        
        if (!objectp(tmp_origin))
        {
            if (!objectp(actor->query_default_start_location()))
                continue;
            
            tmp_origin = actor->query_default_start_location();
        }
        
        if (all_moved(({ actor }), tmp_origin))
            moved += ({ actor });
    }
    
    hook_moved_to_origin(moved, origin);
    return sizeof(moved) == sizeof(actors);
}

static nomask status
update_transport_location(object *actors, object origin, object location)
{
    stasis["actors"] |= actors;
    if (stasis["location"] != location)
    {
        // Location changed
        if (objectp(stasis["location"]))
            hook_location_changed(actors, stasis["location"], location);
        
        if (!sizeof(stasis["coords"]))
            stasis["coords"] = coords_from_room(origin) +
                               coords_from_room(location);
        
        remove_alarm(stasis["alarm"]);
        stasis["location"] = location;
        stasis["origin"] = origin;
        stasis["alarm"] = set_alarm(0.0, interval, &move_coords(actors));
        
        return 1;
    }
    
    return 0;
}

public nomask status
move_actor_to_stasis(object *actors, object origin, object location)
{
    if (!IS_CLONE)
    {
        object instance = clone_object(MASTER);
        return instance->move_actor_to_stasis(actors, origin, location);
    }
    
    if (!viable_origin(actors, origin))
    {
        hook_non_viable_origin(actors, origin);
        return dismantle_instance(origin);
    }
    
    if (!all_moved(actors, this_object()))
    {
        hook_non_movable_actor(actors, origin, location);
    
        if (!query_stasis_split_group())
            move_actor_to_origin(actors, origin);
        
        return dismantle_instance(origin);
    }
    
    if (!m_sizeof(stasis))
    {
        stasis = ([
            "actors":({}),
            "location":0,
            "origin":0,
            "alarm":0,
            "coords":({}),
            "history":({})
        ]);
    }
    
    if (!update_transport_location(actors, origin, location))
        return dismantle_instance(origin);
    
    hook_moved_to_stasis(actors, origin, location);
    return 1;
}

public object
query_transport_location(object actor, string str)
{
    string *list = m_indexes(locations);
    if (member_array(str, list) < 0)
    {
        if (!sizeof(list))
        {
            hook_no_transport_locations(actor);
            return 0;
        }
        
        hook_transport_location_not_found(actor, str, list);
        return 0;
    }
    
    return locations[str];
}


static nomask string
query_room_domain(object room)
{
    if (!objectp(room))
        return "";
    
    string *list = explode(file_name(room), "/");
    
    if (!sizeof(list) || list[1] != "d")
        return "";
    
    return list[2];
}

int
quit()
{
    // Dont want people to abuse the quit command to teleport home.
    move_actor_to_origin(({ this_player() }));
    m_delkey(stasis["actors"], this_player());
    this_player()->quit();
    
    if (!m_sizeof(stasis["actors"]))
        dismantle_instance(0);
    
    return 1;
}

void
init()
{
    ::init();
    add_action(quit, "quit");
}