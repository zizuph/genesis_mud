inherit "/std/object";

#include "default.h"

#define MIN_AWARENESS_NEEDED 40
#define MIN_AWARENESS_FOR_CLUE 25

int torn;
int pulled;

void
create_object()
{
   set_short("leather bound book");
   set_name("book");
   add_name("cover");
   set_adj("leather");
   add_adj("bound");
   set_long("@@book_desc@@");
   
   add_prop(OBJ_I_VOLUME, 330);
   add_prop(OBJ_I_WEIGHT, 900);
   add_prop(OBJ_I_VALUE, 320);
   add_prop(OBJ_M_NO_BUY, 1);
   
   add_prop(OBJ_S_SEARCH_FUN, "search_cover");
   add_prop(OBJ_I_SEARCH_TIME, 5);
   
   pulled = 0;
}

string
search_cover(object player, string str)
{
   int awareness;
   
   if (str != "book" && str != "cover")
      {
      return 0;
   }
   
   awareness = player->query_skill(SS_AWARENESS);
   awareness += random(awareness + 1);
   
   if (awareness >= MIN_AWARENESS_NEEDED)
      {
      return (break_string("When you search the cover of the leather " +
            "bound book, you discover a dog-eared corner. Pulling the "+
            "corner slightly, you see an ornate and caligraphised "+
            "paper.", 78) + "\n");
      remove_item("corner");
      add_item("corner","The corner portrudes from the cover.\n");
   }
   
   if (awareness >= MIN_AWARENESS_FOR_CLUE)
      {
      return (break_string("Searching the cover of the leather bound " +
            "book didn't reveal anything to you. You sense however that " +
            "there is something wrong with the inside of the cover.", 78) +
         "\n");
   }
   
   if(pulled)
      {
      return break_string("You search the book but find nothing.\n", 76);
   }
   
   return (break_string("Searching the cover of the leather bound book " +
         "doesn't reaveal anything to you.", 78) + "\n");
}

void
init()
{
   ::init();
   add_action("do_pull","pull");
}

int
do_pull(string str)
{
   object ob, sheets;
   
   if(!parse_command(str, this_object(),
            "'corner' 'from' %o", ob))
   {
      write("Pull what from what?\n");
      return 1;
   }
   
   if(pulled)
      {
      notify_fail("There is nothing there to pull.\n");
      return 0;
   }
   
   if(member_array("cover", ob->query_names()) >= 0)
      {
      setuid();
      seteuid(getuid());
      sheets = clone_object("/d/Emerald/room/keep/part2");
      write("You pull the sheets from the cover.\n");
      say(QCTNAME(this_player())+" pulls something from the "+
         "cover of the book.\n");
      sheets->move(this_player());
      pulled = 1;
      return 1;
   }
   notify_fail("Pull sheets from what?\n");
   return 0;
}

string
book_desc()
{
   string re_st;
   
   if(pulled)
      re_st = "";
   else
      re_st = " A corner of some sheets peek from the cover.";
   
   return break_string("This book is leather bound, with large symbols "+
      "on the cover, which are undecipherable." + re_st + "\n", 76);
}

