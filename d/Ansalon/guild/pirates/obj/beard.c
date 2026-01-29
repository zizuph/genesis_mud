#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
inherit "/lib/keep";

inherit "/std/object";

#define BEARD_SUBLOC "fake_beard_subloc"

int worn = 0;

void
create_object()
{
    mixed *color;
    mixed *shape;
    int n, m, j;
    
    set_name("beard");
    j = random(2);

    color = ({"black", "white", "brown", "yellow", "red",
              "gray", "blond"});
    n = random(sizeof(color));
    if (strlen(color[n]))
        set_adj(color[n]);
    if (j == 1)
    {
        shape = ({"long", "short", "forked", "twisted", "wild"});
        m = random(sizeof(shape));
        if (strlen(shape[m]))
            set_adj(shape[m]);
        set_short(shape[m]+ " "+color[n]+" beard");
    }
    else
    {
        set_short(color[n]+" beard");
    }
 
    set_long("This is a fake "+short()+", made for pirates so "+
             "they can earn the respect that they deserve. It "+
             "covers most of the neck and offers a limited form of "+
             "protection.\n"+
             "There's a small note inside the beard.\n");

    add_item(({"note", "words"}),"The note reads:\n"+
                                "'brub'.\n");

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
wear_beard(string str)
{
    NF("Wear what?\n");
    if (!str)
        return 0;

    if (str != "beard")
        return 0;

    NF("You are already wearing your beard.\n");
    if (worn == 1)
        return 0;

    if (TP->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
        worn = 1;

        write("You turn your head as you quickly strap on the fake beard, making "+
              "sure that no one sees you.\n");

        TP->add_subloc(BEARD_SUBLOC, TO);
        set_no_show_composite(1);
        return 1;
    }
    else
    {
        write("You fail to wear the beard, as it keeps falling off.\n");
        return 1; // we know that player wanted to wear the beard but he is
                  // not allowed, but we take care of messages to avoid double
                  // messages from mud itself
    }
}

int
remove_beard(string str)
{

    NF("Remove what?\n");
    if (!str)
        return 0;

    if (str != "beard")
        return 0;

    NF("You are not wearing your beard.\n");
    if (worn == 0)
        return 0;

    worn = 0;

    write("You remove your fake beard.\n");

    TP->remove_subloc(BEARD_SUBLOC);
    set_no_show_composite(0);
    return 1;
}

string
show_subloc(string subloc, object wearer, object for_obj)
{

    string str;

    if (wearer->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are wearing a fake beard.\n";

    if (for_obj == wearer)
        str = "You have ";
    else
        str = capitalize(wearer->query_pronoun()) + " has ";

    return str + "a magnificent "+short()+".\n";
}

int
emote_brub()
{
    write("You rub your "+short()+" thoughtfully.\n");
    TP->tell_watcher(QCTNAME(TP)+ " rubs "+HIS(TP)+
                          " "+short()+" thoughtfully.\n");
    return 1;
}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    worn = 0;
    TP->remove_subloc(BEARD_SUBLOC);
    set_no_show_composite(0);
}

void
init()
{
    add_action("wear_beard", "wear");
    add_action("remove_beard", "remove");
    add_action("emote_brub", "brub");
    ::init();
}

