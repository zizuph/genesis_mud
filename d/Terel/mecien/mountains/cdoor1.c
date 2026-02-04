/* An example door made by Nick, 1991-12-19 */

#define PATH "/d/Terel/mecien/mountains"

inherit "/std/door";

create_door() {

    /* If you do this you'll get the default descriptions of the door, if you do
       this you only have to set the following functions.
    */
  ::create_door();

    /* You need an id  
    */
  set_door_id("cellardoor");

    /* Here you decide wich command will take you through the door, 'enter' is no
       good pass command, at least not yet, since argument is not tested. If the
       first pass command has only one or two letters in it the second pass command
       will be used in the standard description of the door.
    */
  set_pass_command(({"n","north"}));


    /* The name of the door. The first name in the array will be used in the
       standard description of the door.
    */
  set_door_name(({"iron door","door"}));

    /* This is the room on the other side of the door.
    */
  set_other_room(PATH + "/cellar2");

    /* If you want to have a look on the door you need to define the following
       sets too.
    */
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

  set_open(0);       
  set_locked(1);       

}
