/* Created 4/1/99 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

object alchemist;

void
reset_room()
{
    seteuid(getuid());

    if (!objectp(alchemist))
    {
        alchemist = clone_object(RUST_NPCS +"gnome_alchemist");
        alchemist->equip_me();
        alchemist->move_living("in", TO);
    }
}

create_room()
{
    set_short("A house in the gnome village"); 

    set_long("You have entered a rather messy hut. The walls are" +
        " filled with shelves holding various jars and containers" +
        " of all sizes and shapes. In a corner you see a" +
        " disorganized bed. There is also a large desk and a" +
        " couple of tables holding more jars and piles of" +
        " parchaments. The room is brightly lit by oil lamps.\n");

    add_item("walls","They're nearly all covered in shelves.\n");
    add_item("shelves","The sturdy wooden shelves are solidly" +
        " built, and are probably made to hold a lot of weight.\n");
    add_item(({"jars","containers"}), "@@present_alchemist@@");
    add_item("bed","It's obviously made for a short person, and" +
        " looks very comfortable. Judging from the state it's in," +
        " noone has bothered to make it for a while.\n");
    add_item("desk","The desk is half covered with parchment. The" +
        " other half has been cleared for some reason.\n");
    add_item("tables","These seem to be used just as an extension" +
        " of the shelf space.\n");
    add_item(({"piles of parchments","parchments", "parchment"}), 
        "@@present_alchemist2@@");
    add_item("opening","You can't see outside, since it's covered" +
        " by the fur.\n");
    add_item("ceiling","It's about 10 feet up.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item("lamps", "They cast the room in bright light.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path13","out",0,1);

    reset_room();
}

string
present_alchemist()
{
    if (!present(alchemist))
    {
        if(TP->query_skill(SS_ALCHEMY) > 49 && 
            TP->query_skill(SS_LANGUAGE) >64)
        {
            return "You look through the jars and containers, and" +
                " are able to decipher the cryptic language the" +
                " labels have been written in. However, it still" +
                " makes no sense. Must be written in some kind of" +
                " code.\n";
        }
        else
        {
            return "You look through the jars and containers, but" +
                " are unable to decipher any of the labels.\n";
        }
    }
    else
    {
        return "As you move closer to examine the jars and" +
            " containers, the gnome stops" +
            " you with a hard stare.\n";
    }
}

string
present_alchemist2()
{
    if(!present(alchemist))
    {
        if(TP->query_skill(SS_LANGUAGE) > 64)
        {
            return "You are able to decipher the cryptic language" +
                " the parchments have been written in, but it" +
                " still makes no sense at all. It must be written" +
                " in some kind of code.\n";
        }
        else
        {
            return "You are unable to decipher the language in" +
                " which the parchments have been written.\n";
        }
    }
    else
    {
        return "The gnome stops you with a hard" +
            " stare as you approach to examine the parchments.\n";
    }
}