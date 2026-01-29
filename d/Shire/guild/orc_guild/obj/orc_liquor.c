/* 
	*Strange brew, eh?
	*Altrus, May 2005
*/

inherit "/std/drink";

void create_drink()
{
        set_name("liquor");
        set_pname("liquors");
	set_short("orcish liquor");
        set_pshort("orcish liquors");
        set_adj("orcish");
        set_long("This is an extremely potent concoction made by orcs. Don't drink it unless you mean business.\n");
        set_soft_amount(50);
        set_alco_amount(65);
        
}
