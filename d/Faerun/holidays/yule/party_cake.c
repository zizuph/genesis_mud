/*
 * Birthday cake. Taken from the old party system and now 
 * is a standalone object. Eating cake has no food value.
 * -- Finwe, November 2001
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Shire/sys/defs.h"

#define UNCUT 1
#define CUT 0
#define CAKE_PIECE  "/d/Faerun/holidays/yule/cake_piece"
#define CAKE_NAME   "_party_cake"

string xtra_cake_desc = "\nThe cake hasn't been cut. You may <cut cake>.";
string cake_cutter = "";
int cake = UNCUT;


void create_object()
{
    set_name("cake");
    add_name(CAKE_NAME);
    set_adj("tall");
    set_adj("yule-time");
    set_short("tall yule-time cake");
    set_long("@@my_long_desc@@");

    add_prop(OBJ_I_WEIGHT, 10000000);
    add_prop(OBJ_I_VOLUME, 800000);
}

string
my_long_desc()
{
    return "This is a tall yule-time cake. It is in the shape of a tall evergreen and towers above you. Magical lights are draped along its branches and twinkle off and on. Sugar decorations in the shapes of colored balls, wreathes, elves, animals, and holly branches are scattered across the cake. " + xtra_cake_desc + "\n";

}

void init()
{
    ::init();
    add_action("do_cut", "cut");
    add_action("do_catch_get", "get");
    add_action("do_catch_get", "take");

}


int
do_catch_get(string str)
{
    seteuid(getuid(TO));

   if (str != "cake" && str != "piece of cake" && str != "a piece of cake")
      return 0;
   
   if (present("cake", this_object()))
      return 0;
   
   if (present("piece", this_object()))
      return 0;
   
   if (present("_cake_piece", this_player()))
      {
      write("You already have some.\n");
      return 1;
   }
   
   if (cake == UNCUT)
      {
      write("The cake isn't cut yet.\n");
      return 1;
      }
    else
    {
        write("You quickly get yourself a piece of cake.\n");
        clone_object(CAKE_PIECE)->move(this_player());
        xtra_cake_desc = "\n" + cake_cutter + " cut the cake earlier and people have started eating it. You may <get a piece of cake>."; 
        return 1;
    }
    return 1;
}

int
do_cut(string str)
{
   if (str != "cake")
      return 0;
   
   if (cake == CUT)
      {
      write("It is already cut.\n");
      return 1;
   }
   
   write("You cut up big slices of cake for everyone.\n");
   say(QCTNAME(this_player()) + " cuts up the party cake so everyone can get a piece.\n");
   cake = CUT;
   xtra_cake_desc = "\nThe cake was cut by " + this_player()->query_name()
   + ".";
    cake_cutter = this_player()->query_name();
   return 1;
}