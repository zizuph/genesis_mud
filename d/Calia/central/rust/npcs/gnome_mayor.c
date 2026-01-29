/* This is the mayor of Rust. Created 4.1.99, Bishop of Calia. */

inherit "/std/monster.c";
inherit "/d/Genesis/lib/intro.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <const.h>
#include "defs.h"

#define STATAV   60
#define STATDIFF  5
#define ALIGN   0

void
equip_me()
{
    object armour;

    seteuid(getuid(this_object()));

    armour = clone_object(RUST_ARMOURS + "mayor_coat");
    armour->move(TO);

    command("wear armours");
}


void
create_monster()
{
    set_name("fenlean");
    add_name("fenlean");
    set_race_name("gnome");
    add_adj("haughty");
    add_adj("big-nosed");

    set_gender(G_MALE);

    set_long("This impeccably dressed gnome is looking at you with" +
        " cold green eyes. He has a very pronounced nose, even" +
        " for a gnome, and a tiny pair of spectacles fits on top" +
        " of it.\n");

    set_alignment(ALIGN);
    set_title("the Mayor of Rust");

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 75);

    set_hp(query_max_hp());

    set_act_time(4);
    add_act("emote adjusts his spectacles slightly.");
    add_act("say Can I help you with anything?");
    add_act("smile faintly");
    add_act("emote removes a speck of dust from his clothes.");

    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(CONT_I_HEIGHT, 90);
    add_prop(NPC_I_NO_LOOKS,1);
}

public void
greet(object who)
{
    if (who->query_gender() == 0)
    {
        command("introduce myself to " + OB_NAME(who));
        command("say Greetings, Mister " + who->query_name() + ".");
    }
    else
    if (who->query_gender() == 1)
    {
        command("introduce myself to " + OB_NAME(who));
        command("say Greetings, Milady " + who->query_name() + ".");
    }
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    (RUST_SPECIALS + "guard_rescue.c")->set_priority(1, TO);
    set_alarm(1.0, 0.0, &command("emote rolls his eyes, and" +
        " mumbles something about violence being the last resort" +
        " of the feeble-minded."));
    set_alarm(2.0, 0.0, &command("shout Guards! Someone" +
        " is trying to murder me.")); 
}
