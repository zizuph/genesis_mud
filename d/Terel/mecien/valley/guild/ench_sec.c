/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/d/Terel/mecien/valley/guild/mystic_sk_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(xx)        notify_fail(xx)
#define TO            this_object()
#define TP            this_player()
#define BS(xx)        break_string(xx, 70)
#define STAND_DIR     "/d/Terel/mecien/valley/guild/"
#define CLOSED        0      /* 1 = closed,   0 = open.  */

int closed;

/*
* Prototypes
*/
void set_up_skills();

void
create_room()
{ 
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   set_short("Enchantment Section");
   set_long("This section of the library is filled with very large and arcane\n"
     +"books and tomes. Many of the books look like they come from distant\n"
     +"lands, due to their unusual make. A layer of dust has settled over the\n"
     +"entire area, though the books are untouched by it.\n");
   
   
   add_exit(STAND_DIR+"arcane","out",0);
   
   create_skill_raise();
   set_up_skills();
}

string
wizinfo()
{
   return ("If there should be due cause to close down the guild, do so by\n" +
      "typing:  Call here close_guild\n" +
      "This will temporarily prevent mortals from entering. After a\n" +
      "reboot, the guild will be open by default. Please send me some\n" +
      "mail if there is anything that needs to be fixed.\n\n   /Mecien.\n"
   );
}

void
enter_inv(object ob, mixed from) 
{
   ::enter_inv(ob, from);
   
   if (!query_ip_number(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. " +
      "I'm doing some work on the guild.\n");
   else
      {
      write("The guild is closed. Come back later.\n");
      ob->move_living("M", STAND_DIR+"hall");
   }
}

void
init()
{
   ::init();
   init_skill_raise();
   add_action("read", "read");
}

string
close_guild()
{
   if (closed)
      {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() { return closed; }

int
read(string str){
   write("The tomes and books are ancient and contain lore of enchantments\n"
      +"and the use of such magic. To study them would bring great knowledge\n"
      +"and ability in such areas.\n");
   return 1;
} 

void
set_up_skills()
{
   string me, ot;
   
   me = "use enchantment spells"; ot = me;
   sk_add_train(SS_FORM_ENCHANTMENT, ({me, ot}), 0, 0, MYSTIC_MAX_ENCHANTMENT);
}
