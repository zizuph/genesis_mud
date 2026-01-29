public void
gardener_read_notepad()
{
   string text = "", *herbs, name = shadow_who->query_real_name();
   mapping notes = restore_map(MEMBER_NOTES(name));
   int i, j, sz, hsz, msz = m_sizeof(notes);

   if(!msz)
   {
      shadow_who->catch_tell("Your annotation scroll is empty.\n");
      return;
   }

   herbs = m_indices(notes);
   hsz = sizeof(herbs);

   if(!hsz)
   {
      shadow_who->catch_tell("Your annotation scroll is empty.\n");
      return;
   }

   for(i = 0; i < hsz; i++)
   {
      sz = sizeof(notes[herbs[i]]);

      for(j = 0; j < sz; j++)
      {
         text += notes[herbs[i]][j];

         if(j < (sz - 1))
         {
            text += "\n";
         }
      }

      if(i < (hsz-1))
      {
         text += "\n\n";
      }
   }

   shadow_who->more(text);
}
