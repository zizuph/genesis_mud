/* A grapefruit for the new VK, modified by Teth Dec 6 1996 */

inherit "/std/food";

public void
create_food()
{
    set_name("grapefruit");
    add_name(({"fruit","food"}));
    set_pname("grapefruits");
    add_pname(({"fruits","foods"}));
    set_adj("ripe");
    add_adj("grape");
    set_short("ripe grapefruit");
    set_pshort("ripe grapefruits");
    set_long("This is a plump ripe grapefruit, undoubtedly " +
        "juicy and quite tasty. Grapefruits aren't native to " +
        "Solamnia, so it must be imported.\n");
    set_amount(111);
}
