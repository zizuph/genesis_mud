
/* 
   Include file for resetting a sting ray.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object sray; 

void
reset_room()
{
    if (!objectp(sray))
    {
         sray = clone_object(SEA_CREATURES+"sray"); 
         sray->move_living("into the sea", this_object()); 
     }
}

