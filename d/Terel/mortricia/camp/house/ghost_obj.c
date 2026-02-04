/*
 * A ghost object, makes the player into a ghost as long as
 * it is in the inventory, used in Spectre's quest.
 */

inherit "/std/object";
#include <macros.h>

#define TO            this_object()
#define TP            this_player()
#define WHERE         environment(TO)

object find_q_ring(int q_no, object ob);
int query_ghost_object();

int ghost_set_by_me = 0;

create_object()
{
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (living(dest) && find_q_ring(7, dest)) {
        dest->catch_msg("You have become a ghost.\n");
        dest->set_ghost(1);
        ghost_set_by_me = 1;
    }
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from) && from->query_ghost() && ghost_set_by_me) {
        from->set_ghost(0);
        ghost_set_by_me = 0;
        from->catch_msg("You stop being a ghost.\n");
    }
}

object
find_q_ring(int q_no, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_prop("q_number") == q_no &&
            ob_arr[i]->query_prop("q_solver") == ob->query_name()) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

string
stat_object()
{
    string s;

    s = ::stat_object();
    s += "This is a quest object, be cautious when removing it.\n";

    return s;
}

int
query_ghost_object()
{
    return 1;
}
