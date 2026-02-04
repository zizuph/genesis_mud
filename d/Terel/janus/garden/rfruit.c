/*  rfruit.c */
/*  janus 920831 */
inherit "/std/food";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define TP             this_player()
#define TO             this_object()
#define ETO            environment(TO)

int aid = 0;

public void
create_food()
{
    set_name("fruit");
    add_name("red fruit");
    set_short("fruit");
    set_amount(0);
    set_adj("red");
    set_long("A peanut sized red fruit.\n");
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop("is_mixable",1);
}

public void
do_puke(object who)
{
    if (!who || ETO != who) {
        aid = 0;
        remove_object();
        return;
    }
       
    who->catch_msg("Suddenly the fruit and the rest of your stomach content " +
                   "burst from your mouth in a wet, soursmelling cascade.\n");
    tell_room(environment(who),
              "A huge cascade of half digested food comes from " + QTNAME(who) +
              "'s mouth. A sour smell permeates the air.\n", who);
    who->reduce_hit_point(50);
    if (who->query_hp() <= 0) who->do_die(TO);
    aid = 0;
    remove_object();
}

public int
do_eat(string str)
{
     object diploma;
     
     if (!id(str) || aid) return 0;
     
     diploma = present("diploma", TP);

     if (diploma) {
         write("Since your gardening course is still fresh in memory " +
               "you recognize this fruit as slightly poisonous. " +
               "Eating it will probably cause some stomach problems, " +
               "so you refrain from eating it.\n");
     } else {
         set_amount(-100);
         write("The fruit tastes bad, YEUCH. Your stomach is in uproar.\n");
         say(QCTNAME(TP)+" eats something. "+QTNAME(TP)+" face takes on a " +
             "green tinge.\n");
         set_no_show();
         add_prop(OBJ_M_NO_DROP, 1);
         aid = set_alarm(60.0, -1.0, &do_puke(TP));
     }
     return 1;
}

public void
init()
{
    ::init();
    add_action(do_eat,"eat");
}

public string
query_recover()
{
    if (aid) return "";
    
    return MASTER;
}
