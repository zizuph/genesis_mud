/*
 * base functions used by all rooms in the Archer Guild
 * in addition to Krynn standard room functions
 *
 * Vitwitch, Nov 2020
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/std/room";

string gViewFallDest;
string FORTNAME = "High Vantage";
string gBlurbPfx = "You stand in a fortress, hidden amongst the whispering treetops.";
string gBlurbSfx = "The ground below can be viewed through loopholes in the walls.";


public void
hook_smelled(string str)
{
    write("The scent of elder sap fills the air; a reminder of the wisdom of the forest.\n");
}

string
fort_description()
{
    string text = "All about you, mighty branches have been bound and "+
                  "brought together by silken strands of strength "+
                  "running between the ends of tufted shafts protruding "+
                  "from the living wood itself. Leaves of green and grey "+
                  "and silver are layered upon one another, and bonded "+
                  "hard by amber sap to clad this sprawling fortress in "+
                  "the dense foliage of the treetops.\n";
    return text;
}

string
fort_purpose()
{
    string text = "From the fortress of " + FORTNAME + ", among the "+
                  "whispering treetops, the "+
                  "Elven Archers of Ansalon watch over "+
                  "and protect the forest realm of Qualinesti.\n";
    return text;
}

string 
fort_vantage()
{
    string text = "The floor of the Qualinesti forest lies far below. "+
            "Your privileged vantage high up in the fort "+
            "allows you to <view> the ground unseen.\n";
    return text;
}


string
fort_foliage()
{
    string text = "Dense leafy foliage is all about, " +
               "concealing " + FORTNAME + " from all who walk below "+
               "or fly above. It difficult is to see far into the forest "+
               "at treetop level.\n";
    return text;
}

string
fort_stakes()
{
    string text = "Looking closely at "+
               "the short stakes growing at angles from trunks and branches, "+
               "they appear as nothing quite so much as the shafts of arrows "+
               "with stiff flower petals rather than feathers for fletching. "+
               "In place of a callus and wounded bark such as an embedded "+
               "arrow might cause in a tree, each stake is held in place "+
               "by a powerful swelling of living wood about it. Running "+
               "between the tips of the stakes, a network of silvery strands "+
               "weave all together, glimmering in the play of light through "+
               "treetops, shifting ever gently in the breeze.\n";
    return text;
}

string
fort_walls()
{
    string text = "The green and yellow walls "+
              "of the fortress consist of layer upon layer of leaves, laid down "+
              "over seasons, shielded and bonded in place by the golden sap of "+
              "the elder trees of Qualinesti, turned hard and charmed to "+
              "turn the elements of water, wind and fire from penetrating "+
              "within. Loopholes through the walls of the fort "+
              "provide the means to view the ground below.\n";
    return text;
}


/**
 * This function helps decide whether an archer can pass. 
 * It stops non-OCC guild members (and non-members).
 *
 * @return 0 if can enter, 1 otherwise.
 */
int
elite_check()
{

    if(this_player()->query_guild_name_occ() == "Ansalon Elvish Archers")
    {
        return 0;
    }

    write("Strong elven wards prevent you from going in that direction! " +
          "That room is only for occupational archers.\n");

    return 1;
}

int
view_down()
{
        /* This function returns an equivalent of 'look' from viewdest
         * most importantly without any supporting code from the
         * target room.
         */

        object *inv, *obs, *ppl, target;
        string desc;

        target = find_object(gViewFallDest);

        if (!objectp(target)) return 0;

        write(gViewFallDest->long());

        inv = all_inventory(target);
        obs = FILTER_SHOWN(FILTER_DEAD(inv));
        ppl = FILTER_LIVE(inv);

        if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
            write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");

        if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
            write(one_of_list(({"Down below you see ",
                                "You notice below ",
                                "Down below you spy "}))
                              + desc + ".\n");

        return 1;
}


int
not_good_archer(object ob)
{
    if ( ob->query_wiz_level() ) return 0;

    if(!(ob->query_guild_name_occ() == "Ansalon Elvish Archers") &&
       !(ob->query_guild_name_lay() == "Ansalon Elvish Archers"))
    {
        return 1;
    }
    else
    {
        if( ob->query_alignment() < -100 ) return 1; 
    }
    return 0;
}


void
fall_down(object ob)
{

    if (!ob || !present(ob, this_object()))
        return;

    if (interactive(ob))
    {
        tell_room(gViewFallDest, "There is a huge crashing sound!!" +
               " Something has fallen to earth from great height.\n");

        tell_object(ob,
          "...all of " + FORTNAME + " shivers about you in revulsion...\n" +
          "...your feet slip and slide, suddenly slick with fresh sap...\n" +
          "...you fall through an opening gap betwixt branch and leaf...\n"+
          "...to plummet headlong in the shadowed space between trunks...\n"+
           "...and impact the forest litter with a bone-breaking WHUMP!!\n\n");

        say( QCTNAME(this_player())+" is "+
              "cast out by the very living wood of " + FORTNAME + "!\n");

        /* injure the faller, no death */
        ob->heal_hp(-300);

        ob->move_living("M", gViewFallDest, 1, 0);

    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
    if ( not_good_archer(ob) )
        call_out("fall_down", 1, ob);
}

