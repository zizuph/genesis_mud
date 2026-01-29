/* A jug; can be filled with water. ~solace/puzzle/objects/jug */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

int how_full;		/* How full of water. Min (0) max (1000) millilitres. */

#define STATE	({ "almost empty",                               \
                   "filled about about a quarter-full of water", \
                   "about half-filled with water",               \
                   "quite full of water",                        \
                   "full of water"                               })

#define TO_FILL	({ "with a drop",                                \
                   "with a trickle",                             \
                   "about half-full",                            \
                   "quite full",                                 \
                   "full"                                        })

int query_filled()
{
    return how_full;
}

void fill_me(int amount)
{
    if(how_full + amount <= 1000)
        how_full += amount;
    else
        how_full = 1000;
}

void create_object()
{
    set_name("jug");
    set_adj("strong");
    add_adj("brass");
    set_long("@@long_desc");
}

void init()
{
    ::init();

    add_action("do_pour", "pour");
    add_action("do_fill", "fill");
    add_action("do_empty", "empty");
}

string long_desc()
{
    int calc;
    string str = "A medium-sized jug made from a very nice coloured metal.";

    if(how_full > 0)
    {
        calc = ((how_full / 200) - 1) < 0 ? 0 : ((how_full / 200) - 1);
        str += " It seems to be "+STATE[calc]+".";
    }

    return str + " You reckon you might be able to fill it, empty it or "+
        "pour its contents into something.\n";
}

int do_pour(string str)
{
    int tube_cont;
    string what, where;
    object puddle, tube, *cont;

    if(!str || str == "")
        return 0;

    if(!parse_command(str, TP, "%s 'in' / 'into' %s", what, where))
    {
        notify_fail("Pour [what] into [what]?\n");
        return 0;
    }

    if(E(TO) != TP)
    {
        notify_fail("You have to be holding the jug first!\n");
        return 0;
    }

    if(what != "water")
    {
        notify_fail("Pour what into what? IE: 'pour water into bath'.\n");
        return 0;
    }

    tube = present("tube", E(TP));
    cont = FIND_STR_IN_OBJECT(where, E(TP));

    if(!sizeof(cont))
    {
        notify_fail("There isn't "+LANG_ADDART(where)+" here!\n");
        return 0;
    }

    if(tube != cont[0])
    {
        notify_fail("You cannot pour the water into there.\n");
        return 0;
    }

    if(!how_full)
    {
        notify_fail("The jug is empty.\n");
        return 0;
    }

    tube_cont = tube->query_filled();

    if(tube_cont + how_full >= 3000)
    {
        if(tube_cont == 3000)
        {
            TP->catch_msg("You empty the contents of the jug into the tube, "+
                "but it is already full, so the water just slops over the "+
                "rim.\n");

            tell_room(E(TP), QCTNAME(TP)+" empties the contents of "+
                POSSESSIVE(TP)+" jug into the tube, but it is already full, "+
                "so the water just slops over the side.\n", TP);
        }
        else if(tube_cont + how_full == 3000)
        {
            tube->fill_me(3000 - tube_cont);

            TP->catch_msg("You empty the contents of the jug into the tube, "+
                "filling it right to the rim.\n");

            tell_room(E(TP), QCTNAME(TP)+" empties the contents of "+
                POSSESSIVE(TP)+" jug into the tube, filling it right to "+
                "the rim.\n", TP);
        }
        else
        {
            tube->fill_me(3000 - tube_cont);

            TP->catch_msg("You empty the contents of the jug into the tube "+
                "and the water level rises to the top. Excess water spills "+
                "onto the floor.\n");

            tell_room(E(TP), QCTNAME(TP)+" empties the contents of "+
                POSSESSIVE(TP)+" jug into the tube and the water level rises "+
                "to the top. Excess water spills onto the floor.\n", TP);
        }

        puddle = present("puddle", E(TP));

        if(!objectp(puddle))
        {
            seteuid(getuid(TO));
            puddle = clone_object(OBJECTS + "puddle");

            puddle->add_water(how_full);
            puddle->move(E(TP));
        }
    }
    else
    {
        tube->fill_me(how_full);

        TP->catch_msg("You empty the contents of the jug into the tube, "+
            "making the water-level rise.\n");

        tell_room(E(TP), QCTNAME(TP)+" empties the contents of "+POSSESSIVE(TP)+
            "jug into the tube, making the water-level rise.\n", TP);
    }

    how_full = 0;
    return 1;
}

int do_fill(string str)
{
    object puddle;
    string what, where;
    int amount, room_left;

    if(!str || str == "")
        return 0;

    if(!parse_command(str, TP, "%s 'at' / 'from' %s", what, where))
    {
        notify_fail("Fill what, where?\n");
        return 0;
    }

    if(E(TO) != TP)
    {
        notify_fail("You have to be holding the jug first!\n");
        return 0;
    }

    if(member_array(TO, FIND_STR_IN_OBJECT(what, TP)) == -1)
    {
        notify_fail("Fill what, where? IE: 'fill jug at swimming-pool'.\n");
        return 0;
    }

    if(where != "puddle")
    {
        write("You don't seem to be able to fill the jug there.\n");
        return 1;
    }

    puddle = present("puddle", E(TP));

    if(!objectp(puddle))
    {
        write("You can't fill the jug at "+LANG_ADDART(where)+" if there "+
            "isn't one here!\n");
        return 1;
    }

    if(how_full == 1000) // 1 litre.
    {
        write("You try to fill the jug some more but the water just spills "+
            "over the brim.\n");

        say(QCTNAME(TP)+" tries to fill "+POSSESSIVE(TP)+" jug at the "+where+
            ", but it is already full.\n");
            return 1;
    }

    amount = puddle->query_filled(); // Check how much water is left in
                                     // the puddle. (It drains away).
    if(amount == 0)
    {
        write("You try to fill your jug, but there is no water left.\n");

        say(QCTNAME(TP)+" tries to fill "+POSSESSIVE(TP)+" jug with water, "+
            "but finds that there is none left.\n");
        return 1;
    }

    room_left = 1000 - how_full;

    if(amount > room_left)
    {
        how_full = 1000;

        write("You fill the jug until it is overflowing with water.\n");
    }
    else
    {
        fill_me(amount);

        write("You fill the jug "+TO_FILL[(((amount / 200) - 1) < 0 ? 0 :
            ((amount / 200) - 1))]+" of water at the "+where+".\n");
    }

    puddle->remove_object();

    say(QCTNAME(TP)+" fills "+POSSESSIVE(TP)+" jug at the "+where+".\n");
        return 1;
}
 
int do_empty(string str)
{
    object puddle;

    if(!strlen(str))
    {
        notify_fail("Empty what?\n");
        return 0;
    }

    if(member_array(TO, FIND_STR_IN_OBJECT(str, TP)) == -1)
    {
        notify_fail("Empty what?\n");
        return 0;
    }

    if(!how_full)
    {
        write("You tip the jug up but it is empty - nothing comes out.\n");

        say(QCTNAME(TP)+" tips "+POSSESSIVE(TP)+" jug up as if to empty "+
            "something out of it, but nothing happens.\n");
        return 1;
    }

    puddle = present("puddle", E(TP));

    if(!objectp(puddle))
    {
        seteuid(getuid(TO));
        puddle = clone_object(OBJECTS + "puddle");

        puddle->add_water(how_full);
        puddle->move(E(TP));
    }

    how_full = 0;

    write("You tip the jug up and empty the water onto the floor.\n");

    say(QCTNAME(TP)+" tips "+POSSESSIVE(TP)+" jug upside down and all the "+
        "water in it falls onto the floor.\n");
    return 1;
}
