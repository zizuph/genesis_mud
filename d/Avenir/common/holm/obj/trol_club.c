// Serpentine staff  /d/Avenir/common/holm/obj/trol_club
// creator(s):   Lilith, 10/25/97
// purpose:      To be wielded by trolobieson the Holm
// last update:         
// note:         
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====

inherit "/std/weapon";
#include "../holm.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

string
my_long()
{
    return "A simple, yet deadly club made from the "+
           "thorny trunk of a yark bush. The thorns have been cut "+
           "away and the wood carefully peeled back to make a sturdy "+
           "handle, wrapped in oiled leather. It is twice the length "+
           "of your arm and thick as your thigh.\n";
}

void
create_weapon()
{
    set_name("club");    
    add_name(({"weapon"}));
    set_pname(({"clubs", "weapons"}));
    set_adj(({"gnarled", "thorned", "thorny"}));
    set_short("gnarled thorny club");
    set_long(my_long());                                   
    set_hit(25 + random(10));
    set_pen(25 + random(10));
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_SLASH); // It is 'spiked'.
    set_hands(W_ANYH);
    
    add_item(({"thorn", "thorns"}),
        "Vicious-looking thorns as wide as your thumbnail, with "+
        "a hook-like tip that will rip flesh to ribbons. The thorns "+
        "grow in a curious spiral pattern along the length of the "+
        "club.\n");
    add_item(({"handle", "leather handle", "oiled leather handle"}),
        "Wood has been peeled back in spirals, following the natural "+
        "growth of the thorns, and oiled leather has been wound "+
        "into the grooves.\n");
    add_item(({"wood", "yark"}),
        "The club is made from the yark bush, a strong, light"+
        "weight wood which grows viscious thorns.\n");
}


