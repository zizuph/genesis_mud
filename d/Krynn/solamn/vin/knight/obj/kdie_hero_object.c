inherit "/std/poison_effect";
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#define HERO_SUBLOC   "hero_subloc"
#define DURATION 1000 + random(500)
#define KDIE_LOG KLOG + "kdie_log"

object who;

int
cure_poison(string *cure_type, int success)
{
    return 0;
}

void
create_poison_effect()
{
    recovery = 1;
    set_interval(DURATION);
    set_silent(2);
    set_time((DURATION /2));
    set_damage(({ POISON_FATIGUE, 1, POISON_HP, 1, POISON_STAT, SS_WIS }));
    set_strength(100);
    seteuid(getuid(TO));
}

init()
{
    initialize();
    ::init();
}

void
initialize()
{
    who = E(TO);
    who->set_stat_extra(0, (who->query_stat(0)/2));
    who->set_stat_extra(5, (who->query_stat(5)/2));
    who->add_prop(LIVE_I_QUICKNESS, 100);
    who->set_fatigue(TP->query_max_fatigue());
    who->heal_hp(TP->query_max_hp() / 2);
    who->add_prop("_knight_hero_prop", 1);
    who->add_subloc(HERO_SUBLOC, TO);
}

public void
timeout()
{
    remove_alarm(a_dam);
    set_alarm(2.0, 0.0, remove_object);
    who = E(TO);
    who->set_stat_extra(0, 0);
    who->set_stat_extra(5, 0);
    who->remove_prop(LIVE_I_QUICKNESS);
    who->remove_prop("_knight_hero_prop");
    who->remove_subloc(HERO_SUBLOC);

    if(!(random(2)))
    {
	who->catch_msg("You glance down at your many wounds, and are astonished to "+
	  "see the severity of them! You realize that you are dying.\n\n");
	set_alarm(1.0, 0.0, "message1", who);
	return;
    }

    who->catch_msg("You glance down at your many wounds, astonished that you cannot "+
      "recall getting most of them. You realize that you have survived, but you "+
      "are both physically and mentally exhausted.\n");
    tell_room(E(who), who->query_The_name(TP)+" glances down at "+ POSSESSIVE(who)+
      " near-mortal many wounds, and smiles proudly as "+PRONOUN(who)+" narrowly "+
      "escapes death.\n", who);
    write_file(KDIE_LOG, ctime(time()) + ", "+TP->query_name()+
      " survived kdie.\n");
    if (who->query_fatigue() > (TP->query_max_fatigue() / 10))
	who->set_fatigue((TP->query_max_fatigue() / 10));
    if (who->query_hp() > (TP->query_max_hp() / 10))
	who->set_hp((TP->query_max_hp() / 10));
    if (who->query_mana() > (TP->query_max_mana() / 10))
   who->set_mana((TP->query_max_mana() / 10));
}

void
message1(object who)
{
    who->catch_msg("In the distance you hear the clarion call of trumpets...\n\n"+
      "A warm peace washes over you, as you are enveloped in a brilliant, "+
      "life-giving light, and you look up instinctively... \n\n"+
      "...into a soft visage that could only be the face of...\n");
    tell_room(E(who), who->query_The_name(TP)+"'s eyes glaze over and "+PRONOUN(who)+
      " stares blankly into the sky.\n\n", who);
    tell_room(E(who), who->query_The_name(TP)+" is suddenly gone.\n", who);
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    who->heal_hp(-who->query_hp());
    write_file(KDIE_LOG, ctime(time()) + ", "+TP->query_name()+
      " perished using kdie. :)\n");
    who->do_die(TO);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{

    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if(for_obj == carrier)
	str = "";
    else
	str = C(PRONOUN(carrier))+" seems to be confident despite all, fearless "+
	"in the face of danger, virtually unstoppable.\n";

    return str;
}

