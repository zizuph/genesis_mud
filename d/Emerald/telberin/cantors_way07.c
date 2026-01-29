#include "defs.h"

inherit TELBERIN_CANTORS_WAY;

public void
create_cantors_way()
{
    set_em_long("Branching from the Royal Circle to the southwest,"
      + " Cantors Way curves more gradually to the east, where it"
      + " runs the length of a long reflecting pool. The Arts Quarter"
      + " lies in that direction, offering to citizens and travellers"
      + " a taste of the unique culture of the city. Just west of here,"
      + " the Royal Magic Garden blossoms in its sanctuary. The"
      + " road curves markedly to the southwest to join with the Royal"
      + " Circle. Skirting the borders of the garden, one can also"
      + " travel northwest toward Scholars Way.\n");

    add_item( ({ "border", "borders", "border of the garden",
                 "borders of the garden", "sanctuary" }),
        "The garden is well protected, and kept separate from the"
      + " street-level of the city by stone walls.\n");
    add_item( ({ "stone wall", "stone walls", "walls of stone",
                 "garden wall", "garden walls", "walls of the garden",
                 "wall of the garden" }),
        "The wall of the garden is rather tall, allowing only small"
      + " glimpses of what lies beyond.\n");
    add_exit("royal_circle03", "southwest");
    add_exit("cantors_way06", "east");
    add_exit("scholars_way01", "northwest");
}
