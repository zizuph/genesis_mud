#pragma strict_types
#pragma no_inherit

inherit "/std/guild/guild_craft_sh";
inherit "/d/Earthsea/guilds/gardeners/lib/herb_functions";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <stdproperties.h>
#include <tasks.h>
#include <filter_funs.h>

#include "specials/herbs.c"
#include "specials/notepad.c"
#include "specials/lcopy.c"
#include "specials/lfind.c"
#include "specials/desc.c"

public string
query_guild_name_craft()
{
   return GARDENER_NAME;
}

public string
query_guild_style_craft()
{
   return GARDENER_STYLE;
}

public int
query_guild_tax_craft()
{
   return GARDENER_TAX;
}

public string
query_guild_title_craft()
{
   if(query_gardener_display_title() == GARDENER_TITLE_PRES)
   {
      return query_gardener_title();
   }

   return 0;
}

public string
query_guild_trainer_craft()
{
    return GARDENER_TRAINER;
}

public void
init_new_gardener()
{
   clone_object(GARDENER_JOURNAL_OBJ)->move(shadow_who, 1);
   clone_object(GARDENER_NOTEBOOK_OBJ)->move(shadow_who, 1);
}

public int
remove_gardeners_guild()
{
   string name = shadow_who->query_real_name();
   object journal = present(GARDENER_JOURNAL_ID, shadow_who),
      notebook = present(GARDENER_NOTEBOOK_ID, shadow_who);
   string old_dir = GEN_OLD_MEMBER_DIR(name);

   shadow_who->clear_guild_stat(SS_CRAFT);
   shadow_who->remove_skill(GARDENER_SKILL_TITLE);

   if(file_size(MEMBER_DIR(name)) == -2)
   {
      mkdir(old_dir);

      if(file_size(MEMBER_DATA(name) + ".o") >= 0)
      {
         rename(MEMBER_DATA(name) + ".o", old_dir + "data.o");
      }

      if(file_size(MEMBER_NOTES(name) + ".o") >= 0)
      {
         rename(MEMBER_NOTES(name) + ".o", old_dir + "notes.o");
      }

      if(file_size(MEMBER_JOURNAL(name) + ".o") >= 0)
      {
         rename(MEMBER_JOURNAL(name) + ".o", old_dir + "journal.o");
      }

      if(file_size(MEMBER_HERBS(name) + ".o") >= 0)
      {
         rename(MEMBER_HERBS(name) + ".o", old_dir + "herbs.o");
      }

      rmdir(MEMBER_DIR(name));
   }

   if(journal)
      journal->remove_object();

   if(notebook)
      notebook->remove_object();

   write_file(GARDENER_LOG_MEMBERS,
      sprintf("%-24s [%-15s] left the craft guild.\n", ctime(time()),
      shadow_who->query_cap_name()));

   return remove_guild_craft();
}

public void
add_soul()
{
   shadow_who->add_cmdsoul(GARDENER_SOUL);
   shadow_who->update_hooks();
}

public void
init_craft_shadow(string arg)
{
   string name = shadow_who->query_real_name();
   int pindan_id;
   mapping data;

   ::init_craft_shadow(arg);

   setuid();
   seteuid(getuid());

   if(file_size(MEMBER_DIR(name)) != -2)
   {
      if(!mkdir(MEMBER_DIR(name)))
      {
         shadow_who->catch_tell("An error occured while accessing " +
            "your guild data. Please contact the guildmaster of the " +
            GARDENER_NAME + ".\n");
      }

      write_file(GARDENER_LOG_MEMBERS,
         sprintf("%-24s [%-15s] joined the craft guild.\n", ctime(time()),
         shadow_who->query_cap_name()));

      if(file_size(MEMBER_DATA(name)) < 0)
      {
         save_map((["join_time" : time()]), MEMBER_DATA(name));
      }

      if(file_size(MEMBER_NOTES(name)) < 0)
      {
         save_map(([]), MEMBER_NOTES(name));
      }

      if(file_size(MEMBER_JOURNAL(name)) < 0)
      {
         save_map(([ "pindan" : ({
            "Johanna sent me on a task to procure this extremely " +
            "rare herb found only in the very pits of Moria! To " +
            "my surprise I was able to pull a fine sample off the " +
            "walls and return it to her safely. She explained to " +
            "me that when inhaled it stirs the senses and allows " +
            "one to find their way in the most difficult terrain." }) ]),
            MEMBER_JOURNAL(name));
      }

      if(file_size(MEMBER_HERBS(name)) < 0)
      {
         pindan_id = GARDENER_HERBS->query_name_ids("pindan")[0];
         save_map(([ "herb_varieties" : ({ pindan_id }) ]),
            MEMBER_HERBS(name));
      }
   }

   set_alarm(0.0, 0.0, add_soul);
   init_gardener_herbs();
   init_gardener_lfind();

   if(file_size(GARDENER_NEWS))
   {
      shadow_who->catch_tell(read_file(GARDENER_NEWS));
   }
}
