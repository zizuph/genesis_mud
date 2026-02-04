// path_s08.c
// This path runs southwest from the big Tree and then 
// west behind the townhouses toward the West Gate.
// Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
inherit CALATHIN_DIR + "paths/path_s00";

public void
create_terel_room()
{
    set_short("Western path near the wall");
    set_long("The West Gate is southwest of here, providing security "+
      "and peace of mind to the residents of Calathin. "+
      "This is a path running east-west through the forest behind a "+
      "row of townhouses. "+
      "There are a fair number of tree stumps south of here from a "+
      "recent clear-cut of the area. "+
      "Above the walls, a spectacular mountain range seems to pierce "+
      "the sky like the jagged teeth of a mythical beast. "+
      "The wind is so bitterly cold it makes your bones ache.\n");  


    /* inherited from path_s00 */
    add_here();
    add_town();
    add_trees();
    add_buildings();

    add_item(({"road","west road","west","west gate","gate","snowy road"}), 
      "The road is frozen hard and leads toward Calathin's West Gate.\n");

    add_exit(CALATHIN_DIR + "roads/road_w08", "south", 0);
    add_exit(CALATHIN_DIR + "paths/path_s07", "east", 0);	
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

