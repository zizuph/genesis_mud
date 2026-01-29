
 /*           Calian Elevator

   coder(s):     Digit
                 Glykron
   history:
                23 MAY 95    added add_item    Digit
                 12/5/95     typos removed                  Maniac
                 23/2/95     added remove_exit statements, room
                             descriptions - Digit
                 19/2/95     added movement routine - Glykron
                 19/2/95     created - Digit
   purpose:      Take players up to Hallway
   exits:        Out at bottom, players forced out at top.
   objects:      button (can only be pressed)
   npcs:         none
   quests:       none
   special:      When button is pressed, elevator moves up and kicks
                 players out at top
   to do:        add mule sounds to moving description
   bugs:         none known
 */

#pragma save_binary

inherit "/std/room";
#include <macros.h>
#include <filter_funs.h>

#include "/d/Calia/domain.h"

#define TOP "/d/Calia/mountain/cr_tunnel/rooms/hallway"
#define BOTTOM "/d/Calia/mountain/lower_tunnel/tun11"
#define ELEVATOR "/d/Calia/mountain/lower_tunnel/elevator"

int bp, id;

void
create_room()
{
    bp = 0;

    set_short("In an elevator");
    set_long("This chamber seems to be a wooden structure that "+
       "has been quickly thrown together.  There is a button on "+
       "one wall and a set of wooden panels which you assume are "+
       "supposed to be doors in the south wall.\n");

    add_item("button","It looks just like a little black button "+
       "that you could press.  Why don't you press it and find out "+
       "what it does?\n");

    add_item(({"panel","panels"}),"These wooden panels seem to slide open "+
       "and closed somehow.  They don't look very strong.\n");
    add_exit(BOTTOM, "out");

}

void
init()
{
    ::init();
    add_action("push_button","press");
    add_action("push_button","push");
}

push_button(string str)
{
    if (str != "button")
    {
    NF("Press what?\n");
    return 0;
    }
    if (bp >= 1)
    {
       write("Someone has already pushed the button.  Be patient!\n");
       say(QCTNAME(TP)+" tries to make the elevator go faster by "+
          "pressing the button again, but fails miserably.\n");
       return 1;
    }
    bp = 1;
    write("You press the button and the panels close.  The room "+
       "begins to rumble and shake.  You feel it start to move "+
       "upwards, banging against the walls as it does.  You feel "+
       "as if you may have made a big mistake.\n");
    say(QCTNAME(TP)+ " presses the button and the panels close.  "+
       "The room begins to rumble and shake, and begins to move "+
       "upwards, banging against the walls as it does.  You think "+
       "that "+TP->query_pronoun()+" has made a big mistake.\n");

    tell_room(BOTTOM,"The opening "+
       "in the north wall suddenly closes.  Strange noises come "+
       "from behind it.\n");

    remove_exit("out");
    BOTTOM->remove_exit("opening");
    id = set_alarm(1.0, 3.5, "move_elevator");

    return 1;
}

void
move_elevator()
{
    object *objs;
    int i;
    if (bp !=8)
    {
    tell_room(THIS, "The room continues to rumble and bang "+
       "against the walls.\n");
    ++bp;
    return;
    }
    tell_room(THIS,"\nThe room stops moving and the panels in "+
       "the south wall suddenly open up.  You decide that you "+
       "want to get out as soon as possible and step out.\n\n");
    tell_room(TOP,"Wooden panels in the north wall open up.\n");
    objs = FILTER_LIVE(all_inventory(THIS));
    for (i = 0; i < sizeof(objs); ++i)
    {
    objs[i]->catch_msg("As you step away from the moving room, "+
       "it completely falls apart and tumbles down the blackened "+
       "shaft which you assume you just came up.  Good thing you "+
       "got out when you did!\n\n");
    tell_room(TOP,QCTNAME(objs[i])+ " steps out of the north wall.\n");
    objs[i]->move_living("M",TOP);
    }
    remove_alarm(id);
    tell_room(BOTTOM,"You hear a "+
       "tremendous noise from behind the north wall which sounds "+
       "suspiciously like something heavy falling.  Two gnomes "+
       "appear out of the shadows, open the wall, quickly assemble "+
       "something and return to the shadows where they were "+
       "hiding before.\n");
    bp = 0;
    add_exit(BOTTOM,"out");
    BOTTOM->add_exit(ELEVATOR,"opening",0,0);
}
