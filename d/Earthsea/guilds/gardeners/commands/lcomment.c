#pragma strict_types
#pragma no_clone

#include "../defs.h"
#include <files.h>
#include <macros.h>
#include <language.h>

public void
gardener_comment_herb(object tp, string herb, string str)
{
   string name = tp->query_real_name();
   mapping journal;

   setuid();
   seteuid(getuid());

   journal = restore_map(MEMBER_JOURNAL(name));

   if(!str || !strlen(str) || !herb || !strlen(herb) ||
      !journal[herb] || !sizeof(journal[herb]))
   {
      tp->catch_tell("You don't seem to find a place for your " +
         "comments.\n");
      return;
   }

   journal[herb] += ({ str });

   save_map(journal, MEMBER_JOURNAL(name));
   tp->catch_tell("You carefully add your comment to your journal.\n");
   tell_room(environment(tp),
      QCTNAME(tp) + " scribbles something in " +
      tp->query_possessive() + " " +
      LANG_SHORT(present(GARDENER_JOURNAL_ID, tp)) + ".\n",
      ({ tp }));
}

public int
_lcomment(string str)
{
   object tp = this_player();
   string name, rep_name;
   mapping journal;

   if(!str || !strlen(str))
   {
      return notify_fail("Comment on what?\n");
   }

   setuid();
   seteuid(getuid());

   name = tp->query_real_name();
   rep_name = implode(explode(str, " "), "_");
   journal = restore_map(MEMBER_JOURNAL(name));

   if(!journal[rep_name] || !sizeof(journal[rep_name]))
   {
      return notify_fail("Comment on which herb in your journal?\n");
   }

   clone_object(EDITOR_OBJECT)->edit(
      &gardener_comment_herb(tp, rep_name));

   return 1;
}
