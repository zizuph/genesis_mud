inherit "/std/monster";

#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/smis/sys/statserv.h"

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#define TRICK_FILE	"/d/Avenir/event/halloween/mischief"
#define RAND_ONEOF(x)   ((x) [random(sizeof(x))])
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif


int      alarm_id;
object   searcher;

void 
set_searcher(object ob)
{
    searcher = ob;
}

string
query_searcher()
{
    return searcher->query_real_name();
}

void 
create_monster()
{
    set_name("mischief");
    set_living_name("mischief");
    set_race_name("gnome");
    set_adj(({"tricky"}));
    set_long("He is a tricky little gnome with a "
        +"mischievous grin on his face. He seems to "
        +"have travelled a long way.\n");

    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME, 16000);
    add_prop(OBJ_M_NO_ATTACK, "He is under divine protection.");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "He is under divine protection.\n");
    set_stats(({50, 100, 30, 90, 90, 10}));

    set_skill(SS_AWARENESS, 99);
    set_skill(SS_DEFENCE, 99);

    set_act_time(4);
    add_act("say Trick or treat!");
    add_act("sigh impatient");
    add_act("smile misch");
    add_act("sings: I've got something the Horseman wants, the "+
        "the Horseman wants, the Horseman wants!");

    if (searcher)
    {
        add_act("say If "+capitalize(query_searcher()) +" finds me, "+
           "I've got the best treat of all!"); 
        add_act("say If you see "+capitalize(query_searcher()) +", "+                  "tell 'em you saw me and I'm waiting!");   
        add_act("say "+capitalize(query_searcher()) +" is too slow. "+
           "I've got tricks to pull and treats to give!");
    }

}

int 
valid_go(object ob)
{
    if(ob->query_wiz_level() || ob->query_link_dead() 
        || ob->query_ghost() || ENV(ob)->query_prop(ROOM_I_INSIDE))
        return 0;

    return 1;
}

void 
new_place()
{
    object   person,
            *people;

    string   place,
             nihil;


    people = filter(users(), valid_go);
    if(!sizeof(people))
        return;

    person = RAND_ONEOF(people);

    command("emote runs away!");
    set_no_show();
    move(ENV(person), 1);

    run_away();
    run_away();
    run_away();
    run_away();
    run_away();

    unset_no_show();
    set_no_show_composite(0);

    place = lower_case(ENV(TO)->short(TO));

    /* Get rid of punctuation that lazy wizards left in short descs */
    sscanf(place, "%s.", place);

    searcher->catch_msg("The voice of "+QTNAME(TO) +" enters your "
        +"mind, laughing.\n"+QCTNAME(TO)+" says: "
        +"Trick or Treat! Catch me and I'll give you a treat! "
        +"Otherwise I'll keep tricking you! I've gone all the way "
        +"to: "+place+" in "+CAP(ENV(TO)->query_domain())
        +"!\nThe voice and its accompanying laughter fades.\n");
}

void 
start_running()
{
    if(!alarm_id || !sizeof(get_alarm(alarm_id)))
        alarm_id = set_alarm(2.0, 1800.0, new_place);
}

void 
reward(object who)
{
    if(!present(who, ENV(TO)))
        return;

    seteuid(getuid());

    clone_object("/d/Avenir/event/halloween/head")->move(this_object());
    SCROLLING_LOG(TRICK_FILE, capitalize(who->query_name()) +
        " found Mischief and got a head.");
    command("say Trick or Treat! You found me, so here's your treat.");
    command("give head to "+ query_searcher());   
    command("say Turn that in for the scavenger hunt!");
    command("grin misch");
    searcher = 0;
    command("emote goes dashing off again!");
    new_place();
}

void 
init_living()
{
    ::init_living();
    
    if(!searcher || searcher->query_linkdead()
        || searcher->query_attack() || searcher->query_ghost())
    {
        if (interactive(TP))
        {
            set_searcher(TP);
            command("say to "+ TP->query_real_name() +" Tag, you're it!");
            command("say to "+ TP->query_real_name() +" I've got something "+
                "from the Headless Horseman! Catch me and you'll get it!");
            SCROLLING_LOG(TRICK_FILE, "Mischief picked "+ TP->query_name() +
                " to tease.");
        }
        start_running();
        return;
    }    

    if (TP == searcher)
        set_alarm(1.0, 0.0, &reward(TP));
}
