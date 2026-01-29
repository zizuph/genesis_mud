/* -*- Mode: C -*-
 *
 * garden.c
 *
 * By Skippern 20(c)01
 *
 * This file is to be inherited in any garden. It will contain some
 * functions that adds flowers and trees items in gardens. With 
 * introducing of standard wood code in Genesis this code will be
 * added in order to better determine the height and descriptions if
 * the trees.
 */
inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <language.h>

#define WINTER 1
#define SPRING 2
#define SUMMER 3
#define AUTUMN 4

/*
 * Function name:    season_change_tree
 * Description  :    Make descriptions that change by the seasons.
 *                   For reasons of simplicity we only have 4 seasons.
 * Arguments    :    tree - name of tree type
 * Returns      :    string desc of item
 */
string
season_change_tree(string tree)
{
    object     clock = find_object(CLOCK);
    string     r;
    int        month = clock->query_month(),
               season;
    if (!stringp(tree)) return "ERROR: tree not string!\n";
    /* Since we only are interested in what season it is then we devide 
     * the year into seasons and save them. */
    if (month == 1 || month == 2 || month == 12) season = WINTER;
    if (month == 3 || month == 4 || month == 5) season = SPRING;
    if (month == 6 || month == 7 || month == 8) season = SUMMER;
    if (month == 9 || month == 10 || month == 11) season = AUTUMN;

    r = "";

    switch(tree)
    {
    case "alder":
        if (season == WINTER)
	    r += "The "+tree+" looks naked with no leafs on its long thin " +
	        "branches.";
        else if (season == SPRING)
            r += "The "+tree+" have a light green mist over it as new " +
                "leaves burst out.";
        else if (season == SUMMER)
	    r += "The "+tree+" is full of small circular green leaves. " +
	        "When the wind catches the leaves they make a rattling " +
	        "sound.";
        else if (season == AUTUMN)
            r += "The "+tree+" have leaves in differnt shades of yellow " +
	        "making it look dressed for thanksgiving. When the wind " +
	        "catches the leaves they make a rattling sound.";
	break;
    case "ash":
        if (season == WINTER)
            r += "The "+tree+" looks naked as it stands tall and twisted " +
	        "branches. You clarely see the rough and ash gray bark " +
	        "covering its stem.";
        else if (season == SPRING)
            r += "The "+tree+" stands tall with its twisted branches. " +
	        "Green leaves starts to burst out filling its light crown " +
	        "with enough shade for some birds to build nests.";
        else if (season == SUMMER)
            r += "The "+tree+" stands tall with its twisted branches. " + 
	        "The large but light crown gives some shade in the hot " +
	        "weather without hiding the sun.";
        else if (season == AUTUMN)
            r += "The "+tree+" with its tall and twisted branshes is a sad " +
	        "sight this time of the year. The leaves are drying out " +
	        "while they'r hanging on the tree. From time to time " +
	        "leaves falls from the tree.";
        break;
    case "aspen":
        if (season == WINTER)
            r += "The "+tree+" are tall and slender trees with thin trunks " +
	        "with white bark. On the naked branches you can see some " +
	        "\"catkins\", shapes looking almost like small caterpilars " +
	        "hanging down from the branches. When you touch these " +
	        "\"catkins\" a cloud of pollen spreads out.";
        else if (season == SPRING)
            r += "The "+tree+" are tall and slender trees with thin trunks " +
	        "with white bark. The trees have a light green mist over " +
	        "them as leave are appearing.";
        else if (season == SUMMER)
            r += "The "+tree+" are tall and slender trees with thin trunks " +
	        "with white bark. The branches is full of small, round " +
	        "green leave.";
        else if (season == AUTUMN)
            r += "The "+tree+" are tall and slender trees with thin trunks " +
	        "with white bark. The small, round leave have turned bright " +
	        "yellow, almost golden.";
        break;
    case "birch":
        if (season == WINTER)
            r += "The "+tree+" looks naked with no leafs on its branches. " +
	        "The stem is white with black spots where it is rifts or " +
	        "holes in the bark.";
        else if (season == SPRING)
            r += "The "+tree+" have a light green mist over it as new " +
                "leaves burst out. Under the green mist you notice " +
	        "the stem is white with black spots where it is rifts or " +
	        "holes in the bark.";
        else if (season == SUMMER)
            r += "The "+tree+" have a tight crown of small green leaves. " +
	        "Under the think crown you see a white stem with black " +
	        "spots where it is rifts or holes in the bark.";
        else if (season == AUTUMN)
            r += "The thick crown of the "+tree+" is colored in a symphony " +
	        "of red and yellow, and all the shades in between aswell. " +
	        "The color of the small leaves have changed from green, " +
	        "and is slowly falling down to the ground.";
	if (month == 5)
	    r += " A cloud of yellowish dust comes from the birch as you " +
	        "touches its branches.";
        break;
    case "elm":
        if (season == WINTER)
            r += "The "+tree+" is a sturdy tree with a wide crown that " +
	      "branch out high up on the stem. The branches are naked in " +
	      "the cold winter.";
        else if (season == SPRING)
            r += "The "+tree+" is a sturdy tree with a wide crown that " +
	      "branch out high up on the stem. Small silvery or white " +
	      "leaves are seen as you look up on the branches high above " +
	      "your head.";
        else if (season == SUMMER)
            r += "The "+tree+" is a sturdy tree with a wide crown that " +
	      "branch out high up on the stem. The crown is thick with " +
	      "silvery or white leaves as you look up on it. From a " +
	      "distance it looks more greenish.";
        else if (season == AUTUMN)
            r += "The "+tree+" is a sturdy tree with a wide crown that " +
	      "branch out high up on the stem. The crown is thick with " +
	      "silvery leaves in shades of yellow and red.";
        break;
    case "hawthorn":
        r += "This evergreen tree have a large irregular crown with " +
	  "thorny leaves and thorny branches. The bark is dark green " +
	  "with a grayish hue.";
	if (season == SPRING || season == SUMMER)
	    r += " Small white flowers shine up the tree.";
      break;
    case "hazel":
        if (season == WINTER)
            r += "The "+tree+" looks naked with no leafs on its branches.";
        else if (season == SPRING)
            r += "The "+tree+" have a light green mist over it as new " +
                "leaves burst out.";
        else if (season == SUMMER)
            r += "The "+tree+" is full of large dark green leaves.";
        else if (season == AUTUMN)
            r += "The "+tree+" have leaves in all coulors making it look " +
                "dressed for thanksgiving.";
        break;
    case "holly":
        r += "This is an evergreen tree with hard prickly leaves.";
	if (season == WINTER)
	    r += " Small red berries is seen on every branche.";
	break;
    case "larch":
        if (season == WINTER)
            r += "The "+tree+" looks naked with its tall naked trunk. " +
	        "The bark is dark and rough.";
        else if (season == SPRING || season == SUMMER)
            r += "The "+tree+" stands tall with dark green needles covering " +
	        "the branches.";
        else if (season == AUTUMN)
            r += "The "+tree+" looks shabby with lots of yellow and brown " +
	        "needles. Needles fall off the branches when you touch " +
	        "them.";
	if (month == 8 || month == 9)
	    r += " Small cones are seen on the branches.";
	if (month == 10) r += " Small cones covers the ground under the tree.";
        break;
    case "maple":
        if (season == WINTER)
            r += "The long and thin twisted branches spreading out " +
	        "from the thick stems makes it look scary. Scars in the " +
	        "bark makes they look very old, they certainly are.";
        else if (season == SPRING)
            r += "Light green leaves is filling the large crown of the " +
	        "maple trees here. Scares in the bark makes they look very " +
	        "old, they certainly are.";
        else if (season == SUMMER)
            r += "Large five pointed dark green leaves make a tight cover " +
	        "in the large crown. Scares in the bark makes the maples " +
	        "look very old, they certainly are.";
        else if (season == AUTUMN)
            r += "The large five pointed leaves of the maples have torned " +
	        "darkish red, and are slowly falling from the trees. Scares " +
	        "in the bark makes them look very old, they certainly are.";
        break;
    case "oak":
        if (season == WINTER)
            r += "The "+tree+" looks naked with no leafs on its branches.";
        else if (season == SPRING)
            r += "The "+tree+" have a light green mist over it as new " +
                "leaves burst out.";
        else if (season == SUMMER)
            r += "The "+tree+" is full of large dark green leaves.";
        else if (season == AUTUMN)
            r += "The "+tree+" have leaves in all coulors making it look " +
                "dressed for thanksgiving.";
        break;
    default:
        if (season == WINTER)
  	    r += "The "+tree+" looks naked with no leafs on its branches.";
	else if (season == SPRING)
	    r += "The "+tree+" have a light green mist over it as new " +
	        "leaves burst out.";
	else if (season == SUMMER)
	    r += "The "+tree+" is full of large dark green leaves.";
	else if (season == AUTUMN)
	    r += "The "+tree+" have leaves in all coulors making it look " +
	        "dressed for thanksgiving.";
    }
    return r+"\n";
}

/*
 * Function name:    add_the_tree
 * Description  :    Makes the item determined bo tree type
 * Arguments    :    tree - name of tree type
 * Returns      :    void
 */
void
add_the_tree(string tree)
{
    string ptree, *atree;

    ptree = LANG_PWORD(tree);

    atree = ({ tree, ptree, tree+" trees", tree+" tree" });

    switch(tree)
    {
    case "cypress":
        add_item( atree, "This is a large evergreen " +
		  "tree with dark green scalish leaves on a tight " +
		  "cone shapen crown. It is almost impossible to " +
		  "see the steam through the tight crown of leaves.\n");
	break;
    case "fir":
        add_item( atree, "This is a large evergreen tree, " +
                  "tall with few branches in reachable hight, and a tighter " +
                  "crown futher up. On the end of each branche is a small " +
                  "fountain of long stiff nidles. The bark is brownish " +
                  "fading towards red.\n");
	break;
    case "hemlock":
        add_item( atree, "This is a large evergreen tree " +
		  "with long hair like green leaves, the crown is " +
		  "irregular conish.\n");
        break;
    case "pine":
        add_item( atree, "This is a large evergreen tree, " +
		  "tall and full of branches. The branches are covered " +
		  "with small green nidles, and the bark is light brown, " +
		  "almost grayisn in some spots.\n");
        break;
    case "spruce":
        add_item( atree, "This is a large evergreen tree, " +
		  "tall with few branches in reachable hight, and a tighter " +
		  "crown futher up. On the end of each branche is a small " +
		  "fountain of long stiff nidles. The bark is brownish " +
		  "fading towards red.\n");
        break;
    default:
        add_item( atree, &season_change_tree(tree));
	break;
    }
    return;
}

/*
 * Function name:    add_tree
 * Description  :    adds tree description to the room.
 * Arguments    :    tree - string or array of strings to identify the
 *                          trees that should be added.
 * Returns      :    void
 */
public void
add_tree(string *trees)
{
    int       num, i;
    string    tree;

    num = sizeof(trees);
    if (num == 0)
    {
        tree = trees[0];
        add_the_tree(tree);
    }
    else
    {
        for (i = 0; i < num; i++)
	{
	    tree = trees[i];
	    add_the_tree(tree);
	}
    }
    return;
}
