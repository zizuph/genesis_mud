/*
 *	/d/Gondor/minas/npc/arrest_officer.c
 *
 *	This officer will lead a troop of guards to arrest
 *	players in Minas Tirith that tried to kill a citizen
 *
 *	Olorin, June 1995
 */
inherit "/d/Gondor/minas/npc/gondor_officer.c";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 *	Definitions
 */
#define PRISON		(MINAS_DIR + "rooms/prison")
#define OFFICE		(MINAS_DIR + "rooms/adoffice")
// #define PARALYZE	(MINAS_DIR + "obj/arrest_paralyze")
#define PARALYZE	"/std/paralyze"
#define PARALYZE_ID	"_Minas_Tirith_arrest_paralyze"
#define CHAINS_SUBLOC	"_MT_arrest_chains_subloc"
#define LIVE_O_MT_ARRESTED	"_live_o_MT_arrested"
// release after 15 minutes
#define PRISON_TIME	900

/*
 *	Prototypes
 */
void    arrest_enemy();

/*
 *	Global variables
 */
int     alarm_id;
object  enemy,
        prisoner;

void
create_monster()
{
    ::create_monster();

    set_short("Gondorian officer");
    set_pshort("officers");
}

void
arm_me()
{
    ::arm_me();
}

void
init_attack()
{
    if (TP == enemy)
        set_alarm(1.0, 0.0, arrest_enemy);
}

void
set_enemy(mixed p)
{
    if (objectp(p))
        enemy = p;
    else if (stringp(p))
    {
        if (!objectp(p = find_player(LOW(p))))
            return;
    }
    else
        return;

}

void
return_home()
{
    object  room = ENV(TO);
    string *dirs;

    if (objectp(ENV(TO)) && sizeof(dirs = room->query_exit_cmds()))
        tell_room(ENV(TO), "The "+query_nonmet_name()+" leaves "
          + ONE_OF_LIST(dirs)+".\n");
    remove_object();
}

void
due_process(object tp)
{
    object  hunthor;

    command("say We will bring you to Hunthor now!");
    tell_room(ENV(TO), "The "+short()+" leads "+QTNAME(tp)
      + " away to Hunthor.\n", ({ tp, }) );
    tp->catch_msg("You are brought before Hunthor.\n");
    move_living("M", OFFICE);
    tp->move_living("M", OFFICE);
    tell_room(ENV(TO), CAP(LANG_ADDART(short())) + " arrives, leading in "
      + QTNAME(tp)+" in chains.\n", ({ tp, }) );

    if (!objectp(hunthor = present("hunthor", ENV(TO))))
    {
        command("hmm");
        command("say Looks like Hunthor is not here.");
        command("say Well, in that case I decide that you go to prison "
          + "for your attack on a citizen of Minas Tirith!");

        tp->move_living("into prison", PRISON);
        PRISON->jail_time(tp, PRISON_TIME);
        tp->remove_stun();
        present(PARALYZE_ID, tp)->remove_object();
        tp->remove_prop(LIVE_O_MT_ARRESTED);
        tp->remove_subloc(CHAINS_SUBLOC);
    }
    else
    {
        hunthor->due_process(tp);
    }
    set_alarm(15.0, 0.0, return_home);
    return;
}

int
filter_weapon(object x)
{
    return (function_exists("create_object", x) == "/std/weapon");
}

void
do_arrest()
{
    int     i;
    object  paralyze,
            prisoner,
           *enemies,
           *weps;

    if (!objectp(enemy) || !present(enemy, ENV(TO)))
    {
        set_alarm(5.0, 0.0, return_home);
        return;
    }

    enemy->catch_msg("The "+short()+" overwhelms you!\n"
      + "You are disarmed and put in chains.\n");
    tell_room(ENV(TO), "The "+short()+" overwhelms "+QTNAME(enemy)
      + " and puts "+enemy->query_objective()+" into chains.\n",
        ({ enemy, }) );
    enemy->add_prop(LIVE_O_MT_ARRESTED, TO);
    enemy->add_subloc(CHAINS_SUBLOC, TO);

    prisoner = enemy;
    enemy = 0;

    // stop all fights
    prisoner->stop_fight(enemies = prisoner->query_enemy(-1));
    for (i = 0; i < sizeof(enemies); i++)
        enemies[i]->stop_fight(prisoner);

    // take away all weapons
    weps = filter(all_inventory(prisoner), filter_weapon);
    for (i = 0; i < sizeof(weps); i++)
    {
        if (objectp(weps[i]->query_wielded()))
            weps[i]->unwield_me();
        weps[i]->move(TO, 1);
    }
    if (sizeof(weps))
    {
        prisoner->catch_msg("The officer takes away "
          + COMPOSITE_DEAD(weps) + " from you.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " take "
          + COMPOSITE_DEAD(weps) + " away from "+QTNAME(prisoner)+".\n",
          ({ prisoner, }) );
    }

    // paralyze
    if (!present(PARALYZE_ID, prisoner))
    {
        paralyze = clone_object(PARALYZE);
        paralyze->add_name(PARALYZE_ID);
        paralyze->set_stop_verb(0);
        paralyze->set_fail_message("You are in chains and under arrest.\n"
          + "You neither dare to move nor do you dare to talk!\n");
        paralyze->move(prisoner, 1);
    }
    // prevent player from fighting
    prisoner->add_stun();

    // lead him away
    set_alarm(2.0, 0.0, &due_process(prisoner));
}

void
arrest_enemy()
{
    tell_room(ENV(TO), "A squad of guards arrives following the officer.\n");
    set_short("squad of city guards");
    set_name("squad of guards");
    set_long("A squad of city guards, commanded by an officer of the guard.\n"
      + BSN("The officer is "+LANG_ADDART(implode(query_adjs()," "))+" dunadan, "
      + "probably from Anorien or Lossarnach, the provinces closest to "
      + "Minas Tirith. His proud stance makes him look like he his the "
      + "veteran of many battles. Experienced and skilled as he is, he "
      + "is a terrifying opponent in combat."));
    
    set_pshort("squads of city guards");
    add_name(({"squad", "squad of guards", "cityguards", "guards", }));
    set_alarm(1.0, 0.0, &do_arrest(enemy));
}

#if 0
int
surrender() 
{
    int     i;
    object  herb,
            tp = TP,
           *enemies;

    if (!tp->query_prop("_gondor_quest_smuggler_runaway") && (tp != query_attack()))
    {
        command("say Why do you want to surrender, "+tp->query_nonmet_name()+"?");
        command("say You haven't done anything illegal, have you?");
        command("peer "+tp->query_real_name());
        return 1;
    }

    if (alarm_id && sizeof(get_alarm(alarm_id)))
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }

    tp->catch_msg("You surrender to the cityguard.\n");
    say(QCTNAME(tp)+" surrenders to the cityguard.\n",tp);

    // we have to stop _all_ fights
    enemies = tp->query_enemy(-1);
    for (i = 0; i < sizeof(enemies); i++)
    {
        enemies[i]->stop_fight(tp);
        enemies[i]->remove_prop(LIVE_O_ENEMY_CLING);
    }
    
    tp->stop_fight(enemies);

    command("say Good! Come with me!");
    tp->catch_msg("The cityguard leads you away.\n");

    if (objectp(herb = present("smuggler_quest_herb",tp)))
    {
        tp->catch_msg("The cityguard confiscates the "+herb->short()+".\n");
        herb->remove_object();
    }

    tp->catch_msg("The cityguard throws you into the city jail.\n");

    say("The cityguard takes "+QTNAME(tp)+" away.\n",tp);
    tp->move_living("with the cityguard", PRISON);
    PRISON->jail_time(tp, 360);
    say(QCTNAME(TO)+" leaves with "+QTNAME(tp)+" to the city jail.\n", tp);
    TO->move_living("M", MINAS_DIR + "rooms/mtoffice");
    tell_room(ENV(TO), LANG_ADDART(query_nonmet_name())+" arrives.\n");
    tp->remove_prop("_gondor_quest_smuggler_runaway");
    tp->remove_prop("_attacked_mt_gate");
    tp->remove_prop("_gondor_quest_is_smuggler");
    set_alarm(15.0, 0.0, "get_back");
    return 1;
}
#endif

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != CHAINS_SUBLOC)
        return ::show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You have ";
    else
	str = CAP(me->query_pronoun()) + " has ";

    str += "been put under arrest by the cityguard of Minas Tirith.\n"
        +  "Hands and feet are tied by heavy chains.\n";

    return str;
}

