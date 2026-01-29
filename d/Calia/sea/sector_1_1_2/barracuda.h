
/* 
   Include file for resetting a barracuda.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object barracuda; 

void
reset_room()
{
    if (!objectp(barracuda))
    {
         barracuda = clone_object(SEA_CREATURES+"barracuda"); 
         barracuda->move_living("into the sea", this_object()); 
     }
}

