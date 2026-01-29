
/* File name  : apple_tree.c
 * Description: A small apple tree in Qualinesti.
 *
 * Blizzard, 15.03.2004
 *
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "../local.h"

inherit  "/std/room.c";

#define  BELOW_TREE          (FDIR + "clearing")

object   kender;

public void
reset_room()
{
    if ( !kender )
    {
        kender = clone_object(NPC + "quiker");
        kender->move(TO, 1);
    }
    
    ::reset_room();

}

public string
ground_desc()
{
    object *seen;
    string clearing_desc = "";
    
    seen = FILTER_LIVE(BELOW_TREE->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    clearing_desc = "There is a small clearing just a few feet below you. " +
        "The bubbling stream circles slowly among the trees.\n";
    
    write("You take a quick glance at the ground below.\n");
    say(QCTNAME(TP) + " takes a quick glance at the ground below.\n");
    
    if ( sizeof(seen) )
    {
        return clearing_desc + "You see " + COMPOSITE_LIVE(seen) +
            " standing on the ground.\n";
    }
    else
        return clearing_desc;
        
}

public mixed
dis_check()
{
    if ( environment(TP) == TO && TP->query_base_stat(SS_DIS) < 90 )
    {
        return "When you prepare to attack your enemy, the branch below " +
            "your feet waggles. You decide to hug the trunk instead.\n";
    }
    else
        return 0;
     
}

public void
create_room()
{
    set_short("on a small apple tree");
    set_long("You are stainding on one of the thick branches of the " +
        "appple tree. The sounds of the forest surround you and from " +
        "time to time you take a quick glance at the ground below, " +
        "attracted by the noise coming from that direction.\n");
	     
    add_item(({ "clearing", "ground", "forest" }), ground_desc);
    add_item(({ "treetops", "treetop", "trees" }),
        "You climb the trunk a bit higher and look around. The forest " +
        "stretches out in all directions. This tree is not so big and " +
        "you can't see much more.\n");
    add_item("tree", "What tree are you trying to look at? There are many " +
        "of them around.\n");
    add_item(({ "fruits", "fruit", "apples", "apple" }),
        "You peer around looking for some fruits, but sadly there are " +
        "none. Maybe someone picked them earlier.\n");
    add_item(({ "apple tree", "lone tree", "small tree" }),
        "You are standing on one of the branches on this apple tree. It's " +
        "not so high, but you feel more comfortable when you have a strong " +
        "grip.\n");
 
    add_cmd_item(({ "ground", "clearing", "forest" }), ({ "glance", "look" }), 
        ground_desc);
        
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK, dis_check);
    
    reset_room();
    
}

public int
do_climb(string str)
{
    if ( str != "down" )
    {
        notify_fail("Climb down?\n");
        return 0;
    }
    
    write("You slowly climb down to the ground.\n");
    say(QCTNAME(TP) + " slowly climbs down to the ground.\n");
    tell_room(BELOW_TREE, QCTNAME(TP) + " arrives climbing down from " +
        "the small apple tree.\n", TP);
    TP->move_living("M", BELOW_TREE);

    return 1;
}

public int
do_jump(string str)
{
    if ( str == "down" || str == "to the ground" || str == "to ground" )
    {
        write("You jump down to the ground.\n");
        say(QCTNAME(TP) + " jumps down to the ground.\n");
        tell_room(BELOW_TREE, QCTNAME(TP) + " lands on the ground with " +
            "a loud thump.\n", TP);
        TP->move_living("M", BELOW_TREE);
        
        return 1;
    }
    
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
    add_action(do_jump, "jump");
}

