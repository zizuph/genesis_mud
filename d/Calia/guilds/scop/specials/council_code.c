
 /*
  * Spirit Circle Guild Council Code
  *
  * This code adapted from Maniac's code for the Calian Council
  *
  * by Jaacar, July 24th, 2003
  *
  */

/* Navarre November 18th 2006, Allowed GUILD_MASTER to do the same as calian wizards */

#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include COUNCIL_HEADER
#include SPIRIT_HEADER

#define EDIT "/obj/edit"
#define MESSAGE_MAX_CHARS 720
#define MIN_TIME_BETWEEN_EDITS 900
#define COUNCIL_S_EDITING "_council_s_editing"
#define STATUE_CHAMBER "/d/Calia/guilds/scop/temple/statue_chamber"

string *council = ({ });
string *speakers = ({ });
string *templebanned = ({ });
mapping punishments = ([ ]);
mapping mentors = ([ ]);

/* guild levels */
string *spirit_apprentices = ({ });
string *spirit_masters = ({ });
string *spirit_elders = ({ });

/* leader titles */
string theurgist = "";
string archon = "";
string patriarch = "";

/* special titles */
string liberator = "";
string cultivator = "";
string beacon = "";
string missionary = "";
string emissary = "";
string luminary = "";
string *conservators = ({ });
string illuminati = "";
string intercessor = "";

mixed
is_calian_wiz(object tp)
{
    return SECURITY->query_wiz_dom(tp->query_real_name()) == "Calia";
}

int
is_spirit(object player)
{
    return player->query_skill(SS_SPIRIT_CHOSEN);
}


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

    for (i = 0; i < sizeof(council); i++)
        if (!SECURITY->exist_player(lower_case(council[i])))
            council[i] = "to_remove";

    council -= ({"to_remove"});
    ind = m_indexes(punishments);
    for (i = 0; i < sizeof(ind); i++)
        if (!SECURITY->exist_player(lower_case(ind[i])))
        {
            punishments = m_delete(punishments, ind[i]);
            find_player("jaacar")->catch_msg("Removed a player from the guild.\n");
        }

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

    if (sizeof(council) == 0)
        cstr = "The Spirit Circle Council does not currently have any members.\n";
    else if (sizeof(council) == 1)
        cstr = "The Spirit Circle Council currently has the following member: "+
            capitalize(council[0]) + ".\n";
    else
    {
        cstr = "The Spirit Circle Council currently has the following members: ";
        cstr += (COMPOSITE_WORDS(map(council, capitalize)) + ".\n");
    }

    return cstr;
}

string
query_speakers()
{
    string sstr;
    int x;

    if (sizeof(speakers) == 0)
        sstr = "There are no approved Speakers at this time.\n";
    else if (sizeof(speakers) == 1)
        sstr = "There is only one approved Speaker at this time: "+
            capitalize(speakers[0]) + ".\n";
    else
    {
        sstr = "The following people are approved Speakers: ";
        sstr += (COMPOSITE_WORDS(map(speakers, capitalize)) + ".\n");
    }

    return sstr;
}

string
query_temple_banned()
{
    string sstr;
    int x;

    if (sizeof(templebanned) == 0)
        sstr = "There is nobody banned from the temple at this time.\n";
    else if (sizeof(templebanned) == 1)
        sstr = "There is only one person banned from the temple at this time: "+
            capitalize(templebanned[0]) + ".\n";
    else
    {
        sstr = "The following people are banned from the temple: ";
        sstr += (COMPOSITE_WORDS(map(templebanned, capitalize)) + ".\n");
    }

    return sstr;
}

string
query_mentors()
{
    string mstr;
    int x;
    mixed indices;
  
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
query_spirit_apprentices()
{
    string sastr;
    int x;

    if (sizeof(spirit_apprentices) == 0)
        sastr = "There are currently no Spirit Circle Apprentices.\n";
    else if (sizeof(spirit_apprentices) == 1)
        sastr = "There is currently only one Spirit Circle Apprentice: "+
            capitalize(spirit_apprentices[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Spirit Circle Apprentices: ";
        sastr += (COMPOSITE_WORDS(map(spirit_apprentices, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_spirit_masters()
{
    string sastr;
    int x;

    if (sizeof(spirit_masters) == 0)
        sastr = "There are currently no Spirit Circle Master Members.\n";
    else if (sizeof(spirit_masters) == 1)
        sastr = "There is currently only one Spirit Circle Master Member: "+
            capitalize(spirit_masters[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Spirit Circle Master Members: ";
        sastr += (COMPOSITE_WORDS(map(spirit_masters, capitalize)) + ".\n");
    }

    return sastr;
}

/*
 * Function:    query_spirit_elders_list
 * Description: Returns a copy of the list of Spirit Elders
 */
string *
query_spirit_elders_list()
{
    return spirit_elders + ({ });
}

string
query_spirit_elders()
{
    string sastr;
    int x;

    if (sizeof(spirit_elders) == 0)
        sastr = "There are currently no Spirit Circle Elder Members.\n";
    else if (sizeof(spirit_elders) == 1)
        sastr = "There is currently only one Spirit Circle Elder Member: "+
            capitalize(spirit_elders[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Spirit Circle Elder Members: ";
        sastr += (COMPOSITE_WORDS(map(spirit_elders, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_liberator()
{
    string lstr;
    int x;

    if (!strlen(liberator))
        lstr = "There is currently no Liberator of Souls.\n";
    else 
        lstr = "The current Liberator of Souls is "+capitalize(liberator)+".\n";
    return lstr;
}

string
query_cultivator()
{
    string lstr;
    int x;

    if (!strlen(cultivator))
        lstr = "There is currently no Cultivator of Life.\n";
    else 
        lstr = "The current Cultivator of Life is "+capitalize(cultivator)+".\n";
    return lstr;
}

string
query_beacon()
{
    string lstr;
    int x;

    if (!strlen(beacon))
        lstr = "There is currently no Beacon of Spirits.\n";
    else 
        lstr = "The current Beacon of Spirits is "+capitalize(beacon)+".\n";
    return lstr;
}

string
query_missionary()
{
    string lstr;
    int x;

    if (!strlen(missionary))
        lstr = "There is currently no Missionary of the Spirit Circle.\n";
    else 
        lstr = "The current Missionary of the Spirit Circle is "+
            capitalize(missionary)+".\n";
    return lstr;
}

string
query_emissary()
{
    string lstr;
    int x;

    if (!strlen(emissary))
        lstr = "There is currently no Emissary.\n";
    else 
        lstr = "The current Emissary is "+capitalize(emissary)+".\n";
    return lstr;
}

string
query_luminary()
{
    string lstr;
    int x;

    if (!strlen(luminary))
        lstr = "There is currently no Luminary of the Spirit Circle.\n";
    else 
        lstr = "The current Luminary of the Spirit Circle is "+
            capitalize(luminary)+".\n";
    return lstr;
}

string
query_conservators()
{
    string sastr;
    int x;

    if (sizeof(conservators) == 0)
        sastr = "There are currently no Conservators of Armaments.\n";
    else if (sizeof(conservators) == 1)
        sastr = "There is currently only one Conservator of Armaments: "+
            capitalize(conservators[0]) + ".\n";
    else
    {
        sastr = "There are currently the following Conservators of Armaments: ";
        sastr += (COMPOSITE_WORDS(map(conservators, capitalize)) + ".\n");
    }

    return sastr;
}

string
query_illuminati()
{
    string lstr;
    int x;

    if (!strlen(illuminati))
        lstr = "There is currently no Illuminati.\n";
    else 
        lstr = "The current Illuminati is "+capitalize(illuminati)+".\n";
    return lstr;
}

string
query_intercessor()
{
    string lstr;
    int x;

    if (!strlen(intercessor))
        lstr = "There is currently no Intercessor of the Spirit Circle.\n";
    else 
        lstr = "The current Intercessor of the Spirit Circle is "+
            capitalize(intercessor)+".\n";
    return lstr;
}

string
query_theurgist()
{
    string lstr;
    int x;

    if (!strlen(theurgist))
        lstr = "There is currently no Archon of Revelation.\n";
    else 
        lstr = "The current Archon of Revelation is "+capitalize(theurgist)+".\n";
    return lstr;
}

string
query_archon()
{
    string lstr;
    int x;

    if (!strlen(archon))
        lstr = "There is currently no Archon of Deliverance.\n";
    else 
        lstr = "The current Archon of Deliverance is "+capitalize(archon)+".\n";
    return lstr;
}

string
query_patriarch()
{
    string lstr;
    int x;

    if (!strlen(patriarch))
        lstr = "There is currently no Archon of Apotheosis.\n";
    else 
        lstr = "The current Archon of Apotheosis is "+capitalize(patriarch)+".\n";
    return lstr;
}

public int
is_patriarch(string str)
{
    if (!str)
        return 0;

    return (lower_case(patriarch) == lower_case(str));
}

public int
is_archon(string str)
{
    if (!str)
        return 0;

    return (lower_case(archon) == lower_case(str));
}

public int
is_theurgist(string str)
{
    if (!str)
        return 0;

    return (lower_case(theurgist) == lower_case(str));
}

public int
is_liberator(string str)
{
    if (!str)
        return 0;

    return (lower_case(liberator) == lower_case(str));
}

public int
is_cultivator(string str)
{
    if (!str)
        return 0;

    return (lower_case(cultivator) == lower_case(str));
}

public int
is_beacon(string str)
{
    if (!str)
        return 0;

    return (lower_case(beacon) == lower_case(str));
}

public int
is_missionary(string str)
{
    if (!str)
        return 0;

    return (lower_case(missionary) == lower_case(str));
}

public int
is_emissary(string str)
{
    if (!str)
        return 0;

    return (lower_case(emissary) == lower_case(str));
}

public int
is_luminary(string str)
{
    if (!str)
        return 0;

    return (lower_case(luminary) == lower_case(str));
}

int
is_conservator(string str)
{
    if (!str)
        return 0;

    str = lower_case(str);

    return (member_array(str,conservators) + 1);
}

public int
is_illuminati(string str)
{
    if (!str)
        return 0;

    return (lower_case(illuminati) == lower_case(str));
}

public int
is_intercessor(string str)
{
    if (!str)
        return 0;

    return (lower_case(intercessor) == lower_case(str));
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
is_spirit_elder(string str)
{
    if (!str)
        return 0;

    str = lower_case(str);
    
    return (member_array(str,spirit_elders) + 1);
}

int
is_spirit_master(string str)
{
    if (!str)
        return 0;

    str = lower_case(str);
    
    return (member_array(str,spirit_masters) + 1);
}

int
is_spirit_apprentice(string str)
{
    if (!str)
        return 0;

    str = lower_case(str);
    
    return (member_array(str,spirit_apprentices) + 1);
}

int
is_temple_banned(string str)
{
    if (!str)
        return 0;

    str = lower_case(str);
    
    return (member_array(str,templebanned) + 1);
}

string
*query_council_members()
{
    return council;
}

string
*query_approved_speakers()
{
    return speakers;
}

string
*query_templebanned()
{
    return templebanned;
}

int
see_mentors(string str)
{
    TP->catch_msg(query_mentors());
    return 1;
}

int
see_liberator(string str)
{
    TP->catch_msg(query_liberator());
    return 1;
}

int
see_cultivator(string str)
{
    TP->catch_msg(query_cultivator());
    return 1;
}

int
see_beacon(string str)
{
    TP->catch_msg(query_beacon());
    return 1;
}

int
see_missionary(string str)
{
    TP->catch_msg(query_missionary());
    return 1;
}

int
see_emissary(string str)
{
    TP->catch_msg(query_emissary());
    return 1;
}

int
see_luminary(string str)
{
    TP->catch_msg(query_luminary());
    return 1;
}

int
see_conservators(string str)
{
    TP->catch_msg(query_conservators());
    return 1;
}

int
see_illuminati(string str)
{
    TP->catch_msg(query_illuminati());
    return 1;
}

int
see_intercessor(string str)
{
    TP->catch_msg(query_intercessor());
    return 1;
}

int
see_theurgist(string str)
{
    TP->catch_msg(query_theurgist());
    return 1;
}

int
see_archon(string str)
{
    TP->catch_msg(query_archon());
    return 1;
}

int
see_patriarch(string str)
{
    TP->catch_msg(query_patriarch());
    return 1;
}

int
see_council(string str)
{
    TP->catch_msg(query_council());
    return 1;
}

int
see_speakers(string str)
{
    TP->catch_msg(query_speakers());
    return 1;
}

int
see_temple_banned(string str)
{
    TP->catch_msg(query_temple_banned());
    return 1;
}

int
see_spirit_apprentices(string str)
{
    TP->catch_msg(query_spirit_apprentices());
    return 1;
}

int
see_spirit_masters(string str)
{
    TP->catch_msg(query_spirit_masters());
    return 1;
}

int
see_spirit_elders(string str)
{
    TP->catch_msg(query_spirit_elders());
    return 1;
}

varargs int
add_council_member(string str, string promoter)
{
    object target;
    string adder;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = TP->query_real_name();
    }
    
    str = lower_case(str);

    if (sizeof(council) >= COUNCIL_MAX_SIZE)
    {
        NF("The Spirit Circle Council is full.\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, council) >= 0)
        {
            NF(capitalize(str) + " is already a member of the "+
                "Spirit Circle Council.\n");
            return 0;
        }
        council += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been added to the Spirit Circle "+
            "Council by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target = find_player(str))
        {
            tell_object(target,"You have been added to the Spirit Circle "+
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
add_speaker(string str)
{
    object target;
    string adder;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    adder = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, speakers) >= 0)
        {
            NF(capitalize(str) + " is already an approved Speaker.\n");
            return 0;
        }
        speakers += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been added to the Speakers by "+
            capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target = find_player(str))
        {
            tell_object(target,"You have been added to the Spirit Circle "+
                "approved Speakers.\n");
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
add_temple_banned(string str)
{
    object target;
    string adder;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    adder = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, templebanned) >= 0)
        {
            NF(capitalize(str) + " is already banned from the temple.\n");
            return 0;
        }
        templebanned += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been banned from the temple by "+
            capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
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

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    remover = TP->query_real_name();
    str = lower_case(str);

    if (sizeof(council) == 0)
    {
        NF("There is nobody on the Spirit Circle Council!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, council) > -1)
        {
            council -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been removed from the Spirit Circle "+
                "Council by " + capitalize(remover) + ".\n");
            write("Ok.\n");
            if (target = find_player(str))
            {
                tell_object(target,"You have been removed from the "+
                    "Spirit Circle Council.\n");
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
remove_speaker(string str)
{
    object target;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    remover = TP->query_real_name();
    str = lower_case(str);

    if (sizeof(speakers) == 0)
    {
        NF("There are no approved Speakers.\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, speakers) > -1)
        {
            speakers -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been removed from the Speakers by " + 
                capitalize(remover) + ".\n");
            write("Ok.\n");
            if (target = find_player(str))
            {
                tell_object(target,"You have been removed from the "+
                    "Spirit Circle approved Speakers.\n");
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
remove_temple_banned(string str)
{
    object target;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    remover = TP->query_real_name();
    str = lower_case(str);

    if (sizeof(templebanned) == 0)
    {
        NF("There is nobody banned from the temple.\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, templebanned) > -1)
        {
            templebanned -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been allowed back in the temple by " + 
                capitalize(remover) + ".\n");
            write("Ok.\n");
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
remove_mentor(string str)
{
    object target;
    string remover;
    string apprentice;
    mixed indices;

    remover = TP->query_real_name();
    str = lower_case(str);

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    indices = m_indexes(mentors);

    if (!sizeof(indices))
    {
        NF("There are currently no mentor/apprentice pairs.\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (apprentice = mentors[str]) 
        { 
            mentors = m_delete(mentors, str); 
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str)+"/"+capitalize(apprentice)+
                " has been removed as an apprentice/mentor pairing by "+
                capitalize(remover) + ".\n");
            save_object(COUNCIL);
            write("Ok.\n");
                
            if (target = find_player(str))
            {
                tell_object(target,"Your Apprentice has been removed "+
                    "from you by the Spirit Circle Council.\n");
            }
            return 1;
        } 
        else 
        { 
            NF("There is no apprentice for that mentor.\n"); 
            return 0;
        }

    }
        
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

varargs int
set_liberator(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == liberator)
        {
            NF(capitalize(str) + " is already the Liberator of Souls!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Liberator of Souls.\n");
            return 0;
        }

        liberator = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Liberator of Souls by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Liberator "+
                "of Souls.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_cultivator(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == cultivator)
        {
            NF(capitalize(str) + " is already the Cultivator of Life!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Cultivator of Life.\n");
            return 0;
        }

        cultivator = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Cultivator of Life by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Cultivator "+
                "of Life.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_beacon(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == beacon)
        {
            NF(capitalize(str) + " is already the Beacon of Spirits!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Beacon of Spirits.\n");
            return 0;
        }

        beacon = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Beacon of Spirits by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Beacon "+
                "of Spirits.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_missionary(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == missionary)
        {
            NF(capitalize(str) + " is already the Missionary of the Spirit "+
               "Circle!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Missionary of the Spirit Circle.\n");
            return 0;
        }

        missionary = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Missionary of the Spirit Circle "+
         "by " +capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Missionary "+
                "of the Spirit Circle.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_emissary(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == emissary)
        {
            NF(capitalize(str) + " is already the Emissary!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Emissary.\n");
            return 0;
        }

        emissary = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Emissary by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Emissary.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_luminary(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == luminary)
        {
            NF(capitalize(str) + " is already the Luminary of the Spirit "+
               "Circle!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Luminary of the Spirit Circle.\n");
            return 0;
        }

        luminary = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Luminary of the Spirit Circle "+
         "by " +capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Luminary "+
                "of the Spirit Circle.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
add_conservator(string str, string promoter)
{
    object target;
    string adder;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = TP->query_real_name();
    }

    str = lower_case(str);

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, conservators) >= 0)
        {
            NF(capitalize(str) + " is already a Conservator of Armaments.\n");
            return 0;
        }
        conservators += ({ str });
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been added to the Conservators of "+
            "Armaments by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        if (target = find_player(str))
        {
            tell_object(target,"You have been added to the Conservators of "+
                "Armaments.\n");
        }
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

varargs int
set_illuminati(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == illuminati)
        {
            NF(capitalize(str) + " is already the Illuminati!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Illuminati.\n");
            return 0;
        }

        illuminati = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Illuminati by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Illuminati.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_intercessor(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    adder = tp->query_real_name();
    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == intercessor)
        {
            NF(capitalize(str) + " is already the Intercessor of the Spirit "+
               "Circle!\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice and cannot hold "+
               "the title of Intercessor of the Spirit Circle.\n");
            return 0;
        }

        intercessor = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Intercessor of the Spirit Circle "+
         "by " + capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Intercessor "+
                "of the Spirit Circle.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_theurgist(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == theurgist)
        {
            NF(capitalize(str) + " is already the Archon of Revelation!\n");
            return 0;
        }

        if (!(member_array(str, spirit_elders) >= 0))
        {
            NF(capitalize(str) + " is not in the Elder ranking. "+
               "If you wish to make this person Archon of Revelation, promote "+
               "them to Elder ranking first.\n");
            return 0;
        }

        if (str == patriarch)
            patriarch = "";
        if (str == archon)
            archon = "";
        
        theurgist = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Archon of Revelation by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Archon of Revelation.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_archon(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str) 
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == archon)
        {
            NF(capitalize(str) + " is already the Archon of Deliverance!\n");
            return 0;
        }

        if (!(member_array(str, spirit_elders) >= 0))
        {
            NF(capitalize(str) + " is not in the Elder ranking. "+
               "If you wish to make this person Archon of Deliverance, promote "+
               "them to Elder ranking first.\n");
            return 0;
        }

        if (str == patriarch)
            patriarch = "";
        if (str == theurgist)
            theurgist = "";
        
        archon = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Archon of Deliverance by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been given the title of Archon of Deliverance.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

varargs int
set_patriarch(string str, string promoter)
{
    object tp = TP; 
    object target;
    string adder;

    if (!str)
        return 0;

    if (! (SECURITY->exist_player(str)) )
    {
        NF("No such player!\n");
        return 0;
    }

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = tp->query_real_name();
    }

    str = lower_case(str);
    target = find_player(str);

    if (is_council_member(adder) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER)
    {
        if (str == patriarch)
        {
            NF(capitalize(str) + " is already the Archon of Apotheosis!\n");
            return 0;
        }

        if (!(member_array(str, spirit_elders) >= 0))
        {
            NF(capitalize(str) + " is not in the Elder ranking. "+
               "If you wish to make this person Archon of Apotheosis, promote "+
               "them to Elder ranking first.\n");
            return 0;
        } 

        if (str == archon)
            archon = "";
        if (str == theurgist)
            theurgist = "";

        patriarch = str;
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() + 
         capitalize(str) + " has been set to Archon of Apotheosis by " + 
         capitalize(adder) + ".\n");
        save_object(COUNCIL);

        if (target = find_player(str))
        {
            tell_object(target,"You have been give the title of Archon of Apotheosis.\n");
            target->query_spirit_circle_title();
            target->query_spirit_circle_level();
        }

        write("Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_liberator(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(liberator))
    {
         NF("There is no Liberator of Souls yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == liberator)
        {
            liberator = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Liberator of "+
               "Souls by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Liberator of Souls!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_cultivator(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(cultivator))
    {
         NF("There is no Cultivator of Life yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == cultivator)
        {
            cultivator = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Cultivator of "+
               "Life by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Cultivator of Life!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_beacon(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(beacon))
    {
         NF("There is no Beacon of Spirits yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == beacon)
        {
            beacon = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Beacon of "+
               "Spirits by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Beacon of Spirits!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_missionary(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(missionary))
    {
         NF("There is no Missionary of the Spirit Circle yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER ) 
    { 
        if (str == missionary)
        {
            missionary = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Missionary of "+
               "the Spirit Circle by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Missionary of the Spirit Circle!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_emissary(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(emissary))
    {
         NF("There is no Emissary yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER ) 
    { 
        if (str == emissary)
        {
            emissary = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Emissary "+
               "by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Emissary!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_luminary(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(luminary))
    {
         NF("There is no Luminary of the Spirit Circle yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == luminary)
        {
            luminary = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Luminary of "+
               "the Spirit Circle by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Luminary of the Spirit Circle!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_conservator(string str)
{
    object target;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
    {
        NF("There is no such player!\n");
        return 0;
    }

    remover = TP->query_real_name();
    str = lower_case(str);

    if (sizeof(conservators) == 0)
    {
        NF("There are no Conservators of the Armaments!\n");
        return 0;
    }

    if (is_council_member(remover) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, conservators) > -1)
        {
            conservators -= ({ str });
            save_object(COUNCIL);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(str) + " has been removed from the Conservators "+
                "of the Armaments by " + capitalize(remover) + ".\n");
            write("Ok.\n");
            if (target = find_player(str))
            {
                tell_object(target,"You have been removed from the "+
                    "Conservators of the Armaments.\n");
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
remove_illuminati(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(illuminati))
    {
         NF("There is no Illuminati yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == illuminati)
        {
            illuminati = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Illuminati "+
               "by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Illuminati!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_intercessor(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(intercessor))
    {
         NF("There is no Intercessor of the Spirit Circle yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == intercessor)
        {
            intercessor = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Intercessor of "+
               "the Spirit Circle by " + capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Intercessor of the Spirit Circle!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_theurgist(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(theurgist))
    {
         NF("There is no Archon of Revelation yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == theurgist)
        {
            theurgist = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Archon of Revelation by " + 
               capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Archon of Revelation!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_archon(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(archon))
    {
         NF("There is no Archon of Deliverance yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == archon)
        {
            archon = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Archon of Deliverance by " + 
               capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Archon of Deliverance!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
remove_patriarch(string str)
{
    object tp = TP;
    string remover;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str) )
    {
        NF("No such player!\n");
        return 0;
    }

    remover = tp->query_real_name();
    str = lower_case(str);
    if (!strlen(patriarch))
    {
         NF("There is no Archon of Apotheosis yet!\n");
         return 0;
    } 

    if (is_council_member(remover) || is_calian_wiz(tp) || TP->query_real_name()==GUILD_MASTER) 
    { 
        if (str == patriarch)
        {
            patriarch = "";
            save_object(COUNCIL);
            (COUNCIL_OBJECTS+"log_book")->update_log_book(my_time() + 
               capitalize(str) + " has been removed as Archon of Apotheosis by " + 
               capitalize(remover) + ".\n");
            tp->catch_msg("Ok.\n");
            return 1;
        }
        else
        {
            NF("That is not the Archon of Apotheosis!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}

int
is_spell_banned(object player)
{
    if (player->query_skill(SS_SPIRIT_PUNISHMENT) == SPELL_BANNED)
        return 1;
    else
        return 0;
}

int
is_train_banned(object player)
{
    if (player->query_skill(SS_SPIRIT_PUNISHMENT) == TRAIN_BANNED)
        return 1;
    else
        return 0;
}

int
is_temple_restricted(object player)
{
    if (player->query_skill(SS_SPIRIT_PUNISHMENT) == TEMPLE_RESTRICTED)
        return 1;
    else
        return 0;
}

int
is_expelled(object player)
{
    if (player->query_skill(SS_SPIRIT_PUNISHMENT) == EXPELLED)
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

    player_name = player->query_real_name();
    if (is_spirit(player))
    {
        player->set_skill(SS_SPIRIT_PUNISHMENT, TRAIN_BANNED);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Spirit Circle Council from "+
            "using the guilds training facilities.\n"}));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_temple_restrict(object player)
{
    string player_name;

    player_name = player->query_real_name();
    if (is_spirit(player))
    {
        player->set_skill(SS_SPIRIT_PUNISHMENT, TEMPLE_RESTRICTED);
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been restricted to the Temple by the Spirit Circle "+
            "Council.\n"}));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_stop_spells(object player)
{
    string player_name;

    player_name = player->query_real_name();
    if (is_spirit(player))
    {
        player->set_skill(SS_SPIRIT_PUNISHMENT, SPELL_BANNED);
        present("_spirit_apprentice_spells_",player)->remove_object();
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been banned by the Spirit Circle Council from "+
            "using your spells.\n"}));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_expel_player(object player)
{
    string player_name;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT, EXPELLED);
    if (is_spirit(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been expelled from the Spirit Circle of Psuchae "+
            "by the Spirit Circle Council.\n"}));
        player->move_living("X","/d/Calia/guilds/scop/temple/chapel",0,1);
        player->command("betray my Blessing");
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_remove_punish(object player)
{
    string player_name;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT,NO_PUNISHMENT);
    present("spirit_spells",player)->activate_spells();
    set_alarmv(1.5, 0.0, "a_message", ({ player,
        "The Spirit Circle Council has removed any punishments "+
        "that have previously been placed on you.\n"}));
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_apromote_player(object player)
{
    string player_name;
    int gstat;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT, A_PROMOTED);
    if (is_spirit(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been promoted to the Master rank "+
            "by the Spirit Circle Council.\n"}));
        gstat = player->query_guild_stat(SS_OCCUP);
        player->set_skill(SS_SPIRIT_TITLE,(gstat-65));
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_mpromote_player(object player)
{
    string player_name;
    int gstat;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT, M_PROMOTED);
    if (is_spirit(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been promoted to the Elder rank "+
            "by the Spirit Circle Council.\n"}));
        gstat = player->query_guild_stat(SS_OCCUP);
        player->set_skill(SS_SPIRIT_TITLE,(gstat - 130));
        if (player->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            player->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);

}

void
exec_mdemote_player(object player)
{
    string player_name;
    int gstat;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT, E_DEMOTED);
    if (is_spirit(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been demoted to the Apprentice rank "+
            "by the Spirit Circle Council.\n"}));
        player->set_skill(SS_SPIRIT_TITLE,0);    // level (none)

    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
}

void
exec_edemote_player(object player)
{
    string player_name;
    int gstat, modstat;

    player_name = player->query_real_name();
    player->set_skill(SS_SPIRIT_PUNISHMENT, M_DEMOTED);
    if (is_spirit(player))
    {
        set_alarmv(1.5, 0.0, "a_message", ({ player,
            "You have been demoted to the Master rank "+
            "by the Spirit Circle Council.\n"}));
        player->set_skill(SS_SPIRIT_TITLE,0);     // level (50)
    }
    punishments = m_delete(punishments, player_name);
    save_object(COUNCIL);
    
}

void
carry_out_punishments(object player)
{
    string player_name;

    player_name = player->query_real_name();
    if (punishments[player_name])
    {
        if (punishments[player_name] == REMOVE_PUNISHMENTS)
        {
            if (player->query_skill(SS_SPIRIT_PUNISHMENT) != NO_PUNISHMENT)
            exec_remove_punish(player);
        }
        else if (punishments[player_name] == TRAIN_BANNED)
            exec_stop_train(player);
        else if (punishments[player_name] == SPELL_BANNED)
            exec_stop_spells(player);
        else if (punishments[player_name] == TEMPLE_RESTRICTED)
            exec_temple_restrict(player);
        else if (punishments[player_name] == EXPELLED)
            exec_expel_player(player);
        else if (punishments[player_name] == A_PROMOTED)
            exec_apromote_player(player);
        else if (punishments[player_name] == M_PROMOTED)
            exec_mpromote_player(player);
        else if (punishments[player_name] == E_DEMOTED)
            exec_edemote_player(player);
        else if (punishments[player_name] == M_DEMOTED)
            exec_mdemote_player(player);
    }
}

void
add_punishment(string punished, int punishment)
{
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

    if (is_council_member(banner) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
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
        else if (is_spirit(player))
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
            NF("Either the player doesn't exist, or isn't a Spirit Circle member.\n");
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
record_temple_restrict(string str)
{
    object player;
    string banner;

    if (!stringp(str))
    {
        NF("Restrict whom to the Temple?\n");
        return 0;
    }

    banner = TP->query_real_name();
    str = lower_case(str);

    if (is_council_member(banner) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, TEMPLE_RESTRICTED);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has restricted " + capitalize(str) +
                " to the Temple.\n");
            write("Ok.\n");
            return 1;
        }
        else if (is_spirit(player))
        {
            exec_temple_restrict(player);
            (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
                capitalize(banner) + " has restricted " + capitalize(str) +
                " to the Temple.\n");
            write("Ok.\n");
            return 1;
        }
        else
        {
            NF("Either the player doesn't exist, or isn't a Spirit Circle member.\n");
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

    if (is_council_member(banner) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
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
        else if (is_spirit(player))
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
            NF("Either the player doesn't exist, or isn't a Spirit Circle "+
               "member.\n");
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

    if (is_council_member(banner) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
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
        else if (is_spirit(player))
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
            NF("Either the player doesn't exist, or isn't a Spirit Circle "+
               "member.\n");
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

    if (is_council_member(banner) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
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
        else if (is_spirit(player))
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
            NF("Either the player doesn't exist, or isn't a Spirit Circle "+
               "member.\n");
            return 0;
        }
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

void
add_apprentice(string str)
{
    str = lower_case(str);
    spirit_apprentices += ({ str });
        
    save_object(COUNCIL);
    
}

void
add_mentor(string myname, string apprentice)
{
    myname = lower_case(myname);
    apprentice = lower_case(apprentice);
    mentors += ([ myname : apprentice ]);

    save_object(COUNCIL);
}

void
remove_apprentice(string str)
{
    str = lower_case(str);
    spirit_apprentices -= ({ str });

    save_object(COUNCIL);
    
}

void
remove_master(string str)
{
    str = lower_case(str);
    spirit_masters -= ({ str });

    save_object(COUNCIL);
}

varargs int
promote_apprentice(string str, string promoter)
{
    object target, player;
    string adder;
    int gstat;

    if (!str)
        return 0;

    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = TP->query_real_name();
    }

    str = lower_case(str);
    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, spirit_masters) >= 0)
        {
            NF(capitalize(str) + " is already in the Master ranking.\n");
            return 0;
        }

        if (member_array(str, spirit_elders) >= 0)
        {
            NF(capitalize(str) + " is an Elder! You will have to demote "+
               "them if you want them in the Master ranking.\n");
            return 0;
        }

        spirit_masters += ({ str });
        spirit_apprentices -= ({ str });
        
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been promoted to the Master "+
            "ranking by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        write("Please remove "+capitalize(str)+" from their " +
            "mentor/apprentice pairing as well.\n");

        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, A_PROMOTED);  // Not a punishment, but ...
        }

        if (target = find_player(str))
        {
            tell_object(target,"You have been promoted to the Master "+
                "ranking.\n");
            gstat=target->query_stat(SS_OCCUP);
            target->set_skill(SS_SPIRIT_TITLE,(gstat - 65));
        }
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that!\n");
        return 0;
    }
}

varargs int
promote_master(string str, string promoter)
{
    object target, player;
    string adder;
    int gstat;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }
    
    if (promoter)
    {
        adder = capitalize(promoter);
    }
    else
    {
        adder = TP->query_real_name();
    }

    str = lower_case(str);
    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, spirit_elders) >= 0)
        {
            NF(capitalize(str) + " is already in the Elder ranking.\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice! You will have to "+
               "promote them to Master ranking first if you want them "+
               "in the Elder ranking.\n");
            return 0;
        }

        spirit_masters -= ({ str });
        spirit_elders += ({ str });
        
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been promoted to the Elder "+
            "ranking by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");

        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, M_PROMOTED);  // Not a punishment, but ...
        }

        if (target = find_player(str))
        {
            tell_object(target,"You have been promoted to the Elder "+
                "ranking.\n");
            gstat=target->query_stat(SS_OCCUP);
            target->set_skill(SS_SPIRIT_TITLE,(gstat - 130));
            if (target->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
                target->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
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
demote_master(string str)
{
    object target, player;
    string adder;
    int gstat;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    adder = TP->query_real_name();
    str = lower_case(str);
    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is already in the Apprentice ranking.\n");
            return 0;
        }

        if (member_array(str, spirit_elders) >= 0)
        {
            NF(capitalize(str) + " is an Elder! You will have to "+
               "demote them to Master ranking first if you want them "+
               "in the Apprentice ranking.\n");
            return 0;
        }

        spirit_masters -= ({ str });
        spirit_apprentices += ({ str });
        
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been demoted to the Apprentice "+
            "ranking by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");
        
        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, M_DEMOTED);  
        }

        if (target = find_player(str))
        {
            tell_object(target,"You have been demoted to the Apprentice "+
                "ranking.\n");
            target->set_skill(SS_SPIRIT_TITLE,0);
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
demote_elder(string str)
{
    object target, player;
    string adder;
    int gstat, modstat;

    if (!str)
        return 0;

    if (!(SECURITY->exist_player(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    adder = TP->query_real_name();
    str = lower_case(str);
    
    if (str == archon)
    {
        NF("You cannot demote the Archon. If you wish to demote "+
           capitalize(str)+", you must first remove them as Archon.\n");
        return 0;
    }

    if (str == patriarch)
    {
        NF("You cannot demote the Patriarch. If you wish to demote "+
           capitalize(str)+", you must first remove them as Patriarch.\n");
        return 0;
    }

    if (is_council_member(adder) || is_calian_wiz(TP) || TP->query_real_name()==GUILD_MASTER)
    {
        if (member_array(str, spirit_masters) >= 0)
        {
            NF(capitalize(str) + " is already in the Master ranking.\n");
            return 0;
        }

        if (member_array(str, spirit_apprentices) >= 0)
        {
            NF(capitalize(str) + " is an Apprentice! You will have to "+
               "use the promote command if you want them in Master ranking.\n");
            return 0;
        }

        spirit_elders -= ({ str });
        spirit_masters += ({ str });
        
        (COUNCIL_OBJECTS + "log_book")->update_log_book(my_time() +
            capitalize(str) + " has been demoted to the Master "+
            "ranking by "+capitalize(adder)+".\n");
        save_object(COUNCIL);
        write("Ok.\n");

        player = find_living(str);
        if ((!player) && SECURITY->exist_player(str))
        {
            add_punishment(str, E_DEMOTED);  
        }

        if (target = find_player(str))
        {
            tell_object(target,"You have been demoted to the Master "+
                "ranking.\n");
            target->set_skill(SS_SPIRIT_TITLE,0);     
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
filter_string(mixed s)
{
    return stringp(s);
}

