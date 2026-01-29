
/* 
   Include file for resetting a turtle.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object turtle; 

void
reset_room()
{
     if (!objectp(turtle)) { 
         turtle = clone_object(SEA_CREATURES+"turtle"); 
         turtle->move_living("into the sea", this_object()); 
     }
}

