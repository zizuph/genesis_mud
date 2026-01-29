/* to be included in all olive groves in Argos */
/* NOTE: Calling procedure must remember to put NUM_OLIVES = MAX_OLIVES */
/* in the reset room procedure, or the olives won't return at reset     */
 
#define MAX_OLIVES 10
int NUM_OLIVES;
object olive=0;
 
/* Allows the player to pick an olive from the tree */
pick_olive()
{
   if (NUM_OLIVES < 1) {
      write("All the olives you can reach have been picked.\n");
      return 1;
   }
   olive = clone_object(OBJ_DIR+"olive.c");
   write("You pick an olive from the tree.\n");
   olive->move(this_player());
   NUM_OLIVES = NUM_OLIVES - 1;
   return 1;
}
 
/* Allows the player to pick all the olives from the tree */
pick_olives()
{
   int i;
 
   if (NUM_OLIVES < 1) {
      write("All the olives you can reach have been picked.\n");
      return 1;
   }
 
   for (i=0; i<NUM_OLIVES; i++)
      set_alarm(1.0,0.0,"pick_olive");
   return 1;
}
