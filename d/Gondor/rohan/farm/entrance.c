/* 
 *	/d/Gondor/olorin/farm/entrance.c
 *	It belongs to a small farm in the Ered Nimrais
 *
 *	Coded by Olorin, Nov 1992
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *  Jan 2020, Finwe: Made it easier to find the path
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
 
/* How easy is it to find the hidden tracks? */
#define TRACKINGSKILL 30 
/* How easy is it to find the hidden exit? */
#define AWARENESSKILL 30 
/* A good chance to survive the experience */
#define SURVIVAL_DIS  70 
/* You might survive, if your wimpy is high! */
#define MINIMUM_DIS   30 
 
#define BUSH_PROP "_have_found_the_path"

// public int     tracking(string str);

static int     Found_Track = 0; // found the tracks?
 
public void
create_area_room()
{
    set_areadesc("field");
    set_areatype(2);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_extraline("There is a path going north, but apparently it ends here "
      + "since there are bushes in all other directions which make it " 
      + "impossible to go any further.");
    add_exit(FARM_DIR + "road/road1", "north", 0, 1);
//    add_item("bushes",BS("They are impenetrable and thorny. Without "
//      + "closer inspection you cannot see anything special about them.\n"));
    add_item("thorns",BS("They are very long and sharp, almost like "
      + "weapons. It would be downright dangerous to try to walk through "
      + "the bushes.\n"));
    add_item("ground",BS("It's stony with a few patches of grass. With "
      + "a bit care an army might walk here and never leave a single "
      + "track.\n"));
    add_item("path",BS("It seems to end in front of the bushes to the south. "
      + "You wonder why it does that, but without a closer inspection "
      + "you have no clue.\n"));
    add_item(({"grass", "patches", "patches of grass"}) ,BS("There are only "
      + "some patches of grass on this "
      + "stony ground. There is nothing special about them.\n"));

    set_up_herbs( ({ HERB_DIR + "clove", HERB_DIR + "sage", }),
                  ({"bushes","grass","forest","path","here"}), 2);
    add_item(({"bush","bushes"}),"@@exa_bush");
}

void
reset_room()
{
    Found_Track = 0;
    remove_exit("south");
    remove_item("tracks");

    ::reset_room();
}
 
public void
init()
{
    ::init();
//    add_action(tracking, "search");
//    add_action(tracking, "examine");
//    add_action(tracking, "exa");

    add_action("enter_bushes", "enter");


}
/* 
public int 
tracking(string str)
{ 
    int     his_track = TP->query_skill(SS_TRACKING),
            his_aware = TP->query_skill(SS_AWARENESS),
            i;
    mixed  *exits;
    string  open_text = " suddenly realizes that the path leading "
                      + "south through the bushes was cleverly hidden "
                      + "with branches cut from other bushes. To clear "
                      + "the way "+ TP->query_pronoun() + " tears the "
                      + "branches away and throws them into the thicket.\n";
 
    if (!strlen(str))
        return 0;

    switch (str)
    {
    case "ground":
    case "grass":
    case "path":
    case "stone":
    case "stones":
        if (his_track > random(TRACKINGSKILL))
        {
            write(BSN("Only a very experienced tracker can make out some "
              + "tracks on the ground which have been hidden with great "
              + "care. They disappear between the bushes to the south. "
              + "Perhaps you should have a closer look at these bushes."));
            Found_Track = 1;
            add_item("tracks",BSN("They disappear between the bushes to the "
              + "south. You wonder how they can disappear there since it "
              + "is obvious that no one could walk through these bushes."));
            return 1;
        }
        write(BSN("There is not much to see on the ground. It is stony "
          + "with a few patches of grass. If a dozen men had walked here, "
          + "you would not be able to see a track."));
        return 1;
        break;
    case "bushes":
        if (member_array("south", TO->query_exit()) > -1)
        {
            write(BSN("The bushes look alike in all directions. You cannot "
              + "make out anything. Only to the north and south are there "
              + "openings, with the path running through."));
            return 1;
        }
        if (Found_Track && his_aware > random(AWARENESSKILL))
        {
            write(BSN("Suddenly you realize that the path leading south "
              + "through the bushes was cleverly hidden with branches cut "
              + "from other bushes. You tear the branches away and throw "
              + "them into the thicket."));
            add_exit(FARM_DIR + "farm/path1", "south", "@@con_pass");
            say(QCTNAME(TP) + open_text);
            return 1;
        }
        write(BSN("The bushes look alike in all directions. Since you "
          + "do not have a clue where to look, you cannot make out "
          + "anything. Perhaps you should look for hints on the ground, "
          + "a broken grass blade, a stone that has been moved can tell "
          + "a lot to the experienced tracker. Only to the north is there "
          + "an opening, with the path running through it."));
        return 1;
        break;
    }
    return 0;
}
*/

/* 
public int
con_pass()
{
    int his_con;
    string move_text;
 
    his_con = this_player()->query_stat(SS_DIS);
 
    if ( his_con > SURVIVAL_DIS )
    {
        write(BS("Suddenly you hesitate, you realize that there is only "
     +    "death and destruction to the south. But then you continue, "
     +    "possibly going to meet Death again.\n"));
        return 0;
    }
    if ( his_con > random(MINIMUM_DIS) + random(SURVIVAL_DIS - MINIMUM_DIS) )
    {
        write(BS("Suddenly you realize that you will be dead soon, if "
     +    "you continue to go south. Something inside your head tells "
     +    "you that there is nothing to find south of here but corpses. "
     +    "Soon your own corpse will lie there, too.\n"));
        return 0;
    }
    write(BS("You hesitate. Suddenly you know that a single step "
        + "further on this path will be suicide. Therefore you decide "
        + "not to continue south, but to explore some other area.\n"));
 
    move_text = " goes some steps south, but suddenly " + 
	TP->query_pronoun() + " is trembling for fear and does not go any further.\n";
 
    say(({ BS(METNAME + move_text),
      BS(ART_NONMETNAME + move_text),
      BS(UNSEEN_NAME + move_text) }));
 
    return 1;
}
*/

string
exa_bush()
{
    if(TP->query_skill(SS_AWARENESS)>15)
    {   
       TP->add_prop(BUSH_PROP,1);
       write("As you examine the bushes, you discover a path leading south into them.\n");
        add_exit(FARM_DIR + "farm/path1", "south");
    return "";
    }
    else
       write("The bushes seems to be dense right here, as if they were hiding something.\n");
       return "";
}

int
enter_bushes(string str)
{
    if(str=="hidden bushes" ||
       str=="trail" || 
       str=="bushes")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You follow a trail into the bushes.\n");
            say(QCTNAME(TP)+" vanishes into the busshes.\n");
            tell_room("/d/Gondor/rohan/farm/farm/path1",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", "/d/Gondor/rohan/farm/farm/path1",1);
	   
            return 1;
        }
        else
        write("You do not see any " + str + " to enter here.\n");
        return 0;
    }
    notify_fail("Enter what?\n");
    return 0;
}
