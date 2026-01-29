inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define STONE_CAVE "/d/Calia/walkers/stone/cave/entrance"

void
create_container()
{
    set_no_show_composite(1);
    set_name("indentation");
    set_short("indentation");
    set_long("The small indentation is circular in shape and appears "+
        "as if something might fit inside of it.\n");

    remove_prop(CONT_I_VOLUME);
    remove_prop(CONT_I_WEIGHT);
    add_prop(CONT_I_MAX_VOLUME, 300);
    add_prop(CONT_I_MAX_WEIGHT, 300);
}

public int
prevent_enter(object ob)
{
    if (!ob->id("_stone_necklace_"))
    {
        write("The " + ob->short() + " doesn't fit in the indentation.\n");
        return 1;
    }

    return 0; 
}

void
finish_up(object ob, object from)
{
    write("The ground begins to shake beneath your feet.\n");
    write("You quickly remove your necklace from the indentation.\n");
    ob->move(from,1);
    write("You feel your skin tingle, lose conciousness for a brief moment, then "+
        "find yourself elsewhere.\n");
    say(QCTNAME(TP)+"'s body begins to pulse then suddenly explodes into millions "+
        "of tiny particles of dust.\n");
    TP->move_living("M",STONE_CAVE);
    say("A slight breeze blows from the western wall which picks up a few dust "+
        "particles from the ground.  The dust swirls around, quickly forming into a "+
        "large mass.  From within the mass steps "+QTNAME(TP)+".  The wind subsides "+
        "and the mass returns to the ground where it came from.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_alarm(1.5, 0.0, &finish_up(ob, from));
}
