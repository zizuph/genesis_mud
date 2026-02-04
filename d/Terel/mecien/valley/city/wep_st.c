inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){
set_short("Armory Storage");

clone_object(PATH + "halberd")->move(this_object());
}

