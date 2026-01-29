/* Stralle @ Genesis 040225
 */

#pragma strict_types

inherit "/d/Ansalon/guild/dragonarmy/dragons/dragon_back";

#include "../guild.h"

int
destinations(string str)
{
    if (str)
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!MEMBER(this_player()))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    write("   --===Destinations===--\n\n" +
        "          Sanction\n" +
        "          Neraka\n" +
        "          Flotsam\n" +
        "          Pax Tharkas\n" +
        "          Solace\n" +
        "          Solamninan plains\n" +
        "          Forest of Icewall\n" +
        "          Clearing in Mithas\n\n");
    
    return 1;
}
