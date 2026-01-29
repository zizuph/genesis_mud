
/* 
   Include file for resetting a shark.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object shark; 

void
reset_room()
{
    if (!objectp(shark))
    {
         shark = clone_object(SEA_CREATURES+"shark"); 
         shark->move_living("into the sea", this_object()); 
     }
}

