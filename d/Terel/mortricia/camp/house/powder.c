/* Some stone powder. Mortricia 921002.  */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#define TP      this_player()
#define TO      this_object()
#define ETO     environment(TO)
#define ETP     environment(TP)
#define NF(xx)  notify_fail(xx)
#define SNAKE   "/d/Terel/mortricia/camp/house/snake"
#define OCTO    "/d/Terel/common/town/mansion/mon/octo"
#define G_OBJ   "/d/Terel/mortricia/camp/house/ghost_obj"

public void throw_back(object to, object from);

public void
init()
{
    ::init();
    if (ETO == TP) add_action("do_throw", "throw");
}

public void
create_object()
{
    set_name("powder");
    set_adj("sandish");
    set_short("@@my_short");
    set_pshort("@@my_pshort");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 60);
}

public string
my_short()
{
    return "handful of "+TO->query_adj()+" powder";
}

public string
my_pshort()
{
    return "handfuls of "+TO->query_adj()+" powder";
}

public string
my_long()
{
    return "It is some fine "+TO->query_adj()+" powder. " +
	   "It looks as if it used to be a stone of some kind.\n";
}

public int
do_throw(string str)
{
    string what, who;
    object *obs;

    NF("Throw what?\n");
    if (!str) return 0;
    if (sscanf(str, "%s at %s", what, who) != 2) {
        what = str;
        who = "";
    }
    obs = FIND_STR_IN_OBJECT(what, TP);
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return 0;
    if (obs[0] != TO) return 0;
    if (strlen(who) == 0) {
        write("You throw the "+short()+".\n");
        say(QCTNAME(TP)+" throws "+LANG_ADDART(short())+".\n");
        obs[0]->move(ETP);
        return 1;
    }
    obs = FIND_STR_IN_OBJECT(who, ETP);
    NF("Throw "+short()+" at who?\n");
    if (sizeof(obs) == 0) return 0;
    if (!CAN_SEE(TP, obs[0])) return 0;
    if (obs[0] == TP) return 0;
    if (living(obs[0])) {
        TP->catch_msg("You throw the " + short() + " at " +
                      QTNAME(obs[0]) + ".\n");
        obs[0]->catch_msg(QCTNAME(TP) + " throws " + LANG_ADDART(short()) +
                          " at you.\n");
        say(QCTNAME(TP) + " throws " + LANG_ADDART(short()) + " at " +
            QTNAME(obs[0]) + ".\n", ({TP, obs[0]}));
        if (obs[0]->query_wiz_level()) {
            tell_room(ETP, "The "+short()+" dissolves in the air.\n");
            remove_object();
        }
        if (TO->move(obs[0])) {
            TO->move(environment(obs[0]));
        }
    } else {
        return 0;
    }
    return 1;
}

public void
enter_env(object to, object from)
{
    int i;
    object *all;

    ::enter_env(to, from);
    if (MASTER_OB(to) == SNAKE && adjectiv_id("black")) {
        to->attack_other_snakes();
        return;
    }
    if (MASTER_OB(to) == OCTO && adjectiv_id("white")) {
        to->self_destruction();
        return;
    }
    if (adjectiv_id("glowing")) {
        all = all_inventory(to);
        for (i=0; i<sizeof(all); i++) {
            if (MASTER_OB(all[i]) == G_OBJ) {
                all[i]->remove_object();
            }
        }
    }
    if (to->query_npc() && function_exists("create_monster", to)) {
        set_alarm(4.0, -1.0, &throw_back(to, from));
    }
}

public void
throw_back(object to, object from)
{
    if (to && from && living(to) && living(from) &&
        environment(to) == environment(from) && environment(TO) == to) {
        to->command("throw " + query_name() + " at " +
                    lower_case(from->query_name()));
    }
}
