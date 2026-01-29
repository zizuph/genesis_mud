#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <money.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

string *things = ({(KOBJ + "bells"), (KOBJ + "cloth"), (KOBJ + "lollipop"),
    (KOBJ + "cfeather"), (KOBJ + "stone"), (KOBJ + "string2")});

int found_junk = 0;
int reset_count = 1;
object kender, cat, kitten, kender_jasmine, junk, fountain;

void
reset_kendermore_room()
{

    if (!find_living("jasmine"))
    {
        kender_jasmine = clone_object(KNPC + "jasmine");
        kender_jasmine->move(TO);
    }

    if (reset_count)
    {
        found_junk = 0;
        reset_count = 0;
    }

    if (!reset_count)
        reset_count++;

    if (!kender)
        {
            kender = clone_object(KNPC + "std_kender");
            kender->move(TO);
        }

    if (!cat)
        {
            cat = clone_object(KNPC + "cat");
            cat->move(TO);
        }

    if (!kitten)
        {
            kitten = clone_object(KNPC + "kitten");
            kitten->move(TO);
            kitten = clone_object(KNPC + "kitten");
            kitten->move(TO);
            kitten = clone_object(KNPC + "kitten");
            kitten->move(TO);
            kitten = clone_object(KNPC + "kitten");
            kitten->move(TO);
        }

    if (!fountain)
    {
        fountain = clone_object(KOBJ + "fountain");
        fountain->move(TO);
    }
}

void
create_kendermore_room()
{
    setuid();
    seteuid(getuid());
    
    set_short("By a marble fountain");
    set_long("@@long_descr");
    add_item(({"house", "houses"}), "Even the houses here have a " + 
        "carefree feeling. " +
        "There doesn't seem to be any way in from here.\n"); 
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds " + 
        "beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item(({"fountain", "water fountain"}), "Sparkling clear water " + 
        "bursts from a statue in the center of the fountain. It is made " + 
        "of white marble stone, and there are some coins tossed in the " + 
        "water.\n");
    add_item("coins", "Leave them alone! They are other " + 
        "peoples' wishes!\n");
    add_item(({"marble", "white stone", "marble stone", "stone"}),
        "It looks very well made, except for a tiny flaw near the base.\n");
    add_item(({"flaw", "base"}), "It looks like a loose stone has been " + 
        "removed and put back in! Maybe you can wiggle it loose.\n");
    add_item("loose stone", "Maybe it could be wiggled loose.\n");

    add_cmd_item("stone", "wiggle", "@@wiggle_stone");
    add_cmd_item("house", "enter", "@@enter_house");
    
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_exit(KROOM + "street25", "north", 0);
    add_exit(KROOM + "street28", "east", 0);

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");

    reset_kendermore_room();
    
    MONEY_MAKE_CC(random(8))->move(fountain, 1);
    MONEY_MAKE_SC(random(8))->move(fountain, 1);
    MONEY_MAKE_GC(random(8))->move(fountain, 1);
    MONEY_MAKE_PC(random(8))->move(fountain, 1);
}

void
init()
{
    ::init();
    add_action("drink_water", "drink");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "Houses stand on both sides " + 
        "of you. A beautiful white fountain decorates the center of the " + 
        "street. " + street_descr() + " The road continues on its " + 
        "winding way to the " + find_exits() + ". Numerous signs point " + 
        "in all directions, but they tend to contradict each other and " + 
        "point in directions where there are no exits.\n");
}

string
enter_house()
{
    write("You look for a way into the house, but find none.\n");
    say(QCTNAME(TP) + " searches for a way into the house, but finds " + 
        "none.\n");
    return "";
}

string
wiggle_stone()
{
    object ob;
    if (found_junk)
    {
        write("Despite your best efforts, the stone seems jammed in there " + 
            "pretty well.\n");
        say(QCTNAME(TP) + " kneels down and starts doing something to the " + 
            "base of the fountain.\n");
        return "";
    }

    ob = clone_object(things[random(6)]);
    if (ob->move(TP))
        ob->move(TO);
    
    found_junk = 1;

    write("You find a loose stone in the base of the fountain and pull it " + 
        "loose. You find something hidden behind it, and quickly pocket it!\n");
    say(QCTNAME(TP) + " kneels down and starts doing something to the " + 
        "base of the fountain.\n");
    return "";
}
        
int
drink_water(string str)
{
    NF("Drink what?\n");
    if ((str == "from water") || (str == "water") || 
        (str == "from fountain") || (str == "water from fountain") ||
        (str == "from liquid") ||
        (str == "from red liquid"))
    {
        if (TP->drink_soft(TP->drink_max() / 16,0))
        {
            if(present("fountain", TO)->is_red())
            {
                say(QCTNAME(TP) + " drinks some red liquid from " +
                    "the fountain.\n");
                write("You drink some sweet red liquid from the " +
                    "fountain and feel very refreshed.\n");
            }
        
            else
            {
                say(QCTNAME(TP) + " drinks some water from the fountain.\n");
                write("You drink some ice cold water and feel very refreshed.\n");
            }
        }
        else
            write("You are bursting already!\n");
        return 1;
    }
    return 0;
}

