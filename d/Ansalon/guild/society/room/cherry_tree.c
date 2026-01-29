/*
 * /d/Ansalon/guild/society/room/cherry_tree.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 * 
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Up in the cherry tree. Players can pull the rope up for privacy.
 *
 * Coded by Gwyneth, 1999
 */
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include DL_CLOCK

inherit KENDERMORE_OUT;

int fruit_here;

string tree_desc();
string hole_desc();
string climb_down();
string pick_fruit();
string pull_rope();
string drop_rope();
string long_descr();

void
reset_kendermore_room()
{
    if (!fruit_here)
        fruit_here = 1;
}

void
create_kendermore_room()
{
    set_short("In the branches of a cherry tree");
    set_long(&long_descr());
    add_item(({"fruit", "cherries", "cherry", "blossoms", "blooms", "blossom",
        "leaves", "leaf", "branches", "branch", "birds", "bird", "lone bird",
        "tree"}), &tree_desc());
    add_item(({"hole", "rope", "strong rope", "middle"}), &hole_desc());
    add_item(({"platform", "wooden platform", "house", "tree house",
        "small tree house", "small house"}), "Solid planks of dark wood " + 
        "make a sturdy base for the tree house.\n");
    add_cmd_item(({"down", "down rope"}), "climb", &climb_down());
    add_cmd_item(({"strong rope", "strong rope up", "up strong rope", "rope",
        "rope up", "up rope"}), ({"draw", "pull"}),
        &pull_rope());
    add_cmd_item(({"rope", "strong rope"}), ({"lower", "drop"}), &drop_rope());
    add_cmd_item(({"cherries", "fruit", "cherry"}), "pick", &pick_fruit());

    reset_kendermore_room();
}

/* Function name : pick_fruit
 * Description   : Pick cherries in the summer
 * Returns       : The description of the fruit picking
 */
string
pick_fruit()
{
    string str;
    switch(GET_SEASON)
    {
    case SPRING:
        str = "The only visible cherries are small and green. Leave them " +
            "alone, and there will be delicious red cherries to be had.\n";
        break;
    case SUMMER:
        if (fruit_here < 8)
        {
            str = "You pick a handful of ripe red cherries.\n";
            clone_object(KGOBJ + "cherries")->move(this_player());
            fruit_here++;
        }
        else
            str = "The lower branches seem to have been picked clean of " +
                "cherries!\n";
        break;
    case AUTUMN:
        str = "The only remaining cherries are only good for the birds.\n";
        break;
    case WINTER:
        str = "There aren't any cherries to be had!\n";
        break;
    }
    return str;
}

public void
enter_inv(object ob, object from)
{
    if (function_exists("create_coins", ob) != 0)
    {
        write("You place " + ob->short() + " on the platform, but they " +
            "roll off and land in the courtyard.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " places " + 
            ob->short() + " on the platform, but they roll off and land in " +
            "the courtyard.\n");
        tell_room(KGROOM + "courtyard", "You see " + ob->short() +
            " fall down from above.\n");
        ob->move(KGROOM + "courtyard");
        ::enter_inv(ob, from);
        return;
    }

    if (!interactive(ob))
    {
        write("You place the " + ob->short() + " on the platform, but it " + 
            "rolls off and lands in the courtyard.\n");
        tell_room(KGROOM + "courtyard", "You see a " + ob->short() +
            " fall down from above.\n");
        ob->move(KGROOM + "courtyard");
    }
    ::enter_inv(ob, from);
}

string
drop_rope()
{
    if ((KGROOM + "courtyard")->query_rope())
        return("The rope is already lowered.\n");
    else
    {
        (KGROOM + "courtyard")->change_rope(1);
        tell_room(KGROOM + "courtyard", "A rope falls down from a tree " + 
            "above.\n");
        tell_room(KGROOM + "cherry_tree", QCTNAME(this_player()) + 
            " lowers the rope down to the ground. People can now climb " +
            "up and down it.\n", this_player());
        return("You lower the rope down to the ground. People can now " +
            "climb up and down it.\n");
    }
}

string
pull_rope()
{
    if ((KGROOM + "courtyard")->query_rope())
    {
        (KGROOM + "courtyard")->change_rope(0);
        tell_room(KGROOM + "courtyard", "The rope is drawn up into the " + 
            "tree. It is now impossible to climb up.\n");
        tell_room(KGROOM + "cherry_tree", QCTNAME(this_player()) + 
            " hauls the rope up, and coils it neatly by the hole. You " +
            "think nobody will be able to disturb you now.\n", this_player());
        return("You haul the rope up, and coil it neatly by the hole. " + 
            "You think nobody will be able to disturb you now.\n");
    }
    else
        return("The rope is already pulled up.\n");
}

string
hole_desc()
{
    if ((KGROOM + "courtyard")->query_rope())
        return "A strong rope leads down through a hole cut " +
            "in the middle of the platform. You could possibly climb " +
            "down, or draw the rope up to prevent others from climbing " +
            "up.\n";
    else
        return "A strong rope is coiled up by a hole cut in the " +
            "middle of the platform. You could lower the rope to allow " +
            "people to climb up or down it.\n";
}

string
tree_desc()
{
    string str;

    switch(GET_SEASON)
    {
        case SPRING:
            str = "White cherry blossoms surround you on all sides, " +
                "while a sweet bird song floats through the air. Soon, " +
                "the branches will be laden with cherries.\n";
            break;
        case SUMMER:
            str = "Red ripe cherries laden the branches around you, and " +
                "fallen white flowers coat the platform. Several birds " +
                "swoop down from above to feast and sing in the branches.\n";
            break;
        case AUTUMN:
            str = "The white blossoms of spring are long gone, and only " +
                "a few overripe cherries remain. The birds still sing " +
                "sweetly in the branches, despite the lack of fruit to " +
                "feast on.\n";
            break;
        case WINTER:
            str = "The branches are bare of fruit, blossom or leaf now " +
                "that winter has fallen. Yet a soft beauty remains hidden " +
                "in the winter slumber of this cherry tree. A lone bird " +
                "hidden in the branches sings a sweet melody that hangs " +
                "in the cold winter air.\n";
            break;
    }
    return str;
}

string
long_descr()
{
    
    string long, rope_desc;

    if ((KGROOM + "courtyard")->query_rope())
        rope_desc = "A strong rope leads down through a hole cut " + 
            "in the middle of the platform. You could possibly climb " + 
            "down, or draw the rope up to prevent others from climbing " + 
            "up.";
    else
        rope_desc = "A strong rope is coiled up by a hole cut in the " + 
            "middle of the platform. You could lower the rope to allow " + 
            "people to climb up or down it.";
    switch(GET_SEASON)
    {
        case SPRING:
            long = "White cherry blossoms surround you on all sides, " + 
                "while a sweet bird song floats through the air. Soon, " + 
                "the branches will be laden with cherries.";
            break;
        case SUMMER:
            long = "Red ripe cherries laden the branches around you, and " + 
                "fallen white flowers coat the platform. Several birds " + 
                "swoop down from above to feast and sing in the branches.";
            break;
        case AUTUMN:
            long = "The white blossoms of spring are long gone, and only " + 
                "a few overripe cherries remain. The birds still sing " + 
                "sweetly in the branches, despite the lack of fruit to " + 
                "feast on.";
            break;
        case WINTER:
            long = "The branches are bare of fruit, blossom or leaf now " + 
                "that winter has fallen. Yet a soft beauty remains hidden " + 
                "in the winter slumber of this cherry tree. A lone bird " + 
                "hidden in the branches sings a sweet melody that hangs " + 
                "in the cold winter air.";
            break;
    }

    return (tod_descr() + season_descr() + " A wooden platform has been " + 
        "built here to make a small tree house. " + rope_desc + " " + 
        long + "\n");
}

string
climb_down()
{
    if ((KGROOM + "courtyard")->query_rope())
    {
        write("You climb down the rope.\n");
        say(QCTNAME(this_player()) + " climbs down the rope.\n");
        this_player()->move_living("M", KGROOM + "courtyard", 1, 0);
        tell_room(KGROOM + "courtyard", QCTNAME(this_player()) + 
            " climbs down from the rope.\n", this_player());
    }
    else
        write("You must lower the rope first.\n");
    return "";
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters, and escorts " +
            "you out of the guild.\n");
        say("A very large looking kender enters, and escorts " +
            QTNAME(who) + " out of the guild.\n", who);
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " +
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KROOM + "joinroom", 0, 0);
        return;
    }
    return;
}

