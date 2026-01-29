inherit "/d/Gondor/common/room";

object door;

create_room()
{
  set_short("The Shades private room");
  set_long("This small room is completely bare.\n");
  add_exit("/d/Gondor/minas/shades/office","east",0);
  door = clone_object("/d/Gondor/minas/shades/office_door");
  door->move(this_object());
}
