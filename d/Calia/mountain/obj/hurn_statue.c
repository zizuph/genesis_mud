/* Statue of Hurn the mighty Calian hero.
   Last and most dangerous guard of the way to the Palace of Caliana,
   will come to life to defend against listed enemies of Calia.
   Coded by Maniac  16.6.95

   History:
*/

inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <const.h>
#include "/d/Calia/glykron/palace/specials/calian.h"
inherit "/d/Calia/std/statue";

int 
is_calian(object player)
{
    return player->query_guild_name_occ() == GUILD_NAME;
}

string
hurn_short()
{
     if (is_calian(this_player()))
         return "statue of Hurn";
     else
         return "statue of a huge muscular human";
}


string
hurn_long()
{
     if (is_calian(this_player()))
         return "This is a statue of Hurn, the mighty Calian hero " +
                "who it is said had the strength to twist the heads " +
                "from wild bulls. Legend has it that it will come to " +
                "life when necessary, in order to repel those who are " +
                "a danger to Calians from entering the palace.\n";
     else
         return "This is a statue of a huge muscular human, " +
                "a hero from Calian legend perhaps. It looks " +
                "ominously lifelike.\n";
}



void
create_object()
{
    set_short("@@hurn_short");
    set_name("hurn");
    add_name("statue");
    set_adj(({"huge", "muscular", "human"}));
    set_long("@@hurn_long");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_VOLUME, 100000);

    set_give_warning(1);
}

