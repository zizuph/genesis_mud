/* Name      : /d/Gondor/harondor/room/camp/npc_cloning.c
 * Purpose   : The file handling the npc cloning.
 *             Simply include this file and you can clone 
 *             NPC's very conveniently.
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 * 
 *
 *   Modified: Sir Toby, Gondor Domain, 2006-07-31
 *                       Updated to support having various numbers of guard.c
 *                       and haradrim.c in a room (for the campE01.c and campE02.c)
 *             Sir Toby, Gondor Domain, 2006-08-26
 *                       Updated the cloning, corrected a bug that cloned
 *                       one more of the regular haradrim every reset.
 */

#pragma strict_types

object leader, *har_s = ({});

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - npc_cloning]: " + x + "\n")

/* Function name: make_haradrim
 * Description  : clones haradrims to the calling room
 * Arguments    : int num_harad - mandatory, int harad_type - mandatory
 *                type: 1 = guard 0 = regular warrior
 * Returns      : 
 */
int 
make_haradrim(object *har_s, int harad_type)
{
   int i, s = sizeof(har_s) - 1;  

   if(s < 1)
      return 0;

   leader = present("_camp_leader_");

   if(harad_type)
   {
      if(!leader)
	  {
          if(!objectp(leader))
          {
             leader = clone_object(HAR_RM_NPC_DIR + "guard");
             leader->set_title(one_of_list(HARAD_OFFICER));
             leader->add_name("_stopping_npc");
             leader->add_name("leader");
             leader->add_name("officer");
             leader->add_name("_camp_leader_");
             leader->arm_me();
             leader->move(TO);
             tell_room(TO,CAP(LANG_ADDART(leader->query_nonmet_name())) +
                 " charges in and prepares for battle.\n");
          }
	   }
	
	   for(i = 0; i < s; i++)
	   {
          if(!objectp(har_s[i]))
          { 
             har_s[i] = clone_object(HAR_RM_NPC_DIR + "guard");
             har_s[i]->add_name("_stopping_npc");
             har_s[i]->arm_me();
             har_s[i]->move(TO);
             leader->team_join(har_s[i]);
             tell_room(TO,CAP(LANG_ADDART(har_s[i]->query_nonmet_name()))+
                 " charges in, preparing for battle.\n");
          }
	   }
    }
    else
    {
	   if(!leader)
	   {
          if(!objectp(leader))
          {
             leader = clone_object(HAR_RM_NPC_DIR + "haradrim");
             leader->set_title(one_of_list(HARAD_OFFICER));
             leader->add_name("_stopping_npc");
             leader->add_name("leader");
             leader->add_name("officer");
             leader->add_name("_camp_leader_");
             leader->arm_me();
             leader->move(TO);
             tell_room(TO,CAP(LANG_ADDART(leader->query_nonmet_name())) +
	             " charges in and prepares for battle.\n");
           }
	   }
	
	   for(i = 0; i < s; i++)
	   {
          if(!objectp(har_s[i]))
          { 
             har_s[i] = clone_object(HAR_RM_NPC_DIR + "haradrim");
             har_s[i]->add_name("_stopping_npc");
             har_s[i]->arm_me();
             har_s[i]->move(TO);
             leader->team_join(har_s[i]);
             tell_room(TO,CAP(LANG_ADDART(har_s[i]->query_nonmet_name()))+
	              " charges in, preparing for battle.\n");
           }
	   }

   }
   return 1;
}

