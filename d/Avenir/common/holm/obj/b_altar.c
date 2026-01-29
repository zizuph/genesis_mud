// file name:   /d/Avenir/common/holm/obj/b_altar.c
// creator(s):  Lilith, March '97
// revision(s): 
// purpose:     Altar for the cave complex on the Holm
// note:             
// bug(s):           
// to-do:

inherit "/d/Avenir/inherit/altar";
#include "/d/Avenir/include/deities.h"
#include "../holm.h"

void
create_altar()
{
    set_name("altar");
    set_adj("alabaster");
    add_name(({"brizhaem", "salilus_altar"}));
    set_altar_name("brizhaem");
    set_altar_hour("1");
    set_god("salilus");
    set_altar_short("alabaster altar");    

    //Remember, no /n on the long descs...its added automatically.
    set_id_long("This is an elegantly simple altar composed of three "+
        "slabs of flawless alabaster. Two of the slabs act as the "+
        "base for the altar, and the third rests atop them. Various "+
        "stylized lock-and-key icons have been carved into the polish"+
        "ed surfaces, and you recognize them as symbols belonging to "+
        "the god Salilus, Overguardian of Sybarus and Master of the "+
        "First Hour.");
    set_unid_long("This is an elegantly simple altar composed of "+
        "three slabs of flawless alabaster. Two of the slabs act as "+
        "the base for the altar, and the third rests atop them. "+
        "Various stylized lock-and-key icons have been carved into "+
        "the polished surfaces.");
    add_item(({"surface", "surfaces", "icons", "symbols", "carvings"}), 
        "@@my_symbol");

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile", "deface"}));
    set_destroy_command(({"destroy", "break"}));
    set_dismantle_command("dismantle");
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(({SALILUS_OFFERING, UNIVERSAL_OFFERING}));
    set_pray_command("pray");
    set_worship_command("worship");
     
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");
}                                                                            

string
my_symbol()
{
    /*    check if player identifies the altar */
    if  (!id_altar_check(this_player()))
        return "Lock and key symbols have been carved into the smooth, "+
               "polished surface of the white alabaster. They are "+
               "stylized and remarkably detailed. Much effort has gone "+
               "into the making of this altar, and you can't help but "+
               "feel that it was raised for the worship of a god of "+
               "great importance.\n";
    else
        return "The lock and key symbols have been carved into the smooth,"+
               " white surface of the alabaster with great care and attent"+
               "ion to detail.\n";
}
