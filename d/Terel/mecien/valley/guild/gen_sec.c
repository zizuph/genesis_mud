/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/d/Terel/mecien/valley/guild/mystic_sk_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)   notify_fail(str)
#define TO        this_object()
#define TP        this_player()
#define BS(xxx)   break_string(xxx,70)
#define STAND_DIR "/d/Terel/mecien/valley/guild/"
#define CLOSED    0      /* 1 = closed,   0 = open.  */

int closed;

/*
* Prototypes
*/
void set_up_skills();

void
create_room()
{ 
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   set_short("General Magic Section");
   set_long("This large section of the library is very dusty. The tall\n" +
      "racks coated in a fine layer of dust, the tomes look as though they\n" +
      "may have been sitting undisturbed for ages. A small bench and a\n" +
      "table sit in the middle of this section.\n");
   
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
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() { return closed; }

int
read(string str){
   write("The tomes and books concern the process and study of the arts\n"
      +"of spellcraft. Their deep knowledge is astounding.\n");
   return 1;
} 

void
set_up_skills()
{
   string me, ot;
   
   me = "use spellcraft" ; ot = me;
   sk_add_train(SS_SPELLCRAFT, ({me, ot}), 0, 0, MYSTIC_MAX_SPELLCRAFT);
}
