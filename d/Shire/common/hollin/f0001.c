#include "forest.h"

create_forest()
{
    set_short("A gloomy forest");
    set_long(
	"You are in a dark and gloomy forest in Eregion. Here also, "+
	"the trees are incredibly large and you feel small in "+
	"the presence of these old beings. You wonder how large "+
	"this forest really is. And how old! On a particular "+
	"root of tree you notice that someone has broken it - "+
	"though you've got no idea on why it is done. "+
	"You could go almost in all directions here, but a large tree "+
	"have fallen down in the west, so you would have to go around "+
	"it if you wanted that direction.\n");

    ADD_EXA("tree,large tree", "It is very large, so you would never get around it.");
    ADD_EXA("root,root of tree", "Well, surely someone did it, but you wouldn't.");

    SOUTH("f0000");
    NORTH("f0002");
    NORTHEAST("f0102");
    EAST("f0101");
    SOUTHEAST("f0100");
}
