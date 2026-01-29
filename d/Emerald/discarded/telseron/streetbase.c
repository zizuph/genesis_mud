inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
public void
create_street()
{
}
 
public void
reset_street()
{
}
 
nomask void
create_room()
{
    set_short("Unconfigured street");
    set_long("A street with no description.\n");
 
    add_item("street", "It is a rather dusty street, with some litter here and there.\n");
    add_item("litter",  "There's some paper and some other stuff; the kind "+
         "of garbage you would expect to find on the street in most small "+
         "towns.\n" );
    add_item("castle",  "From this vantage point, it looks like a very "+
         "grand castle indeed; you think the owner must be a pretty rich "+
         "man to be able to afford a castle like that one. Somehow you "+
         "sense that the castle is what protects the township from its "+
         "enemies.\n" );
 
    create_street();
}
 
public void
reset_room()
{
    reset_street();
}
