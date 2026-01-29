// file name:   /d/Avenir/common/holm/obj/zar_altar.c
// creator(s):  Lilith,Hannah May '02
// revision(s): 
// purpose:     Altar for worship of Zaren
// note:             
// bug(s):           
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/altar";
#include "/d/Avenir/include/deities.h"
#include <stdproperties.h>
#include <cmdparse.h> 

void
create_altar()
{
    set_name("altar");
    set_adj("fist_shaped");
    add_adj("carnelian");
    add_name(({"zaren_altar", "stones", "circle"}));
    set_altar_name("zaren temple");
    set_altar_hour("9");
    set_god("zaren");
    set_altar_short("fist-shaped made of carnelian");       
    set_id_long("This is a small circle of irridescent stones, "+
        "each emitting a pleasing hum reminiscent of tuning forks. "+
        "Symbols representing musical instruments have been carved "+
        "into the stones, along with the single flowing glyph repre"+
        "senting the goddess Bucaphi.");
    set_unid_long("This is a small circle of irridescent stones, "+
        "each emitting a pleasing hum reminiscent of tuning forks. "+
        "Symbols representing musical instruments have been carved "+
        "into the stones, along with a single flowing rune.");
    add_item(({"rune", "glyph", "flowing glyph"}), "@@my_symbol");
    add_item(({"symbols", "symbol", "instruments" }),
        "There are many musical instruments carved into the "+
        "stones. Some of them you recognize as flutes, harps, "+
        "lyres, and sitars.\n");

    set_offer_max(10);
    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile", "deface"}));
    set_destroy_command(({"destroy", "break"}));
    set_dismantle_command("dismantle");
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(({SALILUS_OFFERING, UNIVERSAL_OFFERING}));
    set_pray_command("pray");
    set_worship_command("worship");
     
    add_prop(OBJ_M_NO_GET, "The stones seem to resist your efforts.\n");
}                                                                            

string
my_symbol()
{
    /*    check if player identifies the altar */
    if  (!id_altar_check(this_player()))
        return "This glyph is unique to Bucaphi, Goddess of music. "+
               "It begins as an oval, with a tail that bends away "+
               "at a right angle and seems to flutter before your "+
               "eyes.\n";
    else
        return "This rune begins as an oval, with a tail that "+
               "bends away at a right angle and seems to flutter "+
               "before your eyes.\n";
}

