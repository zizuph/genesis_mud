/* A coffin */
inherit "/std/container";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#define NF(xx)        notify_fail(xx + "\n")
#define TO            this_object()
#define TP            this_player()
#define MANSION       "/d/Terel/common/town/mansion/"
#define GHOST_OBJ     "/d/Terel/mortricia/camp/house/ghost_obj"

object in_coffin;
object ring;

public object *all_objs(string filter);
public object find_q_ring(int q_no, object ob);
public object check_key(string prop, object ob);

public void
create_container()
{
    set_name("coffin");
    set_short("old coffin");
    set_adj("old");
    set_long("@@my_long");
    add_prop(CONT_I_WEIGHT, 45000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_LOCK, 0);
    add_prop(OBJ_I_NO_GET, 1);
    seteuid(getuid(TO));
    in_coffin = clone_object(MANSION + "rooms/in_coffin");
    set_room(in_coffin);
    in_coffin->set_coffin(TO);

    add_item(({"lock"}), "The rusty metal lock seems quite old.\n");
}

public int
do_open(mixed what)
{
    object ob;

    NF("Open what?");
    if (!what) return 0;

    if (stringp(what)) {
        if (!parse_command(what, environment(), "%o", ob)) return 0;
    } else if (objectp(what)) {
        ob = (object)what;
    }

    if (ob != TO) return 0;

    if (query_prop(CONT_I_LOCK)) {
        write("The "+TO->short()+" is locked.\n");
        return 1;
    }
    if (!query_prop(CONT_I_CLOSED)) {
        write("The "+TO->short()+" is already opened.\n");
        return 1;
    }
    write("You open the "+short()+".\n");
    say(QCTNAME(TP) + " opens the " + short() + ".\n");
    if (objectp(what))
        tell_room(environment(TO), "The "+short()+" suddenly opens up.\n");
    else if (stringp(what))
        tell_room(query_room(), "Someone opens the "+short()+".\n");
    add_prop(CONT_I_CLOSED, 0);
    in_coffin->change_prop(ROOM_I_LIGHT, 1);
    return 1;
}

public int
do_close(mixed what)
{
    object ob;

    NF("Close what?");
    if (!what) return 0;

    if (stringp(what)) {
        if (!parse_command(what, environment(), "%o", ob)) return 0;
    } else if (objectp(what)) {
        ob = (object)what;
    }

    if (ob != TO) return 0;

    if (query_prop(CONT_I_CLOSED)) {
        write("The "+TO->short()+" is already closed.\n");
        return 1;
    }
    write("You close the "+short()+".\n");
    say(QCTNAME(TP) + " closes the " + short() + ".\n");
    if (objectp(what))
        tell_room(environment(TO), "The "+short()+" suddenly gets closed.\n");
    else if (stringp(what))
        tell_room(query_room(), "Someone closes the "+short()+".\n");
    TO->add_prop(CONT_I_CLOSED, 1);
    in_coffin->change_prop(ROOM_I_LIGHT, 0);
    return 1;
}

public int
do_unlock(string what)
{
    object key, ob1, ob2;

    if (!CAN_SEE_IN_ROOM(TP)) return 0;
    NF("Unlock what?");
    if (!what) return 0;

    NF("Unlock what with what?");
    if(!parse_command(what, environment(),
        "%o 'with' %o", ob1, ob2)) return 0;

    NF("Unlock what?");
    if (ob1 != TO) return 0;

    NF("Unlock "+short()+" with what?");
    if (ob2->query_name() != "key") return 0;

    if (!query_prop(CONT_I_LOCK)) {
        write("The "+short()+" is already unlocked.\n");
        return 1;
    }

    key = check_key("key_owner_7", TP);
    if (key != ob2) {
        write("You don't have the proper key to do that.\n");
        return 1;
    }

    write("You unlock the "+short()+" with your "+key->short()+".\n");
    say(QCTNAME(TP) + " unlocks the "+short()+".\n");
    add_prop(CONT_I_LOCK, 0);
    return 1;
}

public void
make_ghost(object who)
{
    if (!who || environment(who) != in_coffin ||
        query_prop(CONT_I_LOCK) == 0 ||
        who->query_ghost()) return;

    ring->change_prop("q_step", 3);
    seteuid(getuid());
    clone_object(GHOST_OBJ)->move(who);
}

public int
do_lock(string what)
{
    int i;
    object *objs;
    object key, ob1, ob2;

    if (!CAN_SEE_IN_ROOM(TP)) return 0;
    NF("Lock what?");
    if (!what) return 0;

    NF("Lock what with what?");
    if(!parse_command(what, environment(),
        "%o 'with' %o", ob1, ob2)) return 0;

    NF("Lock what?");
    if (ob1 != TO) return 0;

    NF("Lock "+short()+" with what?");
    if (ob2->query_name() != "key") return 0;

    if (query_prop(CONT_I_LOCK)) {
        write("The "+short()+" is already locked.\n");
        return 1;
    }
    if (!query_prop(CONT_I_CLOSED)) {
        write("The "+short()+" is opened, you have to close it first.\n");
        return 1;
    }

    key = check_key("key_owner_7", TP);
    if (key != ob2) {
        write("You don't have the proper key to do that.\n");
        return 1;
    }
    write("You lock the "+short()+" with your "+key->short()+".\n");
    say(QCTNAME(TP) + " locks the "+short()+".\n");
    add_prop(CONT_I_LOCK, 1);
    objs = all_objs("%l");
    for(i=0; i<sizeof(objs); i++) {
        ring = find_q_ring(7, objs[i]);
        if (ring && ring->query_prop("q_step") >= 2 &&
            key->query_prop("key_owner_7") == objs[i]->query_name()) {
            set_alarm(20.0, -1.0, &make_ghost(objs[i]));
            break;
        }
    }
    return 1;
}

public string
my_long()
{
    string str;

    str = "It's "+LANG_ADDART(short())+". It looks sturdy";
    if (TO->query_prop(CONT_I_CLOSED)) str = str + ". It is closed";
    if (TO->query_prop(CONT_I_LOCK)) str = str + " and locked";
    str += ".\n";
    return str;
}

public object
check_key(string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_prop(prop)) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

public int
do_enter(string what)
{
    object ob;

    if (!CAN_SEE_IN_ROOM(TP)) return 0;
    NF("Enter what?");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    if (query_prop(CONT_I_LOCK)) {
        write("The "+short()+" is locked.\n");
        return 1;
    }
    if (query_prop(CONT_I_CLOSED)) {
        write("The "+short()+" is closed.\n");
        return 1;
    }
    if (sizeof(all_objs("%l")) >= 1) {
        write("The "+short()+" is already occupied.\n");
        return 1;
    }
    if (TP->move_living("M", query_room())) {
        write("You are too big for it!\n");
    } else {
        say(QCTNAME(TP) + " lies down in the " + short() + ".\n");
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_open, "open");
    add_action(do_close, "close");
    add_action(do_lock, "lock");
    add_action(do_unlock, "unlock");
    add_action(do_enter, "enter");
}

public object *
all_objs(string filter)
{
    int i;
    object *tmp, *objs;

    objs = ({ });
    if (in_coffin) {
        tmp = all_inventory(in_coffin);
        for(i=0; i<sizeof(tmp); i++) {
            if (filter == "%l") {
                if (living(tmp[i])) objs += ({ tmp[i] });
            } else {
                objs += ({ tmp[i] });
            }
        }
    }
    return objs;
}

public object
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
