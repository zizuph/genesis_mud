inherit "/std/room";

ceate_room() {
  set_short("The Temporary-room");
  set_long("This room is only to be used as a temporary place to stay\n"+
    "for npc's who are waiting to be moved somewhere else.\n");
  add_exit("/d/Gondor/minas/rooms/mtoffice","down",0);
}
