/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pearl.c
 *
 * A large black pearl
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>
#include <macros.h>

#define LIGHT_TIME 50 + random(10)

int lit=0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    
    set_name("pearl");
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    set_adj("large");
    add_adj("black");

    add_prop(OBJ_I_VALUE,  900 + random(100));
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 18);
    add_prop(OBJ_S_WIZINFO, "A magic pearl. Shines when polished and plays " +
                            "also a part in the magician's quest in the " +
                            "gypsy camp in Terel.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({"This pearl is Penthir's treasure. It shines " +
                                 "for a while if polished.\n", 30 }));
}

public string
my_short()
{
    if (lit)
        return "large white pearl";
    else
        return "large black pearl";
}

public string
my_long()
{
    if (lit)
        return "It's a large white pearl. It shines brightly.\n";
    else
        return "It's a large black pearl. It looks a bit dull. " +
               "Maybe you can make it shine?\n";
}

/*
 * Function name: do_light
 * Description:   Revert back to normal description.
 * Arguments:     me - give a message pearl still in player inventory
 */
public void
do_light(object me)
{
    add_prop(OBJ_I_LIGHT, 0);
    lit = 0;
    remove_adj("white");
    add_adj("black");
    if (ETO->query_prop(ROOM_I_IS))
        ETO->update_light(1);
    else if (environment(ETO)->query_prop(ROOM_I_IS))
        environment(ETO)->update_light(1);
        
    if (me && (me == ETO || environment(me) == ETO))
        me->catch_msg("The pearl stops shining.\n");
}

/*
 * Function name: do_polish
 * Description:   Handle the polish action
 * Returns:       1/0
 */
public int
do_polish(string what)
{
    object ob;

    NF("Polish what?\n");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    write("You polish the pearl.\n");
    say(QCTNAME(TP) + " polishes a pearl.\n");
    
    if (lit) {
        write("Nothing happens.\n");
        return 1;
    }
    
    if (TO->query_prop("q_solver") == TO->query_name()) {
        TO->add_prop("q_solver", TP->query_name());
    }
    
    write("You notice that the pearl has changed.\n");
    lit = 1;
    remove_adj("black");
    add_adj("white");
    
    add_prop(OBJ_I_LIGHT, 1 + TP->query_skill(SS_ELEMENT_FIRE)/10);
    if (ETO->query_prop(ROOM_I_IS))
        ETO->update_light(1);
    else if (ETP->query_prop(ROOM_I_IS))
        ETP->update_light(1);

    set_alarm(itof(LIGHT_TIME + TP->query_skill(SS_ELEMENT_FIRE)),
              -1.0, &do_light(TP));
    
    return 1;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
    add_action(do_polish, "polish");
}

public string
query_recover()
{
    return MASTER + ":" + query_prop("q_solver");
}

public void
init_recover(string arg)
{
    if (strlen(arg))
        add_prop("q_solver", arg); 
}
