
/* 
   Include file for resetting a goldfish.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object goldfish; 
object goldfish2;
object goldfish3;

void
reset_room()
{
    if (!objectp(goldfish))
    {
        goldfish = clone_object(SEA_CREATURES+"goldfish");
         goldfish->move_living("into the sea", this_object()); 
    }
    if (!objectp(goldfish2))
    {
        goldfish2 = clone_object(SEA_CREATURES+"goldfish");
        goldfish2->move_living("into the sea", this_object());
    }
    if (!objectp(goldfish3))
    {
        goldfish3 = clone_object(SEA_CREATURES+"goldfish");
        goldfish3->move_living("into the sea", this_object());
    }
}

