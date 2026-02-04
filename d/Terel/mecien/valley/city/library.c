/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define MEMBER lioving(xxx)

#define NF(str)       notify_fail(str)
#define TO            this_object()
#define TP            this_player()
#define BS(xx)        break_string(xx,68)
#define STAND_DIR     "/d/Terel/mecien/valley/guild/"
#define CLOSED        0      /* 1 = closed,   0 = open.  */
#define PATH "/d/Terel/mecien/valley/city/"

int closed;

/*
* Prototypes
*/
void set_up_skills();


void
create_room()
{ 
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
  set_short("Elnoven Library");
  set_long(
   "This small stone building is a library. It is not grand by any "
   + "means, but it is very old and its knowledge precious. There are " +
"only a few shelves of books here.\n");
   
   add_item("shelves", "They are old and made of wood.\n");
  add_item("books", "They are very old. Most of them contain rather specific knowledge.\n");
   add_exit(PATH + "street13", "south", 0);
   
   create_guild_support();
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
      ob->move(STAND_DIR+"hall");
   }
}

void
init()
{
   ::init();
   init_guild_support();
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
  write("The books are old and mostly unused. They contain knowledge of languages " +
"and speech. Many of the older tomes contain lore on enchantments and studying them "
+"might help.\n");
   return 1;
} 

void
set_up_skills()
{
   string me, ot;
  string what;

   me = "use magical spells"; ot = me;
   sk_add_train(SS_SPELLCRAFT, ({me, ot}), 0, 0, 20);
  what = "ability of language and enchanted speech";
   sk_add_train(SS_LANGUAGE, ({what, what}), 0, 0, 50);
}

void
gs_hook_start_meditate()
{
   write("Slowly you sit down in the quiet alcove and close your eyes.\n" +
      "A feeling of great ease and self control falls upon you.\n" +
      "You block off your senses and concentrate solely upon your\n" +
      "own mind. You find yourself able to <estimate> your different\n" +
      "preferences and <set> them at your own desire.\n" +
      "Just <rise> when you are done meditating.\n");
}

void
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness. You exhale and feel very relaxed as\n" +
      "you get up and leave the alcove.\n");
}
