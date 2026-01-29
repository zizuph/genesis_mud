inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
/* Prototypes */
void add_stuff();
void reset_room();

#define MAX_ORCS 10
#define MAX_TROLLS 3

   object balrog, *orcs = ({}), *trolls = ({});

void make_orcs();
void make_trolls();
void reset_room()
{
   make_orcs();
   make_trolls();
   add_stuff();
}

void
create_room()
{
   set_short("A hot steamy place, deep in the mines");
   set_long("The air is relatively cool and calm, "+
	    "though the steam does not go away entirely. "+
	    "Loud rumbling sounds nearly knock you off balance, "+
	    "and the steam becomes red briefly.\n");


   add_item(({"steam","ground","air"}),
   "The steam rises from the ground, heating the air in this place. "+
   "The ground here is pocked with small depressions, covered with a "+
   "thin film of water.\n");

   add_item(({"red glow","glow","sounds","sound"}),
   "The glow brightens and fades out of time with the low rumbling "+
   "sounds that echo from within the darkness.\n");

   add_item(({"water","film","depressions","depression","pock"}),
   "The water covering the pocked depressions is covered by a thick "+
   "red film that is only partly translucent. "+
   "The depressions are a bit bigger here, and too big to be footprints.\n");

   add_prop(ROOM_I_INSIDE, 1);


   set_noshow_obvious(1);
   reset_room();
}

void
add_stuff()
{
  object balrog;

   if(!find_living("gash"))
  {
     balrog = clone_object("/d/Shire/moria/npc/balrog");
       balrog->move(TO);

  }

}
void
make_trolls()
{
   int i;

   if(!sizeof(trolls))
   trolls = allocate(MAX_TROLLS);
   for(i = 0; i < MAX_TROLLS; i++)
     if(!trolls[i])
     {
       trolls[i] = clone_object("/d/Shire/moria/npc/cavetroll");
       balrog->team_join(trolls[i]);
     trolls[i]->move(TO);
       tell_room(TO, capitalize(LANG_ADDART(trolls[i]->query_nonmet_name()))+
       " comes running in, screaming: Baruk Khazad!\n");
   }
    else
       if(trolls[i]->query_leader() != balrog)
       balrog->team_join(trolls[i]);

}


void
make_orcs()
{
   int i;


   if(!sizeof(orcs))
     orcs = allocate(MAX_ORCS);
     for(i = 0; i < MAX_ORCS; i++)
       if(!orcs[i])
      {
       orcs[i] = clone_object("/d/Shire/orcmaker/orcmaker");
       balrog->team_join(orcs[i]);
       orcs[i]->set_type(9);
       orcs[i]->set_power(200 + random(100));
       orcs[i]->set_random_move(1000000);
       orcs[i]->move(TO);
    tell_room(TO, capitalize(LANG_ADDART(orcs[i]->query_nonmet_name()))+
     " enters through the mist.\n");
     }

   else
     if(orcs[i]->query_leader() != balrog)
     balrog->team_join(orcs[i]);

}
