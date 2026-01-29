/* Faramir now lives with the ithilien company.
 *  This room is defunct.
 */
inherit "/d/Gondor/common/room";

create_room()
{
  set_short("dummy room for faramir to wait for tasks");
  set_long("dummy room for faramir to wait for tasks\n");
}

enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(!ob || !from || !interactive(ob)) return;
  ob->move_living("M",from);
  return;
}
