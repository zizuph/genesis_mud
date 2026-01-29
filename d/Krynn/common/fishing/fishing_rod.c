/*
 *  Standard fishing rod for sailing and fishing rooms.
 *
 *  Taking some components from Greneth's average rod :)
 *  /w/greneth/fishing/rod/averagerod.c
 *
 *  Arman, March 2021
 */
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

/* Defines */
#define FISH_MANAGER                ("/d/Krynn/clubs/fishing/fishing_manager")
#define FISHING_CLUB_XP(x)          FISH_MANAGER->query_fishing_experience(x)
#define FISHING_CLUB_STAT(x)        (x)->exp_to_stat(FISHING_CLUB_XP(x))

#define FISH_OBJECT      "/d/Krynn/common/fishing/fish_object"
#define CASTING_STUN     "/d/Krynn/common/fishing/fparalyze2"
#define REELING_STUN     "/d/Krynn/common/fishing/fparalyze"
#define SKILL_REQUIRED   20

// Add this prop in a room if you want it to be a fishable room.
// Either set as 1 for default check, or a string such as
// "freshwater", "saltwater", "subterranean" depending on the fishing
// location. These location types are defined in ~fishing/fish_object.c
#define LIVE_I_CAN_FISH      "_live_i_can_fish"

// Add this prop if you don't want the room to be fishable.
// If you want a customised message why add prop in room as a string.
#define NO_FISHING_LOCATION  "_live_i_no_fish"

#define ROOM_I_HAS_PIER      "_room_i_has_pier"

#define NAVIGATION_MANAGER  ("/d/Genesis/gsl_ships/control/navigation_manager")

// General experience gained based off F_EXP_HERBSEARCH
// Max of 500 gxp
#define F_EXP_FISHING(catch_chance) \
    (300 + (((catch_chance) > 200) ? 200 : (catch_chance)))

#define FISH_DEBUG(x)  find_player("arman")->catch_msg("[Fish] " + x + "\n")

/* Prototypes */
public int          cast_rod(string str);
public int          bait_hook(string str);
public int          reel_rod(string str);
varargs int         stop_fishing(mixed arg);

/* Global Variables */
public int              Casted = 0;
public int              Baited = 0;
public int              Reeling = 0;
public string           bait_string = "";
static int              fishing_alarm;
static int              reeling_alarm;

object casting_stun, reeling_stun;

public string
query_bait_string()
{
    if(strlen(bait_string))
        return capitalize(bait_string) + 
            " has been hooked to the rod as bait.\n" + 
            "You can <cast rod> from a suitable fishing " +
            "location to try and catch a fish.\n";
    else
        return "The hook is currently empty. You can " +
            "<bait hook with [bait]> if you have " +
            "anything suitable to fish with.\n";
}

public void
create_rod()
{
    // Mask this function to customize the fishing rod.
}


/*
 * Function name:        create_object
 * Description  :        the constructor
 */
public void
create_object()
{
    ::create_object();

    set_name("rod");
    add_name("_krynn_fishing_rod");
    add_adj("fishing");
    set_short("fishing rod");
    set_long("This is a long and heavy fishing rod. It is designed " +
        "specifically for deep sea fishing off a boat, although could " +
        "be adequately used fishing from the shore or a riverbank.\n" +
        "@@query_bait_string");
       
    set_slots(W_BOTH);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT,8000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, 100);
    
    //Enable default item expiration
    set_item_expiration();

    create_rod();
} 

public mixed
hold()
{
    if(TO->query_prop(OBJ_I_BROKEN))
        return "The fishing rod is broken!\n";

    if(this_player()->query_skill(SS_HUNTING) < SKILL_REQUIRED)
    {
        say(QCTNAME(TP) + " isn't skilled enough to use the "
          + short() + ".\n");
        return "You can't figure out how to use the " + short() + ". " +
            "You likely need more hunting skill to be able to use a " +
            "fishing rod.\n";
    }

    write("You skillfully hold the " + short() + ".\n");
    say(QCTNAME(TP) + " holds the " + short() + ".\n");
    return 1;

} /* hold */


public mixed
release()
{
    object wielder;

    if(!objectp(wielder = TO->query_holder()))
    {
        return 1;
    }

    wielder->catch_tell("You release your grip on the " +
       short() + ".\n");
    tell_room(environment(wielder),
        QCTNAME(wielder) + " releases " + HIS(wielder) + " grip on the " +
        short() + ".\n", wielder);

    TO->stop_fishing(this_player());

    return 1;
} /* release */

/*
 * Function name: holdable_item_leave_env
 * Description:   This MUST be called from leave_env(). Failing to do
 *                means that this holdable is not properly released.
 * Arguments:     object env - the environment being left
 *                object to  - the environment being entered
 */
public void
holdable_item_leave_env(object env, object to)
{
    TO->stop_fishing(this_player());

    ::holdable_item_leave_env(env, to);
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function leave_env() as copy of this function. It MUST
 *                make the call to holdable_item_leave_env(from, to) as well.
 *                If you omit this, then the item will not be automatically
 *                released when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

object
query_deep_sea_object(object player)
{
    if(environment(player)->query_ship())
    {
        object ship_env;

        if(objectp(environment(player)->query_boat_out()))
        {
            object ship_env = environment(player)->query_boat_out();
            ship_env = environment(ship_env);

            if(present("_deep_sea_fish_school", ship_env))
            {
                object * sea_object = FIND_STR_IN_OBJECT("_deep_sea_fish_school", 
                    ship_env);
                return sea_object[0];
            }
        }
    }

    return 0;
}

public void
reeling_stun_reset()
{
    if(objectp(reeling_stun))
        reeling_stun->remove_object();
/*
    else
        FISH_DEBUG("No reeling stun to remove.\n");
*/
}

int
query_fishing_challenge()
{
    if(environment(this_player())->query_ship())
    {
        object ship_env;

        // From a Krynn sailable ship
        if(objectp(environment(this_player())->query_boat_out()))
        {
            object ship_env = environment(this_player())->query_boat_out();
            ship_env = environment(ship_env);

            if(present("_deep_sea_fish_school", ship_env))
            {
                return 100;
            }

            if(ship_env->query_sailing_difficulty() > 0)
            {
                return ship_env->query_sailing_difficulty();
            }
        }
    }
    return 1;
}

int
check_word_in_room_long(string word, object room)
{
    string *a, room_long;
    object player = this_object()->query_holder();

    if(!objectp(room))
        return 0;

    room_long = lower_case(room->long());

    if(environment(player)->query_is_deck())
        room_long = lower_case(environment(this_player())->examine_sea());

    a = explode(room_long," ");

    // FISH_DEBUG("Room long: " +room_long);
    // dump_array(a);

    if(member_array(word, a) > 0)
    {
        // FISH_DEBUG("word check member_array: " +member_array(word, a)+ ".");
        return 1;
    }

    return 0;
}

string
query_fishing_terrain()
{
    // A room has been listed as a fishable room.
    if(environment(this_player())->query_prop(LIVE_I_CAN_FISH))
    {
        if(environment(this_player())->query_fishing_area())
        {
            return environment(this_player())->query_fishing_area();
        }

        // If the fishing prop is set as an array of fishing options, 
        // such as ({"subterranean", "saltwater", "freshwater"})
        // randomly select one of them.
        if(pointerp(environment(this_player())->query_prop(LIVE_I_CAN_FISH)))
        {
            string *ter = environment(this_player())->query_prop(LIVE_I_CAN_FISH);

            if(sizeof(ter) > 1)
            {
                string random_ter = ter[random(sizeof(ter))];
                // FISH_DEBUG("Random terrain selected: " +random_ter);
                return random_ter;
            }
            else
                return ter[0]; 
        }

        if(strlen(environment(this_player())->query_prop(LIVE_I_CAN_FISH)))
        {
            return environment(this_player())->query_prop(LIVE_I_CAN_FISH);
        }
    }

    if(environment(this_player())->query_ship())
    {
        object ship_env;

        // From a Krynn sailable ship
        if(objectp(environment(this_player())->query_boat_out()))
        {
            // FISH_DEBUG("query_boat_out ship fishing location called");

            object ship_env = environment(this_player())->query_boat_out();
            ship_env = environment(ship_env);

            if(present("_deep_sea_fish_school", ship_env))
            {
                // FISH_DEBUG("query_sailing_terrain found deep sea fish school");
                return "deep_sea_fishing";
            }

            if(ship_env->query_fishing_area())
            {
                return ship_env->query_fishing_area();
            }

            // If LIVE_I_CAN_FISH is a string it defaults to that 
            // terrain type.
            if(strlen(ship_env->query_prop(LIVE_I_CAN_FISH)))
            {
                // If the fishing prop is set as an array of fishing options, 
                // such as ({"subterranean", "saltwater", "freshwater"})
                // randomly select one of them.
                if(pointerp(ship_env->query_prop(LIVE_I_CAN_FISH)))
                {
                    string *ter = ship_env->query_prop(LIVE_I_CAN_FISH);

                    if(sizeof(ter) > 1)
                        return ter[random(sizeof(ter))];
                    else
                        return ter[0]; 
                }

                return ship_env->query_prop(LIVE_I_CAN_FISH);
            }

            if(check_word_in_room_long("balifor", ship_env) ||
               check_word_in_room_long("balifor,", ship_env) ||
               check_word_in_room_long("balifor.", ship_env))
            {
                return "balifor";
            }

            if(check_word_in_room_long("bloodsea", ship_env) || 
               check_word_in_room_long("blood sea", ship_env) ||
               check_word_in_room_long("bloodsea,", ship_env) ||
               check_word_in_room_long("bloodsea.", ship_env))
            {
                return "bloodsea";
            }

            if(check_word_in_room_long("crystalmir", ship_env) || 
               check_word_in_room_long("crystalmir lake", ship_env) ||
               check_word_in_room_long("crystalmir lake,", ship_env) ||
               check_word_in_room_long("crystalmir lake.", ship_env))
            {
                return "crystalmir";
            }

            if(check_word_in_room_long("cavern", ship_env) ||
               check_word_in_room_long("cavern,", ship_env) ||
               check_word_in_room_long("cavern.", ship_env))
            {
                return "subterranean";
            }

            if(check_word_in_room_long("river", ship_env) || 
               check_word_in_room_long("river.", ship_env) ||
               check_word_in_room_long("river,", ship_env) ||
               check_word_in_room_long("lake", ship_env) ||
               check_word_in_room_long("lake.", ship_env) ||
               check_word_in_room_long("lake,", ship_env) ||
               check_word_in_room_long("stream", ship_env) ||
               check_word_in_room_long("stream.", ship_env) ||
               check_word_in_room_long("stream,", ship_env))
            {
                return "freshwater";
            }

            if(check_word_in_room_long("sea", ship_env) ||
                check_word_in_room_long("sea.", ship_env) || 
                check_word_in_room_long("sea,", ship_env) || 
                check_word_in_room_long("seas", ship_env) ||
                check_word_in_room_long("seas.", ship_env) || 
                check_word_in_room_long("seas,", ship_env) || 
                check_word_in_room_long("ocean.", ship_env) || 
                check_word_in_room_long("ocean,", ship_env) || 
                check_word_in_room_long("ocean", ship_env) ||
                check_word_in_room_long("bay", ship_env) ||
                check_word_in_room_long("beach", ship_env) ||
                check_word_in_room_long("coastline", ship_env) ||
                check_word_in_room_long("coastline,", ship_env) ||
                check_word_in_room_long("coastline.", ship_env) ||
                check_word_in_room_long("coast", ship_env))
            {
                return "saltwater";
            }

        }

        // Attempting to fish from a global ship
        if(objectp(environment(this_player())->query_ship()))
        {
            // FISH_DEBUG("Global ship fishing location called");

            object ship_env = environment(this_player())->query_ship();

            if(strlen(environment(this_player())->surroundings()))
            {
                // FISH_DEBUG("Ship surrounds() called");
                if(objectp(environment(ship_env)))
                {
                    ship_env = environment(ship_env);
                }
            }
            if(strlen(environment(this_player())->examine_sea()))
            {
                // FISH_DEBUG("Ship examine_sea() called");
                if(objectp(environment(ship_env)))
                {
                    ship_env = environment(this_player())->query_ship();
                }
            }

            if(check_word_in_room_long("balifor", ship_env) ||
               check_word_in_room_long("balifor,", ship_env) ||
               check_word_in_room_long("balifor.", ship_env))
            {
                return "balifor";
            }

            if(check_word_in_room_long("bloodsea", ship_env) || 
               check_word_in_room_long("blood sea", ship_env) ||
               check_word_in_room_long("bloodsea,", ship_env) ||
               check_word_in_room_long("bloodsea.", ship_env))
            {
                return "bloodsea";
            }

            if(check_word_in_room_long("crystalmir", ship_env) || 
               check_word_in_room_long("crystalmir lake", ship_env) ||
               check_word_in_room_long("crystalmir lake,", ship_env) ||
               check_word_in_room_long("crystalmir lake.", ship_env))
            {
                return "crystalmir";
            }

            if(check_word_in_room_long("cavern", ship_env) ||
               check_word_in_room_long("cavern,", ship_env) ||
               check_word_in_room_long("cavern.", ship_env))
            {
                return "subterranean";
            }

            if(check_word_in_room_long("river", ship_env) || 
               check_word_in_room_long("river.", ship_env) ||
               check_word_in_room_long("river,", ship_env) ||
               check_word_in_room_long("lake", ship_env) ||
               check_word_in_room_long("lake.", ship_env) ||
               check_word_in_room_long("lake,", ship_env) ||
               check_word_in_room_long("stream", ship_env) ||
               check_word_in_room_long("stream.", ship_env) ||
               check_word_in_room_long("stream,", ship_env))
            {
                    return "freshwater";
            }

            if(check_word_in_room_long("sea", ship_env) || 
                check_word_in_room_long("sea.", ship_env) || 
                check_word_in_room_long("sea,", ship_env) || 
                check_word_in_room_long("seas", ship_env) ||
                check_word_in_room_long("seas.", ship_env) || 
                check_word_in_room_long("seas,", ship_env) || 
                check_word_in_room_long("ocean.", ship_env) || 
                check_word_in_room_long("ocean,", ship_env) || 
                check_word_in_room_long("ocean", ship_env) ||
                check_word_in_room_long("bay", ship_env) ||
                check_word_in_room_long("beach", ship_env) ||
                check_word_in_room_long("coastline", ship_env) ||
                check_word_in_room_long("coastline,", ship_env) ||
                check_word_in_room_long("coastline.", ship_env) ||
                check_word_in_room_long("coast", ship_env))
            {
                    return "saltwater";
            }
        }
    }

    return "default";
}

int
filter_wielding_gaff(object obj)
{
      if (obj->id("_fishing_gaff"))
        return 1;
      else 
        return 0;
}

// % to Catch Fish 
/*
 * Function name:        catch_rod 
 * Description  :        roll to see if we caught a fish
 */
public void
catch_rod()
{     
    int chance_catch, challenge;
    string area;

    // Catch chance is based on a large random element, SS_HUNTING
    // skill (capped at 80), and a stat based on experienced gained
    // from fishing (capped at 20).

    chance_catch = random(100);
    chance_catch += min(80, this_player()->query_skill(SS_HUNTING));
    chance_catch += min(20, (FISHING_CLUB_STAT(this_player()) / 10));
    chance_catch -= random(100);

    // FISH_DEBUG("Catch chance: " +chance_catch+ ".\n");
    
    switch (chance_catch)
    {
        case 1..30:
            write ("You reel in your line but there is nothing on it. Not even " +
                "your bait. Drats!\n");
            say(QCTNAME(this_player()) + " reels in their line but there doesn't "
                + "seem to be anything on the hook.\n");
            Baited = 0;
            bait_string = "";
        break;
        
        case 31..70:
            write ("You reel in your line but there is nothing on it but your " +
                "bait.\n");
            say(QCTNAME(this_player()) + " reels in their line but there doesn't "
                + "seem to be anything on the hook except their bait.\n");
        break;
        
        case 71..500:
        // Spawn a fish depending on sailing area type, difficulty, bait value
            setuid();
            seteuid(getuid());

            object fish = clone_object(FISH_OBJECT);
            int custom_fish = 0;
            area = query_fishing_terrain();
            challenge = query_fishing_challenge();
            fish->set_fish_value(area, Baited, challenge);
            fish->generate_fish();
            fish->create_fish();

            // This is to allow custom fish or fishing catch objects
            // in fish_file.h
            if(wildmatch("customised_fishing_catch_*", fish->query_name())) 
            {
                string custom_catch = fish->query_long();

                setuid();
                seteuid(getuid());
                fish = clone_object(custom_catch);
                custom_fish = 1;
            }

            if(fish->move(this_player()))
            {
                object *team = this_player()->query_team_others() & 
                    all_inventory(environment(this_player())) + ({ this_player() });
                
                if(sizeof(team))
                {
                    // dump_array(team);
                    object * gaffing_team = ({ });
                    int team_weight = this_player()->max_weight() - 
                        this_player()->weight();

                    foreach(object team_member: team)
                    {
                        object *weapon;

                        /* Filter players with fishing gaffs */
                        if(team_member->query_tool(-1))
                            weapon = filter(team_member->query_tool(-1), 
                                filter_wielding_gaff); 

                        if(sizeof(weapon))
                        {
                            gaffing_team += ({ team_member });
                            team_weight += team_member->max_weight() - team_member->weight();
                        }
                    }

                    //FISH_DEBUG("Team weight: " +team_weight+ ", fish weight: " +
                    //    fish->query_prop(OBJ_I_WEIGHT));

                    if(sizeof(gaffing_team))
                    {
                        if(team_weight >= fish->query_prop(OBJ_I_WEIGHT))
                        {
                            string fish_short;
                            if(!custom_fish)
                                fish_short = fish->query_fish_short();
                            else
                                fish_short = fish->query_short();

                            int fish_weight = fish->query_prop(OBJ_I_WEIGHT);
                            int check_new_max = FISH_MANAGER->query_new_max_weight_fish(TP, 
                                fish_short, fish_weight);
                            string new_max_str;

                            if(!custom_fish)
                                FISH_MANAGER->add_player_fish_caught(this_player(), fish_short, 
                                    fish_weight);

                            if(!custom_fish)
                            {
                                if(FISH_MANAGER->query_num_caught_fish(TP, fish_short) == 1)
                                    new_max_str = " Your first ever " +fish_short+ " catch!";
                                else if(check_new_max)
                                    new_max_str = "\nWoah! You've never caught " +fish->short()+ 
                                        " this size before! A new record!";
                                else
                                    new_max_str = "";
                            }
                            else
                                new_max_str = "";
    
                            // Too heavy for one person, so move to environment
                            fish->move(environment(this_player()), 1);

                            write ("You reel in your line with the help of " + 
                                COMPOSITE_LIVE(gaffing_team) + " gaffing for you, pulling in "+
                                fish->short()+ "!" +new_max_str+ "\n");
                            gaffing_team->catch_msg("With your help gaffing " +
                                QTNAME(this_player()) + " reels in their line, pulling in "
                                +fish->short()+ "!\n");
                            this_player()->tell_watcher(QCTNAME(this_player()) + ", with gaffing "
                                + "assistance from " +COMPOSITE_LIVE(gaffing_team)+ ", reels in "
                                + "their line and it seems like they've caught " +fish->short()+
                               "!\n", gaffing_team, ({ this_player() }) + gaffing_team);

                            this_player()->add_exp_general(F_EXP_FISHING(chance_catch));

                            if(!custom_fish)
                                FISH_MANAGER->add_fishing_experience(this_player(), 
                                    F_EXP_FISHING(chance_catch));
                            // FISH_DEBUG("Gxp rewarded: " +F_EXP_FISHING(chance_catch)+ ".\n");
                        }
                        else
                        {
                            write ("You reel in your line, pulling in " +fish->short()+ "! " +
                                "But alas it is too heavy for you to carry, even with the " +
                                "gaffing help from " +COMPOSITE_LIVE(gaffing_team)+ ", and you " +
                                "frustratingly lose it back into the water!\n");
                            gaffing_team->catch_msg(QCTNAME(this_player()) + " reels in their "
                                + "line and it seems like "
                                + "they've caught " +fish->short()+ "!\nBut alas, it is too " +
                                "heavy for " +HIM(this_player())+ " to carry, even with your " +
                                "help gaffing, and " +
                                HE(this_player())+ " loses it back into the water.\n");
                            this_player()->tell_watcher(QCTNAME(this_player()) + " reels "
                                + "in their line and it seems like "
                                + "they've caught " +fish->short()+ "!\nBut alas, it is too " +
                                "heavy for " +HIM(this_player())+ " to carry, even with the " +
                                "gaffing help from " +COMPOSITE_LIVE(gaffing_team)+ ", and " +
                                HE(this_player())+ " loses it back into the water.\n", 
                                gaffing_team, ({ this_player() }) + gaffing_team);
                        }
                    }
                }
                else
                {
                    write ("You reel in your line, pulling in " +fish->short()+ "! " +
                        "But alas it is too heavy for you to carry, and you " +
                        "frustratingly lose it back into the water!\n");
                    say(QCTNAME(this_player()) + " reels in their line and it seems like "
                        + "they've caught " +fish->short()+ "!\nBut alas, it is too " +
                        "heavy for " +HIM(this_player())+ " to carry, and " +
                        HE(this_player())+ " loses it back into the water.\n");
                }
            }
            else
            {
                string fish_short;
                if(!custom_fish)
                    fish_short = fish->query_fish_short();
                else
                    fish_short = fish->query_short();

                int fish_weight = fish->query_prop(OBJ_I_WEIGHT);
                int check_new_max = FISH_MANAGER->query_new_max_weight_fish(TP, 
                    fish_short, fish_weight);
                string new_max_str;

                if(!custom_fish)
                    FISH_MANAGER->add_player_fish_caught(this_player(), fish_short, 
                        fish_weight);

                if(!custom_fish)
                {
                    if(FISH_MANAGER->query_num_caught_fish(TP, fish_short) == 1)
                        new_max_str = " Your first ever " +fish_short+ " catch!";
                    else if(check_new_max)
                        new_max_str = "\nWoah! You've never caught " +fish->short()+ 
                            " this size before! A new record!";
                    else
                        new_max_str = "";
                }
                else
                        new_max_str = "";

                fish->move(this_player(), 1);

                write ("You reel in your line, pulling in " +fish->short()+ 
                    "!" +new_max_str+ "\n");
                say(QCTNAME(this_player()) + " reels in their line and it seems like "
                    + "they've caught " +fish->short()+ "!\n");

                this_player()->add_exp_general(F_EXP_FISHING(chance_catch));
                FISH_MANAGER->add_fishing_experience(this_player(), F_EXP_FISHING(chance_catch));
                // FISH_DEBUG("Gxp rewarded: " +F_EXP_FISHING(chance_catch)+ ".\n");
            }

            Baited = 0;
            bait_string = "";

            if(objectp(query_deep_sea_object(this_player())))
            {
                object deep_sea = query_deep_sea_object(this_player());
                tell_room(E(this_player()), "You notice the " +
                     deep_sea->short()+ " near your ship begins " +
                     "to swiftly disperse.\n");
                deep_sea->fish_leaves(this_player());
            }
        break;
        
        default:
            write ("You reel in your line but there is nothing on it. Not even " +
                "your bait. Drats!\n");
            say(QCTNAME(this_player()) + " reels in their line but there doesn't "
                + "seem to be anything on the hook.\n");
            Baited = 0;
            bait_string = "";
    }

    Casted = 0;
    Reeling = 0;

    return;
} /* catch_rod */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    if(this_player() == environment())
    {
        add_action(cast_rod, "cast");
        add_action(bait_hook, "bait");
        add_action(reel_rod, "reel");
    }
} /* init */

/*
 * Function name:        reeling_reset
 * Description  :        resets the reel
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public void
reeling_reset()
{
    Reeling = 0;
    write ("You can <reel rod> to try again.\n");
}

/*
 * Function name:        reel_rod
 * Description  :        reels in the rod for player interaction
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
reel_rod(string str)
{
    if(!TO->query_held())
    {
        notify_fail("You must be holding the rod to reel it.\n");
        return 0;
    }

    if (!Casted)
    {
        notify_fail("You need to first cast your line.\n");
        return 0;
    }
    
    reeling_stun = present("fishing_reeling_paralyze_object", this_player());
    
    if (Reeling)
    {
        if(!objectp(reeling_stun))
        {
            Reeling = 0;  
            setuid();
            seteuid(getuid());
  
            reeling_stun = clone_object(REELING_STUN);
            reeling_stun->move(this_player(), 1);
            // FISH_DEBUG("Reeling reset as paralyze object not found.\n");
        }
        else
        {
            notify_fail("You shouldn't reel in so quickly.\n");
            return 0;
        }
    }
    
    int reel_chance;   
    reel_chance = random(100) + this_player()->query_skill(SS_HUNTING);

    if(!objectp(reeling_stun))
    {
        reel_chance = 0;
        // FISH_DEBUG("Reel_chance reset as reeling_stun not found.\n");
    }
    
    switch (reel_chance)
    {
        case 40..60:
            write ("You slowly reel in your rod a bit but nothing bites.\n");
            say(QCTNAME(this_player()) + " reels in their line a bit.\n");
            Reeling = 1;
            reeling_alarm = set_alarm(5.0, 0.0, &reeling_reset());
        break;
        
        case 61..80:
            write ("You give a small tug before letting the line go slack "
            + "again.\n");
            say(QCTNAME(this_player()) + " gives a small tug on their line.\n");
            Reeling = 1;
            reeling_alarm = set_alarm(5.0, 0.0, &reeling_reset());
        break;
             
        case 81..200:
            write ("The tip of your rod begins to dip and you notice tension "
            + "on the line. You continue to reel in your line...\n");
            say(QCTNAME(this_player()) + " continues to reel in their line.\n");
            Reeling = 1;
            set_alarm(5.0, 0.0, &reeling_stun_reset());        
            set_alarm(5.0, 0.0, &catch_rod());
        break;
        
        default:
        write ("Your rod jerks down a bit and you yank up hard... but "
            + "the line snaps and your catch is lost!\n");
        say(QCTNAME(this_player()) + " yanks up hard on their line but it snaps!\n");
        set_alarm(0.0, 0.0, &reeling_stun_reset());
        
        Baited = 0;
        Casted = 0;
        Reeling = 0;
        bait_string = "";
    }

    return 1;
} /* reel_rod */    
    

public int
check_valid_fishing_location()
{
    object ship_loc;

    if(environment(this_player())->query_prop(LIVE_I_CAN_FISH))
        return 1;

    if(environment(this_player())->query_ship() ||
        environment(this_player())->query_inside_of_boat())
    {
        ship_loc = environment(this_player())->query_boat_loc();

        if(ship_loc->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
            return 1;

        if(environment(this_player())->query_is_deck())
            return 1;

        if(environment(this_player())->query_room_env())
        {
            ship_loc = environment(this_player())->query_room_env();

            if(ship_loc->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
                return 1;
        }
        // Late inclusion, any boat can be fished from.
        return 1;
    }

    // If the pier room with this prop is inappropriate to fish from
    // add NO_FISHING_LOCATION to the room.
    if(environment(this_player())->query_prop(ROOM_I_HAS_PIER))
        return 1;

    return 0;
}

/*
 * Function name:        finish_casting_action
 * Description  :        applies the paralyze with reel exception
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        
 */
public void
finish_casting_action(object ob)
{
    object paralyze_object;

    if(objectp(casting_stun))
        casting_stun->remove_object();
/*
    else
        FISH_DEBUG("No casting stun to remove.\n");
*/

    if(!ob->query_held())
    {
        ob->stop_fishing(this_player());
        return;
    }

    setuid();
    seteuid(getuid());

    // apply the paralyze object for post cast allowing you to reel
    // this paralysis is named "fishing_reeling_paralyze_object"
    paralyze_object = clone_object(REELING_STUN);
    paralyze_object->move(this_player(), 1);

    write("Your line is cast. You should <reel rod> to try "
        + "and catch something.\n");

    // FISH_DEBUG("Reeling stun cloned.");
}

void
first_casting_action(object ob)
{
    if(!ob->query_held())
    {
        ob->stop_fishing(this_player());
        return;
    }

    write("Your line flies a ways out before dropping down into "
        + "the water.\n\nPLOP!\n\n");

    set_alarm(3.0, 0.0, &finish_casting_action(ob));
}


int
filter_rod(object obj)
{
    if (obj->id("_krynn_fishing_rod")) 
        return 1;
    else 
        return 0;
}

/*
 * Function name:        cast_rod
 * Description  :        allow the player to try to cast with the rod
 * Arguments    :        string str - what the player typed following
 *                       the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
cast_rod(string str)
{
    string ship_short = "";
    string rod_str;
    object * oblist, * rod, rod_obj;

    setuid();
    seteuid(getuid());

    if(!str)
        return 0;

    if(!strlen(str))
    {
        notify_fail("Cast what?\n");
        return 0;
    }

    if (!parse_command(str, deep_inventory(this_player()), 
        "[the] %o", rod_obj))
    {
        notify_fail("Cast what??\n");
        return 0;
    }

    if (!filter_rod(rod_obj))
    {
        notify_fail("Cast what???\n");
        return 0;
    }

    if(!rod_obj->query_held())
    {
        if(this_player()->query_tool(-1))
        {
            object *held_item = filter(this_player()->query_tool(-1), 
                filter_rod);

            if(sizeof(held_item))
            {
                notify_fail("You are carrying too many rods and they " +
                    "tangle with each other. You need to better " +
                    "organise your tackle before you can cast!\n");
                return 0;
            }

        }
        notify_fail("You must be holding the rod to cast it.\n");
        return 0;
    }
        
    if(!rod_obj->query_held())
    {
        notify_fail("You must be holding the rod to cast it.\n");
        return 0;
    }

    if(environment(this_player())->query_prop(NO_FISHING_LOCATION))
    {
        if(strlen(environment(this_player())->query_prop(NO_FISHING_LOCATION)) > 1)
        {
            string no_fish_msg = environment(this_player())->query_prop(NO_FISHING_LOCATION);
            notify_fail(no_fish_msg);
            return 0;
        }
        else
        {
            notify_fail("You cannot fish from this location.\n");
            return 0;
        }
    }

    if(!check_valid_fishing_location())
    {
        notify_fail("You cannot fish from this location.\n");
        return 0;
    }

    if(this_player()->query_skill(SS_HUNTING) < SKILL_REQUIRED)
    {
        notify_fail("The " + short() + " requires more hunting skill to use.\n");
        return 0;
    }

    // FISH_DEBUG("Pre-cast values...\nCasted: " +Casted+ 
    //    ", Reeling: " +Reeling+ ", Baited: " +Baited+ ".");


    if (Casted)
    {
        if (!present("fishing_reeling_paralyze_object", this_player()) &&
            !present("fishing_casting_paralyze_object", this_player()))
        {
            Casted = 0;
        }
        else
        {
            if(present("fishing_casting_paralyze_object", this_player()))
                notify_fail("You are currently casting your line!\n");
            else
                notify_fail("You have already cast your line!\n");

            return 0;
        }
    }
    
    if (!Baited)
    {
        notify_fail("You must first bait your hook!\n");
        return 0;
    }   

    if(environment(this_player())->query_ship())
    {
        object ship_obj = environment(this_player())->query_boat_out();

        if(objectp(ship_obj))
            ship_short = " over the side of the " +lower_case(ship_obj->short());
    }    

    write("You slowly cock your arm back and then whip the "
      + this_object()->query_short()+" forward, casting your line" +ship_short+ ".\n");
    say(QCTNAME(this_player()) + " cocks "
      + this_player()->query_possessive() + " arm back and then whips the "
      + this_object()->query_short()+" forward, casting their line" +ship_short+ ".\n");
    
    if (!present("fishing_casting_paralyze_object", this_player()))
    {
        setuid();
        seteuid(getuid());

        // The paralyze object while casting.
        // FISH_DEBUG("Casting stun cloned.");
        casting_stun = clone_object(CASTING_STUN);
        casting_stun->move(this_player(), 1);

    }

    set_alarm(3.0, 0.0, &first_casting_action(rod_obj));

    Casted = 1;

    return 1;
} /* cast_rod */

/*
 * Function name:        bait_hook
 * Description  :        Attaches bait to the rod
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
bait_hook(string str)
{
    string bait_str;
    object ebait;
    object *fbait;
    object *oblist; 
    int in;
    
    setuid();
    seteuid(getuid());
    
    if(!strlen(str))
    {
        notify_fail("Bait what?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] 'hook' / 'rod' 'with' [the] %s", bait_str))
    {
        notify_fail("Bait hook with <what>?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(bait_str, all_inventory(this_player()))))
    {
        notify_fail("You possess no " + bait_str + " to put on your hook.\n");
        return 0;
    }
      
    fbait = filter(oblist, &->id("_fishing_bait"));

    if(!sizeof(fbait))
    {
        notify_fail("The " +bait_str+ " isn't a suitable bait to " +
            "put on your hook.\n");
        return 0;
    }
    
    if(Baited)
    {
        notify_fail("You already have a piece of bait on your hook.\n");
        return 0;
    }

    // bait_string = fbait[0]->short();  
    bait_string = LANG_ADDART(fbait[0]->singular_short(this_player())); 

    // Different baits have varying quality ratings, improving catch type chance.
    if(!fbait[0]->query_bait_value())
        Baited = 1;
    else
        Baited = fbait[0]->query_bait_value();

    write("You slide " +bait_string+ " bait on the small shiny hook at "
        + "the end of your line.\n");
    say(QCTNAME(this_player()) + " slides " +bait_string+ " bait on " +
        "the hook of " +HIS(this_player())+ " " +short()+ ".\n");

    // remove the bait object
    in = fbait[0]->num_heap();
    if (in)
        fbait[0]->reduce_heap_size();
    else
        fbait[0]->remove_object();      
 
    return 1;
}

/*
 * Function name: stop_fishing
 * Description:   interrupt fishing
 * Arguments:
 * Returns:
 */
varargs int
stop_fishing(mixed arg)
{
    // FISH_DEBUG("Stop fishing called");

    if (fishing_alarm)
    {
        remove_alarm(fishing_alarm);
        fishing_alarm = 0;
        Reeling = 0;
        Casted = 0;
        tell_room(environment(this_player()), QCTNAME(this_player())
            + " stops fishing.\n", this_player());
        
        return 0;
    }

    if (reeling_alarm)
    {
        remove_alarm(reeling_alarm);
        reeling_alarm = 0;
        Reeling = 0;
        Casted = 0;
        tell_room(environment(this_player()), QCTNAME(this_player())
            + " stops fishing.\n", this_player());
        
        return 0;
    }

    if(objectp(casting_stun))
        casting_stun->remove_object();
    if(objectp(reeling_stun))
        reeling_stun->remove_object();

    Reeling = 0;
    Casted = 0;

    return 0;
} /* reel_rod */


string
query_recover()
{
    return MASTER;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
}