inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/din/din_defs.h"

void
create_object()
{
    set_name(({"grubb"}));
    set_short("slimy black grubb");
    add_adj(({"slimy", "black"}));
    set_long(BSN("This vile creature looks like a cross between a leech"
      + " and a ringworm. It is pitch black, and glistens with slime."
      + " The way it writhes around seems to suggest that it might"
      + " try to burrow if put on certain materials."));
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE, 0);
}

int
place_grubb(string str)
{
    mixed placed, placed_on;

    if(!str)
    {
        return 0;
    }

    if (!parse_command(str, environment(TP),
        "%i 'on' / 'onto' [the] %i", placed, placed_on))
    {
        return 0;
    }
    placed = NORMAL_ACCESS(placed, 0, 0)[0];
    placed_on = NORMAL_ACCESS(placed_on, 0, 0)[0];

    if (!placed->id("grubb"))
    {
        write("Do you want to put the grubb on something?\n");
        return 0;
    }

    if (living(placed_on))
    {
        if (TP->query_real_name() == placed_on->query_real_name())
        {
            write(BSN("You place the slimy black grubb on your arm, and"
                + " notice that it squirms about as if attempting"
                + " To burrow into your skin. You quickly remove the"
                + " disturbing creature."));
            return 1;
        }

        TP->catch_msg("You place the slimy black grubb on "
          +QTNAME(placed_on)+ ", who jumps in sudden"
          + " surprise. Grabbing the grubb, "
          +QTNAME(placed_on)+ " throws it on the ground in"
          + " disgust.\n");
        tell_room(environment(TP), QCTNAME(TP)+ " places a"
          + " slimy black grubb on " +QTNAME(placed_on)
          + " who jumps in sudden surprise. Grabbing the"
          + " grubb, " +QTNAME(placed_on)+ " throws it on"
          + " the ground in disgust.\n", ({placed_on, TP}));
        placed_on->catch_msg(QCTNAME(TP)+ " places"
          + " a slimy black grubb on your face! You grab"
          + " it and throw it on the ground in disgust.\n");

        placed->move(environment(TP));
        return 1;
    }

    write("You place the " +placed->short()+ " on the "
        +placed_on->short()+ ".\n");
    say(QCTNAME(TP)+ " places " +LANG_ADDART(placed->short())+
        " on the " +placed_on->short()+ ".\n");

    if (!placed_on->id("firewood") || placed_on->query_adj("ash-grey"))
    {
        tell_room(environment(TP), "The slimy black grubb writhes for a moment"
          + " on the surface of the " +placed_on->short()
          + " but seems unwilling to feed there. It falls"
          + " harmlessly to the ground.\n");

        placed->move(environment(TP));
        return 1;
    }

    tell_room(environment(TP), "The slimy black grubb writhes for a moment"
      + " on the surface of the " +placed_on->short()+ ", and"
      + " then quickly burrows inside. The " +placed_on->short()
      + " looks suddenly different.\n");

    placed_on->destroy_firewood();

    if (placed_on->query_prop(DIN_I_FIREWOOD))
    {
        TP->add_prop(DIN_I_DESTROYED_FIREWOOD, 1);
    }

    set_alarm(1.0, 0.0, "remove_object");
    return 1;
}

void
init()
{
    ::init();
    add_action(place_grubb, "put");
}
