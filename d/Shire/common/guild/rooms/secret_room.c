/*
 *  A secret guild room to reward someone for having joined 
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "/d/Shire/open/randomize.h"
#include "defs.h"

create_room() {
  int i;

  set_short("secret room");
  set_long("@@my_long");
  add_item(({"button", "buttons"}), "@@all_buttons_desc");
  for (i = 0; i < sizeof(COLOURS); i++)
    add_item(COLOURS[i] + " button", "@@button_desc");
  add_prop(ROOM_I_INSIDE, 1);  /* This room is inside */
}

my_long() {
  return break_string(
    "You have arrived in a secret room carefully hidden in the rocks. "+
    "Since you have just joined the Hin Warrior guild, the great Nob "+
    "Nar would like to show you his gratitude of extraordinary "+
    "magnitude. As in a dream, you hear his voice: 'There are 20 buttons "+
    "spread all over this room. If you press the right button, you will "+
    "receive a gift. But be cautious: the wrong button will open a trap-"+
    "door that will always be situated right beneath you...'.\n", 70);
}

all_buttons_desc() {
  string colstr;
  int i;

  colstr = "";
  for (i = 0; i < sizeof(COLOURS)-1; i++) colstr += COLOURS[i]+", ";
  colstr += "and " + COLOURS[sizeof(COLOURS)-1];
  return break_string(
    "You examine the place and count exactly " + sizeof(COLOURS) +
    " buttons; all of a different colour. You see a " + colstr +
    " button.\n", 70);
}

button_desc() {
  switch(random(3)) {
    case 0: return "You don't see anything special about it.\n";
    case 1: return "It looks like it's pressed very often.\n";
    case 2: return "You notice an ominous aura surrounding it.\n";
  }
}

init() {
  ::init();
  add_action("do_press", "press");
  add_action("do_press", "push");
}

do_press(str) {
  object obj;
  string color;
  int ran;

  if (!str) {
    notify_fail("Press what?\n");
    return 0;
  }
  if (str == "buttons") {
    notify_fail("All at once? You can't do that.\n");
    return 0;
  }
  if (str == "button") {
    notify_fail("Which one?\n");
    return 0;
  }
  if (!sscanf(str, "%s button", color)) {
    if (member_array(str, COLOURS) == -1) {
      notify_fail("The only pressable things you see are buttons.\n");
      return 0;
    }
    color = str;
  }
  if (color == "a") {
    color = random_colour();
    write(break_string(
     "You close your eyes and press a button. Wondering which button you "+
     "have pressed, you open your eyes again and see it's a " + color +
     " one.\n", 70));
  }
  else {
    if (member_array(color, COLOURS) == -1) {
      notify_fail("There is no such button.\n");
      return 0;
    }
    write("You press the " + color + " button.\n");
  }
  seteuid(getuid());
  say(QCTNAME(this_player()) + " presses the " + color + " button.\n");
  ran = random(10);
  if (ran > 4) {      /* 50% chance */
    tell_room(this_room(), "Nothing happens.\n");
    return 1;
  }
  if (ran > 1) {      /* 30% chance */
    switch(random(3)) {
      case 0: obj = clone_object(OBJ_DIR + "secret_object");
              obj->move(this_room());
              break;
      case 1: obj = clone_object(ARM_DIR + "secret_armour");
              obj->move(this_room());
              break;
      case 2: obj = clone_object(WEP_DIR + "secret_weapon");
              obj->move(this_room());
    }
    tell_room(this_room(), break_string(
      "Something suddenly materializes at your feet. Because of the smoke " +
      "coming from it, you are having trouble identifying the object. " +
      "When the smoke clears, you see " + LANG_ADDART(obj->short()) +
      " lying on the floor.\n",70));
    return 1;
  }
  tell_room(this_room(), "A trap-door opens.\n");
  write(break_string("You fall down a huge tunnel... and land hard on a very "+
    "familiar looking floor.\n", 70));
  say(QCTNAME(this_player()) + " disappears through the trap-door.\n");
  this_player()->move(HINROOM_DIR + "hguild");
  tell_room(environment(this_player()), QCTNAME(this_player()) +
    " falls down from above you and lands on the floor the hard way.\n",
    this_player());
  return 1;
}
