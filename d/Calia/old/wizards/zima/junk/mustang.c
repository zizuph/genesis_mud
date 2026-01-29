/*  A mustang - gag gift for Mecien */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
     set_name(({"Mustang","mustang"}));
    set_adj("convertible");
    set_adj("red");
    set_adj("toy");
    set_long(break_string(
    "This is a toy car, an exact replica of the 1994 Mustang " +
    "converitble. It is red with a black top, a silver running " +
    "horse ornamenting the grill. You can wind the Mustang with a " +
    "small key on the back. A note attatched reads: TO MECIEN: once " +
    "I move to Indiana, we can go wizzing through the cornfields of the " +
    "Midwest at high speeds and have a great time! FROM ZIMA/P. ;)\n",70));
}
 
init()
{
  add_action("wind_toy", "wind");
}
 
int wind_toy(string cmd)
{
   object ob;                 /* this_player() not accessible in a       */
   ob = this_player();        /* call_out'ed function, so must be passed */
   e  = environment(this_object());
   if (!e->query_prop(ROOM_I_IS))
      write("Put it on the floor and wind it.\n");
   else
      call_out("go_toy",0, ({ob,1}));
   return 1;
}
 
void go_toy(mixed parms)
{
    int step;
    object ob; /* this player */
 
    if (sizeof(parms) != 2) return;
    ob = parms[0];  /* this player */
    set_this_player(ob);
    step =          parms[1];
    room = environment(this_object());
 
    switch (step) {
        case 1: tell_room(room,(
          "You wind the convertible red Mustang and put it on the floor.\n");
          break;
        case 2: tell_room(room,(break_string(
          "The convertible red Mustang begins to "+
          "growl and shrieks its tires as it flies across the floor!\n", 70));
          break;
        case 3: tell_room(room,(break_string(
          "The convertible red Mustang hits the wall with a loud bang, " +
          "angles off, and races across the floor!\n",70));
          break;
        case 4: tell_room(room,(break_string(
          "The convertible red Mustang hits your sore toe with a bone " +
          "crushing sound, angles off, and races across the floor!\n",70));
          break;
        case 5: tell_room(room,(break_string(
          "The convertible red Mustang pops a wheely as it hits the wall, " +
          "angles off, and races toward your feet again!\n",70));
          break;
        case 6:
            tell_room(room,(break_string(
            "The convertible red Mustang screeches to a halt below your " +
            "feet an growls gently.\n",70));
            return;
            break;
    }
    call_out("go_toy",3,({ob,step+1}));
}
