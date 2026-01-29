/* 
	*Strange brew, eh?
	*Altrus, May 2005
*/

inherit "/std/drink";

void create_drink()
{
        set_name("brew");
        set_pname("brews");
	add_name("mug");
	add_pname("mugs");
        set_short("mug of strange brew");
        set_pshort("mugs of strange brew");
        set_adj(({"mug of", "strange"}));
        set_long("This mug contains a very strange-looking drink. It's some powerful brew, eh?\n");
        set_soft_amount(110);
        set_alco_amount(20);
        
}
