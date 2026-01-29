/* 
 * /d/Kalad/common/guilds/thanar/ap_thanar.c
 * Purpose    : The object file of the Thanar ghost.
 * Located    : <called into being by the player>
 * Created By : Sarr 
 * Modified By: Rico 26.Mar.97; clean up, descrip improves.. added items 
 */ 

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include <thanardefs.h>

#define THANAR_TALK   "_thanar_talk"

object owner;
object con;
string query_owner();

void   set_owner(string str);

void
set_owner(object ob)
{
   owner = ob;

   con =  clone_object(THANAR(/ap_con));
   con -> set_thanar(this_object());
   con -> move(ob);
}

void
remove_con()
{
   con -> remove_object();
}

object
query_owner()
{
   return owner;
}

void
create_object()
{
   set_name("thanar");
   add_name(({ "warrior", "ghost", "apparition" }));
   set_adj("ghostly");
   add_adj("apparition");
   set_short("ghostly apparition of Thanar");
   set_long("\nYou see a giant warrior, approximately two and a "+
      "half meters in height. He is covered from head to toe in "+
      "midnight-black armour. A flowing robe of black surrounds "+
      "him. A platinum chain necklace embossed with the emblem of "+
      "Thanar dangles around his neck. The warrior's entire body "+
      "is transparant and ghost-like. From the darkness of his black"+
      " steel visored helm his eyes glow with a burning intensity.\n\n");

   add_item(({ "armour", "midnight black armour", "midnight-black armour",
      "black armour", "black robe", "robe", "flowing robe" }),
      "\nThe warrior's armours are of such a black as to make them "+
      "appear almost invisible in gloomy lighting. The armours help "+
      "to make this apparition seem sureal.\n\n");
   add_item(({ "necklace", "embossed necklace", "platinum necklace", 
      "chain necklace", "platinum chain necklace", "emblem",
      "emblem of thanar", "emblem thanar" }),
      "\nThe necklace is exquisite. It obviously belongs to someone of "+
      "high stature within the Thanars... probably to Thanar himself!\n\n");

   add_prop(OBJ_M_NO_GET, "\nAre you mad?\n\n");
}

