/* Ashlar, 7 Jun 97 - A wild dog that roams the streets */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>

inherit AC_FILE
inherit AUTO_TEAM
inherit "/std/act/action";
inherit "/std/act/domove";


void
create_creature()
{
    ::create_creature();
    set_name("dog");
    add_name("wilddog");
    set_adj(({"grey","black","brown"})[random(3)]);
    add_adj(({"dirty","wild","mangy"})[random(3)]);
    set_race_name("dog");
    set_long("This is a wild dog that roams the streets of Neraka, " +
        "looking for food.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_VOLUME, 25000);
    set_stats(({20,20,20,3,3,20}));
    set_act_time(4);
    add_act("emote barks ferociously.");
    add_act("growl");
    add_act("emote sniffs the ground.");
    add_act("emote barks loudly.");
    add_act("emote pants.");
    set_hitloc_unarmed(0,15,80,"body");
    set_hitloc_unarmed(1,10,20,"head");
    set_attack_unarmed(0,20,30,W_BLUDGEON,40,"front paws");
    set_attack_unarmed(1,20,25,W_BLUDGEON,40,"jaws");
    set_attack_unarmed(2,20,30,W_BLUDGEON,20,"back paws");
    seteuid(getuid());
    set_pick_up_team(({"wilddog"}));
    set_random_move(30);
}

void
init_living()
{
	::init_living();
    init_team_pickup();
}

mixed
oke_to_move(string exit)
{
	object l;
    if ((l=query_leader()) && (l != TO))
        return 0;
    else
        return ::oke_to_move(exit);
}

