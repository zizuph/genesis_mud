inherit "/std/monster";
#include "defs.h";

create_monster(){

set_race_name("spirit");
set_name("spirit");
set_adj("ancient holy");


stuff();
}

stuff(){

tell_room(ENV(TP), TO->query_prop("caller") + ", I have heard thy call.... ");
}

