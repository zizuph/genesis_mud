inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){
set_short("Armory Storage");

clone_object(PATH + "waterskin")->move(this_object());
clone_object(PATH + "pot")->move(this_object());
}

