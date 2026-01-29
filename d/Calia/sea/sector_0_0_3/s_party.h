
/* 
   Include file for resetting a mermaid and warhorse.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object s_mermaid;
object s_triton;
object warhorse;

void
reset_room()
{
    if (!objectp(s_mermaid))
    {
         s_mermaid = clone_object(SEA_CREATURES+"s_mermaid"); 
         s_mermaid->move_living("into the sea", this_object()); 
    }
    if (!objectp(warhorse))
    {
        warhorse = clone_object(SEA_CREATURES+"warhorse");
        warhorse->move_living("into the sea", this_object());
    }
    if (!objectp(s_triton))
    {
        warhorse = clone_object(SEA_CREATURES+"s_triton");
        warhorse->move_living("into the sea", this_object());
    }
}

