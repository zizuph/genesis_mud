
/*
 *    coded by Amelia
 *    the rock which the mermaid sits on;)
 *    coded 8/7/95
 *    Modifications by Maniac 6/9/96 
 */


inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#include SEA_QUESTS

object mermaid;

void
reset_room()
{
    if (!objectp(mermaid)) {
            mermaid = clone_object(SEA_CREATURES+"mermaid");
            mermaid->move_living("onto the rock", this_object());
    }
}


void
create_room()
{
    set_short("A large rock in the sea");
    set_long("This is a large granite rock that juts out "+
        "above the water, and it's fairly dry here. "+
        "You have an excellent view of the harbour area "+
        "to the north, and the sea extends all the way to the horizon. "+
        "Way to the southeast you see a large mountain. Back to "+
        "the east is the white sandy beach. This rock is "+
        "part of a line of rocks that extends out into the "+
        "sea.\n");

   add_item((({"rock", "line of rocks", "granite rock"})),
      "The large, somewhat flat granite rock you are sitting on "+
      "is part of a line of rocks, which extends out from the "+
      "shore into the sea. It forms a natural barrier for the "+
      "harbour.\n");

   add_item((({"sea", "water"})),
      "The blue-green Calian sea is all around you. The "+
      "water appears very clear, but darker blue as it gets "+
      "deeper. You can safely dive back in from this rock.\n");

   add_item((({"harbour", "harbour area"})),
     "To the north you can see the harbour area of Gelan, "+
      "where ships arrive and leave every now and then. "+
      "There is a lot of activity there.\n");

   add_item((({"mountain", "large mountain"})),
      "Far to the southeast, mighty Kyrus dominates the horizon.\n");

   add_item((({"beach", "white sandy beach"})),
      "At some distance to the east you see the shoreline "+
      "and white sandy beach.\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_STEAL,1);

    reset_room();
}


void
ring_restore(object player)
{
    object ring;

    if (objectp(player) && objectp(present(player, this_object()))) { 
         if (!player->test_bit(MERMQ_DOMAIN, MERMQ_GROUP, MERMQ_BIT))
             return;
         if (objectp(ring = present(MERMQ_RING_ID, player)))  
             return;
         ring = clone_object(SEA_OBJECTS+"mermaid_ring");  
         if (!ring->move(player)) { 
             player->catch_msg(capitalize(LANG_ASHORT(ring)) + 
                      " appears in your inventory!\n"); 
             player->catch_msg("If you ever lose your ring, " +
                               "just return here and it " +
                               "will be restored to you.\n"); 
             return;
         }
         player->catch_msg(capitalize(LANG_ASHORT(ring)) +  
                 " tries to appear in your inventory but" +
                 " doesn't find any room!\n"); 
         ring->remove_object(); 
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (interactive(ob)) 
        set_alarm(1.0, 0.0, &ring_restore(ob)); 
}


int
dive_in(string str)
{
    object tp = this_player();

    notify_fail("Dive where?\n");
    if (str == "down" || str == "in" || str == "in water" ||
      str == "back" || str == "down rock") {
            tp->catch_msg("You dive back into the water!\n"); 
            tell_room(environment(tp), QCTNAME(tp) + " dives " + 
                      "back into the water!\n", tp); 
            tp->move_living("M", ROCK_ROOM, 1);
            write("Splash!\n");
            tell_room(environment(tp), "Splash! "+QCTNAME(tp)+
                " dives in!\n", tp);
            return 1;
     }
    return 0;
}


void
init()
{
    ::init();
    add_action(dive_in, "climb");
    add_action(dive_in, "dive");
}

