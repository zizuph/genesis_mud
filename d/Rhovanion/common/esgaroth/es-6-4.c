inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-4", "west");
    set_extras("The owner of this house seems to have chosen this spot " +
        "to live because of its proximity to the pub.  Empty glass bottles " +
        "lie strewn across the floor here.\n");
    add_item("bottles", "These bottles are the evidence of the drinker's " +
        "fondness for alcohol.\n");
}
