public int
gardener_copy_scroll(string str)
{
   string name = shadow_who->query_real_name(), hb_name;
   mapping notes, journal;
   string *herbs;
   int hsz, sz, i, j, start_time, length;

   start_time = shadow_who->query_prop(GARDENER_COPY_START_TIME);
   length = shadow_who->query_prop(GARDENER_COPY_TIME_LENGTH);

   if(!start_time || !length || (start_time + length) > (time() + 1))
   {
      shadow_who->catch_tell("You decide not to copy your notes.\n");
      return 0;
   }

   if(!m_sizeof((notes = restore_map(MEMBER_NOTES(name)))))
   {
      shadow_who->catch_tell("You do not have an annotation scroll!\n");
      return 0;
   }

   herbs = m_indices(notes);

   if(!(hsz = sizeof(herbs)))
   {
      shadow_who->catch_tell("You do not seem to have recorded any " +
         "notes after all!\n");
      return 0;
   }

   journal = restore_map(MEMBER_JOURNAL(name));

   for(i = 0; i < hsz; i++)
   {
      hb_name = herbs[i];
      sz = sizeof(notes[hb_name]);

      if(!journal[hb_name] || !sizeof(journal[hb_name]))
      {
         journal[hb_name] = ({ });
      }

      for(j = 0; j < sz; j++)
      {
         journal[hb_name] += ({ notes[hb_name][j] });
      }
   }

   save_map(journal, MEMBER_JOURNAL(name));
   notes = ([ ]);
   save_map(notes, MEMBER_NOTES(name));
   shadow_who->catch_tell("You finish copying notes into your " +
      "journal.\n");
   tell_room(environment(shadow_who),
      QCTNAME(shadow_who) + " finishes scribbling on " +
      shadow_who->query_possessive() + " " +
      LANG_SHORT(present(GARDENER_JOURNAL_ID, shadow_who)) + ".\n",
      ({ shadow_who }));

   return 0;
}
