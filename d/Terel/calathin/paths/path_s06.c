// path_s06.c
// This path runs southwest from the big Tree and then 
// west behind the townhouses toward the West Gate.
// Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
inherit CALATHIN_DIR + "paths/path_s00";
#define STUMPED "_terel_i_am_stumped_now"
#define TREE   CALATHIN_DIR + "trees/tree_s06"

public void
create_terel_room()
{
    set_short("path along the forest edge");
    set_long("You are midway along a path through the forest's edge. "+
      "The trees grow thickly still, even though you can see evidence "+
      "of cutting here and there. A towering pine tree rises in the "+
      "east, marking the north end of the Calathin town square. "+
      "West are the walls that enclose and protect the area, with "+
      "the icy wilderness and imposing mountains beyond them.\n");

    add_exit(CALATHIN_DIR + "paths/path_s07", "west", 0);
    add_exit(CALATHIN_DIR + "paths/path_s05", "east", 0);	

    /* inherited from path_s00 */
    add_here();
    add_town();
    add_trees();
    add_buildings();
}



int 
stump_act(string str)
{

    notify_fail(capitalize(query_verb()) + " how or where?\n");
    if (!strlen(str))
	return 0;

    if (str == "up")
    {
	notify_fail("The trunks of the trees are too icy to "+
	  "climb, and the branches are too high to reach.\n");
	return 0;
    }

    /* stand on the stump */
    if (!parse_command(str, ({}),
	"[on] [a] / [the] 'stump'", str))
    {
	notify_fail("Where do you want to stand?\n");
	return 0;
    }

    TP->add_prop(STUMPED, 1);	
    write("You "+ query_verb() +" "+ 
      "up on top of the stump. Don't you feel tall! "+
      "You've got a nice view of the West Road and some "+
      "overhanging branches.\n");
    say(QCTNAME(this_player()) + " stands up "+
      "on top of one of stumps nearby.\n");		
    return 1;	
}

int
jump_act(string str)
{

    if (!strlen(str))
	return 0;

    if (!TP->query_prop(STUMPED))
    {
	write("You "+ query_verb() +" up into the air, making "+
	  "deep imprints in the snow when you land.\n");
	say(QCTNAME(TP) +" "+ query_verb() +"s into the air and "+
	  "leaves deep imprints in the snow.\n");
	return 1;
    }

    /* leap for a branch */
    if (!parse_command(str, ({}), "[up] [for] [a] / [at] [the] "+
	"[overhanging] 'branch' / 'branches'", str))
    {
	notify_fail(capitalize(query_verb()) +" for what?\n");
	return 0;
    }


    write("You "+ query_verb() +" up for a branch and manage to grasp "+
      "hold of it and use it to climb up into a tree.\n");
    say(QCTNAME(this_player()) + " "+ query_verb() +"s up for a  "+
      "branch and uses it to climb up into a tree.\n");	
    this_player()->move_living("X", TREE, 1, 0);
    this_player()->remove_prop(STUMPED);		
    return 1;		



}

public void
init()
{
    ::init();

    add_action(stump_act, "stand");
    add_action(stump_act, "climb");
    add_action(jump_act,  "jump");
    add_action(jump_act,  "leap");
    add_action(jump_act,  "lunge");	
}	

