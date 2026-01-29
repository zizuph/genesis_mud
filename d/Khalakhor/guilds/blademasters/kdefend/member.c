#pragma strict_types

#include <macros.h>
#include "skillcache.h"

mapping damagetype_hits = ([ ]);
mapping hitloc_hits = ([ ]);
private string objectid = 0;
string name;

void add_dt_hit(int dt)
{
   if(damagetype_hits[dt]) {
      damagetype_hits[dt]++;
   } else {
      damagetype_hits[dt] = 1;
   }
}

int query_dt_hits(int dt)
{
   if(damagetype_hits[dt])
      return damagetype_hits[dt];

   return 0;
}

void add_hl_hit(int hitloc)
{
   if(hitloc_hits[hitloc]) {
      hitloc_hits[hitloc]++;
   } else {
      hitloc_hits[hitloc] = 1;
   }
}

int query_hl_hits(int hitloc)
{
   if(hitloc_hits[hitloc])
      return hitloc_hits[hitloc];

   return 0;
}

int load(string str)
{
   name = str;

   if(find_player(name)) {
      objectid = OB_NUM(find_player(name));
   }

   if(file_size(MEMBER_FILE(name))) {
      restore_object(MEMBER_FILE(name));
   }
}

void unload()
{
   if(strlen(name)) {
      save_object(MEMBER_FILE(name));
   }
}

void
remove_object()
{
   unload();
   destruct();
}
