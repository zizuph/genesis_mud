/* created by Aridor 10/12/93 */


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit AC_FILE
inherit "/std/act/attack";


void
create_creature()
{
    int i;

    set_name("warhorse");
    set_race_name("horse");
    set_adj("powerful");
    set_short("powerful warhorse");

    set_gender(2);
    set_long("Before you stands a large, powerful warhorse. " +
      "Its brown coat looks well groomed, although it seems " +
      "to need a good run by the looks of its agitated state.\n");

    set_stats(({40,50,40,1,1,90}));

    set_hp(5000);
    set_alignment(5);
    set_knight_prestige(-5);
    
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " doesn't accept any gifts from you.\n");
    
    NEVERKNOWN;

    set_attack_unarmed(1,6,22,W_SLASH,50,"hooves");
    set_attack_unarmed(2, 40, 5, W_IMPALE, 20, "bite");

    set_hitloc_unarmed(1,  4, 90, "body");
    set_hitloc_unarmed(2, 3, 10, "head");


    add_cmd_item("horse","mount","@@mount_horse");
}

string
mount_horse()
{
    write("The way the horse is looking at you, "+
      "you think it would sooner let you spit it with a lance "+
      "than let you ride it.\n");
    return "";
}
