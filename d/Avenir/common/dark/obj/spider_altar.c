// file name:   /d/Avenir/common/dark/obj/spider_altar.c
// creator(s):  Lilith, March '97
// revision(s): 
//              Lucius, Mar 08: Removed ability to destory or defile
//                 the altar as there is no way to repair it.
//
// purpose:     Aclolthayr's altar in the Underdark.
// note:             
// bug(s):           
// to-do:

inherit "/d/Avenir/inherit/altar";
#include "/d/Avenir/include/deities.h"
#include <cmdparse.h> 
#include "/d/Avenir/common/dark/dark.h"

void
create_altar()
{
    set_name("altar");
    set_adj(({"large", "spider-shaped", "spider"}));
    add_name(({"spider-altar","shiboleth", "aclolthayr_altar"}));
    set_altar_name("shiboleth");
    set_god("aclolthayr");
    set_altar_short("large spider-shaped altar");    
    
    set_id_long("It is an altar carved from dark, almost black, "+
        "granite, and is in the shape of a massive spider. It "+
        "is as tall as a human, and smeared all over it are old "+
        "traces of blood. It is supported by eight legs of "+
        "surprising delicacy, each of which has a long, heavy "+
        "chain attached to it. Engraved into the thorax of the "+
        "spider-altar are numerous spirals, which you recognize "+
        "as symbols belonging to the spider goddess Aclolthayr.\n");
    set_unid_long("It is an altar carved from dark, almost black, "+
        "granite, and is in the shape of a massive spider. It "+
        "is as tall as a human, and smeared all over it are old "+
        "traces of blood. It is supported by eight legs of "+
        "surprising delicacy, each of which has a long, heavy "+
        "chain attached to it. You notice that there are numerous "+
        "spiral symbols carved into the thorax of the spider-altar, "+
        "which emanates a dreadful feeling of violence "+
        "and fear, making you hesitant to even go near to it.\n");
    add_item(({"spiral", "spirals", "thorax", "symbols", "carvings"}), 
        "@@my_symbol");
    add_item(({"blood", "traces", "surface"}), "@@my_blood");

    set_offer_max(20);
//    set_bless_command(({"bless", "sanctify"}));
//    set_defile_command(({"desecrate", "defile", "deface"}));
//    set_destroy_command(({"destroy", "break"}));
//    set_dismantle_command("dismantle");
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(({ UNIVERSAL_OFFERING, ACLOLTHAYR_OFFERING }));
    set_pray_command("pray");
    set_worship_command(({"worship", "grovel"}));
     
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");
}                                                                            

string
my_symbol()
{
    /*    check if player identifies the altar */
    if  (!id_altar_check(this_player()))
        return "Spiral symbols have been carved into the surface of "+
               "the dark granite.\n";
    else
        return "The spiral symbols of Aclolthayr have been lovingly "+
               "and fearfully carved into the thorax of the spider "+
               "altar with great precision and care.\n";
}

string
my_blood()
{
    string str;
    if (query_prop(ALTAR_IS_BLOODY))
    {
        str = "Fresh blood darkens the center of the altar, "+
              "glistening obscenely. ";
    }
    else
	str = "";

    str += "A brittle, blackened covering of dried, flaking blood "+
           "extends over most of the altar's surface and onto the "+
           "floor. The number of sacrifices here must have been "+
           "enormous.\n";
    return str;
}
