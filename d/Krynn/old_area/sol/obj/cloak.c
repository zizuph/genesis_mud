/* The cloak of the draconians 
 * to go in disguise and pass as humans.
 * Aridor, 05/96
 *
 * Original code taken from the Morgul Mages Guild Robe.
 */
#include "../local.h"
#include <macros.h>
#include <wa_types.h>

inherit "/std/armour";

object shadow;


void
create_armour()
{
    set_name(({"robe","cloak"}));
    set_adj(({"black", "hooded"}));
    set_short("black hooded robe");
    set_long("This is a black robe, with a hood.\n");
    add_item(({"hood" }), "When worn over the head the hood of the " +
	     "robe will hide the features of the person wearing the robe.\n");
    set_ac(3);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    seteuid(getuid(TO));
}

mixed
remove(object ob)
{
    if (ob != TO)
        return -1;

    if (TP->query_hooded())
        shadow->remove_shadow();

    return 0;
}

mixed
wear(object ob)
{
    object  tp = TP;

    if (ob != TO)
        return -1;
}

void
init()
{
    ::init();

    add_action("do_hood", "hood");
    add_action("do_hood", "wear");
    add_action("do_reveal", "reveal");
    add_action("do_reveal", "unhood");
    add_action("do_reveal", "remove");
}

void
leave_env(object from, object to)
{
    if (from->query_hooded())
    {
        shadow->remove_shadow();
    }

    ::leave_env(from, to);
}

int
do_hood(string str)
{
    string  vb = query_verb(),
            pron;

    if (vb == "hood")
        pron = "whom";
    else
        pron = "what";

    NF(C(vb) + " " + pron + "?\n");
    if (!strlen(str))
        return 0;

    if ((vb == "hood") && (str != "me" && L(str) != E(TO)->query_real_name()))
        return 0;

    if ((vb == "wear") && (str != "hood"))
        return 0;

    if (E(TO) != TP)
    {
        NF("You do not have the robe!\n");
        return 0;
    }

    if (query_worn() != TP)
    {
        NF("You do not wear your robe!\n");
        return 0;
    }

    if (TP->query_hooded())
    {
        NF("You are already wearing your hood!\n");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing your features.\n");
    say(QCTNAME(TP)+" pulls the hood of "+POSSESSIVE(TP)+" robe over "
      + POSSESSIVE(TP) + " head, concealing " + POSSESSIVE(TP) + " features.\n");

    shadow = clone_object(HROAD + "obj/hood_shadow");
    shadow->shadow_me(TP);
    return 1;
}

varargs int
do_reveal(string str, int silent = 0)
{
    string  vb = query_verb(),
            pron;

    switch (vb)
    {
        case "unhood":
        case "reveal":
            pron = "whom";
            break;
        case "mreveal":
            vb = "remove";
        case "remove":
            pron = "what";
            break;
    }

    NF(C(vb) + " " + pron + "?\n");
    if (!strlen(str))
        return 0;

    switch (vb)
    {
        case "unhood":
        case "reveal":
            if (str == "me")
                break;
            if (L(str) == E(TO)->query_real_name())
                break;
            NF("You can only remove your own hood!\n");
            return 0;
            break;
        case "remove":
            if (str != "hood")
                return 0;
            break;
    }

    if (E(TO) != TP)
    {
        NF("You do not have the robe!\n");
        return 0;
    }

    if (!TP->query_hooded())
    {
        NF("You are not wearing your hood!\n");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
        say(QCTNAME(TP)+" removes "+POSSESSIVE(TP)+" hood.\n");
    }

    shadow->remove_shadow();
    return 1;
}

