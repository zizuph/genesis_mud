/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public int query_mystic_rank();
public int query_mystic_office();
public int query_piety();
public int query_spell_level();
public int query_advance_rank();
public int advance_rank(object who);
public int query_lower_rank();
public int lower_rank(object who);
public int query_present_rank();
public void set_rank(int rank);
public void set_piety(int piety);

public int
query_guild_tax_occ()
{
   return GUILD_TAX;
}

/* Returns an array of strings containing all skill trainers
 * see mystic_defs.h
 */
public string *
query_guild_trainer_occ()
{
   return MYSTIC_TRAINERS;
}

/* Function: query_guild_keep_player
 * Description: Has this player been banned from the mystics?
 * Arguments: player - object
 * Returns: 1 - keep player; 0 - kick player out.
 * - Cedric, 5/93
 */
public int
query_guild_keep_player(object player)
{
   if (file_size(BANNED) <= 0 ) return 1;
   seteuid(getuid());
   if (member_array(player->query_real_name(),
                    explode(read_file(BANNED), "\n")) >= 0) {
       player->catch_msg("You have been banned from the " +
                         "Ancient Mystic Order!\n");
       call_other(player, "set_rank", -1);
       return 0;
   }
   return 1;
}

/*
 * Added by Nick
 */
public string query_guild_name_occ() { return GUILD; }
public string query_guild_style_occ() { return GUILD_STYLE; }

public int
query_guild_not_allow_join_occ(object player, string type, string style,
   string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;
    notify_fail("Mystics shall have no other allegiances.\n");
    if (style == "fighter") return 1;
    return 0;
}

public string
query_guild_title_occ()
{
   string str;
   int    occ, npc, rank;
   object who;

   who  = query_shadow_who();
   occ  = who->query_stat(SS_OCCUP);
   rank = query_mystic_rank();

   if (rank < 0) return TRAITOR;

   if (who->query_prop("no_show_title")) return "";

   if (rank >= sizeof(RANKTITLE)) rank = MYSTIC_ARCHON;

    if (rank < 1 && who->query_skill(130008) < 1)
    { str = NOVTITLE[0]; return str; }
   if (rank >= MYSTIC_CANTOR) {
       str = RANKTITLE[rank];
  if(rank == MYSTIC_ARCHON && who->query_alignment() >= HOLY_LIM &&
  occ > 119 && who->query_skill(EXALT) > 0)
           str = "Holy " + str;
   } else if (rank == MYSTIC_NOVITIATE) {
       if (occ <= LEVELS[rank][0])
           str = NOVTITLE[0];
       else
           str = NOVTITLE[1];
   } else {
       str = RANKTITLE[rank];
   if(occ <= LEVELS[rank][0] || who->query_skill(EXALT) < 1)
           str = PRETITLE[0] + str;
   else if (occ <= LEVELS[rank][1] || who->query_skill(EXALT) == 1)
           str = PRETITLE[1] + str;
       else
           str = PRETITLE[2] + str;
   }

   return str;
}
/*

public int
wield(object wep)
{
   if (wep->query_prop(MYSTIC_WEAPON))
      return query_shadow_who()->wield(wep);
      
   query_shadow_who()->catch_msg("Thou shalt take arms of the mystic " +
                                 "ways alone.\n");
      
   return 0;
}
*/

public mixed
query_guild_skill_name(int type)
{
   switch (type)
   {
       case ENTRANCE_QUEST:
           return "";
       case SS_CHANNELING:
           return "channeling";
       case MYSTIC_RANK:
           return "";
       case BLESSED:
           return "";
       case PIETY:
           return "";
       case OFFICE:
           return "";
       case CURSED:
           return "";
	case NOVICE:
	    return "";
   }
   return query_shadow_who()->query_guild_skill_name(type);
}

public void
set_piety(int piety)
{
    query_shadow_who()->set_skill(PIETY, piety);
}

public int
query_piety()
{
    return query_shadow_who()->query_skill(PIETY);
}

add_piety(int num){
   int piety;
   piety = query_shadow_who()->query_skill(PIETY);
   set_piety(piety + num);
}

reduce_piety(int num){
  int piety;
   piety = query_shadow_who()->query_skill(PIETY);
   set_piety(piety - num);
}

public int
query_mystic_rank()
{
    return query_shadow_who()->query_skill(MYSTIC_RANK);
}

public int
query_mystic_office()
{
    return query_shadow_who()->query_skill(OFFICE);
}

public int
query_advance_rank()
{
    int rank, occ, subrank;

    rank = query_mystic_rank();
    occ  = query_shadow_who()->query_stat(SS_OCCUP);

    if (rank < 0) return 0;

    if (rank == MYSTIC_PATRIARCH) return 0;

    subrank = sizeof(LEVELS[rank]) - 1;
    if (occ > LEVELS[rank][subrank]) return 1;

    return 0;
}

public int
advance_rank(object who)
{
    int rank, who_rank;

    if (!who || who == query_shadow_who()) return 0;
    if (!query_advance_rank()) return 0;

    rank = query_mystic_rank();
    who_rank = who->query_mystic_rank();
    if (who_rank < MYSTIC_ARCHON || who_rank <= rank) return 0;

    set_rank(rank + 1);

    return 1;
}

public int
query_lower_rank()
{
    int rank, occ, subrank;

    rank = query_mystic_rank();
    occ  = query_shadow_who()->query_stat(SS_OCCUP);

    if (rank < 0) return 0;

    if (rank == MYSTIC_PATRIARCH) return 0;

    subrank = sizeof(LEVELS[rank]) - 1;
    if (occ > LEVELS[rank][subrank]) return 1;

    return 0;
}

public int
lower_rank(object who)
{
    int rank, who_rank;

    if (!who || who == query_shadow_who()) return 0;
    if (!query_lower_rank()) return 0;

    rank = query_mystic_rank();
    who_rank = who->query_mystic_rank();
    if (who_rank < MYSTIC_ARCHON || who_rank <= rank) return 0;

    set_rank(rank - 1);

    return 1;
}

public void
set_rank(int rank)
{
    query_shadow_who()->set_skill(MYSTIC_RANK, rank);
}

public int
query_spell_level()
{
   int rank, wis;
   object who = query_shadow_who();

   rank = query_mystic_rank();
   wis  = query_shadow_who()->query_stat(SS_WIS);

   if (!query_present_rank()) rank--;

   if (wis > SLEVELS[rank]) wis = SLEVELS[rank];

  if(query_mystic_rank() == 5 && wis > 119 && 
  who->query_skill(EXALT) < 1)
  { wis = 119; return wis; }
  if(query_mystic_rank() < 1 && who->query_skill(NOVICE) < 1)
   { wis = 10; return wis; }
   if(query_mystic_rank() < 1 && wis > 29)
   { wis = 29; return wis; }
  if(query_mystic_rank() == 1){
  if(who->query_skill(EXALT) < 1 && wis > 39)
  { wis = 39; return wis; }
if(who->query_skill(EXALT) == 1 && wis > 49)
  { wis = 49; return wis; }
}

  if(query_mystic_rank() == 2){
  if(who->query_skill(EXALT) < 1 && wis > 69)
  { wis = 69; return wis; }
if(who->query_skill(EXALT) == 1 && wis > 79)
  { wis = 79; return wis; }
}
   return wis;
}

public int
query_present_rank()
{
    int rank, occ, subrank;

    rank = query_mystic_rank();
    occ  = query_shadow_who()->query_stat(SS_OCCUP);

    if (rank <= MYSTIC_NOVITIATE) return 1;

    subrank = sizeof(LEVELS[rank-1]) - 1;
    if (occ > LEVELS[rank-1][subrank]) return 1;

    return 0;
}
