// Coded by Ibun 070612
// bug(s):
// to-do:

#pragma strict_types
#include <stdproperties.h>     /* Where the properties are defined. */
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <state_desc.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";
inherit "/lib/unique";

int called_for_help = 0;
int clone_pal();
int query_called();
void equip_me();

void
create_monster()
{
   set_name("William");
  add_name("thief");
  set_adj("sneaky");
  set_race_name("port thief");
  set_long("This is an undescript man in dark clothes you hardly " +
           "notice till he gets very close to you and saves you the " +
           "trouble of carrying your heavy money purse around.\n");
  set_stats(({130, 130, 130, 60, 60, 90}));
  set_alignment(-1000);
  set_skill(SS_DEFENSE, 100 );
  set_skill(SS_WEP_KNIFE, 100 );
  set_skill(SS_AWARENESS, 70 );
  set_skill(SS_HIDE, 80 );
  set_skill(SS_SNEAK, 80);
  set_skill(SS_PICK_POCKET, 70);
  set_cchat_time(5);
  add_cchat("Burn!");
  add_cchat("Soon you will sleep with the fishes!");
  add_cchat("My brother Barney will show up soon!");
  set_act_time(5);
  add_act("hide");
  add_act("peek all");
  add_act("steal platinum from human");
  equip_me();
}

void
equip_me()
{
    MONEY_MAKE_SC(random(50))->move(this_object(), 1);

    clone_object(PORT + "obj/jacket")->move(this_object(), 1);
    clone_unique((PORT + "obj/thief_gloves"), 5, (PORT + "obj/gloves"),
        1, 30)->move(this_object(), 1);
    command("wear all");
    clone_object(PORT + "obj/uw_dagger")->move(this_object(), 1);
    command("wield dagger");
}

int
special_attack(object enemy)
{
    int i;
    object pal;
    string str;

    pal = (present("pal", ENV(TO)));

    if (pal)
    {
        if (enemy->query_attack() == TO)
        {
            tell_room(ENV(TO), QCTNAME(TO) + " cowardly sneaks " +
                "out of action.\n");
            enemy->stop_fight();
            pal->command("kill " + enemy->query_real_name());
            return 1;
        }
        return 1;
    }

    if (!(random(3)))
        if ((TO->query_hp()) <= (TO->query_max_hp()) / 2)
        {
            if (query_called())
            {
                if (!(pal))
                {
                    if (!(i = random(3)))
                    {
			 foreach(object who: filter(query_enemy(-1), objectp))
			  {
			    who->stop_fight(TO);
			    stop_fight(who);
			  }
                        string exit = one_of_list((ENV(TO)->query_exit_cmds()));
                        command("sneak " + exit);
                        return 1;
                    }
                }
                return 1;
            }
            command("shout Help! Come here boys!");
            called_for_help = 1;
            set_alarm(3.0, 0.0, &clone_pal());
        }
    return 1;
}

int
clone_pal()
{
    object pal, enemy;
    int i;

    tell_room(ENV(TO), "Some thugs arrives!\n");
    for (i = 0; i <= 2; i++)
    {
        pal = clone_object(PORT + "mon/pal");
        pal->move(ENV(TO), 1);
        TO->team_join(pal);
        pal->command("assist");
        TO->team_leave(pal);
    }
    enemy = pal->query_enemy();
    enemy->stop_fight();
    pal->command("kill " + enemy->query_real_name());
    return 1;

}

int
query_called()
{
    return called_for_help;
}
