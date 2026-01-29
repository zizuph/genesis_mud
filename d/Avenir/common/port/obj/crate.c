// creator(s): Ilyian
// last update: 18 April (changed it to a real container)
// purpose: heavy crates for Jarod to carry from warehouse to outpost
// note: Tried to list all the cities of Genesis - there are a lot!
//       Too heavy for alomost anyone to carry.
// bug(s):
// to-do: Use it in some sort of quest...

inherit "/std/receptacle";

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

string *randadj;
string *randplace;

void

create_container()
{
        randadj = ({"heavy","enormous","big","iron-bound","wooden",
                    "massive","oddly-shaped","cubic","flattened",
                    "battered","thick","sweet-smelling","new",
                    "old","large","weathered","rickety","bulky",
                    "curious","stiff","painted","titanic",
                    "suspicious-looking","closed","grey",
                    "long","rounded"});

        randplace = ({"An official stamp on the top reads: Minas Tirith, "
+"via Harlond. Special Shipment.","An official looking label on the side "
+"says: by order of the Company, Kabal, Kalad. Private","An elegant "
+"seal has been burned into the side depicting a four-pointed star. Runes "
+"are painted all around the seal, and you feel a strange aura emanating "
+"from the crate.","Scribbled across the side is: Gelan, through "
+"Sparkle village, by order of Her Grace, Caliana.","Written on "
+"the top in an elegant red script is: City of Calathin, northern "
+"reaches.","A red eye is painted on the side. Beneath is in heavy black "
+"lettering reads only: Minas Morgul.","On the top is scrawled in clumsy "
+"lettering: Southfarthing, delicate!","Beautiful blue lettering on the "
+"side reads: Special shipment, Annuminas Club, not to be opened "
+"under any circumstances whatsoever!","Burned into the top is an image "
+"V painted in a shade of red that looks suspiciously like blood. The "
+"crate smells of the dead, and you feel nervous being near it.","Painted "
+"in large, bold letters on the side is: township of Cove, special "
+"delivery.","On the side in blackened letters reads: The city of Tyr. "
+"Quarantined materials - open under controlled circumstances only.","In "
+"a smooth, gentle script written on the top is: City of Edoras, by order "
+"of Theoden King. Special shipment to Sybarus port."});


        set_name("crate");
        add_name("std_crate_ware");

        set_adj(randadj[random(sizeof(randadj))]);

        set_long("This is a massive wooden crate wrapped in iron "
                 +"bands with a heavy steel padlock securing it. It "
                 +"looks unbearably heavy. "
                 +randplace[random(sizeof(randplace))]+"\n");

        add_item(({"bands","lock","padlock","iron"}), ("The crate is "
                 +"wrapped in thick iron bands to protect it from "
                 +"breaking, and secured with a padlock that looks "
                 +"unbreakable.\n"));

        add_prop (OBJ_I_VALUE,  487); // no one can get it anyway...
        add_prop(CONT_I_CLOSED, 1);
        add_prop(CONT_I_LOCK, 1);
        add_prop(CONT_I_IN,1);
        add_prop(CONT_I_WEIGHT, 300000);
        add_prop(CONT_I_VOLUME, 20000);
        add_prop(CONT_I_MAX_VOLUME, 5000);
        add_prop(CONT_I_MAX_WEIGHT, 5000);
        add_prop(CONT_I_RIGID, 1);

        set_key("Large_Crate_Key");   //for later use only
        set_pick(70);  // don't want anyone getting into them and being
                       // disenchanted.

}


