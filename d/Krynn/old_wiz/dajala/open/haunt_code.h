/* Code to create a haunting when an NPC dies. At the moment this is
   only placed in shopkeepers in Gelan, and the guide. It will hopefully
   deter players from killing them and thus depriving others of their
   services. 

   Coder: Maniac
   Revision history:
                 6.9.94      Created                          Maniac

*/

/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object(OBJECT("ghost")); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ::do_die(killer);

}



