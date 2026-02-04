/*
    top.c

    A child's toy top. Carried by the elven lad Ailin
        (CALATHIN_DIR + "npc/ailin.c")

    Created: 15 Sep 2003, by Bleys


*/

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <macros.h>
#include <stdproperties.h>


// Globals
int wound = 0;

// Prototypes
public int do_spin(string args);
public int do_wind(string args);
public string long_extra();


public void
init()
{

    ::init();
    add_action(do_wind, "wind");
    add_action(do_spin, "spin");

}


public void
create_object()
{

    set_name(({"top"}));
    add_name("toy");
    add_adj(({"child", "child's", "colorful", "toy"}));
    set_short("colorful toy top");
    set_long("This toy top is made of dense wood and elegantly " +
        "painted in light blue with thin, horizontal yellow stripes. " +
        "A bright yellow cord is attached to the place where the " +
        "stem meets the body of the top with a wooden pin. Some " +
        "craftsman put quite a bit of time into the making of this " +
        "fine toy.@@long_extra@@\n");

    add_prop(OBJ_I_VOLUME, 1250);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,  400);

    wound = 1;

}


public string
long_extra()
{

    string extra = "";

    if ( wound )
    {
        extra += " The yellow cord is wound tightly around the stem " +
            "of the top.";
    }
    else
    {
        extra += " The yellow cord dangles loosely from the stem of " +
            "the top.";
    }

    return extra;

}


public int
do_spin(string args)
{

    NF("Do you want to spin the " + short() + "?\n");

    if (!args)
    {
        return 0;
    }

    if ( parse_command(args, TO, "[the] 'top'") )
    {

        if ( wound )
        {
            write("You grab the yellow cord on the top, squat down, " +
                "and yank it hard. The cord spins the top through the " +
                "air. It hits the ground a short distance away, " +
                "bounces twice, and then begins to sway back and " +
                "forth as it spins merrily about. Finally, its " +
                "impetus spent, it topples and rolls to a halt.\n");
            say(QCTNAME(TP) + " squats down and yanks the cord on " +
                HIS_HER + " " + short() + ". The cord spins the top " +
                "through the air. It hits the ground a short distance " +
                "away, bounces twice, and then begins to sway back " +
                "and forth as it spins merrily about. Finally, its " +
                "impetus spent, it topples and rolls to a halt.\n");

            wound = 0;

            return 1;

        }
        else
        {
            NF("You can't spin the top until it is wound up.\n");
            return 0;
        }


    }
    else
    {
        return 0;
    }

    return 0;

}


public int
do_wind(string args)
{

    NF("Do you want to wind the " + TO->short() + "?\n");

    if (!args)
    {
        return 0;
    }

    if ( parse_command(args, TO, "[the] 'top'") )
    {

        if ( wound )
        {
            NF("The " + short() + " is already wound tightly.\n");
            return 0;
        }
        else
        {

            write("You carefully loop the yellow cord around the " +
                "stem of the top, taking care to make sure that " +
                "each loop is tight.\n");

            say(QCTNAME(TP) + " carefully winds a bright yellow " +
                "cord around the stem of " + HIS_HER + " " +
                short() + ".\n");

            wound = 1;

            return 1;

        }

    }
    else
    {
        return 0;
    }

    return 0;

}


