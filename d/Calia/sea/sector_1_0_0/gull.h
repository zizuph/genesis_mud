
/* 
   Include file for resetting a seagull.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object seagull; 
object seagull2;

void
reset_room()
{
    if (!objectp(seagull))
    {
         seagull = clone_object(SEA_CREATURES+"gull"); 
         seagull->move_living("into the sea", this_object()); 
     }
    if (!objectp(seagull2))
    {
        seagull2 = clone_object(SEA_CREATURES+"gull");
        seagull2->move_living("into the sea", this_object());
    }
}

