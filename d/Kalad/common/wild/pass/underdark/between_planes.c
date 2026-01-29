/* 
 * /d/Kalad/common/wild/pass/underdark/between_planes.c
 * Purpose    : This is the room where the deep dragon goes to get the swords he needs for a quest. There is a secret command to enter this room, known to no mortals.
 * Located    : In the underdark
 * Created By : Antharanos ??.??.??
 * Mofied By: Nikklaus, Oct'97: also adapted to dark_dom inherit
 */ 

# pragma strict_types
# include "dark_dom.h"
# include <stdproperties.h>

inherit DARK_DOM;

void
create_dark_dom()
{
    add_prop(ROOM_I_LIGHT, 1);
    set_short("Somewhere in the void between planes");
    set_long("You are within a void that seems to stretch on into "+
      "infinity, its regularity broken only by the nearly "+
      "indistinguishable horizon line in the far distance.\n");
    add_item(({"void"}),"It is nearly featureless.\n");
    add_item(({"horizon line","line"}),"A tiny and dark line in the "+
      "distance.\n");
    add_exit(DARK(between_planes), "west", 0, 0, 0);
    add_exit(DARK(between_planes), "northwest", 0, 0, 0);
    add_exit(DARK(between_planes), "north", 0, 0, 0);
    add_exit(DARK(between_planes), "northeast", 0, 0, 0);
    add_exit(DARK(between_planes), "east", 0, 0, 0);
    add_exit(DARK(between_planes), "southeast", 0, 0, 0);
    add_exit(DARK(between_planes), "south", 0, 0, 0);
    add_exit(DARK(between_planes), "soutwest", 0, 0, 0);
    add_exit(DARK(u37), "back", 0, -1, 0);
    clone_object(SW_SOLARA)->move(this_object());
    clone_object(SW_SOLARA)->move(this_object());
    clone_object(SW_SOLARA)->move(this_object());
    clone_object(SW_SOLARA)->move(this_object());
    clone_object(SW_SOLARA)->move(this_object());
}
