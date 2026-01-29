/* 
 * /d/Kalad/common/wild/pass/underdark/u37.c
 * Purpose    : There is a secret command here to go to between_planes.c
 * Located    : Underdark
 * Created By : Antharanos ??.??.??
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */ 

# pragma strict_types
# include "dark_dom.h"
inherit DARK_DOM;

object ob1;

void
create_dark_dom()
{
    set_short("Shadowgloom's Lair");
    set_long("This enormous oval chamber is the grand lair of the "+
      "greatly feared and respected Shadowgloom, the most powerful dragon "+
      "of the Dark Dominion. Within this massive cavern, the floor, walls "+
      "and ceiling have been worn smooth by the massive bulk of the ancient "+
      "deep dragon. Not a single rough spot mars the cavern's surface, so "+
      "smooth and reflective is the stone that you get the impression of "+
      "being suspended in utter darkness. A geyser filled with hot, steaming "+
      "water and from which yellow vapors emerges, lies near the eastern "+
      "side of this cavern. At the far end of the chamber is a massive pile "+
      "of gold and jewels, a king's ransom!\n");
    add_item(({"chamber","lair","cavern"}),"The enormous enclosed space that "+
	  "surrounds "+
      "you from all sides.\n");
    add_item(({"floor"}),"There is not one stalagmite or other such "+
      "debris cluttering the ground. It is just bare stone.\n");
    add_item(({"walls"}),"You vainly try to look at all the walls of the "+
      "chamber at once...and fail.\n");
    add_item(({"wall"}),"The reflective black stone of one of the chamber's "+
	  "sides looks to be a near-perfect mirror image of the chamber you are "+
      "standing in, including the walls, floor, ceiling, and pool.\n");
    add_item(({"mirror image","image"}),"It looks like a reflection of "+
      "the surrounding area.\n");
    add_item(({"pool"}),"There is no pool in this chamber!\n");
    add_item(({"ceiling"}),"Made of dark, unyielding stone, it looks "+
      "quite strong.\n");
    add_item(({"surface"}),"The surface of the rock in this cavern is "+
      "as smooth as silk.\n");
    add_item(({"stone"}),"The rock here is extremely dark, almost "+
      "unusually so.\n");
    add_item(({"geyser"}),"A small fountain of water that spouts a "+
      "yellowish vapor, in addition to water.\n");
    add_item(({"water"}),"It has been tainted yellow from the gas, it "+
      "doesn't look safe to drink.\n");
    add_item(({"yellow vapors","vapors","yellow vapor","vapor"}),
      "It looks like sulphuric gas...quite dangerous if inhaled.\n");
    add_item(({"pile of gold and jewels","pile","king's ransom"}),
      "The largest collection of treasure and loot you have ever laid "+
      "your eyes upon. It lies in a gleaming pile as high as a hill giant!\n");
    add_cmd_item("geyser","enter","@@enter");
    add_cmd_item("wall","push","@@push");
    add_cmd_item("ibtpotm","coalesce","@@coalesce");
    add_exit(DARK(u38), "east");
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
    if(!ob1)
        (ob1 = clone_object("/d/Kalad/common/wild/pass/npc/deep_dragon"))->
        move_living("xxx", this_object());
    /* Not macroing this npc since it's unique and only appears here. */
}

string
enter()
{
    write("You step into the scalding hot waters of the geyser...\n");
    write("You are burned!\n");
    this_player()->heal_hp(-100);
    set_dircmd("geyser");
    this_player()->move_living("into the geyser", DARK(u22));
    return "After a disorienting ride you find yourself in a different "+
	  "place.\n";
}

string
push()
{
    write("You push the wall gently...\n");
    write("You are violently pulled inside!\n");
    set_dircmd("wall");
    this_player()->move_living("into the wall", DARK(u37a));
    return "You were magically transferred to another room!\n";
}

string
coalesce()
{
    if (!this_player()->query_npc())
        return "What?\n";
    write("You enter the glowing portal between planes.\n");
    set_dircmd("ibtpotm");
    this_player()->move_living("into the glowing portal suddenly created "+
      "out of thin air", DARK(between_planes));
    return "You are no longer within the normal realms of the mortals!\n";
}