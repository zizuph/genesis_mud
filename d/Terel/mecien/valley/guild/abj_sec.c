/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/d/Terel/mecien/valley/guild/mystic_sk_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)     notify_fail(str)
#define TO          this_object()
#define TP          this_player()
#define CLOSED      0      /* 1 = closed,   0 = open.  */

int closed = CLOSED;

/*
* Prototypes
*/
public void set_up_skills();

public void
create_room()
{
   set_short("Abjuration Section");
   set_long("Ancient shelves, line this area, filled with " +
            "thousands of old books and tomes of magical lore. " +
            "A dim light emanates from a small gold lamp that " +
            "is placed upon a desk. The air is warm and dry, a " +
            "silence and stillness abide here as if this place " +
            "were under protection.\n");

   add_item("lamp", "It is a small gold lamp, it burns with a dim " +
                    "light, perhaps fueled by oil.\n");
   add_item("shelves", "They are ancient and hold thousands of books.\n");
   add_item(({"books", "tomes"}), "There are thousands, they seem to " +
                                  "command and detail magic lore.\n");
   add_item("desk", "It is a simple desk for studying.\n");
   
   add_exit(GUILD_DIR + "arcane", "out", 0);

   add_prop(OBJ_S_WIZINFO, "@@wizinfo");

   create_guild_support();
   create_skill_raise();
   set_up_skills();
}

public string
wizinfo()
{
   return "If there should be due cause to close down the guild, do so by " +
      "typing:\n   Call here close_guild\n" +
      "This will temporarily prevent mortals from entering. After a " +
      "reboot, the guild will be open by default. Please send me some " +
      "mail if there is anything that needs to be fixed.\n\n   /Mecien.\n";
}

public void
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
      ob->move_living("M", GUILD_DIR + "arcane");
   }
}

public int
do_read(string str)
{
   write("The tomes and books are ancient and contain lore of enchantments " +
         "and the use of such magic. To study them would bring great knowledge " +
         "and ability in such areas.\n");
   return 1;
}

public void
init()
{
   ::init();
   init_guild_support();
   init_skill_raise();
   add_action(do_read, "read");
}

public string
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

public int query_closed() { return closed; }

public void
set_up_skills()
{
   string me, ot;

   me = "use abjuration spells"; ot = me;
   sk_add_train(SS_FORM_ABJURATION, ({me, ot}), 0, 0, MYSTIC_MAX_ABJURATION);
}

public int
gs_meditate(string str)
{
   if (!MEMBER(TP)) {
      write("You are not a member of this guild.\n");
      return 1;
   }
   return ::gs_meditate(str);
}

public void
gs_hook_start_meditate()
{
   write("Slowly you sit down in the quiet alcove and close your eyes. " +
      "A feeling of great ease and self control falls upon you. " +
      "You block off your senses and concentrate solely upon your " +
      "own mind. You find yourself able to <estimate> your different " +
      "preferences and <set> them at your own desire. " +
      "Just <rise> when you are done meditating.\n");
}

public void
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface " +
         "of your consciousness. You exhale and feel very relaxed as " +
         "you get up and leave the alcove.\n");
}
