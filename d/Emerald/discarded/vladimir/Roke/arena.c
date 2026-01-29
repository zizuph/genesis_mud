/* Vladimir put in the date */

inherit "/std/room.c";

void
create_room()
{
set_name("Arena");
set_long(
         "This room is black, with splatters of blood all over "+
         "the place. It stinks of death and rotten flesh, but "+
         "oddly enough, you see no corpse. Not even a decaying "+
         "bone. Just blood, the ever present blood. There is "+
         "no escape from this room.\n");

//note what I've done up there. You don't need BS or break string anymore...
//the compiler does it for you.
//Try to keep the indenting easy to follow. I'm not much one to comment mind
//you...My indenting arouses lots of comments from other wizes...
//Sir Erane.

}
void
init()
{
::init();
write("You feel as though Death had been here quite recently.\n");
}
