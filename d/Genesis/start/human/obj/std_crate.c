// creator(s):  Lilith Oct 96 (re-make of Ilyian's)
// last update: 
// purpose:     Modified from the std_crate in the port, for use
//              in the Underdark. 
//              Inherit this in crates to be placed in the Underdark
//              by the utt_tres.c SMIS module.
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

string *randadj;
string *randname;

void
create_receptacle()
{
    randadj = ({"heavy","enormous","big","iron-bound","wooden",
                    "massive","cubic","battered","thick","dusty",
                    "old","large","weathered","rickety","bulky",
                    "curious"});
    randname = ({"crate","chest","coffer","trunk"});

    set_name(randname[random(sizeof(randname))]);
    set_adj(randadj[random(sizeof(randadj))]);
    add_name("box"); 
    set_long("This is a massive wooden box wrapped in iron "
        +"bands.\nIt appears to be very heavy.\n");
    add_item(({"bands","iron"}), ("The box is "
        +"wrapped in thick iron bands to protect it from "
        +"breaking.\n"));
    add_prop (OBJ_I_VALUE,  487); // no one can get it anyway..
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 40000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 250000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
}



