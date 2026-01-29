
 /*
  * Walkers Guild Council Code
  *
  * This code adapted from Maniac's code for the Calian Council
  *
  * by Jaacar, December 7th, 1997
  *
  */

#pragma save_binary

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include COUNCIL_HEADER
#include FIRE_HEADER

inherit WALKER_CODE;

#define EDIT "/obj/edit"
#define MESSAGE_MAX_CHARS 720
#define MIN_TIME_BETWEEN_EDITS 900
#define COUNCIL_S_EDITING "_council_s_editing"

string *council = ({ });
string *assistants = ({ });
mapping punishments = ([ ]);
mapping mentors = ([ ]);
string *fire_apprentices = ({ });
string *wind_apprentices = ({ });
string *wave_apprentices = ({ });
string *stone_apprentices = ({ });
string *spirit_apprentices = ({ });
string *fire_granted = ({ });
string *wind_granted = ({ });
string *wave_granted = ({ });
string *stone_granted = ({ });
string *spirit_granted = ({ });
string *fire_elders = ({ });
string *wind_elders = ({ });
string *wave_elders = ({ });
string *stone_elders = ({ });
string *spirit_elders = ({ });

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

void
remove_non_existant()
{
    int i;
    string *ind;

    restore_object(COUNCIL);
    for (i = 0; i < sizeof(council); i++)
        if (!SECURITY->exist_player(lower_case(council[i])))
            council[i] = "to_remove";

    council -= ({"to_remove"});
    ind = m_indexes(punishments);
    for (i = 0; i < sizeof(ind); i++)
        if (!SECURITY->exist_player(lower_case(ind[i])))
            punishments = m_delete(punishments, ind[i]);

    save_object(COUNCIL);
}

void
create()
{
    seteuid(getuid());
    restore_object(COUNCIL);
    set_alarm(1.0, 0.0, remove_non_existant);
}

string
query_council()
{
    string cstr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(council) == 0)
        cstr = "The Walkers Council does not currently have any members.\n";
    else if (sizeof(council) == 1)
        cstr = "The Walkers Council currently has the following member: "+
            capitalize(council[0]) + ".\n";
    else
    {
        cstr = "The Walkers Council currently has the following members: ";
        cstr += (COMPOSITE_WORDS(map(council, capitalize)) + ".\n");
    }

    return cstr;
}

string
query_assistants()
{
    string astr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(assistants) == 0)
        astr = "There are currently no assistants.\n";
    else if (sizeof(assistants) == 1)
        astr = "There is currently only one assistant: "+
            capitalize(assistants[0]) + ".\n";
    else
    {
        astr = "There are currently the following assistants: ";
        astr += (COMPOSITE_WORDS(map(assistants, capitalize)) + ".\n");
    }

    return astr;
}

string
query_mentors()
{
    string mstr;
    int x;
    mixed indices;
  
    seteuid(getuid());
    restore_object(COUNCIL);

    indices = m_indexes(mentors);
    if (!sizeof(indices))
        mstr = "There are currently no mentor/apprentice pairs.\n";
    else if (sizeof(indices) == 1)
    {
        mstr = "There is currently only one mentor/apprentice pair: ";
        mstr +=  capitalize(indices[0])+"/"+capitalize(mentors[indices[0]])+".\n";
    }
    else
    {
        mstr = "There are currently the following mentor/apprentice pairs:\n";
        for (x=0; x < sizeof(indices); x++)
            mstr += capitalize(indices[x]) + "/" +
                capitalize(mentors[indices[x]])+".\n";
    }

    return mstr;
}

string
query_fire_apprentices()
{
    string fastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(fire_apprentices) == 0)
        fastr = "There are currently no Pyros Apprentices.\n";
    else if (sizeof(fire_apprentices) == 1)
        fastr = "There is currently only one Pyros Apprentice: "+
            capitalize(fire_apprentices[0]) + ".\n";
    else
    {
        fastr = "There are currently the following Pyros Apprentices: ";
        fastr += (COMPOSITE_WORDS(map(fire_apprentices, capitalize)) + ".\n");
    }

    return fastr;
}

string
query_wind_apprentices()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wind_apprentices) == 0)
        wastr = "There are currently no Aeria Apprentices.\n";
    else if (sizeof(wind_apprentices) == 1)
        wastr = "There is currently only one Aeria Apprentice: "+
            capitalize(wind_apprentices[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Aeria Apprentices: ";
        wastr += (COMPOSITE_WORDS(map(wind_apprentices, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_wave_apprentices()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wave_apprentices) == 0)
        wastr = "There are currently no Diabrecho Apprentices.\n";
    else if (sizeof(wave_apprentices) == 1)
        wastr = "There is currently only one Diabrecho Apprentice: "+
            capitalize(wave_apprentices[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Diabrecho Apprentices: ";
        wastr += (COMPOSITE_WORDS(map(wave_apprentices, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_stone_apprentices()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(stone_apprentices) == 0)
        sastr = "There are currently no Gu Apprentices.\n";
    else if (sizeof(stone_apprentices) == 1)
        sastr = "There is currently only one Gu Apprentice: "+
            capitalize(stone_apprentices[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Gu Apprentices: ";
        sastr += (COMPOSITE_WORDS(map(stone_apprentices, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_spirit_apprentices()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(spirit_apprentices) == 0)
        sastr = "There are currently no Psuchae Apprentices.\n";
    else if (sizeof(spirit_apprentices) == 1)
        sastr = "There is currently only one Psuchae Apprentice: "+
            capitalize(spirit_apprentices[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Psuchae Apprentices: ";
        sastr += (COMPOSITE_WORDS(map(spirit_apprentices, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_fire_granted()
{
    string fastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(fire_granted) == 0)
        fastr = "There are currently no Firewalker Granted Members.\n";
    else if (sizeof(fire_granted) == 1)
        fastr = "There is currently only one Firewalker Granted Member: "+
            capitalize(fire_granted[0]) + ".\n";
    else
    {
        fastr = "There are currently the following Firewalker Granted Members: ";
        fastr += (COMPOSITE_WORDS(map(fire_granted, capitalize)) + ".\n");
    }

    return fastr;
}

string
query_wind_granted()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wind_granted) == 0)
        wastr = "There are currently no Windwalker Granted Members.\n";
    else if (sizeof(wind_granted) == 1)
        wastr = "There is currently only one Windwalker Granted Members: "+
            capitalize(wind_granted[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Windwalker Granted Members: ";
        wastr += (COMPOSITE_WORDS(map(wind_granted, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_wave_granted()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wave_granted) == 0)
        wastr = "There are currently no Wavewalker Granted Members.\n";
    else if (sizeof(wave_granted) == 1)
        wastr = "There is currently only one Wavewalker Granted Member: "+
            capitalize(wave_granted[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Wavewalker Granted Members: ";
        wastr += (COMPOSITE_WORDS(map(wave_granted, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_stone_granted()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(stone_granted) == 0)
        sastr = "There are currently no Stonewalker Granted Members.\n";
    else if (sizeof(stone_granted) == 1)
        sastr = "There is currently only one Stonewalker Granted Member: "+
            capitalize(stone_granted[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Stonewalker Granted Members: ";
        sastr += (COMPOSITE_WORDS(map(stone_granted, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_spirit_granted()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(spirit_granted) == 0)
        sastr = "There are currently no Spiritwalker Granted Members.\n";
    else if (sizeof(spirit_granted) == 1)
        sastr = "There is currently only one Spiritwalker Granted Member: "+
            capitalize(spirit_granted[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Spiritwalker Granted Members: ";
        sastr += (COMPOSITE_WORDS(map(spirit_granted, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_fire_elders()
{
    string fastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(fire_elders) == 0)
        fastr = "There are currently no Firewalker Elder Members.\n";
    else if (sizeof(fire_elders) == 1)
        fastr = "There is currently only one Firewalker Elder Member: "+
            capitalize(fire_elders[0]) + ".\n";
    else
    {
        fastr = "There are currently the following Firewalker Elder Members: ";
        fastr += (COMPOSITE_WORDS(map(fire_elders, capitalize)) + ".\n");
    }

    return fastr;
}

string
query_wind_elders()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wind_elders) == 0)
        wastr = "There are currently no Windwalker Elder Members.\n";
    else if (sizeof(wind_elders) == 1)
        wastr = "There is currently only one Windwalker Elder Members: "+
            capitalize(wind_elders[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Windwalker Elder Members: ";
        wastr += (COMPOSITE_WORDS(map(wind_elders, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_wave_elders()
{
    string wastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(wave_elders) == 0)
        wastr = "There are currently no Wavewalker Elder Members.\n";
    else if (sizeof(wave_elders) == 1)
        wastr = "There is currently only one Wavewalker Elder Member: "+
            capitalize(wave_elders[0]) + ".\n";
    else
    {
        wastr = "There are currently the following Wavewalker Elder Members: ";
        wastr += (COMPOSITE_WORDS(map(wave_elders, capitalize)) + ".\n");
    }

    return wastr;
}

string
query_stone_elders()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(stone_elders) == 0)
        sastr = "There are currently no Stonewalker Elder Members.\n";
    else if (sizeof(stone_elders) == 1)
        sastr = "There is currently only one Stonewalker Elder Member: "+
            capitalize(stone_elders[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Stonewalker Elder Members: ";
        sastr += (COMPOSITE_WORDS(map(stone_elders, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_spirit_elders()
{
    string sastr;
    int x;

    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(spirit_elders) == 0)
        sastr = "There are currently no Spiritwalker Elder Members.\n";
    else if (sizeof(spirit_elders) == 1)
        sastr = "There is currently only one Spiritwalker Elder Member: "+
            capitalize(spirit_elders[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Spiritwalker Elder Members: ";
        sastr += (COMPOSITE_WORDS(map(spirit_elders, capitalize)) + ".\n");
    }

    return sastr;
}

int
is_assistant(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);

    return (member_array(str,assistants) +1);
}

int
is_council_member(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);

    return (member_array(str,council) + 1);
}

int
is_fire_elder(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,fire_elders) + 1);
}

int
is_wind_elder(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wind_elders) + 1);
}

int
is_wave_elder(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wave_elders) + 1);
}

int
is_stone_elder(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,stone_elders) + 1);
}

int
is_spirit_elder(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,spirit_elders) + 1);
}

int
is_fire_granted(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,fire_granted) + 1);
}

int
is_wind_granted(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wind_granted) + 1);
}

int
is_wave_granted(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wave_granted) + 1);
}

int
is_stone_granted(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,stone_granted) + 1);
}

int
is_spirit_granted(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,spirit_granted) + 1);
}

int
is_fire_apprentice(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,fire_apprentices) + 1);
}

int
is_wind_apprentice(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wind_apprentices) + 1);
}

int
is_wave_apprentice(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,wave_apprentices) + 1);
}

int
is_stone_apprentice(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,stone_apprentices) + 1);
}

int
is_spirit_apprentice(string str)
{
    if (!str)
        return 0;
    str = lower_case(str);
    
    return (member_array(str,spirit_apprentices) + 1);
}

string
*query_all_assistants()
{
    return assistants;
}

string
*query_council_members()
{
    return council;
}

int
see_mentors(string str)
{
    TP->catch_msg(query_mentors());
    return 1;
}

int
see_assistants(string str)
{
    TP->catch_msg(query_assistants());
    return 1;
}

int
see_council(string str)
{
    TP->catch_msg(query_council());
    return 1;
}

int
see_fire_apprentices(string str)
{
    TP->catch_msg(query_fire_apprentices());
    return 1;
}

int
see_wind_apprentices(string str)
{
    TP->catch_msg(query_wind_apprentices());
    return 1;
}

int
see_wave_apprentices(string str)
{
    TP->catch_msg(query_wave_apprentices());
    return 1;
}

int
see_stone_apprentices(string str)
{
    TP->catch_msg(query_stone_apprentices());
    return 1;
}

int
see_spirit_apprentices(string str)
{
    TP->catch_msg(query_spirit_apprentices());
    return 1;
}

int
see_fire_granted(string str)
{
    TP->catch_msg(query_fire_granted());
    return 1;
}

int
see_wind_granted(string str)
{
    TP->catch_msg(query_wind_granted());
    return 1;
}

int
see_wave_granted(string str)
{
    TP->catch_msg(query_wave_granted());
    return 1;
}

int
see_stone_granted(string str)
{
    TP->catch_msg(query_stone_granted());
    return 1;
}

int
see_spirit_granted(string str)
{
    TP->catch_msg(query_spirit_granted());
    return 1;
}

int
see_fire_elders(string str)
{
    TP->catch_msg(query_fire_elders());
    return 1;
}

int
see_wind_elders(string str)
{
    TP->catch_msg(query_wind_elders());
    return 1;
}

int
see_wave_elders(string str)
{
    TP->catch_msg(query_wave_elders());
    return 1;
}

int
see_stone_elders(string str)
{
    TP->catch_msg(query_stone_elders());
    return 1;
}

int
see_spirit_elders(string str)
{
    TP->catch_msg(query_spirit_elders());
    return 1;
}

int
add_council_member(string str)
{
    object target;
    string adder;

    if (!str)
        return 0;

    adder = TP->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);
    if (sizeof(council) >= COUNCIL_MAX_SIZE)
    {
        NF("The Walkers Council is full.\n");
        return 0;
    }

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(TP))
    {
        if (member_array(str, council) >= 0)
        {
            NF(capitalize(str) + " is already a member of the "+
                "Walkers Council.\n");
            return 0;
        }
        council += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been added to the Walkers "+
            "Council by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target = find_player(str))
        {
            target->set_skill(SS_WALKER_CHOSEN, ALL_SPELL_LEVELS);
            target->set_guild_pref(SS_OCCUP, TP->query_guild_tax_occ());
            tell_object(target,"You have been added to the Walkers "+
                "Council.\n");
        }
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
add_assistant(string str)
{
    object target;
    string adder;

    if (!str)
        return 0;

    adder = TP->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(TP))
    {
        if (member_array(str, assistants) >= 0)
        {
            NF(capitalize(str) + " is already an assistant.\n");
            return 0;
        }
        assistants += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been added to the Walkers "+
            "Council Assistants by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target = find_player(str))
        {
            target->set_skill(SS_WALKER_CHOSEN, ALL_SPELL_LEVELS);
            target->set_guild_pref(SS_OCCUP, TP->query_guild_tax_occ());
            tell_object(target,"You are now an assistant to the Walkers "+
                "Council.\n");
        }
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
remove_council_member(string str)
{
    object target;
    string remover;

    if (!str)
        return 0;

    remover = TP->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);

    if (sizeof(council) == 0)
    {
        NF("There is nobody on the Walkers Council!\n");
        return 0;
    }

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP))
    {
        if (member_array(str, council) > -1)
        {
            council -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been removed from the Walkers "+
                "Council by " + capitalize(remover) + ".\n");
            write("Ok.\n");
            if (target = find_player(str))
            {
                tell_object(target,"You have been removed from the "+
                    "Walkers Council.\n");
                target->set_skill(SS_WALKER_CHOSEN,1);
            }
            return 1;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
remove_assistant(string str)
{
    object target;
    string remover;

    if (!str)
        return 0;

    remover = TP->query_real_name();
    str = lower_case(str);
    seteuid(getuid());
    restore_object(COUNCIL);

    if (sizeof(assistants) == 0)
    {
        NF("There are no assistants to remove!\n");
        return 0;
    }

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP))
    {
        if (member_array(str, assistants) > -1)
        {
            assistants -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been removed from the Walkers "+
                "Council Assistants by " + capitalize(remover) + ".\n");
            write("Ok.\n");
            if (target = find_player(str))
            {
                tell_object(target,"You are no longer an assistant to the "+
                    "Walkers Council.\n");
            }
            return 1;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
is_spell_banned(object player)
{
    if (player->query_skill(SS_WALKER_PUNISHMENT) == SPELL_BANNED)
        return 1;
    else
        return 0;
}

int
is_train_banned(object player)
{
    if (player->query_skill(SS_WALKER_PUNISHMENT) == TRAIN_BANNED)
        return 1;
    else
        return 0;
}

int
is_expelled(object player)
{
    if (player->query_skill(SS_WALKER_PUNISHMENT) == EXPELLED)
        return 1;
    else
        return 0;
}

void
a_message(object player, string message)
{
    player->catch_msg(message);
}

void
exec_stop_train(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    if (is_walker(player))
    {
        player->set_skill(SS_WALKER_PUNISHMENT, TRAIN_BANNED);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Walkers Council from "+
            "using the guilds training facilities.\n"}));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_stop_spells(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    if (is_walker(player))
    {
        player->set_skill(SS_WALKER_PUNISHMENT, SPELL_BANNED);
        present("walker_spells",player)->remove_object();
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Walkers Council from "+
            "using your spells.\n"}));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_expel_player(object player)
{
    string player_name;

    seteuid(getuid());
    player_name = player->query_real_name();
    player->set_skill(SS_WALKER_PUNISHMENT, EXPELLED);
    if (is_walker(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been expelled from the Walkers guild "+
            "by the Walkers Council.\n"}));
        player->move_living("X",player->query_default_start_location(),0,1);
        player->command("renounce my oath");
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_remove_punish(object player)
{
    string player_name;

    seteuid(getuid());
    restore_object(COUNCIL);
    player_name = player->query_real_name();
    player->set_skill(SS_WALKER_PUNISHMENT,NO_PUNISHMENT);
    present("walker_spells",player)->activate_spells();
    set_alarmv(1.5, 0.0, "a_message", ({ player,
        "The Walkers Council has removed any punishments "+
        "that have previously been placed on you.\n"}));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
carry_out_punishments(object player)
{
    string player_name;

    player_name = player->query_real_name();
    seteuid(getuid());
    restore_object(COUNCIL);

    if (punishments[player_name])
    {
        if (punishments[player_name] == REMOVE_PUNISHMENTS)
        {
            if (player->query_skill(SS_WALKER_PUNISHMENT) != NO_PUNISHMENT)
            exec_remove_punish(player);
        }
        else if (punishments[player_name] == TRAIN_BANNED)
            exec_stop_train(player);
        else if (punishments[player_name] == SPELL_BANNED)
            exec_stop_spells(player);
        else if (punishments[player_name] == EXPELLED)
            exec_expel_player(player);
    }
}

void
add_punishment(string punished, int punishment)
{
    seteuid(getuid());
    restore_object(COUNCIL);
    if (punishments[punished])
        punishments = m_delete(punishments, punished);
    punishments += ([ punished : punishment ]);
    save_object(COUNCIL);
}

int
record_stop_train(string str)
{
    object player;
    string banner;

    if (!stringp(str))
    {
        NF("Stop who from training?\n");
        return 0;
    }

    banner = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(banner) || is_calian_wiz(TP))
    {
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, TRAIN_BANNED);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has banned " + capitalize(str) +
                " from using the guild's training facilities.\n");
            write("Ok.\n");
            return 1;
        }
        else if (is_walker(player))
        {
            exec_stop_train(player);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has banned " + capitalize(str) +
                " from using the guild's training facilities.\n");
            write("Ok.\n");
            return 1;
        }
        else
        {
            NF("Either the player doesn't exist, or isn't a Walker.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
record_stop_spells(string str)
{
    object player;
    string banner;

    if (!stringp(str))
    {
        NF("Stop who from using spells?\n");
        return 0;
    }

    banner = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(banner) || is_calian_wiz(TP))
    {
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, SPELL_BANNED);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has banned " + capitalize(str) +
                " from using their spells.\n");
            write("Ok.\n");
            return 1;
        }
        else if (is_walker(player))
        {
            exec_stop_spells(player);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has banned " + capitalize(str) +
                " from using their spells.\n");
            write("Ok.\n");
            return 1;
        }
        else
        {
            NF("Either the player doesn't exist, or isn't a Walker.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
record_expel_player(string str)
{
    object player;
    string banner;

    if (!stringp(str))
    {
        NF("Expel who from the guild?\n");
        return 0;
    }

    banner = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(banner) || is_calian_wiz(TP))
    {
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, EXPELLED);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has expelled " + capitalize(str) +
                " from the guild.\n");
            write("Ok.\n");
            return 1;
        }
        else if (is_walker(player))
        {
            exec_expel_player(player);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has expelled " + capitalize(str) +
                " from the guild.\n");
            write("Ok.\n");
            return 1;
        }
        else
        {
            NF("Either the player doesn't exist, or isn't a Walker.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
record_remove_punish(string str)
{
    object player;
    string banner;

    if (!stringp(str))
    {
        NF("Remove punishment from who?\n");
        return 0;
    }

    banner = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(banner) || is_calian_wiz(TP))
    {
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, REMOVE_PUNISHMENTS);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has removed all punishments "+
                "from " + capitalize(str) + ".\n");
            write("Ok.\n");
            return 1;
        }
        else if (is_walker(player))
        {
            exec_remove_punish(player);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has removed all punishements "+
                "from " + capitalize(str) + ".\n");
            write("Ok.\n");
            return 1;
        }
        else
        {
            NF("Either the player doesn't exist, or isn't a Walker.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

int
filter_string(mixed s)
{
    return stringp(s);
}

