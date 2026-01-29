inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PLAYER_I_DOWN "player_i_down"
#define PLAYER_II_DOWN "player_ii_down"

create_room()
{
object hatch;
set_long("You are inside a chamber high up in a tower. "+
         "Several large windows facing the sea provides the room with a "+
         "bright pleasant light. Against one of the windows stands a large"+
         " oak desk with a comfortable stuffed chair behind it. The west"+
         " wall is cowered by a bookshelf, collapsing under a huge load of"+
         " books and papers. A sparkling fire burning in a brick fireplace"+
         " warms up the room. On the floor in front of the fireplace is a"+
          " large bear skin. The distant sound from waves breaking in on the"+
         " cliffs below and the crackling noise from the fire gives the room"+
         " a warm and cosy impression.\n");
set_short("Ciryan's chamber");

hatch=clone_object("d/Calia/ciryan/workroom/upper_hatch.c");
hatch->move(this_object());

add_item(({"window","windows"}),"You look out through the windows and get"+
       " an astonishing view over the sea outside. To the east the ocean"+
       " seems to be endless. Far down below you waves break in on the"+
       " rocky shore.\n");
add_item("desk","This large desk is made from oak wood and seems to be"+
       " well used. The surface is almost cowered with a heap of papers"+
" and maps.\n");
add_item("chair","The armchair looks very well used and comfortable, with"+
       " a thick leather stuffing.\n");
add_item("bookshelf","This bookshelf is very large and contains a huge"+
       " amount of different volumes.\n");
add_item(({"books","papers"}),"There are all kinds of books here, most of"+
       " them seem to be very old and read many times.\n");
add_item(({"fireplace","fire"}),"Inside the fireplace burns a large logfire"+
       " which radiates a pleasant heat to the room.\n");
add_item("skin","The large bear skin is black and soft, and looks very"+
       " inviting to lie down on.\n");

}

void
init()
{
::init();

add_action("lie_down","lie");
add_action("stand_up","stand");
add_action("check_lie","down");
add_action("check_lie","d");
}

int

lie_down(string str)
{
notify_fail("Lie where?\n");

if (str=="down" && (query_prop(PLAYER_I_DOWN)==this_player() || query_prop(PLAYER_II_DOWN)==this_player()))
{
this_player()->catch_msg("You are already lying down.\n");
return 1;
}

if ((str=="down")&&(query_prop(PLAYER_I_DOWN)==0))
{
change_prop(PLAYER_I_DOWN,this_player());
this_player()->catch_msg("You lie down on the soft bear skin"+
        " and feel very relaxed. The heat from the fire warms you"+
        " comfortably, making you wish you could stay here a long time.\n");
tell_room(environment(this_player()),QCTNAME(this_player())+
        " lies down on the large bear skin.\n",this_player());
return 1;
}

if (str=="down" && query_prop(PLAYER_I_DOWN)!=0)
{
change_prop(PLAYER_II_DOWN,this_player());
this_player()->catch_msg("You lie down on the soft bear skin beside "+
       query_prop(PLAYER_I_DOWN)+
       " and feel very relaxed. The heat from the fire warms you"+
       " comfortably, making you wish you could stay here a long time.\n");
tell_room(environment(this_player()),QCTNAME(this_player())+
       " lies down on the large bear skin.\n",this_player());
return 1;
}

if (str=="down" && query_prop(PLAYER_I_DOWN)!=0 && query_prop(PLAYER_II_DOWN)!=0)
{
this_player()->catch_msg("There is only place for two on the skin.\n");
return 1;
}
else
return 0;
}

stand_up(string str)
{

notify_fail("You are already standing up.\n");

if (query_prop(PLAYER_I_DOWN)==this_player())
{

change_prop(PLAYER_I_DOWN,query_prop(PLAYER_II_DOWN));
change_prop(PLAYER_II_DOWN,0);
this_player()->catch_msg("With a sigh you stand up from the nice"+
       " warm bear skin.\n");
tell_room(environment(this_player()),QCTNAME(this_player())+
       " stands up from the bear skin.\n",this_player());
return 1;
}

if (query_prop(PLAYER_II_DOWN)==this_player())
{

change_prop(PLAYER_II_DOWN,0);
this_player()->catch_msg("With a sigh you stand up from the nice"+
       " warm bear skin.\n");
tell_room(environment(this_player()),QCTNAME(this_player())+
       " stands up from the bear skin.\n",this_player());
return 1;
}

else
return 0;
}

check_lie()
{

notify_fail("You have to stand up first to do that.\n");

if (query_prop(PLAYER_I_DOWN)==this_player() || query_prop(PLAYER_II_DOWN)==this_player())
{
return 0;
}
return 1;
}
