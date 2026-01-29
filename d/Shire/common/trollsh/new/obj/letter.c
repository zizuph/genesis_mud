inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

int gLetterFound = 0;

int do_read(string s);

void
create_object()
{
    set_name(({"letter",SHIRE_DWARVEN_FRIEND_LETTER}));
    set_adj(({"bloodied","creased"}));
    set_short("creased bloodied letter");
    set_long("This bloodied creased letter has some writing on it. "+
        "Perhaps you can read it.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();

    add_action(do_read,"read");
}

int
do_read(string s)
{
    if (!stringp(s))
        return 0;

    if (s != "letter")
    {
        NF("Read what?\n");
        return 0;
    }

    write("You read the letter...\n"+
        "Letter contents here.\n");
    return 1;
}

void
enter_env(object new, object old)
{
    ::enter_env(new, old);

    if (gLetterFound)
        return;

    if (!living(new))
        return;

    new->add_prop(PLAYER_I_GOT_DWARVEN_LETTER, 1);
    gLetterFound = 1;
}
