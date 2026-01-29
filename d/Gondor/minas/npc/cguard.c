/* The guard who checks for the herb in the players inventory
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/minas/npc/std_gondor_guard";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

#define PRISON "/d/Gondor/minas/rooms/prison"


#define WEP_ARRAY1 ({WEP_DIR + "dlongsword", WEP_DIR + "gspear", \
	WEP_DIR+"hhalberd"})
#define WEP_ARRAY2 ({WEP_DIR + "grapier", ARM_DIR + "gshield"})
#define ARM_ARRAY1 ({ARM_DIR + "gchainmail"})
#define ARM_ARRAY2 ({ARM_DIR + "ghelmet"})

int     alarm_id = 0;

void
create_monster()
{
    seteuid(getuid(TO));
    ::create_monster();
    set_name(({"cityguard"}));
    set_short("strong cityguard");
    set_long(BSN("This is one of the guards of Minas Tirith, guarding "
      + "the gates and walls from trespassers and unwanted persons. "
      + "He looks quite competent in fighting, as all guards get training "
      + "with the garrison once a week."));
    set_pshort("strong cityguards");
    default_config_npc(random(10)+65);
    set_base_stat(SS_CON,random(10)+85);
    set_base_stat(SS_DIS,random(15)+95);
    set_skill(SS_WEP_SWORD, random(10)+80);
    set_skill(SS_WEP_POLEARM, random(10)+75);
    set_skill(SS_2H_COMBAT, random(10)+75);
    set_skill(SS_PARRY,85);
    set_skill(SS_DEFENCE,85);
    set_skill(SS_AWARENESS,30);
    set_alignment(250 + random(250));

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_VOLUME, 60000);
    add_prop(CONT_I_HEIGHT,   180);

    set_chat_time(20);
    add_chat("Looks like the War is drawing nigh.");
    add_chat("What are you hanging around here for?");
    add_chat("Minas Tirith is a well-guarded city.");
    add_chat("I fear the armies of the Evil One.");
    add_chat("The Walls and the Gates are strong, "
	+ "but are they strong enough?");
    add_chat("Don't hang around too long here.");
    add_chat("I don't like trouble.");
    add_chat("I don't like the dark clouds gathering in the east.");
}

int
herb_test(object pl)
{
    if (pl->query_prop("_gondor_quest_is_smuggler"))
    {
        if (pl->query_prop("_gondor_quest_smuggler_runaway"))
            set_alarm(0.0, 0.0, "kill_smuggler", pl);
        else if (present("smuggler_quest_herb",pl))
            set_alarm(2.0, 0.0, "warning", pl);
        else
            set_alarm(2.0, 0.0, "suspicious", pl);
      return 1;
    }
}

void
init_living() 
{
    ::init_living();   

    add_action("surrender","surrender");
    herb_test(TP);
}

void
set_arm_arrays()
{
    ::set_arm_arrays();
    wep1 = WEP_ARRAY1;
    wep2 = WEP_ARRAY2;
    arm1 = ARM_ARRAY1;
    arm2 = ARM_ARRAY2;
}

void
kill_smuggler(object pl)
{
    if (!objectp(pl))
        return;
    if (ENV(pl) != ENV(TO))
        return;
    if (pl == query_attack())
        return;
    command("say Hah! There you are, "+pl->query_nonmet_name()+"!");
    add_prop(LIVE_O_ENEMY_CLING,pl);
    command("kill "+pl->query_real_name());
}

void
suspicious(object pl)
{
    if (!objectp(pl))
        return;
    if (ENV(pl) != ENV(TO))
        return;
    tell_room(ENV(TO), "The cityguard looks suspiciously at "+
	QTNAME(pl)+"\n"+"but lets "+pl->query_objective()+" pass.\n",pl);
    tell_object(pl,"The cityguard looks suspiciously at you, "+
	"but lets you pass.\n");
}

void
warning(object pl) 
{
    if (!objectp(pl))
        return;

    pl->add_prop("_gondor_quest_smuggler_runaway",1);
    if (ENV(pl) != ENV(TO))
    {
        command("say No! "+CAP(pl->query_pronoun())+" got away!");
        command("shout Stop that "+pl->query_nonmet_name()+"! Smuggler!");
	return;
    }

    command("say That herb you have is illegal, "+pl->query_nonmet_name()+"!");
    command("say Surrender and come with me peacefully at once, "+
	"or you are dead!");
    tell_room(ENV(TO),"The cityguard stares at "+
        QTNAME(pl)+" and prepares his weapon.\n",pl);
    tell_object(pl,"The cityguard stares at you, and prepares his sword!\n");
    set_alarm(10.0, 0.0, "fight_smuggler", pl);
}

void
fight_smuggler(object pl) 
{
    if (!objectp(pl))
        return;
    if (ENV(pl) != ENV(TO))
    {
        command("say No! "+CAP(pl->query_pronoun())+" got away!");
        command("shout Stop that "+pl->query_nonmet_name()+"! Smuggler!");
    }
    command("say I warned you!");
    add_prop(LIVE_O_ENEMY_CLING,pl);
    command("kill "+pl->query_real_name());
}

int
surrender() 
{
    int     i;
    object  herb,
            tp = TP,
           *enemies;

    if (!tp->query_prop("_gondor_quest_smuggler_runaway") &&
    (tp != query_attack()))
    {
        command("say Why do you want to surrender, "+
		tp->query_nonmet_name()+"?");
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

void
get_back()
{
    command("say I have to get back to work.");
    move_living("south", MINAS_DIR + "gate1");
    command("say I'm back again.");
}

int query_knight_prestige() { return -8; }
