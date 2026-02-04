/* A box */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#define HAUN_DIR      MORTRICIADIR + "camp/house/"

#define BS(xx)        break_string(xx, 70)
#define BSN(xx)       break_string(xx + "\n", 70)
#define NF(xx)        notify_fail(xx + "\n")
#define TO            this_object()
#define TP            this_player()

init()
{
    ::init();
    add_action("do_open", "open");
    add_action("do_close", "close");
    add_action("do_shake", "shake");
}

create_container()
{
    set_name("box");
    set_adj("strange");
    set_short(TO->query_adj()+" box");
    set_long("@@my_long");
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(OBJ_M_NO_GET,
       "It cannot be taken (maybe shaken). It's mounted to the floor.\n");

    add_item(({"lock"}), BSN(
	"The lock seems quite old and made of iron."
    ));
}

do_open(string what)
{
    object ob;

    NF("Open what?");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    if (!(TO -> query_prop(CONT_I_CLOSED))) {
	write("The "+TO->short()+" is already opened.\n");
	return 1;
    }
    write("You open the "+TO->short()+".\n");
    say(QCTNAME(TP) + " opens the " + TO->short() + ".\n");
    TO->add_prop(CONT_I_CLOSED, 0);
    return 1;
}

do_close(string what)
{
    object ob;

    NF("Close what?");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    if (TO -> query_prop(CONT_I_CLOSED)) {
	write("The "+TO->short()+" is already closed.\n");
	return 1;
    }
    write("You close the "+TO->short()+".\n");
    say(QCTNAME(TP) + " closes the " + TO->short() + ".\n");
    TO->add_prop(CONT_I_CLOSED, 1);
    return 1;
}

do_shake(string what)
{
    object ob, stone, powder;
    string adj;

    NF("Shake what?");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    write("You shake the "+TO->short()+".\n");
    say(QCTNAME(TP) + " shakes the " + TO->short() + ".\n");
    stone = present("stone", TO);
    if (stone) {
	tell_room(environment(), "You hear noise from the box.\n");
	adj = stone->query_adj();
        if (TO->query_prop(CONT_I_CLOSED) && adj == TO->query_adj()) {
            TO->add_prop(CONT_I_CLOSED, 0);
	    stone -> remove_object();
	    powder = clone_object(HAUN_DIR + "powder");
	    powder -> set_adj(adj);
	    powder -> set_short("handful of "+adj+" powder");
	    powder -> set_pshort("handfuls of "+adj+" powder");
	    powder -> move(TO);
            TO->add_prop(CONT_I_CLOSED, 1);
        }
    }
    return 1;
}

my_long()
{
    string str;

    str = "It's a "+TO->short()+". It looks sturdy";
    if (TO->query_prop(CONT_I_CLOSED)) str = str + ". It is closed";
    str = str + ".";
    return BSN(str);
}
