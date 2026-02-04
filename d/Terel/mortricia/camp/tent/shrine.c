/* A shrine */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>

#define BS(xx)        break_string(xx, 70)
#define NF(xx)        notify_fail(xx)
#define BSN(xx)       break_string(xx + "\n", 70)
#define TO            this_object()
#define TP            this_player()

object check_sh_pr(string sh_desc, string prop, object ob);

init()
{
    ::init();
    add_action("do_open", "open");
    add_action("do_close", "close");
    add_action("do_lock", "lock");
    add_action("do_unlock", "unlock");
}

create_container()
{
    set_name("shrine");
    set_short("beautiful shrine");
    set_long("@@my_long");
    set_adj("beautiful");
    add_prop(CONT_I_WEIGHT, 8000);
    add_prop(CONT_I_MAX_WEIGHT, 9000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_LOCK, 0);
    add_prop(OBJ_M_NO_GET, "It is securely fastened to the floor.\n");
    add_prop(OBJ_M_NO_GIVE, "It is securely fastened to the floor.\n");

    add_item(({"lock", "gold lock"}), BSN(
	"The lock seems quite sophisticated and made of gold. " +
	"From the shape of the lock you realise that " +
	"the key needed to open the shrine, must be quite " +
	"different from ordinary keys. Something that is small " +
	"and circular is needed."
    ));
}

do_open(string what)
{
    if (what != "shrine" && what != "beautiful shrine") return 0;

    if (TO -> query_prop(CONT_I_LOCK)) {
	write("The shrine is locked.\n");
	return 1;
    }
    if (!(TO -> query_prop(CONT_I_CLOSED))) {
	write("The shrine is already opened.\n");
	return 1;
    }
    write("You open the shrine.\n");
    add_prop(CONT_I_CLOSED, 0);
    return 1;
}

do_close(string what)
{
    if (what != "shrine" && what != "beautiful shrine") return 0;

    if (TO -> query_prop(CONT_I_CLOSED)) {
	write("The shrine is already closed.\n");
	return 1;
    }
    write("You close the shrine.\n");
    add_prop(CONT_I_CLOSED, 1);
    return 1;
}

do_unlock(string what)
{
    int i, ok;
    object ring, *keys;
    string s1;

    NF("Unlock what?\n");
    if (!what) return 0;

    NF("With what?\n");
    if (what == "shrine" || what == "beautiful shrine") return 0;

    NF("Unlock what?\n");
    if (sscanf(what, "shrine with %s", s1) != 1) return 0;

    keys = FIND_STR_IN_OBJECT(s1, TP);

    NF("You don't have that!\n");
    if (sizeof(keys) <= 0) return 0;

    NF("You must specify one item!\n");
    if (sizeof(keys) > 1) return 0;

    ring = check_sh_pr("gold ring", "q_solver", TP);
    if (ring != keys[0]) {
	write(capitalize(keys[0]->short()) +
	      " doesn't fit in the lock.\n");
	return 1;
    }
    if (!(TO -> query_prop(CONT_I_LOCK))) {
	write("The shrine is already unlocked.\n");
	return 1;
    }

    write("You unlock the shrine with your "+ring->short()+".\n");
    add_prop(CONT_I_LOCK, 0);
    return 1;
}

do_lock(string what)
{
    int i, ok;
    object ring, *keys;
    string s1;

    NF("Lock what?\n");
    if (!what) return 0;

    NF("With what?\n");
    if (what == "shrine" || what == "beautiful shrine") return 0;

    NF("Lock what?\n");
    if (sscanf(what, "shrine with %s", s1) != 1) return 0;

    keys = FIND_STR_IN_OBJECT(s1, TP);
    NF("You don't have that!\n");
    if (sizeof(keys) <= 0) return 0;

    NF("You must specify one item!\n");
    if (sizeof(keys) > 1) return 0;

    ring = check_sh_pr("gold ring", "q_solver", TP);
    if (ring != keys[0]) {
	write(capitalize(keys[0]->short()) +
	      " doesn't fit in the lock.\n");
	return 1;
    }

    if (TO -> query_prop(CONT_I_LOCK)) {
	write("The shrine is already locked.\n");
	return 1;
    }
    if (!(TO -> query_prop(CONT_I_CLOSED))) {
	write("The shrine is opened, you have to close it first.\n");
	return 1;
    }
    write("You lock the shrine with your "+ring->short()+".\n");
    TO->add_prop(CONT_I_LOCK, 1);
    return 1;
}

my_long()
{
    string str;

    str = "It's a beautiful shrine, made of gneiss";
    if (TO->query_prop(CONT_I_CLOSED)) str = str + ". It is closed";
    if (TO->query_prop(CONT_I_LOCK)) str = str + " and locked";
    str = str + ".";
    return BSN(str);
}

object
check_sh_pr(string sh_desc, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop(prop) == ob->query_name()) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}
