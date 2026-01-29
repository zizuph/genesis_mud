#define GARDENER_HERBALISM "_es_gardener_herbalism"
#define GARDENER_LOCSENSE "_es_gardener_locsense"
#define GARDENER_HUNTING "_es_gardener_hunting"
#define GARDENER_AWARE "_es_gardener_awareness"

private string _specials_lfind_target;

public string
query_lfind_target()
{
   return _specials_lfind_target;
}

public int
set_lfind_target(string str)
{
   string name = shadow_who->query_real_name();

   if(str == 0)
   {
      _specials_lfind_target = 0;
      return 1;
   }

   if(str && strlen(str) > 0)
   {
      if(!query_gardener_encountered_herb(str))
      {
         return 0;
      }

     _specials_lfind_target = str;
      return 1;
   }

   return 0;
}

public void
init_gardener_lfind()
{
   _specials_lfind_target = 0;
}

public void
gardener_add_skill_props()
{
   int sk = shadow_who->query_skill(SS_HERBALISM);

   shadow_who->add_prop(GARDENER_HERBALISM, MIN(sk, 60));

   sk = shadow_who->query_skill(SS_AWARENESS);
   shadow_who->add_prop(GARDENER_AWARE, MIN(sk, 50));

   sk = shadow_who->query_skill(SS_LOC_SENSE);
   shadow_who->add_prop(GARDENER_LOCSENSE, MIN(sk, 50));

   sk = shadow_who->query_skill(SS_HUNTING);
   shadow_who->add_prop(GARDENER_HUNTING, MIN(sk, 30));
}

public void
gardener_remove_skill_props()
{
   shadow_who->remove_prop(GARDENER_HERBALISM);
   shadow_who->remove_prop(GARDENER_LOCSENSE);
   shadow_who->remove_prop(GARDENER_HUNTING);
   shadow_who->remove_prop(GARDENER_AWARE);
}

private static int
get_herb_id(string file)
{
   return GARDENER_HERBS->query_file_id(file);
}

public void
enter_env(object dest, object old)
{
   string *files;
   int *herb_ids, result, *name_ids, i, _in_ids = 0;

   shadow_who->enter_env(dest, old);

   if(!_specials_lfind_target)
   {
      return;
   }

   if(dest->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
      shadow_who->query_mana() <= 0)
   {
      shadow_who->command("$lfind stop");
      return;
   }

   if(old != shadow_who->query_prop(LIVE_O_LAST_ROOM))
   {
      return;
   }

   shadow_who->add_mana(-3);

   files = dest->query_herb_files();

   gardener_add_skill_props();

   if(!files || !sizeof(files) ||
      !(herb_ids = map(map(files, chop_string), get_herb_id) - ({ 0 })) ||
      !sizeof(herb_ids) ||
      (result = shadow_who->resolve_task(
      TASK_DIFFICULT, ({ TS_LAYMAN, GARDENER_HERBALISM,
      GARDENER_AWARE, GARDENER_LOCSENSE, GARDENER_HUNTING }))) <= 0 ||
      !random(result))
   {
      shadow_who->catch_tell("You are not certain if there are any " +
         "herbs here at all!\n");
        gardener_remove_skill_props();
      return;
   }

   name_ids = GARDENER_HERBS->query_name_ids(_specials_lfind_target);

   for(i = 0; i < sizeof(name_ids); i++)
   {
      if(member_array(name_ids[i], herb_ids) != -1)
      {
         _in_ids = 1;
         break;
      }
   }

   if(!_in_ids || !random(result))
   {
      shadow_who->catch_tell("You sense that there may be some useful " +
         "herbage in the area, but you fail to detect any " +
         _specials_lfind_target + ".\n");
      gardener_remove_skill_props();
      return;
   }

   gardener_remove_skill_props();

   shadow_who->catch_tell("Your senses come alive as you enter a new " +
      "environment and detect the distinctive scent of " +
      _specials_lfind_target + ".\n");
}
