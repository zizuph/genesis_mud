#pragma strict_types

inherit "/std/armour";

void
create_armour()
{
    set_name("shirt");
    set_short("stained shirt");
    set_long("This shirt smells almost as bad as it's owner. It has food stains "+
             "in various places, as well as a few nice sized holes.\n");
    set_adj("cloth");
    add_adj("stinking");
    add_adj("stained");
    
    // No. Worn here is presumably like worn out, but it conflicts with
    // worn/unworn.    Lavellan
    //add_adj("worn"); 

    set_default_armour(2);
}
