#pragma strict_types

inherit "/std/armour";

void
create_armour()
{
    set_name("shirt");
    set_short("sleeping shirt");
    set_long("This is what most orcs sleep in. It has rips "+
             "in various places, as well as a few nice sized holes.\n");
    set_adj("cloth");
    add_adj("stinking");
    add_adj("sleeping");
    
    // No. Worn here is presumably like worn out, but it conflicts with
    // worn/unworn.    Lavellan
    //add_adj("worn"); 

    set_default_armour(2);
}
