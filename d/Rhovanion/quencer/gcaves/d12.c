/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR              MISTY_DIR + "gcaves/"
#define PASSWD_TO_THIS_PLACE  "_passwd_to_this_place"
#define ABC ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"})

create_room()
{
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("secret treasure chamber");
    set_long("This is the treasure chamber of the goblin lord. There is nothing "+
             "special here except the fact that this room has no exit. "+
             "And maybe the rune on western wall.\n"+"@@rune_text");

  add_item("rune", "Maybe you can try to read it.\n");
  add_item(({"wall","walls"}),BS("You already know that there is some "+
                                 "magic in western wall.\n"));
}

string
query_rune_text() {
  string password="";
  int i;

    if(TP->query_prop(PASSWD_TO_THIS_PLACE))
      return TP->query_prop(PASSWD_TO_THIS_PLACE);

    for(i=0; i<10; i++)
      password += ABC[random(26)];
    TP->add_prop(PASSWD_TO_THIS_PLACE, password);
    return password;
}

string
rune_text() {
  string rune;

  rune = query_rune_text();
  if(TP->query_prop(PASSWD_TO_THIS_PLACE))
    return "Rune reads:\n     "+rune+"\n";
  if(random(TP->query_skill(SS_LANGUAGE)) > random(30))
    return "Rune reads:\n     "+rune+"\n";
  return "Unfortunately you can't read it.\n";
}

init()
{
    ::init();
    add_action("shout_name", "shout");
    add_action("read_rune", "read");
}

int
read_rune(string rune) {
  string text = rune_text();
  NF("Read what?\n");
  if(rune != "rune") return 0;
  TP->catch_msg(text);
  return 1;
}

int
shout_name(string something)
{
  if(something == (TP->query_prop(PASSWD_TO_THIS_PLACE)))
  {
    TP->catch_msg("You take a deep breath and shout: "+something+"\n"+
                  "Strangely all sound is absorbed by the western wall.\n"+
                  "After the sound, the wall absorbs you too!\n");
    say(QCTNAME(TP)+" takes a deep breath and shouts something. You can't "+
        "tell what it was because the western wall absorbs all sound.\n"+
        "Gasp!!! The wall absorbs "+QTNAME(TP)+" too!\n");
    tell_room(CAVE_DIR+"d11","The eastern wall starts to emit something. "+
                             "Sudenly "+QTNAME(TP)+" is standing here.\n");
    TP->move_living("M",CAVE_DIR+"d11", 1);
    return 1;
   }
  TP->catch_msg("You take a deep breath and shout: "+something+"\n"+
                "Strangely all sound is absorbed by the western wall.\n");
  say(QCTNAME(TP)+" takes a deep breath and shouts something. You can't "+
      "tell what it was because the western wall absorbs all sound.\n");
  return 1;
}
