inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
static object *monks=allocate(3);
static object leader;
 
void
reset_room()
{
    int i=sizeof(monks);
 
    if (!leader)
         {
           leader = clone_object(TEMPLE_DIR + "npc/abbed");
           leader->arm_me();
           leader->move_living("into a room", this_object());
         }
    for (i=0 ; i<4 ; i++)
      if (!monks[i])
       {
         monks[i]=clone_object(TEMPLE_DIR + "npc/monk");
         monks[i]->arm_me();
         monks[i]->move_living("into a room", this_object());
         leader->team_join(monks[i]);
       }
}
 
void
create_room()
{
    set_short("Eastern end of Courtyard");
    set_long("   You are standing in the eastern end of the "+
             "courtyard, among a crowd of doomed players. To the west there "+
             "is a well.\n\n");
 
    set_long("   You are standing in the eastern end of the "+
             "courtyard. Only few figures of monks are "+
             "seen around, since due to the hot sun the place is quite "+
             "warmed. To the west there is a well.\n\n");
 
    add_exit(TEMPLE_DIR + "court_ne", "north", 0);
    add_exit(TEMPLE_DIR + "court_w", "west", 0);
    add_exit(TEMPLE_DIR + "court_se", "south", 0);
 
    set_alarm(1.0,0.0,reset_room);
}
 
void
questdone()
{
  int i;
 
  tell_room(TO,"Abbot smiles happily, then hurries away, " +
             "mumbling happily about his newly acquired ring.\n");
  leader->remove_object();
  for (i=0 ; i<sizeof(monks); i++)
      if (monks[i])
       {
         monks[i]->remove_object();
         tell_room(TO,"The monk leaves following the abbot.\n");
       }
}
