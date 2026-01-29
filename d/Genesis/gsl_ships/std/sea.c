/*
 * A general ocean room
 * There is only one room for the whole grid, but the players
 * arrive into it only in containers, so they are never aware
 * there're many of them in it, unless their coordinates coincide
 */

inherit "/std/room";

void
create_room () {

  set_short("A sea square");
  set_long("A stretch of water in every direction\n");
}

