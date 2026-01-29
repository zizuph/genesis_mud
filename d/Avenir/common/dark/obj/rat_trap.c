// Rat trap, part of rat trap quest.
// Made by Boriska@Genesis, Nov 1994
// Nov 20, Lilith: updated code to use functionpointers
//                 added additional verbs for setting trap.

inherit "/std/object";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/rat_trap.h"

object set_by = 0;
int stink_alarm;
string my_long();
string my_short();
object query_set_by();

create_object()
{
    set_name ("trap");
    add_name (TRAP_ID);
    set_short (my_short);
    add_adj ("rat");
    set_long (my_long);

    add_prop (OBJ_I_WEIGHT, 2000);
    add_prop (OBJ_I_VOLUME, 1000);
    add_prop (OBJ_I_VALUE, 100);
}
  
string
my_long()
{
    string str = 
        "Simple device consisting of a wooden base with rusty metal\n" +
        "cage on it. The cage door can be triggered by a spring having\n" +
        "a hook for attaching a bait. ";
  
    return set_by ? str + "The trap is set now.\n" :
        str + "The trap is not set.\n";
}

string
my_short()
{
    return set_by ? "rat trap is set here" : "rat trap";
}


int
do_set (string str)
{
    object tp = this_player();
    object meat;
    object rat;
  
    notify_fail ("Set what?\n");
    if (!str || str != "trap")
        return 0;

    if (query_set_by())
    {
        tp->catch_msg (
	   "The trap is set already, so you just lay it on the ground.\n");
        say (QCTNAME(tp) + " lays the rat trap on the ground.\n");
        move(environment(tp));
        if (rat = present (RAT_ALIVE_ID, environment()))
            rat->start_trap_seq(this_object());
        return 1;
    }
  
    if (!(meat = present (MEAT_ID, tp)))
    {
        tp->catch_msg (
            "You lack something for setting your trap properly.\n");
        return 1;
    }

    tp->catch_msg (
	"Using piece of meat as bait you set the trap and conceal it\n" +
        "as well as you can. Now you should just wait...\n");
    say (QCTNAME(tp) + " skillfully sets the rat trap.\n");
    set_by = tp;
    move(environment(tp));
    // make meat heap smaller
    meat->set_heap_size(meat->num_heap() - 1 );
    stink_alarm = set_alarm (10.0, 200.0, "stink");

    if (rat = present (RAT_ALIVE_ID, environment()))
        rat->start_trap_seq(this_object());
    return 1;
}

private void
stink ()
{
    tell_room (environment(),
        "An awful stench rises from inside the trap.\n"); 
}

object
query_set_by () { return set_by; }

void
disarm_trap() 
{
    set_by = 0;
    remove_alarm(stink_alarm);
}

void
init()
{
    ::init();
    add_action (do_set, "set");
    add_action (do_set, "lay");
    add_action (do_set, "place");
    add_action (do_set, "bait");
    add_action (do_set, "rig");
}
