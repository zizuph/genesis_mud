/*
 * /d/Sparkle/area/spiderlair/drops/drop_master.c
 *
 * This is the dropmaster for the creatures in the spiderlair.
 * Based on various chances, creatures will drop different loot
 * depending on random chance.
 *
 * Nerull, 28/2-09.
 */
 
#include <stdproperties.h>     
#include <wa_types.h>          
#include <ss_types.h>          
#include <tasks.h>             
#include <formulas.h>  

#include "../common_drops.h";
#include "../uncommon_drops.h";
#include "../rare_drops.h";
#include "../epic_drops.h";
#include "../legendary_drops.h";
#include "../artifact_drops.h";   
#include "../dungeon_tokens.h";   
                                
#include "../defs.h"

#define LOG(x,y)       write_file(LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )            

// The token drops
void
spider_token_drop(int i)
{
    
    seteuid(getuid());
    
    if (i == 1)
    {
    		object token_drop;
  	  	                
        token_drop = clone_object(P_TOKEN +
        dungeon_token[random(sizeof(dungeon_token))]);

        LOG("token_drop", capitalize(this_player()->query_real_name())+
        " dropped a "+token_drop->query_short()+" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        token_drop->move(this_object(), 1);
        
        return;        
    }
 
    if (random(DUNGEONTOKEN_DROPCHANCE) <= 1)
    {  
      	object token_drop;
  	  	                
        token_drop = clone_object(P_TOKEN +
        dungeon_token[random(sizeof(dungeon_token))]);

        LOG("token_drop", capitalize(this_player()->query_real_name())+
        " dropped a "+token_drop->query_short()+" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        token_drop->move(this_object(), 1);
    
    }
}
  
                                
                                
// Common drops
void
common_drop(int i)
{
 
		if (i == 1)
    {
    		object common_drop;
  	  	                
        common_drop = clone_object(P_COMMON +
        common[random(sizeof(common))]);

        LOG("common_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + common_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        common_drop->move(this_object(), 1);
        
        return;        
    }
 
    if (random(COMMON_DROPCHANCE) <= 1)
    {  
  	    object common_drop;
  	 	                
        common_drop = clone_object(P_COMMON + 
        common[random(sizeof(common))]);

        LOG("common_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + common_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        common_drop->move(this_object(), 1);
    
    }
}


// Uncommon drops
void
uncommon_drop(int i)
{
	
    if (i == 1)
    {
    		object uncommon_drop;
  	  	                
        uncommon_drop = clone_object(P_UNCOMMON +
        uncommon[random(sizeof(uncommon))]);

        LOG("uncommon_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + uncommon_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        uncommon_drop->move(this_object(), 1);
        
        return;        
    }

    if (random(UNCOMMON_DROPCHANCE) <= 1)
    {                  
  	    object uncommon_drop;
  	  	                
        uncommon_drop = clone_object(P_UNCOMMON + 
        uncommon[random(sizeof(uncommon))]);

        LOG("uncommon_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + uncommon_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        uncommon_drop->move(this_object(), 1);
  
    }
}


// Rare drops
void
rare_drop(int i)
{
  	   	 
  	if (i == 1)
    {
    		object rare_drop;
  	  	                
        rare_drop = clone_object(P_RARE +
        rare[random(sizeof(rare))]);

        LOG("rare_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + rare_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        rare_drop->move(this_object(), 1);
        
        return;        
    }
  	 
    if (random(RARE_DROPCHANCE) <= 1)
    {                  
    	  object rare_drop;
  	  	                
        rare_drop = clone_object(P_RARE + rare[random(sizeof(rare))]);

        LOG("rare_drop", capitalize(this_player()->query_real_name()) +
        " dropped a " + rare_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        rare_drop->move(this_object(), 1); 
    }
}


// Epic drops
void
epic_drop(int i)
{
 	 	
 	 	if (i == 1)
    {
    		object epic_drop;
  	  	                
        epic_drop = clone_object(P_EPIC +
        epic[random(sizeof(epic))]);

        LOG("epic_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + epic_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        epic_drop->move(this_object(), 1);
        
        return;        
    }
 	 	
    if (random(EPIC_DROPCHANCE) <= 1)
    {                  
  	    object epic_drop;
  	  	                
        epic_drop = clone_object(P_EPIC + epic[random(sizeof(epic))]);

        LOG("epic_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + epic_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
				epic_drop->move(this_object(), 1);  
		}
}


// Legendary drops
void
legendary_drop(int i)
{
   	  	
   	if (i == 1)
    {
    		object legendary_drop;
  	  	                
        legendary_drop = clone_object(P_LEGENDARY +
        legendary[random(sizeof(legendary))]);

        LOG("legendary_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + legendary_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        legendary_drop->move(this_object(), 1);
        
        return;        
    }
   	  	
    if (random(LEGENDARY_DROPCHANCE) <= 1)
		{                  
  	    object legendary_drop;
  	  	                
        legendary_drop = clone_object(P_LEGENDARY + 
        legendary[random(sizeof(legendary))]);

        LOG("legendary_drop", capitalize(this_player()->
        query_real_name()) +
        " dropped a " + legendary_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
				legendary_drop->move(this_object(), 1);  
		}
}


// Artifact drops
void
artifact_drop(int i)
{
 	
 	  if (i == 1)
    {
    		object artifact_drop;
  	  	                
        artifact_drop = clone_object(P_ARTIFACT +
        artifact[random(sizeof(artifact))]);

        LOG("artifact_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + artifact_drop->query_short() +" in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        artifact_drop->move(this_object(), 1);
        
        return;        
    }
 	
    if (random(ARTIFACT_DROPCHANCE) <= 1)
    {                
  	    object artifact_drop;
  	  	                
        artifact_drop = clone_object(P_ARTIFACT + 
        artifact[random(sizeof(artifact))]);

        LOG("artifact_drop", capitalize(this_player()->query_real_name())+
        " dropped a " + artifact_drop->query_short() + " in " + 
        file_name(environment(this_player())) + " at " + 
        ctime(time()) + ".\n");
              
        artifact_drop->move(this_object(), 1);  
    }

}


/* This function added in the do_die-routine of an npc
 * will roll the dice in every category.
 */
void
deluxe_drop()
{
	
	  spider_token_drop(0);
	  
	  common_drop(0);
	  uncommon_drop(0);		  	
  	rare_drop(0);
  	epic_drop(0);
  	legendary_drop(0);
  	artifact_drop(0);	
}







    
