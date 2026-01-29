/* Xak Tsorath coded by Percy */

/**
 * Navarre March 20th 2009.
 * Made the scroll use clone_unique, to ensure we don't have too many floating around.
 * Also made the scroll be placed inside the scrollcase instead of next to it.
 * Also ensured the chest will be closed and locked upon reset of the room.
 *
 * Removed the anti-magic scroll, replaced it with a gloom spell - Arman May 2016
 *
 * Added OotS revelation - Arman May 2017
 */
#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit  XAKINROOM
inherit "/lib/unique";

object dragon, treasure, chest;
int puddle;


void
reset_xak_room()
{
    object scrollcase;
    object scroll;

    // We don't want to reset the room if a player is here.
    // Let us make sure he gets the quest items he faught hard for,
    // and not close and lock the chest after he opens it.
    if(sizeof(FILTER_PLAYERS(all_inventory(TO))) > 0)
    {
        return;
    }

    chest->remove_object();

    chest = clone_object(OBJ + "chest.c");
    chest->move(TO, 1);


    if ((!treasure || environment(treasure) != chest))
    {
        treasure = clone_object(KROBJECT + "disks_of_mish");
        treasure->move(chest,1);
    }

    // Replaced antimag_scroll with gloom scroll - Arman Kharas May 2016

    if(!objectp(scrollcase))
    {
        // We use the scroll case here as a dummy object, we just need something to
        // make us able to clone nothing if we don't get the unique. 0 doesn't work.

        scrollcase = clone_object(KROBJECT + "scroll_caseiv");
        scrollcase->move(chest, 1);

        if(random(2))
        {
           scroll = clone_object(KRSCROLL + "gloom_scroll");
           scroll->move(scrollcase, 1);
        }
        else
        {
           scroll = clone_object(KRSCROLL + "prot_acid_scroll");
           scroll->move(scrollcase, 1);
        }

    }

    if (!dragon)
    {
        dragon = clone_object(KRNPC + "khisanth.c");
        dragon->move(TO);
    }
}


void
create_xak_room() 
{
    set_short("The cavern");
    set_long("@@mylong");
    
    add_exit(DDIR + "cavernentry.c", "north", 0, 0);
    
    INSIDE;
    DARK;
    add_item(({"cavern", "wall", "walls"}), "@@cavern");
    add_item(({"puddle", "puddles", "puddle of acid", "acid", "puddle acid"}),
	     "@@puddle");

    reset_room();
}

string
mylong()
{
    string long;
    long = "This is an immense underground cavern"
      + " with strangely smooth walls....\n";
    if (puddle == 1)
    {
        long += "The ground contains several puddles of acid.";
    }
    return long + "\n";
}

void
spuddles()
{
    puddle = 1;
    set_alarm(160.0,0.0,"clpuddles");
}

void
clpuddles()
{
    tell_room(this_object(), "The acid in the puddles evaporates.\n");
    puddle = 0;
}

void
init()
{
    ::init();
    ADA("fill");
}

/*
int
go_north()
{
    object *ob;
    int leave, i;
    ob = FILTER_LIVE(all_inventory(this_object()));
    for (i = 0; i < sizeof(ob); i++)
      {
          if (ob[i]->query_name() == "Khisanth" && CAN_SEE(ob[i],TP))
            leave = 1;
      }

    if (leave == 1)
      {
          if (member_array(dragon, TP->query_enemy(-1)) >= 0)
            {
                write("Khisanth tries to block your exit but you manage to " +
                      "make a headlong leap over the dragons claw and into " +
                      "the tunnel beyond!\n");
                return 0;
            }
          write("You go to leave but the dragon simply places a huge"
                + " claw over the exit.\n");
          SAY(" tries to leave but can't as the dragon "
              + "puts a huge claw to block the exit.");
          dragon->command("say Foolish mortal, do you think you can escape " +
                          "me?");
          dragon->command("laugh");
      }

    return leave;
}
*/

string
cavern()
{
    write("This cavern is immense and has smooth walls and ground.\n");
    SAY(" examines the cavern.");
    return "";
}

string
puddle()
{
    if (puddle == 0)
      return "What?\n";
    write("All over the floor around the dragon's corpse are small"
	  + " puddles of acid.\n");
    SAY(" examines the puddles of acid.");
    return "";
}

int
fill(string str)
{
    int i, prp;
    object ob, ob2;
    string obstr, str1, obstr2;
    
    
    NF("Fill what with what?\n");
    if (puddle == 0)
      return 0;
    if (sscanf(str, "%s %s %s", obstr, str1, obstr2) != 3)
      return 0;
    if (str1 != "with")
      return 0;
    if (obstr2 != "acid")
      return 0;			
    if (obstr == "bottle" || obstr == "glass bottle")
    {
        if (ob2 = present("xak_bottle", TP))
        {
            ob2->remove_object();
            clone_object(OBJ + "bottlea.c")->move(TP);
            write("You fill a glass bottle up with acid from the puddles.\n");
            SAY(" fills a bottle with black acid.");
            prp = TP->query_prop("_player_i_black_dragon_quest");
            TP->add_prop("_player_i_black_dragon_quest",prp | 4);
            return 1;
        }
        if (ob2 = present("xaka_bottle", TP))
        {
            NF("The bottle is already full of acid.\n");
            return 0;
        }
        if (!FIND_STR_IN_OBJECT(obstr, TP))
        {
            NF("What bottle?\n");
            return 0;
        }
    }
    if (!FIND_STR_IN_OBJECT(obstr,TP))
      return 0;
    NF("You think the acid might be too strong to do that.\n");
    return 0;
}


/** MODIFIED Disks will now always clone to make the quest
*** repeatable.  Louie July 2005  ***
    if ((!treasure || environment(treasure) != chest) &&
	!QUERY_QUEST("black_dragon"))
    {
	treasure = clone_object(KROBJECT + "disks_of_mish");
	treasure->move(chest, 1);
    }
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
       if(IS_OOTS(ob))
       {
          if(!OOTS_QUERY_REV(TP, "disksofmishakal"))
          {
            TP->catch_msg("\n\nAs you enter the immense cavern you are suddenly " +
               "provided a divine revelation on recent and distant events relating " +
               "to the Holy Disks of Mishakal!\n\n\n");
            OOTS_ADD_REV(TP,"disksofmishakal","edification - the disks of mishakal");  
          }
       }
    }

}
