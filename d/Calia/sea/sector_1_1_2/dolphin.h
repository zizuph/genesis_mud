
/* 
   Include file for resetting a dolphin.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object dolphin; 

void
reset_room()
{
    if (!objectp(dolphin))
    {
         dolphin = clone_object(SEA_CREATURES+"dolphin"); 
         dolphin->move_living("into the sea", this_object()); 
     }
}

