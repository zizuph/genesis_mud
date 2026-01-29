inherit "/std/room";

#include <macros.h>

#include "defs.h"

#define SOBJ ISLAND_STRHOLD+"server"
#define FORGET_TIME 604800

mapping enemy;

void check_forget()
{
 mixed *ind;
 int i;
 int tm;

 ind=m_indexes(enemy);
 for(i=0;i<sizeof(ind);i++) 
  {
   tm=enemy[ind[i]];
   if((time()-tm)>=FORGET_TIME) enemy=m_delete(enemy,ind[i]);
  }
 save_object(SOBJ);
}

void create_room()
{
 enemy=([]);
 restore_object(SOBJ);

 check_forget();
}

void add_enemy(string name)
{
 if(member_array(name,m_indexes(enemy))!=-1)
  {
   enemy[name]=time();
   return;
  }

 if(!find_player(name)) return;

 enemy+=([ name:time() ]);
 save_object(SOBJ);
}

void remove_enemy(string name)
{
 enemy=m_delete(enemy,name);
 save_object(SOBJ);
}

string *query_enemies() { return m_indexes(enemy); }

int is_enemy(string name)
{
 return (member_array(name,m_indexes(enemy))==-1 ? 0 : 1);
}

void clear() 
{
 enemy=([]);
 save_object(SOBJ);
}

string *who_is_in()
{
 int i;
 object *pl;
 string *res=({});

 pl=users();
 for(i=0;i<sizeof(pl);i++)
   if(ENV(pl[i])->query_stronghold_room())
     res+=({ pl[i]->query_real_name() });

 return res;
}

void throw_out()
{
 string *in;
 int i;
 object pl;

 in=who_is_in();
 for(i=0;i<sizeof(in);i++)
  {
   pl=find_player(in[i]);
   if(!pl) continue;
   pl->catch_msg("Suddenly you hear the sound of alarm!\n"+
     "You decide to run before kargs find and kill you!\n");
   tell_room(ENV(pl),QCTNAME(pl)+" runs out.\n",pl);
   pl->move_living("M",ISLAND_DIR+"rooms/forest/path25");
   tell_room(ENV(pl),QCTNAME(pl)+" runs in.\n",pl);
  }
}

