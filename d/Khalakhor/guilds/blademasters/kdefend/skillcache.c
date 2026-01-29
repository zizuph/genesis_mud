/* 
  basically we keep a list of how many times they've been hit each way and
  use that plus their skills, stats, guild exp, whatever to adapt their
  parrying to the blow that's being made.

  what this file does is keep a cache of member-damage type hashes
*/

#pragma no_inherit
#pragma no_clone
#pragma strict_types

#include "skillcache.h"

mapping name_cacheobj = ([ ]);
mapping locked_names = ([ ]);

int lock(string name);
int unlock(string name);

object get_member(string name)
{
   object m;

   if(!strlen(name))
      return 0;

   if(objectp(name_cacheobj[name]))
      return name_cacheobj[name];

   m = clone_object(CACHE_MEMBER_OBJ);
   m->load(name);
   name_cacheobj[name] = m;
   return m;
}

int lock(string name)
{
   if(!strlen(name)) return 0;

   if(locked_names[name]) return -1;

   locked_names[name] = 1;
   return 1;
}

int unlock(string name)
{
   if(!strlen(name)) return 0;

   if(locked_names[name]) {
      locked_names = m_delete(locked_names, name);
      return 1;
   }

   return -1;
}

void garbage_collect()
{
   int i;
   string *keys = m_indices(name_cacheobj);

   for(i=0; i<sizeof(keys); i++) {
      if(lock(keys[i])) {
         if(!find_player(keys[i])) {
            if(objectp(name_cacheobj[keys[i]])) {
               name_cacheobj[keys[i]]->remove_object();
            }
            name_cacheobj = m_delete(name_cacheobj, keys[i]);
         }

         unlock(keys[i]);
      }
   }
}

void
remove_object()
{
   int i;
   string *keys = m_indices(name_cacheobj);

   for(i=0; i<sizeof(keys); i++) {
      name_cacheobj[keys[i]]->remove_object();
      name_cacheobj = m_delete(name_cacheobj, keys[i]);
   }

   destruct();
}
