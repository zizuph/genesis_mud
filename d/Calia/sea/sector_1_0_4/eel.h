
/* 
   Include file for resetting a eel.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object eel; 

void
reset_room()
{
    if (!objectp(eel))
    {
         eel = clone_object(SEA_CREATURES+"eel"); 
         eel->move_living("into the sea", this_object()); 
     }
}

