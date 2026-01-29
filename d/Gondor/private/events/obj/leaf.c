inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

string *colour = ({"red", "orange", "yellow", "brown", "green"});

void
create_object()
{
    string col = colour[random(5)];
    set_name(({"leaf", "_gondor_scavenger_leaf_"}));
    set_adj(col);
    add_adj("gondorian");
    set_short(col + " gondorian oak leaf");
    set_pname("leaves");
    set_pshort(col + " gondorian oak leaves");
    add_adj("oak");
    set_long("One of the last leaves of Autumn, this leaf may just bring you " +
    "some luck! You could probably 'declare victory' when you have all " +
    "five colours and you are among the first three to do so, but beware! " +
    "Declaring false victory might anger " +
    "the gods of Autumn.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 15);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!living(dest))
        return;

    setuid();
    seteuid(getuid());
    if (!present("leaf_master", dest))
    {
        clone_object("/d/Gondor/private/events/obj/invis_leaf")->move(dest, 1);
        return;
    }
}
