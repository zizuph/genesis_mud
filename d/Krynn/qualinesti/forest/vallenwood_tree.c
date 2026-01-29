
/* File name  : vallenwood_tree.c
 * Description: One of the vallendwood trees in Qualinesti.
 *
 * Blizzard, 15.03.2004
 *
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <tasks.h>
#include <macros.h>
#include "../local.h"

inherit  "/std/room.c";

#define  BELOW_TREE          (FDIR + "forest5")
#define  CLEARING            (FDIR + "clearing")
#define  APPLE_TREE          (FDIR + "apple_tree")

#define  READY_TO_JUMP       "_player_ready_to_jump"

public void
reset_qualinesti_room()
{

}

public string
clearing_desc()
{
    object *seen;
    string clearing_desc = "";
    
    seen = FILTER_LIVE(CLEARING->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    clearing_desc = "There is a small clearing just east from here. " +
        "The bubbling stream circles slowly among the trees below your " +
        "feet. You wonder if you could jump there.\n";
    
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

public string
ground_desc()
{
    object *seen;
    string ground_desc = "";
    
    if ( TP->query_prop(READY_TO_JUMP) )
    {
        return "You are standing on the solid branch just a few feet " +
            "above the bubbling stream.\n";
    }
    
    seen = FILTER_LIVE(BELOW_TREE->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    ground_desc = "The forest stretches out in all directions and it " +
        "looks all the same. Only to the east you notice a small clearing " +
        "on the opposite side of the stream that circles below.\n";
        
    write("You take a quick glance at the ground below.\n");
    say(QCTNAME(TP) + " takes a quick glance at the ground below.\n");
    
    if ( sizeof(seen) )
    {
        return ground_desc + "You see " + COMPOSITE_LIVE(seen) +
            " standing on the ground.\n";
    }
    else
        return ground_desc;
        
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
    set_short("on a solid branch of the vallenwood tree");
    set_long("You are stainding on a solid branch of the vallenwood " +
        "tree. It's so thick that you do not need to worry it could snap. " +
        "From this place you can see quite a big part of the forest, but " +
        "it looks almost the same in all directions. Only to the east " +
        "you notice a small clearing, just on the opposite side of " +
        "the stream that flows below.\n");
	     
    add_item(({ "clearing", "small clearing" }), clearing_desc);
    add_item(({ "ground", "below", "forest" }), ground_desc);
    add_item(({ "treetops", "treetop", "trees" }),
        "You climb the trunk a bit higher and look around. The forest " +
        "stretches out in all directions.\n");
    add_item("tree", "What tree are you trying to look at? There are many " +
        "of them around.\n");
    add_item(({ "apple tree", "lone tree", "small tree" }),
        "There is a small apple tree growing on the opposite side of the " +
        "stream. You guess the distance is a bit too big for a jump.\n");
    add_item(({ "stream", "river", "water" }), "A small bubbling stream " +
        "circles slowly among trees just to the east.\n");
    add_item(({ "branches", "branch" }),
        "The tree has many strong and thick branches. One of the them " +
        "stretches eastwards, above the stream.\n");
    
    add_cmd_item(({ "ground", "clearing", "forest" }), ({ "glance", "look" }),
        ground_desc);
        
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK, dis_check);
    
    reset_qualinesti_room();
    
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
        "the big vallenwood tree.\n", TP);
    TP->move_living("M", BELOW_TREE);

    return 1;
}

public int
do_jump(string str)
{
    if ( strlen(str) && parse_command(str, ({}), "[to] [over] [the] [apple] 'clearing' / 'east' / 'stream' / 'tree'") )
    {
        if ( (TP->resolve_task(TASK_ROUTINE, ({ SS_ACROBAT, TS_DEX })) < 0) ||
            !TP->query_prop(READY_TO_JUMP) )
        {
            write("You jump over the steam and land with a thump " +
                "on its other side.\n");
            say(QCTNAME(TP) + " jumps over the stream and lands on the " +
                "ground with a thump.\n");
            tell_room(CLEARING, QCTNAME(TP) + " lands on the ground with " +
                "a loud thump.\n", TP);
            TP->move_living("M", CLEARING);

            TP->heal_hp(-150);
                
            if ( TP->query_hp() <= 0 )
            {
                TP->do_die(TO);
            }
        
            return 1;
        }
        
        if ( (TP->query_race() != "gnome" || TP->query_race() != "hobbit") &&
            (TP->query_prop(OBJ_I_WEIGHT) > 60000) )
        {
            if ( random(5) == 3 )
            {
                write("You jump, but unfortunately it was not long enough " +
                    "and you land with a splash in the stream.\n");
                say(QCTNAME(TP) + " tries to jump over the stream, but " +
                    "lands in the water with a splash!\n");
                tell_room(CLEARING, QCTNAME(TP) + " lands in the stream " +
                    "with a splash!\n", TP);
                TP->move_living("M", CLEARING);
                
                TP->heal_hp(-80);
                
                if ( TP->query_hp() <= 0 )
                {
                    TP->do_die(TO);
                }
        
                return 1;
            }
            
            if ( random(5) == 4 )
            {
                write("You jump, but as you grasp one of the branches it " +
                    "snaps and you land on the ground with a thump!\n");
                say(QCTNAME(TP) + " jumps, but as " + HE(TP) + " grasps " +
                    "one of the branches... it snaps! " + QCTNAME(TP) +
                    " lands on the ground with a soft thump!\n");
                tell_room(CLEARING, QCTNAME(TP) + " lands on the ground " +
                    "with a thump! A few small branches fall on " + HIS(TP) +
                    " head.\n", TP);
                TP->move_living("M", CLEARING);

                TP->heal_hp(-150);
                
                if ( TP->query_hp() <= 0 )
                {
                    TP->do_die(TO);
                }

                return 1;
            }        
        }
        
        write("You take a breath and jump over the stream! Suddenly, you " +
            "feel like someting pulls your arms as you grasp one of " +
            "the branches and land on the apple tree.\n");
        say(QCTNAME(TP) + " takes a breath and jumps high into the air! " +
            "You notice " + HIM(TP) + " landing on one of the more solid " +
            "branches of the apple tree that grows on the other side of " +
            "the stream.\n");
        tell_room(APPLE_TREE, QCTNAME(TP) + " suddenly lands on the branch " +
            "next to you, causing the tree to shake dangerously.\n", TP);
        TP->move_living("M", APPLE_TREE);

        return 1;
    }
    
    if ( strlen(str) && parse_command(str, ({}), "[to] [the] 'ground' / 'down'") )
    {
        write("You jump down to the ground.\n");
        say(QCTNAME(TP) + " jumps down to the ground.\n");

        if ( TP->query_prop(READY_TO_JUMP) )
        {
            TP->move_living("M", CLEARING);
            tell_room(CLEARING, QCTNAME(TP) + " lands on the ground with " +
                "a loud thump.\n", TP);
        
            return 1;
        }

        tell_room(BELOW_TREE, QCTNAME(TP) + " lands on the ground with " +
            "a loud thump.\n", TP);
        TP->move_living("M", BELOW_TREE);
        
        return 1;
    }
     
    return 0;
}

public int
do_approach(string str)
{
    if ( !strlen(str) )
    {
        notify_fail("Approach what?\n");
        return 0;
    }
    
    if ( parse_command(str, ({}), "[carefully] [to] [the] [a] [small] [lone] [apple] [opposite] [river] 'east' / 'tree' / 'clearing' / 'stream' / 'bank' [carefully]" ) )
    {
        if ( !TP->query_prop(READY_TO_JUMP) )
        {
            write("Carefully putting your feet on the branch, you approach " +
                "the opposite river bank.\n");
            say("Making " + HIS(TP) + " steps slowly, " + QTNAME(TP) + 
                " moves eastwards towards the clearing.\n");
            TP->add_prop(READY_TO_JUMP, 1);

            return 1;
        }
        
        write("Buy you can't go further in that direction.\n");
        return 1;
    }
    
    if ( parse_command(str, ({}),
        "[carefully] [to] [the] [a] [vallenwood] 'west' / 'vallenwood' / 'trunk' / 'back' [carefully]" ) )
    {
        if ( TP->query_prop(READY_TO_JUMP) )
        {
            write("You chicken! Got scared? You slowly move back to " +
                "the trunk of the vallenwood.\n");
            say(QCTNAME(TP) + " looks scared and slowly moves back, " +
                "approaching the trunk of a vallenwood tree.\n");
            TP->remove_prop(READY_TO_JUMP);

            return 1;
        }
        
        write("But you are standing just next to the trunk of this " +
            "vallenwood. There is no need to be scared.\n");
        say(QCTNAME(TP) + " looks around with a fear in " + HIS(TP) +
            " eyes.\n");

        return 1;
    }
    
    notify_fail("Approach what?\n");
    return 0;
     
}

public void
init()
{
    ::init();
    add_action(do_climb   , "climb");
    add_action(do_jump    , "jump");
    add_action(do_approach, "approach");
    add_action(do_approach, "move");
}

public void
leave_inv(object ob, object new)
{
    ::leave_inv(ob, new);
    
    if ( ob->query_prop(READY_TO_JUMP) )
        ob->remove_prop(READY_TO_JUMP);
}
