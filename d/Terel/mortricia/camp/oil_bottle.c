/* A bottle of oil. Mortricia 921002.  */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define CAMP_DIR MORTRICIADIR + "camp/"
#define TP this_player()
#define NF(xx) notify_fail(xx)
#define TO this_object()
#define OIL_TIME 300

int empty;
object oil;

init()
{
    ::init();
    add_action("do_pour", "pour");
    add_action("do_pour", "apply");
    add_action("do_pour", "use");
}

create_object()
{
    set_name("bottle");
    add_name("bottle of oil");
    set_short("@@my_short");
    set_pshort("@@my_pshort");
    set_long("@@my_long");
    set_adj("small");
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, 100);

    empty = 0;
}

do_pour(string what)
{
    if ((what=="oil" || what=="oil over body" ||
	 what=="oil on body" || what=="oil on myself" ||
	 what=="oil over myself") && present(TO, TP)) {
        if (empty) {
            write("The bottle is empty!\n");
            return 1;
        }
        empty = 1;
        write("You pour the oil all over your body.\n");
        say(QCTNAME(TP) + " pours oil all over " +
            TP->query_possessive() + " body.\n");
        seteuid(getuid());
        oil = clone_object(CAMP_DIR + "oil");
        oil -> move(TP);
        oil -> add_prop(OBJ_M_NO_GIVE, 1);
        return 1;
    } else {
        NF(capitalize(query_verb()) + " what? Oil?\n");
    }
    return 0;
}

my_short()
{
    if (empty) {
        return "empty bottle";
    } else {
        return "bottle of oil";
    }
}

my_pshort()
{
    if (empty) {
        return "empty bottles";
    } else {
        return "bottles of oil";
    }
}

my_long()
{
    if (empty) {
        return "An empty bottle. From the label you realise that " +
               "it used to contain oil.\n";
    } else {
        return "A bottle of oil. It's not empty.\n";
    }
}

my_value()
{
    if (empty) {
        return 10;
    } else {
        return 50;
    }
}

my_weight()
{
    if (empty) {
        return 50;
    } else {
        return 100;
    }
}
