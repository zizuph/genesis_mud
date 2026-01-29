#include "defs.h"

int web_here;

CONSTRUCT_ROOM
{
   set_short("Cavern");
   set_long(
      "You are in a cavern with a domed ceiling. There is an opening "+
      "in the west and smaller in the east and somewhat down. There "+
      "is also a third opening in the north through an arched opening. "+
      "@@web_text@@\n");
   add_item("opening", "Which opening? The north, east or west?");
   add_item(({"exit","exits"}), "Which exit? North, east or west?");
   add_item(({"west opening","west exit","west"}),
      "This is just a small opening leading to another room in the west.");
   add_item(({"north opening","arched opening", "arch", "north", "north exit"}),
      "The northern opening is arched and leads to another room.");
   add_item(({"small opening", "web", "east", "east exit", "east opening"}),
      "@@exa_east@@");
   add_item("ceiling",
      "The ceiling domes high above you. It is spherical, and ornamented "+
      "in several colours.");
   add_item(({"colours","ornaments","flames"}),
      "The colours are mostly in red, yellow and brown. It looks like flames "+
      "which crawl upwards. This makes you feel like standing in the middle "+
      "of a fire-place. Weird..");
   add_item(({"stench","air","predators"}),
      "The stench is awful here, and seems to come from the east.");
   NORTH("mjunc");
   WEST("widepas1");
   add_exit(THIS_DIR+"study","east","@@chk_east@@");
   
   web_here = 1;
}

RESET_ROOM
{
   web_here = 1;
}

int
chk_east()
{
   if (web_here)
      write("No, it is impossible to trespass the webs. They are far too thick.\n");
   return web_here;
}

string
web_text()
{
   if (web_here) return
      "The eastern exit is blocked by a thick web! It seems too "+
   "powerful to strike through, even with enchanted weapons. "+
   "There is a ghastly stench of predators from there, and the "+
   "dark passage leading inwards seems so frightening that you "+
   "shouldn't use too much of your time to investigate it further.";
   else return
      "The eastern exit leads into a frightening dark passage. A "+
   "ghastly stench of predators permeates the air, and you "+
   "shiver at the thought of entering that way.";
}

string
exa_east()
{
   if (web_here) return
      "The eastern exit is blocked by a thick web. You can't strike "+
   "through it because it seems mighty strong.";
   else return
      "The dark passage leads into the east, but a foul stench comes "+
   "from there. You shiver from the thought of what might be in there.";
}

init()
{
   ::init();
   add_action("no_cut","cut");
   add_action("no_cut","slash");
   add_action("do_burn","burn");
   add_action("do_burn","fire");
   add_action("do_burn","light");
}

int no_cut(string what)
{
   if (what=="web"&&web_here) {
      write("It is far too strong. You can't even budge it!\n");
      say(QCTNAME(TP)+" tries to "+query_verb()+" the web, but fails.\n");
      return 1;
   }
}

int do_burn(string what)
{
    int i;
    object *inv_list;

    inv_list = deep_inventory(TP);

    if (what!="web")
        return notify_fail(CAP(query_verb())+" what?\n");

    if(inv_list[i]->query_prop("_obj_i_light")  && function_exists("create_object",inv_list[i]) == "/std/torch")
    {
        web_here = 0;
        tell_room(TO, "Suddenly, the web flames up and in seconds the web disappears!!\n");
        return 1;
    }
    else
    {
        write("You don't have anything hot enough to burn the webs away.\n");
        return 1;
    }
}
