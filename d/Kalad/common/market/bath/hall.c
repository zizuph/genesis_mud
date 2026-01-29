inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);

    set_short("Entrance Hall");
    set_long(BS(
      "This is the entrance hall to the baths and saunas " +
      "of the Dirty Swine. The public bath is to the north, " +
      "the public sauna is to the east, the private baths are " +
      "to the northwest, and the private saunas are to the west. " +
      "The lobby is to the south. " +
      "\n"));

    add_prop(MRKT_IN_NO_HEAR,1);

   add_exit(MARKET(bath/lobby),"south",0,-3,-1);/*inside:no tired*/
    add_exit(MARKET(bath/pub_bath),"north","@@n_block",0);
}

/* check to see if player has the right ticket */
n_block()
{
    object *ob;
    int i;

    if (TP->query_invis())
      return 0;

    ob = deep_inventory(TP);

    for (i = 0; i < sizeof(ob); i++)
      if (ob[i]->id("public bath ticket"))
      {
        write(BS(
        "A massive attendant with no neck takes your " +
        "ticket and leads you north to the public bath.\n"));
        say(BS(QCTNAME(TP)+" hands a ticket to a massive attendant.\n"));
        ob[i]->remove_object();
        return 0;
      }

        write(BS(
          "A massive attendant with no neck stops you at the door " +
          "and grunts: 'You don't have a public bath ticket...'" +
           " He scratches his head then says: 'Uhhhh...." +
          "you better go away now'.\n"));
        say(BS(
          QCTNAME(TP)+" tries to leave north but is stopped " +
          "by a massive attendant with no neck.\n"));
        return 1;
}
