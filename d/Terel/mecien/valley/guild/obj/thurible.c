/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/container.c";
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define BURN_TIME   70
#define TP          this_player()
#define TO          this_object()
#define ETO         environment(TO)
#define ETP         environment(TP)
#define EN environment

public void burn_out(object ob);

int lit, loaded, aid = 0;

public string
query_auto_load()
{
    return MASTER;
}

public void
init()
{
    ::init();
    add_action("do_meditate","meditate");
    add_action("do_load", "load");
    add_action("do_load", "fill");
    add_action("do_light","light");
    add_action("catch_put","put");
     add_action("do_swing", "swing");
}

public int
catch_put(string str)
{
    string foo;
    object ob;

    if (parse_command(str, ETO, "%s 'in' / 'into' %o", foo, ob)) {
        if (ob == TO) {
            write("Only incense may be loaded into the thurible.\n");
            return 1;
        }
    }
    return 0;
}

public void
create_container()
{
    set_name("thurible");
    add_name("burner");
    add_adj("holy");
    set_long("This is a small device, carefully crafted of brass " +
          "and beautifully worked. It is designed to hold burning " +
          "incense and to provide a focus for meditation. You may load " +
          "the thurible with incense, light the incense, and meditate " +
          "upon the ancients.\n");
    add_prop(CONT_I_MAX_WEIGHT, 250);
    add_prop(CONT_I_MAX_VOLUME, 500);
    add_prop(CONT_I_WEIGHT, 25);
    add_prop(CONT_I_VOLUME, 50);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, "You needn't sell the holy thurible. Once " +
             "bought, it will remain with you always.\n");
    loaded = 0;
    lit = 0;
}

public int
do_load(string str)
{
    object ob1, ob2;

    if (parse_command(str, ETO, "%o 'with' %o", ob1, ob2)) {
        if (ob1 == TO && ob2->id("incense")) {
            if (!loaded) {
                ob2->move(TO);
                write("You load the thurible with " + ob2->short() +
                      ".\n");
                loaded = 1;
                return 1;
            } else {
                notify_fail("The thurible is already loaded!\n");
                return 0;
            }
        } else {
            notify_fail("You may only load the thurible with the " +
                        "mystic incense.\n");
            return 0;
        }
    }
    if (parse_command(str, ETO, "%o 'into' %o", ob1, ob2)) {
        if (ob1->id("incense") && ob2 == TO) {
            if (!loaded) {
                ob1->move(TO);
                write("You load the " + ob1->short() +
                      " into the thurible.\n");
                loaded = 1;
                return 1;
            } else {
                notify_fail("The thurible is already loaded!\n");
                return 0;
            }
        } else {
            notify_fail("You may only load the thurible with the " +
                        "mystic incense.\n");
            return 0;
        }
    }
    notify_fail("Load what into what?\n");
    return 0;
}

public int
do_light(string str)
{
    object ob1, ob2;

    if (!str) return 0;
    
    if (parse_command(str, ETO, "%o", ob1)) {
        if (ob1 == TO) {
            if (ob2 = present("incense", TO)) {
                if (!lit) {
                    write("You light the " + ob2->short() +
                          ". Now you can meditate!\n");
                    say(QCTNAME(TP) + " does something with " +
                        TP->query_possessive() + " thurible.\n");
                    aid = set_alarm(itof(BURN_TIME), -1.0, &burn_out(ob2));
                    lit = 1;
                    return 1;
                } else {
                    notify_fail("The incense in the thurible is already burning!\n");
                    return 0;
                }
            } else {
                notify_fail("There is no incense in the thurible!\n");
                return 0;
            }
        } else {
            if (ob1->id("incense")) {
                if (!lit) {
                    write("You light the " + ob1->short() +
                          ". Now you can meditate!\n");
                    say(QCTNAME(TP) + " does something with " +
                        TP->query_possessive() + " thurible.\n");
                    aid = set_alarm(itof(BURN_TIME), -1.0, &burn_out(ob1));
                    lit = 1;
                    return 1;
                } else {
                    notify_fail("The incense in the thurible is already burning!\n");
                    return 0;
                }
            } else {
                notify_fail("What are you trying to light?\n");
                return 0;
            }
        }
    }
    notify_fail("Light what?\n");
    return 0;
}

public void
burn_out(object ob)
{
    if (!ob) ob = present("incense", TO);
    if (ob) {
        if (ETO && living(ETO) && MEMBER(ETO))
            ETO->catch_msg("The " + ob->short() +
                           " in the thurible has burned away.\n");
        ob->remove_object();
    }
    if (aid) {
        remove_alarm(aid);
        aid = 0;
    }
    lit = 0;
    loaded = 0;
}

do_swing(string str){

 object incense;
  int n;

  incense = present("holy_incense", TO);

  if(lit && loaded && incense){
  n = incense->query_uses();
   say(QCTNAME(TP) + " holds up " + TP->query_possessive() + " thurible and swings it back and forth, a cloud of incense issuing forth.\n");
  TP->catch_msg("You raise your thurible and swing it back and forth, allowing a cloud of incense to form.\n");
        if(n > 1) incense->set_uses(n - 1);
else burn_out(incense);
   return 1;
  }

  notify_fail("For some reason the thurible cannot be used ritually.\n");
 return 0;


}

public int
do_meditate(string str)
{
    int u;
    object incense = present("incense", TO);

    if (lit && loaded && incense) {
        say(QCTNAME(TP) + " meditates upon " + TP->query_possessive() +
            " thurible.\n");
        if (incense->do_it(TP)) {
            TP->catch_msg(incense->query_meditate_text());
            u = incense->query_uses();
            if (u > 1)
                incense->set_uses(u - 1);
            else 
                burn_out(incense);
            return 1;
        } else {
            notify_fail("For some reason you cannot concentrate, and " +
                        "the meditation does you little good.\n");
            return 0;
        }
    }
    notify_fail("To meditate, you must first load the thurible " +
                "with incense and light the incense.\n");
    return 0;
}
