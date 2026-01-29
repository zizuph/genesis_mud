#pragma strict_types
#pragma no_clone

#include "../defs.h"
#include <language.h>
#include <macros.h>
#include <filter_funs.h>

public int
_lcopy(string str)
{
   object tp, paralyze;
   mapping notes;
   string *herbs;
   int hsz, sz, paralyze_time;

   if(!str || !strlen(str) || str != "notes")
   {
      return notify_fail("Copy what? Notes?\n");
   }

   setuid();
   seteuid(getuid());

   tp = this_player();
   notes = restore_map(MEMBER_NOTES(tp->query_real_name()));

   if(!m_sizeof(notes))
   {
      return notify_fail("Your annotation scroll is empty.\n");
   }

   herbs = m_indices(notes);

   if(!(hsz = sizeof(herbs)))
   {
      return notify_fail("Your annotation scroll is empty.\n");
   }
   
   paralyze_time = 3 + random(7) + (hsz * (3+random(2)));
   tp->add_prop(GARDENER_COPY_TIME_LENGTH, paralyze_time);
   paralyze = clone_object("/std/paralyze");
   paralyze->set_name("_gardener_lcopy_paralysis_");
   paralyze->set_stop_verb("stop");
   paralyze->set_fail_message("You are busy copying your notes " +
      "to your journal. You must 'stop' to do anything else.\n");
   paralyze->set_stop_object(tp);
   paralyze->set_stop_fun("gardener_copy_scroll");
   paralyze->set_remove_time(paralyze_time);
   paralyze->set_stop_message(0);
   tp->add_prop(GARDENER_COPY_START_TIME, time());
   paralyze->move(tp, 1);

   write("You begin copying your notes into your journal.\n");
   say(QCTNAME(tp) + " fetches a quill and begins reading " +
      LANG_ASHORT(present(GARDENER_NOTEBOOK_ID, tp)) + " and " +
      "simultaneously scribbling in " + tp->query_possessive() +
      " " + LANG_ASHORT(present(GARDENER_JOURNAL_ID, tp)) + ".\n",
      ({ tp }));

   return 1;
}
