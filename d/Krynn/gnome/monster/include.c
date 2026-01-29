/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object(TDIR + "monster/ghost"); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ghost->set_inform_msg("YouDeprivedMeOfThePossibilityTo"
	+ "FulfillMyOfficeInTheGuild.\nYouWillSurelyPay.\n");
  ::do_die(killer);

}
