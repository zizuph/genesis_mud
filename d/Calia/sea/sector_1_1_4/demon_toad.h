
/* 
   Include file for resetting a demon toad.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object demon_toad; 

void
reset_room()
{
    if (!objectp(demon_toad))
    {
         demon_toad = clone_object(SEA_CREATURES+"demon_toad"); 
         demon_toad->move_living("into the sea", this_object()); 
     }
}

