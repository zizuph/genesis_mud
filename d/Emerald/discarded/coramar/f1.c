#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");
    set_long("   As you gaze down the narrow, moss-covered path "+
             "which descends deeper to the north into the ancient forest, you begin to wonder "+
            "if you should continue. The enormous trees are wider "+
           "than ten men at the narrowest, and unimaginably tall. "+
          "You try and peer up to see their peaks but see nothing "+
          "more than the dark outlines of the branches swaying in "+
     "the cold wind above. The sound of the soft, chill wind "+
          "blowing through the gaps in the trees creates a ghostly "+
           "sound that sends a shiver to the base of your spine. You try "+
           "and see down the path to the north, but you see nothing but "+
           "the dark shadows of the massive gray trunks of the ancient "+
           "trees.\n\n");


    add_fexit(CORAMAR+"f2", "north", 0);
}
