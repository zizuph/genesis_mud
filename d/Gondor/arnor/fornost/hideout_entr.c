/*
 *      /d/Gondor/arnor/fornost/hideout_entr.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
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

    add_cmd_item("door", "enter", "@@fail1");
    add_cmd_item("door", "open", "@@fail2");
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
    if (TP->query_guild_name_occ() == "Rangers of the Westlands" ||
        TP->query_skill(SS_AWARENESS) >= AWARE_NEEDED)
        desc +=  "Under the arch the faint outline of a door can "+
        "be seen. ";
    desc += query_arnor_time();

    return BSN(desc);
}

public void
init()
{
    ::init();
    add_action("gr_say", "grsay");
    add_action("s_say", "say");
    add_action("s_say", "'", 1);
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

int
gr_say(string str)
{
    if(str == "estel" && (TP->query_guild_name_occ() == 
    "Rangers of the Westlands"))
    {
        set_alarm(1.0, 0.0, "closed");
    }
    return 0;
}

void
enter()
{
     object opener = TP;

     opener->catch_msg("As you speak the stone door opens. You leave "+
     "through the door.\n");
     say(QCTNAME(opener) + " speaks and the door opens.\n");
     tell_room(RANGER_NORTH_DIR + "stairs", "The stone door opens.\n");
     opener->move_living("through the door", RANGER_NORTH_DIR + "stairs");
     opener->catch_msg("The door closes behind you.\n");
     tell_room(TO, "The stone door closes.\n", opener);
}


int
s_say(string str)
{
    if(str == "estel" || query_verb() == "'estel")
    {
        set_alarm(1.0, 0.0, "speak");
    }
    return 0;   
}   

void
speak()
{
    TP->catch_msg("As you speak the star glows briefly.\n");
    say("As "+ QCTNAME(TP)+" speaks the star glows briefly.\n");
}

void
closed()
{
    TP->catch_msg("As you speak the star glows brightly!\n"
      + "The door fails to open like it used to, but somehow you feel there's yet hope.....\n");
    say("As "+ QCTNAME(TP)+" speaks, the star glows brightly.\n");
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
    "Only those who carry ancient 'Hope' in heart and mouth can pass here.\n";
}

int
fail1()
{
    TP->catch_msg("You must open the door first.\n");
    return 1;
}

int
fail2()
{
    TP->catch_msg("But how will you do that? There is neither a handle nor a "+
    "keyhole.\n");
    return 1;
}
