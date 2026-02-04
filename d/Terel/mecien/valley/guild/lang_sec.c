/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)   notify_fail(str)
#define TO        this_object()
#define TP        this_player()
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
   
   set_short("Language Section");
   set_long("Tall dusty shelves adorned with ancient tomes, scrolls,\n" +
      "ledgers, books and papers. They appear to be written in\n" +
      "many different languages. A desk and a stool are also\n" +
      "here to assist study efforts.\n");
   
   add_exit(STAND_DIR+"library","out",0);
   
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
   else {
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
   write("The books seem to be all about languages. Their use\n"
      +"and understanding, making it possible to study them.\n");
   return 1;
} 

void
set_up_skills()
{
   string me, ot;
   
   me = "understand languages"; ot = me;
   sk_add_train(SS_LANGUAGE, ({me, ot}), 0, 0, MYSTIC_MAX_LANGUAGE);
}

int
sk_improve(string sk)
{
   if (!MEMBER(TP)) {
      write("You are not a member of the Order.\n");
      return 1;
   }
   return ::sk_improve(sk);
}
