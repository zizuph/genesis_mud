/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()

public string
query_auto_load()
{
    return MASTER;
}

public int
do_pray(string str)
{
   if (str) return 0;

   write("You mumble a short prayer, clutching the beads closely.\n");
   say(QCTNAME(TP) +
       " mumbles a prayer, holding some old stone beads closely.\n");
   return 1;
}

public int
do_rub(string str)
{
   object shadow;

   if (!id(str)) return 0;

   write("You rub the old prayer beads, hoping for inspiration.\n");
   say(QCTNAME(TP) + " rubs a string of old stone beads.\n");

   if (MEMBER(TP) || TP->query_skill(BLESSED) < 1) return 1;

   if (member_array(SEEKER_SHADOW + ":",
                    TP->query_autoshadow_list()) == -1) {
       seteuid(getuid());
       shadow = clone_object(SEEKER_SHADOW);
       if (shadow->shadow_me(TP, "race", "cleric", "Mystic Seeker") != 1)
       {
           write("For some reason you do not become one " +
                 "of the chosen seekers.\n");
           "/secure/master"->do_debug("destroy", shadow);
           return 0;
       }
   }

   return 1;
}

public void
init()
{
   ::init();
   add_action(do_pray, "pray");
   add_action(do_rub, "rub");
}

public void
create_object()
{
   set_name("beads");
   add_name("prayer beads");
   add_name(MYSTIC_BEADS);
   set_adj("stone");
   add_adj("old");

   set_short("string of old stone prayer beads");
   set_long(
      "A string of old stone prayer beads. Each stone is inscribed with " +
      "cryptic symbols and runes.\n");
}

public void
destroy_beads(object ob)
{
   if (ob && living(ob)) {
       seteuid(getuid());
       clone_object(GUILD_DIR + "quest/dust")->move(ob);
       ob->catch_msg("The stone beads crumble into dust.\n");
   
       if (member_array(SEEKER_SHADOW + ":",
                        ob->query_autoshadow_list()) >= 0)
           ob->remove_autoshadow(SEEKER_SHADOW);
   }
   remove_object();
}

public void
enter_env(object to, object from)
{
   ::enter_env(to, from);
   
   if (!to || !living(to)) return;

   if (MEMBER(to) || to->query_alignment() < JOIN_LIM)
       set_alarm(2.0, -1.0, &destroy_beads(to));
}
