/* Key to the slave collar at the Neraka Slavemaster's hut
   Ashlar, 13 Jul 97
*/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
inherit "/std/key";
inherit "/lib/keep";

// #define DEBUG(x)    find_player("ashlar")->catch_msg("NHUT: " + x + "\n")

int ratty_alarm;
int prop_set;

void
create_key() 
{
    set_name("key");
    add_name("_neraka_slave_key_");
    set_short("small iron key");
    set_adj("small");
    add_adj("iron");
    set_long("This is a small iron key without any particular markings. " +
        "It is scratched and worn, having seen much usage.\n");
   
   set_key(SLAVE_KEY);
   ratty_alarm = 0;
}

void
do_ratty()
{
    object rat;
    remove_prop(OBJ_M_NO_GET);
    setuid();
    seteuid(getuid(this_object()));
    rat = clone_object(NNPC + "key_rat");
    rat->move_living("M",E(TO));
    rat->set_key(TO);
    move(rat,1);
}

/* This is called when someone tries to take a newly found key
   from among the straw */
string
foil1()
{
    object p = TP;

    if(!ratty_alarm)
    {
        ratty_alarm = set_alarm(0.5,0.0, do_ratty);
        tell_room(E(TO),QCTNAME(p) + " bends to pick up something, but " +
            "a rat darts out and grabs the thing in its mouth. The rat " +
            "runs into a corner and chitters gleefully. " + QCTNAME(p) +
            " shakes " + HIS(p) + " fist at the rat in frustration.\n", p);
    }

    return "As you reach for the " + short() + ", a rat darts out " +
        "and grabs the key in its mouth. The rat runs into a corner and " +
        "chitters gleefully. You shake your fist at the rat in " +
        "frustration.\n";
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!prop_set && interactive(env))
    {
        env->add_prop(NERAKA_I_FOUND_THE_SLAVE_KEY, 1);
        prop_set = 1;
    }
}
