/*
 * The Gondorian Ranger Guild shadow
 *
 * Original code by Elessar
 * Modifications by Olorin and Mercade
 * Added functionability for punishments.
 * Elessar, May 1994.
 */

inherit "/std/guild/guild_occ_sh";
inherit "/d/Gondor/common/guild/lib/r_titles";

#include <ss_types.h>
#include <language.h>
#include <const.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/binbit.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

/*
 * This is the initial taxrate for the guild. Use set_guild_pref() in 
 * the player to change it if needed.
 */
int
query_guild_tax_occ()
{ 
    if (query_bin_bits(1,16,2,query_shadow_who()) == 0) return PUPIL_TAX;
    return TAXRATE;
}

string
query_guild_style_occ()
{
    return "ranger";
}

string
query_guild_name_occ()
{
    return "Gondorian Rangers Guild";
}
      
string
query_guild_skill_name(int type)
{
    if (type == SS_HEARING) return "hearing";
    if (type == SS_BRAWLING) return "brawling";
    if (type == PUNISHMENT) return "";
    if (type == PUNISHED) return "";
    if (type == REWARDED) return "";
    if (type == MASTER_TASK) return "";
    if (type == OLD_BRAWLING) return "";
    if (type == OLD_HEARING) return "";
    if (type == OLD_REWARDED) return "";
    if (type == OLD_PUNISHED) return "";

    return query_shadow_who()->query_guild_skill_name(type);
}

int
query_guild_not_allow_join_occ(object player, string type,
                               string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
	return 1;

    notify_fail("No Ranger may become a Bloodguard and supporter of Evil!\n");
    if (name == "Bloodguard guild")
        return 1;
    notify_fail("No Ranger may become a magician!\n");
    if (style == "mage")
        return 1;
    return 0;
}

void
do_leave_guild(object pl)
{
    (GUILD)->short();
    (GUILD)->throw_out(pl);
}

int
query_guild_keep_player(object ob)
{
    if (ob->query_guild_style_lay() == "mage")
    {
        notify_fail("No mages may be a Ranger of the Westlands!\n");
        do_leave_guild(ob);
        return 0;
    }
    if (ob->query_race_name()=="goblin")
    {
        notify_fail("No goblins may be a Ranger of the Westlands!\n");
        do_leave_guild(ob);
        return 0;
    }
    if (ob->query_alignment() < 0)
    {
        notify_fail("The Dark Lord has tempted you too much!\n" +
            "You are no longer worthy of being a Ranger!\n");
	do_leave_guild(ob);
	return 0;
    }
    return 1;
}

string
query_company()
{
    return COMPANY_TITLE[query_bin_bits(1,16,2,query_shadow_who())];
}

nomask public string
query_guild_title_occ()
{
  object token = present("ranger_guild_object",query_shadow_who());
  FIX_EUID;
  if (query_bin_bits( 1, 16, 2, query_shadow_who()) == 2) {
    if (!objectp(token)) return "";
      else if (!token->query_worn()) return "";
    }
  if (query_shadow_who()->query_wiz_level())
    return query_shadow_who()->query_title();
  return query_ranger_title();
}

void log_killing(object killed, string whom)
{
    string file,
           domain;
    file = file_name(environment(query_shadow_who()));
    if((domain = explode(file,"/")[2]) == "Gondor")
        domain = CAP(explode(file,"/")[3]);
    write_file(RANGER_KILLS, ctime(time()) + " " +
        query_shadow_who()->query_name() + " killed " +
        killed->query_name() + ", " + LANG_ADDART(whom) + ", in " + domain + ".\n");
    write_file(NPC_KILLS, ctime(time()) + " " +
        query_shadow_who()->query_name() + " killed " +
        killed->query_name() + ", " + LANG_ADDART(whom) + " (" +
        file_name(environment(query_shadow_who())) + ").\n");
}

int
notify_you_killed_me(object killed)
{
    string  killed_race = (string)killed->query_race_name();
    mixed   whom;

/* you have to do this in case more than one shadow defines the function, Olorin */
    shadow_who->notify_you_killed_me(killed);
    seteuid(getuid(TO));
    if (interactive(killed))
    {
        write_file(RANGER_KILLS, ctime(time()) + " " +
            query_shadow_who()->query_name() + " killed " +
            killed->query_name() + ", a player (" + killed_race + ").\n");
        if (killed_race == "elf" || killed_race == "hobbit" ||
            killed_race == "dwarf" || killed_race == "human" ||
            killed_race == "gnome")
        {
            tell_object(query_shadow_who(),
                "You are not supposed to kill players, and especially not a "
                + killed_race + "!\n");
            tell_object(query_shadow_who(),
                "Consider this a warning from the Rangers Guild.\n");
        }
    }
    if (killed->id("Cityguard") || killed->id("_gondor_guard"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing cityguards and the like.\n");
        tell_object(query_shadow_who(),
            "Consider this a warning from the Rangers Guild.\n");
    }
    else if(killed->id("ranger"))
    {
        tell_object(query_shadow_who(),
            "Oh no! You killed one of your own guild!\n" +
            "Consider this a warning from the Ranger Council.\n");
        log_killing(killed, "ranger");
    }
    else if(killed->id("rohirrim"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing Rohirrim, who are our allies!\n" +
            "Consider this a warning from the Rangers Guild.\n");
        log_killing(killed, "rohirrim");
    }
    else if((function_exists("create_captain", killed) == "/d/Genesis/ship/captain") ||
            (function_exists("create_monster", killed) == "/d/Genesis/ship/captain"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing ship captains!\n" +
            "Consider this a warning from the Rangers Guild.\n");
        log_killing(killed, "ship captain");
    }
    else if((whom = killed->query_prop(GONDOR_M_LOG_RANGER_KILL)))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing the allies of the White Tower!\n" +
            "Consider this a warning from the Rangers Guild.\n");
        if (stringp(whom))
            log_killing(killed, whom);
        else
            log_killing(killed, killed->short());
    }
    return 1;
}

string
query_def_post()
{
  return COMPANY_POST[query_bin_bits(1,16,2,query_shadow_who())];
}

string
query_guild_trainer_occ()
{
  return COMPANY_TRAIN[query_bin_bits(1,16,2,query_shadow_who())];
}

void
init_occ_shadow(string arg)
{
  object pl;
  ::init_occ_shadow(arg);
  pl = query_shadow_who();
  if (pl->query_skill(SS_BRAWLING) < pl->query_skill(OLD_BRAWLING))
    pl->set_skill(SS_BRAWLING, pl->query_skill(OLD_BRAWLING));
  if (pl->query_skill(SS_HEARING) < pl->query_skill(OLD_HEARING))
    pl->set_skill(SS_HEARING, pl->query_skill(OLD_HEARING));
  if (pl->query_skill(REWARDED) < pl->query_skill(OLD_REWARDED))
      pl->set_skill(REWARDED, pl->query_skill(OLD_REWARDED));
  if (pl->query_skill(PUNISHED) < pl->query_skill(OLD_PUNISHED))
    pl->set_skill(PUNISHED, pl->query_skill(OLD_PUNISHED));
  pl->remove_skill(OLD_BRAWLING);
  pl->remove_skill(OLD_HEARING);
  pl->remove_skill(OLD_REWARDED);
  pl->remove_skill(OLD_PUNISHED);
}

