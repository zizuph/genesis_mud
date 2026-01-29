inherit "/d/Gondor/pelargir/npc/ruffian.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_WEIGHT	1000

void
create_thief()
{
   set_name(({"urchin","boy"}));
   set_adj(({"smiling", "young", }));
   set_short("young urchin");
   set_pshort("young urchins");
   set_long("A smiling young boy.\n");

   set_act_time(2);
   add_act("peek all");
   add_act("sigh");
   add_act(VBFC_ME("do_steal"));

   set_chat_time(10);
   add_chat("Can't see me!");
   add_chat("I'm not doing anyone any harm.");
   add_chat("I have to earn a living somehow, you know.");
   add_chat("That sure is some nice stuff you got there.");
   add_chat("Spare a copper?");
   add_chat("These sailors don't have anything worth taking.");
   add_chat("You wouldn't hurt an orphan, would you??");

   set_act_time(5);
   add_act("peek all");
   add_act("sigh");
   add_act(VBFC_ME("do_steal"));

   set_random_move(10);
   set_restrain_path(PELAR_DIR + "docks");
   set_whimpy(50);

   add_prop(LIVE_I_NEVERKNOWN, 1);
}

nomask void
create_ruffian()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    add_name("thief");

    set_stats(({ 5 + rnd1,  5 + rnd2,  5 + (rnd1 + rnd2) / 2,
                10 + rnd1 / 2, 10 + rnd2 / 2, 5 + rnd1 + rnd2 / 2}));

    set_alignment(-150);

    set_skill(SS_WEP_KNIFE, 10 + rnd1);
    set_skill(SS_DEFENCE,   10 + rnd2);
    set_skill(SS_PARRY,      1 + rnd1 / 2);

    set_skill(SS_SNEAK, 30 + rnd1);
    set_skill(SS_HIDE,  40 + rnd2);
    set_skill(SS_PICK_POCKET, 40 + (rnd1 + rnd2) / 2);

    create_thief();
}

/*
 * This function makes the thief sneak when moving randomly
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    return "sneak "+exit;
}

int
query_worn_or_wielded(object x)
{
    return (objectp(x->query_worn()) || objectp(x->query_wielded()));
}

int
query_weight(object x)
{
    return !( (x->query_prop(HEAP_I_IS) &&
              (x->query_prop(HEAP_I_UNIT_WEIGHT) < MAX_WEIGHT)) ||
              (x->query_prop(OBJ_I_WEIGHT) < MAX_WEIGHT) );
}

varargs void
sneak_away(string dir)
{
    string *dirs;

    if (strlen(dir))
    {
        command("sneak "+dir);
        return;
    }

    dirs = ENV(TO)->query_exit_cmds();

    dir = ONE_OF_LIST(dirs);

    command("sneak "+dir);
    sneak_away(dir);
}

string
do_steal()
{
    int     skpp = query_skill(SS_PICK_POCKET),
            v_aware;
    object *arr,
            victim,
            item;

    if (!sizeof(arr = FILTER_PLAYERS(all_inventory(ENV(TO)))))
        return "";
    victim = ONE_OF_LIST(arr);

    v_aware = victim->query_skill(SS_AWARENESS);

    if (CAN_SEE(victim, TO))
        skpp /= 2;

    skpp += random(skpp);

    if (skpp < (v_aware / 2))
    {
        tell_room(ENV(TO), QCTNAME(TO) + " clumsily tries to steal "
          + "something from " + QTNAME(victim) + ", but fails.\n",
          ({ TO, victim }));
        victim->catch_msg(QCTNAME(TO) + " clumsily tries to steal "
          + "something from you but fails.\n");
        sneak_away();
        return "";
    }

    if (skpp < v_aware)
        return "";

    arr = FILTER_SHOWN(all_inventory(victim));
//  dump_array(arr);
    arr -= filter(arr, &operator(!=)(0) @ &->query_prop(OBJ_M_NO_DROP));
//  dump_array(arr);
    arr -= filter(arr, &operator(!=)(0) @ &->query_prop(OBJ_M_NO_GIVE));
//  dump_array(arr);
    arr -= filter(arr, &operator(!=)(0) @ &->query_prop(OBJ_M_NO_STEAL));
//  dump_array(arr);
    arr -= filter(arr, query_worn_or_wielded);
//  dump_array(arr);
    arr -= filter(arr, query_weight);
//  dump_array(arr);

    if (!sizeof(arr))
        return "";

    item = ONE_OF_LIST(arr);

    if (item->query_prop(HEAP_I_IS))
    {
        item->split_heap(1);
        tell_room(ENV(TO), QCTNAME(TO) + " steals " + (item->short())
          + " from " + QTNAME(victim) + ".\n", ({ TO, victim }));
        victim->catch_msg(QCTNAME(TO) + " steals " + (item->short())
          + " from you!\n");
    }
    else
    {
        tell_room(ENV(TO), QCTNAME(TO) + " steals " + LANG_ADDART(item->short())
          + " from " + QTNAME(victim) + ".\n", ({ TO, victim }));
        victim->catch_msg(QCTNAME(TO) + " steals " + LANG_ADDART(item->short())
          + " from you!\n");
    }
    item->move(TO);
    sneak_away();

    return "";
}

