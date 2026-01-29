/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Computing Department");
    set_long("This is a very strange room. You can see about 20 people "
           + "sitting each in front of a little desk with a strange "
           + "apparatus in their hands. There is quite some noise in this "
           + "room, a lot of clicking and clacking.\n");

    add_exit(PALACE + "hall2","west",0,0);

    add_item(({"people"}),"They are mostly gnomes here since gnomes are so "
          +  "fascinated with mechanics.\n");
    add_item(({"apparatus"}),"It appears all the apparati are the same, each "
          +  "is an abacus really.\n");
    add_item(({"desk","desks","chair","chairs"}),"The desks and chairs are "
          +  "very small, fitting for a gnome though. You can see lots of "
          +  "parchment piling up on each desk.\n");
    add_item(({"paper","papers","parchment","parchments"}),"Very strange "
          +  "symbols and signs fill each one of the papers, hmmm...\n");
    add_item(({"symbol","symbols","sign","signs"}),"You just cannot make any"
          +  "thing sensible of it.\n");
}



