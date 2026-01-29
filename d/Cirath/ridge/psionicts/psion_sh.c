/* glad_sh.c: The Gladiator-Guild Shadow: Mylos & Anton, 10-8-93.
 *     Redone for guild revision: Shiva, 1/15/95.
 *     Redone for reopening: Serpine, 4/26/95.
 *     Efficeincy and bug fixes: Astro & Serpine, 11/26/95.
 */
 
#pragma strict_types
#pragma save_binary
 
inherit "/std/guild/guild_occ_sh";
#include "defs.h"
#include <const.h>
 
#define LEVEL_BY_GUILD_STAT
#define QSW query_shadow_who()
#define SET(x, y) if (QSW->query_skill(x) > y) \
      (y < 1 ? QSW->remove_skill(x) : QSW->set_skill(x, y))
 
 /* Standard functions for any occupational guild */
int query_guild_tax_occ() { return TAX; }
string query_guild_style_occ() { return GUILD_STYLE; }
string query_guild_name_occ() { return GUILD_NAME; }
string query_def_post() { return (PSION_ROOM+"postoffc.c"); }
public mixed query_guild_trainer_occ()
        { return "/d/Cirath/ridge/psionicts/room/training"; }
 
 /* Pre-declaration of important functions */
varargs void kick_out_psion(int spare);
 
 
/* Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc("psionict_subloc", this_object());
    set_alarm(1.0, 0.0, "check_psion", ob);
    return 1;
}
 
void
check_psion(object obp)
{
    string name = obp->query_real_name();
 
 
    obp->catch_msg("You awake from nightmares of slavery and violence "+
          "only to face them in reality: Such is your path, the path of "+
          "a warrior of Athas.\n");
 
    if(!present(AMUL_ID, obp))
        (MANAGER)->give_amulet(obp);
 
    if (member_array(PSION_SOUL, obp->query_cmdsoul_list()) < 0)
    {
        obp->add_cmdsoul(PSION_SOUL);
        obp->update_hooks();
    }
 
    obp->catch_msg("Hail, oh Gladiator!\n");
}
 
/* Function name: query_gladiator_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_psionict_level()
{
#ifdef LEVEL_BY_GUILD_STAT
  return shadow_who->query_base_stat(SS_OCCUP) / 5;
#else
  return shadow_who->query_base_skill(SS_PSION_LEVEL);
#endif
}
 
/*
 * Function name: query_guild_title_occ
 * Description:   Gives the guild title.
 * Returns:       Guess what.
 */
string query_guild_title_occ()
{
    int stat, max_stat, gender, cnslot;
    object this_psion = shadow_who;
 
    if (present(COUN_AMUL_ID, this_psion))
    {
        if (present(OVER_AMUL_ID, this_psion)) return PSION_OVER_TITLE;
        
        cnslot=QUERY_COUN_MEMB(lower_case(this_psion->query_name()));
        if (cnslot>0) return PSION_COUN_SLOTS[cnslot-1]+" "+PSION_COUN_TITLE;
    }
 
    stat = query_psionict_level();
    max_stat = sizeof((gender = shadow_who->query_gender()) == G_FEMALE ?
               FEMALE_TITLES : MALE_TITLES) - 1;
    if (stat < 0) stat = 0;
    else if (stat > max_stat) stat = max_stat;
 
    return (gender == G_FEMALE ? FEMALE_TITLES[stat] : MALE_TITLES[stat])+
            " of the minds";
}
 
/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != "psionict_subloc")
        return shadow_who->show_subloc(subloc, me, for_obj);
 
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
     return(for_obj == me ? "You have an intellegent look about " +
     "you.\n" : CAP(me->query_pronoun()) +
     " has an intellegent look.\n");
}
 
 
/* Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_CHARGE) return "charge";
    if (type == SS_BERSERK) return "berserk";
    if (type == SS_GLAD_COMPARE) return "gcompare";
    if (type == SS_PSION_LEVEL) return "";
    return 0;
}
 
public void
leave_env(object from, object to)
{
    object me = query_shadow_who();
 
    if(me->query_prop(GLAD_I_IS_CHARGE) == 1)
    {
        me->add_prop(GLAD_I_IS_CHARGE, 2);
        me->catch_msg("Your sudden movement ruins your concentration, "
            +"making you unable to charge again for a moment.\n");
    }
     
    me->leave_env(from, to);
}
 

varargs void
kick_out_psion(int spare)
{
    object amul;
    string str;
    int i;
 
    CLEAR_GBIT(shadow_who, PSION_MEMBER);
 
    while(amul = present(AMUL_ID, shadow_who)) amul->remove_object();
 
    shadow_who->remove_cmdsoul(PSION_SOUL);
    shadow_who->update_hooks();
 
    SET(SS_BERSERK, 0);
    SET(SS_CHARGE, 0);
    SET(SS_GLAD_COMPARE, 0);
    SET(SS_PSION_LEVEL, 0);
 
    setuid(); seteuid(getuid());
    if(!IS_WIZ(shadow_who)&&extract(str=shadow_who->query_real_name(),-2)!="jr")
    {
        WRITE_LOG(QUIT_LOG, shadow_who, "has just left the guild.");
        // rm(MEM_FILE(str));
    }
 
    (MANAGER)->remove_member(str);
    (MANAGER)->remove_council(shadow_who->query_name());
 
    shadow_who->catch_msg("You are no longer a Gladiator of Athas.\n");    
 
    if(!spare) (MANAGER)->snuff_psionict(shadow_who);
 
    shadow_who->setup_skill_decay();
    shadow_who->clear_guild_stat(SS_OCCUP);
    remove_guild_occ();
}
 
#ifndef LEVELS_BY_GUILD_STAT
int 
set_skill(int skill, int level)
{
    if (skill == SS_PSION_LEVEL && !IS_WIZ(previous_object()) && 
                 !previous_object()->query_PSION_challenge())
    return 0;
 
    return shadow_who->set_skill(skill, level);
}
#endif
