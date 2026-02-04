/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/armour";

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#define TOWN_DIR "/d/Terel/common/town/"
#define VALLEY_DIR "/d/Terel/mecien/valley/"
#define DOMAIN_DIR "/d/Terel/"

#define TO  this_object()
#define TP  this_player()
#define ENV environment

public int
in_here(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
  if(player->query_alignment() > -100) return 0;
    if(ENV(player) == ENV(TP)) return 1;
}
public int
in_shrine(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
  if(player->query_alignment() > -100) return 0;
   return wildmatch(GUILD_DIR + "*", file_name(ENV(player)));
}

public int
in_town(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
  if(player->query_alignment() > -100) return 0;
   return wildmatch(TOWN_DIR + "*", file_name(ENV(player)));
}
public int
in_valley(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
  if(player->query_alignment() > -100) return 0;
   return wildmatch(VALLEY_DIR + "*", file_name(ENV(player)));
}
public int
in_terel(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
  if(player->query_alignment() > -100) return 0;
   return wildmatch(DOMAIN_DIR + "*", file_name(ENV(player)));
}
public mixed
malo(string str)
{
  string place;
   string *places;
   object *players;
   
    places = ({ "town", "Calathin", "terel", "Terel", "Valley", "valley",
     "shrine"});
  if(!present(MYSTIC_AMULET, TP)) return "You will need the amulet.\n";
  if(TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_ELEMENT_LIFE) <
   random(70)) return "You fail to gain any vision.\n";
  if(TP->query_mana() < 25) return "You do not have the strength.\n";
  if(str){
  if(member_array(str, places) < 0) return "Search where for evil?\n";
   }
   say(QCTNAME(TP) + " places " + TP->query_possessive() + " hand upon " +
      TP->query_possessive() + " heart and intones some ancient words.\n");
   TP->catch_msg("Placing your hand upon your heart, you gaze into the spirit world for the presence of evil.\n");
   
  TP->add_mana(-15);
   /* Filter all users() to see who is in the Shrine and who is not. If
   * there is no-one in the Shrine, tell the player.
   */
   if(str == "Calathin") str = "town";
  if(str == "Terel") str = "terel";
  if(!str) players = filter(users(), in_here);
   if(str == "shrine") players = filter(users(), in_shrine);
   if(str == "valley") players = filter(users(), in_valley);
   if(str == "town") players = filter(users(), in_town);
   if(str == "terel") players = filter(users(), in_terel);
   if (!sizeof(players))
      {
      write("You do not sense any evil.\n");
      return 1;
   }
   
   /* players->query_the_name(TP) will give an array of the names of the
   * players who are in the Shrine if we know them. COMPOSITE_WORDS puts
      * that list in a nice string of 'a, b and c'. Then, if it is singular,
      * use 'is', else 'are'.
      */
   if(str == "town") place = "the town of Calathin";
   if(str == "valley") place = "the Valley of the Ancients";
   if(str == "shrine")  place = "the sacred shrine";
   if(str == "terel") place = "the lands of Terel";
if(!str){
   write("You sense that " + COMPOSITE_WORDS(players->query_the_name(TP)) +
      ((sizeof(players) == 1) ? " is" : " are") +
   " evil.\n");
   return 1;
}
/*
   write("You sense that " + COMPOSITE_WORDS(players->query_the_name(TP)) +
      ((sizeof(players) == 1) ? " is" : " are") +
*/
   write("You sense that there is evil" +
   " within " + place + ".\n");
   return 1;
}

