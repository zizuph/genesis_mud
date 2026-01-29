/*
 * The Revelations list for OotS
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

string
oots_revelations_list()
{

    mapping revelations = OOTS_MANAGER->query_oots_revelations(TP);

    string message_text = "Revelations granted to you by " +
                          oots_god_name(TP)+ "\n\n";
    string buffer = "              ";
    string no_rev = ".........................................";

    if(member_array(lower_case("paladine"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Paladine");

    if(member_array(lower_case("mishakal"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Mishakal");

    if(member_array(lower_case("kirijolith"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Kiri-Jolith");

    if(member_array(lower_case("habbakuk"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Habbakuk");

    if(member_array(lower_case("branchala"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Branchala");

    if(member_array(lower_case("majere"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Majere");

    if(member_array(lower_case("solinari"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "The Aspect of Solinari");

    if(member_array(lower_case("paladinechurch"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - the Church of Paladine");

    if(member_array(lower_case("disksofmishakal"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - the Disks of Mishakal");

    if(member_array(lower_case("canticle12"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - Canticle of the Dragon, verse 1 and 2");

    if(member_array(lower_case("canticle34"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - Canticle of the Dragon, verse 3 and 4");

    if(member_array(lower_case("canticle56"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - Canticle of the Dragon, verse 5 and 6");

    if(member_array(lower_case("canticle78"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Edification - Canticle of the Dragon, verse 7 and 8");

    if(member_array(lower_case("ageofstarbirth"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - the Age of Starbirth");

    if(member_array(lower_case("curseofpaladine"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - Ogre Races and the Curse of Paladine");

    if(member_array(lower_case("lightbringer"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - the Lightbringer");

    if(member_array(lower_case("13warnings"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - The Fall of Istar, the Thirteen Warnings");

    if(member_array(lower_case("divinehammer"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - the Order of the Divine Hammer");

    if(member_array(lower_case("innfellows"), m_indexes(revelations)) < 0)
       message_text += sprintf("%-=71s \n", buffer + no_rev);
    else
       message_text += sprintf("%-=71s \n", buffer + 
                       "Enlightenment - the Innfellows");

    return message_text;
}

