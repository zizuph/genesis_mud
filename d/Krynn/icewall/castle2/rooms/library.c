#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

#include <macros.h>
#include <stdproperties.h>
 
inherit ICEINROOM;

int    hidden_door_found = 0;  /* 0 = hidden door NOT found */
int    scroll_reset = 1;
object scroll;

public void
reset_icewall_room()
{
   scroll_reset = 1;
}

void
create_icewall_room()
{
    object gdoor;

    set_short("Renovated library");
    set_long("@@long_descr");

  add_item(({"window","narrow window"}),"Two an a half meters above " +
    "ground, this window is narrow enough to prevent anyone entering " +
    "from the castle's courtyard, but tall enough to invite enough " +
    "of the sunlight to brighten the room during the day.\n");
  add_item(({"rug","green-black rug","vivid green-black rug"}), "" +
    "The rug is thick and undamaged. Mostly black, it has been " +
    "decorated with a green motif of a large plant called chokevine " +
    "renowned for the way it strangles other, less aggressive " +
    "plants.\n");
  add_item(({"desk","massive desk"}),"Heavy and dark, the desk is " +
    "bare of paper or other writing materials. Four large drawers " +
    "attract your attention, however.\n");
  add_item(({"drawer","drawers","large drawer","large drawers"}),"" +
    "The drawers fit snuggly into the desk. It might be possible " +
    "to pull them out.\n");
  add_item("chair","The chair is made out of the same dark wood as " +
    "the desk, but is also covered with plush backing in all the " +
    "right places. It looks quite comfortable.\n");
  add_item(({"chandelier","chandeliers"}),"Two beautiful crystal " +
    "chandeliers have been hung high under the ceiling. Scores of " +
    "white candles have been set in them, but you see no easy " +
    "way to light them, unless there is a hidden ladder somewhere, " +
    "or the maid has learned the fabled skill of levitation...\n");
  add_item(({"pot","pots","plant","plants"}),"The two pots by the " +
    "east door contain strange plants. They looks like a small " +
    "conifer, and smell alike, but have no needles. Instead, " +
    "they sprout small, flat green leaves with a distinct white " +
    "sheen to them. They seem to be prospering in this arctic " +
    "climate quite well.\n");
  add_item(({"bookcase","bookcases"}),"The bookcases hold hundreds " +
    "of books, and completely cover three walls of the room. Without " +
    "a ladder it appears impossible to reach the highest shelves, " +
    "though one could always stand on the desk.\n");
  add_item("highest shelves","They are too high to be examined " +
    "from here.\n");
  add_item(({"books","book"}),"Hundreds of books fill this room. " +
    "As it is impossible for them to have weathered the Cataclysm " +
    "in such perfect condition, someone must have brought them just " +
    "recently. The books touch upon a variety of subjects, such " +
    "as history, geography, philosophy, as well as elven fiction " +
    "and poetry. Their owner must be a scholar... or very rich. " +
    "Most of the books are easily readable. You cannot spot a " +
    "speck of dust on them.\n");
  add_item(({"wall","walls"}),"Three walls are completely covered " +
    "by bookshelves. The fourth one, by the door you have just " +
    "entered, stands free, cold and smooth as only ancient stone " +
    "can be.\n");

   add_search("bookcase", 3, "find_door", 1);

   set_tell_time(900);

   add_tell("You hear some footsteps above you, on the second floor " +
    "of the lower building.\n");
 
     gdoor = clone_object(OBJK + "oakendoor2");
     gdoor->move(this_object());

    reset_room();

}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
    "You stand in the castle's library, or perhaps a workroom. " +
    "The room has been extensively redecorated, and looks " +
    "suprisingly new and well-cared for. The stone floor has " +
    "been covered with a vivid green-black rug. In the middle of " +
    "room, a massive desk has been placed complete with a " +
    "comfortable chair for long reading. On north, east, and south " +
    "walls, sturdy and well-crafted oaken bookcases cover the stone " +
    "from the floor all the way up to the ceiling. During the day, " +
    "illumination is provided by the narrow window located high " +
    "on the southern wall. During the night, the many-armed " +
    "candle chandeliers bask the library in soft, warm glow. On the " +
    "west wall, by the sturdy but plain door, two pots with strange, " +
    "white-green plants have been placed.\n");
}


int
pull(string str)
{   
    if(str == "out first drawer")
      {
        write("You pull out the first drawer, but find it " +
         "completely empty! You slide the drawer back inside the " +
         "desk.\n");        
        say(QCTNAME(TP) + " pulls out the first drawer, but with " +
         "a dissapointed look on his face slides it back in.\n");
        return 1;
      }

    if(str == "out second drawer")
      {
        write("You pull out the second drawer, but find it " +
         "completely empty! You slide the drawer back inside the " +
         "desk.\n");        
        say(QCTNAME(TP) + " pulls out the second drawer, but with " +
         "a dissapointed look on his face slides it back in.\n");
        return 1;
      }

    if(str == "out third drawer")
      {
        write("You pull out the third drawer, but find it " +
         "completely empty! You slide the drawer back inside the " +
         "desk.\n");        
        say(QCTNAME(TP) + " pulls out the third drawer, but with " +
         "a dissapointed look on his face slides it back in.\n");
        return 1;
      }

    if(str == "out fourth drawer")
      if(scroll_reset)
      {
        write("You pull out the fourth drawer and find a " +
         "crinkled parchment within! You take it and slide the drawer " +
         "back inside the desk.\n");        
        say(QCTNAME(TP) + " pulls out the fourth drawer and takes something " +
         "from within it before closing the drawer.\n");

        scroll = clone_object("/d/Krynn/common/scrolls/ice_strike_scroll");
        scroll->move(this_player());

        scroll_reset = 0;

        return 1;
       }
      else
      {
        write("You pull out the fourth drawer, but find it " +
         "completely empty! You slide the drawer back inside the " +
         "desk.\n");        
        say(QCTNAME(TP) + " pulls out the fourth drawer, but with " +
         "a dissapointed look on his face slides it back in.\n");
        return 1;
      }
    
    notify_fail("Pull out which drawer? There are four of them!\n");
    return 0;
}

int
sit(string str)
{
     if(str != "on chair")
        {
          notify_fail("Sit on what? The chair?\n");
          return 0;
        }

     write("Resting your bones, you plop down on the chair for a " +
      "while.\n");
     say(QCTNAME(TP) + " rests " + HIS(TP) + " bones, plopping down on the chair " +
      "for a while.\n");
     TP->add_fatigue(10);
     return 1;
} 

int
stand(string str)
{
      if(str != "on desk")
        {
          notify_fail("Stand on what?\n");
          return 0;
        }

      write("You stand on the desk, and carefully examine the " +
       "upper shelves. Suprisingly, they are full of dust, as if " +
       "noone touched or cleaned them in over a year. If that would " +
       "be true, why all the bother with the lower shelves?\n");
      say(QCTNAME(TP) + " stands on the desk, and carefully examines " +
       "the upper shelves. After a moment of consideration, " + HE(TP) +
       " appears mildly suprised, and steps down from the desk.\n");   

      TP->add_prop("_i_am_suspicious_of_the_icewall_library",1);
      return 1;       
}

int
read(string str)
{
        if(str != "a book")
          {
            notify_fail("Read what? A book?\n");
            return 0;
          }

        say(QCTNAME(TP) + " reaches for a random book and begins " +
         "to leaf through it.\n");
        write("You reach for a random book and leaf through it...\n\n" +
         "A short while later, none the wiser, you replace it on " +
         "the shelf.\n");
        return 1;
}

mixed
find_door(object searcher, string what)
{
   if (hidden_door_found)
      return 0;

   if ((searcher->query_prop("_i_am_suspicious_of_the_icewall_library")==1) && (searcher->query_skill(110) > 45))
   {
      add_exit("library_secret", "north", 0);
      say(QCTNAME(searcher) + " somehow discovers a hidden door! " +
       "The whole northern bookcase swings open to reveal a " +
       "passage north.\n");
      hidden_door_found = 1;
      return "Ah, of course! This library is just for show... and " +
       "here is the book that opens the secret passage.\n";
   }

   return 0;
}

void
init()
{
    ::init();

    add_action(read, "read");
    add_action(pull,"pull");
    add_action(sit,"sit");
    add_action(stand,"stand");
}
              