
/* 
   Include file for resetting a small water kroug.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object wkroug; 

void
reset_room()
{
     if (!objectp(wkroug)) { 
         wkroug = clone_object(SEA_CREATURES+"small_wkroug"); 
         wkroug->arm_me(); 
         wkroug->move_living("into the sea", this_object()); 
     }
}

