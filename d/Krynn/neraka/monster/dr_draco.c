/* drunk draconian, coded by nick */
/* use the drac base, aridor 11/96 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Krynn/std/baaz";

void
create_baaz()
{
    int i;

    set_name("drunk");
    /*set_living_name("drunk");*/
    set_long("This draconian is in very bad shape. It looks like he has been " +
	     "drinking for days, a disgrace for the dragon army.\n");
    set_race_name("draconian");
    set_adj("drunk");

    add_act("say Hey, who are you? Stand still will yah!");
    add_act("grin");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");
    add_act("@@make_drunk@@");

    set_act_time(1);

    set_color("red");

    for (i = 0; i < 6; i++)
      set_base_stat(i, 15 + random(5));

    set_alignment(-130);
    set_knight_prestige(200);

    set_all_attack_unarmed(12, 17);
    set_all_hitloc_unarmed(10);

    NEVERKNOWN;

    if (IS_CLONE)
      set_alarm(1.0,0.0,"get_stuff");
}

string
make_drunk()
{
    command("emote orders a beer and swallows it at once.");
    drink_alco(10,0);
    return "";
}

void
get_stuff()
{
    seteuid(getuid(TO));
    all_inventory(TO)->remove_object();
    MONEY_MAKE_CC(30 + random(30))->move(TO);
    make_drunk();
    make_drunk();
    make_drunk();
}
