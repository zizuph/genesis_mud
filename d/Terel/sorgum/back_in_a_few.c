inherit "/std/room";


create_room()
{

  set_short("break room.");
  set_long(break_string("This is Sorgum's break room. "
	+ "This is where Sorgum comes when he may be away from his "
        + "workstation or busy working in another window.  He should be "
	+ "paying attention again in a few minutes\n", 69));
  add_exit("/d/Terel/sorgum/workroom", "workroom", 0);       
}
