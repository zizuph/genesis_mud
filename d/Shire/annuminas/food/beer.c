
inherit "/std/drink";

void
create_drink()
{
        set_name("beer");
        add_name("pint");
        add_name("pint of beer");
        set_pname("beers");
        add_pname("pints");
        add_pname("pints of beers");
        set_short("pint of beer");
        set_pshort("pints of beer");
        set_long("It's a pine of watered down beer. It's not as good as " +
            "the good stuff, but drunks won't notice the difference.\n");
        set_soft_amount(75);
        set_alco_amount(20);
        
}
