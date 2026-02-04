// path_01.c
// This path runs southwest from the big Tree and then 
// west behind the townhouses toward the West Gate.
// Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
inherit CALATHIN_DIR + "paths/path_s00";

public void
create_terel_room()
{ 
    set_short("path near the towering pine");
    set_long("The biggest pine tree you've ever seen rises to "+
      "the east. It towers over all the other trees, providing "+
      "the Calathin town square with its signature landmark. "+
      "Thick forest surrounds you here. There is a juncture "+
      "to the northeast, and another one a little further "+
      "south. You can hear the people conducting trades to "+
      "the east. The air is frigid and carries the scent of "+
      "woodsmoke.\n");

    /* inherited from path_s00 */
    add_here();
    add_town();
    add_trees();
    add_buildings();

    add_exit(CALATHIN_DIR + "roads/road_n01", "northeast", 0);
    add_exit(CALATHIN_DIR + "paths/path_s02", "south", 0);
    add_npc(CALATHIN_DIR +"npc/std_move_citizen", 1);  
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

    /* leap for a branch */
    if (parse_command(str, ({}), "[up] [for] [a] / [at] [the] "+
	"[overhanging] 'branch' / 'branches'", str))
    {    
	write("You "+ query_verb() +" up for a branch and manage to grasp "+
	  "hold of it but it slips from your hands.\n");
	say(QCTNAME(this_player()) + " "+ query_verb() +"s up for a  "+
	  "branch but fails to hold on to it.\n");	
	return 1;		
    }	

    write("You "+ query_verb() +" up into the air, making "+
      "deep imprints in the snow when you land.\n");
    say(QCTNAME(TP) +" "+ query_verb() +"s into the air and "+
      "leaves deep imprints in the snow.\n");
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

