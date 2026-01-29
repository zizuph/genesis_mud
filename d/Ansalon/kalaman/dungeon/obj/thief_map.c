/*
 * Thief Map 
 *
 * Funny Item (nothing special)
 *
 * Lunatari of Krynn
 * 2008-02-18: Created (based on the handkerchief.c)
 */
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

int gMap = 0;
string map_get_short();
string map_get_long();
string map_furl();
string map_unfurl();
mixed map_get_adjs();

void
create_object()
{
    set_name(({"map","_kalaman_thief_map_"}));

    set_adj(map_get_adjs);
    set_short(map_get_short);

    set_long(map_get_long);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);

    add_cmd_item("map", "furl", map_furl);
    add_cmd_item("map", "unfurl", map_unfurl);
}

string
map_get_long()
{
   string text;

   if(gMap)
   {
      text = "This is an old unfurled map. It seems to be a crude " +
        "drawing of the sewers of Kalaman.\n\n";
      text += "o-----------------------------------------------------o\n";
      text += "| The map starts with a small poem.                   |\n";
      text += "|                                                     |\n";
      text += "| ...                                                 |\n";
      text += "|                                                     |\n";
      text += "| For when the age comes close to the end, the memory |\n";
      text += "| fails, when body is weak and you can barely see.    |\n";
      text += "|                                                     |\n";
      text += "| Remember in your pain the only thing that matters,  |\n";
      text += "| the one that was forever, the well is the key.      |\n";
      text += "|                                                     |\n";
      text += "| If you cannot climb a slippery stone, too wet for   |\n";
      text += "| feet to stand on, then from above, use a rope.      |\n";
      text += "|                                                     |\n";
      text += "| Now at the waters edge, climb up again, for when    |\n";
      text += "| you through the bars crawl, there lies hope.        |\n";
      text += "|                                                     |\n";
      text += "| ...                                                 |\n";
      text += "|                                                     |\n";
      text += "| The map then shows a small well in what seems to    |\n";
      text += "| the location of the garden in Kalaman. The map is   |\n";
      text += "| also showing what seems to be a system of tunnels   |\n";
      text += "| underneath the city.                                |\n";
      text += "|                                                     |\n";
      text += "|                                                     |\n";
      text += "o-----------------------------------------------------o\n";
   }
   else
   {
      text = "This is an old furled map. Not much can be said " +
        "about the map until it is unfurled.";
   }

   return text + "\n";
}

mixed
map_get_adjs()
{
   if(gMap)
      return ({ "old", "unfurled" });
   
   return ({ "old", "furled" });
}

string
map_get_short()
{
   if(gMap)
      return "an old unfurled map";
   
   return "an old furled map";
}

string
map_furl()
{
    write("You carefully furl the map.\n");

/*    say(QCTNAME(TP) + " opens a " + query_short() + " and study the " +
      "content for a while and then closes it again.n");
*/
    gMap = 0;
    TO->update();
    return "";
}

string
map_unfurl()
{
    write("You carefully unfurl the map.\n");

    gMap = 1;
    TO->update();
    return "";
}
