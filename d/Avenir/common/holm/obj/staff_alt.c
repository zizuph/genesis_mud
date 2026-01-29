// Serp staff alternate /d/Avenir/common/holm/obj/staff_alt.c
// creator(s):   Lilith, 1/25/97
// purpose:      To be wielded by priestly students of the Beast
// last update:         
// note:         This object is a non-magical duplicate of the 
//               serpent_staff.
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

string my_long()
{
    return "A staff carved of wood stripped of its bark and "+
           "polished to a high sheen. It is wavy or serpentine "+
           "in form, and has scales carved into it. One end of the "+
           "staff is fashioned into the head of a snake, its mouth "+
           "open to reveal prodigious fangs. The tail is barbed "+
           "with spikes not unlike the fangs.\n";
}

void create_weapon()
{
    set_name("staff");    
    set_pname("staffs");
    add_name(({"polearm", "weapon"}));
    set_adj(({"serpentine"}));
    set_short("serpentine staff");
    set_long(my_long());                                   
    set_hit(28);
    set_pen(22);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);

    add_item(({"head", "fangs", "mouth"}),
        "This is a very realistic-looking snake head. The artistry "+
        "of the carving is quite amazing, even down to the fangs "+
        "in the open, silently hissing mouth.\n");
    add_item(({"tail", "barb", "spike", "spikes"}), 
        "The tail is barbed with slightly curving spikes that occur "+
        "in a spiral around the end of the staff. They look quite "+
        "sharp.\n");

}
