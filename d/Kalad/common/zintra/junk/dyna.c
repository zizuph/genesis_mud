inherit "std/object";
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

#define SUBLOC "_dynamite_subloc"

int lit;
object make_crater();

void
create_object()
{
    set_name(({"stick", "dynamite"}));
    set_pname("sticks of dynamite");
    set_short("@@d_short");
    set_pshort("@@pd_short");
    set_long("@@d_long");
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 200);
    lit = 0;
}

string
d_short()
{
    if (lit) return "lit stick of dynamite";
    return "stick of dynamite";
}

string
pd_short()
{
    if (lit) return "lit sticks of dynamite";
    return "sticks of dynamite";
}

string
d_long()
{
    if (lit) return BS(
        "This is a small stick of dynamite.  It has a short fuse that is " +
        "currently lit.  You have no idea how much time you have left, " +
        "but you'd better get rid of it, quick!\n");
    return BS(
        "This is a small stick of dynamite.  It has a short fuse that you " +
        "estimate lasts around 5 seconds.  The fuse is just waiting to " +
        "be lit.\n");
}

void
init()
{
    add_action("arm", "light");
}

int
arm(string str)
{
    NF("Light what?\n");
    if (!str) return 0;
    if (str != "stick" && str != "fuse" && str != "dynamite") return 0;
    if (lit)
    {
        write ("Its already lit.  Better get rid of it.\n");
        return 1;
    }
    lit = 1;
    write (BS("You light the end of the fuse, and it starts to spark and burn.  " +
        "You estimate that you have about 5 seconds to get rid of it.\n"));
    say (BS(QCTNAME(TP) + " takes what seems to be a small stick, and " +
        "lights one end.\n"));
    call_out("explosion", 5 + random(11));
    return 1;
}

void
explosion()
{
    int i;
    object *ob, crater;
    tell_room(ENV, BS("There is a tremendous amount of noise and " +
        "light as the dynamite explodes.  Spectacular!  "));
    if (living(ENV))
    {
        ENV->heal_hp(-20);
        tell_room(ENV, BS("You were foolish enough to hold a lit " +
            "stick of dynamite while it exploded.  I sure hope you " +
            "survived the blast.\n"));
        tell_room(environment(ENV), "You hear a muffled bang, and " +
            "smoke starts pouring out of " + QTNAME(ENV) + ".\n", ENV);
        if (ENV->query_hp() < 1) ENV->do_die(TO);
        ENV->add_subloc(SUBLOC, TO);
    }
    tell_room(ENV, BS("You were foolish enough to remain in a room with a " +
        "stick of dynamite while it exploded.  I sure hope you " +
        "survived the blast.\n"));
    ob = all_inventory(ENV);
    for(i = 0; i < sizeof(ob); i++)
    {
        if (living(ob[i]))
        {
            ob[i]->add_subloc(SUBLOC, TO);
            ob[i]->heal_hp(-20);
            if (ob[i]->query_hp() < 1) ob[i]->do_die(TO);
        }
    }
    crater = make_crater();
    crater->move(ENV);
    remove_object();
}

object
make_crater()
{
    object crater;

    seteuid(getuid());
    crater = clone_object("/std/object");
    crater->set_name("crater");
    crater->set_adj("small");
    crater->set_short("small crater");
    crater->set_long(BS("There is a small crater here, in the ground.  It " +
        "looks as if someone has recently set off a small explosion.\n"));
    crater->add_prop(OBJ_M_NO_GET, "You can't take a crater.  Its a hole in " +
        "the ground!\n");

    return crater;
}

string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string str;
    on_obj = ENV;
    if (subloc != SUBLOC) return "";
    if (on_obj == for_obj) str = "You are ";
    else str = on_obj->query_pronoun() + " is ";
        str += "looking rather charred and sooty, " +
            "as if caught in a recent explosion.\n";
    return str;
}
