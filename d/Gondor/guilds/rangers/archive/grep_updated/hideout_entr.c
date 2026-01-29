/*
 *      /d/Gondor/arnor/fornost/hideout_entr.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 *      30-Mar-2002, Alto:  Revision - this is no longer entrance to RoN!
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define AWARE_NEEDED 34

public void
create_fornost()
{
    set_short("inside a ruined tower in the ruins of Fornost");

    add_tower_wall();
    add_item(({ "stone arch", "arch" }),
    "There is an inscription written on the arch.\n");
    add_item(({ "stone door", "door" }), BSN(
    "The door is made of stone. "+
    "In the upper half of the door there appear to be some runes. "+
    "Below the runes you see two symbols, a star and a tree. "+
    "In the very center of the door is a many rayed star. "+
    "Furthest down is the tree."));
    add_item("inscription", "@@inscription");
    add_item("runes", "@@runes");
    add_item("star", "It is the star of the house of Feanor.\n");
    add_item("tree", "It is the white tree of Gondor.\n");

    add_cmd_item("runes", "read", "@@runes");
    add_cmd_item("inscription", "read", "@@inscription");
    
    add_exit(FORNOST_DIR + "l_tower", "out", 0, 1);
}

string
set_arnor_long()
{
    string desc;

    desc = "Inside a ruined tower in the ruins of Fornost. "+
    "The top of the walls of the tower "+
    "have been destroyed, but the lower part is still in good shape. "+
    "A stone arch is in the wall. ";
    desc += query_arnor_time();

    return BSN(desc);
}

public void
init()
{
    ::init();
    add_action("touch", "touch");
}

int
touch(string str)
{
    if(str == "star")
    {
         TP->catch_msg(BSN("You touch the star and marvel. The star is made "+
         "with such great skill that it feels magical to the touch."));
         return 1;
    }
    if(str == "runes")
    {
         TP->catch_msg("You touch the runes and feel that they are inscribed "+
         "beautifully.\n");
         return 1;
    }
    if(str == "tree")
    {
         TP->catch_msg("You touch the tree and feel that it is carved "+
         "exquisitely.\n");
         return 1;
    }
    else
    {
         TP->catch_msg("Touch what?\n");
         return 1;
    }
}


string
runes()
{
    return "\n"+
    "        #  #                #       \n"+
    "       #  #                #        \n"+
    "      #                             \n"+
    "     # ##   #   ###    ######   #   \n"+
    "    #    #   # #   #  #   #  ###    \n"+
    "    #    #    #    #     #          \n"+
    "    #    #    #    #    #           \n"+
    "     ####     #  ##      ###        \n"+
    "              #                     \n"+
    "              #                     \n"+
    "              #                     \n"+
    "\n";
}

string 
inscription()
{
    return  "You read:\n"+
    "There remains much hope in the world. It cannot be found here, however.\n";
}
