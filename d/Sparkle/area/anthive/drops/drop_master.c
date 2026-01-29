
#include <stdproperties.h>     /* Where the properties are defined. */
#include <wa_types.h>          /* Where weapon and armour defs are. */
#include <ss_types.h>          /* Where the skill defines are.      */
#include <tasks.h>             /* For using resolve_task in wear()  */
#include <formulas.h>          /* Where the formulas for value, 
                                * weight, volume, etc are located.  */
#include "../defs.h"

#define LOG(x,y)       write_file(LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )            

#define  P_COMMON      DROPS_DIR + "common/"
#define  P_UNCOMMON    DROPS_DIR + "uncommon/"
#define  P_RARE        DROPS_DIR + "rare/"
#define  P_EPIC        DROPS_DIR + "epic/"
#define  P_LEGENDARY   DROPS_DIR + "legendary/"
#define  P_ARTIFACT    DROPS_DIR + "artifact/"

#define  P_TAROT       DROPS_DIR + "tarotdeck/"


string *common =    ({"minor_heal_pot"});
                   
string *uncommon =  ({"major_heal_pot"});
                   
string *rare =      ({"spider_slippers"});
                                     
                   
string *epic =      ({"epic_weapon"});
                   
string *legendary = ({"legendary_weapon"});
                   
string *artifact =  ({"artifact_weapon"});


// The tarot

string *tarot =     ({"tarot_1",
                      "tarot_2",
                      "tarot_3",
                      "tarot_4",
                      "tarot_5",
                      "tarot_6",
                      "tarot_7",
                      "tarot_8",
                      "tarot_9",
                      "tarot_10",
                      "tarot_11",
                      "tarot_12",
                      "tarot_13",
                      "tarot_14",
                      "tarot_15",
                      "tarot_16",
                      "tarot_17",
                      "tarot_18",
                      "tarot_19",
                      "tarot_20",
                      "tarot_21",
                      "tarot_22"});
  
  
  
// The tarot deck drop

void
tarot_drop()
{
 
  if (random(300) <= 1)
  {  
  	object tarot_drop;
  	
  	                
   tarot_drop = clone_object(P_TAROT + tarot[random(sizeof(tarot))]);

   LOG("tarot_drop", capitalize(this_player()->query_real_name()) +
                " dropped a tarot card in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  tarot_drop->move(this_object());
  
  
  }

}
  
                                
                                
// Common drops
void
common_drop()
{
 
  if (random(COMMON_DROPCHANCE) <= 1)
  {  
  	object common_drop;
  	
  	                
   common_drop = clone_object(P_COMMON + common[random(sizeof(common))]);

   LOG("common_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + common_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  common_drop->move(this_object());
  
  
  }

}


// Uncommon drops
void
uncommon_drop()
{
	
 
  if (random(UNCOMMON_DROPCHANCE) <= 1)
  {                  
  	object uncommon_drop;
  	
  	                
   uncommon_drop = clone_object(P_UNCOMMON + uncommon[random(sizeof(uncommon))]);

   LOG("uncommon_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + uncommon_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  uncommon_drop->move(this_object());
  
  }

}


// Rare drops
void
rare_drop()
{
  	
 
  if (random(RARE_DROPCHANCE) <= 1)
  {                  
  	object rare_drop;
  	
  	                
   rare_drop = clone_object(P_RARE + rare[random(sizeof(rare))]);

   LOG("rare_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + rare_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  rare_drop->move(this_object());
 
  }

}


// Epic drops
void
epic_drop()
{
 	
 	
  if (random(EPIC_DROPCHANCE) <= 1)
  {                  
  	object epic_drop;
  	
  	                
   epic_drop = clone_object(P_EPIC + epic[random(sizeof(epic))]);

   LOG("epic_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + epic_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  epic_drop->move(this_object());
  
  }

}


// Legendary drops
void
legendary_drop()
{
   	
   	
  if (random(LEGENDARY_DROPCHANCE) <= 1)
  {                  
  	object legendary_drop;
  	
  	                
   legendary_drop = clone_object(P_LEGENDARY + legendary[random(sizeof(legendary))]);

   LOG("legendary_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + legendary_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  legendary_drop->move(this_object());
  
  }

}


// Artifact drops
void
artifact_drop()
{
 	

  if (random(ARTIFACT_DROPCHANCE) <= 1)
  {                
  	object artifact_drop;
  	
  	                
   artifact_drop = clone_object(P_ARTIFACT + artifact[random(sizeof(artifact))]);

   LOG("artifact_drop", capitalize(this_player()->query_real_name()) +
                " dropped a " + artifact_drop->query_short() + " in " + 
              file_name(environment(this_player())) + " at " + 
              ctime(time()) + ".\n");
              
  artifact_drop->move(this_object());
  
  }

}


//////////////

void
deluxe_drop()
{
	common_drop();
	uncommon_drop();
	
	tarot_drop();
	
	rare_drop();
	epic_drop();
	legendary_drop();
	artifact_drop();
	
}







    
