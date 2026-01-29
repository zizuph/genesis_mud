
/* 
   Include file for resetting a manta ray.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object mray; 

void
reset_room()
{
    if (!objectp(mray))
    {
         mray = clone_object(SEA_CREATURES+"mray"); 
         mray->move_living("into the sea", this_object()); 
     }
}

