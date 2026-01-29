#include "defs.h"

inherit TELBERIN_CHANNELERS_WAY;

public void
create_channelers_way()
{
    set_em_long("Running in a long, narrow ellipse, Channelers Way"
      + " travels between the Royal Circle to the north and the"
      + " Magic Quarter to the south. Just northeast, the street"
      + " curves markedly as it approaches the Palace. South of here,"
      + " it arcs gradually alongside a slender reflecting pool"
      + " which extends between the Tower of Telan-Ri and Channelers"
      + " Plaza. Directly to the north, a large gazebo rests before"
      + " the confines of the Royal Fruit Garden.\n");

    add_item( ({ "border", "borders", "border of the garden",
                 "borders of the garden", "sanctuary", "confines" }),
        "The garden is well protected, and kept separate from the"
      + " street-level of the city by stone walls.\n");
    add_item( ({ "stone wall", "stone walls", "walls of stone",
                 "garden wall", "garden walls", "walls of the garden",
                 "wall of the garden" }),
        "The wall of the garden is rather tall, allowing only small"
      + " glimpses of what lies beyond.\n");
    add_item( ({ "gazebo", "large gazebo" }),
        "The gazebo which stands before the walls of the garden is"
      + " white, and elegantly framed. From a distance, it is easy"
      + " to mistake how truly large a structure it is. There are"
      + " people coming and going from within it.\n");

    add_exit("channelers_way02", "south");
    add_exit("royal_circle04", "northeast");
    add_exit("artisans_way07", "northwest");
    add_exit("/d/Emerald/telberin/gazebo", "north", 0, 1, 1);

    add_building("/d/Emerald/telberin/gazebo");
}
