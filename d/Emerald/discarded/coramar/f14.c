#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    set_long("   The forest seems to take on a life of its own as the "+
             "tremendous trunks bend slightly across the path, dropping vines to the floor below "+
             "and littering the forest floor with fallen debris from "+
             "the canopy above. The effect is stifling and creates the "+
             "illusion that the forest is trying to smother the path and "+
             "those on it. Even though the effect is natural, it instills you with a sense "+
             "of wariness and unease. Huge bushes and ferns appear everywhere along "+
             "the forest floor. The thick, slow-moving mist distorts and "+
             "conceals much of the forest beyond your immediate view. "+
             "Ordinarily majestic and towering trees fade into a black "+
             "shadow beyond the veil of the mist. A cool breeze whistles "+
             "across the path, making the hanging vines swing from left "+
             "to right, occasionally brushing up against you.\n\n");

    add_fexit(CORAMAR+"f15", "north", 0);
    add_fexit(CORAMAR+"f13", "east", 0);
}
