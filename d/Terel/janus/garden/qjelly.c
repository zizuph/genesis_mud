/*  qjelly */
/*  janus 930715 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define TP             this_player()
#define TO             this_object()
#define ETO            environment(TO)

int aid = 0;

public void
create_object()
{
  set_name("jelly");
  set_adj("red");
  add_adj("clear");
  set_long("A clear red jelly in a thin flexible membrane. " +
           "There is a faint acrid smell eminating from it. The " +
           "jelly seems to be about a mouthful, though who would " +
           "be crazy to eat it?\n");
  add_prop(OBJ_I_WEIGHT,100);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE, 500);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop("is_mixable",1);
}

public void
do_bamse(object who)
{
    if (!who || ETO != who) {
        aid = 0;
        remove_object();
        return;
    }
    who->catch_msg("Your muscular spasms stop and you feel how energy " +
                   "surges through your body and how your muscles grow " +
                   "stronger.\n");
    tell_room(environment(who), QCTNAME(who) + " stops having muscular " +
              "spasms and look much better.\n", who);
    who->add_tmp_stat(SS_STR, 10, 6);
    who->set_prop("_ate_qjelly_", 1);
    aid = 0;
    remove_object();
}

public int
do_eat(string str)
{
     if (!id(str) || aid) return 0;
     
     write("You feel the jelly slide down your throat with a "+
           "burning sensation, all your muscles in your body "+
           "starts to contract in strong spasms. Was it really "+
           "wise to eat this?\n");
     say(QCTNAME(TP) + " eats some red jelly and you see how " +
         TP->query_pronoun() +
         " starts to suffer severe muscular spasms.\n");
     add_prop(OBJ_M_NO_DROP, 1);
     set_no_show();
     aid = set_alarm(10.0, -1.0, &do_bamse(TP));
     
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
