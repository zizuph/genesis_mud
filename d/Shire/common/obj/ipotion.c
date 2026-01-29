/*
This is a potion of invisibility.
Code stolen from yodah.
Written by Merrygrin
*/

inherit "/d/Shire/open/potion";

#include "macros.h"
#include <stdproperties.h>

#define TP   this_player()

create_potion() {
  ::create_potion();
  seteuid(getuid());
  set_duration(25);
  set_color("white");
  set_effectshort("invisibility");
  set_effectlong("This potion will temporarily make the subject invisible.\n");
  set_smell("rotten");
  set_taste("honey");
  set_identified(0);
  /*set_identvalue(600); */
  add_prop(OBJ_I_VALUE, 100);

}

int end_effect() {

  if (TP->query_invis()) {
    TP->set_invis(0);
    write("You are now visible.\n");
    say(TP->query_mm_in() + "\n");
  }
  ::end_effect();
}

int start_effect() {

  ::start_effect();
  write("Yumi! This potion tasted GOOOOOD!\n");
  if(this_player()->query_invis())
    write("Nothing seems to happen though.\n");
  else {
    write("OOOPS! Where did my body go?\n");
    this_player()->set_invis(1);
    write("You are now invisible.\n");
    say(QCTNAME(TP) + " " + "fades away and disappears\n");
  }

}
 
 
 
 
 
 
 
 
 
 
 
 
