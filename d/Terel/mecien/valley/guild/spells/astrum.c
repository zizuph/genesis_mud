#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <comb_mag.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO   this_object()
#define TP   this_player()
#define ETP  environment(TP)
#define COST 50
#define SUC  30

/*
public void summon_star(object who);
*/

nomask mixed
astrum(string str)
{
    int suc;
   object who;
    object pend = present(MYSTIC_PENDANT, TP);
    
    if (TP->query_mana() < COST)
        return "You do not possess the strength.\n";
    if (NPMAGIC(TP))
        return "Somehow your call to the stars fails here.\n";
    if (!pend)
        return "You do not possess the pendant.\n";

    suc  = random(TP->query_stat(SS_WIS));
    suc += random(TP->query_skill(SS_SPELLCRAFT));
    if (suc < random(SUC)) {
        TP->add_mana(-COST/3);
        return "Your call to the stars fails.\n";
    }

    write("You clutch your " + pend->short() +
          " and sing out to the glory of the stars.\n");
    say(QCTNAME(TP) + " looks upwards, holds aloft a " +
        pend->short() + " and incants a mysterious song.\n", TP);

   who = TP;
   set_alarm(10.0, -1.0, "summon_star", TP);
/*
    set_alarm(10.0, -1.0, &summon_star(TP));
*/

    TP->add_mana(-COST);
    return 1;
}

public void
summon_star(object who)
{
   object star;
   
   if (!who || NPMAGIC(who)) return;
   seteuid(getuid());
   
   star = clone_object(SPELL_DIR + "star_spirit");
       
    star->move_living("X", environment(who));
   star->set_master(who);
   star->set_duration(who->query_stat(SS_WIS) +
                      random(who->query_skill(SS_ELEMENT_FIRE)));
   star->master();
}

