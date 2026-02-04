/*
 * A king's sceptre, used in the final gypsy camp quest
 */
inherit "/std/object";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <wa_types.h>
#include <language.h>

#define TP         this_player()
#define TO         this_object()
#define NF(xx)     notify_fail(xx)
#define SUBLOC     "held_sceptre_subloc"

int held;
string hand = "left";

void hold_me();

public void
create_object()
{
   set_name("sceptre");
   set_adj("royal");
   set_long(
        "A royal sceptre made of pure gold. It is decorated " +
        "diamonds and rubins.\n"
   );
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_VALUE, 0);
}

public string
query_recover()
{
    return MASTER+":"+held;
}

void
init_recover(string str)
{
    held = 0;
    if (!str) return;
    sscanf(str, "%d", held);
}

void
init()
{
   ::init();
   add_action("do_hold", "hold");
   add_action("do_hide", "hide");
}

public void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if (held) set_alarm(2.0, -1.0, hold_me);
}

public void
leave_env(object from, object to)
{
    held = 0;
    if (living(from)) from->remove_subloc(SUBLOC);
    ::leave_env(from, to);
}

public int
do_hold(string str)
{
    object *obs;

    NF("Hold what?\n");
    if (!str) return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(obs) == 0) return 0;
    if (sizeof(obs) > 1) return 0;
    if (obs[0] != TO) return 0;
    NF("It's already held by you.\n");
    if (held) return 0;
    NF("You do not have a hand free.\n");
    if(TP->query_weapon(W_LEFT))  {
        hand = "right";
        if(TP->query_weapon(W_RIGHT))
        return 0;
    }
    hold_me();
    held = 1;
    return 1;
}

void hold_me()
{
    object who;

    who = environment(TO);
    if (!living(who)) return;
    who->catch_msg("You take hold of your "+short()+".\n");
    who->add_subloc(SUBLOC, TO);
}

int
do_hide(string str)
{
    object *obs;

    NF("Hide what?\n");
    if (!str) return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(obs) == 0) return 0;
    if (sizeof(obs) > 1) return 0;
    if (obs[0] != TO) return 0;
    NF("It's already hidden.\n");
    if (!held) return 0;
    write("You hide your "+short()+".\n");
    TP->remove_subloc(SUBLOC);
    held = 0;
    return 1;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (for_obj == carrier)
        str = "You are holding your "+short()+".\n";
    else
        str = capitalize(carrier->query_pronoun()) +
        " holds "+LANG_ADDART(short())+".\n";

    return str;
}
