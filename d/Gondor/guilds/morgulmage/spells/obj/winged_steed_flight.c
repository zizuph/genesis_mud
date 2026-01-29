/*
 * Flight functions for the winged steed. Is inheritted by
 * the main steed object.
 *
 * Zizuph 2021-11 Removed custom destinations, to avoid adding
 *   the new 2h teleport cooldown.
 *
 */

#pragma no_clone

#include <stdproperties.h>
#include "../../morgulmage.h";
#include <composite.h>
#include <language.h>
#include <terrain.h>
#include <macros.h>
#include "/d/Avenir/include/steed.h"

#define MESSAGE_TIME 5.0

string destination_name;
int flight_alarm = -1;
object last_location;

mixed circling = 0;
int circling_started = 0;
object *players_in_circle_region(int ignore_hidden = 0);
object *spotted_players = ({});

void set_last_location(object location) {
    last_location = location;
}

object environment_room() {
    object room = environment(this_object());
    while (room && !room->query_prop(ROOM_I_IS))
    {
        room = environment(room);
    }  
    return room;
}

void tell_rooms(object room, string environment_message, string adjecent_message) {
    tell_room(room, environment_message, ({ this_object() }));

    foreach(object adjecent_room : filter(map(room->query_exit_rooms(), 
        find_object), not @ &->query_prop(ROOM_I_INSIDE))) {
        tell_room(adjecent_room, adjecent_message);
    }
    
}

void take_off() {
    environment_room()->notify_winged_steed_take_off();

    tell_rooms(environment_room(),
        "The winged beast stretches its pinions and flies "
        + "off into the sky.\n",

        "A dark, winged shape rises into the sky "
        + "like a dark cloud and flies off into the distance.\n");

    this_object()->move_living("M", MORGUL_WINGED_STEED_ROOM);
}

void take_off_and_remove() {
    take_off();
    this_object()->remove_object();
}

public string determine_domain(object room) {
    string dom = domain(room);
    if ((dom == "Shire") || (dom == "Gondor")) return "Middle Earth";
    return dom;
}

public float determine_flight_time(object source, object destination) {
    string sourcedomain = determine_domain(source);
    string destinationdomain = determine_domain(destination);

    if (sourcedomain == destinationdomain) {
        return 20.0;
    }

    return 40.0;
}

int in_flight() {
    return (flight_alarm != -1);
}

int is_circling() {
    return (circling != 0) && circling_started;
}

string query_destination_name() {
    return destination_name;
}

string query_circling_region() {
    return ((circling != 0) && circling_started) ? destination_name : 0;
}

string capitalize_words(string text) {
    return implode(map(explode(text, " "), capitalize), " ");
}

string combine_locations(string *destinations) {
    return COMPOSITE_WORDS(map(destinations, capitalize_words));
}

void show_destinations() {
    write("Your steed recognizes these destinations:\n\n");
    string *preset_locations = m_indexes(MORGUL_MASTER->query_winged_steed_fixed_destinations());
    write(break_string(combine_locations(preset_locations) + ".\n", 60, "\t"));

    /*
    string *custom_locations = m_indexes(MORGUL_MASTER->query_winged_steed_destinations(this_player()));
    if (sizeof(custom_locations)) {
        write("\nThe winged beast has remembered the following additional locations:\n\n");
        write(break_string(combine_locations(custom_locations) + ".\n", 60, "\t"));        
    } else {
        write("\nThe winged beast has not remembered any additional locations.\n\n");
    }
    */

    write("\nAdditionally you can order your steed to circle these regions:\n\n");
    string *circle_locations = m_indexes(MORGUL_MASTER->query_winged_steed_circle_locations());
    write(break_string(combine_locations(circle_locations) + ".\n", 60, "\t"));
}

string *random_messages = ({});
void random_flight_message() {
    if (!sizeof(random_messages))
    {
        random_messages =
        ({
            "The chilly wind is blowing icily into your face.\n",
            "Far below your steed, clouds are passing.\n",
            "Beating its pinions slowly, your steed is carrying you "
                + "swiftly to your destination.\n",
            "Like a dark cloud out of Mordor you and your steed are "
                + "passing across the realms.\n",
            "Your steed utters a harsh croaking scream, spreading "
                + "terror in the lands below.\n",
            "Faster than any wind your winged steed carries you onwards.\n"
        });
    }

    string txt = one_of_list(random_messages);
    tell_room(this_object(), txt);
    random_messages -= ({ txt });
}

void perform_flight_alarm(object target, mixed data, int messages_remaining, 
    float time_per_message) {

    flight_alarm = -1;

    switch(messages_remaining) {
        case 0: {
            tell_rooms(target, 
                "A huge winged beast descends from the sky and "
                + "lands here.\n",

                "A huge winged beast descends from the "
                + "sky and seems to land not far from here.\n");

            target->notify_winged_steed_landing();
            this_object()->move_living("M", target);

            if (data["site"]) {
                tell_room(this_object(), data["site"]);
            } else {
                tell_room(this_object(), "And then, suddenly, your steed "
                    + "lands with a mighty beating of the pinions and you "
                    + "are back on solid earth.\n");
            }

            last_location = target;
            break;
        }
        case 1: {
            tell_room(target, "Blind fear and deadly cold embrace you as the "
                + "dark shape draws nearer.\n");
            tell_room(this_object(), "Down, down the beast falls out of the "
                + "sky almost like a rock, diving through the air to the "
                + "ground.\n");

            target->notify_winged_steed_approach(1);
            break;
        }
        case 2: {
            tell_room(target, "A dark shape, like a cloud and yet not "
                + "like a cloud, for it moves far too quickly, is coming " 
                + "out of the sky, speeding towards you, blocking out all "
                + "light as it approaches.\n");
            tell_room(this_object(), "Your fell beast is beginning to "
                + "descend again.\n");
            target->notify_winged_steed_approach(2);
            break;
        }
        default: {
            random_flight_message();
            break;
        }
    }

    if (messages_remaining > 0) {
        messages_remaining--;
        flight_alarm = set_alarm(time_per_message, 0.0, 
            &perform_flight_alarm(target, data, messages_remaining, 
                time_per_message));
    }
}

void prepare_flight(string key, mixed data) {
    destination_name = capitalize_words(key);

    catch(data["path"]->teleledningsanka());
    object target = find_object(data["path"]);

    if (!objectp(target)) {
        write("Your steed does not know the direction to " 
            + capitalize_words(key) + ". Please leave a bug "
            + "report.\n");
        return;
    }


    if(!in_flight()) {
        take_off();

        tell_room(this_object(), "Your winged steed stretches its pinions "
            + "and takes off into the sky, carrying you with it.\n",
            ({ this_object() }) );
    } else {
        remove_alarm(flight_alarm);
        flight_alarm = -1;

        players_in_circle_region()->catch_tell("The fell beast races "
            + "above, turns, and then is gone, flying away with the speed "
            + "of a wraith of Mordor. Behind it the wind roars away, leaving "
            + "the sky bare and bleak.\n");
        circling = 0;

        tell_room(this_object(), "Your winged steed wheels through "
            + "a large circle, finds the new course and shoots away "
            + "like an arrow towards the new destination.\n", 
            ({ this_object() }) );
    }

    float flight_duration = determine_flight_time(last_location, target);
    int number_of_messages = max(3, ftoi(flight_duration / MESSAGE_TIME));
    float time_per_message = flight_duration / itof(number_of_messages);

    flight_alarm = set_alarm(time_per_message, 0.0, 
        &perform_flight_alarm(target, data, number_of_messages - 1, 
            time_per_message));
}

void fly_to_destination(string args) {
    string *preset_locations = m_indexes(MORGUL_MASTER->query_winged_steed_fixed_destinations());
    string *custom_locations = m_indexes(MORGUL_MASTER->query_winged_steed_destinations(this_player()));

    args = lower_case(args);

    if (member_array(args, preset_locations) != -1) {
        write("You command your winged steed to bring you to " 
            + capitalize_words(args) + ".\n");
        set_alarm(2.0, 0.0, &prepare_flight(args, 
            MORGUL_MASTER->query_winged_steed_fixed_destinations()[args]));
    /*
    } else if (member_array(args, custom_locations) != -1) {
        write("You command your winged steed to bring you to " 
            + capitalize_words(args) + ".\n");
        set_alarm(2.0, 0.0, &prepare_flight(args, 
            MORGUL_MASTER->query_winged_steed_destinations(this_player())[args]));
    */
    } else {
        write(capitalize(args) + " is not a possible direction!\n"); return;
    }
}

/****************************************************
 * Circling regions
 ****************************************************/

int in_region(string filename, object player)
{
    object env;

    env = environment(player);
    if(!objectp(env)) return 0;
    return wildmatch(filename, file_name(env));
}

object *players_in_circle_region(int ignore_hidden = 0) {
    if (!circling) return ({ });

    object *all_users, *ignored_users, *remaining_users;
    int i;

    all_users = users();
    ignored_users = all_users;

    // Find all players in this region
    for(i=0;i<sizeof(circling["paths"]);i++)
    {
        // Keep all users that are not in this region
        ignored_users = filter(ignored_users, not @
            &in_region(circling["paths"][i] + "*"));
    }

    // All users that are not ignored are the ones in our region
    remaining_users = all_users - ignored_users;

    // Filter out all inside users
    remaining_users = filter(remaining_users,
        not @ &->query_prop(ROOM_I_INSIDE) @ environment);

    // See if we need to ignore hidden and invis users
    if(ignore_hidden)
    {
        // Filter invis users
        remaining_users = filter(remaining_users,
            not @ &->query_prop(OBJ_I_INVIS));

        // Filter hidden users
        remaining_users = filter(remaining_users,
            &operator(<=)(, 15) @ &->query_prop(OBJ_I_HIDE));
    }

    // Temporary filter for users and jr's
    // ignored_users = remaining_users;
    // ignored_users = filter(ignored_users, not @ &->query_wiz_level());
    // ignored_users = filter(ignored_users, not @ &wildmatch("*jr") @ &->query_real_name());
    // remaining_users -= ignored_users;

    return remaining_users;
}

void add_spotted_player(object player)
{
    // Make sure we have only four members
    if(sizeof(spotted_players) > 4)
        spotted_players = exclude_array(spotted_players, 4, 
            sizeof(spotted_players));

    // Add the player to the beginning of the array
    spotted_players = ({ player }) + spotted_players;
}

int spot_player()
{
    object  *dest_users;
    object  player;

    // Find all visible users
    dest_users = players_in_circle_region(1);

    // Remove all previously spotted players
    dest_users -= spotted_players;

    // We don't always spot players
    if((random(100) > 70) || (!sizeof(dest_users)))
    {
        add_spotted_player(0);
        return 0;
    }

    // Find a player to spot
    player = one_of_list(dest_users);
    add_spotted_player(player);

    player->catch_msg("The shadow of horror wheels and turns, passing " 
        + "lower now and sweeping past with its enormous wings. The rider " 
        + "atop the winged steed looks directly at you and jerks the reins " 
        + "in your direction. As he nears you, the wraith hisses " 
        + "threateningly in your direction and rasps loudly to his bird-like " 
        + "steed. The steed skillfully rises to the heavens once again.\n");
    tell_room(environment(player),
          "The shadow of horror wheels and turns, passing lower now and " 
        + "sweeping past with its enormous wings. The rider atop the " 
        + "winged steed looks directly at " + QTNAME(player) + " and jerks " 
        + "the reins in " + player->query_possessive() + " direction. As he " 
        + "nears " + player->query_objective() + ", the wraith hisses " 
        + "threateningly in " + player->query_possessive() + " direction and " 
        + "rasps loudly to his bird-like steed. The steed skillfully rises to " 
        + "the heavens once again.\n", player);
    tell_room(this_object(), "Your fell steed wheels and turns, passing " 
        + "lower now and sweeping down with its enormous wings. You hiss as " 
        + "you sight " + QNAME(player) + " below and inform your steed of " 
        + player->query_possessive() + " presence with a sharp rasp.\n");
    return 1;
}

mixed random_circle_messages = ({});
void random_circle_message() {
    if(!sizeof(random_circle_messages)) {
        random_circle_messages = 
            ({
                ({ // User message
                "The winged beast slowly spirals down examining an " +
                "area a short distance away.\n",
                // Nazgul message
                "Your winged beast slowly spirals down to examine an " +
                "area, but you note nothing of importance.\n" 
                }),

                ({ 
                "The winged beast circles high above yet the fear " +
                "and terror emanating from it is quite palpable.\n",
                "Your winged beast soars high searching for prey.\n"
                }),

                ({
                "The winged beast wheels abruptly and approaches you. " +
                "The desire to hide tightly grips your mind.\n",
                "Your steed wheels abruptly, its great pinions beating " +
                "slowly. Terror spreads across the lands below.\n" 
                }),

                ({
                "The winged beast rushes past barely overhead, its " +
                "ghastly pinions beating slowly. A dark hooded figure " +
                "mounted on its back peers intently from side to side " +
                "at the ground. They swiftly pass out of sight.\n",
                "Your steed wheels abruptly, its great pinions beating " +
                "slowly. You peer intently at the ground, but you fail " +
                "to locate suitable prey.\n"
                }),

                ({
                "The winged beast suddenly dives down over a nearby " +
                "point. Seconds later it rockets skyward.\n",
                "Your beast spots something on the ground and spirals " +
                "downward. You see nothing of interest and order it to " +
                "ascend once again.\n"
                }),

                ({
                "The winged beast effortlessly glides in tight circles " +
                "not far from you, letting out a guttural croak. As the " +
                "circles widen, it angles farther and farther away.\n",
                "Your winged steed glides effortlessly in tight circles, " +
                "then angles wider and wider to scan an increasingly " +
                "broad area.\n"
                })
            });
    }

    mixed txt = one_of_list(random_circle_messages);
    random_circle_messages -= ({ txt });

    // Write to the nazgul and the players in the region
    players_in_circle_region()->catch_msg(txt[0]);
    tell_room(this_object(), txt[1]);
}

void perform_circle_alarm(mixed data, int messages_remaining, float time_per_message) {
    flight_alarm = -1;

    switch(messages_remaining) {
        case 0:
            if (!spot_player()) {
                random_circle_message();
            }
            time_per_message = itof(10 + random( 10 ));
            break;
        case 1:
            MORGUL_MASTER->increase_activity(this_object()->get_owner(), 
                ACTIVITY_RARE_SPELL);

            tell_room(this_object(), "Your winged steed decends and starts "
                + "circling over " + query_destination_name() + ".\n");
            players_in_circle_region()->catch_tell("The winged figure curves "
                + "in an arc through the lowest clouds then gracefully begins "
                + "circling in the air above.\n");

            circling_started = 1;
            last_location = find_object(MORGUL_WINGED_STEED_ROOM);
            break;
        case 2:
            tell_room(this_object(), "You order your steed lower to " 
                + "scout " + query_destination_name() + ".\n");
            players_in_circle_region()->catch_tell("A distant bird-like "
                + "shape streaks down from the clouds overhead at dizzying "
                + "speeds. Horror stiffens every muscle in your body.\n");
            break;
        default:
            random_flight_message();
            break;
    }

    if (messages_remaining > 0) {
        messages_remaining--;
    }

    flight_alarm = set_alarm(time_per_message, 0.0, 
        &perform_circle_alarm(data, messages_remaining, time_per_message));
}

void prepare_circle_flight(string key, mixed data) {
    destination_name = capitalize_words(key);

    if(!in_flight()) {
        take_off();

        tell_room(this_object(), "Your winged steed stretches its pinions "
            + "and takes off into the sky, carrying you with it.\n",
            ({ this_object() }) );
    } else {
        remove_alarm(flight_alarm);
        flight_alarm = -1;

        players_in_circle_region()->catch_tell("The fell beast races "
            + "above, turns, and then is gone, flying away with the speed "
            + "of a wraith of Mordor. Behind it the wind roars away, leaving "
            + "the sky bare and bleak.\n");

        tell_room(this_object(), "Your winged steed wheels through "
            + "a large circle, finds the new course and shoots away "
            + "like an arrow towards the new destination.\n", 
            ({ this_object() }) );
    }

    circling = data;

    float flight_duration = determine_flight_time(last_location, 
        find_object(MORGUL_WINGED_STEED_ROOM));
    int number_of_messages = max(3, ftoi(flight_duration / MESSAGE_TIME));
    float time_per_message = flight_duration / itof(number_of_messages);

    flight_alarm = set_alarm(time_per_message, 0.0, 
        &perform_circle_alarm(data, number_of_messages - 1, time_per_message));
}

void circle_destination(string args) {
    string  *destinations = m_indexes(MORGUL_MASTER->query_winged_steed_circle_locations());

    args = lower_case(args);
    if (member_array(args, destinations) != -1) {
        write( "You command your winged steed to circle " 
            + capitalize_words(args) + ".\n" );

        set_alarm(2.0, 0.0, &prepare_circle_flight(args, 
            MORGUL_MASTER->query_winged_steed_circle_locations()[args]));
    } else {
        write(capitalize(args) + " is not a possible region!\n");
        return;
    }
}

void forget_location(string args) {
    string *custom_destinations = m_indexes(MORGUL_MASTER->query_winged_steed_destinations(this_player()));

    args = lower_case(args);
    if (member_array(args, custom_destinations) == -1) {
        write("Your winged steed does not remember a location by that name.\n");
        return;
    }

    MORGUL_MASTER->remove_winged_steed_destination(this_player(), args);
    write("You order your winged steed to forget the destination " 
        + capitalize_words(args) + ".\n");
}

void remember_location(string args) {
    if (in_flight()) {
        write("You are in flight, and the clouds do not provide enough "
            + "reference for your winged steed.\n");
        return;
    }

    args = lower_case(args);

    string *custom_destinations = m_indexes(MORGUL_MASTER->query_winged_steed_destinations(this_player()));
    int total_custom_destinations = sizeof(custom_destinations);
    int available_destinations = MORGUL_MASTER->query_max_number_of_winged_steed_destinations(this_player());

    if (member_array(args, custom_destinations) != -1) { 
        write("Your steed is already remembering a destination by that name.\n");
        return;
    }

    if (available_destinations <= total_custom_destinations) {
        write("Your steed cannot remember any more destinations.\n");
        return;
    }

    object room = environment(this_object());
    if (!room->query_prop(ROOM_I_IS) || 
        (room->query_prop(ROOM_I_INSIDE) && 
        (file_name(room) != AVENIR_PORT_PATH))) {
        write("You are indoors, your winged steed wil not be able "
            + "to return here.\n");
        return;
    }

    if (room->query_prop(ROOM_M_NO_TELEPORT) || 
        room->query_prop(MORGUL_I_NO_SUMMON_STEED)) {
        write("Forces greater than the Dark Lord prevent your steed "
            + "from remembering this location.\n");
        return;
    }

    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
        (room->terrain_includes_any(TERRAIN_UNDERWATER))) {
        write("Your winged steed is unable to remember this location.\n");
        return;
    }

    string filename = file_name(environment(this_object()));
    if ((filename[0..2] != "/d/") || (filename != MASTER_OB(room))) {
        write("Your winged steed is unable to remember this location.\n");
        return;
    }

    write("You order your steed to remember this location as " + args + ".\n");
    MORGUL_MASTER->add_winged_steed_destination(this_player(), lower_case(args),
        filename);

    int remaining = available_destinations - total_custom_destinations - 1;
    if (remaining == 0) {
        write("It will not be able to remember more locations.\n");
    } else {
        write("It can remember " + LANG_NUM2WORD(remaining) + " additional "
            + (remaining == 1 ? "location" : "locations") + ".\n");
    }
}

int do_command(string args) {
    if (environment(this_player()) != this_object()) return 0;

    object o;
    string where;

    if (!args || !strlen(args)) {
        notify_fail("Command what?\n");
        return 0;       
    }

    if (args == "destinations") {
        show_destinations();
        return 1;
    }

    if (parse_command(args, ({ this_object() }), "%l [to] 'circle' %s", o, where)) {
        circle_destination(where);
        return 1;
    }
    /*

    if (parse_command(args, ({ this_object() }), "%l [to] 'remember' [this] [location] [as] %s", o, where)) {
        remember_location(where);
        return 1;
    }

    if (parse_command(args, ({ this_object() }), "%l [to] 'forget' [location] %s", o, where)) {
        forget_location(where);
        return 1;
    }
    */

    if (parse_command(args, ({ this_object() }), "%l [to] [go] / [fly] [to] %s", o, where)) {
        fly_to_destination(where);
        return 1;
    }

    notify_fail("Command whom to do what?\n");
    return 0;
}
