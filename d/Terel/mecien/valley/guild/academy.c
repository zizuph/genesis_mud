/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str) notify_fail(str)
#define TO      this_object()
#define TP      this_player()
#define BS(xx)  break_string(xx, 72)
#define PATH    "/d/Terel/mecien/valley/guild/"
#define CLOSED  0      /* 1 = closed,   0 = open.  */

int closed;

/*
* Prototypes
*/
void set_up_skills();

int closed;
object obj;

reset_room(arg)
{
    if(!obj){
        obj=clone_object(PATH + "savant");
        obj->move(TO);
    }
}


create_room() { 
   
   closed = CLOSED; 
   
   set_short("Academy");
   set_long(
   "Arcane in its design, this gothic stone hall stands dark and\n"
 +"ominous, its ceiling vaulted and supported by dark golden wooden\n"
 +"arches. The chamber itself is ovular, the floor depressed, in the\n"
  +"center of which is an arena. A large desk, tall shelves, a table\n"
 +"and several cabinets fill the rest of the hall. Tall bronze candelabra\n"
 +"stand all about the hall, illuminating it with their dancing\n"
+"flames, providing a hypnotic feeling.\n"
);
   add_item("arches", "The support the vault, made of golden wood.\n");
   add_item("arena", "It is a small circular area in the center of\n" +
    "the hall where one might train in physical skills.\n");
   add_item("shelves", "They contain scrolls and tomes.\n");
   add_item(({"scrolls", "tomes"}), "They are ancient, usable only by\n"
   +"the wisest of savants.\n");
   add_item("cabinets", "They contain articles used for training.\n");
  add_item(({"writing desk", "desk"}), "It is a golden wood writing desk,\n"
   + "upon which are illuminated manuscripts, tins of paint and some\n"
   + "some brishes.\n");
  add_item("manuscripts", "They are pictures being worked on.\n");
   add_item(({"tins", "tin", "paint", "tins of paint"}),
   "Special paints used in making illunimated pages for manuscripts.\n");
   add_item("brushes", "Used for painting the manuscipts.\n");
   add_item("table", "It is a long stone table, old and cracked.\n");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   add_exit(PATH + "vesti", "east", 0);
   
   
   create_skill_raise();
   set_up_skills();

   reset_room();
}

wizinfo() {
   return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   /Styles.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   
   if (!query_ip_number(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move(PATH + "vesti");
   }
}


init() {
   ::init();
   init_skill_raise();
}

close_guild() {
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() { return closed; }

set_up_skills() {
   string me, ot;

   me = "use a sword"; ot = me;
   sk_add_train(SS_WEP_SWORD, ({me, ot}), 0,0, MYSTIC_MAX_SWORD);
   me = "use a knife"; ot = me;
   sk_add_train(SS_WEP_KNIFE, ({me, ot}), 0,0, MYSTIC_MAX_KNIFE);
   me = "appraise your opponents"; ot = "appraise opponents";
   sk_add_train(SS_APPR_MON,  ({me, ot}), 0,0, MYSTIC_MAX_APPR_MON);
   me = "appraise different objects"; ot = me;
   sk_add_train(SS_APPR_OBJ,  ({me, ot}), 0,0, MYSTIC_MAX_APPR_OBJ);
   me = "use your sense of location"; ot = "use the sense of location";
   sk_add_train(SS_LOC_SENSE, ({me, ot}), 0,0, MYSTIC_MAX_LOC_SENSE);
}

int
sk_improve(string sk)
{
   if(!MEMBER(TP)) {
      write("You are not a member of the Order.\n");
      return 1;
   }
   if (!present("allorhal", TO)) {
       write("There is no one here to teach you.\n");
       return 1;
   }
   
   return ::sk_improve(sk);
}
