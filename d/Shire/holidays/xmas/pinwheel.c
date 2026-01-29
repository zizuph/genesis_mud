/*
 * Pinwheel
 * -- Finwe, April 2001
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";
inherit "/lib/keep";


void
create_object()
{
    seteuid(getuid());

    set_name("pinwheel");
    set_pname("pinwheels");
    set_adj("colorful");
    set_long("This is a eight pointed snowflake attached to a long " +
        "thin piece of wood. The snowflake is made of colorful " +
        "paper. A golden nail runs through the center of the " +
        "snowflake and is attached to the top of the piece of wood. " +
        "The snowflake can be spun around and around.\n");
    add_item(({"nail", "gold nail"}),
        "The nail is small and attaches the paper snowflake to the " +
        "piece of wood. The head of the nail is rounded.\n");
    add_item(({"piece of wood"}),
        "The piece of wood is about arm's length and pencil " +
        "thin. Attached to the to top is a paper snowflake.\n");
    add_item(({"snowflake", "paper snowflake"}),
        "The snowflake is made from a square piece of paper. The " +
        "eight corners are gathered to the center of the " +
        "paper and form a eight pointed snowflake. A golden nail runs " +
        "through the center of the snowflake and keeps the four " +
        "corners together.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);

    set_keep(1);
}


void init() 
{
    add_action("blow_pinwheel", "blow");
    add_action("spin_around", "spin");
}

int blow_pinwheel(string str)
{
    if(str !="pinwheel") return 0;

    say(QCTNAME(TP) + " blows on " + HIS_HER(TP) + short() + 
        ". It spins around rapidly for a few minutes, creating " +
        "a blur of color at the top of the stick. The pinwheel " +
        "slows down and stops spinning.\n"); 
    TP->catch_msg("You blow on the " + short() + ". It spins " +
        "around rapidly for a few minutes, creating a blur of " +
        "color at the top of the stick. The pinwheel slows down " +
        "and stops spinning.\n");
    return 1;
}                 

 int spin_around(string str)
{
    if(str !="around") return 0;

    say(QCTNAME(TP) + " extends " + HIS_HER(TP) + " arm and spins " +
        "around quickly. The "+short() + " spins around rapidly " +
        "for a few minutes, creating a blur of color at the top " +
        "of the stick. The pinwheel slows down and stops " +
        "spinning. " + QCTNAME(TP)+ " stumbles around " +
        "momentarily and almost falls down.\n"); 
    TP->catch_msg("You extend your arm and spin around quickly. " +
        "The " + short() + " spins around rapidly for a few " +
        "minutes, creating a blur of color at the top of the " +
        "stick. The pinwheel slows down and stops spinning. You " +
        "stumble around momentarily and almost fall down.\n");
    return 1;
}
