/*
 * File Name        : pirate_shop.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : The pirates shop. They can collect
 *                    a free parrot here, each login.
 *                    Perhaps I'll make it so that they
 *                    can buy some pirate stuff here, like
 *                    hooks, eyepatches and stuff.
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <std.h>

#define GOT_PARROT        "_i_got_parrot"

inherit MITHAS_IN;

void
create_mithas_room()
{
    set_short("Underground storeroom");
    set_long("@@long_descr");

    add_exit("pirate_center_room","west",0,0);

    add_item(({"cages", "parrots"}),"The parrots have "+
               "been trapped here for quite some time, "+
               "if you are lucky you might be to collect "+
               "one.\n");
}

string
long_descr()
{ 
   return "You are standing in a huge underground cave, beneth "+
          "the isle of Mithas. The black rock walls "+
          "are drenched with water and the smell of the fresh "+
          "seawater and wet soil dominate this place. This "+
          "might be a good place to hide ourself or something. "+
          "This room must be some sort of storeroom, small cages "+
          "containing colorful parrots fill the floor and "+
          "ceiling of this room. A only exit out of here is "+
          "to the west.\n";
}

void
init()
{
    ADA("collect");
    ::init();
}

int
collect(string str)
{
    object obj;

    if (str == "parrot" || str == "a parrot")
      {
          if (this_player()->query_prop(GOT_PARROT))
          {
              write("You have already collected a parrot today. Why "+
                    "would you want another one?\n");
              return 1;
          }
          this_player()->add_prop(GOT_PARROT, 2);
          setuid();
          seteuid(getuid());
          obj = clone_object("/d/Ansalon/goodlund/nethosak/club/parrot");
          obj->move(this_player(),1);
          write("You carefully open one of the cages and skillfully catch a "+
                "small parrot.\n");
          say(QCTNAME(this_player()) + " opens one of the cages, and skillfully catches "+
              "a parrot.\n");
      }
    else
      write("Collect what? A parrot maybe?\n");
    return 1; /* always return 1 to prevent the team joining */
}

