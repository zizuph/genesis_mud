/*
 *  /d/Emerald/blackwall/delrimmon/obj/quest_manager.c
 *
 *  This object controls the information which is assigned to the
 *  players who encounter elements of the Torque Quest. Due to
 *  my rather unsophisticated level of coding prowess, I may have
 *  accomplished certain things here the "long way" as some might
 *  put it. If anything you see here is confusing, or needs
 *  clarification, please do not hesitate to ask me about it.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 *
 *  Reworked the signal routines, simplifying the code a bit, but, most
 *  importantly, eliminating some problems with handling longer signal
 *  patterns. Be aware that the query_signal_pattern() routine does still
 *  combine each of the individual patterns into one integer, and so
 *  overflow is still a concern; therefore, we should make sure that the
 *  total pattern length cannot exceed 30. Currently the maximum is 20
 *  (five sets of four). This could also be overcome simply by not bit
 *  encoding the query_signal_pattern() value. -Shiva, Oct 13 2003
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include <time.h>
#include <math.h>

#define QUEST_RILLIAN         "On_Rillian_Quest"
#define QUEST_SPELL           "Quest_Spell"
#define QUEST_PASSWORD        "Quest_Password"
#define QUEST_EMBLEM_1        "Quest_Emblem_1"
#define QUEST_EMBLEM_2        "Quest_Emblem_2"
#define QUEST_READ_TABLET     "Read_the_tablet"
#define QUEST_SAW_SHADOW      "Saw_the_shadow"
#define QUEST_DOOR_LOCATION   "Door_Location"
#define QUEST_FIRST_PATTERN   "First_Pattern"
#define QUEST_SECOND_PATTERN  "Second_Pattern"
#define QUEST_THIRD_PATTERN   "Third_Pattern"
#define QUEST_FOURTH_PATTERN  "Fourth_Pattern"
#define QUEST_FIFTH_PATTERN   "Fifth_Pattern"
#define QUEST_SIGNAL_PATTERN  "Signal_Pattern"
#define QUEST_SUFFIX          "Suffix"
#define QUEST_DUG_WATERFALL   "Dug_the_Waterfall"
#define QUEST_READ_JOURNAL    "Read_the_Journal"
#define QUEST_READ_LOG        "Read_Military_Log"
#define QUEST_TRIG_BEACON     "Triggered_the_Beacon"
#define QUEST_FOUND_TOWER     "Found_the_Tower"
#define QUEST_LOST_TORQUE     "Destroyed_the_Torque"

/* see the file /d/Emerald/blackwall/delrimmon/text/emblem_codes */
#define EMBLEM_CODES    ({ (170),\
                           (85),\
                           (41),\
                           (82),\
                           (164),\
                           (73),\
                           (146),\
                           (37),\
                           (74),\
                           (148),\
                           (138),\
                           (162),\
                           (168),\
                           (42),\
                       })

// Signal patterns are bit-encoded values, 1 = long 0 = short. A 1 is
// prepended to allow for leading shorts; it should not be used as part of
// the signal. For example, four shorts is binary 10000, but only 0000, four
// shorts, represents the actual signal.
#define SIGNAL_PATTERNS ({ 16, /* 4 short */ \
                            9, /* 2 short, 1 long */ \
                           12, /* 1 long, 2 short */ \
                            7, /* 2 long */ \
                           10, /* 1 short, 1 long, 1 short */ \
                        })
#define DOOR_LOCATIONS  ({ (STUMP),\
                           (SAND),\
                           (CLEARING),\
                           (BOULDER),\
                       })
#define PASSWORDS       ({ ("lindelii"),\
                           ("freaveil"),\
                           ("shalaine"),\
                           ("arnala"),\
                           ("vraentil"),\
                           ("shbalet"),\
                           ("anlai"),\
                           ("rendaelti"),\
                           ("farein"),\
                           ("saeinid"),\
                           ("halleiva"),\
                           ("venliel"),\
                           ("shenaddei"),\
                           ("rantorei"),\
                       })
#define SPELLS          ({ ("fiilant"),\
                           ("spael"),\
                           ("utenika"),\
                           ("relantis"),\
                           ("enkenso"),\
                           ("sucreti"),\
                           ("yileffai"),\
                           ("hjendsi"),\
                           ("rendist"),\
                           ("uutvidentis"),\
                           ("messindid"),\
                           ("dracinn"),\
                           ("kveittael"),\
                           ("leliccina"),\
                        })
#define SUFFICIES       ({ ("tra"),\
                           ("tar"),\
                           ("tan"),\
                           ("tri"),\
                           ("tor"),\
                           ("ten"),\
                           ("tas"),\
                       })


#define QM_LOG_FILE ("/d/Emerald/log/del_rimmon/quest_manager_changes")

public void
create_data_manager()
{
    set_save_dir("/d/Emerald/log/del_rimmon/quest_data/");
    set_garbage_dir("/d/Emerald/log/del_rimmon/quest_data/old");
}

public void
log_change(mixed who, string change)

{
    if (!(who = get_id(who)))
    {
        who = "???";
    }

    setuid();
    seteuid(getuid());

    write_file(QM_LOG_FILE, sprintf("%s %-11s %s\n", ctime(time()), who, change));

    if (file_size(QM_LOG_FILE) > 40000)
    {
        int cnt = 0;
        string arch_file, tmp;
        arch_file = QM_LOG_FILE + "-" + TIME2FORMAT(time(), "yyyymmdd");
        tmp = arch_file;
        while (file_size(tmp) != -1)
        {
            tmp = arch_file + "-" + (++cnt);
        }

        arch_file = tmp;

        write_file(arch_file, read_file(QM_LOG_FILE));
        rm(QM_LOG_FILE);
    }
}

public int
set_info(mixed index, string info, mixed val)
{
    mixed previous = get_info(index, info);
    int ret = ::set_info(index, info, val);

    if (previous != val)
    {
        log_change(index, info + ": " + val);
    }

    return ret;
}

public int
remove_info(mixed index, string info)
{
    int ret;
    if ((ret = ::remove_info(index, info)))
    {
        log_change(index, info + " <<REMOVED>>");
    }

    return ret;
}

public int
delete_data(string id)
{
    ::delete_data(id);
    log_change(id, "data deleted");
}

public int
set_rillian(mixed who, string rillian)
{
    return set_info(who, QUEST_RILLIAN, rillian);
}

public string
query_rillian(mixed who)
{
    return get_info(who, QUEST_RILLIAN);
}

public int
set_spell(mixed who, string spell)
{
    return set_info(who, QUEST_SPELL, spell);
}

public string
query_spell(mixed who)
{
    return get_info(who, QUEST_SPELL);
}

public int
set_password(mixed who, string pass)
{
    return set_info(who, QUEST_PASSWORD, pass);
}

public string
query_password(mixed who)
{
    return get_info(who, QUEST_PASSWORD);
}

public int
set_emblem_1(mixed who, int code)
{
    return set_info(who, QUEST_EMBLEM_1, code);
}

public int
query_emblem_1(mixed who)
{
    return get_info(who, QUEST_EMBLEM_1);
}

public int
set_emblem_2(mixed who, int code)
{
    return set_info(who, QUEST_EMBLEM_2, code);
}

public int
query_emblem_2(mixed who)
{
    return get_info(who, QUEST_EMBLEM_2);
}

public int
set_read_tablet(mixed who, string arg)
{
    return set_info(who, QUEST_READ_TABLET, arg);
}

public string
query_read_tablet(mixed who)
{
    return get_info(who, QUEST_READ_TABLET);
}

public int
set_saw_shadow(mixed who, string arg)
{
    return set_info(who, QUEST_SAW_SHADOW, arg);
}

public string
query_saw_shadow(mixed who)
{
    return get_info(who, QUEST_SAW_SHADOW);
}

public int
set_door_location(mixed who, string location)
{
    return set_info(who, QUEST_DOOR_LOCATION, location);
}

public string
query_door_location(mixed who)
{
    return get_info(who, QUEST_DOOR_LOCATION);
}


public int
set_first_pattern(mixed who, int pattern)
{
    return set_info(who, QUEST_FIRST_PATTERN, pattern);
}

public int
query_first_pattern(mixed who)
{
    return get_info(who, QUEST_FIRST_PATTERN);
}

public int
set_second_pattern(mixed who, int pattern)
{
    return set_info(who, QUEST_SECOND_PATTERN, pattern);
}

public int
query_second_pattern(mixed who)
{
    return get_info(who, QUEST_SECOND_PATTERN);
}

public int
set_third_pattern(mixed who, int pattern)
{
    return set_info(who, QUEST_THIRD_PATTERN, pattern);
}

public int
query_third_pattern(mixed who)
{
    return get_info(who, QUEST_THIRD_PATTERN);
}

public int
set_fourth_pattern(mixed who, int pattern)
{
    return set_info(who, QUEST_FOURTH_PATTERN, pattern);
}

public int
query_fourth_pattern(mixed who)
{
    return get_info(who, QUEST_FOURTH_PATTERN);
}

public int
set_fifth_pattern(mixed who, int pattern)
{
    return set_info(who, QUEST_FIFTH_PATTERN, pattern);
}

public int
query_fifth_pattern(mixed who)
{
    return get_info(who, QUEST_FIFTH_PATTERN);
}

/*
 * Function name: query_signal_pattern
 * Description:   Get all five signal patterns encoded as one value. A
 *                1 is prepended to allow for 0's at the start of the
 *                pattern, but it should be ignored/discarded otherwise.
 */
public int
query_signal_pattern(mixed who)
{
    int *bits = ({ 1 });

    bits += DEC2BIN(query_first_pattern(who))[1..];
    bits += DEC2BIN(query_second_pattern(who))[1..];
    bits += DEC2BIN(query_third_pattern(who))[1..];
    bits += DEC2BIN(query_fourth_pattern(who))[1..];
    bits += DEC2BIN(query_fifth_pattern(who))[1..];

    // Perhaps should check for overflow, but we'll assume that a pattern
    // will never be long enough for it to matter.

    return BIN2DEC(bits);
}

public int
set_suffix(mixed who, int suffix)
{
    return set_info(who, QUEST_SUFFIX, suffix);
}

public string
query_suffix(mixed who)
{
    return get_info(who, QUEST_SUFFIX);
}

public int
set_dug_waterfall(mixed who, string arg)
{
    return set_info(who, QUEST_DUG_WATERFALL, arg);
}

public string
query_dug_waterfall(mixed who)
{
    return get_info(who, QUEST_DUG_WATERFALL);
}

public int
set_read_journal(mixed who, string arg)
{
    return set_info(who, QUEST_READ_JOURNAL, arg);
}

public string
query_read_journal(mixed who)
{
    return get_info(who, QUEST_READ_JOURNAL);
}

public int
set_read_log(mixed who, string arg)
{
    return set_info(who, QUEST_READ_LOG, arg);
}

public string
query_read_log(mixed who)
{
    return get_info(who, QUEST_READ_LOG);
}


public int
set_triggered_beacon(mixed who, string arg)
{
    return set_info(who, QUEST_TRIG_BEACON, arg);
}

public string
query_triggered_beacon(mixed who)
{
    return get_info(who, QUEST_TRIG_BEACON);
}

public int
set_found_tower(mixed who, string arg)
{
    return set_info(who, QUEST_FOUND_TOWER, arg);
}

public string
query_found_tower(mixed who)
{
    return get_info(who, QUEST_FOUND_TOWER);
}


public int
set_lost_torque(mixed who, string arg)
{
    return set_info(who, QUEST_LOST_TORQUE, arg);
}

public string
query_lost_torque(mixed who)
{
    return get_info(who, QUEST_LOST_TORQUE);
}


/*
 * Function name:        assign_emblem_codes
 * Description  :        assign codes for both emblems to the
 *                       player save data, making sure that
 *                       the shapes are not the same.
 * Arguments    :        object player - the player object
 */
public void
assign_emblem_codes(object player)
{
    if (query_emblem_1(player))
    {
        return;
    }

    set_emblem_1(player, ONE_OF_LIST(EMBLEM_CODES));
    set_emblem_2(player, ONE_OF_LIST(EMBLEM_CODES));

    while(query_emblem_1(player) == query_emblem_2(player))
    {
        set_emblem_2(player, ONE_OF_LIST(EMBLEM_CODES));
    }

    return;
} /* assign_emblem_codes */


/*
 * Function name:        assign_spell
 * Description  :        assign the unification command word
 * Arguments    :        object player - the player object
 */
public void
assign_spell(object player)
{
    if (query_spell(player))
    {
        return;
    }

    set_spell(player, ONE_OF_LIST(SPELLS));

    return;
} /* assign_spell */


/*
 * Function name:        assign_password
 * Description  :        assign the password for the outposts
 * Arguments    :        object player - the player object
 */
public void
assign_password(object player)
{
    if (query_password(player))
    {
        return;
    }

    set_password(player, ONE_OF_LIST(PASSWORDS));

    return;
} /* assign_password */


/*
 * Function name:        assign_door_location
 * Description  :        assign a room to the player for the door
 *                       location
 * Arguments    :        object player - the player object
 */
public void
assign_door_location(object player)
{
    if (query_door_location(player))
    {
        return;
    }

    set_door_location(player, ONE_OF_LIST(DOOR_LOCATIONS));

    return;
} /* assign_door_location */


/*
 * Function name:        assign_suffix
 * Description  :        assign a suffix to the player
 * Arguments    :        object player - the player object
 */
public void
assign_suffix(object player)
{
    if (query_suffix(player))
    {
        return;
    }

    set_suffix(player, ONE_OF_LIST(SUFFICIES));
} /* assign_suffix */


/*
 * Function name:        assign_signal_pattern
 * Description  :        assign a signal pattern to the player
 * Arguments    :        object player - the player object
 */
public void
assign_signal_pattern(object player)
{
    if (query_first_pattern(player))
    {
        return;
    }

    set_first_pattern(player, ONE_OF_LIST(SIGNAL_PATTERNS));
    set_second_pattern(player, ONE_OF_LIST(SIGNAL_PATTERNS));
    set_third_pattern(player, ONE_OF_LIST(SIGNAL_PATTERNS));
    set_fourth_pattern(player, ONE_OF_LIST(SIGNAL_PATTERNS));
    set_fifth_pattern(player, ONE_OF_LIST(SIGNAL_PATTERNS));
} /* assign_signal_pattern */

