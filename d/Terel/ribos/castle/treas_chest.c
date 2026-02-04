/* Decoy teasure chest. The real ones are elsewhere in the castle.
 * This one is behind a locked door, player has to get the key, etc
 */

inherit "/std/receptacle";

#include "/d/Terel/include/Terel.h"
#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <money.h>

string *randadj;
string *randname;

void
reset_chest()
{
    object gem;
    /* fill the box with decoy treasures */
    if (sizeof(all_inventory(this_object())) < 2)
    {
        FIX_EUID;


        gem = RANDOM_GEM(GEM_RARE);
                  gem->move(this_object(), 1);
        gem = RANDOM_GEM(-1);
                  gem->move(this_object(),1);
        gem = RANDOM_GEM(-1);
                  gem->move(this_object(),1);
        gem = RANDOM_GEM(-1);
                  gem->move(this_object(),1);
        gem = RANDOM_GEM(-1);
                  gem->move(this_object(),1);
        gem = RANDOM_GEM(GEM_RARE);
                  gem->move(this_object(), 1);
        gem = RANDOM_GEM(GEM_RARE);
                  gem->move(this_object(), 1);

        MONEY_MAKE_CC(500 + random(100))->move(this_object(), 1);
        MONEY_MAKE_SC(100 + random(500))->move(this_object(), 1);
        MONEY_MAKE_GC( 50 + random(10) )->move(this_object(), 1);
        MONEY_MAKE_PC( 10 + random(10) )->move(this_object(), 1);
    }

}

void
create_receptacle()
{
    randadj = ({"heavy","big","iron-bound","massive","gilded","gem-encrusted",
                "red-lacquered", "monarch's"});
    randname = ({"chest","coffer", "strongbox"});

    set_name(randname[random(sizeof(randname))]);
    set_adj(randadj[random(sizeof(randadj))]);
    add_name("box"); 
    set_long("Very fancy, it looks heavy enough that it would take two "+
        "strong men to carry it. It probably contains the King's Ransom "+
        "for whoever kills the dragon that plagues this land.\n");
    add_item(({"bands","iron"}), ("The box is "
        +"wrapped in thick iron bands to protect it from "
        +"breaking.\n"));
    add_prop (OBJ_I_VALUE,  487); // no one can get it anyway..
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 1500000);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 400000);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 250000); // 250 kilos
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
    reset_chest();
}



