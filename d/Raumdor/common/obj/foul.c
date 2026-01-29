/*
  code that fouls food/drinks, made by Valen, based on original made by Sarr
*/

#include <files.h>
#include <macros.h>
#include <composite.h>

#define ROTTEN_FOOD     "/d/Raumdor/common/obj/rot_new"
#define ROTTEN_DRINK    "/d/Raumdor/common/obj/drot_new"

int filter_foul(object ob)
{
    if (IS_DRINK_OBJECT(ob) || IS_FOOD_OBJECT(ob))
    {
      if(ob->query_prop("_no_raumdor_foul") ||
         ob->id("_event_egg_")) return 0;
      return 1;
    }
    return 0;
}

public void
foul(object who)
{
    object *all;
    int i;
    int plural;
    string compdesc;

    if(!living(who) || environment(who) != environment(this_object())) return;

    who->catch_msg("A black aura surrounds the " + this_object()->short() + ".\n");

    all = filter(deep_inventory(who), filter_foul);

    i = sizeof(all);

    if(i == 0) return;

    plural = (i > 1 || all[0]->num_heap() > 1);
    compdesc = COMPOSITE_DEAD(all);

    for (i--; i >= 0; i--)
    {
        object ob = all[i];
        object repl;
        object env;

        if(IS_FOOD_OBJECT(ob))
        {
            repl = clone_object(ROTTEN_FOOD);
        }
        else
        {
            repl = clone_object(ROTTEN_DRINK);
        }

        repl->set_name(ob->query_name());
        repl->set_adj(ob->query_adj(-1));
        repl->set_short("rotting " + ob->singular_short(who));
        repl->set_long(ob->long() + "Its been fouled.\n");
        repl->set_amount(ob->query_amount());
        repl->set_heap_size(ob->num_heap());

        env = environment(ob);
        ob->remove_object();

        repl->move(env,1);
    }

    who->catch_msg("You notice " + compdesc + (plural ? " are" : " is") +
        " fouled by the black aura!\n");

    tell_room(environment(who), "You notice " + compdesc +
        " owned by " + QTNAME(who) + (plural ? " are" : " is") +
        " fouled by the black aura!\n", who);
}

