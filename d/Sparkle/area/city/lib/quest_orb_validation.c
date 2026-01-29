/*
 * /d/Sparkle/area/city/lib/quest_orb_validation.c
 *
 * These are the validation functions to see whether someone
 * is eligible for the quests in sparkle. Their names are specified
 * in /d/Sparkle/area/city/data/questdb/*.txt.
 *
 * This file is inherited by the quest orb, located in 
 * /d/Sparkle/area/city/obj/quest_orb.c
 *
 * Created April 2008, by Petros
 */
 
#include <macros.h>
#include "/d/Sparkle/sys/quests.h"

/*
 * Function name:        reverse_sequential
 * Description  :        Validation function to check bits that are used
 *                       in a sequential manner rather than bit by bit
 *                       individually. these are commonly used for tour
 *                       quests and any group of quests that must be
 *                       solved in sequence.
 * Arguments    :        player - person checking quest status
 *                       domain - domain to check bits in
 *                       args   - Arguments passed in, comman separated
 *                                1. Group
 *                                2. Begin Bit Number
 *                                3. End Bit Number
 *                                4. Value to confirm against (minimum)
 *                       set_bits - mapping of set bits
 * Returns      :        0/1/2 - don't show/not completed/completed
 */
public int
reverse_sequential(object player, string domain, string args,
                mapping set_bits)
{
    string * arguments;
    int num_bits, group, begin_bit, end_bit, minimum;
    int player_bits;
    
    arguments = explode(args, ",");
    // Arguments should be: group, begin bit, end bit, tour value
    if (sizeof(arguments) != 4)
    {
        return 0;
    }
    group = atoi(arguments[0]);
    begin_bit = atoi(arguments[1]);
    end_bit = atoi(arguments[2]);
    minimum = atoi(arguments[3]);
    
    num_bits = end_bit - begin_bit + 1;
    player_bits = 0;
    for (int index = 0; index < num_bits; ++index)
    {
        player_bits = player_bits << 1;
        if (player->test_bit(domain, group, begin_bit + index))
        {
            player_bits += 1;
        }
    }
    
    if (player_bits >= minimum)
    {
        for (int index = begin_bit; index <= end_bit; ++index)
        {
            set_bits[(group * 20) + index] = 0;
        }
        return 2;
    }
    
    return 1;
}

/*
 * Function name:        sequential_bits
 * Description  :        Validation function to check bits that are used
 *                       in a sequential manner rather than bit by bit
 *                       individually. these are commonly used for tour
 *                       quests and any group of quests that must be
 *                       solved in sequence.
 * Arguments    :        player - person checking quest status
 *                       domain - domain to check bits in
 *                       args   - Arguments passed in, comman separated
 *                                1. Group
 *                                2. Begin Bit Number
 *                                3. End Bit Number
 *                                4. Value to confirm against (minimum)
 *                       set_bits - mapping of set bits
 * Returns      :        0/1/2 - don't show/not completed/completed
 */
public int
sequential_bits(object player, string domain, string args,
                mapping set_bits)
{
    string * arguments;
    int num_bits, group, begin_bit, end_bit, minimum;
    int player_bits;
    
    arguments = explode(args, ",");
    // Arguments should be: group, begin bit, end bit, tour value
    if (sizeof(arguments) != 4)
    {
        return 0;
    }
    group = atoi(arguments[0]);
    begin_bit = atoi(arguments[1]);
    end_bit = atoi(arguments[2]);
    minimum = atoi(arguments[3]);
    
    num_bits = end_bit - begin_bit + 1;
    player_bits = 0;
    for (int index = num_bits - 1; index >= 0; --index)
    {
        player_bits = player_bits << 1;
        if (player->test_bit(domain, group, begin_bit + index))
        {
            player_bits += 1;
        }
    }
    
    if (player_bits >= minimum)
    {
        for (int index = begin_bit; index <= end_bit; ++index)
        {
            set_bits[(group * 20) + index] = 0;
        }
        return 2;
    }
    
    return 1;
}

/*
 * Function name:        in_area
 * Description  :        Validation function to check whether someone
 *                       should be able to see the quest that should
 *                       only be seen if they are in a particular area
 *                       For example, this is used for tutorial qusets
 *                       that should only been seen if someone is in
 *                       the tutorial
 * Arguments    :        player - person checking quest status
 * Returns      :        0/1 - should not see/should see
 */
public int
in_area(object player, string domain, string args, mapping set_bits)
{
    if (wildmatch(args + "*", 
                  MASTER_OB(environment(player))))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        in_guild
 * Description  :        Validation function to check whether someone
 *                       should be able to see the quest that should
 *                       only be seen if they are in a particular
 *                       guild
 * Arguments    :        player - person checking quest status
 *                       domain - domain being checked
 *                       set_bits - bits set in player
 * Returns      :        0/1 - should not see/should see
 */
public int
in_guild(object player, string domain, string args, mapping set_bits)
{
    if (player->query_guild_name_occ() == args)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        is_monk
 * Description  :        Validation function to check whether someone
 *                       should be able to see the Monk guru quest
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/0/1 - should not see/should see
 */
public int
is_monk(object player, string domain, string args, mapping set_bits)
{
    string * arguments;
    int group, bit;
    
    arguments = explode(args, ",");
    group = atoi(arguments[0]);
    bit = atoi(arguments[1]);
    if (player->test_bit (S_QUEST_DOMAIN_OLD, 1, 5))
    {
        set_bits[(group * 20) + bit] = 0;
        return -1;
    }
    
    if (player->query_guild_name_occ() == "Order of the Dragon")
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        is_knight
 * Description  :        Validation function to check whether someone
 *                       should be able to see the Monk guru quest
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/0/1 - should not see/should see
 */
public int
is_knight(object player)
{
    if (player->query_guild_name_occ() == "Solamnian Knights")
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        is_dragonarmy
 * Description  :        Validation function to check whether someone
 *                       should be able to see the Dragonarmy guru quest
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/0/1 - should not see/should see
 */
public int
is_dragonarmy(object player)
{
    if (player->query_guild_name_occ() == "Dragonarmy")
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        is_neidar
 * Description  :        Validation function to check whether someone
 *                       should be able to see the Neidar guru quest
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/0/1 - should not see/should see
 */
public int
is_neidar(object player)
{
    if (player->query_guild_name_occ() 
        == "Dwarven Warriors of the Neidar Clan")
    {
        return 1;
    }
    
    return 0;
}
  
public int
clean_fountain(object player)
{
    if (player->test_bit("krynn", 3, 17))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name:        false_unless_done
 * Description  :        Certain situations like Genesis domain quests
 *                       should always validate to false. That way,
 *                       they won't be shown unless they are completed.
 * Arguments    :        player - person checking quest status
 * Returns      :        0/1 - should not see/should see
 */
public int
false_unless_done(object player)
{
    return 0;
}

/*
 * Function name:        always_false
 * Description  :        Certain bits are used but should never be shown
 *                       These should use this validation function
 * Arguments    :        player - person checking quest status
 *                       domain - domain where bits are being checked
 *                       args - arguments
 *                       set_bits - mapping of set quest bits
 * Returns      :        0/1 - should not see/should see
 */
public int
always_false(object player, string domain, string args,
             mapping set_bits)
{
    string * arguments;
    int group, bit;
    
    // We set the bit to 0 so that when the final log gets
    // printed, we'll count this quest as one that's done.
    arguments = explode(args, ",");
    group = atoi(arguments[0]);
    bit = atoi(arguments[1]);
    set_bits[(group * 20) + bit] = 0;
    
    return -1;
}

/*
 * Function name:        old_orc_figurine
 * Description  :        An old Genesis domain quest. If player has
 *                       bit set in the Genesis domain, don't make
 *                       the Sparkle quest eligible
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/1 - should not see/should see
 */
public int
old_orc_figurine(object player)
{
    return (player->test_bit (S_QUEST_DOMAIN_OLD, 0, 0)) ? -1 : 1;
}

/*
 * Function name:        old_sacrifice_duck
 * Description  :        An old Genesis domain quest. If player has
 *                       bit set in the Genesis domain, don't make
 *                       the Sparkle quest eligible
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/1 - should not see/should see
 */
public int
old_sacrifice_duck(object player)
{
    return (player->test_bit (S_QUEST_DOMAIN_OLD, 0, 1)) ? -1 : 1;
}

/*
 * Function name:        old_dwarfheim_king
 * Description  :        An old Genesis domain quest. If player has
 *                       bit set in the Genesis domain, don't make
 *                       the Sparkle quest eligible
 * Arguments    :        player - person checking quest status
 * Returns      :        -1/1 - should not see/should see
 */
public int
old_dwarfheim_king(object player)
{
    return (player->test_bit (S_QUEST_DOMAIN_OLD, 2, 0)) ? -1 : 1;    
}

public int
can_do_prisoner_quest(object player)
{
    // the prisoner quest has 4 parts. Once you finish it, you
    // cannot go back and finish the unfinished parts. This will
    // remove the lines from the quest orb.
    if (player->test_bit("shire", 3, 14))
    {
        return 0;
    }
    
    return 1;
}

public int
is_riverstead_newbie(object player)
{
    // Riverstead only allows people who are below stat 50.
    if (player->query_average_stat() < 50)
    {
        return 1;
    }
    
    return 0;
}
