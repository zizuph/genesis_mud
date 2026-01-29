/*
 * The nexus apparatus. It opens a portal if the right combination is set to
 * the Necromancers of Vile Darkness guildhalls. This is the alternative
 * way to join the guild for those that arent directly invited.
 *
 * Fixed so it's able to load properly - Nerull 15/4/2015
 *
 */
/* 2018-02-26 Malus: Various minor fixes to code and clarity. */ 

#include <macros.h>
#include <stdproperties.h>
#include "/d/Faerun/guilds/nov/nov.h"

#define LOG(x,y) write_file("/d/Faerun/faerun_logs/" + x, \
    extract(ctime(time()), 4, 15) + " " + y )

inherit "/std/object.c";

int xaxis;
int yaxis;
int zaxis;

int circle1;
int circle2;
int circle3;

int glowbutton = 0;
int broken = 0;

void
create_object()
{

    set_short("ancient apparatus");
    set_pshort("ancient apparatuses");
    set_name("apparatus");
    add_adj("ancient");
    add_adj("stone");
    set_long("This is an ancient stone apparatus. It is made up of three " +
        "adjustable metal circles surrounded by a disc of black stone. " +
        "You can see tiny arrow-markings on all three circles, pointing " +
        "outwards. You see the markings on each circle aligned with a " +
        "small symbol on the surrounding stone disc. The symbols are " +
        "engraved in the surface of the stone, each representing a number " +
        "between 0 and 10. Within the inner circle you see the etched mark " +
        "of a rune.\n");
    add_item(({"circle", "circles"}), "The three circles of metal on the " +
        "apparatus all have a tiny, faint arrow-mark engraved upon them. " +
        "There is an inner, middle, and outer circle, which can each be " +
        "adjusted.\n");
    add_item(({"rune", "glyph"}), "It seems to be an ancient glyph " +
        "of some sort, but you are unsure of its meaning. Looking at " +
        "the surface in detail, you see it is more than just a marking. " +
        "The edges recede into the stone, suggesting a deeper connection " +
        "with the apparatus. It is too shallow to press, but perhaps it is " +
        "sensitive to touch.\n");
    add_item(({"disc", "obsidian disc"}), "Made of obsidian, the disc " +
        "is engraved with symbols representing the numbers between 0 " +
        "and 10, spaced evenly all around.\n");
    add_item(({"inner circle"}), "@@inner_circle@@");
    add_item(({"middle circle"}), "@@middle_circle@@");
    add_item(({"outer circle"}), "@@outer_circle@@");
    add_prop(OBJ_M_NO_STEAL, "The apparatus is too heavy to move.\n");
    add_prop(OBJ_M_NO_GET, "The apparatus is too heavy to move.\n");
    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);

    xaxis = random(11);
    yaxis = random(11);
    zaxis = random(11);

    // Testing parameters.
    xaxis = 6;
    yaxis = 6;
    zaxis = 6;

    circle1 = random(11);
    circle2 = random(11);
    circle3 = random(11);

    broken = 0;

    setuid();
    seteuid(getuid());

}

string
inner_circle()
{
    return "Following the line of the arrow-point, you see the number " +
        circle3 + " on the obsidian disc.\n";
}

string
middle_circle()
{
    return "Following the line of the arrow-point, you see the number " +
        circle2 + " on the obsidian disc.\n";
}

string
outer_circle()
{
    return "Following the line of the arrow-point, you see the number " +
        circle1 + " on the obsidian disc.\n";
}

void
button_reset()
{
    tell_room(environment(this_object()), "The rune on the " +
         "ancient apparatus stops glowing.\n");
    glowbutton = 0;
}

int
query_broken()
{
    return broken;
}

int
summon_portal(string str)
{
    object portal;
    if (str != "rune" && str != "glyph")
    {
        write("Touch what? The rune?\n");
        return 1;
    }

    if (broken == 1)
    {
        tell_room(environment(this_object()), this_player()->query_name() + 
            " touches the apparatus, but nothing happens.\n", this_player());
        write("You touch the rune, but nothing happens. Perhaps the " +
            "apparatus is broken.\n");
        return 1;
    }

    if (glowbutton == 1)
    {
        write("The rune is already glowing. It's probably not the right " +
            "time to do that.\n");
        return 1;
    }

    if ((circle1 == xaxis) && (circle2 == yaxis) && (circle3 == zaxis))
    {
        if (broken == 1)
        {
            tell_room(environment(this_object()), QCTNAME(this_player()) +
                " touches a rune on the apparatus.\nThe rune begins to glow " +
                "faintly with a red colour, but nothing happens.\n",
                this_player());
            write("You touch the rune.\nIt begins to glow faintly with a " +
                "red colour, but nothing happens.\n");
            return 1;
        }

        setuid();
        seteuid(getuid());

        tell_room(environment(this_object()), QCTNAME(this_player()) +
            " touches a rune on the apparatus.\n", this_player());
        write("You touch the rune on the apparatus.\n");
        tell_room(environment(this_object()), "The rune suddently glows " +
            "faintly in a red colour!\nThe apparatus begins to make a " +
            "clicking sound as the circles change position.\n");
        portal = clone_object("/d/Raumdor/common/obj/nportal");
        portal->move(environment(this_object()), 1);

        //this_player()->add_prop(NACCEPTED2, 1);
        this_player()->add_prop(NACCEPTED, 1);

        glowbutton = 1;

        set_alarm(15.0,0.0, &button_reset());

        xaxis = random(11);
        yaxis = random(11);
        zaxis = random(11);

        LOG("necrotemple_portal", capitalize(this_player()->query_real_name()) +
            " opened a nexus portal to necro temple in " + 
            file_name(environment(this_player())) + " at " + 
            ctime(time()) + ".\n");
        return 1;

    }
    tell_room(environment(this_object()), QCTNAME(this_player()) +
        " touches a rune on the apparatus.\nThe rune begins to glow " +
        "faintly with a blue colour, but nothing else happens.\n",
        this_player());
    write("You touch the rune on the apparatus.\nIt begins to glow " +
        "faintly with a blue colour, but nothing else happens.\n");

    glowbutton = 1;

    set_alarm(15.0,0.0, &button_reset());

    return 1;
}

int
nbreak_apparatus(string str)
{
    if (!this_player()->query_skill(COUNCIL))
        return 0;

    if (str != "gateway")
    {
        notify_fail(capitalize(query_verb()) + "the gateway?\n");
        return 0;
    }

    if (broken == 1)
    {
        write("The gateway to the temple are already disabled.\n");
        return 1;
    }

    tell_room(environment(this_object()), QCTNAME(this_player()) + 
        " gestures with unusual motions at the apparatus, which responds by " +
        "making a faint humming sound for a short moment.\n", this_player());

    write("You make a magical gesture towards the apparatus and it makes a " +
        "a faint humming sound for a short moment. You have now disabled " +
        "its ability to open a gateway to the Necromancer temple.\n");

    broken = 1;

    return 1;
}

int
adjust_circles(string str)
{
    int result;
    if (str == "outer circle")
    {
        circle1 = circle1 + 1;
        if (circle1 > 10)
            circle1 = 0;
        result = circle1;
    }
    else if (str == "middle circle")
    {
        circle2 = circle2 + 1;
        if (circle2 > 10)
            circle2 = 0;
        result = circle2;
    }
    else if (str == "inner circle")
    {
        circle3 = circle3 + 1;
        if (circle3 > 10)
            circle3 = 0;
        result = circle3;
    }
    else
    {
        notify_fail("Adjust what? The outer, middle, or inner circle?\n");
        return 0;
    }

    tell_room(environment(this_object()), QCTNAME(this_player()) +
        " adjusts the " + str + "on the apparatus. Its tiny, " +
        "faint arrow-mark now points at the number " + result+ ".\n",
        this_player());
    write("You adjust the " + str + " on the apparatus. Its tiny, faint " +
        "arrow-marks now points at the number " + result + ".\n");
     return 1;
}


void
init()
{
    ::init();
    add_action(summon_portal, "touch");
    add_action(adjust_circles, "adjust");
    add_action(nbreak_apparatus, "disable");
}
