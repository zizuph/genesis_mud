/* Created by Karath */
/* A merman Patrol for Coral Requiem */


inherit "/d/Emerald/std/emerald_guard";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Emerald/eclipsia/edefs.h"

void add_k9_turtles();

create_emerald_monster()
{
    set_name("merman");
    set_short("strong merman");
    set_adj("strong");
    set_race_name("merfolk");
    set_long("This merfolk is a strong, experienced-looking male. He " +
	"seems to be keeping a watchful eye on everyone. He pays special "+
	"attention to visitors such as you"+
        ".\n");

    set_restrain_path( ({"/d/Emerald/eclipsia/coral_requiem/"}) );

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(MAGIC_I_BREATH_WATER,1);
    add_prop("_coral_requiem_npc_",1);
    set_alignment(200);
    set_act_time(1);
    add_act("say Welcome to our beautiful town. Don't cause any trouble.");
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 75000);
    set_skill(SS_WEP_POLEARM, 85);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 50);

    set_stats(({(random(50)+70),(random(40)+70),(random(40)+60),
        80,80,(random(40)+60)}));

    MONEY_MAKE_SC(30)->move(this_object(), 1);

    add_equipment( ({ ECLIPSIA_OBJ + "pat_trident", ECLIPSIA_OBJ +
	"shell_plate"}) );

    set_random_move(8);

    log_my_kills( ECLIPSIA_DIR + "log/guardkills");

    trig_new("%w 'leaves' / 'sneaks' %s", "follow_attacker");

    set_alarm(2.0, 0.0, "add_k9_turtles");
}

void
add_k9_turtles()
{
    int m, n;

    object turtle;

    setuid();
    seteuid(getuid());

    m = (1 + random(2));

    TO->set_leader();
    for (n = 0; n < m; n++)
      {
	turtle = clone_object(ECLIPSIA_DIR + "npc/turtle");
        turtle->set_restrain_paths( ({"/d/Emerald/eclipsia/coral_requiem/"}) );
	turtle->move(environment(TO));
	tell_room(environment(TO), capitalize(LANG_ADDART(turtle->query_race_name())) +
	" swims up to the " + TO->query_short() + ".\n");
	TO->team_join(turtle);
      }
}

void
assist(object enemy)
{
    switch (random(3))
      {
      case 0:
	command("say Couldn't restrain yourself eh?! Neither shall I!");
	break;
      case 1:
	command("shout Prepare to be impaled!");
	break;
      case 2:
	command("shout Thy evil deed will be thy doom!!");
	break;
      }
    tell_room(environment(TO), "The " + short() + " joins the fray!\n");
}
