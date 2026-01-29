
/* 
   Include file for resetting a seasnake.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object seasnake; 

void
reset_room()
{
    if (!objectp(seasnake))
    {
         seasnake = clone_object(SEA_CREATURES+"seasnake"); 
         seasnake->move_living("into the sea", this_object()); 
     }
}

