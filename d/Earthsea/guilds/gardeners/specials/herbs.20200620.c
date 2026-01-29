private string *_specials_known_herbs;
private int *_specials_herb_varieties;

public int
query_gardener_encountered_variety(int id)
{
   return (member_array(id, _specials_herb_varieties) != -1);
}

public int
query_gardener_encountered_herb(string name)
{
   return (member_array(name, _specials_known_herbs) != -1);
}

public void
init_gardener_herbs()
{
   string name, pl_name = shadow_who->query_real_name();
   mapping map = restore_map(MEMBER_HERBS(pl_name));
   int i, sz;

   _specials_herb_varieties = map["herb_varieties"];
   sz = sizeof(_specials_herb_varieties);
   _specials_known_herbs = ({ });

   for(i = 0; i < sz; i++)
   {
      name = GARDENER_HERBS->query_id_name(_specials_herb_varieties[i]);

      if(member_array(name, _specials_known_herbs) == -1)
      {
         _specials_known_herbs += ({ name });
      }
   }
}

private void
register_herb(object tp, object herb)
{
   string pl_name = tp->query_real_name(),
      hb_name = herb->query_herb_name(),
      rarity = describe_rarity(herb->query_find_diff()),
      difficulty = describe_difficulty(herb->query_id_diff()),
      domain = (SECURITY->domain_object(herb));
   object env = environment(tp);
   mapping notes = restore_map(MEMBER_NOTES(pl_name));

   notes[implode(explode(hb_name, " "), "_")] = ({
      ctime(time()) + "\n" +
      "I have encountered a new herb today, the " + rarity + " " +
      hb_name + " from the lands of " + domain + ". It was " +
      difficulty + " to spot as I travelled through \"" +
      capitalize(env->short(tp)) + "\".\n" });
   save_map(notes, MEMBER_NOTES(pl_name));

   tp->catch_tell("You realize that you have encountered this herb " +
      "in your studies before. It is the " + rarity + " herb " +
      hb_name + " from the lands of " + domain + ", which is " +
      difficulty + " to identify.\n" +
      "You take a moment to update your annotation scroll.\n");
}

private void
register_variety(object tp, object herb)
{
   string pl_name = tp->query_real_name(),
      hb_name = herb->query_herb_name(),
      rarity = describe_rarity(herb->query_find_diff()),
      difficulty = describe_difficulty(herb->query_id_diff()),
      hb_name_safe = implode(explode(hb_name, " "), "_"),
      domain = (SECURITY->domain_object(herb));
   object env = environment(tp);
   mapping notes = restore_map(MEMBER_NOTES(pl_name));

   if(!notes[hb_name_safe] || !sizeof(notes[hb_name_safe]))
   {
      notes[hb_name_safe] = ({ });
   }

   notes[hb_name_safe] += ({
      ctime(time()) + "\n" +
      "I have encountered a " + rarity + " new variety of " + hb_name +
      ", apparently originating in the lands of " +
      domain + ". It was " + difficulty +
      " to spot as I travelled through \"" + capitalize(env->short(tp)) +
      "\".\n" });
   save_map(notes, MEMBER_NOTES(pl_name));

   tp->catch_tell("You realize you have encountered a new variety of " +
      hb_name + " from the lands of " + domain + ".\n" +
      "You take a moment to update your annotation scroll.\n");
}

public void
enter_inv(object ob, object old)
{
   string pl_name, name, file;
   int id;
   object env;

   shadow_who->enter_inv(ob, old);

   if(old && objectp(old))
   {
      return;
   }

   if (!IS_HERB_OBJECT(ob))
   {
      return;
   }

    if(ob->query_dried())
    {
        return;
    }

   if(!ob->do_id_check(shadow_who))
   {
      return;
   }

   env = environment(shadow_who);
   file = HERB_FILE(ob);

   if(member_array(file, map(env->query_herb_files(), chop_string)) == -1)
   {
      return;
   }

   id = GARDENER_HERBS->query_file_id(file);

   if(!id)
   {
      id = GARDENER_HERBS->add_herb(ob);

      if(!id)
      {
         return;
      }
   }

   name = ob->query_herb_name();
   pl_name = shadow_who->query_real_name();

   if(member_array(name, _specials_known_herbs) == -1)
   {
      _specials_known_herbs += ({ name });

      if(member_array(id, _specials_herb_varieties) == -1)
      {
         _specials_herb_varieties += ({ id });
         set_alarm(0.0, 0.0, &register_variety(shadow_who, ob));
      } else {
         set_alarm(0.0, 0.0, &register_herb(shadow_who, ob));
      }

      save_map(([ "herb_varieties" : _specials_herb_varieties ]),
         MEMBER_HERBS(pl_name));
   }
}
